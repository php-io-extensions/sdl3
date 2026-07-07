
extern zend_class_entry *sdl3_sdl_gpu_sdlgpu_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Gpu_SDLGPU);

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGPUSupportsShaderFormats);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGPUSupportsProperties);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUDevice);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUDeviceWithProperties);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDestroyGPUDevice);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetNumGPUDrivers);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUDriver);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUDeviceDriver);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUShaderFormats);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUDeviceProperties);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUComputePipeline);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUGraphicsPipeline);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUSampler);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUShader);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUTexture);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUTransferBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUBufferName);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUTextureName);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLInsertGPUDebugLabel);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLPushGPUDebugGroup);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLPopGPUDebugGroup);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUTexture);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUSampler);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUTransferBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUComputePipeline);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUShader);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUGraphicsPipeline);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLAcquireGPUCommandBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLPushGPUVertexUniformData);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLPushGPUFragmentUniformData);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLPushGPUComputeUniformData);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBeginGPURenderPass);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUGraphicsPipeline);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUViewport);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUScissor);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUBlendConstants);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUStencilReference);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUVertexBuffers);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUIndexBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUVertexSamplers);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUVertexStorageTextures);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUVertexStorageBuffers);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUFragmentSamplers);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUFragmentStorageTextures);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUFragmentStorageBuffers);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDrawGPUIndexedPrimitives);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDrawGPUPrimitives);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDrawGPUPrimitivesIndirect);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDrawGPUIndexedPrimitivesIndirect);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLEndGPURenderPass);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBeginGPUComputePass);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUComputePipeline);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUComputeSamplers);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUComputeStorageTextures);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUComputeStorageBuffers);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDispatchGPUCompute);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDispatchGPUComputeIndirect);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLEndGPUComputePass);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLMapGPUTransferBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLUnmapGPUTransferBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, writeToGPUTransferBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, readFromGPUTransferBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBeginGPUCopyPass);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLUploadToGPUTexture);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLUploadToGPUBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCopyGPUTextureToTexture);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCopyGPUBufferToBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDownloadFromGPUTexture);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDownloadFromGPUBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLEndGPUCopyPass);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGenerateMipmapsForGPUTexture);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBlitGPUTexture);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLWindowSupportsGPUSwapchainComposition);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLWindowSupportsGPUPresentMode);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLClaimWindowForGPUDevice);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseWindowFromGPUDevice);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUSwapchainParameters);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUAllowedFramesInFlight);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUSwapchainTextureFormat);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLAcquireGPUSwapchainTexture);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLWaitForGPUSwapchain);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLWaitAndAcquireGPUSwapchainTexture);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSubmitGPUCommandBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSubmitGPUCommandBufferAndAcquireFence);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCancelGPUCommandBuffer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLWaitForGPUIdle);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLWaitForGPUFences);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLQueryGPUFence);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUFence);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGPUTextureFormatTexelBlockSize);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGPUTextureSupportsFormat);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGPUTextureSupportsSampleCount);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCalculateGPUTextureFormatSize);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetPixelFormatFromGPUTextureFormat);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUTextureFormatFromPixelFormat);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGDKSuspendGPU);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGDKResumeGPU);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPURenderer);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPURendererDevice);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPURenderState);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPURenderStateFragmentUniforms);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPURenderState);
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDestroyGPURenderState);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgpusupportsshaderformats, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, format_flags, IS_LONG, 0)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgpusupportsproperties, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpudevice, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format_flags, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, debug_mode, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpudevicewithproperties, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdldestroygpudevice, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetnumgpudrivers, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgpudriver, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgpudevicedriver, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgpushaderformats, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgpudeviceproperties, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpucomputepipeline, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_INFO(0, createinfo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpugraphicspipeline, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_INFO(0, createinfo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpusampler, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_INFO(0, createinfo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpushader, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_INFO(0, createinfo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategputexture, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_INFO(0, createinfo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpubuffer, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_INFO(0, createinfo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategputransferbuffer, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_INFO(0, createinfo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpubuffername, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgputexturename, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlinsertgpudebuglabel, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlpushgpudebuggroup, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlpopgpudebuggroup, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegputexture, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegpusampler, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sampler, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegpubuffer, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegputransferbuffer, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, transfer_buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegpucomputepipeline, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, compute_pipeline, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegpushader, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, shader, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegpugraphicspipeline, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, graphics_pipeline, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlacquiregpucommandbuffer, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlpushgpuvertexuniformdata, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, slot_index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlpushgpufragmentuniformdata, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, slot_index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlpushgpucomputeuniformdata, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, slot_index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbegingpurenderpass, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
	ZEND_ARG_INFO(0, color_target_infos)
	ZEND_ARG_INFO(0, depth_stencil_target_info)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpugraphicspipeline, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, graphics_pipeline, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpuviewport, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_INFO(0, viewport)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpuscissor, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_INFO(0, scissor)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpublendconstants, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_INFO(0, blend_constants)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpustencilreference, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, reference, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpuvertexbuffers, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_slot, IS_LONG, 0)
	ZEND_ARG_INFO(0, bindings)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpuindexbuffer, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_INFO(0, binding)
	ZEND_ARG_TYPE_INFO(0, index_element_size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpuvertexsamplers, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_slot, IS_LONG, 0)
	ZEND_ARG_INFO(0, bindings)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpuvertexstoragetextures, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_slot, IS_LONG, 0)
	ZEND_ARG_INFO(0, storage_textures)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpuvertexstoragebuffers, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_slot, IS_LONG, 0)
	ZEND_ARG_INFO(0, storage_buffers)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpufragmentsamplers, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_slot, IS_LONG, 0)
	ZEND_ARG_INFO(0, bindings)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpufragmentstoragetextures, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_slot, IS_LONG, 0)
	ZEND_ARG_INFO(0, storage_textures)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpufragmentstoragebuffers, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_slot, IS_LONG, 0)
	ZEND_ARG_INFO(0, storage_buffers)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdldrawgpuindexedprimitives, 0, 6, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, num_indices, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, num_instances, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, vertex_offset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_instance, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdldrawgpuprimitives, 0, 5, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, num_vertices, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, num_instances, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_vertex, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_instance, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdldrawgpuprimitivesindirect, 0, 4, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, draw_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdldrawgpuindexedprimitivesindirect, 0, 4, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, draw_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlendgpurenderpass, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, render_pass, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbegingpucomputepass, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
	ZEND_ARG_INFO(0, storage_texture_bindings)
	ZEND_ARG_INFO(0, storage_buffer_bindings)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpucomputepipeline, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, compute_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, compute_pipeline, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpucomputesamplers, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, compute_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_slot, IS_LONG, 0)
	ZEND_ARG_INFO(0, bindings)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpucomputestoragetextures, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, compute_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_slot, IS_LONG, 0)
	ZEND_ARG_INFO(0, storage_textures)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpucomputestoragebuffers, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, compute_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first_slot, IS_LONG, 0)
	ZEND_ARG_INFO(0, storage_buffers)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdldispatchgpucompute, 0, 4, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, compute_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, groupcount_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, groupcount_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, groupcount_z, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdldispatchgpucomputeindirect, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, compute_pass, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlendgpucomputepass, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, compute_pass, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlmapgputransferbuffer, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, transfer_buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, cycle, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlunmapgputransferbuffer, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, transfer_buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_writetogputransferbuffer, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, transfer_buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, cycle, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_readfromgputransferbuffer, 0, 3, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, transfer_buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, length, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlbegingpucopypass, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdluploadtogputexture, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, copy_pass, IS_LONG, 0)
	ZEND_ARG_INFO(0, source)
	ZEND_ARG_INFO(0, destination)
	ZEND_ARG_TYPE_INFO(0, cycle, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdluploadtogpubuffer, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, copy_pass, IS_LONG, 0)
	ZEND_ARG_INFO(0, source)
	ZEND_ARG_INFO(0, destination)
	ZEND_ARG_TYPE_INFO(0, cycle, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcopygputexturetotexture, 0, 6, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, copy_pass, IS_LONG, 0)
	ZEND_ARG_INFO(0, source)
	ZEND_ARG_INFO(0, destination)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, d, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, cycle, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcopygpubuffertobuffer, 0, 4, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, copy_pass, IS_LONG, 0)
	ZEND_ARG_INFO(0, source)
	ZEND_ARG_INFO(0, destination)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, cycle, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdldownloadfromgputexture, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, copy_pass, IS_LONG, 0)
	ZEND_ARG_INFO(0, source)
	ZEND_ARG_INFO(0, destination)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdldownloadfromgpubuffer, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, copy_pass, IS_LONG, 0)
	ZEND_ARG_INFO(0, source)
	ZEND_ARG_INFO(0, destination)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlendgpucopypass, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, copy_pass, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgeneratemipmapsforgputexture, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlblitgputexture, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
	ZEND_ARG_INFO(0, info)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlwindowsupportsgpuswapchaincomposition, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, swapchain_composition, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlwindowsupportsgpupresentmode, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, present_mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlclaimwindowforgpudevice, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasewindowfromgpudevice, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpuswapchainparameters, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, swapchain_composition, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, present_mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpuallowedframesinflight, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, allowed_frames_in_flight, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgpuswapchaintextureformat, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlacquiregpuswapchaintexture, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlwaitforgpuswapchain, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlwaitandacquiregpuswapchaintexture, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlsubmitgpucommandbuffer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlsubmitgpucommandbufferandacquirefence, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcancelgpucommandbuffer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, command_buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlwaitforgpuidle, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlwaitforgpufences, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, wait_all, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, fences)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlquerygpufence, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fence, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegpufence, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fence, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgputextureformattexelblocksize, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgputexturesupportsformat, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, usage, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgputexturesupportssamplecount, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sample_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcalculategputextureformatsize, 0, 4, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, depth_or_layer_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetpixelformatfromgputextureformat, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgputextureformatfrompixelformat, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgdksuspendgpu, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgdkresumegpu, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpurenderer, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgpurendererdevice, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpurenderstate, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_INFO(0, createinfo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpurenderstatefragmentuniforms, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, state, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, slot_index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpurenderstate, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, state, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_gpu_sdlgpu_sdldestroygpurenderstate, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, state, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_gpu_sdlgpu_method_entry) {
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGPUSupportsShaderFormats, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgpusupportsshaderformats, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGPUSupportsProperties, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgpusupportsproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUDevice, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpudevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUDeviceWithProperties, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpudevicewithproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLDestroyGPUDevice, arginfo_sdl3_sdl_gpu_sdlgpu_sdldestroygpudevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGetNumGPUDrivers, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetnumgpudrivers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUDriver, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgpudriver, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUDeviceDriver, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgpudevicedriver, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUShaderFormats, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgpushaderformats, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUDeviceProperties, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgpudeviceproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUComputePipeline, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpucomputepipeline, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUGraphicsPipeline, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpugraphicspipeline, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUSampler, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpusampler, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUShader, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpushader, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUTexture, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategputexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpubuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUTransferBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategputransferbuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUBufferName, arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpubuffername, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUTextureName, arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgputexturename, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLInsertGPUDebugLabel, arginfo_sdl3_sdl_gpu_sdlgpu_sdlinsertgpudebuglabel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLPushGPUDebugGroup, arginfo_sdl3_sdl_gpu_sdlgpu_sdlpushgpudebuggroup, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLPopGPUDebugGroup, arginfo_sdl3_sdl_gpu_sdlgpu_sdlpopgpudebuggroup, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUTexture, arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegputexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUSampler, arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegpusampler, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegpubuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUTransferBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegputransferbuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUComputePipeline, arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegpucomputepipeline, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUShader, arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegpushader, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUGraphicsPipeline, arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegpugraphicspipeline, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLAcquireGPUCommandBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_sdlacquiregpucommandbuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLPushGPUVertexUniformData, arginfo_sdl3_sdl_gpu_sdlgpu_sdlpushgpuvertexuniformdata, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLPushGPUFragmentUniformData, arginfo_sdl3_sdl_gpu_sdlgpu_sdlpushgpufragmentuniformdata, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLPushGPUComputeUniformData, arginfo_sdl3_sdl_gpu_sdlgpu_sdlpushgpucomputeuniformdata, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBeginGPURenderPass, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbegingpurenderpass, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUGraphicsPipeline, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpugraphicspipeline, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUViewport, arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpuviewport, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUScissor, arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpuscissor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUBlendConstants, arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpublendconstants, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUStencilReference, arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpustencilreference, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUVertexBuffers, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpuvertexbuffers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUIndexBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpuindexbuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUVertexSamplers, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpuvertexsamplers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUVertexStorageTextures, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpuvertexstoragetextures, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUVertexStorageBuffers, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpuvertexstoragebuffers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUFragmentSamplers, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpufragmentsamplers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUFragmentStorageTextures, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpufragmentstoragetextures, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUFragmentStorageBuffers, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpufragmentstoragebuffers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLDrawGPUIndexedPrimitives, arginfo_sdl3_sdl_gpu_sdlgpu_sdldrawgpuindexedprimitives, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLDrawGPUPrimitives, arginfo_sdl3_sdl_gpu_sdlgpu_sdldrawgpuprimitives, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLDrawGPUPrimitivesIndirect, arginfo_sdl3_sdl_gpu_sdlgpu_sdldrawgpuprimitivesindirect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLDrawGPUIndexedPrimitivesIndirect, arginfo_sdl3_sdl_gpu_sdlgpu_sdldrawgpuindexedprimitivesindirect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLEndGPURenderPass, arginfo_sdl3_sdl_gpu_sdlgpu_sdlendgpurenderpass, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBeginGPUComputePass, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbegingpucomputepass, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUComputePipeline, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpucomputepipeline, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUComputeSamplers, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpucomputesamplers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUComputeStorageTextures, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpucomputestoragetextures, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUComputeStorageBuffers, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbindgpucomputestoragebuffers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLDispatchGPUCompute, arginfo_sdl3_sdl_gpu_sdlgpu_sdldispatchgpucompute, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLDispatchGPUComputeIndirect, arginfo_sdl3_sdl_gpu_sdlgpu_sdldispatchgpucomputeindirect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLEndGPUComputePass, arginfo_sdl3_sdl_gpu_sdlgpu_sdlendgpucomputepass, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLMapGPUTransferBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_sdlmapgputransferbuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLUnmapGPUTransferBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_sdlunmapgputransferbuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, writeToGPUTransferBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_writetogputransferbuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, readFromGPUTransferBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_readfromgputransferbuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBeginGPUCopyPass, arginfo_sdl3_sdl_gpu_sdlgpu_sdlbegingpucopypass, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLUploadToGPUTexture, arginfo_sdl3_sdl_gpu_sdlgpu_sdluploadtogputexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLUploadToGPUBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_sdluploadtogpubuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCopyGPUTextureToTexture, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcopygputexturetotexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCopyGPUBufferToBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcopygpubuffertobuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLDownloadFromGPUTexture, arginfo_sdl3_sdl_gpu_sdlgpu_sdldownloadfromgputexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLDownloadFromGPUBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_sdldownloadfromgpubuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLEndGPUCopyPass, arginfo_sdl3_sdl_gpu_sdlgpu_sdlendgpucopypass, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGenerateMipmapsForGPUTexture, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgeneratemipmapsforgputexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLBlitGPUTexture, arginfo_sdl3_sdl_gpu_sdlgpu_sdlblitgputexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLWindowSupportsGPUSwapchainComposition, arginfo_sdl3_sdl_gpu_sdlgpu_sdlwindowsupportsgpuswapchaincomposition, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLWindowSupportsGPUPresentMode, arginfo_sdl3_sdl_gpu_sdlgpu_sdlwindowsupportsgpupresentmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLClaimWindowForGPUDevice, arginfo_sdl3_sdl_gpu_sdlgpu_sdlclaimwindowforgpudevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseWindowFromGPUDevice, arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasewindowfromgpudevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUSwapchainParameters, arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpuswapchainparameters, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUAllowedFramesInFlight, arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpuallowedframesinflight, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUSwapchainTextureFormat, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgpuswapchaintextureformat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLAcquireGPUSwapchainTexture, arginfo_sdl3_sdl_gpu_sdlgpu_sdlacquiregpuswapchaintexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLWaitForGPUSwapchain, arginfo_sdl3_sdl_gpu_sdlgpu_sdlwaitforgpuswapchain, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLWaitAndAcquireGPUSwapchainTexture, arginfo_sdl3_sdl_gpu_sdlgpu_sdlwaitandacquiregpuswapchaintexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLSubmitGPUCommandBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_sdlsubmitgpucommandbuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLSubmitGPUCommandBufferAndAcquireFence, arginfo_sdl3_sdl_gpu_sdlgpu_sdlsubmitgpucommandbufferandacquirefence, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCancelGPUCommandBuffer, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcancelgpucommandbuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLWaitForGPUIdle, arginfo_sdl3_sdl_gpu_sdlgpu_sdlwaitforgpuidle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLWaitForGPUFences, arginfo_sdl3_sdl_gpu_sdlgpu_sdlwaitforgpufences, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLQueryGPUFence, arginfo_sdl3_sdl_gpu_sdlgpu_sdlquerygpufence, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUFence, arginfo_sdl3_sdl_gpu_sdlgpu_sdlreleasegpufence, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGPUTextureFormatTexelBlockSize, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgputextureformattexelblocksize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGPUTextureSupportsFormat, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgputexturesupportsformat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGPUTextureSupportsSampleCount, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgputexturesupportssamplecount, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCalculateGPUTextureFormatSize, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcalculategputextureformatsize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGetPixelFormatFromGPUTextureFormat, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetpixelformatfromgputextureformat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUTextureFormatFromPixelFormat, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgputextureformatfrompixelformat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGDKSuspendGPU, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgdksuspendgpu, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGDKResumeGPU, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgdkresumegpu, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPURenderer, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpurenderer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPURendererDevice, arginfo_sdl3_sdl_gpu_sdlgpu_sdlgetgpurendererdevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPURenderState, arginfo_sdl3_sdl_gpu_sdlgpu_sdlcreategpurenderstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPURenderStateFragmentUniforms, arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpurenderstatefragmentuniforms, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPURenderState, arginfo_sdl3_sdl_gpu_sdlgpu_sdlsetgpurenderstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Gpu_SDLGPU, SDLDestroyGPURenderState, arginfo_sdl3_sdl_gpu_sdlgpu_sdldestroygpurenderstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
