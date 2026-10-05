#include "SDL_gpu_types.h"
#include "../stubs/SDL_gpu_arginfo.h"

zend_class_entry *sdl3_ce_SDL_GPUDevice;
zend_class_entry *sdl3_ce_SDL_GPUCommandBuffer;
zend_class_entry *sdl3_ce_SDL_GPUCopyPass;
zend_class_entry *sdl3_ce_SDL_GPUFence;

SDL3_POINTER_METHODS(SDL_GPUDevice)
SDL3_POINTER_METHODS(SDL_GPUCommandBuffer)
SDL3_POINTER_METHODS(SDL_GPUCopyPass)
SDL3_POINTER_METHODS(SDL_GPUFence)

static void sdl3_finish_command_buffer(zend_object *command_buffer)
{
	sdl3_release(command_buffer);
}

ZEND_FUNCTION(SDL_CreateGPUDevice)
{
	zend_long format_flags;
	bool debug_mode;
	zend_string *name = NULL;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(format_flags)
		Z_PARAM_BOOL(debug_mode)
		Z_PARAM_STR_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();

	sdl3_box(return_value, SDL_CreateGPUDevice((SDL_GPUShaderFormat) format_flags, debug_mode,
		name != NULL ? ZSTR_VAL(name) : NULL), sdl3_ce_SDL_GPUDevice);
}

ZEND_FUNCTION(SDL_DestroyGPUDevice)
{
	zval *device_zv;
	SDL_GPUDevice *device;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	SDL_DestroyGPUDevice(device);
	sdl3_release(Z_OBJ_P(device_zv));
}

ZEND_FUNCTION(SDL_GetGPUDeviceDriver)
{
	zval *device_zv;
	SDL_GPUDevice *device;
	const char *driver;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	driver = SDL_GetGPUDeviceDriver(device);
	if (driver == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(driver);
}

ZEND_FUNCTION(SDL_GetGPUShaderFormats)
{
	zval *device_zv;
	SDL_GPUDevice *device;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	RETURN_LONG(SDL_GetGPUShaderFormats(device));
}

ZEND_FUNCTION(SDL_CreateGPUTexture)
{
	zval *device_zv;
	zend_object *info_obj;
	SDL_GPUDevice *device;
	SDL_GPUTextureCreateInfo info;
	sdl3_scratch scratch;
	SDL_GPUTexture *texture;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJ_OF_CLASS(info_obj, sdl3_ce_SDL_GPUTextureCreateInfo)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_SDL_GPUTextureCreateInfo_from(info_obj, &info, &scratch)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	texture = SDL_CreateGPUTexture(device, &info);
	sdl3_scratch_free(&scratch);
	sdl3_box(return_value, texture, sdl3_ce_SDL_GPUTexture);
}

ZEND_FUNCTION(SDL_ReleaseGPUTexture)
{
	zval *device_zv, *texture_zv;
	SDL_GPUDevice *device;
	SDL_GPUTexture *texture;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(texture_zv, sdl3_ce_SDL_GPUTexture)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	texture = device != NULL ? sdl3_handle_ptr(texture_zv, sdl3_ce_SDL_GPUTexture, 2) : NULL;
	if (device == NULL || texture == NULL) {
		RETURN_THROWS();
	}

	SDL_ReleaseGPUTexture(device, texture);
	sdl3_release(Z_OBJ_P(texture_zv));
}

ZEND_FUNCTION(SDL_GPUTextureSupportsFormat)
{
	zval *device_zv;
	zend_long format, type, usage;
	SDL_GPUDevice *device;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_LONG(format)
		Z_PARAM_LONG(type)
		Z_PARAM_LONG(usage)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_GPUTextureSupportsFormat(device, (SDL_GPUTextureFormat) format,
		(SDL_GPUTextureType) type, (SDL_GPUTextureUsageFlags) usage));
}

ZEND_FUNCTION(SDL_GPUTextureSupportsSampleCount)
{
	zval *device_zv;
	zend_long format, sample_count;
	SDL_GPUDevice *device;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_LONG(format)
		Z_PARAM_LONG(sample_count)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_GPUTextureSupportsSampleCount(device, (SDL_GPUTextureFormat) format,
		(SDL_GPUSampleCount) sample_count));
}

