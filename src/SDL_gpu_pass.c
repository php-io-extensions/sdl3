#include "SDL_gpu_types.h"

zend_class_entry *sdl3_ce_SDL_GPUGraphicsPipeline;
zend_class_entry *sdl3_ce_SDL_GPURenderPass;

SDL3_POINTER_METHODS(SDL_GPUGraphicsPipeline)
SDL3_POINTER_METHODS(SDL_GPURenderPass)

static bool sdl3_list_element(zval *item, zend_class_entry *ce, uint32_t arg_num)
{
	if (Z_TYPE_P(item) != IS_OBJECT || !instanceof_function(Z_OBJCE_P(item), ce)) {
		zend_argument_type_error(arg_num, "must be a list of %s", ZSTR_VAL(ce->name));
		return false;
	}

	return true;
}

static void sdl3_push_uniform(INTERNAL_FUNCTION_PARAMETERS, void (*push)(SDL_GPUCommandBuffer *, Uint32, const void *, Uint32))
{
	zval *command_zv;
	zend_long slot, length;
	zend_string *data;
	SDL_GPUCommandBuffer *command_buffer;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(command_zv, sdl3_ce_SDL_GPUCommandBuffer)
		Z_PARAM_LONG(slot)
		Z_PARAM_STR(data)
		Z_PARAM_LONG(length)
	ZEND_PARSE_PARAMETERS_END();

	if (length < 0 || (size_t) length > ZSTR_LEN(data)) {
		zend_argument_value_error(3, "must hold " ZEND_LONG_FMT " bytes, %zu given", length, ZSTR_LEN(data));
		RETURN_THROWS();
	}

	command_buffer = sdl3_handle_ptr(command_zv, sdl3_ce_SDL_GPUCommandBuffer, 1);
	if (command_buffer == NULL) {
		RETURN_THROWS();
	}

	push(command_buffer, (Uint32) slot, ZSTR_VAL(data), (Uint32) length);
}

ZEND_FUNCTION(SDL_CreateGPUShader)
{
	zval *device_zv;
	zend_object *info_obj;
	SDL_GPUDevice *device;
	SDL_GPUShaderCreateInfo info;
	sdl3_scratch scratch;
	SDL_GPUShader *shader;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJ_OF_CLASS(info_obj, sdl3_ce_SDL_GPUShaderCreateInfo)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_SDL_GPUShaderCreateInfo_from(info_obj, &info, &scratch)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	shader = SDL_CreateGPUShader(device, &info);
	sdl3_scratch_free(&scratch);
	sdl3_box(return_value, shader, sdl3_ce_SDL_GPUShader);
}

ZEND_FUNCTION(SDL_ReleaseGPUShader)
{
	zval *device_zv, *shader_zv;
	SDL_GPUDevice *device;
	SDL_GPUShader *shader;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(shader_zv, sdl3_ce_SDL_GPUShader)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	shader = device != NULL ? sdl3_handle_ptr(shader_zv, sdl3_ce_SDL_GPUShader, 2) : NULL;
	if (device == NULL || shader == NULL) {
		RETURN_THROWS();
	}

	SDL_ReleaseGPUShader(device, shader);
	sdl3_release(Z_OBJ_P(shader_zv));
}

ZEND_FUNCTION(SDL_CreateGPUGraphicsPipeline)
{
	zval *device_zv;
	zend_object *info_obj;
	SDL_GPUDevice *device;
	SDL_GPUGraphicsPipelineCreateInfo info;
	sdl3_scratch scratch;
	SDL_GPUGraphicsPipeline *pipeline;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJ_OF_CLASS(info_obj, sdl3_ce_SDL_GPUGraphicsPipelineCreateInfo)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_SDL_GPUGraphicsPipelineCreateInfo_from(info_obj, &info, &scratch)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	pipeline = SDL_CreateGPUGraphicsPipeline(device, &info);
	sdl3_scratch_free(&scratch);
	sdl3_box(return_value, pipeline, sdl3_ce_SDL_GPUGraphicsPipeline);
}

