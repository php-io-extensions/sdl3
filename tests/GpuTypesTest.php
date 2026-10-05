<?php

declare(strict_types=1);

it('starts every GPU struct at zero with its nested structs made', function (): void {
    $info = new SDL_GPUGraphicsPipelineCreateInfo();

    expect($info->vertex_shader)->toBeNull()
        ->and($info->depth_stencil_state->front_stencil_state->compare_op)->toBe(0)
        ->and($info->target_info->color_target_descriptions)->toBe([])
        ->and($info->multisample_state->sample_count)->toBe(0)
        ->and((new SDL_GPUColorTargetInfo())->clear_color)->toBeInstanceOf(SDL_FColor::class)
        ->and((new SDL_GPUBlitInfo())->source)->toBeInstanceOf(SDL_GPUBlitRegion::class);
});

it('takes a shader\'s code as one string', function (): void {
    $info = new SDL_GPUShaderCreateInfo();
    $info->code = "\x03\x02\x23\x07";
    $info->entrypoint = 'main';

    expect($info->code)->toBe("\x03\x02\x23\x07")
        ->and(property_exists($info, 'code_size'))->toBeFalse();
});

it('carries the header values for the GPU constants', function (): void {
    expect(SDL_GPU_SHADERFORMAT_SPIRV)->toBe(2)
        ->and(SDL_GPU_SHADERFORMAT_MSL)->toBe(16)
        ->and(SDL_GPU_SAMPLECOUNT_4)->toBe(2)
        ->and(SDL_GPU_STOREOP_RESOLVE)->toBeInt()
        ->and(SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM)->toBeInt()
        ->and(SDL_GPU_TEXTUREFORMAT_D24_UNORM_S8_UINT)->not->toBe(SDL_GPU_TEXTUREFORMAT_D32_FLOAT_S8_UINT);
});
