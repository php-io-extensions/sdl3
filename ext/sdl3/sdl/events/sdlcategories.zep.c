
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

#include <SDL3/SDL.h>
#include <stdio.h>



ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLCategories)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Events, SDLCategories, sdl3, sdl_events_sdlcategories, sdl3_sdl_events_sdlcategories_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Events_SDLCategories, SDLSetEventEnabled)
{
	zend_bool enabled;
	zval *type_param = NULL, *enabled_param = NULL;
	zend_long type;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(type)
		Z_PARAM_BOOL(enabled)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &type_param, &enabled_param);
	
            SDL_SetEventEnabled((Uint32) type, (bool) enabled);
        
}

PHP_METHOD(Sdl3_SDL_Events_SDLCategories, SDLEventEnabled)
{
	zend_bool result = 0;
	zval *type_param = NULL;
	zend_long type;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(type)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &type_param);
	
            result = SDL_EventEnabled((Uint32) type);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLCategories, SDLRegisterEvents)
{
	zval *numevents_param = NULL;
	zend_long numevents, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(numevents)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &numevents_param);
	
            result = (zend_long) SDL_RegisterEvents((int) numevents);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLCategories, SDLGetWindowFromEvent)
{
	zval *event_ptr_param = NULL;
	zend_long event_ptr, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(event_ptr)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &event_ptr_param);
	
            SDL_Event *event = (SDL_Event *)(uintptr_t) event_ptr;
            SDL_Window *window = SDL_GetWindowFromEvent((const SDL_Event *) event);
            result = (zend_long) (uintptr_t) window;
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLCategories, SDLGetEventDescription)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *event_ptr_param = NULL, *buflen_param = NULL;
	zend_long event_ptr, buflen;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(event_ptr)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(buflen)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &event_ptr_param, &buflen_param);
	if (!buflen_param) {
		buflen = 256;
	} else {
		}
	ZEPHIR_INIT_VAR(&result);
	
            int len = (int) buflen;

            if (len > 0) {
                char *buf = emalloc((size_t) len);
                if (buf != NULL) {
#if SDL_VERSION_ATLEAST(3, 4, 0)
                    SDL_Event *event = (SDL_Event *)(uintptr_t) event_ptr;
                    SDL_GetEventDescription((const SDL_Event *) event, buf, len);
                    ZVAL_STRING(&result, buf);
#else
                    snprintf(buf, (size_t) len, "SDL_GetEventDescription unavailable: SDL < 3.4.0");
                    ZVAL_STRING(&result, buf);
#endif
                    efree(buf);
                }
            }
        
	RETURN_CTOR(&result);
}

