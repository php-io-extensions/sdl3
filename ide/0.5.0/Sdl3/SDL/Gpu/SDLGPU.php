<?php

namespace Sdl3\SDL\Gpu;

/**
 * Bindings for the SDL3 GPU API (SDL_gpu.h) plus the GPU render-state
 * functions from SDL_render.h.
 *
 * All opaque SDL_GPU objects (device, buffers, textures, samplers, shaders,
 * pipelines, command buffers, passes, fences, render states) travel across
 * the PHP boundary as opaque int handles. Creation-info structs are assoc
 * arrays that mirror the C struct field names exactly; nested struct lists
 * are arrays of assoc arrays. Shader bytecode and uniform data are binary
 * PHP strings.
 */
class SDLGPU
{


    /**
     * @param int $format_flags
     * @param mixed $name
     * @return bool
     */
    public static function SDLGPUSupportsShaderFormats(int $format_flags, $name = null): bool
    {
    }

    /**
     * @param int $props
     * @return bool
     */
    public static function SDLGPUSupportsProperties(int $props): bool
    {
    }

    /**
     * @param int $format_flags
     * @param bool $debug_mode
     * @param mixed $name
     * @return int
     */
    public static function SDLCreateGPUDevice(int $format_flags, bool $debug_mode, $name = null): int
    {
    }

    /**
     * @param int $props
     * @return int
     */
    public static function SDLCreateGPUDeviceWithProperties(int $props): int
    {
    }

    /**
     * @param int $device
     * @return void
     */
    public static function SDLDestroyGPUDevice(int $device): void
    {
    }

    /**
     * @return int
     */
    public static function SDLGetNumGPUDrivers(): int
    {
    }

    /**
     * @param int $index
     * @return string
     */
    public static function SDLGetGPUDriver(int $index): string
    {
    }

    /**
     * @param int $device
     * @return string
     */
    public static function SDLGetGPUDeviceDriver(int $device): string
    {
    }

    /**
     * @param int $device
     * @return int
     */
    public static function SDLGetGPUShaderFormats(int $device): int
    {
    }

    /**
     * @param int $device
     * @return int
     */
    public static function SDLGetGPUDeviceProperties(int $device): int
    {
    }

    /**
     * createinfo: ["code": string (bytecode), "entrypoint": string, "format": int,
     *  "num_samplers": int, "num_readonly_storage_textures": int,
     *  "num_readonly_storage_buffers": int, "num_readwrite_storage_textures": int,
     *  "num_readwrite_storage_buffers": int, "num_uniform_buffers": int,
     *  "threadcount_x": int, "threadcount_y": int, "threadcount_z": int, "props": int]
     *
     * @param int $device
     * @param mixed $createinfo
     * @return int
     */
    public static function SDLCreateGPUComputePipeline(int $device, $createinfo): int
    {
    }

    /**
     * createinfo: ["vertex_shader": int, "fragment_shader": int,
     *  "vertex_input_state": ["vertex_buffer_descriptions": array, "vertex_attributes": array],
     *  "primitive_type": int, "rasterizer_state": array, "multisample_state": array,
     *  "depth_stencil_state": array,
     *  "target_info": ["color_target_descriptions": array, "depth_stencil_format": int,
     *                  "has_depth_stencil_target": bool],
     *  "props": int]
     *
     * @param int $device
     * @param mixed $createinfo
     * @return int
     */
    public static function SDLCreateGPUGraphicsPipeline(int $device, $createinfo): int
    {
    }

    /**
     * createinfo: ["min_filter": int, "mag_filter": int, "mipmap_mode": int,
     *  "address_mode_u": int, "address_mode_v": int, "address_mode_w": int,
     *  "mip_lod_bias": float, "max_anisotropy": float, "compare_op": int,
     *  "min_lod": float, "max_lod": float, "enable_anisotropy": bool,
     *  "enable_compare": bool, "props": int]
     *
     * @param int $device
     * @param mixed $createinfo
     * @return int
     */
    public static function SDLCreateGPUSampler(int $device, $createinfo): int
    {
    }