ZEND_FUNCTION(SDL_ReleaseGPUGraphicsPipeline)
{
	zval *device_zv, *pipeline_zv;
	SDL_GPUDevice *device;
	SDL_GPUGraphicsPipeline *pipeline;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(pipeline_zv, sdl3_ce_SDL_GPUGraphicsPipeline)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	pipeline = device != NULL ? sdl3_handle_ptr(pipeline_zv, sdl3_ce_SDL_GPUGraphicsPipeline, 2) : NULL;
	if (device == NULL || pipeline == NULL) {
		RETURN_THROWS();
	}

	SDL_ReleaseGPUGraphicsPipeline(device, pipeline);
	sdl3_release(Z_OBJ_P(pipeline_zv));
}

ZEND_FUNCTION(SDL_BeginGPURenderPass)
{
	zval *command_zv, *colors_zv, *item;
	zend_object *depth_obj = NULL;
	SDL_GPUCommandBuffer *command_buffer;
	sdl3_scratch scratch;
	uint32_t count, index;
	SDL_GPUColorTargetInfo *colors = NULL;
	SDL_GPUDepthStencilTargetInfo depth;
	const SDL_GPUDepthStencilTargetInfo *depth_ptr = NULL;
	SDL_GPURenderPass *pass;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(command_zv, sdl3_ce_SDL_GPUCommandBuffer)
		Z_PARAM_ARRAY(colors_zv)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(depth_obj, sdl3_ce_SDL_GPUDepthStencilTargetInfo)
	ZEND_PARSE_PARAMETERS_END();

	command_buffer = sdl3_handle_ptr(command_zv, sdl3_ce_SDL_GPUCommandBuffer, 1);
	if (command_buffer == NULL) {
		RETURN_THROWS();
	}

	count = zend_hash_num_elements(Z_ARRVAL_P(colors_zv));
	sdl3_scratch_init(&scratch);
	if (count > 0) {
		colors = sdl3_scratch_alloc(&scratch, sizeof(SDL_GPUColorTargetInfo) * count);
		index = 0;
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(colors_zv), item) {
			if (!sdl3_list_element(item, sdl3_ce_SDL_GPUColorTargetInfo, 2)) {
				sdl3_scratch_free(&scratch);
				RETURN_THROWS();
			}
			if (!sdl3_SDL_GPUColorTargetInfo_from(Z_OBJ_P(item), &colors[index], &scratch)) {
				sdl3_scratch_free(&scratch);
				RETURN_THROWS();
			}
			index++;
		} ZEND_HASH_FOREACH_END();
	}
	if (depth_obj != NULL) {
		if (!sdl3_SDL_GPUDepthStencilTargetInfo_from(depth_obj, &depth, &scratch)) {
			sdl3_scratch_free(&scratch);
			RETURN_THROWS();
		}
		depth_ptr = &depth;
	}

	pass = SDL_BeginGPURenderPass(command_buffer, colors, count, depth_ptr);
	sdl3_scratch_free(&scratch);
	sdl3_box(return_value, pass, sdl3_ce_SDL_GPURenderPass);
}

ZEND_FUNCTION(SDL_EndGPURenderPass)
{
	zval *pass_zv;
	SDL_GPURenderPass *pass;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPURenderPass)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPURenderPass, 1);
	if (pass == NULL) {
		RETURN_THROWS();
	}

	SDL_EndGPURenderPass(pass);
	sdl3_release(Z_OBJ_P(pass_zv));
}

ZEND_FUNCTION(SDL_BindGPUGraphicsPipeline)
{
	zval *pass_zv, *pipeline_zv;
	SDL_GPURenderPass *pass;
	SDL_GPUGraphicsPipeline *pipeline;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPURenderPass)
		Z_PARAM_OBJECT_OF_CLASS(pipeline_zv, sdl3_ce_SDL_GPUGraphicsPipeline)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPURenderPass, 1);
	pipeline = pass != NULL ? sdl3_handle_ptr(pipeline_zv, sdl3_ce_SDL_GPUGraphicsPipeline, 2) : NULL;
	if (pass == NULL || pipeline == NULL) {
		RETURN_THROWS();
	}

	SDL_BindGPUGraphicsPipeline(pass, pipeline);
}

