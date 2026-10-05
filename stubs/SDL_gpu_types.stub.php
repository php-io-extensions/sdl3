<?php

/** @generate-class-entries */

/**
 * An address other than 0 is trusted.
 *
 * @not-serializable
 */
final class SDL_GPUShader
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): static {}
}

final class SDL_GPUTexture
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): static {}
}

final class SDL_GPUBuffer
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): static {}
}

final class SDL_GPUTransferBuffer
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): static {}
}

final class SDL_GPUSampler
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class SDL_FColor
{
    public float $r = 0.0;

    public float $g = 0.0;

    public float $b = 0.0;

    public float $a = 0.0;
}

/**
 * @not-serializable
 */
final class SDL_GPUViewport
{
    public float $x = 0.0;

    public float $y = 0.0;

    public float $w = 0.0;

    public float $h = 0.0;

    public float $min_depth = 0.0;

    public float $max_depth = 0.0;
}

/**
 * @not-serializable
 */
final class SDL_GPUShaderCreateInfo
{
    public string $code = '';

    public string $entrypoint = '';

    public int $format = 0;

    public int $stage = 0;

    public int $num_samplers = 0;

    public int $num_storage_textures = 0;

    public int $num_storage_buffers = 0;

    public int $num_uniform_buffers = 0;

