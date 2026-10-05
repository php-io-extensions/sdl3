<?php

declare(strict_types=1);

/** The fixture shader for this device's format. */
function flatShader(int $stage): SDL_GPUShader
{
    $info = new SDL_GPUShaderCreateInfo();
    $info->stage = $stage;
    $fragment = $stage === SDL_GPU_SHADERSTAGE_FRAGMENT;
    if (SDL_GetGPUShaderFormats(gpu()) & SDL_GPU_SHADERFORMAT_SPIRV) {
        $info->format = SDL_GPU_SHADERFORMAT_SPIRV;
        $info->code = file_get_contents(__DIR__ . '/Fixtures/flat.' . ($fragment ? 'frag' : 'vert') . '.spv');
        $info->entrypoint = 'main';
    } else {
        $info->format = SDL_GPU_SHADERFORMAT_MSL;
        $info->code = file_get_contents(__DIR__ . '/Fixtures/flat.metal');
        $info->entrypoint = $fragment ? 'flat_fragment' : 'flat_vertex';
    }
    $info->num_uniform_buffers = $fragment ? 1 : 0;

    return SDL_CreateGPUShader(gpu(), $info) ?? throw new RuntimeException('SDL_CreateGPUShader: ' . SDL_GetError());
}

function stencilFormat(): int
{
    return SDL_GPUTextureSupportsFormat(gpu(), SDL_GPU_TEXTUREFORMAT_D24_UNORM_S8_UINT, SDL_GPU_TEXTURETYPE_2D, SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET)
        ? SDL_GPU_TEXTUREFORMAT_D24_UNORM_S8_UINT
        : SDL_GPU_TEXTUREFORMAT_D32_FLOAT_S8_UINT;
}

/** A flat pipeline into RGBA8 + stencil at 4x: colour written or not, stencil compare and pass op as given. */
function flatPipeline(bool $writeColor, int $compare, int $pass): SDL_GPUGraphicsPipeline
{
    $info = new SDL_GPUGraphicsPipelineCreateInfo();
    $info->vertex_shader = flatShader(SDL_GPU_SHADERSTAGE_VERTEX);
    $info->fragment_shader = flatShader(SDL_GPU_SHADERSTAGE_FRAGMENT);
    $info->primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;

    $buffer = new SDL_GPUVertexBufferDescription();
    $buffer->slot = 0;
    $buffer->pitch = 8;
    $buffer->input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
    $attribute = new SDL_GPUVertexAttribute();
    $attribute->location = 0;
    $attribute->buffer_slot = 0;
    $attribute->format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2;
    $info->vertex_input_state->vertex_buffer_descriptions = [$buffer];
    $info->vertex_input_state->vertex_attributes = [$attribute];

    $info->multisample_state->sample_count = SDL_GPU_SAMPLECOUNT_4;
    $stencil = $info->depth_stencil_state;
    $stencil->enable_stencil_test = true;
    $stencil->compare_mask = 0xFF;
    $stencil->write_mask = 0xFF;
    foreach ([$stencil->front_stencil_state, $stencil->back_stencil_state] as $face) {
        $face->compare_op = $compare;
        $face->pass_op = $pass;
        $face->fail_op = SDL_GPU_STENCILOP_KEEP;
        $face->depth_fail_op = SDL_GPU_STENCILOP_KEEP;
    }

    $color = new SDL_GPUColorTargetDescription();
    $color->format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
    $color->blend_state->enable_color_write_mask = true;
    $color->blend_state->color_write_mask = $writeColor
        ? SDL_GPU_COLORCOMPONENT_R | SDL_GPU_COLORCOMPONENT_G | SDL_GPU_COLORCOMPONENT_B | SDL_GPU_COLORCOMPONENT_A
        : 0;
    $info->target_info->color_target_descriptions = [$color];
    $info->target_info->has_depth_stencil_target = true;
    $info->target_info->depth_stencil_format = stencilFormat();

    return SDL_CreateGPUGraphicsPipeline(gpu(), $info) ?? throw new RuntimeException('SDL_CreateGPUGraphicsPipeline: ' . SDL_GetError());
}

/** RGBA8 pixel at (x, y) of a tightly packed 8-wide image, as hex. */
function pixelAt(string $bytes, int $x, int $y): string
{
    return bin2hex(substr($bytes, ($y * 8 + $x) * 4, 4));
}

