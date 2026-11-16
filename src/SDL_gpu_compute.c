#include "SDL_gpu_types.h"

zend_class_entry *sdl3_ce_SDL_GPUComputePipeline;
zend_class_entry *sdl3_ce_SDL_GPUComputePass;

ZEND_METHOD(SDL_GPUComputePipeline, __construct)
{
	ZEND_PARSE_PARAMETERS_NONE();
}

ZEND_METHOD(SDL_GPUComputePipeline, pointer)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG((zend_long) (uintptr_t) sdl3_handle_from(Z_OBJ_P(ZEND_THIS))->ptr);
}

ZEND_METHOD(SDL_GPUComputePipeline, fromPointer)
{
	zend_long address;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(address)
	ZEND_PARSE_PARAMETERS_END();

	sdl3_box(return_value, (void *) (uintptr_t) address, zend_get_called_scope(execute_data));
}

ZEND_METHOD(SDL_GPUComputePass, __construct)
{
	ZEND_PARSE_PARAMETERS_NONE();
}

ZEND_METHOD(SDL_GPUComputePass, pointer)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG((zend_long) (uintptr_t) sdl3_handle_from(Z_OBJ_P(ZEND_THIS))->ptr);
}

ZEND_METHOD(SDL_GPUComputePass, fromPointer)
{
	zend_long address;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(address)
	ZEND_PARSE_PARAMETERS_END();

	sdl3_box(return_value, (void *) (uintptr_t) address, zend_get_called_scope(execute_data));
}

bool sdl3_handle_list(zval *list_zv, zend_class_entry *ce, uint32_t list_arg, zend_long given, uint32_t count_arg, sdl3_scratch *scratch, void ***out)
{
	zval *item;
	uint32_t count, index;
	void **native = NULL;

	count = zend_hash_num_elements(Z_ARRVAL_P(list_zv));
	if (!sdl3_list_count(given, count, count_arg, list_arg)) {
		return false;
	}
	if (count > 0) {
		native = sdl3_scratch_alloc(scratch, sizeof(void *) * count);
		index = 0;
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(list_zv), item) {
			if (!sdl3_list_element(item, ce, list_arg)) {
				return false;
			}
			native[index] = sdl3_handle_ptr(item, ce, 0);
			if (EG(exception)) {
				return false;
			}
			index++;
		} ZEND_HASH_FOREACH_END();
	}

	*out = native;
	return true;
}

ZEND_FUNCTION(SDL_CreateGPUComputePipeline)
{
	zval *device_zv;
	zend_object *info_obj;
	SDL_GPUDevice *device;
	SDL_GPUComputePipelineCreateInfo info;
	sdl3_scratch scratch;
	SDL_GPUComputePipeline *pipeline;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJ_OF_CLASS(info_obj, sdl3_ce_SDL_GPUComputePipelineCreateInfo)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_SDL_GPUComputePipelineCreateInfo_from(info_obj, &info, &scratch)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	pipeline = SDL_CreateGPUComputePipeline(device, &info);
	sdl3_scratch_free(&scratch);
	sdl3_box(return_value, pipeline, sdl3_ce_SDL_GPUComputePipeline);
}

ZEND_FUNCTION(SDL_ReleaseGPUComputePipeline)
{
	zval *device_zv, *pipeline_zv;
	SDL_GPUDevice *device;
	SDL_GPUComputePipeline *pipeline;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(pipeline_zv, sdl3_ce_SDL_GPUComputePipeline)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	pipeline = !EG(exception) ? sdl3_handle_ptr(pipeline_zv, sdl3_ce_SDL_GPUComputePipeline, 2) : NULL;
	if (EG(exception)) {
		RETURN_THROWS();
	}

	SDL_ReleaseGPUComputePipeline(device, pipeline);
	sdl3_release(Z_OBJ_P(pipeline_zv));
}

ZEND_FUNCTION(SDL_BeginGPUComputePass)
{
	zval *command_zv, *textures_zv, *buffers_zv, *item;
	zend_long num_textures, num_buffers;
	SDL_GPUCommandBuffer *command_buffer;
	sdl3_scratch scratch;
	uint32_t texture_count, buffer_count, index;
	SDL_GPUStorageTextureReadWriteBinding *textures = NULL;
	SDL_GPUStorageBufferReadWriteBinding *buffers = NULL;
	SDL_GPUComputePass *pass;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(command_zv, sdl3_ce_SDL_GPUCommandBuffer)
		Z_PARAM_ARRAY(textures_zv)
		Z_PARAM_LONG(num_textures)
		Z_PARAM_ARRAY(buffers_zv)
		Z_PARAM_LONG(num_buffers)
	ZEND_PARSE_PARAMETERS_END();

	command_buffer = sdl3_handle_ptr(command_zv, sdl3_ce_SDL_GPUCommandBuffer, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	texture_count = zend_hash_num_elements(Z_ARRVAL_P(textures_zv));
	buffer_count = zend_hash_num_elements(Z_ARRVAL_P(buffers_zv));
	if (!sdl3_list_count(num_textures, texture_count, 3, 2) || !sdl3_list_count(num_buffers, buffer_count, 5, 4)) {
		RETURN_THROWS();
	}
	sdl3_scratch_init(&scratch);
	if (texture_count > 0) {
		textures = sdl3_scratch_alloc(&scratch, sizeof(SDL_GPUStorageTextureReadWriteBinding) * texture_count);
		index = 0;
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(textures_zv), item) {
			if (!sdl3_list_element(item, sdl3_ce_SDL_GPUStorageTextureReadWriteBinding, 2)
				|| !sdl3_SDL_GPUStorageTextureReadWriteBinding_from(Z_OBJ_P(item), &textures[index], &scratch)) {
				sdl3_scratch_free(&scratch);
				RETURN_THROWS();
			}
			index++;
		} ZEND_HASH_FOREACH_END();
	}
	if (buffer_count > 0) {
		buffers = sdl3_scratch_alloc(&scratch, sizeof(SDL_GPUStorageBufferReadWriteBinding) * buffer_count);
		index = 0;
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(buffers_zv), item) {
			if (!sdl3_list_element(item, sdl3_ce_SDL_GPUStorageBufferReadWriteBinding, 4)
				|| !sdl3_SDL_GPUStorageBufferReadWriteBinding_from(Z_OBJ_P(item), &buffers[index], &scratch)) {
				sdl3_scratch_free(&scratch);
				RETURN_THROWS();
			}
			index++;
		} ZEND_HASH_FOREACH_END();
	}

	pass = SDL_BeginGPUComputePass(command_buffer, textures, (Uint32) num_textures, buffers, (Uint32) num_buffers);
	sdl3_scratch_free(&scratch);
	sdl3_box(return_value, pass, sdl3_ce_SDL_GPUComputePass);
}