    /**
     * createinfo: ["code": string (bytecode), "entrypoint": string, "format": int,
     *  "stage": int, "num_samplers": int, "num_storage_textures": int,
     *  "num_storage_buffers": int, "num_uniform_buffers": int, "props": int]
     *
     * @param int $device
     * @param mixed $createinfo
     * @return int
     */
    public static function SDLCreateGPUShader(int $device, $createinfo): int
    {
    }

    /**
     * createinfo: ["type": int, "format": int, "usage": int, "width": int,
     *  "height": int, "layer_count_or_depth": int, "num_levels": int,
     *  "sample_count": int, "props": int]
     *
     * @param int $device
     * @param mixed $createinfo
     * @return int
     */
    public static function SDLCreateGPUTexture(int $device, $createinfo): int
    {
    }

    /**
     * createinfo: ["usage": int, "size": int, "props": int]
     *
     * @param int $device
     * @param mixed $createinfo
     * @return int
     */
    public static function SDLCreateGPUBuffer(int $device, $createinfo): int
    {
    }

    /**
     * createinfo: ["usage": int, "size": int, "props": int]
     *
     * @param int $device
     * @param mixed $createinfo
     * @return int
     */
    public static function SDLCreateGPUTransferBuffer(int $device, $createinfo): int
    {
    }

    /**
     * @param int $device
     * @param int $buffer
     * @param string $text
     * @return void
     */
    public static function SDLSetGPUBufferName(int $device, int $buffer, string $text): void
    {
    }

    /**
     * @param int $device
     * @param int $texture
     * @param string $text
     * @return void
     */
    public static function SDLSetGPUTextureName(int $device, int $texture, string $text): void
    {
    }

    /**
     * @param int $command_buffer
     * @param string $text
     * @return void
     */
    public static function SDLInsertGPUDebugLabel(int $command_buffer, string $text): void
    {
    }

    /**
     * @param int $command_buffer
     * @param string $name
     * @return void
     */
    public static function SDLPushGPUDebugGroup(int $command_buffer, string $name): void
    {
    }

    /**
     * @param int $command_buffer
     * @return void
     */
    public static function SDLPopGPUDebugGroup(int $command_buffer): void
    {
    }

    /**
     * @param int $device
     * @param int $texture
     * @return void
     */
    public static function SDLReleaseGPUTexture(int $device, int $texture): void
    {
    }

    /**
     * @param int $device
     * @param int $sampler
     * @return void
     */
    public static function SDLReleaseGPUSampler(int $device, int $sampler): void
    {
    }

    /**
     * @param int $device
     * @param int $buffer
     * @return void
     */
    public static function SDLReleaseGPUBuffer(int $device, int $buffer): void
    {
    }

    /**
     * @param int $device
     * @param int $transfer_buffer
     * @return void
     */
    public static function SDLReleaseGPUTransferBuffer(int $device, int $transfer_buffer): void
    {
    }

    /**
     * @param int $device
     * @param int $compute_pipeline
     * @return void
     */
    public static function SDLReleaseGPUComputePipeline(int $device, int $compute_pipeline): void
    {
    }

    /**
     * @param int $device
     * @param int $shader
     * @return void
     */
    public static function SDLReleaseGPUShader(int $device, int $shader): void
    {
    }

    /**
     * @param int $device
     * @param int $graphics_pipeline
     * @return void
     */
    public static function SDLReleaseGPUGraphicsPipeline(int $device, int $graphics_pipeline): void
    {
    }

    /**
     * @param int $device
     * @return int
     */
    public static function SDLAcquireGPUCommandBuffer(int $device): int
    {
    }

    /**
     * @param int $command_buffer
     * @param int $slot_index
     * @param string $data
     * @return void
     */
    public static function SDLPushGPUVertexUniformData(int $command_buffer, int $slot_index, string $data): void
    {
    }

