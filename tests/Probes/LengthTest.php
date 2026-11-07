<?php

declare(strict_types=1);

// Sites sdl3-surface-pixels-length, sdl3-uniform-length and sdl3-write-io-length (outcome 1): SDL reads
// the byte count the caller gives from the string. A count past the string makes it read past the end of
// PHP's memory. The child runs under libgmalloc, so the over-read faults at the guard page.

beforeEach(fn () => requireProbeBuild());

it('refuses surface pixels shorter than pitch × height, which SDL reads past (SIGSEGV) without the refusal', function (): void {
    // 376840196 is SDL_PIXELFORMAT_RGBA8888.
    $code = <<<'PHP'
        $surface = SDL_CreateSurfaceFrom(256, 256, 376840196, 'ab', 1024);
        $window = SDL_CreateWindow('probe', 256, 256, SDL_WINDOW_HIDDEN);
        SDL_BlitSurface($surface, null, SDL_GetWindowSurface($window), null);
    PHP;

    $kept = sdl3Probe($code, null, gmalloc: true);
    $off = sdl3Probe($code, 'sdl3-surface-pixels-length', gmalloc: true);

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError: SDL_CreateSurfaceFrom(): Argument #4 ($pixels) must hold')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});

it('refuses uniform data shorter than its length, which SDL copies past (SIGSEGV) without the refusal', function (): void {
    $code = <<<'PHP'
        $device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_SPIRV, false, null);
        $commands = SDL_AcquireGPUCommandBuffer($device);
        try {
            SDL_PushGPUVertexUniformData($commands, 0, 'ab', 1 << 16);
        } finally {
            SDL_CancelGPUCommandBuffer($commands);
        }
    PHP;

    $kept = sdl3Probe($code, null, gmalloc: true);
    $off = sdl3Probe($code, 'sdl3-uniform-length', gmalloc: true);

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});

it('refuses a write size past the string, which SDL copies past (SIGSEGV) without the refusal', function (): void {
    $code = <<<'PHP'
        $memory = SDL_IOFromMem(SDL_CreateSurfaceFrom(64, 64, 376840196, str_repeat("\0", 64 * 256), 256)->pixels(), 64 * 256);
        SDL_WriteIO($memory, 'ab', 8192);
    PHP;

    $kept = sdl3Probe($code, null, gmalloc: true);
    $off = sdl3Probe($code, 'sdl3-write-io-length', gmalloc: true);

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError: SDL_WriteIO(): Argument #2 ($ptr) must hold')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});