ZEND_FUNCTION(SDL_EndGPUComputePass)
{
	zval *pass_zv;
	SDL_GPUComputePass *pass;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPUComputePass)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPUComputePass, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	SDL_EndGPUComputePass(pass);
	sdl3_release(Z_OBJ_P(pass_zv));
}

ZEND_FUNCTION(SDL_BindGPUComputePipeline)
{
	zval *pass_zv, *pipeline_zv;
	SDL_GPUComputePass *pass;
	SDL_GPUComputePipeline *pipeline;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPUComputePass)
		Z_PARAM_OBJECT_OF_CLASS(pipeline_zv, sdl3_ce_SDL_GPUComputePipeline)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPUComputePass, 1);
	pipeline = !EG(exception) ? sdl3_handle_ptr(pipeline_zv, sdl3_ce_SDL_GPUComputePipeline, 2) : NULL;
	if (EG(exception)) {
		RETURN_THROWS();
	}

	SDL_BindGPUComputePipeline(pass, pipeline);
}

ZEND_FUNCTION(SDL_BindGPUComputeStorageBuffers)
{
	zval *pass_zv, *list_zv;
	zend_long first_slot, num_bindings;
	SDL_GPUComputePass *pass;
	sdl3_scratch scratch;
	void **native = NULL;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPUComputePass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ARRAY(list_zv)
		Z_PARAM_LONG(num_bindings)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPUComputePass, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_handle_list(list_zv, sdl3_ce_SDL_GPUBuffer, 3, num_bindings, 4, &scratch, &native)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	SDL_BindGPUComputeStorageBuffers(pass, (Uint32) first_slot, (SDL_GPUBuffer *const *) native, (Uint32) num_bindings);
	sdl3_scratch_free(&scratch);
}

ZEND_FUNCTION(SDL_BindGPUComputeStorageTextures)
{
	zval *pass_zv, *list_zv;
	zend_long first_slot, num_bindings;
	SDL_GPUComputePass *pass;
	sdl3_scratch scratch;
	void **native = NULL;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPUComputePass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ARRAY(list_zv)
		Z_PARAM_LONG(num_bindings)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPUComputePass, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_handle_list(list_zv, sdl3_ce_SDL_GPUTexture, 3, num_bindings, 4, &scratch, &native)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	SDL_BindGPUComputeStorageTextures(pass, (Uint32) first_slot, (SDL_GPUTexture *const *) native, (Uint32) num_bindings);
	sdl3_scratch_free(&scratch);
}

ZEND_FUNCTION(SDL_BindGPUComputeSamplers)
{
	zval *pass_zv, *bindings_zv, *item;
	zend_long first_slot, num_bindings;
	SDL_GPUComputePass *pass;
	sdl3_scratch scratch;
	uint32_t count, index;
	SDL_GPUTextureSamplerBinding *bindings = NULL;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPUComputePass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ARRAY(bindings_zv)
		Z_PARAM_LONG(num_bindings)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPUComputePass, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	count = zend_hash_num_elements(Z_ARRVAL_P(bindings_zv));
	if (!sdl3_list_count(num_bindings, count, 4, 3)) {
		RETURN_THROWS();
	}
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
	SDL_BindGPUComputeSamplers(pass, (Uint32) first_slot, bindings, (Uint32) num_bindings);
	sdl3_scratch_free(&scratch);
}

ZEND_FUNCTION(SDL_DispatchGPUCompute)
{
	zval *pass_zv;
	zend_long groupcount_x, groupcount_y, groupcount_z;
	SDL_GPUComputePass *pass;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPUComputePass)
		Z_PARAM_LONG(groupcount_x)
		Z_PARAM_LONG(groupcount_y)
		Z_PARAM_LONG(groupcount_z)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPUComputePass, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	SDL_DispatchGPUCompute(pass, (Uint32) groupcount_x, (Uint32) groupcount_y, (Uint32) groupcount_z);
}