    /**
     * @param int $command_buffer
     * @param int $slot_index
     * @param string $data
     * @return void
     */
    public static function SDLPushGPUFragmentUniformData(int $command_buffer, int $slot_index, string $data): void
    {
    }

    /**
     * @param int $command_buffer
     * @param int $slot_index
     * @param string $data
     * @return void
     */
    public static function SDLPushGPUComputeUniformData(int $command_buffer, int $slot_index, string $data): void
    {
    }

    /**
     * color_target_infos: array of ["texture": int, "mip_level": int,
     *  "layer_or_depth_plane": int, "clear_color": ["r","g","b","a"],
     *  "load_op": int, "store_op": int, "resolve_texture": int,
     *  "resolve_mip_level": int, "resolve_layer": int, "cycle": bool,
     *  "cycle_resolve_texture": bool]
     * depth_stencil_target_info: assoc array or null.
     *
     * @param int $command_buffer
     * @param mixed $color_target_infos
     * @param mixed $depth_stencil_target_info
     * @return int
     */
    public static function SDLBeginGPURenderPass(int $command_buffer, $color_target_infos, $depth_stencil_target_info = null): int
    {
    }

    /**
     * @param int $render_pass
     * @param int $graphics_pipeline
     * @return void
     */
    public static function SDLBindGPUGraphicsPipeline(int $render_pass, int $graphics_pipeline): void
    {
    }

    /**
     * viewport: ["x", "y", "w", "h", "min_depth", "max_depth"]
     *
     * @param int $render_pass
     * @param mixed $viewport
     * @return void
     */
    public static function SDLSetGPUViewport(int $render_pass, $viewport): void
    {
    }

    /**
     * scissor: ["x": int, "y": int, "w": int, "h": int]
     *
     * @param int $render_pass
     * @param mixed $scissor
     * @return void
     */
    public static function SDLSetGPUScissor(int $render_pass, $scissor): void
    {
    }

    /**
     * blend_constants: ["r", "g", "b", "a"] floats
     *
     * @param int $render_pass
     * @param mixed $blend_constants
     * @return void
     */
    public static function SDLSetGPUBlendConstants(int $render_pass, $blend_constants): void
    {
    }

    /**
     * @param int $render_pass
     * @param int $reference
     * @return void
     */
    public static function SDLSetGPUStencilReference(int $render_pass, int $reference): void
    {
    }

    /**
     * bindings: array of ["buffer": int, "offset": int]
     *
     * @param int $render_pass
     * @param int $first_slot
     * @param mixed $bindings
     * @return void
     */
    public static function SDLBindGPUVertexBuffers(int $render_pass, int $first_slot, $bindings): void
    {
    }

    /**
     * binding: ["buffer": int, "offset": int]
     *
     * @param int $render_pass
     * @param mixed $binding
     * @param int $index_element_size
     * @return void
     */
    public static function SDLBindGPUIndexBuffer(int $render_pass, $binding, int $index_element_size): void
    {
    }

    /**
     * bindings: array of ["texture": int, "sampler": int]
     *
     * @param int $render_pass
     * @param int $first_slot
     * @param mixed $bindings
     * @return void
     */
    public static function SDLBindGPUVertexSamplers(int $render_pass, int $first_slot, $bindings): void
    {
    }

    /**
     * storage_textures: array of int texture handles
     *
     * @param int $render_pass
     * @param int $first_slot
     * @param mixed $storage_textures
     * @return void
     */
    public static function SDLBindGPUVertexStorageTextures(int $render_pass, int $first_slot, $storage_textures): void
    {
    }

    /**
     * storage_buffers: array of int buffer handles
     *
     * @param int $render_pass
     * @param int $first_slot
     * @param mixed $storage_buffers
     * @return void
     */
    public static function SDLBindGPUVertexStorageBuffers(int $render_pass, int $first_slot, $storage_buffers): void
    {
    }