ZEND_FUNCTION(SDL_CreateGPUSampler)
{
	zval *device_zv;
	zend_object *info_obj;
	SDL_GPUDevice *device;
	SDL_GPUSamplerCreateInfo info;
	sdl3_scratch scratch;
	SDL_GPUSampler *sampler;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJ_OF_CLASS(info_obj, sdl3_ce_SDL_GPUSamplerCreateInfo)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_SDL_GPUSamplerCreateInfo_from(info_obj, &info, &scratch)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	sampler = SDL_CreateGPUSampler(device, &info);
	sdl3_scratch_free(&scratch);
	sdl3_box(return_value, sampler, sdl3_ce_SDL_GPUSampler);
}

ZEND_FUNCTION(SDL_ReleaseGPUSampler)
{
	zval *device_zv, *sampler_zv;
	SDL_GPUDevice *device;
	SDL_GPUSampler *sampler;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(sampler_zv, sdl3_ce_SDL_GPUSampler)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	sampler = device != NULL ? sdl3_handle_ptr(sampler_zv, sdl3_ce_SDL_GPUSampler, 2) : NULL;
	if (device == NULL || sampler == NULL) {
		RETURN_THROWS();
	}

	SDL_ReleaseGPUSampler(device, sampler);
	sdl3_release(Z_OBJ_P(sampler_zv));
}

ZEND_FUNCTION(SDL_CreateGPUBuffer)
{
	zval *device_zv;
	zend_object *info_obj;
	SDL_GPUDevice *device;
	SDL_GPUBufferCreateInfo info;
	sdl3_scratch scratch;
	SDL_GPUBuffer *buffer;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJ_OF_CLASS(info_obj, sdl3_ce_SDL_GPUBufferCreateInfo)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_SDL_GPUBufferCreateInfo_from(info_obj, &info, &scratch)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	buffer = SDL_CreateGPUBuffer(device, &info);
	sdl3_scratch_free(&scratch);
	sdl3_box(return_value, buffer, sdl3_ce_SDL_GPUBuffer);
}

ZEND_FUNCTION(SDL_ReleaseGPUBuffer)
{
	zval *device_zv, *buffer_zv;
	SDL_GPUDevice *device;
	SDL_GPUBuffer *buffer;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(buffer_zv, sdl3_ce_SDL_GPUBuffer)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	buffer = device != NULL ? sdl3_handle_ptr(buffer_zv, sdl3_ce_SDL_GPUBuffer, 2) : NULL;
	if (device == NULL || buffer == NULL) {
		RETURN_THROWS();
	}

	SDL_ReleaseGPUBuffer(device, buffer);
	sdl3_release(Z_OBJ_P(buffer_zv));
}

ZEND_FUNCTION(SDL_CreateGPUTransferBuffer)
{
	zval *device_zv;
	zend_object *info_obj;
	SDL_GPUDevice *device;
	SDL_GPUTransferBufferCreateInfo info;
	sdl3_scratch scratch;
	SDL_GPUTransferBuffer *transfer;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJ_OF_CLASS(info_obj, sdl3_ce_SDL_GPUTransferBufferCreateInfo)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_SDL_GPUTransferBufferCreateInfo_from(info_obj, &info, &scratch)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	transfer = SDL_CreateGPUTransferBuffer(device, &info);
	sdl3_scratch_free(&scratch);
	sdl3_box(return_value, transfer, sdl3_ce_SDL_GPUTransferBuffer);
}

ZEND_FUNCTION(SDL_ReleaseGPUTransferBuffer)
{
	zval *device_zv, *transfer_zv;
	SDL_GPUDevice *device;
	SDL_GPUTransferBuffer *transfer;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(transfer_zv, sdl3_ce_SDL_GPUTransferBuffer)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	transfer = device != NULL ? sdl3_handle_ptr(transfer_zv, sdl3_ce_SDL_GPUTransferBuffer, 2) : NULL;
	if (device == NULL || transfer == NULL) {
		RETURN_THROWS();
	}

	SDL_ReleaseGPUTransferBuffer(device, transfer);
	sdl3_release(Z_OBJ_P(transfer_zv));
}

