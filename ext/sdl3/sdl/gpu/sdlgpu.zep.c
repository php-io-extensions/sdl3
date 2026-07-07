
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/array.h"

#include <SDL3/SDL.h>
#include <string.h>

/* --- assoc-array field readers ------------------------------------------ */

static zval *php_sdl_gpu_field(zval *arr, const char *key)
{
    if (arr == NULL || Z_TYPE_P(arr) != IS_ARRAY) {
        return NULL;
    }
    return zend_hash_str_find(Z_ARRVAL_P(arr), key, strlen(key));
}

static zend_long php_sdl_gpu_long(zval *arr, const char *key, zend_long defval)
{
    zval *v = php_sdl_gpu_field(arr, key);
    return v ? zval_get_long(v) : defval;
}

static double php_sdl_gpu_double(zval *arr, const char *key, double defval)
{
    zval *v = php_sdl_gpu_field(arr, key);
    return v ? zval_get_double(v) : defval;
}

static bool php_sdl_gpu_bool(zval *arr, const char *key, bool defval)
{
    zval *v = php_sdl_gpu_field(arr, key);
    return v ? (zend_is_true(v) ? true : false) : defval;
}

static void *php_sdl_gpu_handle(zval *arr, const char *key)
{
    return (void *)(uintptr_t) php_sdl_gpu_long(arr, key, 0);
}

static Uint32 php_sdl_gpu_count(zval *arr)
{
    if (arr == NULL || Z_TYPE_P(arr) != IS_ARRAY) {
        return 0;
    }
    return (Uint32) zend_hash_num_elements(Z_ARRVAL_P(arr));
}

/* --- struct builders (assoc arrays mirror the C field names) ------------- */

static void php_sdl_gpu_fcolor(zval *arr, SDL_FColor *out)
{
    out->r = (float) php_sdl_gpu_double(arr, "r", 0.0);
    out->g = (float) php_sdl_gpu_double(arr, "g", 0.0);
    out->b = (float) php_sdl_gpu_double(arr, "b", 0.0);
    out->a = (float) php_sdl_gpu_double(arr, "a", 0.0);
}

static void php_sdl_gpu_viewport(zval *arr, SDL_GPUViewport *out)
{
    SDL_zerop(out);
    out->x = (float) php_sdl_gpu_double(arr, "x", 0.0);
    out->y = (float) php_sdl_gpu_double(arr, "y", 0.0);
    out->w = (float) php_sdl_gpu_double(arr, "w", 0.0);
    out->h = (float) php_sdl_gpu_double(arr, "h", 0.0);
    out->min_depth = (float) php_sdl_gpu_double(arr, "min_depth", 0.0);
    out->max_depth = (float) php_sdl_gpu_double(arr, "max_depth", 1.0);
}

static void php_sdl_gpu_color_target_info(zval *arr, SDL_GPUColorTargetInfo *out)
{
    zval *cc;

    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->mip_level = (Uint32) php_sdl_gpu_long(arr, "mip_level", 0);
    out->layer_or_depth_plane = (Uint32) php_sdl_gpu_long(arr, "layer_or_depth_plane", 0);
    cc = php_sdl_gpu_field(arr, "clear_color");
    if (cc != NULL) {
        php_sdl_gpu_fcolor(cc, &out->clear_color);
    }
    out->load_op = (SDL_GPULoadOp) php_sdl_gpu_long(arr, "load_op", 0);
    out->store_op = (SDL_GPUStoreOp) php_sdl_gpu_long(arr, "store_op", 0);
    out->resolve_texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "resolve_texture");
    out->resolve_mip_level = (Uint32) php_sdl_gpu_long(arr, "resolve_mip_level", 0);
    out->resolve_layer = (Uint32) php_sdl_gpu_long(arr, "resolve_layer", 0);
    out->cycle = php_sdl_gpu_bool(arr, "cycle", false);
    out->cycle_resolve_texture = php_sdl_gpu_bool(arr, "cycle_resolve_texture", false);
}

static void php_sdl_gpu_depth_stencil_target_info(zval *arr, SDL_GPUDepthStencilTargetInfo *out)
{
    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->clear_depth = (float) php_sdl_gpu_double(arr, "clear_depth", 0.0);
    out->load_op = (SDL_GPULoadOp) php_sdl_gpu_long(arr, "load_op", 0);
    out->store_op = (SDL_GPUStoreOp) php_sdl_gpu_long(arr, "store_op", 0);
    out->stencil_load_op = (SDL_GPULoadOp) php_sdl_gpu_long(arr, "stencil_load_op", 0);
    out->stencil_store_op = (SDL_GPUStoreOp) php_sdl_gpu_long(arr, "stencil_store_op", 0);
    out->cycle = php_sdl_gpu_bool(arr, "cycle", false);
    out->clear_stencil = (Uint8) php_sdl_gpu_long(arr, "clear_stencil", 0);
    out->mip_level = (Uint8) php_sdl_gpu_long(arr, "mip_level", 0);
    out->layer = (Uint8) php_sdl_gpu_long(arr, "layer", 0);
}

static void php_sdl_gpu_buffer_binding(zval *arr, SDL_GPUBufferBinding *out)
{
    SDL_zerop(out);
    out->buffer = (SDL_GPUBuffer *) php_sdl_gpu_handle(arr, "buffer");
    out->offset = (Uint32) php_sdl_gpu_long(arr, "offset", 0);
}

static void php_sdl_gpu_texture_sampler_binding(zval *arr, SDL_GPUTextureSamplerBinding *out)
{
    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->sampler = (SDL_GPUSampler *) php_sdl_gpu_handle(arr, "sampler");
}

static void php_sdl_gpu_storage_texture_rw_binding(zval *arr, SDL_GPUStorageTextureReadWriteBinding *out)
{
    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->mip_level = (Uint32) php_sdl_gpu_long(arr, "mip_level", 0);
    out->layer = (Uint32) php_sdl_gpu_long(arr, "layer", 0);
    out->cycle = php_sdl_gpu_bool(arr, "cycle", false);
}

static void php_sdl_gpu_storage_buffer_rw_binding(zval *arr, SDL_GPUStorageBufferReadWriteBinding *out)
{
    SDL_zerop(out);
    out->buffer = (SDL_GPUBuffer *) php_sdl_gpu_handle(arr, "buffer");
    out->cycle = php_sdl_gpu_bool(arr, "cycle", false);
}

static void php_sdl_gpu_texture_transfer_info(zval *arr, SDL_GPUTextureTransferInfo *out)
{
    SDL_zerop(out);
    out->transfer_buffer = (SDL_GPUTransferBuffer *) php_sdl_gpu_handle(arr, "transfer_buffer");
    out->offset = (Uint32) php_sdl_gpu_long(arr, "offset", 0);
    out->pixels_per_row = (Uint32) php_sdl_gpu_long(arr, "pixels_per_row", 0);
    out->rows_per_layer = (Uint32) php_sdl_gpu_long(arr, "rows_per_layer", 0);
}

static void php_sdl_gpu_texture_region(zval *arr, SDL_GPUTextureRegion *out)
{
    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->mip_level = (Uint32) php_sdl_gpu_long(arr, "mip_level", 0);
    out->layer = (Uint32) php_sdl_gpu_long(arr, "layer", 0);
    out->x = (Uint32) php_sdl_gpu_long(arr, "x", 0);
    out->y = (Uint32) php_sdl_gpu_long(arr, "y", 0);
    out->z = (Uint32) php_sdl_gpu_long(arr, "z", 0);
    out->w = (Uint32) php_sdl_gpu_long(arr, "w", 0);
    out->h = (Uint32) php_sdl_gpu_long(arr, "h", 0);
    out->d = (Uint32) php_sdl_gpu_long(arr, "d", 0);
}

static void php_sdl_gpu_texture_location(zval *arr, SDL_GPUTextureLocation *out)
{
    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->mip_level = (Uint32) php_sdl_gpu_long(arr, "mip_level", 0);
    out->layer = (Uint32) php_sdl_gpu_long(arr, "layer", 0);
    out->x = (Uint32) php_sdl_gpu_long(arr, "x", 0);
    out->y = (Uint32) php_sdl_gpu_long(arr, "y", 0);
    out->z = (Uint32) php_sdl_gpu_long(arr, "z", 0);
}

static void php_sdl_gpu_transfer_buffer_location(zval *arr, SDL_GPUTransferBufferLocation *out)
{
    SDL_zerop(out);
    out->transfer_buffer = (SDL_GPUTransferBuffer *) php_sdl_gpu_handle(arr, "transfer_buffer");
    out->offset = (Uint32) php_sdl_gpu_long(arr, "offset", 0);
}

static void php_sdl_gpu_buffer_location(zval *arr, SDL_GPUBufferLocation *out)
{
    SDL_zerop(out);
    out->buffer = (SDL_GPUBuffer *) php_sdl_gpu_handle(arr, "buffer");
    out->offset = (Uint32) php_sdl_gpu_long(arr, "offset", 0);
}

static void php_sdl_gpu_buffer_region(zval *arr, SDL_GPUBufferRegion *out)
{
    SDL_zerop(out);
    out->buffer = (SDL_GPUBuffer *) php_sdl_gpu_handle(arr, "buffer");
    out->offset = (Uint32) php_sdl_gpu_long(arr, "offset", 0);
    out->size = (Uint32) php_sdl_gpu_long(arr, "size", 0);
}

static void php_sdl_gpu_blit_region(zval *arr, SDL_GPUBlitRegion *out)
{
    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->mip_level = (Uint32) php_sdl_gpu_long(arr, "mip_level", 0);
    out->layer_or_depth_plane = (Uint32) php_sdl_gpu_long(arr, "layer_or_depth_plane", 0);
    out->x = (Uint32) php_sdl_gpu_long(arr, "x", 0);
    out->y = (Uint32) php_sdl_gpu_long(arr, "y", 0);
    out->w = (Uint32) php_sdl_gpu_long(arr, "w", 0);
    out->h = (Uint32) php_sdl_gpu_long(arr, "h", 0);
}

static void php_sdl_gpu_stencil_op_state(zval *arr, SDL_GPUStencilOpState *out)
{
    SDL_zerop(out);
    out->fail_op = (SDL_GPUStencilOp) php_sdl_gpu_long(arr, "fail_op", 0);
    out->pass_op = (SDL_GPUStencilOp) php_sdl_gpu_long(arr, "pass_op", 0);
    out->depth_fail_op = (SDL_GPUStencilOp) php_sdl_gpu_long(arr, "depth_fail_op", 0);
    out->compare_op = (SDL_GPUCompareOp) php_sdl_gpu_long(arr, "compare_op", 0);
}

static void php_sdl_gpu_color_target_blend_state(zval *arr, SDL_GPUColorTargetBlendState *out)
{
    SDL_zerop(out);
    out->src_color_blendfactor = (SDL_GPUBlendFactor) php_sdl_gpu_long(arr, "src_color_blendfactor", 0);
    out->dst_color_blendfactor = (SDL_GPUBlendFactor) php_sdl_gpu_long(arr, "dst_color_blendfactor", 0);
    out->color_blend_op = (SDL_GPUBlendOp) php_sdl_gpu_long(arr, "color_blend_op", 0);
    out->src_alpha_blendfactor = (SDL_GPUBlendFactor) php_sdl_gpu_long(arr, "src_alpha_blendfactor", 0);
    out->dst_alpha_blendfactor = (SDL_GPUBlendFactor) php_sdl_gpu_long(arr, "dst_alpha_blendfactor", 0);
    out->alpha_blend_op = (SDL_GPUBlendOp) php_sdl_gpu_long(arr, "alpha_blend_op", 0);
    out->color_write_mask = (SDL_GPUColorComponentFlags) php_sdl_gpu_long(arr, "color_write_mask", 0);
    out->enable_blend = php_sdl_gpu_bool(arr, "enable_blend", false);
    out->enable_color_write_mask = php_sdl_gpu_bool(arr, "enable_color_write_mask", false);
}

