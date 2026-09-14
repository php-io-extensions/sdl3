
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
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/object.h"
#include "kernel/operators.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>



/**
 * SDL_vulkan.h. Every Vulkan handle crosses as raw pointer bits in an int
 * (0 = VK_NULL_HANDLE), the ext-vulkan currency. CreateSurface collapses
 * SDL's bool + out-param into the surface bits, 0 on failure — read
 * SDLError::SDLGetError() for the reason.
 */
ZEPHIR_INIT_CLASS(Sdl3_SDL_Video_SDLVulkan)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Video, SDLVulkan, sdl3, sdl_video_sdlvulkan, sdl3_sdl_video_sdlvulkan_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanLoadLibrary)
{
	zend_bool result = 0, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *path = NULL, path_sub, __$null, p, _1$$3, _2$$3, _3$$3;

	ZVAL_UNDEF(&path_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&p);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &path);
	if (!path) {
		path = &path_sub;
		path = &__$null;
	}
	_0 = Z_TYPE_P(path) != IS_NULL;
	if (_0) {
		_0 = Z_TYPE_P(path) != IS_STRING;
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, zend_ce_type_error);
		ZEPHIR_INIT_VAR(&_2$$3);
		zephir_gettype(&_2$$3, path);
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SV(&_3$$3, "SDLVulkanLoadLibrary() expects ?string $path, got ", &_2$$3);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 2, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "sdl3/sdl/video/sdlvulkan.zep", 21);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&p, path);
	
            const char *libpath = (Z_TYPE_P(&p) == IS_NULL) ? NULL : Z_STRVAL(p);
            result = SDL_Vulkan_LoadLibrary(libpath);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanUnloadLibrary)
{

	
            SDL_Vulkan_UnloadLibrary();
        
}

PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanGetVkGetInstanceProcAddr)
{
	zend_long ptr = 0;
	
            SDL_FunctionPointer fn = SDL_Vulkan_GetVkGetInstanceProcAddr();
            ptr = (zend_long)(uintptr_t) fn;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanGetInstanceExtensions)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            Uint32 count = 0;
            char const * const *names = SDL_Vulkan_GetInstanceExtensions(&count);

            array_init(&result);
            if (names != NULL) {
                for (Uint32 i = 0; i < count; i++) {
                    add_next_index_string(&result, names[i]);
                }
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanCreateSurface)
{
	zval *window_param = NULL, *instance_param = NULL, *allocator_param = NULL;
	zend_long window, instance, allocator, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(instance)
		Z_PARAM_LONG(allocator)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &window_param, &instance_param, &allocator_param);
	
            VkSurfaceKHR surface = 0;
            bool ok = SDL_Vulkan_CreateSurface(
                (SDL_Window *)(uintptr_t) window,
                (VkInstance)(uintptr_t) instance,
                (const struct VkAllocationCallbacks *)(uintptr_t) allocator,
                &surface
            );
            ptr = ok ? (zend_long)(uintptr_t) surface : 0;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanDestroySurface)
{
	zval *instance_param = NULL, *surface_param = NULL, *allocator_param = NULL;
	zend_long instance, surface, allocator;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(instance)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(allocator)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &instance_param, &surface_param, &allocator_param);
	
            SDL_Vulkan_DestroySurface(
                (VkInstance)(uintptr_t) instance,
                (VkSurfaceKHR)(uintptr_t) surface,
                (const struct VkAllocationCallbacks *)(uintptr_t) allocator
            );
        
}

PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanGetPresentationSupport)
{
	zend_bool result = 0;
	zval *instance_param = NULL, *physical_device_param = NULL, *queue_family_index_param = NULL;
	zend_long instance, physical_device, queue_family_index;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(instance)
		Z_PARAM_LONG(physical_device)
		Z_PARAM_LONG(queue_family_index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &instance_param, &physical_device_param, &queue_family_index_param);
	
            result = SDL_Vulkan_GetPresentationSupport(
                (VkInstance)(uintptr_t) instance,
                (VkPhysicalDevice)(uintptr_t) physical_device,
                (Uint32) queue_family_index
            );
        
	RETURN_BOOL(result);
}

