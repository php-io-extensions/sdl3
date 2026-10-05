/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 88419444d0350d9047825d66b53ec9dae5226c41 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_CreateGPUDevice, 0, 3, SDL_GPUDevice, 1)
	ZEND_ARG_TYPE_INFO(0, format_flags, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, debug_mode, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_DestroyGPUDevice, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetGPUDeviceDriver, 0, 1, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetGPUShaderFormats, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_CreateGPUTexture, 0, 2, SDL_GPUTexture, 1)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, createinfo, SDL_GPUTextureCreateInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_ReleaseGPUTexture, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, texture, SDL_GPUTexture, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GPUTextureSupportsFormat, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, usage, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GPUTextureSupportsSampleCount, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sample_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_CreateGPUSampler, 0, 2, SDL_GPUSampler, 1)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, createinfo, SDL_GPUSamplerCreateInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_ReleaseGPUSampler, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, sampler, SDL_GPUSampler, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_CreateGPUBuffer, 0, 2, SDL_GPUBuffer, 1)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, createinfo, SDL_GPUBufferCreateInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_ReleaseGPUBuffer, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, buffer, SDL_GPUBuffer, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_CreateGPUTransferBuffer, 0, 2, SDL_GPUTransferBuffer, 1)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, createinfo, SDL_GPUTransferBufferCreateInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_ReleaseGPUTransferBuffer, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, transfer_buffer, SDL_GPUTransferBuffer, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_MapGPUTransferBuffer, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, transfer_buffer, SDL_GPUTransferBuffer, 0)
	ZEND_ARG_TYPE_INFO(0, cycle, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_UnmapGPUTransferBuffer arginfo_SDL_ReleaseGPUTransferBuffer

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_AcquireGPUCommandBuffer, 0, 1, SDL_GPUCommandBuffer, 1)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SubmitGPUCommandBuffer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, command_buffer, SDL_GPUCommandBuffer, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_SubmitGPUCommandBufferAndAcquireFence, 0, 1, SDL_GPUFence, 1)
	ZEND_ARG_OBJ_INFO(0, command_buffer, SDL_GPUCommandBuffer, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_CancelGPUCommandBuffer arginfo_SDL_SubmitGPUCommandBuffer

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_QueryGPUFence, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, fence, SDL_GPUFence, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_ReleaseGPUFence, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, fence, SDL_GPUFence, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_WaitForGPUFences, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_TYPE_INFO(0, wait_all, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, fences, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_WaitForGPUIdle, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_BeginGPUCopyPass, 0, 1, SDL_GPUCopyPass, 1)
	ZEND_ARG_OBJ_INFO(0, command_buffer, SDL_GPUCommandBuffer, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_UploadToGPUTexture, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, copy_pass, SDL_GPUCopyPass, 0)
	ZEND_ARG_OBJ_INFO(0, source, SDL_GPUTextureTransferInfo, 0)
	ZEND_ARG_OBJ_INFO(0, destination, SDL_GPUTextureRegion, 0)
	ZEND_ARG_TYPE_INFO(0, cycle, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_UploadToGPUBuffer, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, copy_pass, SDL_GPUCopyPass, 0)
	ZEND_ARG_OBJ_INFO(0, source, SDL_GPUTransferBufferLocation, 0)
	ZEND_ARG_OBJ_INFO(0, destination, SDL_GPUBufferRegion, 0)
	ZEND_ARG_TYPE_INFO(0, cycle, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_DownloadFromGPUTexture, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, copy_pass, SDL_GPUCopyPass, 0)
	ZEND_ARG_OBJ_INFO(0, source, SDL_GPUTextureRegion, 0)
	ZEND_ARG_OBJ_INFO(0, destination, SDL_GPUTextureTransferInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_EndGPUCopyPass, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, copy_pass, SDL_GPUCopyPass, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_CreateGPUShader, 0, 2, SDL_GPUShader, 1)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, createinfo, SDL_GPUShaderCreateInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_ReleaseGPUShader, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, shader, SDL_GPUShader, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_CreateGPUGraphicsPipeline, 0, 2, SDL_GPUGraphicsPipeline, 1)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, createinfo, SDL_GPUGraphicsPipelineCreateInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_ReleaseGPUGraphicsPipeline, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, pipeline, SDL_GPUGraphicsPipeline, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_BeginGPURenderPass, 0, 3, SDL_GPURenderPass, 1)
	ZEND_ARG_OBJ_INFO(0, command_buffer, SDL_GPUCommandBuffer, 0)
	ZEND_ARG_TYPE_INFO(0, color_target_infos, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, depth_stencil_target_info, SDL_GPUDepthStencilTargetInfo, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_EndGPURenderPass, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, render_pass, SDL_GPURenderPass, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_BindGPUGraphicsPipeline, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, render_pass, SDL_GPURenderPass, 0)
	ZEND_ARG_OBJ_INFO(0, pipeline, SDL_GPUGraphicsPipeline, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetGPUViewport, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, render_pass, SDL_GPURenderPass, 0)
	ZEND_ARG_OBJ_INFO(0, viewport, SDL_GPUViewport, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetGPUScissor, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, render_pass, SDL_GPURenderPass, 0)
	ZEND_ARG_OBJ_INFO(0, scissor, SDL_Rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetGPUStencilReference, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, render_pass, SDL_GPURenderPass, 0)
	ZEND_ARG_TYPE_INFO(0, reference, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_BindGPUVertexBuffers, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, render_pass, SDL_GPURenderPass, 0)
	ZEND_ARG_TYPE_INFO(0, first_slot, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bindings, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_BindGPUIndexBuffer, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, render_pass, SDL_GPURenderPass, 0)
	ZEND_ARG_OBJ_INFO(0, binding, SDL_GPUBufferBinding, 0)
	ZEND_ARG_TYPE_INFO(0, index_element_size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_BindGPUFragmentSamplers, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, render_pass, SDL_GPURenderPass, 0)
	ZEND_ARG_TYPE_INFO(0, first_slot, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture_sampler_bindings, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_PushGPUVertexUniformData, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, command_buffer, SDL_GPUCommandBuffer, 0)
	ZEND_ARG_TYPE_INFO(0, slot_index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, length, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_PushGPUFragmentUniformData arginfo_SDL_PushGPUVertexUniformData

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_DrawGPUPrimitives, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, render_pass, SDL_GPURenderPass, 0)
	ZEND_ARG_TYPE_INFO(0, num_vertices, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, num_instances, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_vertex, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_instance, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_DrawGPUIndexedPrimitives, 0, 6, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, render_pass, SDL_GPURenderPass, 0)
	ZEND_ARG_TYPE_INFO(0, num_indices, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, num_instances, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, vertex_offset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_instance, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_BlitGPUTexture, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, command_buffer, SDL_GPUCommandBuffer, 0)
	ZEND_ARG_OBJ_INFO(0, info, SDL_GPUBlitInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_ClaimWindowForGPUDevice, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_ReleaseWindowFromGPUDevice, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetGPUSwapchainParameters, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, swapchain_composition, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, present_mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetGPUSwapchainTextureFormat, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, device, SDL_GPUDevice, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_AcquireGPUSwapchainTexture, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, command_buffer, SDL_GPUCommandBuffer, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_OBJ_INFO(1, swapchain_texture, SDL_GPUTexture, 1)
	ZEND_ARG_TYPE_INFO(1, swapchain_texture_width, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, swapchain_texture_height, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_GPUDevice___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_GPUDevice_pointer, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_GPUDevice_fromPointer, 0, 1, IS_STATIC, 0)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_SDL_GPUCommandBuffer___construct arginfo_class_SDL_GPUDevice___construct

#define arginfo_class_SDL_GPUCommandBuffer_pointer arginfo_class_SDL_GPUDevice_pointer

#define arginfo_class_SDL_GPUCommandBuffer_fromPointer arginfo_class_SDL_GPUDevice_fromPointer

#define arginfo_class_SDL_GPUCopyPass___construct arginfo_class_SDL_GPUDevice___construct

#define arginfo_class_SDL_GPUCopyPass_pointer arginfo_class_SDL_GPUDevice_pointer

#define arginfo_class_SDL_GPUCopyPass_fromPointer arginfo_class_SDL_GPUDevice_fromPointer

#define arginfo_class_SDL_GPUFence___construct arginfo_class_SDL_GPUDevice___construct

#define arginfo_class_SDL_GPUFence_pointer arginfo_class_SDL_GPUDevice_pointer

#define arginfo_class_SDL_GPUFence_fromPointer arginfo_class_SDL_GPUDevice_fromPointer

#define arginfo_class_SDL_GPUGraphicsPipeline___construct arginfo_class_SDL_GPUDevice___construct

#define arginfo_class_SDL_GPUGraphicsPipeline_pointer arginfo_class_SDL_GPUDevice_pointer

#define arginfo_class_SDL_GPUGraphicsPipeline_fromPointer arginfo_class_SDL_GPUDevice_fromPointer

#define arginfo_class_SDL_GPURenderPass___construct arginfo_class_SDL_GPUDevice___construct

#define arginfo_class_SDL_GPURenderPass_pointer arginfo_class_SDL_GPUDevice_pointer

#define arginfo_class_SDL_GPURenderPass_fromPointer arginfo_class_SDL_GPUDevice_fromPointer

ZEND_FUNCTION(SDL_CreateGPUDevice);
ZEND_FUNCTION(SDL_DestroyGPUDevice);
ZEND_FUNCTION(SDL_GetGPUDeviceDriver);
ZEND_FUNCTION(SDL_GetGPUShaderFormats);
ZEND_FUNCTION(SDL_CreateGPUTexture);
ZEND_FUNCTION(SDL_ReleaseGPUTexture);
ZEND_FUNCTION(SDL_GPUTextureSupportsFormat);
ZEND_FUNCTION(SDL_GPUTextureSupportsSampleCount);
ZEND_FUNCTION(SDL_CreateGPUSampler);
ZEND_FUNCTION(SDL_ReleaseGPUSampler);
ZEND_FUNCTION(SDL_CreateGPUBuffer);
ZEND_FUNCTION(SDL_ReleaseGPUBuffer);
ZEND_FUNCTION(SDL_CreateGPUTransferBuffer);
ZEND_FUNCTION(SDL_ReleaseGPUTransferBuffer);
ZEND_FUNCTION(SDL_MapGPUTransferBuffer);
ZEND_FUNCTION(SDL_UnmapGPUTransferBuffer);
ZEND_FUNCTION(SDL_AcquireGPUCommandBuffer);
ZEND_FUNCTION(SDL_SubmitGPUCommandBuffer);
ZEND_FUNCTION(SDL_SubmitGPUCommandBufferAndAcquireFence);
ZEND_FUNCTION(SDL_CancelGPUCommandBuffer);
ZEND_FUNCTION(SDL_QueryGPUFence);
ZEND_FUNCTION(SDL_ReleaseGPUFence);
ZEND_FUNCTION(SDL_WaitForGPUFences);
ZEND_FUNCTION(SDL_WaitForGPUIdle);
ZEND_FUNCTION(SDL_BeginGPUCopyPass);
ZEND_FUNCTION(SDL_UploadToGPUTexture);
ZEND_FUNCTION(SDL_UploadToGPUBuffer);
ZEND_FUNCTION(SDL_DownloadFromGPUTexture);
ZEND_FUNCTION(SDL_EndGPUCopyPass);
ZEND_FUNCTION(SDL_CreateGPUShader);
ZEND_FUNCTION(SDL_ReleaseGPUShader);
ZEND_FUNCTION(SDL_CreateGPUGraphicsPipeline);
ZEND_FUNCTION(SDL_ReleaseGPUGraphicsPipeline);
ZEND_FUNCTION(SDL_BeginGPURenderPass);
ZEND_FUNCTION(SDL_EndGPURenderPass);
ZEND_FUNCTION(SDL_BindGPUGraphicsPipeline);
ZEND_FUNCTION(SDL_SetGPUViewport);
ZEND_FUNCTION(SDL_SetGPUScissor);
ZEND_FUNCTION(SDL_SetGPUStencilReference);
ZEND_FUNCTION(SDL_BindGPUVertexBuffers);
ZEND_FUNCTION(SDL_BindGPUIndexBuffer);
ZEND_FUNCTION(SDL_BindGPUFragmentSamplers);
ZEND_FUNCTION(SDL_PushGPUVertexUniformData);
ZEND_FUNCTION(SDL_PushGPUFragmentUniformData);
ZEND_FUNCTION(SDL_DrawGPUPrimitives);
ZEND_FUNCTION(SDL_DrawGPUIndexedPrimitives);
ZEND_FUNCTION(SDL_BlitGPUTexture);
ZEND_FUNCTION(SDL_ClaimWindowForGPUDevice);
ZEND_FUNCTION(SDL_ReleaseWindowFromGPUDevice);
ZEND_FUNCTION(SDL_SetGPUSwapchainParameters);
ZEND_FUNCTION(SDL_GetGPUSwapchainTextureFormat);
ZEND_FUNCTION(SDL_AcquireGPUSwapchainTexture);
ZEND_METHOD(SDL_GPUDevice, __construct);
ZEND_METHOD(SDL_GPUDevice, pointer);
ZEND_METHOD(SDL_GPUDevice, fromPointer);
ZEND_METHOD(SDL_GPUCommandBuffer, __construct);
ZEND_METHOD(SDL_GPUCommandBuffer, pointer);
ZEND_METHOD(SDL_GPUCommandBuffer, fromPointer);
ZEND_METHOD(SDL_GPUCopyPass, __construct);
ZEND_METHOD(SDL_GPUCopyPass, pointer);
ZEND_METHOD(SDL_GPUCopyPass, fromPointer);
ZEND_METHOD(SDL_GPUFence, __construct);
ZEND_METHOD(SDL_GPUFence, pointer);
ZEND_METHOD(SDL_GPUFence, fromPointer);
ZEND_METHOD(SDL_GPUGraphicsPipeline, __construct);
ZEND_METHOD(SDL_GPUGraphicsPipeline, pointer);
ZEND_METHOD(SDL_GPUGraphicsPipeline, fromPointer);
ZEND_METHOD(SDL_GPURenderPass, __construct);
ZEND_METHOD(SDL_GPURenderPass, pointer);
ZEND_METHOD(SDL_GPURenderPass, fromPointer);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(SDL_CreateGPUDevice, arginfo_SDL_CreateGPUDevice)
	ZEND_FE(SDL_DestroyGPUDevice, arginfo_SDL_DestroyGPUDevice)
	ZEND_FE(SDL_GetGPUDeviceDriver, arginfo_SDL_GetGPUDeviceDriver)
	ZEND_FE(SDL_GetGPUShaderFormats, arginfo_SDL_GetGPUShaderFormats)
	ZEND_FE(SDL_CreateGPUTexture, arginfo_SDL_CreateGPUTexture)
	ZEND_FE(SDL_ReleaseGPUTexture, arginfo_SDL_ReleaseGPUTexture)
	ZEND_FE(SDL_GPUTextureSupportsFormat, arginfo_SDL_GPUTextureSupportsFormat)
	ZEND_FE(SDL_GPUTextureSupportsSampleCount, arginfo_SDL_GPUTextureSupportsSampleCount)
	ZEND_FE(SDL_CreateGPUSampler, arginfo_SDL_CreateGPUSampler)
	ZEND_FE(SDL_ReleaseGPUSampler, arginfo_SDL_ReleaseGPUSampler)
	ZEND_FE(SDL_CreateGPUBuffer, arginfo_SDL_CreateGPUBuffer)
	ZEND_FE(SDL_ReleaseGPUBuffer, arginfo_SDL_ReleaseGPUBuffer)
	ZEND_FE(SDL_CreateGPUTransferBuffer, arginfo_SDL_CreateGPUTransferBuffer)
	ZEND_FE(SDL_ReleaseGPUTransferBuffer, arginfo_SDL_ReleaseGPUTransferBuffer)
	ZEND_FE(SDL_MapGPUTransferBuffer, arginfo_SDL_MapGPUTransferBuffer)
	ZEND_FE(SDL_UnmapGPUTransferBuffer, arginfo_SDL_UnmapGPUTransferBuffer)
	ZEND_FE(SDL_AcquireGPUCommandBuffer, arginfo_SDL_AcquireGPUCommandBuffer)
	ZEND_FE(SDL_SubmitGPUCommandBuffer, arginfo_SDL_SubmitGPUCommandBuffer)
	ZEND_FE(SDL_SubmitGPUCommandBufferAndAcquireFence, arginfo_SDL_SubmitGPUCommandBufferAndAcquireFence)
	ZEND_FE(SDL_CancelGPUCommandBuffer, arginfo_SDL_CancelGPUCommandBuffer)
	ZEND_FE(SDL_QueryGPUFence, arginfo_SDL_QueryGPUFence)
	ZEND_FE(SDL_ReleaseGPUFence, arginfo_SDL_ReleaseGPUFence)
	ZEND_FE(SDL_WaitForGPUFences, arginfo_SDL_WaitForGPUFences)
	ZEND_FE(SDL_WaitForGPUIdle, arginfo_SDL_WaitForGPUIdle)
	ZEND_FE(SDL_BeginGPUCopyPass, arginfo_SDL_BeginGPUCopyPass)
	ZEND_FE(SDL_UploadToGPUTexture, arginfo_SDL_UploadToGPUTexture)
	ZEND_FE(SDL_UploadToGPUBuffer, arginfo_SDL_UploadToGPUBuffer)
	ZEND_FE(SDL_DownloadFromGPUTexture, arginfo_SDL_DownloadFromGPUTexture)
	ZEND_FE(SDL_EndGPUCopyPass, arginfo_SDL_EndGPUCopyPass)
	ZEND_FE(SDL_CreateGPUShader, arginfo_SDL_CreateGPUShader)
	ZEND_FE(SDL_ReleaseGPUShader, arginfo_SDL_ReleaseGPUShader)
	ZEND_FE(SDL_CreateGPUGraphicsPipeline, arginfo_SDL_CreateGPUGraphicsPipeline)
	ZEND_FE(SDL_ReleaseGPUGraphicsPipeline, arginfo_SDL_ReleaseGPUGraphicsPipeline)
	ZEND_FE(SDL_BeginGPURenderPass, arginfo_SDL_BeginGPURenderPass)
	ZEND_FE(SDL_EndGPURenderPass, arginfo_SDL_EndGPURenderPass)
	ZEND_FE(SDL_BindGPUGraphicsPipeline, arginfo_SDL_BindGPUGraphicsPipeline)
	ZEND_FE(SDL_SetGPUViewport, arginfo_SDL_SetGPUViewport)
	ZEND_FE(SDL_SetGPUScissor, arginfo_SDL_SetGPUScissor)
	ZEND_FE(SDL_SetGPUStencilReference, arginfo_SDL_SetGPUStencilReference)
	ZEND_FE(SDL_BindGPUVertexBuffers, arginfo_SDL_BindGPUVertexBuffers)
	ZEND_FE(SDL_BindGPUIndexBuffer, arginfo_SDL_BindGPUIndexBuffer)
	ZEND_FE(SDL_BindGPUFragmentSamplers, arginfo_SDL_BindGPUFragmentSamplers)
	ZEND_FE(SDL_PushGPUVertexUniformData, arginfo_SDL_PushGPUVertexUniformData)
	ZEND_FE(SDL_PushGPUFragmentUniformData, arginfo_SDL_PushGPUFragmentUniformData)
	ZEND_FE(SDL_DrawGPUPrimitives, arginfo_SDL_DrawGPUPrimitives)
	ZEND_FE(SDL_DrawGPUIndexedPrimitives, arginfo_SDL_DrawGPUIndexedPrimitives)
	ZEND_FE(SDL_BlitGPUTexture, arginfo_SDL_BlitGPUTexture)
	ZEND_FE(SDL_ClaimWindowForGPUDevice, arginfo_SDL_ClaimWindowForGPUDevice)
	ZEND_FE(SDL_ReleaseWindowFromGPUDevice, arginfo_SDL_ReleaseWindowFromGPUDevice)
	ZEND_FE(SDL_SetGPUSwapchainParameters, arginfo_SDL_SetGPUSwapchainParameters)
	ZEND_FE(SDL_GetGPUSwapchainTextureFormat, arginfo_SDL_GetGPUSwapchainTextureFormat)
	ZEND_FE(SDL_AcquireGPUSwapchainTexture, arginfo_SDL_AcquireGPUSwapchainTexture)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_GPUDevice_methods[] = {
	ZEND_ME(SDL_GPUDevice, __construct, arginfo_class_SDL_GPUDevice___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SDL_GPUDevice, pointer, arginfo_class_SDL_GPUDevice_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_GPUDevice, fromPointer, arginfo_class_SDL_GPUDevice_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_GPUCommandBuffer_methods[] = {
	ZEND_ME(SDL_GPUCommandBuffer, __construct, arginfo_class_SDL_GPUCommandBuffer___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SDL_GPUCommandBuffer, pointer, arginfo_class_SDL_GPUCommandBuffer_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_GPUCommandBuffer, fromPointer, arginfo_class_SDL_GPUCommandBuffer_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_GPUCopyPass_methods[] = {
	ZEND_ME(SDL_GPUCopyPass, __construct, arginfo_class_SDL_GPUCopyPass___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SDL_GPUCopyPass, pointer, arginfo_class_SDL_GPUCopyPass_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_GPUCopyPass, fromPointer, arginfo_class_SDL_GPUCopyPass_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_GPUFence_methods[] = {
	ZEND_ME(SDL_GPUFence, __construct, arginfo_class_SDL_GPUFence___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SDL_GPUFence, pointer, arginfo_class_SDL_GPUFence_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_GPUFence, fromPointer, arginfo_class_SDL_GPUFence_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_GPUGraphicsPipeline_methods[] = {
	ZEND_ME(SDL_GPUGraphicsPipeline, __construct, arginfo_class_SDL_GPUGraphicsPipeline___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SDL_GPUGraphicsPipeline, pointer, arginfo_class_SDL_GPUGraphicsPipeline_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_GPUGraphicsPipeline, fromPointer, arginfo_class_SDL_GPUGraphicsPipeline_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_GPURenderPass_methods[] = {
	ZEND_ME(SDL_GPURenderPass, __construct, arginfo_class_SDL_GPURenderPass___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SDL_GPURenderPass, pointer, arginfo_class_SDL_GPURenderPass_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_GPURenderPass, fromPointer, arginfo_class_SDL_GPURenderPass_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_SDL_GPUDevice(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_GPUDevice", class_SDL_GPUDevice_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_SDL_GPUCommandBuffer(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_GPUCommandBuffer", class_SDL_GPUCommandBuffer_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_SDL_GPUCopyPass(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_GPUCopyPass", class_SDL_GPUCopyPass_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_SDL_GPUFence(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_GPUFence", class_SDL_GPUFence_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_SDL_GPUGraphicsPipeline(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_GPUGraphicsPipeline", class_SDL_GPUGraphicsPipeline_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_SDL_GPURenderPass(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_GPURenderPass", class_SDL_GPURenderPass_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}