ZEND_FUNCTION(SDL_SetGPUViewport)
{
	zval *pass_zv;
	zend_object *viewport_obj;
	SDL_GPURenderPass *pass;
	SDL_GPUViewport viewport;
	sdl3_scratch scratch;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPURenderPass)
		Z_PARAM_OBJ_OF_CLASS(viewport_obj, sdl3_ce_SDL_GPUViewport)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPURenderPass, 1);
	if (pass == NULL) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_SDL_GPUViewport_from(viewport_obj, &viewport, &scratch)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	SDL_SetGPUViewport(pass, &viewport);
	sdl3_scratch_free(&scratch);
}

ZEND_FUNCTION(SDL_SetGPUScissor)
{
	zval *pass_zv;
	zend_object *scissor_obj;
	SDL_GPURenderPass *pass;
	SDL_Rect scissor;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPURenderPass)
		Z_PARAM_OBJ_OF_CLASS(scissor_obj, sdl3_ce_SDL_Rect)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPURenderPass, 1);
	if (pass == NULL) {
		RETURN_THROWS();
	}

	{
		zend_long x, y, w, h;
		if (!sdl3_prop_long(scissor_obj, "x", &x) || !sdl3_prop_long(scissor_obj, "y", &y)
			|| !sdl3_prop_long(scissor_obj, "w", &w) || !sdl3_prop_long(scissor_obj, "h", &h)) {
			RETURN_THROWS();
		}
		scissor = (SDL_Rect) { (int) x, (int) y, (int) w, (int) h };
	}
	SDL_SetGPUScissor(pass, &scissor);
}

ZEND_FUNCTION(SDL_SetGPUStencilReference)
{
	zval *pass_zv;
	zend_long reference;
	SDL_GPURenderPass *pass;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPURenderPass)
		Z_PARAM_LONG(reference)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPURenderPass, 1);
	if (pass == NULL) {
		RETURN_THROWS();
	}

	SDL_SetGPUStencilReference(pass, (Uint8) reference);
}

ZEND_FUNCTION(SDL_BindGPUVertexBuffers)
{
	zval *pass_zv, *bindings_zv, *item;
	zend_long first_slot;
	SDL_GPURenderPass *pass;
	sdl3_scratch scratch;
	uint32_t count, index;
	SDL_GPUBufferBinding *bindings = NULL;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPURenderPass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ARRAY(bindings_zv)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPURenderPass, 1);
	if (pass == NULL) {
		RETURN_THROWS();
	}

	count = zend_hash_num_elements(Z_ARRVAL_P(bindings_zv));
	sdl3_scratch_init(&scratch);
	if (count > 0) {
		bindings = sdl3_scratch_alloc(&scratch, sizeof(SDL_GPUBufferBinding) * count);
		index = 0;
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(bindings_zv), item) {
			if (!sdl3_list_element(item, sdl3_ce_SDL_GPUBufferBinding, 3)) {
				sdl3_scratch_free(&scratch);
				RETURN_THROWS();
			}
			if (!sdl3_SDL_GPUBufferBinding_from(Z_OBJ_P(item), &bindings[index], &scratch)) {
				sdl3_scratch_free(&scratch);
				RETURN_THROWS();
			}
			index++;
		} ZEND_HASH_FOREACH_END();
	}
	SDL_BindGPUVertexBuffers(pass, (Uint32) first_slot, bindings, count);
	sdl3_scratch_free(&scratch);
}

ZEND_FUNCTION(SDL_BindGPUIndexBuffer)
{
	zval *pass_zv;
	zend_object *binding_obj;
	zend_long element_size;
	SDL_GPURenderPass *pass;
	SDL_GPUBufferBinding binding;
	sdl3_scratch scratch;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPURenderPass)
		Z_PARAM_OBJ_OF_CLASS(binding_obj, sdl3_ce_SDL_GPUBufferBinding)
		Z_PARAM_LONG(element_size)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPURenderPass, 1);
	if (pass == NULL) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_SDL_GPUBufferBinding_from(binding_obj, &binding, &scratch)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	SDL_BindGPUIndexBuffer(pass, &binding, (SDL_GPUIndexElementSize) element_size);
	sdl3_scratch_free(&scratch);
}