/* Build an emalloc'd array of opaque handles from a PHP list of ints. */
static void **php_sdl_gpu_handle_list(zval *arr, Uint32 *out_count)
{
    Uint32 n = php_sdl_gpu_count(arr);
    void **items;
    Uint32 i = 0;
    zval *el;

    *out_count = n;
    if (n == 0) {
        return NULL;
    }

    items = (void **) emalloc(sizeof(void *) * n);
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(arr), el) {
        items[i] = (void *)(uintptr_t) zval_get_long(el);
        i++;
    } ZEND_HASH_FOREACH_END();

    return items;
}



/**
 * Bindings for the SDL3 GPU API (SDL_gpu.h) plus the GPU render-state
 * functions from SDL_render.h.
 *
 * All opaque SDL_GPU* objects (device, buffers, textures, samplers, shaders,
 * pipelines, command buffers, passes, fences, render states) travel across
 * the PHP boundary as opaque int handles. Creation-info structs are assoc
 * arrays that mirror the C struct field names exactly; nested struct lists
 * are arrays of assoc arrays. Shader bytecode and uniform data are binary
 * PHP strings.
 */
ZEPHIR_INIT_CLASS(Sdl3_SDL_Gpu_SDLGPU)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Gpu, SDLGPU, sdl3, sdl_gpu_sdlgpu, sdl3_sdl_gpu_sdlgpu_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGPUSupportsShaderFormats)
{
	zend_bool result = 0;
	zval *format_flags_param = NULL, *name = NULL, name_sub, __$null;
	zend_long format_flags;

	ZVAL_UNDEF(&name_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(format_flags)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &format_flags_param, &name);
	if (!name) {
		name = &name_sub;
		name = &__$null;
	}
	
            const char *drv = (Z_TYPE_P(name) == IS_STRING) ? Z_STRVAL_P(name) : NULL;
            result = SDL_GPUSupportsShaderFormats((SDL_GPUShaderFormat) format_flags, drv);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGPUSupportsProperties)
{
	zend_bool result = 0;
	zval *props_param = NULL;
	zend_long props;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(props)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &props_param);
	
            result = SDL_GPUSupportsProperties((SDL_PropertiesID) props);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUDevice)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool debug_mode;
	zval *format_flags_param = NULL, *debug_mode_param = NULL, *name = NULL, name_sub, __$null, _0$$3, _1$$3, _2$$3;
	zend_long format_flags, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&name_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(format_flags)
		Z_PARAM_BOOL(debug_mode)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &format_flags_param, &debug_mode_param, &name);
	if (!name) {
		name = &name_sub;
		name = &__$null;
	}
	
            const char *drv = (Z_TYPE_P(name) == IS_STRING) ? Z_STRVAL_P(name) : NULL;
            SDL_GPUDevice *device = SDL_CreateGPUDevice((SDL_GPUShaderFormat) format_flags, debug_mode ? true : false, drv);
            ptr = (zend_long)(uintptr_t) device;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateGPUDevice failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 297);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUDeviceWithProperties)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *props_param = NULL, _0$$3, _1$$3, _2$$3;
	zend_long props, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(props)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &props_param);
	
            SDL_GPUDevice *device = SDL_CreateGPUDeviceWithProperties((SDL_PropertiesID) props);
            ptr = (zend_long)(uintptr_t) device;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateGPUDeviceWithProperties failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 313);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDestroyGPUDevice)
{
	zval *device_param = NULL;
	zend_long device;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(device)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &device_param);
	
            SDL_DestroyGPUDevice((SDL_GPUDevice *)(uintptr_t) device);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetNumGPUDrivers)
{
	zend_long result = 0;
	
            result = (zend_long) SDL_GetNumGPUDrivers();
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUDriver)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *index_param = NULL;
	zend_long index;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &index_param);
	ZEPHIR_INIT_VAR(&result);
	
            const char *drv = SDL_GetGPUDriver((int) index);
            if (drv != NULL) {
                ZVAL_STRING(&result, drv);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUDeviceDriver)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *device_param = NULL;
	zend_long device;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(device)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &device_param);
	ZEPHIR_INIT_VAR(&result);
	
            const char *drv = SDL_GetGPUDeviceDriver((SDL_GPUDevice *)(uintptr_t) device);
            if (drv != NULL) {
                ZVAL_STRING(&result, drv);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUShaderFormats)
{
	zval *device_param = NULL;
	zend_long device, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(device)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &device_param);
	
            result = (zend_long) SDL_GetGPUShaderFormats((SDL_GPUDevice *)(uintptr_t) device);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUDeviceProperties)
{
	zval *device_param = NULL;
	zend_long device, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(device)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &device_param);
	
            result = (zend_long) SDL_GetGPUDeviceProperties((SDL_GPUDevice *)(uintptr_t) device);
        
	RETURN_LONG(result);
}