    /**
     * bindings: array of ["texture": int, "sampler": int]
     *
     * @param int $render_pass
     * @param int $first_slot
     * @param mixed $bindings
     * @return void
     */
    public static function SDLBindGPUFragmentSamplers(int $render_pass, int $first_slot, $bindings): void
    {
    }

    /**
     * storage_textures: array of int texture handles
     *
     * @param int $render_pass
     * @param int $first_slot
     * @param mixed $storage_textures
     * @return void
     */
    public static function SDLBindGPUFragmentStorageTextures(int $render_pass, int $first_slot, $storage_textures): void
    {
    }

    /**
     * storage_buffers: array of int buffer handles
     *
     * @param int $render_pass
     * @param int $first_slot
     * @param mixed $storage_buffers
     * @return void
     */
    public static function SDLBindGPUFragmentStorageBuffers(int $render_pass, int $first_slot, $storage_buffers): void
    {
    }

    /**
     * @param int $render_pass
     * @param int $num_indices
     * @param int $num_instances
     * @param int $first_index
     * @param int $vertex_offset
     * @param int $first_instance
     * @return void
     */
    public static function SDLDrawGPUIndexedPrimitives(int $render_pass, int $num_indices, int $num_instances, int $first_index, int $vertex_offset, int $first_instance): void
    {
    }

    /**
     * @param int $render_pass
     * @param int $num_vertices
     * @param int $num_instances
     * @param int $first_vertex
     * @param int $first_instance
     * @return void
     */
    public static function SDLDrawGPUPrimitives(int $render_pass, int $num_vertices, int $num_instances, int $first_vertex, int $first_instance): void
    {
    }

    /**
     * @param int $render_pass
     * @param int $buffer
     * @param int $offset
     * @param int $draw_count
     * @return void
     */
    public static function SDLDrawGPUPrimitivesIndirect(int $render_pass, int $buffer, int $offset, int $draw_count): void
    {
    }

    /**
     * @param int $render_pass
     * @param int $buffer
     * @param int $offset
     * @param int $draw_count
     * @return void
     */
    public static function SDLDrawGPUIndexedPrimitivesIndirect(int $render_pass, int $buffer, int $offset, int $draw_count): void
    {
    }

    /**
     * @param int $render_pass
     * @return void
     */
    public static function SDLEndGPURenderPass(int $render_pass): void
    {
    }

    /**
     * storage_texture_bindings: array of ["texture": int, "mip_level": int, "layer": int, "cycle": bool]
     * storage_buffer_bindings: array of ["buffer": int, "cycle": bool]
     *
     * @param int $command_buffer
     * @param mixed $storage_texture_bindings
     * @param mixed $storage_buffer_bindings
     * @return int
     */
    public static function SDLBeginGPUComputePass(int $command_buffer, $storage_texture_bindings = null, $storage_buffer_bindings = null): int
    {
    }

    /**
     * @param int $compute_pass
     * @param int $compute_pipeline
     * @return void
     */
    public static function SDLBindGPUComputePipeline(int $compute_pass, int $compute_pipeline): void
    {
    }

    /**
     * bindings: array of ["texture": int, "sampler": int]
     *
     * @param int $compute_pass
     * @param int $first_slot
     * @param mixed $bindings
     * @return void
     */
    public static function SDLBindGPUComputeSamplers(int $compute_pass, int $first_slot, $bindings): void
    {
    }

    /**
     * storage_textures: array of int texture handles
     *
     * @param int $compute_pass
     * @param int $first_slot
     * @param mixed $storage_textures
     * @return void
     */
    public static function SDLBindGPUComputeStorageTextures(int $compute_pass, int $first_slot, $storage_textures): void
    {
    }

    /**
     * storage_buffers: array of int buffer handles
     *
     * @param int $compute_pass
     * @param int $first_slot
     * @param mixed $storage_buffers
     * @return void
     */
    public static function SDLBindGPUComputeStorageBuffers(int $compute_pass, int $first_slot, $storage_buffers): void
    {
    }