ZEND_FUNCTION(SDL_BindGPUFragmentSamplers)
{
	zval *pass_zv, *bindings_zv, *item;
	zend_long first_slot;
	SDL_GPURenderPass *pass;
	sdl3_scratch scratch;
	uint32_t count, index;
	SDL_GPUTextureSamplerBinding *bindings = NULL;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPURenderPass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ARRAY(bindings_zv)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPURenderPass, 1);
	if (pass == NULL) {
		RETURN_THROWS();
	}

	count = zend_hash_num_elements(Z_ARRVAL_P(bindings_zv));
	sdl3_scratch_init(&scratch);
	if (count > 0) {
		bindings = sdl3_scratch_alloc(&scratch, sizeof(SDL_GPUTextureSamplerBinding) * count);
		index = 0;
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(bindings_zv), item) {
			if (!sdl3_list_element(item, sdl3_ce_SDL_GPUTextureSamplerBinding, 3)) {
				sdl3_scratch_free(&scratch);
				RETURN_THROWS();
			}
			if (!sdl3_SDL_GPUTextureSamplerBinding_from(Z_OBJ_P(item), &bindings[index], &scratch)) {
				sdl3_scratch_free(&scratch);
				RETURN_THROWS();
			}
			index++;
		} ZEND_HASH_FOREACH_END();
	}
	SDL_BindGPUFragmentSamplers(pass, (Uint32) first_slot, bindings, count);
	sdl3_scratch_free(&scratch);
}

ZEND_FUNCTION(SDL_PushGPUVertexUniformData)
{
	sdl3_push_uniform(INTERNAL_FUNCTION_PARAM_PASSTHRU, SDL_PushGPUVertexUniformData);
}

ZEND_FUNCTION(SDL_PushGPUFragmentUniformData)
{
	sdl3_push_uniform(INTERNAL_FUNCTION_PARAM_PASSTHRU, SDL_PushGPUFragmentUniformData);
}

ZEND_FUNCTION(SDL_DrawGPUPrimitives)
{
	zval *pass_zv;
	zend_long num_vertices, num_instances, first_vertex, first_instance;
	SDL_GPURenderPass *pass;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPURenderPass)
		Z_PARAM_LONG(num_vertices)
		Z_PARAM_LONG(num_instances)
		Z_PARAM_LONG(first_vertex)
		Z_PARAM_LONG(first_instance)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPURenderPass, 1);
	if (pass == NULL) {
		RETURN_THROWS();
	}

	SDL_DrawGPUPrimitives(pass, (Uint32) num_vertices, (Uint32) num_instances,
		(Uint32) first_vertex, (Uint32) first_instance);
}

ZEND_FUNCTION(SDL_DrawGPUIndexedPrimitives)
{
	zval *pass_zv;
	zend_long num_indices, num_instances, first_index, vertex_offset, first_instance;
	SDL_GPURenderPass *pass;

	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPURenderPass)
		Z_PARAM_LONG(num_indices)
		Z_PARAM_LONG(num_instances)
		Z_PARAM_LONG(first_index)
		Z_PARAM_LONG(vertex_offset)
		Z_PARAM_LONG(first_instance)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPURenderPass, 1);
	if (pass == NULL) {
		RETURN_THROWS();
	}

	SDL_DrawGPUIndexedPrimitives(pass, (Uint32) num_indices, (Uint32) num_instances,
		(Uint32) first_index, (Sint32) vertex_offset, (Uint32) first_instance);
}

ZEND_FUNCTION(SDL_BlitGPUTexture)
{
	zval *command_zv;
	zend_object *info_obj;
	SDL_GPUCommandBuffer *command_buffer;
	SDL_GPUBlitInfo info;
	sdl3_scratch scratch;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(command_zv, sdl3_ce_SDL_GPUCommandBuffer)
		Z_PARAM_OBJ_OF_CLASS(info_obj, sdl3_ce_SDL_GPUBlitInfo)
	ZEND_PARSE_PARAMETERS_END();

	command_buffer = sdl3_handle_ptr(command_zv, sdl3_ce_SDL_GPUCommandBuffer, 1);
	if (command_buffer == NULL) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_SDL_GPUBlitInfo_from(info_obj, &info, &scratch)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	SDL_BlitGPUTexture(command_buffer, &info);
	sdl3_scratch_free(&scratch);
}

