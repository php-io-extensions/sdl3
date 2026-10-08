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

    public static function fromPointer(int $pointer): static {}
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

    public static function fromPointer(int $pointer): static {}
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

    public static function fromPointer(int $pointer): static {}
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

    public static function fromPointer(int $pointer): static {}
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

/** An empty list passes NULL and a count of 0. A non-fence element is a TypeError. A released fence is a ValueError. */
function SDL_WaitForGPUFences(SDL_GPUDevice $device, bool $wait_all, array $fences): bool {}

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

    public static function fromPointer(int $pointer): static {}
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

    public static function fromPointer(int $pointer): static {}
}

function SDL_CreateGPUShader(SDL_GPUDevice $device, SDL_GPUShaderCreateInfo $createinfo): ?SDL_GPUShader {}

function SDL_ReleaseGPUShader(SDL_GPUDevice $device, SDL_GPUShader $shader): void {}

function SDL_CreateGPUGraphicsPipeline(SDL_GPUDevice $device, SDL_GPUGraphicsPipelineCreateInfo $createinfo): ?SDL_GPUGraphicsPipeline {}

function SDL_ReleaseGPUGraphicsPipeline(SDL_GPUDevice $device, SDL_GPUGraphicsPipeline $pipeline): void {}

/** An empty list passes NULL and a count of 0. A wrong element is a TypeError. A released handle inside an element is a ValueError. */
function SDL_BeginGPURenderPass(SDL_GPUCommandBuffer $command_buffer, array $color_target_infos, ?SDL_GPUDepthStencilTargetInfo $depth_stencil_target_info): ?SDL_GPURenderPass {}

function SDL_EndGPURenderPass(SDL_GPURenderPass $render_pass): void {}

function SDL_BindGPUGraphicsPipeline(SDL_GPURenderPass $render_pass, SDL_GPUGraphicsPipeline $pipeline): void {}

function SDL_SetGPUViewport(SDL_GPURenderPass $render_pass, SDL_GPUViewport $viewport): void {}

function SDL_SetGPUScissor(SDL_GPURenderPass $render_pass, SDL_Rect $scissor): void {}

function SDL_SetGPUStencilReference(SDL_GPURenderPass $render_pass, int $reference): void {}

/** An empty list passes NULL and a count of 0. */
function SDL_BindGPUVertexBuffers(SDL_GPURenderPass $render_pass, int $first_slot, array $bindings): void {}

function SDL_BindGPUIndexBuffer(SDL_GPURenderPass $render_pass, SDL_GPUBufferBinding $binding, int $index_element_size): void {}

/** An empty list passes NULL and a count of 0. */
function SDL_BindGPUFragmentSamplers(SDL_GPURenderPass $render_pass, int $first_slot, array $texture_sampler_bindings): void {}

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


