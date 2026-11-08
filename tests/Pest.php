<?php

declare(strict_types=1);

if (! extension_loaded('sdl3')) {
    throw new RuntimeException('The sdl3 extension is not loaded; run ./install-macos.sh or ./install-debian-trixie.sh');
}

/** Video up once for the whole run; SDL_Quit() runs at shutdown. */
function video(): void
{
    static $up = false;
    if (! $up) {
        SDL_Init(SDL_INIT_VIDEO) || throw new RuntimeException('SDL_Init: ' . SDL_GetError());
        register_shutdown_function('SDL_Quit');
        $up = true;
    }
}

/** macOS signal numbers a kept refusal's probe dies by. */
const PROBE_SIGBUS = 10;
const PROBE_SIGSEGV = 11;

/** Skips a tests/Probes test unless the loaded ext-sdl3 is a probe build (--enable-sdl3-probes). */
function requireProbeBuild(): void
{
    if (! defined('SDL3_PROBES')) {
        test()->markTestSkipped('ext-sdl3 is not a probe build (configure --enable-sdl3-probes): SDL3_PROBES is undefined');
    }
}

/**
 * Runs $code in a child of this PHP with only ext-sdl3 loaded and video up. $siteOff names the kept
 * site SDL3_PROBE_OFF turns off, null keeps every site. $gmalloc runs the child under libgmalloc with
 * Zend's allocator off, so a native over-read of PHP memory faults at the guard page.
 *
 * @return array{signal: ?int, stdout: string}
 */
function sdl3Probe(string $code, ?string $siteOff, bool $gmalloc = false): array
{
    $script = "<?php\ndeclare(strict_types=1);\nSDL_Init(SDL_INIT_VIDEO);\ntry {\n".$code."\n} catch (Throwable \$t) {\n    echo 'REFUSED ', get_class(\$t), ': ', \$t->getMessage(), \"\\n\";\n}\necho \"SURVIVED\\n\";\n";
    $file = tempnam(sys_get_temp_dir(), 'sdl3-probe');
    file_put_contents($file, $script);

    $env = getenv();
    unset($env['SDL3_PROBE_OFF'], $env['DYLD_INSERT_LIBRARIES'], $env['USE_ZEND_ALLOC']);
    $env['XDEBUG_MODE'] = 'off';
    if ($siteOff !== null) {
        $env['SDL3_PROBE_OFF'] = $siteOff;
    }
    if ($gmalloc) {
        $env['DYLD_INSERT_LIBRARIES'] = '/usr/lib/libgmalloc.dylib';
        $env['USE_ZEND_ALLOC'] = '0';
    }

    $command = [PHP_BINARY, '-n', '-d', 'memory_limit=128M', '-d', 'extension='.ini_get('extension_dir').'/sdl3.so', $file];
    $process = proc_open($command, [0 => ['file', '/dev/null', 'r'], 1 => ['pipe', 'w'], 2 => ['file', '/dev/null', 'w']], $pipes, null, $env);
    $stdout = (string) stream_get_contents($pipes[1]);
    fclose($pipes[1]);
    do {
        $status = proc_get_status($process);
        if ($status['running']) {
            usleep(20_000);
        }
    } while ($status['running']);
    proc_close($process);
    @unlink($file);

    return ['signal' => $status['signaled'] ? $status['termsig'] : null, 'stdout' => $stdout];
}

function hiddenWindow(int $flags = 0): SDL_Window
{
    video();

    return SDL_CreateWindow('ext-sdl3 test', 160, 120, SDL_WINDOW_HIDDEN | $flags)
        ?? throw new RuntimeException('SDL_CreateWindow: '.SDL_GetError());
}

function gpu(): SDL_GPUDevice
{
    static $device = null;
    if ($device === null) {
        video();
        $device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_SPIRV, false, null)
            ?? throw new RuntimeException('SDL_CreateGPUDevice: '.SDL_GetError());
        register_shutdown_function(static function () use ($device): void {
            SDL_DestroyGPUDevice($device);
        });
    }

    return $device;
}