static bool sdl3_assign_ref_zval(zval *dest, zval *value)
{
	zend_reference *ref = Z_REF_P(dest);

	if (UNEXPECTED(ZEND_REF_HAS_TYPE_SOURCES(ref))) {
		return zend_try_assign_typed_ref_zval(ref, value) == SUCCESS;
	}

	zval_ptr_dtor(&ref->val);
	ZVAL_COPY(&ref->val, value);
	return true;
}

ZEND_FUNCTION(SDL_ClaimWindowForGPUDevice)
{
	zval *device_zv, *window_zv;
	SDL_GPUDevice *device;
	SDL_Window *window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	window = device != NULL ? sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 2) : NULL;
	if (device == NULL || window == NULL) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_ClaimWindowForGPUDevice(device, window));
}

ZEND_FUNCTION(SDL_ReleaseWindowFromGPUDevice)
{
	zval *device_zv, *window_zv;
	SDL_GPUDevice *device;
	SDL_Window *window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	window = device != NULL ? sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 2) : NULL;
	if (device == NULL || window == NULL) {
		RETURN_THROWS();
	}

	SDL_ReleaseWindowFromGPUDevice(device, window);
}

ZEND_FUNCTION(SDL_SetGPUSwapchainParameters)
{
	zval *device_zv, *window_zv;
	zend_long composition, present_mode;
	SDL_GPUDevice *device;
	SDL_Window *window;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_LONG(composition)
		Z_PARAM_LONG(present_mode)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	window = device != NULL ? sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 2) : NULL;
	if (device == NULL || window == NULL) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_SetGPUSwapchainParameters(device, window,
		(SDL_GPUSwapchainComposition) composition, (SDL_GPUPresentMode) present_mode));
}

ZEND_FUNCTION(SDL_GetGPUSwapchainTextureFormat)
{
	zval *device_zv, *window_zv;
	SDL_GPUDevice *device;
	SDL_Window *window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	window = device != NULL ? sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 2) : NULL;
	if (device == NULL || window == NULL) {
		RETURN_THROWS();
	}

	RETURN_LONG(SDL_GetGPUSwapchainTextureFormat(device, window));
}

ZEND_FUNCTION(SDL_AcquireGPUSwapchainTexture)
{
	zval *command_zv, *window_zv, *texture_zv, *width_zv, *height_zv;
	SDL_GPUCommandBuffer *command_buffer;
	SDL_Window *window;
	SDL_GPUTexture *texture = NULL;
	Uint32 width = 0, height = 0;
	zval boxed;
	bool acquired;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(command_zv, sdl3_ce_SDL_GPUCommandBuffer)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_ZVAL(texture_zv)
		Z_PARAM_ZVAL(width_zv)
		Z_PARAM_ZVAL(height_zv)
	ZEND_PARSE_PARAMETERS_END();

	command_buffer = sdl3_handle_ptr(command_zv, sdl3_ce_SDL_GPUCommandBuffer, 1);
	window = command_buffer != NULL ? sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 2) : NULL;
	if (command_buffer == NULL || window == NULL) {
		RETURN_THROWS();
	}

	acquired = SDL_AcquireGPUSwapchainTexture(command_buffer, window, &texture, &width, &height);
	if (!acquired) {
		RETURN_FALSE;
	}

	sdl3_box(&boxed, texture, sdl3_ce_SDL_GPUTexture);
	if (texture != NULL) {
		sdl3_keep_handle(Z_OBJ_P(command_zv), Z_OBJ(boxed));
	}
	if (!sdl3_assign_ref_zval(texture_zv, &boxed)) {
		zval_ptr_dtor(&boxed);
		RETURN_THROWS();
	}
	zval_ptr_dtor(&boxed);
	ZEND_TRY_ASSIGN_REF_LONG(width_zv, (zend_long) width);
	ZEND_TRY_ASSIGN_REF_LONG(height_zv, (zend_long) height);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_TRUE;
}
