<?php

declare(strict_types=1);

function gpuBuffer(int $size, int $usage): SDL_GPUBuffer
{
    $info = new SDL_GPUBufferCreateInfo();
    $info->usage = $usage;
    $info->size = $size;

    return SDL_CreateGPUBuffer(gpu(), $info)
        ?? throw new RuntimeException('SDL_CreateGPUBuffer: '.SDL_GetError());
}

function submitAndWait(SDL_GPUCommandBuffer $commands): void
{
    $fence = SDL_SubmitGPUCommandBufferAndAcquireFence($commands)
        ?? throw new RuntimeException('SDL_SubmitGPUCommandBufferAndAcquireFence: '.SDL_GetError());
    SDL_WaitForGPUFences(gpu(), true, [$fence], 1);
    SDL_ReleaseGPUFence(gpu(), $fence);
}

it('names each GPU backend SDL was built with and the shader formats it takes', function (): void {
    video();
    $names = [];
    for ($i = 0; $i < SDL_GetNumGPUDrivers(); $i++) {
        $names[] = SDL_GetGPUDriver($i);
    }
    $platform = PHP_OS_FAMILY === 'Darwin' ? 'metal' : 'vulkan';
    $format = PHP_OS_FAMILY === 'Darwin' ? SDL_GPU_SHADERFORMAT_MSL : SDL_GPU_SHADERFORMAT_SPIRV;

    expect($names)->toContain($platform)
        ->and(SDL_GetGPUDriver(count($names)))->toBeNull()
        ->and(SDL_GPUSupportsShaderFormats($format, $platform))->toBeTrue()
        ->and(SDL_GPUSupportsShaderFormats($format, null))->toBeTrue()
        ->and(SDL_GPUSupportsShaderFormats(SDL_GPU_SHADERFORMAT_DXIL, $platform))->toBeFalse();
});

it('copies part of one buffer into another and downloads it', function (): void {
    $bytes = random_bytes(16);
    $from = gpuBuffer(16, SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_READ);
    $to = gpuBuffer(8, SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_READ);
    $up = transferBuffer(16, SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD);
    $down = transferBuffer(8, SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD);
    writeMapped($up, $bytes);

    $upSource = new SDL_GPUTransferBufferLocation();
    $upSource->transfer_buffer = $up;
    $upRegion = new SDL_GPUBufferRegion();
    $upRegion->buffer = $from;
    $upRegion->size = 16;
    $source = new SDL_GPUBufferLocation();
    $source->buffer = $from;
    $source->offset = 4;
    $destination = new SDL_GPUBufferLocation();
    $destination->buffer = $to;
    $downRegion = new SDL_GPUBufferRegion();
    $downRegion->buffer = $to;
    $downRegion->size = 8;
    $downTarget = new SDL_GPUTransferBufferLocation();
    $downTarget->transfer_buffer = $down;

    $commands = SDL_AcquireGPUCommandBuffer(gpu());
    $copy = SDL_BeginGPUCopyPass($commands);
    SDL_UploadToGPUBuffer($copy, $upSource, $upRegion, false);
    SDL_CopyGPUBufferToBuffer($copy, $source, $destination, 8, false);
    SDL_DownloadFromGPUBuffer($copy, $downRegion, $downTarget);
    SDL_EndGPUCopyPass($copy);
    submitAndWait($commands);

    expect(readMapped($down, 8))->toBe(substr($bytes, 4, 8));

    SDL_ReleaseGPUTransferBuffer(gpu(), $up);
    SDL_ReleaseGPUTransferBuffer(gpu(), $down);
    SDL_ReleaseGPUBuffer(gpu(), $from);
    SDL_ReleaseGPUBuffer(gpu(), $to);
});

it('copies a rectangle of one texture into another at an offset', function (): void {
    $bytes = random_bytes(4 * 4 * 2);
    $from = gpuTexture(4, 2, SDL_GPU_TEXTUREUSAGE_SAMPLER);
    $to = gpuTexture(3, 2, SDL_GPU_TEXTUREUSAGE_SAMPLER);
    $up = transferBuffer(32, SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD);
    $down = transferBuffer(24, SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD);
    writeMapped($up, $bytes);

    $upInfo = new SDL_GPUTextureTransferInfo();
    $upInfo->transfer_buffer = $up;
    $whole = new SDL_GPUTextureRegion();
    $whole->texture = $from;
    [$whole->w, $whole->h, $whole->d] = [4, 2, 1];
    $source = new SDL_GPUTextureLocation();
    $source->texture = $from;
    $source->x = 1;
    $destination = new SDL_GPUTextureLocation();
    $destination->texture = $to;
    $destination->x = 1;
    $downRegion = new SDL_GPUTextureRegion();
    $downRegion->texture = $to;
    [$downRegion->w, $downRegion->h, $downRegion->d] = [3, 2, 1];
    $downInfo = new SDL_GPUTextureTransferInfo();
    $downInfo->transfer_buffer = $down;

    $commands = SDL_AcquireGPUCommandBuffer(gpu());
    $copy = SDL_BeginGPUCopyPass($commands);
    SDL_UploadToGPUTexture($copy, $upInfo, $whole, false);
    SDL_CopyGPUTextureToTexture($copy, $source, $destination, 2, 2, 1, false);
    SDL_DownloadFromGPUTexture($copy, $downRegion, $downInfo);
    SDL_EndGPUCopyPass($copy);
    submitAndWait($commands);

    // Source columns 1-2 land in destination columns 1-2 of each row; column 0 was never written.
    $got = readMapped($down, 24);
    foreach ([0, 1] as $row) {
        expect(substr($got, $row * 12 + 4, 8))->toBe(substr($bytes, $row * 16 + 4, 8));
    }
    SDL_ReleaseGPUTransferBuffer(gpu(), $up);
    SDL_ReleaseGPUTransferBuffer(gpu(), $down);
    SDL_ReleaseGPUTexture(gpu(), $from);
    SDL_ReleaseGPUTexture(gpu(), $to);
});

