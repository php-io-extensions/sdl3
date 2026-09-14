
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/operators.h"
#include "kernel/object.h"

#include <SDL3/SDL.h>



/**
 * SDL_metal.h: a CAMetalLayer-backed view on an SDL window. The layer
 * crosses as raw pointer bits — the only currency between extensions.
 * Compiles everywhere; on a non-Apple box CreateView fails and throws.
 */
ZEPHIR_INIT_CLASS(Sdl3_SDL_Video_SDLMetal)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Video, SDLMetal, sdl3, sdl_video_sdlmetal, sdl3_sdl_video_sdlmetal_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Video_SDLMetal, SDLMetalCreateView)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0$$3, _1$$3, _2$$3;
	zend_long window, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            SDL_MetalView view = SDL_Metal_CreateView((SDL_Window *)(uintptr_t) window);
            ptr = (zend_long)(uintptr_t) view;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_Metal_CreateView failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/video/sdlmetal.zep", 23);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLMetal, SDLMetalDestroyView)
{
	zval *view_param = NULL;
	zend_long view;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(view)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &view_param);
	
            SDL_Metal_DestroyView((SDL_MetalView)(uintptr_t) view);
        
}

PHP_METHOD(Sdl3_SDL_Video_SDLMetal, SDLMetalGetLayer)
{
	zval *view_param = NULL;
	zend_long view, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(view)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &view_param);
	
            void *layer = SDL_Metal_GetLayer((SDL_MetalView)(uintptr_t) view);
            ptr = (zend_long)(uintptr_t) layer;
        
	RETURN_LONG(ptr);
}