function gpuTexture(int $w, int $h, int $usage, int $samples = SDL_GPU_SAMPLECOUNT_1, int $format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM): SDL_GPUTexture
{
    $info = new SDL_GPUTextureCreateInfo();
    $info->type = SDL_GPU_TEXTURETYPE_2D;
    $info->format = $format;
    $info->usage = $usage;
    $info->width = $w;
    $info->height = $h;
    $info->layer_count_or_depth = 1;
    $info->num_levels = 1;
    $info->sample_count = $samples;

    return SDL_CreateGPUTexture(gpu(), $info)
        ?? throw new RuntimeException('SDL_CreateGPUTexture: '.SDL_GetError());
}

function transferBuffer(int $size, int $usage): SDL_GPUTransferBuffer
{
    $info = new SDL_GPUTransferBufferCreateInfo();
    $info->usage = $usage;
    $info->size = $size;

    return SDL_CreateGPUTransferBuffer(gpu(), $info)
        ?? throw new RuntimeException('SDL_CreateGPUTransferBuffer: '.SDL_GetError());
}

function writeMapped(SDL_GPUTransferBuffer $buffer, string $bytes): void
{
    $address = SDL_MapGPUTransferBuffer(gpu(), $buffer, false);
    if ($address === 0) {
        throw new RuntimeException('SDL_MapGPUTransferBuffer: '.SDL_GetError());
    }
    $io = SDL_IOFromMem($address, strlen($bytes));
    $written = SDL_WriteIO($io, $bytes, strlen($bytes));
    SDL_CloseIO($io);
    SDL_UnmapGPUTransferBuffer(gpu(), $buffer);
    if ($written !== strlen($bytes)) {
        throw new RuntimeException('SDL_WriteIO wrote '.$written.' of '.strlen($bytes));
    }
}

function readMapped(SDL_GPUTransferBuffer $buffer, int $size): string
{
    $address = SDL_MapGPUTransferBuffer(gpu(), $buffer, false);
    if ($address === 0) {
        throw new RuntimeException('SDL_MapGPUTransferBuffer: '.SDL_GetError());
    }
    $io = SDL_IOFromConstMem($address, $size);
    $bytes = readIO($io, $size);
    SDL_CloseIO($io);
    SDL_UnmapGPUTransferBuffer(gpu(), $buffer);

    return $bytes;
}

/** $size bytes read with SDL_ReadIO into an ext-fb buffer, which gives the address it writes to. */
function readIO(SDL_IOStream $io, int $size): string
{
    $into = new FbBuffer(new FbFormat(FB_LAYOUT_RGBA8888, channelOrder: FB_CHANNELS_RGBA), max(1, intdiv($size + 3, 4)), 1);
    $got = SDL_ReadIO($io, $into->pointer(), $size);

    return substr($into->bytes(), 0, $got);
}

/**
 * Pumps until $until accepts an event or $seconds pass; answers the event types seen.
 *
 * @return list<int>
 */
function pumpEvents(?Closure $until = null, float $seconds = 0.5): array
{
    $seen = [];
    $event = new SDL_Event();
    $deadline = hrtime(true) + (int) ($seconds * 1e9);

    while (hrtime(true) < $deadline) {
        while (SDL_PollEvent($event)) {
            $seen[] = $event->type;
            if ($until !== null && $until($event)) {
                return $seen;
            }
        }
        usleep(5_000);
    }

    return $seen;
}

function driver(): string
{
    video();

    return SDL_GetCurrentVideoDriver() ?? '';
}

/** The window's NSWindow, as ext-appkit holds it. */
function nsWindowOf(SDL_Window $window): NSWindow
{
    return NSWindow::fromPointer(SDL_GetPointerProperty(SDL_GetWindowProperties($window), SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, null));
}