/**
 * createinfo: ["code": string (bytecode), "entrypoint": string, "format": int,
 *  "num_samplers": int, "num_readonly_storage_textures": int,
 *  "num_readonly_storage_buffers": int, "num_readwrite_storage_textures": int,
 *  "num_readwrite_storage_buffers": int, "num_uniform_buffers": int,
 *  "threadcount_x": int, "threadcount_y": int, "threadcount_z": int, "props": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUComputePipeline)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *device_param = NULL, *createinfo, createinfo_sub, _0$$3, _1$$3, _2$$3;
	zend_long device, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&createinfo_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_ZVAL(createinfo)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &device_param, &createinfo);
	
            SDL_GPUComputePipelineCreateInfo ci;
            zval *code = php_sdl_gpu_field(createinfo, "code");
            zval *entry = php_sdl_gpu_field(createinfo, "entrypoint");

            SDL_zero(ci);
            if (code != NULL && Z_TYPE_P(code) == IS_STRING) {
                ci.code = (const Uint8 *) Z_STRVAL_P(code);
                ci.code_size = (size_t) Z_STRLEN_P(code);
            }
            ci.entrypoint = (entry != NULL && Z_TYPE_P(entry) == IS_STRING) ? Z_STRVAL_P(entry) : "main";
            ci.format = (SDL_GPUShaderFormat) php_sdl_gpu_long(createinfo, "format", 0);
            ci.num_samplers = (Uint32) php_sdl_gpu_long(createinfo, "num_samplers", 0);
            ci.num_readonly_storage_textures = (Uint32) php_sdl_gpu_long(createinfo, "num_readonly_storage_textures", 0);
            ci.num_readonly_storage_buffers = (Uint32) php_sdl_gpu_long(createinfo, "num_readonly_storage_buffers", 0);
            ci.num_readwrite_storage_textures = (Uint32) php_sdl_gpu_long(createinfo, "num_readwrite_storage_textures", 0);
            ci.num_readwrite_storage_buffers = (Uint32) php_sdl_gpu_long(createinfo, "num_readwrite_storage_buffers", 0);
            ci.num_uniform_buffers = (Uint32) php_sdl_gpu_long(createinfo, "num_uniform_buffers", 0);
            ci.threadcount_x = (Uint32) php_sdl_gpu_long(createinfo, "threadcount_x", 0);
            ci.threadcount_y = (Uint32) php_sdl_gpu_long(createinfo, "threadcount_y", 0);
            ci.threadcount_z = (Uint32) php_sdl_gpu_long(createinfo, "threadcount_z", 0);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            SDL_GPUComputePipeline *pipeline = SDL_CreateGPUComputePipeline((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) pipeline;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateGPUComputePipeline failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 428);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

/**
 * createinfo: ["vertex_shader": int, "fragment_shader": int,
 *  "vertex_input_state": ["vertex_buffer_descriptions": array, "vertex_attributes": array],
 *  "primitive_type": int, "rasterizer_state": array, "multisample_state": array,
 *  "depth_stencil_state": array,
 *  "target_info": ["color_target_descriptions": array, "depth_stencil_format": int,
 *                  "has_depth_stencil_target": bool],
 *  "props": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUGraphicsPipeline)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *device_param = NULL, *createinfo, createinfo_sub, _0$$3, _1$$3, _2$$3;
	zend_long device, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&createinfo_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_ZVAL(createinfo)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &device_param, &createinfo);
	
            SDL_GPUGraphicsPipelineCreateInfo ci;
            SDL_GPUVertexBufferDescription *vbds = NULL;
            SDL_GPUVertexAttribute *vats = NULL;
            SDL_GPUColorTargetDescription *ctds = NULL;
            zval *vis, *rs, *ms, *dss, *ti, *el;
            Uint32 i;

            SDL_zero(ci);
            ci.vertex_shader = (SDL_GPUShader *) php_sdl_gpu_handle(createinfo, "vertex_shader");
            ci.fragment_shader = (SDL_GPUShader *) php_sdl_gpu_handle(createinfo, "fragment_shader");
            ci.primitive_type = (SDL_GPUPrimitiveType) php_sdl_gpu_long(createinfo, "primitive_type", 0);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            vis = php_sdl_gpu_field(createinfo, "vertex_input_state");
            if (vis != NULL && Z_TYPE_P(vis) == IS_ARRAY) {
                zval *vbd_arr = php_sdl_gpu_field(vis, "vertex_buffer_descriptions");
                zval *vat_arr = php_sdl_gpu_field(vis, "vertex_attributes");
                Uint32 nvb = php_sdl_gpu_count(vbd_arr);
                Uint32 nva = php_sdl_gpu_count(vat_arr);

                if (nvb > 0) {
                    vbds = (SDL_GPUVertexBufferDescription *) emalloc(sizeof(*vbds) * nvb);
                    i = 0;
                    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(vbd_arr), el) {
                        SDL_zerop(&vbds[i]);
                        vbds[i].slot = (Uint32) php_sdl_gpu_long(el, "slot", 0);
                        vbds[i].pitch = (Uint32) php_sdl_gpu_long(el, "pitch", 0);
                        vbds[i].input_rate = (SDL_GPUVertexInputRate) php_sdl_gpu_long(el, "input_rate", 0);
                        vbds[i].instance_step_rate = (Uint32) php_sdl_gpu_long(el, "instance_step_rate", 0);
                        i++;
                    } ZEND_HASH_FOREACH_END();
                }
                if (nva > 0) {
                    vats = (SDL_GPUVertexAttribute *) emalloc(sizeof(*vats) * nva);
                    i = 0;
                    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(vat_arr), el) {
                        SDL_zerop(&vats[i]);
                        vats[i].location = (Uint32) php_sdl_gpu_long(el, "location", 0);
                        vats[i].buffer_slot = (Uint32) php_sdl_gpu_long(el, "buffer_slot", 0);
                        vats[i].format = (SDL_GPUVertexElementFormat) php_sdl_gpu_long(el, "format", 0);
                        vats[i].offset = (Uint32) php_sdl_gpu_long(el, "offset", 0);
                        i++;
                    } ZEND_HASH_FOREACH_END();
                }

                ci.vertex_input_state.vertex_buffer_descriptions = vbds;
                ci.vertex_input_state.num_vertex_buffers = nvb;
                ci.vertex_input_state.vertex_attributes = vats;
                ci.vertex_input_state.num_vertex_attributes = nva;
            }

            rs = php_sdl_gpu_field(createinfo, "rasterizer_state");
            if (rs != NULL && Z_TYPE_P(rs) == IS_ARRAY) {
                ci.rasterizer_state.fill_mode = (SDL_GPUFillMode) php_sdl_gpu_long(rs, "fill_mode", 0);
                ci.rasterizer_state.cull_mode = (SDL_GPUCullMode) php_sdl_gpu_long(rs, "cull_mode", 0);
                ci.rasterizer_state.front_face = (SDL_GPUFrontFace) php_sdl_gpu_long(rs, "front_face", 0);
                ci.rasterizer_state.depth_bias_constant_factor = (float) php_sdl_gpu_double(rs, "depth_bias_constant_factor", 0.0);
                ci.rasterizer_state.depth_bias_clamp = (float) php_sdl_gpu_double(rs, "depth_bias_clamp", 0.0);
                ci.rasterizer_state.depth_bias_slope_factor = (float) php_sdl_gpu_double(rs, "depth_bias_slope_factor", 0.0);
                ci.rasterizer_state.enable_depth_bias = php_sdl_gpu_bool(rs, "enable_depth_bias", false);
                ci.rasterizer_state.enable_depth_clip = php_sdl_gpu_bool(rs, "enable_depth_clip", false);
            }

            ms = php_sdl_gpu_field(createinfo, "multisample_state");
            if (ms != NULL && Z_TYPE_P(ms) == IS_ARRAY) {
                ci.multisample_state.sample_count = (SDL_GPUSampleCount) php_sdl_gpu_long(ms, "sample_count", 0);
                ci.multisample_state.sample_mask = (Uint32) php_sdl_gpu_long(ms, "sample_mask", 0);
                ci.multisample_state.enable_mask = php_sdl_gpu_bool(ms, "enable_mask", false);
                ci.multisample_state.enable_alpha_to_coverage = php_sdl_gpu_bool(ms, "enable_alpha_to_coverage", false);
            }

            dss = php_sdl_gpu_field(createinfo, "depth_stencil_state");
            if (dss != NULL && Z_TYPE_P(dss) == IS_ARRAY) {
                zval *back = php_sdl_gpu_field(dss, "back_stencil_state");
                zval *front = php_sdl_gpu_field(dss, "front_stencil_state");

                ci.depth_stencil_state.compare_op = (SDL_GPUCompareOp) php_sdl_gpu_long(dss, "compare_op", 0);
                if (back != NULL) {
                    php_sdl_gpu_stencil_op_state(back, &ci.depth_stencil_state.back_stencil_state);
                }
                if (front != NULL) {
                    php_sdl_gpu_stencil_op_state(front, &ci.depth_stencil_state.front_stencil_state);
                }
                ci.depth_stencil_state.compare_mask = (Uint8) php_sdl_gpu_long(dss, "compare_mask", 0);
                ci.depth_stencil_state.write_mask = (Uint8) php_sdl_gpu_long(dss, "write_mask", 0);
                ci.depth_stencil_state.enable_depth_test = php_sdl_gpu_bool(dss, "enable_depth_test", false);
                ci.depth_stencil_state.enable_depth_write = php_sdl_gpu_bool(dss, "enable_depth_write", false);
                ci.depth_stencil_state.enable_stencil_test = php_sdl_gpu_bool(dss, "enable_stencil_test", false);
            }

            ti = php_sdl_gpu_field(createinfo, "target_info");
            if (ti != NULL && Z_TYPE_P(ti) == IS_ARRAY) {
                zval *ctd_arr = php_sdl_gpu_field(ti, "color_target_descriptions");
                Uint32 nct = php_sdl_gpu_count(ctd_arr);

                if (nct > 0) {
                    ctds = (SDL_GPUColorTargetDescription *) emalloc(sizeof(*ctds) * nct);
                    i = 0;
                    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(ctd_arr), el) {
                        zval *bs = php_sdl_gpu_field(el, "blend_state");
                        SDL_zerop(&ctds[i]);
                        ctds[i].format = (SDL_GPUTextureFormat) php_sdl_gpu_long(el, "format", 0);
                        if (bs != NULL) {
                            php_sdl_gpu_color_target_blend_state(bs, &ctds[i].blend_state);
                        }
                        i++;
                    } ZEND_HASH_FOREACH_END();
                }

                ci.target_info.color_target_descriptions = ctds;
                ci.target_info.num_color_targets = nct;
                ci.target_info.depth_stencil_format = (SDL_GPUTextureFormat) php_sdl_gpu_long(ti, "depth_stencil_format", 0);
                ci.target_info.has_depth_stencil_target = php_sdl_gpu_bool(ti, "has_depth_stencil_target", false);
            }

            SDL_GPUGraphicsPipeline *pipeline = SDL_CreateGPUGraphicsPipeline((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) pipeline;

            if (vbds != NULL) { efree(vbds); }
            if (vats != NULL) { efree(vats); }
            if (ctds != NULL) { efree(ctds); }
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateGPUGraphicsPipeline failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 572);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

/**
 * createinfo: ["min_filter": int, "mag_filter": int, "mipmap_mode": int,
 *  "address_mode_u": int, "address_mode_v": int, "address_mode_w": int,
 *  "mip_lod_bias": float, "max_anisotropy": float, "compare_op": int,
 *  "min_lod": float, "max_lod": float, "enable_anisotropy": bool,
 *  "enable_compare": bool, "props": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUSampler)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *device_param = NULL, *createinfo, createinfo_sub, _0$$3, _1$$3, _2$$3;
	zend_long device, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&createinfo_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_ZVAL(createinfo)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &device_param, &createinfo);
	
            SDL_GPUSamplerCreateInfo ci;

            SDL_zero(ci);
            ci.min_filter = (SDL_GPUFilter) php_sdl_gpu_long(createinfo, "min_filter", 0);
            ci.mag_filter = (SDL_GPUFilter) php_sdl_gpu_long(createinfo, "mag_filter", 0);
            ci.mipmap_mode = (SDL_GPUSamplerMipmapMode) php_sdl_gpu_long(createinfo, "mipmap_mode", 0);
            ci.address_mode_u = (SDL_GPUSamplerAddressMode) php_sdl_gpu_long(createinfo, "address_mode_u", 0);
            ci.address_mode_v = (SDL_GPUSamplerAddressMode) php_sdl_gpu_long(createinfo, "address_mode_v", 0);
            ci.address_mode_w = (SDL_GPUSamplerAddressMode) php_sdl_gpu_long(createinfo, "address_mode_w", 0);
            ci.mip_lod_bias = (float) php_sdl_gpu_double(createinfo, "mip_lod_bias", 0.0);
            ci.max_anisotropy = (float) php_sdl_gpu_double(createinfo, "max_anisotropy", 0.0);
            ci.compare_op = (SDL_GPUCompareOp) php_sdl_gpu_long(createinfo, "compare_op", 0);
            ci.min_lod = (float) php_sdl_gpu_double(createinfo, "min_lod", 0.0);
            ci.max_lod = (float) php_sdl_gpu_double(createinfo, "max_lod", 0.0);
            ci.enable_anisotropy = php_sdl_gpu_bool(createinfo, "enable_anisotropy", false);
            ci.enable_compare = php_sdl_gpu_bool(createinfo, "enable_compare", false);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            SDL_GPUSampler *sampler = SDL_CreateGPUSampler((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) sampler;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateGPUSampler failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 613);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

/**
 * createinfo: ["code": string (bytecode), "entrypoint": string, "format": int,
 *  "stage": int, "num_samplers": int, "num_storage_textures": int,
 *  "num_storage_buffers": int, "num_uniform_buffers": int, "props": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUShader)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *device_param = NULL, *createinfo, createinfo_sub, _0$$3, _1$$3, _2$$3;
	zend_long device, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&createinfo_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_ZVAL(createinfo)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &device_param, &createinfo);
	
            SDL_GPUShaderCreateInfo ci;
            zval *code = php_sdl_gpu_field(createinfo, "code");
            zval *entry = php_sdl_gpu_field(createinfo, "entrypoint");

            SDL_zero(ci);
            if (code != NULL && Z_TYPE_P(code) == IS_STRING) {
                ci.code = (const Uint8 *) Z_STRVAL_P(code);
                ci.code_size = (size_t) Z_STRLEN_P(code);
            }
            ci.entrypoint = (entry != NULL && Z_TYPE_P(entry) == IS_STRING) ? Z_STRVAL_P(entry) : "main";
            ci.format = (SDL_GPUShaderFormat) php_sdl_gpu_long(createinfo, "format", 0);
            ci.stage = (SDL_GPUShaderStage) php_sdl_gpu_long(createinfo, "stage", 0);
            ci.num_samplers = (Uint32) php_sdl_gpu_long(createinfo, "num_samplers", 0);
            ci.num_storage_textures = (Uint32) php_sdl_gpu_long(createinfo, "num_storage_textures", 0);
            ci.num_storage_buffers = (Uint32) php_sdl_gpu_long(createinfo, "num_storage_buffers", 0);
            ci.num_uniform_buffers = (Uint32) php_sdl_gpu_long(createinfo, "num_uniform_buffers", 0);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            SDL_GPUShader *shader = SDL_CreateGPUShader((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) shader;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateGPUShader failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 652);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

/**
 * createinfo: ["type": int, "format": int, "usage": int, "width": int,
 *  "height": int, "layer_count_or_depth": int, "num_levels": int,
 *  "sample_count": int, "props": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUTexture)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *device_param = NULL, *createinfo, createinfo_sub, _0$$3, _1$$3, _2$$3;
	zend_long device, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&createinfo_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_ZVAL(createinfo)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &device_param, &createinfo);
	
            SDL_GPUTextureCreateInfo ci;

            SDL_zero(ci);
            ci.type = (SDL_GPUTextureType) php_sdl_gpu_long(createinfo, "type", 0);
            ci.format = (SDL_GPUTextureFormat) php_sdl_gpu_long(createinfo, "format", 0);
            ci.usage = (SDL_GPUTextureUsageFlags) php_sdl_gpu_long(createinfo, "usage", 0);
            ci.width = (Uint32) php_sdl_gpu_long(createinfo, "width", 0);
            ci.height = (Uint32) php_sdl_gpu_long(createinfo, "height", 0);
            ci.layer_count_or_depth = (Uint32) php_sdl_gpu_long(createinfo, "layer_count_or_depth", 1);
            ci.num_levels = (Uint32) php_sdl_gpu_long(createinfo, "num_levels", 1);
            ci.sample_count = (SDL_GPUSampleCount) php_sdl_gpu_long(createinfo, "sample_count", 0);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            SDL_GPUTexture *texture = SDL_CreateGPUTexture((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) texture;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateGPUTexture failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 686);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

/**
 * createinfo: ["usage": int, "size": int, "props": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUBuffer)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *device_param = NULL, *createinfo, createinfo_sub, _0$$3, _1$$3, _2$$3;
	zend_long device, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&createinfo_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_ZVAL(createinfo)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &device_param, &createinfo);
	
            SDL_GPUBufferCreateInfo ci;

            SDL_zero(ci);
            ci.usage = (SDL_GPUBufferUsageFlags) php_sdl_gpu_long(createinfo, "usage", 0);
            ci.size = (Uint32) php_sdl_gpu_long(createinfo, "size", 0);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            SDL_GPUBuffer *buf = SDL_CreateGPUBuffer((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) buf;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateGPUBuffer failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 712);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

/**
 * createinfo: ["usage": int, "size": int, "props": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPUTransferBuffer)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *device_param = NULL, *createinfo, createinfo_sub, _0$$3, _1$$3, _2$$3;
	zend_long device, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&createinfo_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_ZVAL(createinfo)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &device_param, &createinfo);
	
            SDL_GPUTransferBufferCreateInfo ci;

            SDL_zero(ci);
            ci.usage = (SDL_GPUTransferBufferUsage) php_sdl_gpu_long(createinfo, "usage", 0);
            ci.size = (Uint32) php_sdl_gpu_long(createinfo, "size", 0);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            SDL_GPUTransferBuffer *buf = SDL_CreateGPUTransferBuffer((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) buf;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateGPUTransferBuffer failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 738);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUBufferName)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval text;
	zval *device_param = NULL, *buffer_param = NULL, *text_param = NULL;
	zend_long device, buffer;

	ZVAL_UNDEF(&text);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(buffer)
		Z_PARAM_STR(text)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &device_param, &buffer_param, &text_param);
	zephir_get_strval(&text, text_param);
	
            SDL_SetGPUBufferName((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUBuffer *)(uintptr_t) buffer, Z_STRVAL(text));
        
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUTextureName)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval text;
	zval *device_param = NULL, *texture_param = NULL, *text_param = NULL;
	zend_long device, texture;

	ZVAL_UNDEF(&text);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(texture)
		Z_PARAM_STR(text)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &device_param, &texture_param, &text_param);
	zephir_get_strval(&text, text_param);
	
            SDL_SetGPUTextureName((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUTexture *)(uintptr_t) texture, Z_STRVAL(text));
        
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLInsertGPUDebugLabel)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval text;
	zval *command_buffer_param = NULL, *text_param = NULL;
	zend_long command_buffer;

	ZVAL_UNDEF(&text);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(command_buffer)
		Z_PARAM_STR(text)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &command_buffer_param, &text_param);
	zephir_get_strval(&text, text_param);
	
            SDL_InsertGPUDebugLabel((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer, Z_STRVAL(text));
        
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLPushGPUDebugGroup)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval name;
	zval *command_buffer_param = NULL, *name_param = NULL;
	zend_long command_buffer;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(command_buffer)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &command_buffer_param, &name_param);
	zephir_get_strval(&name, name_param);
	
            SDL_PushGPUDebugGroup((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer, Z_STRVAL(name));
        
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLPopGPUDebugGroup)
{
	zval *command_buffer_param = NULL;
	zend_long command_buffer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(command_buffer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &command_buffer_param);
	
            SDL_PopGPUDebugGroup((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUTexture)
{
	zval *device_param = NULL, *texture_param = NULL;
	zend_long device, texture;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &texture_param);
	
            SDL_ReleaseGPUTexture((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUTexture *)(uintptr_t) texture);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUSampler)
{
	zval *device_param = NULL, *sampler_param = NULL;
	zend_long device, sampler;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(sampler)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &sampler_param);
	
            SDL_ReleaseGPUSampler((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUSampler *)(uintptr_t) sampler);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUBuffer)
{
	zval *device_param = NULL, *buffer_param = NULL;
	zend_long device, buffer;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(buffer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &buffer_param);
	
            SDL_ReleaseGPUBuffer((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUBuffer *)(uintptr_t) buffer);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUTransferBuffer)
{
	zval *device_param = NULL, *transfer_buffer_param = NULL;
	zend_long device, transfer_buffer;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(transfer_buffer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &transfer_buffer_param);
	
            SDL_ReleaseGPUTransferBuffer((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUComputePipeline)
{
	zval *device_param = NULL, *compute_pipeline_param = NULL;
	zend_long device, compute_pipeline;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(compute_pipeline)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &compute_pipeline_param);
	
            SDL_ReleaseGPUComputePipeline((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUComputePipeline *)(uintptr_t) compute_pipeline);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUShader)
{
	zval *device_param = NULL, *shader_param = NULL;
	zend_long device, shader;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(shader)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &shader_param);
	
            SDL_ReleaseGPUShader((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUShader *)(uintptr_t) shader);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUGraphicsPipeline)
{
	zval *device_param = NULL, *graphics_pipeline_param = NULL;
	zend_long device, graphics_pipeline;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(graphics_pipeline)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &graphics_pipeline_param);
	
            SDL_ReleaseGPUGraphicsPipeline((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUGraphicsPipeline *)(uintptr_t) graphics_pipeline);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLAcquireGPUCommandBuffer)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *device_param = NULL, _0$$3, _1$$3, _2$$3;
	zend_long device, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(device)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &device_param);
	
            SDL_GPUCommandBuffer *cb = SDL_AcquireGPUCommandBuffer((SDL_GPUDevice *)(uintptr_t) device);
            ptr = (zend_long)(uintptr_t) cb;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_AcquireGPUCommandBuffer failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 844);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLPushGPUVertexUniformData)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval data;
	zval *command_buffer_param = NULL, *slot_index_param = NULL, *data_param = NULL;
	zend_long command_buffer, slot_index;

	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(command_buffer)
		Z_PARAM_LONG(slot_index)
		Z_PARAM_STR(data)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &command_buffer_param, &slot_index_param, &data_param);
	zephir_get_strval(&data, data_param);
	
            SDL_PushGPUVertexUniformData(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                (Uint32) slot_index,
                (const void *) Z_STRVAL(data),
                (Uint32) Z_STRLEN(data)
            );
        
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLPushGPUFragmentUniformData)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval data;
	zval *command_buffer_param = NULL, *slot_index_param = NULL, *data_param = NULL;
	zend_long command_buffer, slot_index;

	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(command_buffer)
		Z_PARAM_LONG(slot_index)
		Z_PARAM_STR(data)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &command_buffer_param, &slot_index_param, &data_param);
	zephir_get_strval(&data, data_param);
	
            SDL_PushGPUFragmentUniformData(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                (Uint32) slot_index,
                (const void *) Z_STRVAL(data),
                (Uint32) Z_STRLEN(data)
            );
        
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLPushGPUComputeUniformData)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval data;
	zval *command_buffer_param = NULL, *slot_index_param = NULL, *data_param = NULL;
	zend_long command_buffer, slot_index;

	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(command_buffer)
		Z_PARAM_LONG(slot_index)
		Z_PARAM_STR(data)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &command_buffer_param, &slot_index_param, &data_param);
	zephir_get_strval(&data, data_param);
	
            SDL_PushGPUComputeUniformData(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                (Uint32) slot_index,
                (const void *) Z_STRVAL(data),
                (Uint32) Z_STRLEN(data)
            );
        
	ZEPHIR_MM_RESTORE();
}

/**
 * color_target_infos: array of ["texture": int, "mip_level": int,
 *  "layer_or_depth_plane": int, "clear_color": ["r","g","b","a"],
 *  "load_op": int, "store_op": int, "resolve_texture": int,
 *  "resolve_mip_level": int, "resolve_layer": int, "cycle": bool,
 *  "cycle_resolve_texture": bool]
 * depth_stencil_target_info: assoc array or null.
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBeginGPURenderPass)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *command_buffer_param = NULL, *color_target_infos, color_target_infos_sub, *depth_stencil_target_info = NULL, depth_stencil_target_info_sub, __$null, _0$$3, _1$$3, _2$$3;
	zend_long command_buffer, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&color_target_infos_sub);
	ZVAL_UNDEF(&depth_stencil_target_info_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(command_buffer)
		Z_PARAM_ZVAL(color_target_infos)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(depth_stencil_target_info)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &command_buffer_param, &color_target_infos, &depth_stencil_target_info);
	if (!depth_stencil_target_info) {
		depth_stencil_target_info = &depth_stencil_target_info_sub;
		depth_stencil_target_info = &__$null;
	}
	
            SDL_GPUColorTargetInfo *targets = NULL;
            SDL_GPUDepthStencilTargetInfo ds;
            SDL_GPUDepthStencilTargetInfo *dsp = NULL;
            Uint32 num_targets = php_sdl_gpu_count(color_target_infos);
            zval *el;
            Uint32 i = 0;

            if (num_targets > 0) {
                targets = (SDL_GPUColorTargetInfo *) emalloc(sizeof(*targets) * num_targets);
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(color_target_infos), el) {
                    php_sdl_gpu_color_target_info(el, &targets[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }

            if (Z_TYPE_P(depth_stencil_target_info) == IS_ARRAY) {
                php_sdl_gpu_depth_stencil_target_info(depth_stencil_target_info, &ds);
                dsp = &ds;
            }

            SDL_GPURenderPass *pass = SDL_BeginGPURenderPass(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                targets, num_targets, dsp
            );
            ptr = (zend_long)(uintptr_t) pass;

            if (targets != NULL) { efree(targets); }
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_BeginGPURenderPass failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 931);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUGraphicsPipeline)
{
	zval *render_pass_param = NULL, *graphics_pipeline_param = NULL;
	zend_long render_pass, graphics_pipeline;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_LONG(graphics_pipeline)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &render_pass_param, &graphics_pipeline_param);
	
            SDL_BindGPUGraphicsPipeline((SDL_GPURenderPass *)(uintptr_t) render_pass, (SDL_GPUGraphicsPipeline *)(uintptr_t) graphics_pipeline);
        
}

/**
 * viewport: ["x", "y", "w", "h", "min_depth", "max_depth"]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUViewport)
{
	zval *render_pass_param = NULL, *viewport, viewport_sub;
	zend_long render_pass;

	ZVAL_UNDEF(&viewport_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_ZVAL(viewport)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &render_pass_param, &viewport);
	
            SDL_GPUViewport vp;
            php_sdl_gpu_viewport(viewport, &vp);
            SDL_SetGPUViewport((SDL_GPURenderPass *)(uintptr_t) render_pass, &vp);
        
}

/**
 * scissor: ["x": int, "y": int, "w": int, "h": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUScissor)
{
	zval *render_pass_param = NULL, *scissor, scissor_sub;
	zend_long render_pass;

	ZVAL_UNDEF(&scissor_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_ZVAL(scissor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &render_pass_param, &scissor);
	
            SDL_Rect rect;
            rect.x = (int) php_sdl_gpu_long(scissor, "x", 0);
            rect.y = (int) php_sdl_gpu_long(scissor, "y", 0);
            rect.w = (int) php_sdl_gpu_long(scissor, "w", 0);
            rect.h = (int) php_sdl_gpu_long(scissor, "h", 0);
            SDL_SetGPUScissor((SDL_GPURenderPass *)(uintptr_t) render_pass, &rect);
        
}

/**
 * blend_constants: ["r", "g", "b", "a"] floats
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUBlendConstants)
{
	zval *render_pass_param = NULL, *blend_constants, blend_constants_sub;
	zend_long render_pass;

	ZVAL_UNDEF(&blend_constants_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_ZVAL(blend_constants)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &render_pass_param, &blend_constants);
	
            SDL_FColor color;
            php_sdl_gpu_fcolor(blend_constants, &color);
            SDL_SetGPUBlendConstants((SDL_GPURenderPass *)(uintptr_t) render_pass, color);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUStencilReference)
{
	zval *render_pass_param = NULL, *reference_param = NULL;
	zend_long render_pass, reference;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_LONG(reference)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &render_pass_param, &reference_param);
	
            SDL_SetGPUStencilReference((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint8) reference);
        
}

/**
 * bindings: array of ["buffer": int, "offset": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUVertexBuffers)
{
	zval *render_pass_param = NULL, *first_slot_param = NULL, *bindings, bindings_sub;
	zend_long render_pass, first_slot;

	ZVAL_UNDEF(&bindings_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ZVAL(bindings)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &render_pass_param, &first_slot_param, &bindings);
	
            SDL_GPUBufferBinding *items = NULL;
            Uint32 n = php_sdl_gpu_count(bindings);
            Uint32 i = 0;
            zval *el;

            if (n > 0) {
                items = (SDL_GPUBufferBinding *) emalloc(sizeof(*items) * n);
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(bindings), el) {
                    php_sdl_gpu_buffer_binding(el, &items[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }

            SDL_BindGPUVertexBuffers((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, items, n);

            if (items != NULL) { efree(items); }
        
}

/**
 * binding: ["buffer": int, "offset": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUIndexBuffer)
{
	zval *render_pass_param = NULL, *binding, binding_sub, *index_element_size_param = NULL;
	zend_long render_pass, index_element_size;

	ZVAL_UNDEF(&binding_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_ZVAL(binding)
		Z_PARAM_LONG(index_element_size)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &render_pass_param, &binding, &index_element_size_param);
	
            SDL_GPUBufferBinding item;
            php_sdl_gpu_buffer_binding(binding, &item);
            SDL_BindGPUIndexBuffer((SDL_GPURenderPass *)(uintptr_t) render_pass, &item, (SDL_GPUIndexElementSize) index_element_size);
        
}

/**
 * bindings: array of ["texture": int, "sampler": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUVertexSamplers)
{
	zval *render_pass_param = NULL, *first_slot_param = NULL, *bindings, bindings_sub;
	zend_long render_pass, first_slot;

	ZVAL_UNDEF(&bindings_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ZVAL(bindings)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &render_pass_param, &first_slot_param, &bindings);
	
            SDL_GPUTextureSamplerBinding *items = NULL;
            Uint32 n = php_sdl_gpu_count(bindings);
            Uint32 i = 0;
            zval *el;

            if (n > 0) {
                items = (SDL_GPUTextureSamplerBinding *) emalloc(sizeof(*items) * n);
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(bindings), el) {
                    php_sdl_gpu_texture_sampler_binding(el, &items[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }

            SDL_BindGPUVertexSamplers((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, items, n);

            if (items != NULL) { efree(items); }
        
}

/**
 * storage_textures: array of int texture handles
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUVertexStorageTextures)
{
	zval *render_pass_param = NULL, *first_slot_param = NULL, *storage_textures, storage_textures_sub;
	zend_long render_pass, first_slot;

	ZVAL_UNDEF(&storage_textures_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ZVAL(storage_textures)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &render_pass_param, &first_slot_param, &storage_textures);
	
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(storage_textures, &n);

            SDL_BindGPUVertexStorageTextures((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, (SDL_GPUTexture *const *) items, n);

            if (items != NULL) { efree(items); }
        
}

/**
 * storage_buffers: array of int buffer handles
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUVertexStorageBuffers)
{
	zval *render_pass_param = NULL, *first_slot_param = NULL, *storage_buffers, storage_buffers_sub;
	zend_long render_pass, first_slot;

	ZVAL_UNDEF(&storage_buffers_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ZVAL(storage_buffers)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &render_pass_param, &first_slot_param, &storage_buffers);
	
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(storage_buffers, &n);

            SDL_BindGPUVertexStorageBuffers((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, (SDL_GPUBuffer *const *) items, n);

            if (items != NULL) { efree(items); }
        
}

/**
 * bindings: array of ["texture": int, "sampler": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUFragmentSamplers)
{
	zval *render_pass_param = NULL, *first_slot_param = NULL, *bindings, bindings_sub;
	zend_long render_pass, first_slot;

	ZVAL_UNDEF(&bindings_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ZVAL(bindings)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &render_pass_param, &first_slot_param, &bindings);
	
            SDL_GPUTextureSamplerBinding *items = NULL;
            Uint32 n = php_sdl_gpu_count(bindings);
            Uint32 i = 0;
            zval *el;

            if (n > 0) {
                items = (SDL_GPUTextureSamplerBinding *) emalloc(sizeof(*items) * n);
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(bindings), el) {
                    php_sdl_gpu_texture_sampler_binding(el, &items[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }

            SDL_BindGPUFragmentSamplers((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, items, n);

            if (items != NULL) { efree(items); }
        
}

/**
 * storage_textures: array of int texture handles
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUFragmentStorageTextures)
{
	zval *render_pass_param = NULL, *first_slot_param = NULL, *storage_textures, storage_textures_sub;
	zend_long render_pass, first_slot;

	ZVAL_UNDEF(&storage_textures_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ZVAL(storage_textures)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &render_pass_param, &first_slot_param, &storage_textures);
	
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(storage_textures, &n);

            SDL_BindGPUFragmentStorageTextures((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, (SDL_GPUTexture *const *) items, n);

            if (items != NULL) { efree(items); }
        
}

/**
 * storage_buffers: array of int buffer handles
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUFragmentStorageBuffers)
{
	zval *render_pass_param = NULL, *first_slot_param = NULL, *storage_buffers, storage_buffers_sub;
	zend_long render_pass, first_slot;

	ZVAL_UNDEF(&storage_buffers_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ZVAL(storage_buffers)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &render_pass_param, &first_slot_param, &storage_buffers);
	
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(storage_buffers, &n);

            SDL_BindGPUFragmentStorageBuffers((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, (SDL_GPUBuffer *const *) items, n);

            if (items != NULL) { efree(items); }
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDrawGPUIndexedPrimitives)
{
	zval *render_pass_param = NULL, *num_indices_param = NULL, *num_instances_param = NULL, *first_index_param = NULL, *vertex_offset_param = NULL, *first_instance_param = NULL;
	zend_long render_pass, num_indices, num_instances, first_index, vertex_offset, first_instance;

	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_LONG(num_indices)
		Z_PARAM_LONG(num_instances)
		Z_PARAM_LONG(first_index)
		Z_PARAM_LONG(vertex_offset)
		Z_PARAM_LONG(first_instance)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(6, 0, &render_pass_param, &num_indices_param, &num_instances_param, &first_index_param, &vertex_offset_param, &first_instance_param);
	
            SDL_DrawGPUIndexedPrimitives(
                (SDL_GPURenderPass *)(uintptr_t) render_pass,
                (Uint32) num_indices, (Uint32) num_instances,
                (Uint32) first_index, (Sint32) vertex_offset, (Uint32) first_instance
            );
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDrawGPUPrimitives)
{
	zval *render_pass_param = NULL, *num_vertices_param = NULL, *num_instances_param = NULL, *first_vertex_param = NULL, *first_instance_param = NULL;
	zend_long render_pass, num_vertices, num_instances, first_vertex, first_instance;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_LONG(num_vertices)
		Z_PARAM_LONG(num_instances)
		Z_PARAM_LONG(first_vertex)
		Z_PARAM_LONG(first_instance)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &render_pass_param, &num_vertices_param, &num_instances_param, &first_vertex_param, &first_instance_param);
	
            SDL_DrawGPUPrimitives(
                (SDL_GPURenderPass *)(uintptr_t) render_pass,
                (Uint32) num_vertices, (Uint32) num_instances,
                (Uint32) first_vertex, (Uint32) first_instance
            );
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDrawGPUPrimitivesIndirect)
{
	zval *render_pass_param = NULL, *buffer_param = NULL, *offset_param = NULL, *draw_count_param = NULL;
	zend_long render_pass, buffer, offset, draw_count;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_LONG(buffer)
		Z_PARAM_LONG(offset)
		Z_PARAM_LONG(draw_count)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &render_pass_param, &buffer_param, &offset_param, &draw_count_param);
	
            SDL_DrawGPUPrimitivesIndirect(
                (SDL_GPURenderPass *)(uintptr_t) render_pass,
                (SDL_GPUBuffer *)(uintptr_t) buffer,
                (Uint32) offset, (Uint32) draw_count
            );
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDrawGPUIndexedPrimitivesIndirect)
{
	zval *render_pass_param = NULL, *buffer_param = NULL, *offset_param = NULL, *draw_count_param = NULL;
	zend_long render_pass, buffer, offset, draw_count;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(render_pass)
		Z_PARAM_LONG(buffer)
		Z_PARAM_LONG(offset)
		Z_PARAM_LONG(draw_count)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &render_pass_param, &buffer_param, &offset_param, &draw_count_param);
	
            SDL_DrawGPUIndexedPrimitivesIndirect(
                (SDL_GPURenderPass *)(uintptr_t) render_pass,
                (SDL_GPUBuffer *)(uintptr_t) buffer,
                (Uint32) offset, (Uint32) draw_count
            );
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLEndGPURenderPass)
{
	zval *render_pass_param = NULL;
	zend_long render_pass;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(render_pass)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &render_pass_param);
	
            SDL_EndGPURenderPass((SDL_GPURenderPass *)(uintptr_t) render_pass);
        
}

/**
 * storage_texture_bindings: array of ["texture": int, "mip_level": int, "layer": int, "cycle": bool]
 * storage_buffer_bindings: array of ["buffer": int, "cycle": bool]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBeginGPUComputePass)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *command_buffer_param = NULL, *storage_texture_bindings = NULL, storage_texture_bindings_sub, *storage_buffer_bindings = NULL, storage_buffer_bindings_sub, __$null, _0$$3, _1$$3, _2$$3;
	zend_long command_buffer, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&storage_texture_bindings_sub);
	ZVAL_UNDEF(&storage_buffer_bindings_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_LONG(command_buffer)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(storage_texture_bindings)
		Z_PARAM_ZVAL_OR_NULL(storage_buffer_bindings)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &command_buffer_param, &storage_texture_bindings, &storage_buffer_bindings);
	if (!storage_texture_bindings) {
		storage_texture_bindings = &storage_texture_bindings_sub;
		storage_texture_bindings = &__$null;
	}
	if (!storage_buffer_bindings) {
		storage_buffer_bindings = &storage_buffer_bindings_sub;
		storage_buffer_bindings = &__$null;
	}
	
            SDL_GPUStorageTextureReadWriteBinding *tex_items = NULL;
            SDL_GPUStorageBufferReadWriteBinding *buf_items = NULL;
            Uint32 num_tex = php_sdl_gpu_count(storage_texture_bindings);
            Uint32 num_buf = php_sdl_gpu_count(storage_buffer_bindings);
            Uint32 i;
            zval *el;

            if (num_tex > 0) {
                tex_items = (SDL_GPUStorageTextureReadWriteBinding *) emalloc(sizeof(*tex_items) * num_tex);
                i = 0;
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(storage_texture_bindings), el) {
                    php_sdl_gpu_storage_texture_rw_binding(el, &tex_items[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }
            if (num_buf > 0) {
                buf_items = (SDL_GPUStorageBufferReadWriteBinding *) emalloc(sizeof(*buf_items) * num_buf);
                i = 0;
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(storage_buffer_bindings), el) {
                    php_sdl_gpu_storage_buffer_rw_binding(el, &buf_items[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }

            SDL_GPUComputePass *pass = SDL_BeginGPUComputePass(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                tex_items, num_tex, buf_items, num_buf
            );
            ptr = (zend_long)(uintptr_t) pass;

            if (tex_items != NULL) { efree(tex_items); }
            if (buf_items != NULL) { efree(buf_items); }
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_BeginGPUComputePass failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 1234);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUComputePipeline)
{
	zval *compute_pass_param = NULL, *compute_pipeline_param = NULL;
	zend_long compute_pass, compute_pipeline;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(compute_pass)
		Z_PARAM_LONG(compute_pipeline)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &compute_pass_param, &compute_pipeline_param);
	
            SDL_BindGPUComputePipeline((SDL_GPUComputePass *)(uintptr_t) compute_pass, (SDL_GPUComputePipeline *)(uintptr_t) compute_pipeline);
        
}

/**
 * bindings: array of ["texture": int, "sampler": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUComputeSamplers)
{
	zval *compute_pass_param = NULL, *first_slot_param = NULL, *bindings, bindings_sub;
	zend_long compute_pass, first_slot;

	ZVAL_UNDEF(&bindings_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(compute_pass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ZVAL(bindings)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &compute_pass_param, &first_slot_param, &bindings);
	
            SDL_GPUTextureSamplerBinding *items = NULL;
            Uint32 n = php_sdl_gpu_count(bindings);
            Uint32 i = 0;
            zval *el;

            if (n > 0) {
                items = (SDL_GPUTextureSamplerBinding *) emalloc(sizeof(*items) * n);
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(bindings), el) {
                    php_sdl_gpu_texture_sampler_binding(el, &items[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }

            SDL_BindGPUComputeSamplers((SDL_GPUComputePass *)(uintptr_t) compute_pass, (Uint32) first_slot, items, n);

            if (items != NULL) { efree(items); }
        
}

/**
 * storage_textures: array of int texture handles
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUComputeStorageTextures)
{
	zval *compute_pass_param = NULL, *first_slot_param = NULL, *storage_textures, storage_textures_sub;
	zend_long compute_pass, first_slot;

	ZVAL_UNDEF(&storage_textures_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(compute_pass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ZVAL(storage_textures)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &compute_pass_param, &first_slot_param, &storage_textures);
	
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(storage_textures, &n);

            SDL_BindGPUComputeStorageTextures((SDL_GPUComputePass *)(uintptr_t) compute_pass, (Uint32) first_slot, (SDL_GPUTexture *const *) items, n);

            if (items != NULL) { efree(items); }
        
}

/**
 * storage_buffers: array of int buffer handles
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBindGPUComputeStorageBuffers)
{
	zval *compute_pass_param = NULL, *first_slot_param = NULL, *storage_buffers, storage_buffers_sub;
	zend_long compute_pass, first_slot;

	ZVAL_UNDEF(&storage_buffers_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(compute_pass)
		Z_PARAM_LONG(first_slot)
		Z_PARAM_ZVAL(storage_buffers)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &compute_pass_param, &first_slot_param, &storage_buffers);
	
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(storage_buffers, &n);

            SDL_BindGPUComputeStorageBuffers((SDL_GPUComputePass *)(uintptr_t) compute_pass, (Uint32) first_slot, (SDL_GPUBuffer *const *) items, n);

            if (items != NULL) { efree(items); }
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDispatchGPUCompute)
{
	zval *compute_pass_param = NULL, *groupcount_x_param = NULL, *groupcount_y_param = NULL, *groupcount_z_param = NULL;
	zend_long compute_pass, groupcount_x, groupcount_y, groupcount_z;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(compute_pass)
		Z_PARAM_LONG(groupcount_x)
		Z_PARAM_LONG(groupcount_y)
		Z_PARAM_LONG(groupcount_z)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &compute_pass_param, &groupcount_x_param, &groupcount_y_param, &groupcount_z_param);
	
            SDL_DispatchGPUCompute(
                (SDL_GPUComputePass *)(uintptr_t) compute_pass,
                (Uint32) groupcount_x, (Uint32) groupcount_y, (Uint32) groupcount_z
            );
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDispatchGPUComputeIndirect)
{
	zval *compute_pass_param = NULL, *buffer_param = NULL, *offset_param = NULL;
	zend_long compute_pass, buffer, offset;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(compute_pass)
		Z_PARAM_LONG(buffer)
		Z_PARAM_LONG(offset)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &compute_pass_param, &buffer_param, &offset_param);
	
            SDL_DispatchGPUComputeIndirect(
                (SDL_GPUComputePass *)(uintptr_t) compute_pass,
                (SDL_GPUBuffer *)(uintptr_t) buffer,
                (Uint32) offset
            );
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLEndGPUComputePass)
{
	zval *compute_pass_param = NULL;
	zend_long compute_pass;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(compute_pass)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &compute_pass_param);
	
            SDL_EndGPUComputePass((SDL_GPUComputePass *)(uintptr_t) compute_pass);
        
}

/**
 * Returns the mapped memory address as an opaque int. Prefer the
 * writeToGPUTransferBuffer / readFromGPUTransferBuffer helpers, which
 * handle the map/copy/unmap cycle with PHP binary strings.
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLMapGPUTransferBuffer)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool cycle;
	zval *device_param = NULL, *transfer_buffer_param = NULL, *cycle_param = NULL, _0$$3, _1$$3, _2$$3;
	zend_long device, transfer_buffer, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(transfer_buffer)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(cycle)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &device_param, &transfer_buffer_param, &cycle_param);
	if (!cycle_param) {
		cycle = 0;
	} else {
		}
	
            void *mapped = SDL_MapGPUTransferBuffer(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer,
                cycle ? true : false
            );
            ptr = (zend_long)(uintptr_t) mapped;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_MapGPUTransferBuffer failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 1351);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLUnmapGPUTransferBuffer)
{
	zval *device_param = NULL, *transfer_buffer_param = NULL;
	zend_long device, transfer_buffer;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(transfer_buffer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &transfer_buffer_param);
	
            SDL_UnmapGPUTransferBuffer(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer
            );
        
}

/**
 * Helper: maps the transfer buffer, copies the binary string into it at
 * the given byte offset, and unmaps it.
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, writeToGPUTransferBuffer)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool cycle, result;
	zval data;
	zval *device_param = NULL, *transfer_buffer_param = NULL, *data_param = NULL, *cycle_param = NULL, *offset_param = NULL;
	zend_long device, transfer_buffer, offset;

	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(3, 5)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(transfer_buffer)
		Z_PARAM_STR(data)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(cycle)
		Z_PARAM_LONG(offset)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 2, &device_param, &transfer_buffer_param, &data_param, &cycle_param, &offset_param);
	zephir_get_strval(&data, data_param);
	if (!cycle_param) {
		cycle = 0;
	} else {
		}
	if (!offset_param) {
		offset = 0;
	} else {
		}
	result = 0;
	if (offset < 0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "offset must be >= 0", "sdl3/sdl/gpu/sdlgpu.zep", 1376);
		return;
	}
	
            void *mapped = SDL_MapGPUTransferBuffer(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer,
                cycle ? true : false
            );

            if (mapped != NULL) {
                memcpy((Uint8 *) mapped + (size_t) offset, Z_STRVAL(data), Z_STRLEN(data));
                SDL_UnmapGPUTransferBuffer(
                    (SDL_GPUDevice *)(uintptr_t) device,
                    (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer
                );
                result = true;
            }
        
	RETURN_MM_BOOL(result);
}

/**
 * Helper: maps the transfer buffer, copies `length` bytes out from the
 * given byte offset as a binary string, and unmaps it.
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, readFromGPUTransferBuffer)
{
	zend_bool _0;
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *device_param = NULL, *transfer_buffer_param = NULL, *length_param = NULL, *offset_param = NULL;
	zend_long device, transfer_buffer, length, offset;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(transfer_buffer)
		Z_PARAM_LONG(length)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(offset)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 1, &device_param, &transfer_buffer_param, &length_param, &offset_param);
	if (!offset_param) {
		offset = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&result);
	_0 = length < 0;
	if (!(_0)) {
		_0 = offset < 0;
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "length and offset must be >= 0", "sdl3/sdl/gpu/sdlgpu.zep", 1408);
		return;
	}
	
            void *mapped = SDL_MapGPUTransferBuffer(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer,
                false
            );

            if (mapped != NULL && length > 0) {
                ZVAL_STRINGL(&result, (char *)((Uint8 *) mapped + (size_t) offset), (size_t) length);
            }
            if (mapped != NULL) {
                SDL_UnmapGPUTransferBuffer(
                    (SDL_GPUDevice *)(uintptr_t) device,
                    (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer
                );
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBeginGPUCopyPass)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *command_buffer_param = NULL, _0$$3, _1$$3, _2$$3;
	zend_long command_buffer, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(command_buffer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &command_buffer_param);
	
            SDL_GPUCopyPass *pass = SDL_BeginGPUCopyPass((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer);
            ptr = (zend_long)(uintptr_t) pass;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_BeginGPUCopyPass failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 1444);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

/**
 * source: ["transfer_buffer": int, "offset": int, "pixels_per_row": int, "rows_per_layer": int]
 * destination: ["texture": int, "mip_level": int, "layer": int, "x", "y", "z", "w", "h", "d"]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLUploadToGPUTexture)
{
	zend_bool cycle;
	zval *copy_pass_param = NULL, *source, source_sub, *destination, destination_sub, *cycle_param = NULL;
	zend_long copy_pass;

	ZVAL_UNDEF(&source_sub);
	ZVAL_UNDEF(&destination_sub);
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_LONG(copy_pass)
		Z_PARAM_ZVAL(source)
		Z_PARAM_ZVAL(destination)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(cycle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 1, &copy_pass_param, &source, &destination, &cycle_param);
	if (!cycle_param) {
		cycle = 0;
	} else {
		}
	
            SDL_GPUTextureTransferInfo src;
            SDL_GPUTextureRegion dst;

            php_sdl_gpu_texture_transfer_info(source, &src);
            php_sdl_gpu_texture_region(destination, &dst);

            SDL_UploadToGPUTexture((SDL_GPUCopyPass *)(uintptr_t) copy_pass, &src, &dst, cycle ? true : false);
        
}

/**
 * source: ["transfer_buffer": int, "offset": int]
 * destination: ["buffer": int, "offset": int, "size": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLUploadToGPUBuffer)
{
	zend_bool cycle;
	zval *copy_pass_param = NULL, *source, source_sub, *destination, destination_sub, *cycle_param = NULL;
	zend_long copy_pass;

	ZVAL_UNDEF(&source_sub);
	ZVAL_UNDEF(&destination_sub);
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_LONG(copy_pass)
		Z_PARAM_ZVAL(source)
		Z_PARAM_ZVAL(destination)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(cycle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 1, &copy_pass_param, &source, &destination, &cycle_param);
	if (!cycle_param) {
		cycle = 0;
	} else {
		}
	
            SDL_GPUTransferBufferLocation src;
            SDL_GPUBufferRegion dst;

            php_sdl_gpu_transfer_buffer_location(source, &src);
            php_sdl_gpu_buffer_region(destination, &dst);

            SDL_UploadToGPUBuffer((SDL_GPUCopyPass *)(uintptr_t) copy_pass, &src, &dst, cycle ? true : false);
        
}

/**
 * source/destination: ["texture": int, "mip_level": int, "layer": int, "x", "y", "z"]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCopyGPUTextureToTexture)
{
	zend_bool cycle;
	zval *copy_pass_param = NULL, *source, source_sub, *destination, destination_sub, *w_param = NULL, *h_param = NULL, *d_param = NULL, *cycle_param = NULL;
	zend_long copy_pass, w, h, d;

	ZVAL_UNDEF(&source_sub);
	ZVAL_UNDEF(&destination_sub);
	ZEND_PARSE_PARAMETERS_START(6, 7)
		Z_PARAM_LONG(copy_pass)
		Z_PARAM_ZVAL(source)
		Z_PARAM_ZVAL(destination)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(d)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(cycle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(6, 1, &copy_pass_param, &source, &destination, &w_param, &h_param, &d_param, &cycle_param);
	if (!cycle_param) {
		cycle = 0;
	} else {
		}
	
            SDL_GPUTextureLocation src;
            SDL_GPUTextureLocation dst;

            php_sdl_gpu_texture_location(source, &src);
            php_sdl_gpu_texture_location(destination, &dst);

            SDL_CopyGPUTextureToTexture(
                (SDL_GPUCopyPass *)(uintptr_t) copy_pass,
                &src, &dst,
                (Uint32) w, (Uint32) h, (Uint32) d,
                cycle ? true : false
            );
        
}

/**
 * source/destination: ["buffer": int, "offset": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCopyGPUBufferToBuffer)
{
	zend_bool cycle;
	zval *copy_pass_param = NULL, *source, source_sub, *destination, destination_sub, *size_param = NULL, *cycle_param = NULL;
	zend_long copy_pass, size;

	ZVAL_UNDEF(&source_sub);
	ZVAL_UNDEF(&destination_sub);
	ZEND_PARSE_PARAMETERS_START(4, 5)
		Z_PARAM_LONG(copy_pass)
		Z_PARAM_ZVAL(source)
		Z_PARAM_ZVAL(destination)
		Z_PARAM_LONG(size)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(cycle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 1, &copy_pass_param, &source, &destination, &size_param, &cycle_param);
	if (!cycle_param) {
		cycle = 0;
	} else {
		}
	
            SDL_GPUBufferLocation src;
            SDL_GPUBufferLocation dst;

            php_sdl_gpu_buffer_location(source, &src);
            php_sdl_gpu_buffer_location(destination, &dst);

            SDL_CopyGPUBufferToBuffer(
                (SDL_GPUCopyPass *)(uintptr_t) copy_pass,
                &src, &dst,
                (Uint32) size,
                cycle ? true : false
            );
        
}

/**
 * source: texture region, destination: texture transfer info.
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDownloadFromGPUTexture)
{
	zval *copy_pass_param = NULL, *source, source_sub, *destination, destination_sub;
	zend_long copy_pass;

	ZVAL_UNDEF(&source_sub);
	ZVAL_UNDEF(&destination_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(copy_pass)
		Z_PARAM_ZVAL(source)
		Z_PARAM_ZVAL(destination)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &copy_pass_param, &source, &destination);
	
            SDL_GPUTextureRegion src;
            SDL_GPUTextureTransferInfo dst;

            php_sdl_gpu_texture_region(source, &src);
            php_sdl_gpu_texture_transfer_info(destination, &dst);

            SDL_DownloadFromGPUTexture((SDL_GPUCopyPass *)(uintptr_t) copy_pass, &src, &dst);
        
}

/**
 * source: buffer region, destination: transfer buffer location.
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDownloadFromGPUBuffer)
{
	zval *copy_pass_param = NULL, *source, source_sub, *destination, destination_sub;
	zend_long copy_pass;

	ZVAL_UNDEF(&source_sub);
	ZVAL_UNDEF(&destination_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(copy_pass)
		Z_PARAM_ZVAL(source)
		Z_PARAM_ZVAL(destination)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &copy_pass_param, &source, &destination);
	
            SDL_GPUBufferRegion src;
            SDL_GPUTransferBufferLocation dst;

            php_sdl_gpu_buffer_region(source, &src);
            php_sdl_gpu_transfer_buffer_location(destination, &dst);

            SDL_DownloadFromGPUBuffer((SDL_GPUCopyPass *)(uintptr_t) copy_pass, &src, &dst);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLEndGPUCopyPass)
{
	zval *copy_pass_param = NULL;
	zend_long copy_pass;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(copy_pass)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &copy_pass_param);
	
            SDL_EndGPUCopyPass((SDL_GPUCopyPass *)(uintptr_t) copy_pass);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGenerateMipmapsForGPUTexture)
{
	zval *command_buffer_param = NULL, *texture_param = NULL;
	zend_long command_buffer, texture;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(command_buffer)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &command_buffer_param, &texture_param);
	
            SDL_GenerateMipmapsForGPUTexture((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer, (SDL_GPUTexture *)(uintptr_t) texture);
        
}

/**
 * info: ["source": blit region, "destination": blit region, "load_op": int,
 *  "clear_color": ["r","g","b","a"], "flip_mode": int, "filter": int, "cycle": bool]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLBlitGPUTexture)
{
	zval *command_buffer_param = NULL, *info, info_sub;
	zend_long command_buffer;

	ZVAL_UNDEF(&info_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(command_buffer)
		Z_PARAM_ZVAL(info)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &command_buffer_param, &info);
	
            SDL_GPUBlitInfo bi;
            zval *src = php_sdl_gpu_field(info, "source");
            zval *dst = php_sdl_gpu_field(info, "destination");
            zval *cc = php_sdl_gpu_field(info, "clear_color");

            SDL_zero(bi);
            if (src != NULL) {
                php_sdl_gpu_blit_region(src, &bi.source);
            }
            if (dst != NULL) {
                php_sdl_gpu_blit_region(dst, &bi.destination);
            }
            bi.load_op = (SDL_GPULoadOp) php_sdl_gpu_long(info, "load_op", 0);
            if (cc != NULL) {
                php_sdl_gpu_fcolor(cc, &bi.clear_color);
            }
            bi.flip_mode = (SDL_FlipMode) php_sdl_gpu_long(info, "flip_mode", 0);
            bi.filter = (SDL_GPUFilter) php_sdl_gpu_long(info, "filter", 0);
            bi.cycle = php_sdl_gpu_bool(info, "cycle", false);

            SDL_BlitGPUTexture((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer, &bi);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLWindowSupportsGPUSwapchainComposition)
{
	zend_bool result = 0;
	zval *device_param = NULL, *window_param = NULL, *swapchain_composition_param = NULL;
	zend_long device, window, swapchain_composition;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(swapchain_composition)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &device_param, &window_param, &swapchain_composition_param);
	
            result = SDL_WindowSupportsGPUSwapchainComposition(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_Window *)(uintptr_t) window,
                (SDL_GPUSwapchainComposition) swapchain_composition
            );
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLWindowSupportsGPUPresentMode)
{
	zend_bool result = 0;
	zval *device_param = NULL, *window_param = NULL, *present_mode_param = NULL;
	zend_long device, window, present_mode;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(present_mode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &device_param, &window_param, &present_mode_param);
	
            result = SDL_WindowSupportsGPUPresentMode(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_Window *)(uintptr_t) window,
                (SDL_GPUPresentMode) present_mode
            );
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLClaimWindowForGPUDevice)
{
	zend_bool result = 0;
	zval *device_param = NULL, *window_param = NULL;
	zend_long device, window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &window_param);
	
            result = SDL_ClaimWindowForGPUDevice((SDL_GPUDevice *)(uintptr_t) device, (SDL_Window *)(uintptr_t) window);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseWindowFromGPUDevice)
{
	zval *device_param = NULL, *window_param = NULL;
	zend_long device, window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &window_param);
	
            SDL_ReleaseWindowFromGPUDevice((SDL_GPUDevice *)(uintptr_t) device, (SDL_Window *)(uintptr_t) window);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUSwapchainParameters)
{
	zend_bool result = 0;
	zval *device_param = NULL, *window_param = NULL, *swapchain_composition_param = NULL, *present_mode_param = NULL;
	zend_long device, window, swapchain_composition, present_mode;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(swapchain_composition)
		Z_PARAM_LONG(present_mode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &device_param, &window_param, &swapchain_composition_param, &present_mode_param);
	
            result = SDL_SetGPUSwapchainParameters(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_Window *)(uintptr_t) window,
                (SDL_GPUSwapchainComposition) swapchain_composition,
                (SDL_GPUPresentMode) present_mode
            );
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPUAllowedFramesInFlight)
{
	zend_bool result = 0;
	zval *device_param = NULL, *allowed_frames_in_flight_param = NULL;
	zend_long device, allowed_frames_in_flight;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(allowed_frames_in_flight)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &allowed_frames_in_flight_param);
	
            result = SDL_SetGPUAllowedFramesInFlight((SDL_GPUDevice *)(uintptr_t) device, (Uint32) allowed_frames_in_flight);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUSwapchainTextureFormat)
{
	zval *device_param = NULL, *window_param = NULL;
	zend_long device, window, result = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &window_param);
	
            result = (zend_long) SDL_GetGPUSwapchainTextureFormat((SDL_GPUDevice *)(uintptr_t) device, (SDL_Window *)(uintptr_t) window);
        
	RETURN_LONG(result);
}

/**
 * Returns ["texture": int, "width": int, "height": int]; "texture" is 0
 * when the swapchain is not ready (too many frames in flight).
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLAcquireGPUSwapchainTexture)
{
	zend_bool ok = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *command_buffer_param = NULL, *window_param = NULL, _3, _0$$3, _1$$3, _2$$3;
	zend_long command_buffer, window, ZEPHIR_LAST_CALL_STATUS, tex_ptr, tex_w, tex_h;

	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(command_buffer)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &command_buffer_param, &window_param);
	tex_ptr = 0;
	tex_w = 0;
	tex_h = 0;
	
            SDL_GPUTexture *texture = NULL;
            Uint32 w = 0, h = 0;

            ok = SDL_AcquireGPUSwapchainTexture(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                (SDL_Window *)(uintptr_t) window,
                &texture, &w, &h
            );
            tex_ptr = (zend_long)(uintptr_t) texture;
            tex_w = (zend_long) w;
            tex_h = (zend_long) h;
        
	if (!(ok)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_AcquireGPUSwapchainTexture failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 1717);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_create_array(return_value, 3, 0);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_LONG(&_3, tex_ptr);
	zephir_array_update_string(return_value, SL("texture"), &_3, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_LONG(&_3, tex_w);
	zephir_array_update_string(return_value, SL("width"), &_3, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_LONG(&_3, tex_h);
	zephir_array_update_string(return_value, SL("height"), &_3, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLWaitForGPUSwapchain)
{
	zend_bool result = 0;
	zval *device_param = NULL, *window_param = NULL;
	zend_long device, window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &window_param);
	
            result = SDL_WaitForGPUSwapchain((SDL_GPUDevice *)(uintptr_t) device, (SDL_Window *)(uintptr_t) window);
        
	RETURN_BOOL(result);
}

/**
 * Returns ["texture": int, "width": int, "height": int].
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLWaitAndAcquireGPUSwapchainTexture)
{
	zend_bool ok = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *command_buffer_param = NULL, *window_param = NULL, _3, _0$$3, _1$$3, _2$$3;
	zend_long command_buffer, window, ZEPHIR_LAST_CALL_STATUS, tex_ptr, tex_w, tex_h;

	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(command_buffer)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &command_buffer_param, &window_param);
	tex_ptr = 0;
	tex_w = 0;
	tex_h = 0;
	
            SDL_GPUTexture *texture = NULL;
            Uint32 w = 0, h = 0;

            ok = SDL_WaitAndAcquireGPUSwapchainTexture(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                (SDL_Window *)(uintptr_t) window,
                &texture, &w, &h
            );
            tex_ptr = (zend_long)(uintptr_t) texture;
            tex_w = (zend_long) w;
            tex_h = (zend_long) h;
        
	if (!(ok)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_WaitAndAcquireGPUSwapchainTexture failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 1759);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_create_array(return_value, 3, 0);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_LONG(&_3, tex_ptr);
	zephir_array_update_string(return_value, SL("texture"), &_3, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_LONG(&_3, tex_w);
	zephir_array_update_string(return_value, SL("width"), &_3, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_LONG(&_3, tex_h);
	zephir_array_update_string(return_value, SL("height"), &_3, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSubmitGPUCommandBuffer)
{
	zend_bool result = 0;
	zval *command_buffer_param = NULL;
	zend_long command_buffer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(command_buffer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &command_buffer_param);
	
            result = SDL_SubmitGPUCommandBuffer((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSubmitGPUCommandBufferAndAcquireFence)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *command_buffer_param = NULL, _0$$3, _1$$3, _2$$3;
	zend_long command_buffer, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(command_buffer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &command_buffer_param);
	
            SDL_GPUFence *fence = SDL_SubmitGPUCommandBufferAndAcquireFence((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer);
            ptr = (zend_long)(uintptr_t) fence;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_SubmitGPUCommandBufferAndAcquireFence failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 1788);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCancelGPUCommandBuffer)
{
	zend_bool result = 0;
	zval *command_buffer_param = NULL;
	zend_long command_buffer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(command_buffer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &command_buffer_param);
	
            result = SDL_CancelGPUCommandBuffer((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLWaitForGPUIdle)
{
	zend_bool result = 0;
	zval *device_param = NULL;
	zend_long device;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(device)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &device_param);
	
            result = SDL_WaitForGPUIdle((SDL_GPUDevice *)(uintptr_t) device);
        
	RETURN_BOOL(result);
}

/**
 * fences: array of int fence handles
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLWaitForGPUFences)
{
	zend_bool wait_all, result = 0;
	zval *device_param = NULL, *wait_all_param = NULL, *fences, fences_sub;
	zend_long device;

	ZVAL_UNDEF(&fences_sub);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(device)
		Z_PARAM_BOOL(wait_all)
		Z_PARAM_ZVAL(fences)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &device_param, &wait_all_param, &fences);
	
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(fences, &n);

            result = SDL_WaitForGPUFences(
                (SDL_GPUDevice *)(uintptr_t) device,
                wait_all ? true : false,
                (SDL_GPUFence *const *) items,
                n
            );

            if (items != NULL) { efree(items); }
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLQueryGPUFence)
{
	zend_bool result = 0;
	zval *device_param = NULL, *fence_param = NULL;
	zend_long device, fence;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(fence)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &fence_param);
	
            result = SDL_QueryGPUFence((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUFence *)(uintptr_t) fence);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLReleaseGPUFence)
{
	zval *device_param = NULL, *fence_param = NULL;
	zend_long device, fence;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(fence)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &device_param, &fence_param);
	
            SDL_ReleaseGPUFence((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUFence *)(uintptr_t) fence);
        
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGPUTextureFormatTexelBlockSize)
{
	zval *format_param = NULL;
	zend_long format, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &format_param);
	
            result = (zend_long) SDL_GPUTextureFormatTexelBlockSize((SDL_GPUTextureFormat) format);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGPUTextureSupportsFormat)
{
	zend_bool result = 0;
	zval *device_param = NULL, *format_param = NULL, *type_param = NULL, *usage_param = NULL;
	zend_long device, format, type, usage;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(format)
		Z_PARAM_LONG(type)
		Z_PARAM_LONG(usage)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &device_param, &format_param, &type_param, &usage_param);
	
            result = SDL_GPUTextureSupportsFormat(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_GPUTextureFormat) format,
                (SDL_GPUTextureType) type,
                (SDL_GPUTextureUsageFlags) usage
            );
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGPUTextureSupportsSampleCount)
{
	zend_bool result = 0;
	zval *device_param = NULL, *format_param = NULL, *sample_count_param = NULL;
	zend_long device, format, sample_count;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(format)
		Z_PARAM_LONG(sample_count)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &device_param, &format_param, &sample_count_param);
	
            result = SDL_GPUTextureSupportsSampleCount(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_GPUTextureFormat) format,
                (SDL_GPUSampleCount) sample_count
            );
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCalculateGPUTextureFormatSize)
{
	zval *format_param = NULL, *width_param = NULL, *height_param = NULL, *depth_or_layer_count_param = NULL;
	zend_long format, width, height, depth_or_layer_count, result = 0;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(format)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(depth_or_layer_count)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &format_param, &width_param, &height_param, &depth_or_layer_count_param);
	
            result = (zend_long) SDL_CalculateGPUTextureFormatSize(
                (SDL_GPUTextureFormat) format,
                (Uint32) width, (Uint32) height, (Uint32) depth_or_layer_count
            );
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetPixelFormatFromGPUTextureFormat)
{
	zval *format_param = NULL;
	zend_long format, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &format_param);
	
            result = (zend_long) SDL_GetPixelFormatFromGPUTextureFormat((SDL_GPUTextureFormat) format);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPUTextureFormatFromPixelFormat)
{
	zval *format_param = NULL;
	zend_long format, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &format_param);
	
            result = (zend_long) SDL_GetGPUTextureFormatFromPixelFormat((SDL_PixelFormat) format);
        
	RETURN_LONG(result);
}

/**
 * Only functional on GDK (Xbox) builds; throws elsewhere.
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGDKSuspendGPU)
{
	zend_bool supported;
	zval *device_param = NULL;
	zend_long device;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(device)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &device_param);
	supported = 0;
	
#ifdef SDL_PLATFORM_GDK
            SDL_GDKSuspendGPU((SDL_GPUDevice *)(uintptr_t) device);
            supported = true;
#else
            (void) device;
#endif
        
	if (!(supported)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "SDL_GDKSuspendGPU is only available on the GDK (Xbox) platform", "sdl3/sdl/gpu/sdlgpu.zep", 1957);
		return;
	}
}

/**
 * Only functional on GDK (Xbox) builds; throws elsewhere.
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGDKResumeGPU)
{
	zend_bool supported;
	zval *device_param = NULL;
	zend_long device;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(device)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &device_param);
	supported = 0;
	
#ifdef SDL_PLATFORM_GDK
            SDL_GDKResumeGPU((SDL_GPUDevice *)(uintptr_t) device);
            supported = true;
#else
            (void) device;
#endif
        
	if (!(supported)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "SDL_GDKResumeGPU is only available on the GDK (Xbox) platform", "sdl3/sdl/gpu/sdlgpu.zep", 1978);
		return;
	}
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPURenderer)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *device_param = NULL, *window_param = NULL, _0$$3, _1$$3, _2$$3;
	zend_long device, window, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &device_param, &window_param);
	
            SDL_Renderer *renderer = SDL_CreateGPURenderer((SDL_GPUDevice *)(uintptr_t) device, (SDL_Window *)(uintptr_t) window);
            ptr = (zend_long)(uintptr_t) renderer;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateGPURenderer failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 1994);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLGetGPURendererDevice)
{
	zval *renderer_param = NULL;
	zend_long renderer, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &renderer_param);
	
            SDL_GPUDevice *device = SDL_GetGPURendererDevice((SDL_Renderer *)(uintptr_t) renderer);
            ptr = (zend_long)(uintptr_t) device;
        
	RETURN_LONG(ptr);
}

/**
 * createinfo: ["fragment_shader": int,
 *  "sampler_bindings": array of ["texture": int, "sampler": int],
 *  "storage_textures": array of int, "storage_buffers": array of int,
 *  "props": int]
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLCreateGPURenderState)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, *createinfo, createinfo_sub, _0$$3, _1$$3, _2$$3;
	zend_long renderer, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&createinfo_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_ZVAL(createinfo)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &renderer_param, &createinfo);
	
            SDL_GPURenderStateCreateInfo ci;
            SDL_GPUTextureSamplerBinding *samplers = NULL;
            void **stex = NULL;
            void **sbuf = NULL;
            zval *sb_arr = php_sdl_gpu_field(createinfo, "sampler_bindings");
            Uint32 nsb = php_sdl_gpu_count(sb_arr);
            Uint32 ntex = 0;
            Uint32 nbuf = 0;
            Uint32 i = 0;
            zval *el;

            SDL_zero(ci);
            ci.fragment_shader = (SDL_GPUShader *) php_sdl_gpu_handle(createinfo, "fragment_shader");
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            if (nsb > 0) {
                samplers = (SDL_GPUTextureSamplerBinding *) emalloc(sizeof(*samplers) * nsb);
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(sb_arr), el) {
                    php_sdl_gpu_texture_sampler_binding(el, &samplers[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }
            ci.num_sampler_bindings = (Sint32) nsb;
            ci.sampler_bindings = samplers;

            stex = php_sdl_gpu_handle_list(php_sdl_gpu_field(createinfo, "storage_textures"), &ntex);
            ci.num_storage_textures = (Sint32) ntex;
            ci.storage_textures = (SDL_GPUTexture *const *) stex;

            sbuf = php_sdl_gpu_handle_list(php_sdl_gpu_field(createinfo, "storage_buffers"), &nbuf);
            ci.num_storage_buffers = (Sint32) nbuf;
            ci.storage_buffers = (SDL_GPUBuffer *const *) sbuf;

            SDL_GPURenderState *state = SDL_CreateGPURenderState((SDL_Renderer *)(uintptr_t) renderer, &ci);
            ptr = (zend_long)(uintptr_t) state;

            if (samplers != NULL) { efree(samplers); }
            if (stex != NULL) { efree(stex); }
            if (sbuf != NULL) { efree(sbuf); }
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateGPURenderState failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/gpu/sdlgpu.zep", 2065);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPURenderStateFragmentUniforms)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval data;
	zval *state_param = NULL, *slot_index_param = NULL, *data_param = NULL;
	zend_long state, slot_index;

	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(state)
		Z_PARAM_LONG(slot_index)
		Z_PARAM_STR(data)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &state_param, &slot_index_param, &data_param);
	zephir_get_strval(&data, data_param);
	
            result = SDL_SetGPURenderStateFragmentUniforms(
                (SDL_GPURenderState *)(uintptr_t) state,
                (Uint32) slot_index,
                (const void *) Z_STRVAL(data),
                (Uint32) Z_STRLEN(data)
            );
        
	RETURN_MM_BOOL(result);
}

/**
 * Pass state = 0 to clear the current render state.
 */
PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLSetGPURenderState)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *state_param = NULL;
	zend_long renderer, state;

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(state)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &renderer_param, &state_param);
	if (!state_param) {
		state = 0;
	} else {
		}
	
            result = SDL_SetGPURenderState((SDL_Renderer *)(uintptr_t) renderer, (SDL_GPURenderState *)(uintptr_t) state);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Gpu_SDLGPU, SDLDestroyGPURenderState)
{
	zval *state_param = NULL;
	zend_long state;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(state)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &state_param);
	
            SDL_DestroyGPURenderState((SDL_GPURenderState *)(uintptr_t) state);
        
}

