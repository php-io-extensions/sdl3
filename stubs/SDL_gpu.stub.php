<?php

/** @generate-class-entries */

/**
 * An address other than 0 is trusted.
 *
 * @not-serializable
 */
final class SDL_GPUDevice
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/**
 * An address other than 0 is trusted.
 * Submitted, cancelled, or acquired-with-fence, this handle is released.
 *
 * @not-serializable
 */
final class SDL_GPUCommandBuffer
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/**
 * An address other than 0 is trusted.
 *
 * @not-serializable
 */
final class SDL_GPUCopyPass
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/**
 * An address other than 0 is trusted.
 *
 * @not-serializable
 */
final class SDL_GPUFence
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

function SDL_CreateGPUDevice(int $format_flags, bool $debug_mode, ?string $name): ?SDL_GPUDevice {}

function SDL_DestroyGPUDevice(SDL_GPUDevice $device): void {}

function SDL_GetGPUDeviceDriver(SDL_GPUDevice $device): ?string {}

function SDL_GetGPUShaderFormats(SDL_GPUDevice $device): int {}

function SDL_CreateGPUTexture(SDL_GPUDevice $device, SDL_GPUTextureCreateInfo $createinfo): ?SDL_GPUTexture {}

function SDL_ReleaseGPUTexture(SDL_GPUDevice $device, SDL_GPUTexture $texture): void {}

function SDL_GPUTextureSupportsFormat(SDL_GPUDevice $device, int $format, int $type, int $usage): bool {}

function SDL_GPUTextureSupportsSampleCount(SDL_GPUDevice $device, int $format, int $sample_count): bool {}

function SDL_CreateGPUSampler(SDL_GPUDevice $device, SDL_GPUSamplerCreateInfo $createinfo): ?SDL_GPUSampler {}

function SDL_ReleaseGPUSampler(SDL_GPUDevice $device, SDL_GPUSampler $sampler): void {}

function SDL_CreateGPUBuffer(SDL_GPUDevice $device, SDL_GPUBufferCreateInfo $createinfo): ?SDL_GPUBuffer {}

function SDL_ReleaseGPUBuffer(SDL_GPUDevice $device, SDL_GPUBuffer $buffer): void {}

function SDL_CreateGPUTransferBuffer(SDL_GPUDevice $device, SDL_GPUTransferBufferCreateInfo $createinfo): ?SDL_GPUTransferBuffer {}

function SDL_ReleaseGPUTransferBuffer(SDL_GPUDevice $device, SDL_GPUTransferBuffer $transfer_buffer): void {}

/** The mapped address, or 0 when SDL fails. */
function SDL_MapGPUTransferBuffer(SDL_GPUDevice $device, SDL_GPUTransferBuffer $transfer_buffer, bool $cycle): int {}

function SDL_UnmapGPUTransferBuffer(SDL_GPUDevice $device, SDL_GPUTransferBuffer $transfer_buffer): void {}

function SDL_AcquireGPUCommandBuffer(SDL_GPUDevice $device): ?SDL_GPUCommandBuffer {}

function SDL_SubmitGPUCommandBuffer(SDL_GPUCommandBuffer $command_buffer): bool {}

function SDL_SubmitGPUCommandBufferAndAcquireFence(SDL_GPUCommandBuffer $command_buffer): ?SDL_GPUFence {}

function SDL_CancelGPUCommandBuffer(SDL_GPUCommandBuffer $command_buffer): bool {}

function SDL_QueryGPUFence(SDL_GPUDevice $device, SDL_GPUFence $fence): bool {}

function SDL_ReleaseGPUFence(SDL_GPUDevice $device, SDL_GPUFence $fence): void {}

/** A non-fence element is a TypeError. $num_fences past the list is a ValueError. A released fence is NULL. */
function SDL_WaitForGPUFences(SDL_GPUDevice $device, bool $wait_all, array $fences, int $num_fences): bool {}

function SDL_WaitForGPUIdle(SDL_GPUDevice $device): bool {}

function SDL_BeginGPUCopyPass(SDL_GPUCommandBuffer $command_buffer): ?SDL_GPUCopyPass {}

function SDL_UploadToGPUTexture(SDL_GPUCopyPass $copy_pass, SDL_GPUTextureTransferInfo $source, SDL_GPUTextureRegion $destination, bool $cycle): void {}

function SDL_UploadToGPUBuffer(SDL_GPUCopyPass $copy_pass, SDL_GPUTransferBufferLocation $source, SDL_GPUBufferRegion $destination, bool $cycle): void {}

function SDL_DownloadFromGPUTexture(SDL_GPUCopyPass $copy_pass, SDL_GPUTextureRegion $source, SDL_GPUTextureTransferInfo $destination): void {}

