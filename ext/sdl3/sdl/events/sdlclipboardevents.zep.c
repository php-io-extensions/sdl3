
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



ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLClipboardEvents)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Events, SDLClipboardEvents, sdl3, sdl_events_sdlclipboardevents, sdl3_sdl_events_sdlclipboardevents_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Events_SDLClipboardEvents, SDLReadClipboardEvent)
{
	zval result;
	zval *ptr_param = NULL;
	zend_long ptr;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(ptr)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ptr_param);
	
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_ClipboardEvent *cev = &event->clipboard;

            array_init(&result);
            add_assoc_long(&result, "type",           (zend_long) cev->type);
            add_assoc_long(&result, "timestamp",      (zend_long) cev->timestamp);
            add_assoc_long(&result, "owner",          (zend_long) cev->owner);
            add_assoc_long(&result, "num_mime_types", (zend_long) cev->num_mime_types);

            if (cev->num_mime_types > 0 && cev->mime_types != NULL) {
                zval mime_array;
                array_init(&mime_array);
                for (int i = 0; i < (int) cev->num_mime_types; i++) {
                    if (cev->mime_types[i] != NULL) {
                        add_next_index_string(&mime_array, cev->mime_types[i]);
                    }
                }
                add_assoc_zval(&result, "mime_types", &mime_array);
            } else {
                zval empty_array;
                array_init(&empty_array);
                add_assoc_zval(&result, "mime_types", &empty_array);
            }

            efree(event);
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLClipboardEvents, SDLSetClipboardText)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *text_param = NULL;
	zval text;

	ZVAL_UNDEF(&text);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(text)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &text_param);
	zephir_get_strval(&text, text_param);
	
            result = SDL_SetClipboardText((const char *) Z_STRVAL(text));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLClipboardEvents, SDLGetClipboardText)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&result);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&result);
	
            const char *text = SDL_GetClipboardText();
            if (text) {
                ZVAL_STRING(&result, text);
                SDL_free((void *) text);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLClipboardEvents, SDLHasClipboardText)
{
	zend_bool result = 0;
	
            result = SDL_HasClipboardText();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLClipboardEvents, SDLSetPrimarySelectionText)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *text_param = NULL;
	zval text;

	ZVAL_UNDEF(&text);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(text)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &text_param);
	zephir_get_strval(&text, text_param);
	
            result = SDL_SetPrimarySelectionText((const char *) Z_STRVAL(text));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLClipboardEvents, SDLGetPrimarySelectionText)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&result);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&result);
	
            const char *text = SDL_GetPrimarySelectionText();
            if (text) {
                ZVAL_STRING(&result, text);
                SDL_free((void *) text);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLClipboardEvents, SDLHasPrimarySelectionText)
{
	zend_bool result = 0;
	
            result = SDL_HasPrimarySelectionText();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLClipboardEvents, SDLGetClipboardMimeTypes)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            const char **mime_types = SDL_GetClipboardMimeTypes(NULL);

            array_init(&result);
            if (mime_types != NULL) {
                for (int i = 0; mime_types[i] != NULL; i++) {
                    add_next_index_string(&result, mime_types[i]);
                }
                SDL_free(mime_types);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLClipboardEvents, SDLHasClipboardData)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *mime_type_param = NULL;
	zval mime_type;

	ZVAL_UNDEF(&mime_type);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(mime_type)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &mime_type_param);
	zephir_get_strval(&mime_type, mime_type_param);
	
            result = SDL_HasClipboardData((const char *) Z_STRVAL(mime_type));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLClipboardEvents, SDLClearClipboardData)
{

	
            SDL_ClearClipboardData();
        
}

