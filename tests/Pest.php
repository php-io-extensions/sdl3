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
    $bytes = SDL_ReadIO($io, $size);
    SDL_CloseIO($io);
    SDL_UnmapGPUTransferBuffer(gpu(), $buffer);

    return $bytes;
}
