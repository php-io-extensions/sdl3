<?php

declare(strict_types=1);

it('opens the GPU device the platform has', function (): void {
    expect(SDL_GetGPUDeviceDriver(gpu()))->toBe(PHP_OS_FAMILY === 'Darwin' ? 'metal' : 'vulkan')
        ->and(SDL_GetGPUShaderFormats(gpu()) & (PHP_OS_FAMILY === 'Darwin' ? SDL_GPU_SHADERFORMAT_MSL : SDL_GPU_SHADERFORMAT_SPIRV))->not->toBe(0)
        ->and(SDL_GPUTextureSupportsSampleCount(gpu(), SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM, SDL_GPU_SAMPLECOUNT_4))->toBeTrue()
        ->and(SDL_GPUTextureSupportsFormat(gpu(), SDL_GPU_TEXTUREFORMAT_D24_UNORM_S8_UINT, SDL_GPU_TEXTURETYPE_2D, SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET)
            || SDL_GPUTextureSupportsFormat(gpu(), SDL_GPU_TEXTUREFORMAT_D32_FLOAT_S8_UINT, SDL_GPU_TEXTURETYPE_2D, SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET))->toBeTrue();
});

it('uploads a texture and downloads it again through transfer buffers', function (): void {
    $bytes = random_bytes(4 * 2 * 4);
    $texture = gpuTexture(4, 2, SDL_GPU_TEXTUREUSAGE_SAMPLER);
    $up = transferBuffer(32, SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD);
    $down = transferBuffer(32, SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD);
    writeMapped($up, $bytes);

    $region = new SDL_GPUTextureRegion();
    $region->texture = $texture;
    [$region->w, $region->h, $region->d] = [4, 2, 1];
    $from = new SDL_GPUTextureTransferInfo();
    $from->transfer_buffer = $up;
    $to = new SDL_GPUTextureTransferInfo();
    $to->transfer_buffer = $down;

    $commands = SDL_AcquireGPUCommandBuffer(gpu());
    $copy = SDL_BeginGPUCopyPass($commands);
    SDL_UploadToGPUTexture($copy, $from, $region, false);
    SDL_DownloadFromGPUTexture($copy, $region, $to);
    SDL_EndGPUCopyPass($copy);
    $fence = SDL_SubmitGPUCommandBufferAndAcquireFence($commands);

    expect(SDL_WaitForGPUFences(gpu(), true, [$fence]))->toBeTrue()
        ->and(SDL_QueryGPUFence(gpu(), $fence))->toBeTrue()
        ->and(readMapped($down, 32))->toBe($bytes)
        ->and(fn () => SDL_SubmitGPUCommandBuffer($commands))->toThrow(ValueError::class, 'SDL_GPUCommandBuffer has been destroyed');

    SDL_ReleaseGPUFence(gpu(), $fence);
    SDL_ReleaseGPUTransferBuffer(gpu(), $up);
    SDL_ReleaseGPUTransferBuffer(gpu(), $down);
    SDL_ReleaseGPUTexture(gpu(), $texture);
});

it('uploads a buffer, makes a sampler, cancels a command buffer and waits for idle', function (): void {
    $info = new SDL_GPUBufferCreateInfo();
    $info->usage = SDL_GPU_BUFFERUSAGE_VERTEX;
    $info->size = 16;
    $buffer = SDL_CreateGPUBuffer(gpu(), $info);
    $up = transferBuffer(16, SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD);
    writeMapped($up, str_repeat("\x01", 16));
    $source = new SDL_GPUTransferBufferLocation();
    $source->transfer_buffer = $up;
    $destination = new SDL_GPUBufferRegion();
    $destination->buffer = $buffer;
    $destination->size = 16;

    $commands = SDL_AcquireGPUCommandBuffer(gpu());
    $copy = SDL_BeginGPUCopyPass($commands);
    SDL_UploadToGPUBuffer($copy, $source, $destination, false);
    SDL_EndGPUCopyPass($copy);

    expect(SDL_SubmitGPUCommandBuffer($commands))->toBeTrue()
        ->and(SDL_CancelGPUCommandBuffer(SDL_AcquireGPUCommandBuffer(gpu())))->toBeTrue()
        ->and(SDL_CreateGPUSampler(gpu(), new SDL_GPUSamplerCreateInfo()))->toBeInstanceOf(SDL_GPUSampler::class)
        ->and(SDL_WaitForGPUIdle(gpu()))->toBeTrue();

    SDL_ReleaseGPUTransferBuffer(gpu(), $up);
    SDL_ReleaseGPUBuffer(gpu(), $buffer);
});

it('refuses a fence list holding something else', function (): void {
    SDL_WaitForGPUFences(gpu(), true, ['not a fence']);
})->throws(TypeError::class);