ZEND_FUNCTION(SDL_MapGPUTransferBuffer)
{
	zval *device_zv, *transfer_zv;
	bool cycle;
	SDL_GPUDevice *device;
	SDL_GPUTransferBuffer *transfer;
	void *mapped;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(transfer_zv, sdl3_ce_SDL_GPUTransferBuffer)
		Z_PARAM_BOOL(cycle)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	transfer = device != NULL ? sdl3_handle_ptr(transfer_zv, sdl3_ce_SDL_GPUTransferBuffer, 2) : NULL;
	if (device == NULL || transfer == NULL) {
		RETURN_THROWS();
	}

	mapped = SDL_MapGPUTransferBuffer(device, transfer, cycle);
	RETURN_LONG((zend_long) (uintptr_t) mapped);
}

ZEND_FUNCTION(SDL_UnmapGPUTransferBuffer)
{
	zval *device_zv, *transfer_zv;
	SDL_GPUDevice *device;
	SDL_GPUTransferBuffer *transfer;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(transfer_zv, sdl3_ce_SDL_GPUTransferBuffer)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	transfer = device != NULL ? sdl3_handle_ptr(transfer_zv, sdl3_ce_SDL_GPUTransferBuffer, 2) : NULL;
	if (device == NULL || transfer == NULL) {
		RETURN_THROWS();
	}

	SDL_UnmapGPUTransferBuffer(device, transfer);
}

ZEND_FUNCTION(SDL_AcquireGPUCommandBuffer)
{
	zval *device_zv;
	SDL_GPUDevice *device;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	sdl3_box(return_value, SDL_AcquireGPUCommandBuffer(device), sdl3_ce_SDL_GPUCommandBuffer);
}

ZEND_FUNCTION(SDL_SubmitGPUCommandBuffer)
{
	zval *command_zv;
	SDL_GPUCommandBuffer *command_buffer;
	bool submitted;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(command_zv, sdl3_ce_SDL_GPUCommandBuffer)
	ZEND_PARSE_PARAMETERS_END();

	command_buffer = sdl3_handle_ptr(command_zv, sdl3_ce_SDL_GPUCommandBuffer, 1);
	if (command_buffer == NULL) {
		RETURN_THROWS();
	}

	submitted = SDL_SubmitGPUCommandBuffer(command_buffer);
	sdl3_finish_command_buffer(Z_OBJ_P(command_zv));
	RETURN_BOOL(submitted);
}

ZEND_FUNCTION(SDL_SubmitGPUCommandBufferAndAcquireFence)
{
	zval *command_zv;
	SDL_GPUCommandBuffer *command_buffer;
	SDL_GPUFence *fence;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(command_zv, sdl3_ce_SDL_GPUCommandBuffer)
	ZEND_PARSE_PARAMETERS_END();

	command_buffer = sdl3_handle_ptr(command_zv, sdl3_ce_SDL_GPUCommandBuffer, 1);
	if (command_buffer == NULL) {
		RETURN_THROWS();
	}

	fence = SDL_SubmitGPUCommandBufferAndAcquireFence(command_buffer);
	sdl3_finish_command_buffer(Z_OBJ_P(command_zv));
	sdl3_box(return_value, fence, sdl3_ce_SDL_GPUFence);
}

ZEND_FUNCTION(SDL_CancelGPUCommandBuffer)
{
	zval *command_zv;
	SDL_GPUCommandBuffer *command_buffer;
	bool cancelled;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(command_zv, sdl3_ce_SDL_GPUCommandBuffer)
	ZEND_PARSE_PARAMETERS_END();

	command_buffer = sdl3_handle_ptr(command_zv, sdl3_ce_SDL_GPUCommandBuffer, 1);
	if (command_buffer == NULL) {
		RETURN_THROWS();
	}

	cancelled = SDL_CancelGPUCommandBuffer(command_buffer);
	sdl3_finish_command_buffer(Z_OBJ_P(command_zv));
	RETURN_BOOL(cancelled);
}

ZEND_FUNCTION(SDL_QueryGPUFence)
{
	zval *device_zv, *fence_zv;
	SDL_GPUDevice *device;
	SDL_GPUFence *fence;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(fence_zv, sdl3_ce_SDL_GPUFence)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	fence = device != NULL ? sdl3_handle_ptr(fence_zv, sdl3_ce_SDL_GPUFence, 2) : NULL;
	if (device == NULL || fence == NULL) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_QueryGPUFence(device, fence));
}