it('fills a triangle by stencil-then-cover into a 4x target, resolves, blits and reads it back', function (): void {
    // Vertices: the triangle (-1,-1), (1,-1), (-1,1), then a cover quad as two triangles.
    $points = pack('g18', -1.0, -1.0, 1.0, -1.0, -1.0, 1.0,   -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0);
    $bufferInfo = new SDL_GPUBufferCreateInfo();
    $bufferInfo->usage = SDL_GPU_BUFFERUSAGE_VERTEX;
    $bufferInfo->size = strlen($points);
    $vertices = SDL_CreateGPUBuffer(gpu(), $bufferInfo);
    $upload = transferBuffer(strlen($points), SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD);
    writeMapped($upload, $points);

    $msaa = gpuTexture(8, 8, SDL_GPU_TEXTUREUSAGE_COLOR_TARGET, SDL_GPU_SAMPLECOUNT_4);
    $stencilTarget = gpuTexture(8, 8, SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET, SDL_GPU_SAMPLECOUNT_4, stencilFormat());
    $resolved = gpuTexture(8, 8, SDL_GPU_TEXTUREUSAGE_COLOR_TARGET | SDL_GPU_TEXTUREUSAGE_SAMPLER);
    $blitted = gpuTexture(8, 8, SDL_GPU_TEXTUREUSAGE_COLOR_TARGET | SDL_GPU_TEXTUREUSAGE_SAMPLER);
    $download = transferBuffer(2 * 256, SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD);
    $stencilPipeline = flatPipeline(false, SDL_GPU_COMPAREOP_ALWAYS, SDL_GPU_STENCILOP_INVERT);
    $coverPipeline = flatPipeline(true, SDL_GPU_COMPAREOP_NOT_EQUAL, SDL_GPU_STENCILOP_ZERO);

    $commands = SDL_AcquireGPUCommandBuffer(gpu());

    $copy = SDL_BeginGPUCopyPass($commands);
    $source = new SDL_GPUTransferBufferLocation();
    $source->transfer_buffer = $upload;
    $destination = new SDL_GPUBufferRegion();
    $destination->buffer = $vertices;
    $destination->size = strlen($points);
    SDL_UploadToGPUBuffer($copy, $source, $destination, false);
    SDL_EndGPUCopyPass($copy);

    $color = new SDL_GPUColorTargetInfo();
    $color->texture = $msaa;
    $color->resolve_texture = $resolved;
    $color->load_op = SDL_GPU_LOADOP_CLEAR;
    [$color->clear_color->r, $color->clear_color->g, $color->clear_color->b, $color->clear_color->a] = [0.0, 0.0, 0.0, 1.0];
    $color->store_op = SDL_GPU_STOREOP_RESOLVE;
    $depthStencil = new SDL_GPUDepthStencilTargetInfo();
    $depthStencil->texture = $stencilTarget;
    $depthStencil->clear_depth = 1.0;
    $depthStencil->load_op = SDL_GPU_LOADOP_CLEAR;
    $depthStencil->store_op = SDL_GPU_STOREOP_DONT_CARE;
    $depthStencil->stencil_load_op = SDL_GPU_LOADOP_CLEAR;
    $depthStencil->stencil_store_op = SDL_GPU_STOREOP_DONT_CARE;
    $depthStencil->clear_stencil = 0;
    $binding = new SDL_GPUBufferBinding();
    $binding->buffer = $vertices;

    $pass = SDL_BeginGPURenderPass($commands, [$color], $depthStencil);
    SDL_BindGPUVertexBuffers($pass, 0, [$binding]);
    // Stencil: invert where the triangle covers, no colour written.
    SDL_BindGPUGraphicsPipeline($pass, $stencilPipeline);
    SDL_DrawGPUPrimitives($pass, 3, 1, 0, 0);
    // Cover: red where the stencil is not 0, and the stencil back to 0.
    SDL_BindGPUGraphicsPipeline($pass, $coverPipeline);
    SDL_SetGPUStencilReference($pass, 0);
    $red = pack('g4', 1.0, 0.0, 0.0, 1.0);
    SDL_PushGPUFragmentUniformData($commands, 0, $red, strlen($red));
    SDL_DrawGPUPrimitives($pass, 6, 1, 3, 0);
    SDL_EndGPURenderPass($pass);

    $blit = new SDL_GPUBlitInfo();
    $blit->source->texture = $resolved;
    [$blit->source->w, $blit->source->h] = [8, 8];
    $blit->destination->texture = $blitted;
    [$blit->destination->w, $blit->destination->h] = [8, 8];
    $blit->load_op = SDL_GPU_LOADOP_DONT_CARE;
    $blit->filter = SDL_GPU_FILTER_NEAREST;
    SDL_BlitGPUTexture($commands, $blit);

    $copy = SDL_BeginGPUCopyPass($commands);
    foreach ([$resolved, $blitted] as $i => $texture) {
        $region = new SDL_GPUTextureRegion();
        $region->texture = $texture;
        [$region->w, $region->h, $region->d] = [8, 8, 1];
        $to = new SDL_GPUTextureTransferInfo();
        $to->transfer_buffer = $download;
        $to->offset = $i * 256;
        SDL_DownloadFromGPUTexture($copy, $region, $to);
    }
    SDL_EndGPUCopyPass($copy);
    $fence = SDL_SubmitGPUCommandBufferAndAcquireFence($commands);
    SDL_WaitForGPUFences(gpu(), true, [$fence]);

    $both = readMapped($download, 512);
    [$pixels, $copied] = [substr($both, 0, 256), substr($both, 256)];

    expect($copied)->toBe($pixels)
        // Texture row 0 is the top. Inside the triangle near the bottom-left, outside near the top-right.
        ->and(pixelAt($pixels, 1, 6))->toBe('ff0000ff')
        ->and(pixelAt($pixels, 0, 1))->toBe('ff0000ff')
        ->and(pixelAt($pixels, 6, 1))->toBe('000000ff')
        // The hypotenuse runs (i, i): resolved from 4 samples, every pixel there is neither solid colour.
        ->and(array_filter(range(0, 7), fn (int $i): bool => in_array(pixelAt($pixels, $i, $i), ['ff0000ff', '000000ff'], true)))->toBe([]);

    SDL_ReleaseGPUFence(gpu(), $fence);
    foreach ([$msaa, $stencilTarget, $resolved, $blitted] as $texture) {
        SDL_ReleaseGPUTexture(gpu(), $texture);
    }
    SDL_ReleaseGPUTransferBuffer(gpu(), $upload);
    SDL_ReleaseGPUTransferBuffer(gpu(), $download);
    SDL_ReleaseGPUBuffer(gpu(), $vertices);
    SDL_ReleaseGPUGraphicsPipeline(gpu(), $stencilPipeline);
    SDL_ReleaseGPUGraphicsPipeline(gpu(), $coverPipeline);
});

it('refuses uniform data shorter than the length given', function (): void {
    SDL_PushGPUFragmentUniformData(SDL_AcquireGPUCommandBuffer(gpu()), 0, 'abc', 16);
})->throws(ValueError::class, 'must hold');