function SDL_EndGPUCopyPass(SDL_GPUCopyPass $copy_pass): void {}

/**
 * An address other than 0 is trusted.
 *
 * @not-serializable
 */
final class SDL_GPUGraphicsPipeline
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/**
 * An address other than 0 is trusted.
 *
 * @not-serializable
 */
final class SDL_GPURenderPass
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

function SDL_CreateGPUShader(SDL_GPUDevice $device, SDL_GPUShaderCreateInfo $createinfo): ?SDL_GPUShader {}

function SDL_ReleaseGPUShader(SDL_GPUDevice $device, SDL_GPUShader $shader): void {}

function SDL_CreateGPUGraphicsPipeline(SDL_GPUDevice $device, SDL_GPUGraphicsPipelineCreateInfo $createinfo): ?SDL_GPUGraphicsPipeline {}

function SDL_ReleaseGPUGraphicsPipeline(SDL_GPUDevice $device, SDL_GPUGraphicsPipeline $pipeline): void {}

/** A wrong element is a TypeError. $num_color_targets past the list is a ValueError. A released handle inside an element is NULL. */
function SDL_BeginGPURenderPass(SDL_GPUCommandBuffer $command_buffer, array $color_target_infos, int $num_color_targets, ?SDL_GPUDepthStencilTargetInfo $depth_stencil_target_info): ?SDL_GPURenderPass {}

function SDL_EndGPURenderPass(SDL_GPURenderPass $render_pass): void {}

function SDL_BindGPUGraphicsPipeline(SDL_GPURenderPass $render_pass, SDL_GPUGraphicsPipeline $pipeline): void {}

function SDL_SetGPUViewport(SDL_GPURenderPass $render_pass, SDL_GPUViewport $viewport): void {}

function SDL_SetGPUScissor(SDL_GPURenderPass $render_pass, SDL_Rect $scissor): void {}

function SDL_SetGPUStencilReference(SDL_GPURenderPass $render_pass, int $reference): void {}

/** $num_bindings past the list is a ValueError. */
function SDL_BindGPUVertexBuffers(SDL_GPURenderPass $render_pass, int $first_slot, array $bindings, int $num_bindings): void {}

function SDL_BindGPUIndexBuffer(SDL_GPURenderPass $render_pass, SDL_GPUBufferBinding $binding, int $index_element_size): void {}

/** $num_bindings past the list is a ValueError. */
function SDL_BindGPUFragmentSamplers(SDL_GPURenderPass $render_pass, int $first_slot, array $texture_sampler_bindings, int $num_bindings): void {}

function SDL_PushGPUVertexUniformData(SDL_GPUCommandBuffer $command_buffer, int $slot_index, string $data, int $length): void {}

function SDL_PushGPUFragmentUniformData(SDL_GPUCommandBuffer $command_buffer, int $slot_index, string $data, int $length): void {}

function SDL_DrawGPUPrimitives(SDL_GPURenderPass $render_pass, int $num_vertices, int $num_instances, int $first_vertex, int $first_instance): void {}

function SDL_DrawGPUIndexedPrimitives(SDL_GPURenderPass $render_pass, int $num_indices, int $num_instances, int $first_index, int $vertex_offset, int $first_instance): void {}

function SDL_BlitGPUTexture(SDL_GPUCommandBuffer $command_buffer, SDL_GPUBlitInfo $info): void {}

function SDL_ClaimWindowForGPUDevice(SDL_GPUDevice $device, SDL_Window $window): bool {}

function SDL_ReleaseWindowFromGPUDevice(SDL_GPUDevice $device, SDL_Window $window): void {}

function SDL_WindowSupportsGPUPresentMode(SDL_GPUDevice $device, SDL_Window $window, int $present_mode): bool {}

function SDL_WindowSupportsGPUSwapchainComposition(SDL_GPUDevice $device, SDL_Window $window, int $swapchain_composition): bool {}

/** 1 to 3 frames the device may have in flight; fewer lowers latency, more raises throughput. SDL checks the range only in its GPU debug mode: a release build answers true for any value. */
function SDL_SetGPUAllowedFramesInFlight(SDL_GPUDevice $device, int $allowed_frames_in_flight): bool {}

/** Blocks until a swapchain texture of $window is free to acquire. */
function SDL_WaitForGPUSwapchain(SDL_GPUDevice $device, SDL_Window $window): bool {}

function SDL_SetGPUSwapchainParameters(SDL_GPUDevice $device, SDL_Window $window, int $swapchain_composition, int $present_mode): bool {}