ZEND_FUNCTION(SDL_ReleaseGPUFence)
{
	zval *device_zv, *fence_zv;
	SDL_GPUDevice *device;
	SDL_GPUFence *fence;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_OBJECT_OF_CLASS(fence_zv, sdl3_ce_SDL_GPUFence)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	fence = device != NULL ? sdl3_handle_ptr(fence_zv, sdl3_ce_SDL_GPUFence, 2) : NULL;
	if (device == NULL || fence == NULL) {
		RETURN_THROWS();
	}

	SDL_ReleaseGPUFence(device, fence);
	sdl3_release(Z_OBJ_P(fence_zv));
}

ZEND_FUNCTION(SDL_WaitForGPUFences)
{
	zval *device_zv, *fences_zv, *item;
	bool wait_all;
	SDL_GPUDevice *device;
	sdl3_scratch scratch;
	uint32_t count, index;
	SDL_GPUFence **native = NULL;
	bool waited;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
		Z_PARAM_BOOL(wait_all)
		Z_PARAM_ARRAY(fences_zv)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	count = zend_hash_num_elements(Z_ARRVAL_P(fences_zv));
	sdl3_scratch_init(&scratch);
	if (count > 0) {
		native = sdl3_scratch_alloc(&scratch, sizeof(SDL_GPUFence *) * count);
		index = 0;
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(fences_zv), item) {
			if (Z_TYPE_P(item) != IS_OBJECT || !instanceof_function(Z_OBJCE_P(item), sdl3_ce_SDL_GPUFence)) {
				sdl3_scratch_free(&scratch);
				zend_argument_type_error(3, "must be a list of %s", ZSTR_VAL(sdl3_ce_SDL_GPUFence->name));
				RETURN_THROWS();
			}
			native[index] = sdl3_handle_ptr(item, sdl3_ce_SDL_GPUFence, 0);
			if (native[index] == NULL) {
				sdl3_scratch_free(&scratch);
				RETURN_THROWS();
			}
			index++;
		} ZEND_HASH_FOREACH_END();
	}

	waited = SDL_WaitForGPUFences(device, wait_all, (SDL_GPUFence *const *) native, count);
	sdl3_scratch_free(&scratch);
	RETURN_BOOL(waited);
}

ZEND_FUNCTION(SDL_WaitForGPUIdle)
{
	zval *device_zv;
	SDL_GPUDevice *device;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(device_zv, sdl3_ce_SDL_GPUDevice)
	ZEND_PARSE_PARAMETERS_END();

	device = sdl3_handle_ptr(device_zv, sdl3_ce_SDL_GPUDevice, 1);
	if (device == NULL) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_WaitForGPUIdle(device));
}

ZEND_FUNCTION(SDL_BeginGPUCopyPass)
{
	zval *command_zv;
	SDL_GPUCommandBuffer *command_buffer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(command_zv, sdl3_ce_SDL_GPUCommandBuffer)
	ZEND_PARSE_PARAMETERS_END();

	command_buffer = sdl3_handle_ptr(command_zv, sdl3_ce_SDL_GPUCommandBuffer, 1);
	if (command_buffer == NULL) {
		RETURN_THROWS();
	}

	sdl3_box(return_value, SDL_BeginGPUCopyPass(command_buffer), sdl3_ce_SDL_GPUCopyPass);
}

ZEND_FUNCTION(SDL_UploadToGPUTexture)
{
	zval *pass_zv;
	zend_object *source_obj, *destination_obj;
	bool cycle;
	SDL_GPUCopyPass *pass;
	SDL_GPUTextureTransferInfo source;
	SDL_GPUTextureRegion destination;
	sdl3_scratch scratch;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPUCopyPass)
		Z_PARAM_OBJ_OF_CLASS(source_obj, sdl3_ce_SDL_GPUTextureTransferInfo)
		Z_PARAM_OBJ_OF_CLASS(destination_obj, sdl3_ce_SDL_GPUTextureRegion)
		Z_PARAM_BOOL(cycle)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPUCopyPass, 1);
	if (pass == NULL) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_SDL_GPUTextureTransferInfo_from(source_obj, &source, &scratch)
		|| !sdl3_SDL_GPUTextureRegion_from(destination_obj, &destination, &scratch)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	SDL_UploadToGPUTexture(pass, &source, &destination, cycle);
	sdl3_scratch_free(&scratch);
}