it('makes a compute pipeline from a kernel, and passes a bad one through to SDL', function (): void {
    if (PHP_OS_FAMILY !== 'Darwin') {
        $this->markTestSkipped('The kernel here is MSL.');
    }
    $info = new SDL_GPUComputePipelineCreateInfo();
    $info->code = <<<'MSL'
        #include <metal_stdlib>
        using namespace metal;
        kernel void fill(device uint *out [[buffer(0)]], uint id [[thread_position_in_grid]]) { out[id] = id * 3u; }
        MSL;
    $info->entrypoint = 'fill';
    $info->format = SDL_GPU_SHADERFORMAT_MSL;
    $info->num_readwrite_storage_buffers = 1;
    [$info->threadcount_x, $info->threadcount_y, $info->threadcount_z] = [8, 1, 1];

    $pipeline = SDL_CreateGPUComputePipeline(gpu(), $info);
    expect($pipeline)->toBeInstanceOf(SDL_GPUComputePipeline::class)
        ->and($pipeline->pointer())->not->toBe(0)
        ->and(SDL_GPUComputePipeline::fromPointer($pipeline->pointer()))->toBe($pipeline);
    SDL_ReleaseGPUComputePipeline(gpu(), $pipeline);

    // SDL's Metal backend logs why it failed; it does not set SDL_GetError().
    $info->entrypoint = 'missing';
    expect(SDL_CreateGPUComputePipeline(gpu(), $info))->toBeNull();
});

function computePipeline(string $msl, int $uniforms, int $textures, int $buffers): SDL_GPUComputePipeline
{
    $info = new SDL_GPUComputePipelineCreateInfo();
    $info->code = $msl;
    $info->entrypoint = 'run';
    $info->format = SDL_GPU_SHADERFORMAT_MSL;
    $info->num_uniform_buffers = $uniforms;
    $info->num_readwrite_storage_textures = $textures;
    $info->num_readwrite_storage_buffers = $buffers;
    [$info->threadcount_x, $info->threadcount_y, $info->threadcount_z] = [8, 1, 1];

    return SDL_CreateGPUComputePipeline(gpu(), $info)
        ?? throw new RuntimeException('SDL_CreateGPUComputePipeline failed');
}

it('dispatches a kernel that writes a storage buffer from a pushed uniform', function (): void {
    if (PHP_OS_FAMILY !== 'Darwin') {
        $this->markTestSkipped('The kernel here is MSL.');
    }
    // SDL's Metal slots: uniform buffers first, then read-write storage buffers.
    $pipeline = computePipeline(<<<'MSL'
        #include <metal_stdlib>
        using namespace metal;
        kernel void run(constant uint &add [[buffer(0)]], device uint *out [[buffer(1)]], uint id [[thread_position_in_grid]]) { out[id] = id * 3u + add; }
        MSL, 1, 0, 1);
    $out = gpuBuffer(64, SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_WRITE);
    $down = transferBuffer(64, SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD);
    $binding = new SDL_GPUStorageBufferReadWriteBinding();
    $binding->buffer = $out;
    $region = new SDL_GPUBufferRegion();
    $region->buffer = $out;
    $region->size = 64;
    $target = new SDL_GPUTransferBufferLocation();
    $target->transfer_buffer = $down;

    $commands = SDL_AcquireGPUCommandBuffer(gpu());
    $pass = SDL_BeginGPUComputePass($commands, [], 0, [$binding], 1);
    expect($pass)->toBeInstanceOf(SDL_GPUComputePass::class);
    SDL_BindGPUComputePipeline($pass, $pipeline);
    SDL_PushGPUComputeUniformData($commands, 0, pack('V', 100), 4);
    SDL_DispatchGPUCompute($pass, 2, 1, 1);
    SDL_EndGPUComputePass($pass);
    $copy = SDL_BeginGPUCopyPass($commands);
    SDL_DownloadFromGPUBuffer($copy, $region, $target);
    SDL_EndGPUCopyPass($copy);
    submitAndWait($commands);

    expect(array_values(unpack('V16', readMapped($down, 64))))->toBe(array_map(fn ($i) => $i * 3 + 100, range(0, 15)))
        ->and($pass->pointer())->toBe(0);

    SDL_ReleaseGPUTransferBuffer(gpu(), $down);
    SDL_ReleaseGPUBuffer(gpu(), $out);
    SDL_ReleaseGPUComputePipeline(gpu(), $pipeline);
});