    /**
     * @param int $compute_pass
     * @param int $groupcount_x
     * @param int $groupcount_y
     * @param int $groupcount_z
     * @return void
     */
    public static function SDLDispatchGPUCompute(int $compute_pass, int $groupcount_x, int $groupcount_y, int $groupcount_z): void
    {
    }

    /**
     * @param int $compute_pass
     * @param int $buffer
     * @param int $offset
     * @return void
     */
    public static function SDLDispatchGPUComputeIndirect(int $compute_pass, int $buffer, int $offset): void
    {
    }

    /**
     * @param int $compute_pass
     * @return void
     */
    public static function SDLEndGPUComputePass(int $compute_pass): void
    {
    }

    /**
     * Returns the mapped memory address as an opaque int. Prefer the
     * writeToGPUTransferBuffer / readFromGPUTransferBuffer helpers, which
     * handle the map/copy/unmap cycle with PHP binary strings.
     *
     * @param int $device
     * @param int $transfer_buffer
     * @param bool $cycle
     * @return int
     */
    public static function SDLMapGPUTransferBuffer(int $device, int $transfer_buffer, bool $cycle = false): int
    {
    }

    /**
     * @param int $device
     * @param int $transfer_buffer
     * @return void
     */
    public static function SDLUnmapGPUTransferBuffer(int $device, int $transfer_buffer): void
    {
    }

    /**
     * Helper: maps the transfer buffer, copies the binary string into it at
     * the given byte offset, and unmaps it.
     *
     * @param int $device
     * @param int $transfer_buffer
     * @param string $data
     * @param bool $cycle
     * @param int $offset
     * @return bool
     */
    public static function writeToGPUTransferBuffer(int $device, int $transfer_buffer, string $data, bool $cycle = false, int $offset = 0): bool
    {
    }

    /**
     * Helper: maps the transfer buffer, copies `length` bytes out from the
     * given byte offset as a binary string, and unmaps it.
     *
     * @param int $device
     * @param int $transfer_buffer
     * @param int $length
     * @param int $offset
     * @return string
     */
    public static function readFromGPUTransferBuffer(int $device, int $transfer_buffer, int $length, int $offset = 0): string
    {
    }

    /**
     * @param int $command_buffer
     * @return int
     */
    public static function SDLBeginGPUCopyPass(int $command_buffer): int
    {
    }

    /**
     * source: ["transfer_buffer": int, "offset": int, "pixels_per_row": int, "rows_per_layer": int]
     * destination: ["texture": int, "mip_level": int, "layer": int, "x", "y", "z", "w", "h", "d"]
     *
     * @param int $copy_pass
     * @param mixed $source
     * @param mixed $destination
     * @param bool $cycle
     * @return void
     */
    public static function SDLUploadToGPUTexture(int $copy_pass, $source, $destination, bool $cycle = false): void
    {
    }

    /**
     * source: ["transfer_buffer": int, "offset": int]
     * destination: ["buffer": int, "offset": int, "size": int]
     *
     * @param int $copy_pass
     * @param mixed $source
     * @param mixed $destination
     * @param bool $cycle
     * @return void
     */
    public static function SDLUploadToGPUBuffer(int $copy_pass, $source, $destination, bool $cycle = false): void
    {
    }

    /**
     * source/destination: ["texture": int, "mip_level": int, "layer": int, "x", "y", "z"]
     *
     * @param int $copy_pass
     * @param mixed $source
     * @param mixed $destination
     * @param int $w
     * @param int $h
     * @param int $d
     * @param bool $cycle
     * @return void
     */
    public static function SDLCopyGPUTextureToTexture(int $copy_pass, $source, $destination, int $w, int $h, int $d, bool $cycle = false): void
    {
    }