ZEND_FUNCTION(SDL_UploadToGPUBuffer)
{
	zval *pass_zv;
	zend_object *source_obj, *destination_obj;
	bool cycle;
	SDL_GPUCopyPass *pass;
	SDL_GPUTransferBufferLocation source;
	SDL_GPUBufferRegion destination;
	sdl3_scratch scratch;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPUCopyPass)
		Z_PARAM_OBJ_OF_CLASS(source_obj, sdl3_ce_SDL_GPUTransferBufferLocation)
		Z_PARAM_OBJ_OF_CLASS(destination_obj, sdl3_ce_SDL_GPUBufferRegion)
		Z_PARAM_BOOL(cycle)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPUCopyPass, 1);
	if (pass == NULL) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_SDL_GPUTransferBufferLocation_from(source_obj, &source, &scratch)
		|| !sdl3_SDL_GPUBufferRegion_from(destination_obj, &destination, &scratch)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	SDL_UploadToGPUBuffer(pass, &source, &destination, cycle);
	sdl3_scratch_free(&scratch);
}

ZEND_FUNCTION(SDL_DownloadFromGPUTexture)
{
	zval *pass_zv;
	zend_object *source_obj, *destination_obj;
	SDL_GPUCopyPass *pass;
	SDL_GPUTextureRegion source;
	SDL_GPUTextureTransferInfo destination;
	sdl3_scratch scratch;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPUCopyPass)
		Z_PARAM_OBJ_OF_CLASS(source_obj, sdl3_ce_SDL_GPUTextureRegion)
		Z_PARAM_OBJ_OF_CLASS(destination_obj, sdl3_ce_SDL_GPUTextureTransferInfo)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPUCopyPass, 1);
	if (pass == NULL) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	if (!sdl3_SDL_GPUTextureRegion_from(source_obj, &source, &scratch)
		|| !sdl3_SDL_GPUTextureTransferInfo_from(destination_obj, &destination, &scratch)) {
		sdl3_scratch_free(&scratch);
		RETURN_THROWS();
	}
	SDL_DownloadFromGPUTexture(pass, &source, &destination);
	sdl3_scratch_free(&scratch);
}

ZEND_FUNCTION(SDL_EndGPUCopyPass)
{
	zval *pass_zv;
	SDL_GPUCopyPass *pass;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(pass_zv, sdl3_ce_SDL_GPUCopyPass)
	ZEND_PARSE_PARAMETERS_END();

	pass = sdl3_handle_ptr(pass_zv, sdl3_ce_SDL_GPUCopyPass, 1);
	if (pass == NULL) {
		RETURN_THROWS();
	}

	SDL_EndGPUCopyPass(pass);
	sdl3_release(Z_OBJ_P(pass_zv));
}

void sdl3_register_SDL_gpu(int module_number)
{
	(void) module_number;

	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);

	sdl3_ce_SDL_GPUDevice = register_class_SDL_GPUDevice();
	sdl3_handle_setup(sdl3_ce_SDL_GPUDevice);
	sdl3_ce_SDL_GPUCommandBuffer = register_class_SDL_GPUCommandBuffer();
	sdl3_handle_setup(sdl3_ce_SDL_GPUCommandBuffer);
	sdl3_ce_SDL_GPUCopyPass = register_class_SDL_GPUCopyPass();
	sdl3_handle_setup(sdl3_ce_SDL_GPUCopyPass);
	sdl3_ce_SDL_GPUFence = register_class_SDL_GPUFence();
	sdl3_handle_setup(sdl3_ce_SDL_GPUFence);
	sdl3_ce_SDL_GPUGraphicsPipeline = register_class_SDL_GPUGraphicsPipeline();
	sdl3_handle_setup(sdl3_ce_SDL_GPUGraphicsPipeline);
	sdl3_ce_SDL_GPURenderPass = register_class_SDL_GPURenderPass();
	sdl3_handle_setup(sdl3_ce_SDL_GPURenderPass);
}