it('dispatches a kernel that writes a storage texture', function (): void {
    if (PHP_OS_FAMILY !== 'Darwin') {
        $this->markTestSkipped('The kernel here is MSL.');
    }
    $pipeline = computePipeline(<<<'MSL'
        #include <metal_stdlib>
        using namespace metal;
        kernel void run(texture2d<float, access::write> out [[texture(0)]], uint2 id [[thread_position_in_grid]]) { out.write(float4(1.0, 0.0, 0.0, 1.0), id); }
        MSL, 0, 1, 0);
    $texture = gpuTexture(8, 1, SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_WRITE);
    $down = transferBuffer(32, SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD);
    $binding = new SDL_GPUStorageTextureReadWriteBinding();
    $binding->texture = $texture;
    $region = new SDL_GPUTextureRegion();
    $region->texture = $texture;
    [$region->w, $region->h, $region->d] = [8, 1, 1];
    $info = new SDL_GPUTextureTransferInfo();
    $info->transfer_buffer = $down;

    $commands = SDL_AcquireGPUCommandBuffer(gpu());
    $pass = SDL_BeginGPUComputePass($commands, [$binding], 1, [], 0);
    SDL_BindGPUComputePipeline($pass, $pipeline);
    SDL_DispatchGPUCompute($pass, 1, 1, 1);
    SDL_EndGPUComputePass($pass);
    $copy = SDL_BeginGPUCopyPass($commands);
    SDL_DownloadFromGPUTexture($copy, $region, $info);
    SDL_EndGPUCopyPass($copy);
    submitAndWait($commands);

    expect(readMapped($down, 32))->toBe(str_repeat("\xff\x00\x00\xff", 8));

    SDL_ReleaseGPUTransferBuffer(gpu(), $down);
    SDL_ReleaseGPUTexture(gpu(), $texture);
    SDL_ReleaseGPUComputePipeline(gpu(), $pipeline);
});

it('checks the lists of SDL_BeginGPUComputePass and the length of compute uniforms', function (): void {
    $commands = SDL_AcquireGPUCommandBuffer(gpu());

    expect(fn () => SDL_BeginGPUComputePass($commands, [new SDL_GPUStorageBufferReadWriteBinding()], 1, [], 0))
        ->toThrow(TypeError::class, 'must be a list of SDL_GPUStorageTextureReadWriteBinding')
        ->and(fn () => SDL_BeginGPUComputePass($commands, [], 0, [], 1))
        ->toThrow(ValueError::class, 'must be between 0 and the length of argument #4')
        ->and(fn () => SDL_PushGPUComputeUniformData($commands, 0, 'abc', 4))
        ->toThrow(ValueError::class, 'must hold 4 bytes, 3 given');
    SDL_CancelGPUCommandBuffer($commands);
});

it('binds fragment storage buffers and textures, and checks the lists', function (): void {
    $target = gpuTexture(4, 4, SDL_GPU_TEXTUREUSAGE_COLOR_TARGET);
    $buffer = gpuBuffer(16, SDL_GPU_BUFFERUSAGE_GRAPHICS_STORAGE_READ);
    $texture = gpuTexture(4, 4, SDL_GPU_TEXTUREUSAGE_GRAPHICS_STORAGE_READ);
    $color = new SDL_GPUColorTargetInfo();
    $color->texture = $target;
    $color->load_op = SDL_GPU_LOADOP_CLEAR;
    $color->store_op = SDL_GPU_STOREOP_STORE;

    $commands = SDL_AcquireGPUCommandBuffer(gpu());
    $pass = SDL_BeginGPURenderPass($commands, [$color], 1, null);
    SDL_BindGPUFragmentStorageBuffers($pass, 0, [$buffer], 1);
    SDL_BindGPUFragmentStorageTextures($pass, 0, [$texture], 1);

    expect(fn () => SDL_BindGPUFragmentStorageBuffers($pass, 0, [$texture], 1))
        ->toThrow(TypeError::class, 'must be a list of SDL_GPUBuffer')
        ->and(fn () => SDL_BindGPUFragmentStorageTextures($pass, 0, [$buffer], 1))
        ->toThrow(TypeError::class, 'must be a list of SDL_GPUTexture')
        ->and(fn () => SDL_BindGPUFragmentStorageBuffers($pass, 0, [$buffer], 2))
        ->toThrow(ValueError::class, 'must be between 0 and the length of argument #3');

    SDL_EndGPURenderPass($pass);
    submitAndWait($commands);
    SDL_ReleaseGPUBuffer(gpu(), $buffer);
    SDL_ReleaseGPUTexture(gpu(), $texture);
    SDL_ReleaseGPUTexture(gpu(), $target);
});