function SDL_GetGPUSwapchainTextureFormat(SDL_GPUDevice $device, SDL_Window $window): int {}

/** A null texture with true is SDL's "none available yet". The texture, when present, is released when this command buffer is submitted or cancelled. */
/** As SDL_AcquireGPUSwapchainTexture, blocking until a texture is free. A null texture with true: the window is not shown. Released with the command buffer. */
function SDL_WaitAndAcquireGPUSwapchainTexture(SDL_GPUCommandBuffer $command_buffer, SDL_Window $window, ?SDL_GPUTexture &$swapchain_texture, ?int &$swapchain_texture_width, ?int &$swapchain_texture_height): bool {}

function SDL_AcquireGPUSwapchainTexture(SDL_GPUCommandBuffer $command_buffer, SDL_Window $window, ?SDL_GPUTexture &$swapchain_texture, ?int &$swapchain_texture_width, ?int &$swapchain_texture_height): bool {}

/**
 * An address other than 0 is trusted.
 *
 * @not-serializable
 */
final class SDL_GPUComputePipeline
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/**
 * An address other than 0 is trusted.
 * Ended, this handle is released.
 *
 * @not-serializable
 */
final class SDL_GPUComputePass
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

function SDL_GetNumGPUDrivers(): int {}

function SDL_GetGPUDriver(int $index): ?string {}

function SDL_GPUSupportsShaderFormats(int $format_flags, ?string $name): bool {}

function SDL_CreateGPUComputePipeline(SDL_GPUDevice $device, SDL_GPUComputePipelineCreateInfo $createinfo): ?SDL_GPUComputePipeline {}

function SDL_ReleaseGPUComputePipeline(SDL_GPUDevice $device, SDL_GPUComputePipeline $compute_pipeline): void {}

/** A wrong element is a TypeError. A count past its list is a ValueError. A released handle inside an element is NULL. */
function SDL_BeginGPUComputePass(SDL_GPUCommandBuffer $command_buffer, array $storage_texture_bindings, int $num_storage_texture_bindings, array $storage_buffer_bindings, int $num_storage_buffer_bindings): ?SDL_GPUComputePass {}

function SDL_EndGPUComputePass(SDL_GPUComputePass $compute_pass): void {}

function SDL_PushGPUComputeUniformData(SDL_GPUCommandBuffer $command_buffer, int $slot_index, string $data, int $length): void {}

function SDL_BindGPUComputePipeline(SDL_GPUComputePass $compute_pass, SDL_GPUComputePipeline $compute_pipeline): void {}

/** A non-buffer element is a TypeError. $num_bindings past the list is a ValueError. A released buffer is NULL. */
function SDL_BindGPUComputeStorageBuffers(SDL_GPUComputePass $compute_pass, int $first_slot, array $storage_buffers, int $num_bindings): void {}

/** A non-texture element is a TypeError. $num_bindings past the list is a ValueError. A released texture is NULL. */
function SDL_BindGPUComputeStorageTextures(SDL_GPUComputePass $compute_pass, int $first_slot, array $storage_textures, int $num_bindings): void {}

/** $num_bindings past the list is a ValueError. */
function SDL_BindGPUComputeSamplers(SDL_GPUComputePass $compute_pass, int $first_slot, array $texture_sampler_bindings, int $num_bindings): void {}

function SDL_DispatchGPUCompute(SDL_GPUComputePass $compute_pass, int $groupcount_x, int $groupcount_y, int $groupcount_z): void {}

/** A non-buffer element is a TypeError. $num_bindings past the list is a ValueError. A released buffer is NULL. */
function SDL_BindGPUFragmentStorageBuffers(SDL_GPURenderPass $render_pass, int $first_slot, array $storage_buffers, int $num_bindings): void {}

/** A non-texture element is a TypeError. $num_bindings past the list is a ValueError. A released texture is NULL. */
function SDL_BindGPUFragmentStorageTextures(SDL_GPURenderPass $render_pass, int $first_slot, array $storage_textures, int $num_bindings): void {}

function SDL_CopyGPUTextureToTexture(SDL_GPUCopyPass $copy_pass, SDL_GPUTextureLocation $source, SDL_GPUTextureLocation $destination, int $w, int $h, int $d, bool $cycle): void {}

function SDL_CopyGPUBufferToBuffer(SDL_GPUCopyPass $copy_pass, SDL_GPUBufferLocation $source, SDL_GPUBufferLocation $destination, int $size, bool $cycle): void {}

function SDL_DownloadFromGPUBuffer(SDL_GPUCopyPass $copy_pass, SDL_GPUBufferRegion $source, SDL_GPUTransferBufferLocation $destination): void {}