    public int $props = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUVertexBufferDescription
{
    public int $slot = 0;

    public int $pitch = 0;

    public int $input_rate = 0;

    public int $instance_step_rate = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUVertexAttribute
{
    public int $location = 0;

    public int $buffer_slot = 0;

    public int $format = 0;

    public int $offset = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUVertexInputState
{
    /** @var list<SDL_GPUVertexBufferDescription> */
    public array $vertex_buffer_descriptions = [];

    /** @var list<SDL_GPUVertexAttribute> */
    public array $vertex_attributes = [];
}

/**
 * @not-serializable
 */
final class SDL_GPUStencilOpState
{
    public int $fail_op = 0;

    public int $pass_op = 0;

    public int $depth_fail_op = 0;

    public int $compare_op = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPURasterizerState
{
    public int $fill_mode = 0;

    public int $cull_mode = 0;

    public int $front_face = 0;

    public float $depth_bias_constant_factor = 0.0;

    public float $depth_bias_clamp = 0.0;

    public float $depth_bias_slope_factor = 0.0;

    public bool $enable_depth_bias = false;

    public bool $enable_depth_clip = false;
}

/**
 * @not-serializable
 */
final class SDL_GPUMultisampleState
{
    public int $sample_count = 0;

    public int $sample_mask = 0;

    public bool $enable_mask = false;
}

/**
 * @not-serializable
 */
final class SDL_GPUDepthStencilState
{
    public int $compare_op = 0;

    public SDL_GPUStencilOpState $back_stencil_state;

    public SDL_GPUStencilOpState $front_stencil_state;

    public int $compare_mask = 0;

    public int $write_mask = 0;

    public bool $enable_depth_test = false;

    public bool $enable_depth_write = false;

    public bool $enable_stencil_test = false;

    public function __construct() {}
}

/**
 * @not-serializable
 */
final class SDL_GPUColorTargetBlendState
{
    public int $src_color_blendfactor = 0;

    public int $dst_color_blendfactor = 0;

    public int $color_blend_op = 0;

    public int $src_alpha_blendfactor = 0;

    public int $dst_alpha_blendfactor = 0;

    public int $alpha_blend_op = 0;

    public int $color_write_mask = 0;

    public bool $enable_blend = false;

    public bool $enable_color_write_mask = false;
}

/**
 * @not-serializable
 */
final class SDL_GPUColorTargetDescription
{
    public int $format = 0;

    public SDL_GPUColorTargetBlendState $blend_state;

    public function __construct() {}
}

/**
 * @not-serializable
 */
final class SDL_GPUGraphicsPipelineTargetInfo
{
    /** @var list<SDL_GPUColorTargetDescription> */
    public array $color_target_descriptions = [];

    public int $depth_stencil_format = 0;

    public bool $has_depth_stencil_target = false;
}

/**
 * @not-serializable
 */
final class SDL_GPUGraphicsPipelineCreateInfo
{
    public ?SDL_GPUShader $vertex_shader = null;

    public ?SDL_GPUShader $fragment_shader = null;

    public SDL_GPUVertexInputState $vertex_input_state;

    public int $primitive_type = 0;

    public SDL_GPURasterizerState $rasterizer_state;

    public SDL_GPUMultisampleState $multisample_state;

    public SDL_GPUDepthStencilState $depth_stencil_state;

    public SDL_GPUGraphicsPipelineTargetInfo $target_info;

    public int $props = 0;

    public function __construct() {}
}

/**
 * @not-serializable
 */
final class SDL_GPUTextureCreateInfo
{
    public int $type = 0;

    public int $format = 0;

    public int $usage = 0;

    public int $width = 0;

    public int $height = 0;

    public int $layer_count_or_depth = 0;

    public int $num_levels = 0;

    public int $sample_count = 0;

    public int $props = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUSamplerCreateInfo
{
    public int $min_filter = 0;

    public int $mag_filter = 0;

    public int $mipmap_mode = 0;

    public int $address_mode_u = 0;

    public int $address_mode_v = 0;

    public int $address_mode_w = 0;

    public float $mip_lod_bias = 0.0;

    public float $max_anisotropy = 0.0;

    public int $compare_op = 0;

    public float $min_lod = 0.0;

    public float $max_lod = 0.0;

    public bool $enable_anisotropy = false;

    public bool $enable_compare = false;

    public int $props = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUBufferCreateInfo
{
    public int $usage = 0;

    public int $size = 0;

    public int $props = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUTransferBufferCreateInfo
{
    public int $usage = 0;

    public int $size = 0;

    public int $props = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUTextureTransferInfo
{
    public ?SDL_GPUTransferBuffer $transfer_buffer = null;

    public int $offset = 0;

    public int $pixels_per_row = 0;

    public int $rows_per_layer = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUTransferBufferLocation
{
    public ?SDL_GPUTransferBuffer $transfer_buffer = null;

    public int $offset = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUTextureRegion
{
    public ?SDL_GPUTexture $texture = null;

    public int $mip_level = 0;

    public int $layer = 0;

    public int $x = 0;

    public int $y = 0;

    public int $z = 0;

    public int $w = 0;

    public int $h = 0;

    public int $d = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUBufferRegion
{
    public ?SDL_GPUBuffer $buffer = null;

    public int $offset = 0;

    public int $size = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUBlitRegion
{
    public ?SDL_GPUTexture $texture = null;

    public int $mip_level = 0;

    public int $layer_or_depth_plane = 0;

    public int $x = 0;

    public int $y = 0;

    public int $w = 0;

    public int $h = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUColorTargetInfo
{
    public ?SDL_GPUTexture $texture = null;

    public int $mip_level = 0;

    public int $layer_or_depth_plane = 0;

    public SDL_FColor $clear_color;

    public int $load_op = 0;

    public int $store_op = 0;

    public ?SDL_GPUTexture $resolve_texture = null;

    public int $resolve_mip_level = 0;

    public int $resolve_layer = 0;

    public bool $cycle = false;

    public bool $cycle_resolve_texture = false;

    public function __construct() {}
}

/**
 * @not-serializable
 */
final class SDL_GPUDepthStencilTargetInfo
{
    public ?SDL_GPUTexture $texture = null;

    public float $clear_depth = 0.0;

    public int $load_op = 0;

    public int $store_op = 0;

    public int $stencil_load_op = 0;

    public int $stencil_store_op = 0;

    public bool $cycle = false;

    public int $clear_stencil = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUBufferBinding
{
    public ?SDL_GPUBuffer $buffer = null;

    public int $offset = 0;
}

/**
 * @not-serializable
 */
final class SDL_GPUTextureSamplerBinding
{
    public ?SDL_GPUTexture $texture = null;

    public ?SDL_GPUSampler $sampler = null;
}

/**
 * @not-serializable
 */
final class SDL_GPUBlitInfo
{
    public SDL_GPUBlitRegion $source;

    public SDL_GPUBlitRegion $destination;

    public int $load_op = 0;

    public SDL_FColor $clear_color;

    public int $flip_mode = 0;

    public int $filter = 0;

    public bool $cycle = false;

    public function __construct() {}
}

/**
 * @var int
 * @cvalue SDL_GPU_PRIMITIVETYPE_TRIANGLELIST
 */
const SDL_GPU_PRIMITIVETYPE_TRIANGLELIST = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_PRIMITIVETYPE_TRIANGLESTRIP
 */
const SDL_GPU_PRIMITIVETYPE_TRIANGLESTRIP = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_PRIMITIVETYPE_LINELIST
 */
const SDL_GPU_PRIMITIVETYPE_LINELIST = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_PRIMITIVETYPE_LINESTRIP
 */
const SDL_GPU_PRIMITIVETYPE_LINESTRIP = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_PRIMITIVETYPE_POINTLIST
 */
const SDL_GPU_PRIMITIVETYPE_POINTLIST = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_LOADOP_LOAD
 */
const SDL_GPU_LOADOP_LOAD = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_LOADOP_CLEAR
 */
const SDL_GPU_LOADOP_CLEAR = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_LOADOP_DONT_CARE
 */
const SDL_GPU_LOADOP_DONT_CARE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_STOREOP_STORE
 */
const SDL_GPU_STOREOP_STORE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_STOREOP_DONT_CARE
 */
const SDL_GPU_STOREOP_DONT_CARE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_STOREOP_RESOLVE
 */
const SDL_GPU_STOREOP_RESOLVE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_STOREOP_RESOLVE_AND_STORE
 */
const SDL_GPU_STOREOP_RESOLVE_AND_STORE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_INDEXELEMENTSIZE_16BIT
 */
const SDL_GPU_INDEXELEMENTSIZE_16BIT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_INDEXELEMENTSIZE_32BIT
 */
const SDL_GPU_INDEXELEMENTSIZE_32BIT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_INVALID
 */
const SDL_GPU_TEXTUREFORMAT_INVALID = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_A8_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_A8_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R8_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_R8_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R8G8_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_R8G8_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_R16_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16G16_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_R16G16_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16G16B16A16_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_R16G16B16A16_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R10G10B10A2_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_R10G10B10A2_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_B5G6R5_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_B5G6R5_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_B5G5R5A1_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_B5G5R5A1_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_B4G4R4A4_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_B4G4R4A4_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_B8G8R8A8_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_B8G8R8A8_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_BC1_RGBA_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_BC1_RGBA_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_BC2_RGBA_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_BC2_RGBA_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_BC3_RGBA_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_BC3_RGBA_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_BC4_R_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_BC4_R_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_BC5_RG_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_BC5_RG_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_BC7_RGBA_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_BC7_RGBA_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_BC6H_RGB_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_BC6H_RGB_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_BC6H_RGB_UFLOAT
 */
const SDL_GPU_TEXTUREFORMAT_BC6H_RGB_UFLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R8_SNORM
 */
const SDL_GPU_TEXTUREFORMAT_R8_SNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R8G8_SNORM
 */
const SDL_GPU_TEXTUREFORMAT_R8G8_SNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R8G8B8A8_SNORM
 */
const SDL_GPU_TEXTUREFORMAT_R8G8B8A8_SNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16_SNORM
 */
const SDL_GPU_TEXTUREFORMAT_R16_SNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16G16_SNORM
 */
const SDL_GPU_TEXTUREFORMAT_R16G16_SNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16G16B16A16_SNORM
 */
const SDL_GPU_TEXTUREFORMAT_R16G16B16A16_SNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_R16_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16G16_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_R16G16_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16G16B16A16_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_R16G16B16A16_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R32_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_R32_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R32G32_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_R32G32_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R32G32B32A32_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_R32G32B32A32_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R11G11B10_UFLOAT
 */
const SDL_GPU_TEXTUREFORMAT_R11G11B10_UFLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R8_UINT
 */
const SDL_GPU_TEXTUREFORMAT_R8_UINT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R8G8_UINT
 */
const SDL_GPU_TEXTUREFORMAT_R8G8_UINT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UINT
 */
const SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UINT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16_UINT
 */
const SDL_GPU_TEXTUREFORMAT_R16_UINT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16G16_UINT
 */
const SDL_GPU_TEXTUREFORMAT_R16G16_UINT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16G16B16A16_UINT
 */
const SDL_GPU_TEXTUREFORMAT_R16G16B16A16_UINT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R32_UINT
 */
const SDL_GPU_TEXTUREFORMAT_R32_UINT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R32G32_UINT
 */
const SDL_GPU_TEXTUREFORMAT_R32G32_UINT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R32G32B32A32_UINT
 */
const SDL_GPU_TEXTUREFORMAT_R32G32B32A32_UINT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R8_INT
 */
const SDL_GPU_TEXTUREFORMAT_R8_INT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R8G8_INT
 */
const SDL_GPU_TEXTUREFORMAT_R8G8_INT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R8G8B8A8_INT
 */
const SDL_GPU_TEXTUREFORMAT_R8G8B8A8_INT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16_INT
 */
const SDL_GPU_TEXTUREFORMAT_R16_INT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16G16_INT
 */
const SDL_GPU_TEXTUREFORMAT_R16G16_INT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R16G16B16A16_INT
 */
const SDL_GPU_TEXTUREFORMAT_R16G16B16A16_INT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R32_INT
 */
const SDL_GPU_TEXTUREFORMAT_R32_INT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R32G32_INT
 */
const SDL_GPU_TEXTUREFORMAT_R32G32_INT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R32G32B32A32_INT
 */
const SDL_GPU_TEXTUREFORMAT_R32G32B32A32_INT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_B8G8R8A8_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_B8G8R8A8_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_BC1_RGBA_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_BC1_RGBA_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_BC2_RGBA_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_BC2_RGBA_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_BC3_RGBA_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_BC3_RGBA_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_BC7_RGBA_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_BC7_RGBA_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_D16_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_D16_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_D24_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_D24_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_D32_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_D32_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_D24_UNORM_S8_UINT
 */
const SDL_GPU_TEXTUREFORMAT_D24_UNORM_S8_UINT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_D32_FLOAT_S8_UINT
 */
const SDL_GPU_TEXTUREFORMAT_D32_FLOAT_S8_UINT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_4x4_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_4x4_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_5x4_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_5x4_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_5x5_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_5x5_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_6x5_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_6x5_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_6x6_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_6x6_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_8x5_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_8x5_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_8x6_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_8x6_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_8x8_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_8x8_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_10x5_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_10x5_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_10x6_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_10x6_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_10x8_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_10x8_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_10x10_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_10x10_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_12x10_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_12x10_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_12x12_UNORM
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_12x12_UNORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_4x4_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_4x4_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_5x4_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_5x4_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_5x5_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_5x5_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_6x5_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_6x5_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_6x6_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_6x6_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_8x5_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_8x5_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_8x6_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_8x6_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_8x8_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_8x8_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_10x5_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_10x5_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_10x6_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_10x6_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_10x8_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_10x8_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_10x10_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_10x10_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_12x10_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_12x10_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_12x12_UNORM_SRGB
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_12x12_UNORM_SRGB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_4x4_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_4x4_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_5x4_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_5x4_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_5x5_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_5x5_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_6x5_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_6x5_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_6x6_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_6x6_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_8x5_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_8x5_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_8x6_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_8x6_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_8x8_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_8x8_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_10x5_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_10x5_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_10x6_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_10x6_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_10x8_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_10x8_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_10x10_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_10x10_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_12x10_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_12x10_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREFORMAT_ASTC_12x12_FLOAT
 */
const SDL_GPU_TEXTUREFORMAT_ASTC_12x12_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTURETYPE_2D
 */
const SDL_GPU_TEXTURETYPE_2D = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTURETYPE_2D_ARRAY
 */
const SDL_GPU_TEXTURETYPE_2D_ARRAY = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTURETYPE_3D
 */
const SDL_GPU_TEXTURETYPE_3D = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTURETYPE_CUBE
 */
const SDL_GPU_TEXTURETYPE_CUBE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTURETYPE_CUBE_ARRAY
 */
const SDL_GPU_TEXTURETYPE_CUBE_ARRAY = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SAMPLECOUNT_1
 */
const SDL_GPU_SAMPLECOUNT_1 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SAMPLECOUNT_2
 */
const SDL_GPU_SAMPLECOUNT_2 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SAMPLECOUNT_4
 */
const SDL_GPU_SAMPLECOUNT_4 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SAMPLECOUNT_8
 */
const SDL_GPU_SAMPLECOUNT_8 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD
 */
const SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD
 */
const SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SHADERSTAGE_VERTEX
 */
const SDL_GPU_SHADERSTAGE_VERTEX = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SHADERSTAGE_FRAGMENT
 */
const SDL_GPU_SHADERSTAGE_FRAGMENT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_INVALID
 */
const SDL_GPU_VERTEXELEMENTFORMAT_INVALID = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_INT
 */
const SDL_GPU_VERTEXELEMENTFORMAT_INT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_INT2
 */
const SDL_GPU_VERTEXELEMENTFORMAT_INT2 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_INT3
 */
const SDL_GPU_VERTEXELEMENTFORMAT_INT3 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_INT4
 */
const SDL_GPU_VERTEXELEMENTFORMAT_INT4 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_UINT
 */
const SDL_GPU_VERTEXELEMENTFORMAT_UINT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_UINT2
 */
const SDL_GPU_VERTEXELEMENTFORMAT_UINT2 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_UINT3
 */
const SDL_GPU_VERTEXELEMENTFORMAT_UINT3 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_UINT4
 */
const SDL_GPU_VERTEXELEMENTFORMAT_UINT4 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_FLOAT
 */
const SDL_GPU_VERTEXELEMENTFORMAT_FLOAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2
 */
const SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3
 */
const SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4
 */
const SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_BYTE2
 */
const SDL_GPU_VERTEXELEMENTFORMAT_BYTE2 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_BYTE4
 */
const SDL_GPU_VERTEXELEMENTFORMAT_BYTE4 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_UBYTE2
 */
const SDL_GPU_VERTEXELEMENTFORMAT_UBYTE2 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4
 */
const SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_BYTE2_NORM
 */
const SDL_GPU_VERTEXELEMENTFORMAT_BYTE2_NORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_BYTE4_NORM
 */
const SDL_GPU_VERTEXELEMENTFORMAT_BYTE4_NORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_UBYTE2_NORM
 */
const SDL_GPU_VERTEXELEMENTFORMAT_UBYTE2_NORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4_NORM
 */
const SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4_NORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_SHORT2
 */
const SDL_GPU_VERTEXELEMENTFORMAT_SHORT2 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_SHORT4
 */
const SDL_GPU_VERTEXELEMENTFORMAT_SHORT4 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_USHORT2
 */
const SDL_GPU_VERTEXELEMENTFORMAT_USHORT2 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_USHORT4
 */
const SDL_GPU_VERTEXELEMENTFORMAT_USHORT4 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_SHORT2_NORM
 */
const SDL_GPU_VERTEXELEMENTFORMAT_SHORT2_NORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_SHORT4_NORM
 */
const SDL_GPU_VERTEXELEMENTFORMAT_SHORT4_NORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_USHORT2_NORM
 */
const SDL_GPU_VERTEXELEMENTFORMAT_USHORT2_NORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_USHORT4_NORM
 */
const SDL_GPU_VERTEXELEMENTFORMAT_USHORT4_NORM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_HALF2
 */
const SDL_GPU_VERTEXELEMENTFORMAT_HALF2 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXELEMENTFORMAT_HALF4
 */
const SDL_GPU_VERTEXELEMENTFORMAT_HALF4 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXINPUTRATE_VERTEX
 */
const SDL_GPU_VERTEXINPUTRATE_VERTEX = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_VERTEXINPUTRATE_INSTANCE
 */
const SDL_GPU_VERTEXINPUTRATE_INSTANCE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_FILLMODE_FILL
 */
const SDL_GPU_FILLMODE_FILL = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_FILLMODE_LINE
 */
const SDL_GPU_FILLMODE_LINE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_CULLMODE_NONE
 */
const SDL_GPU_CULLMODE_NONE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_CULLMODE_FRONT
 */
const SDL_GPU_CULLMODE_FRONT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_CULLMODE_BACK
 */
const SDL_GPU_CULLMODE_BACK = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE
 */
const SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_FRONTFACE_CLOCKWISE
 */
const SDL_GPU_FRONTFACE_CLOCKWISE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_COMPAREOP_INVALID
 */
const SDL_GPU_COMPAREOP_INVALID = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_COMPAREOP_NEVER
 */
const SDL_GPU_COMPAREOP_NEVER = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_COMPAREOP_LESS
 */
const SDL_GPU_COMPAREOP_LESS = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_COMPAREOP_EQUAL
 */
const SDL_GPU_COMPAREOP_EQUAL = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_COMPAREOP_LESS_OR_EQUAL
 */
const SDL_GPU_COMPAREOP_LESS_OR_EQUAL = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_COMPAREOP_GREATER
 */
const SDL_GPU_COMPAREOP_GREATER = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_COMPAREOP_NOT_EQUAL
 */
const SDL_GPU_COMPAREOP_NOT_EQUAL = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_COMPAREOP_GREATER_OR_EQUAL
 */
const SDL_GPU_COMPAREOP_GREATER_OR_EQUAL = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_COMPAREOP_ALWAYS
 */
const SDL_GPU_COMPAREOP_ALWAYS = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_STENCILOP_INVALID
 */
const SDL_GPU_STENCILOP_INVALID = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_STENCILOP_KEEP
 */
const SDL_GPU_STENCILOP_KEEP = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_STENCILOP_ZERO
 */
const SDL_GPU_STENCILOP_ZERO = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_STENCILOP_REPLACE
 */
const SDL_GPU_STENCILOP_REPLACE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_STENCILOP_INCREMENT_AND_CLAMP
 */
const SDL_GPU_STENCILOP_INCREMENT_AND_CLAMP = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_STENCILOP_DECREMENT_AND_CLAMP
 */
const SDL_GPU_STENCILOP_DECREMENT_AND_CLAMP = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_STENCILOP_INVERT
 */
const SDL_GPU_STENCILOP_INVERT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_STENCILOP_INCREMENT_AND_WRAP
 */
const SDL_GPU_STENCILOP_INCREMENT_AND_WRAP = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_STENCILOP_DECREMENT_AND_WRAP
 */
const SDL_GPU_STENCILOP_DECREMENT_AND_WRAP = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDOP_INVALID
 */
const SDL_GPU_BLENDOP_INVALID = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDOP_ADD
 */
const SDL_GPU_BLENDOP_ADD = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDOP_SUBTRACT
 */
const SDL_GPU_BLENDOP_SUBTRACT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDOP_REVERSE_SUBTRACT
 */
const SDL_GPU_BLENDOP_REVERSE_SUBTRACT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDOP_MIN
 */
const SDL_GPU_BLENDOP_MIN = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDOP_MAX
 */
const SDL_GPU_BLENDOP_MAX = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_INVALID
 */
const SDL_GPU_BLENDFACTOR_INVALID = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_ZERO
 */
const SDL_GPU_BLENDFACTOR_ZERO = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_ONE
 */
const SDL_GPU_BLENDFACTOR_ONE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_SRC_COLOR
 */
const SDL_GPU_BLENDFACTOR_SRC_COLOR = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_COLOR
 */
const SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_COLOR = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_DST_COLOR
 */
const SDL_GPU_BLENDFACTOR_DST_COLOR = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_ONE_MINUS_DST_COLOR
 */
const SDL_GPU_BLENDFACTOR_ONE_MINUS_DST_COLOR = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_SRC_ALPHA
 */
const SDL_GPU_BLENDFACTOR_SRC_ALPHA = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA
 */
const SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_DST_ALPHA
 */
const SDL_GPU_BLENDFACTOR_DST_ALPHA = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_ONE_MINUS_DST_ALPHA
 */
const SDL_GPU_BLENDFACTOR_ONE_MINUS_DST_ALPHA = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_CONSTANT_COLOR
 */
const SDL_GPU_BLENDFACTOR_CONSTANT_COLOR = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_ONE_MINUS_CONSTANT_COLOR
 */
const SDL_GPU_BLENDFACTOR_ONE_MINUS_CONSTANT_COLOR = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BLENDFACTOR_SRC_ALPHA_SATURATE
 */
const SDL_GPU_BLENDFACTOR_SRC_ALPHA_SATURATE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_FILTER_NEAREST
 */
const SDL_GPU_FILTER_NEAREST = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_FILTER_LINEAR
 */
const SDL_GPU_FILTER_LINEAR = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SAMPLERMIPMAPMODE_NEAREST
 */
const SDL_GPU_SAMPLERMIPMAPMODE_NEAREST = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SAMPLERMIPMAPMODE_LINEAR
 */
const SDL_GPU_SAMPLERMIPMAPMODE_LINEAR = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SAMPLERADDRESSMODE_REPEAT
 */
const SDL_GPU_SAMPLERADDRESSMODE_REPEAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SAMPLERADDRESSMODE_MIRRORED_REPEAT
 */
const SDL_GPU_SAMPLERADDRESSMODE_MIRRORED_REPEAT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE
 */
const SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_PRESENTMODE_VSYNC
 */
const SDL_GPU_PRESENTMODE_VSYNC = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_PRESENTMODE_IMMEDIATE
 */
const SDL_GPU_PRESENTMODE_IMMEDIATE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_PRESENTMODE_MAILBOX
 */
const SDL_GPU_PRESENTMODE_MAILBOX = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SWAPCHAINCOMPOSITION_SDR
 */
const SDL_GPU_SWAPCHAINCOMPOSITION_SDR = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SWAPCHAINCOMPOSITION_SDR_LINEAR
 */
const SDL_GPU_SWAPCHAINCOMPOSITION_SDR_LINEAR = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SWAPCHAINCOMPOSITION_HDR_EXTENDED_LINEAR
 */
const SDL_GPU_SWAPCHAINCOMPOSITION_HDR_EXTENDED_LINEAR = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SWAPCHAINCOMPOSITION_HDR10_ST2084
 */
const SDL_GPU_SWAPCHAINCOMPOSITION_HDR10_ST2084 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREUSAGE_SAMPLER
 */
const SDL_GPU_TEXTUREUSAGE_SAMPLER = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREUSAGE_COLOR_TARGET
 */
const SDL_GPU_TEXTUREUSAGE_COLOR_TARGET = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET
 */
const SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREUSAGE_GRAPHICS_STORAGE_READ
 */
const SDL_GPU_TEXTUREUSAGE_GRAPHICS_STORAGE_READ = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_READ
 */
const SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_READ = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_WRITE
 */
const SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_WRITE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_SIMULTANEOUS_READ_WRITE
 */
const SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_SIMULTANEOUS_READ_WRITE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BUFFERUSAGE_VERTEX
 */
const SDL_GPU_BUFFERUSAGE_VERTEX = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BUFFERUSAGE_INDEX
 */
const SDL_GPU_BUFFERUSAGE_INDEX = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BUFFERUSAGE_INDIRECT
 */
const SDL_GPU_BUFFERUSAGE_INDIRECT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BUFFERUSAGE_GRAPHICS_STORAGE_READ
 */
const SDL_GPU_BUFFERUSAGE_GRAPHICS_STORAGE_READ = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_READ
 */
const SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_READ = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_WRITE
 */
const SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_WRITE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SHADERFORMAT_INVALID
 */
const SDL_GPU_SHADERFORMAT_INVALID = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SHADERFORMAT_PRIVATE
 */
const SDL_GPU_SHADERFORMAT_PRIVATE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SHADERFORMAT_SPIRV
 */
const SDL_GPU_SHADERFORMAT_SPIRV = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SHADERFORMAT_DXBC
 */
const SDL_GPU_SHADERFORMAT_DXBC = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SHADERFORMAT_DXIL
 */
const SDL_GPU_SHADERFORMAT_DXIL = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SHADERFORMAT_MSL
 */
const SDL_GPU_SHADERFORMAT_MSL = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_SHADERFORMAT_METALLIB
 */
const SDL_GPU_SHADERFORMAT_METALLIB = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_COLORCOMPONENT_R
 */
const SDL_GPU_COLORCOMPONENT_R = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_COLORCOMPONENT_G
 */
const SDL_GPU_COLORCOMPONENT_G = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_COLORCOMPONENT_B
 */
const SDL_GPU_COLORCOMPONENT_B = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GPU_COLORCOMPONENT_A
 */
const SDL_GPU_COLORCOMPONENT_A = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_FLIP_NONE
 */
const SDL_FLIP_NONE = UNKNOWN;