    /**
     * source/destination: ["buffer": int, "offset": int]
     *
     * @param int $copy_pass
     * @param mixed $source
     * @param mixed $destination
     * @param int $size
     * @param bool $cycle
     * @return void
     */
    public static function SDLCopyGPUBufferToBuffer(int $copy_pass, $source, $destination, int $size, bool $cycle = false): void
    {
    }

    /**
     * source: texture region, destination: texture transfer info.
     *
     * @param int $copy_pass
     * @param mixed $source
     * @param mixed $destination
     * @return void
     */
    public static function SDLDownloadFromGPUTexture(int $copy_pass, $source, $destination): void
    {
    }

    /**
     * source: buffer region, destination: transfer buffer location.
     *
     * @param int $copy_pass
     * @param mixed $source
     * @param mixed $destination
     * @return void
     */
    public static function SDLDownloadFromGPUBuffer(int $copy_pass, $source, $destination): void
    {
    }

    /**
     * @param int $copy_pass
     * @return void
     */
    public static function SDLEndGPUCopyPass(int $copy_pass): void
    {
    }

    /**
     * @param int $command_buffer
     * @param int $texture
     * @return void
     */
    public static function SDLGenerateMipmapsForGPUTexture(int $command_buffer, int $texture): void
    {
    }

    /**
     * info: ["source": blit region, "destination": blit region, "load_op": int,
     *  "clear_color": ["r","g","b","a"], "flip_mode": int, "filter": int, "cycle": bool]
     *
     * @param int $command_buffer
     * @param mixed $info
     * @return void
     */
    public static function SDLBlitGPUTexture(int $command_buffer, $info): void
    {
    }

    /**
     * @param int $device
     * @param int $window
     * @param int $swapchain_composition
     * @return bool
     */
    public static function SDLWindowSupportsGPUSwapchainComposition(int $device, int $window, int $swapchain_composition): bool
    {
    }

    /**
     * @param int $device
     * @param int $window
     * @param int $present_mode
     * @return bool
     */
    public static function SDLWindowSupportsGPUPresentMode(int $device, int $window, int $present_mode): bool
    {
    }

    /**
     * @param int $device
     * @param int $window
     * @return bool
     */
    public static function SDLClaimWindowForGPUDevice(int $device, int $window): bool
    {
    }

    /**
     * @param int $device
     * @param int $window
     * @return void
     */
    public static function SDLReleaseWindowFromGPUDevice(int $device, int $window): void
    {
    }

    /**
     * @param int $device
     * @param int $window
     * @param int $swapchain_composition
     * @param int $present_mode
     * @return bool
     */
    public static function SDLSetGPUSwapchainParameters(int $device, int $window, int $swapchain_composition, int $present_mode): bool
    {
    }

    /**
     * @param int $device
     * @param int $allowed_frames_in_flight
     * @return bool
     */
    public static function SDLSetGPUAllowedFramesInFlight(int $device, int $allowed_frames_in_flight): bool
    {
    }

    /**
     * @param int $device
     * @param int $window
     * @return int
     */
    public static function SDLGetGPUSwapchainTextureFormat(int $device, int $window): int
    {
    }

    /**
     * Returns ["texture": int, "width": int, "height": int]; "texture" is 0
     * when the swapchain is not ready (too many frames in flight).
     *
     * @param int $command_buffer
     * @param int $window
     * @return array
     */
    public static function SDLAcquireGPUSwapchainTexture(int $command_buffer, int $window): array
    {
    }

    /**
     * @param int $device
     * @param int $window
     * @return bool
     */
    public static function SDLWaitForGPUSwapchain(int $device, int $window): bool
    {
    }

    /**
     * Returns ["texture": int, "width": int, "height": int].
     *
     * @param int $command_buffer
     * @param int $window
     * @return array
     */
    public static function SDLWaitAndAcquireGPUSwapchainTexture(int $command_buffer, int $window): array
    {
    }

    /**
     * @param int $command_buffer
     * @return bool
     */
    public static function SDLSubmitGPUCommandBuffer(int $command_buffer): bool
    {
    }

    /**
     * @param int $command_buffer
     * @return int
     */
    public static function SDLSubmitGPUCommandBufferAndAcquireFence(int $command_buffer): int
    {
    }

    /**
     * @param int $command_buffer
     * @return bool
     */
    public static function SDLCancelGPUCommandBuffer(int $command_buffer): bool
    {
    }

    /**
     * @param int $device
     * @return bool
     */
    public static function SDLWaitForGPUIdle(int $device): bool
    {
    }

    /**
     * fences: array of int fence handles
     *
     * @param int $device
     * @param bool $wait_all
     * @param mixed $fences
     * @return bool
     */
    public static function SDLWaitForGPUFences(int $device, bool $wait_all, $fences): bool
    {
    }

    /**
     * @param int $device
     * @param int $fence
     * @return bool
     */
    public static function SDLQueryGPUFence(int $device, int $fence): bool
    {
    }

    /**
     * @param int $device
     * @param int $fence
     * @return void
     */
    public static function SDLReleaseGPUFence(int $device, int $fence): void
    {
    }

    /**
     * @param int $format
     * @return int
     */
    public static function SDLGPUTextureFormatTexelBlockSize(int $format): int
    {
    }

    /**
     * @param int $device
     * @param int $format
     * @param int $type
     * @param int $usage
     * @return bool
     */
    public static function SDLGPUTextureSupportsFormat(int $device, int $format, int $type, int $usage): bool
    {
    }

    /**
     * @param int $device
     * @param int $format
     * @param int $sample_count
     * @return bool
     */
    public static function SDLGPUTextureSupportsSampleCount(int $device, int $format, int $sample_count): bool
    {
    }

    /**
     * @param int $format
     * @param int $width
     * @param int $height
     * @param int $depth_or_layer_count
     * @return int
     */
    public static function SDLCalculateGPUTextureFormatSize(int $format, int $width, int $height, int $depth_or_layer_count): int
    {
    }

    /**
     * @param int $format
     * @return int
     */
    public static function SDLGetPixelFormatFromGPUTextureFormat(int $format): int
    {
    }

    /**
     * @param int $format
     * @return int
     */
    public static function SDLGetGPUTextureFormatFromPixelFormat(int $format): int
    {
    }

    /**
     * Only functional on GDK (Xbox) builds; throws elsewhere.
     *
     * @param int $device
     * @return void
     */
    public static function SDLGDKSuspendGPU(int $device): void
    {
    }

    /**
     * Only functional on GDK (Xbox) builds; throws elsewhere.
     *
     * @param int $device
     * @return void
     */
    public static function SDLGDKResumeGPU(int $device): void
    {
    }

    /**
     * @param int $device
     * @param int $window
     * @return int
     */
    public static function SDLCreateGPURenderer(int $device, int $window): int
    {
    }

    /**
     * @param int $renderer
     * @return int
     */
    public static function SDLGetGPURendererDevice(int $renderer): int
    {
    }

    /**
     * createinfo: ["fragment_shader": int,
     *  "sampler_bindings": array of ["texture": int, "sampler": int],
     *  "storage_textures": array of int, "storage_buffers": array of int,
     *  "props": int]
     *
     * @param int $renderer
     * @param mixed $createinfo
     * @return int
     */
    public static function SDLCreateGPURenderState(int $renderer, $createinfo): int
    {
    }

    /**
     * @param int $state
     * @param int $slot_index
     * @param string $data
     * @return bool
     */
    public static function SDLSetGPURenderStateFragmentUniforms(int $state, int $slot_index, string $data): bool
    {
    }

    /**
     * Pass state = 0 to clear the current render state.
     *
     * @param int $renderer
     * @param int $state
     * @return bool
     */
    public static function SDLSetGPURenderState(int $renderer, int $state = 0): bool
    {
    }

    /**
     * @param int $state
     * @return void
     */
    public static function SDLDestroyGPURenderState(int $state): void
    {
    }
}
