
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"

#include <SDL3/SDL.h>
#include <stdio.h>



ZEPHIR_INIT_CLASS(Sdl3_SDL_SDLError)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL, SDLError, sdl3, sdl_sdlerror, sdl3_sdl_sdlerror_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_SDLError, SDLGetError)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            ZVAL_STRING(&result, SDL_GetError());
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_SDLError, SDLSetError)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *message_param = NULL;
	zval message;

	ZVAL_UNDEF(&message);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(message)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &message_param);
	zephir_get_strval(&message, message_param);
	
            result = SDL_SetError("%s", Z_STRVAL(message));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDLError, SDLOutOfMemory)
{
	zend_bool result = 0;
	
            result = SDL_OutOfMemory();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDLError, SDLClearError)
{
	zend_bool result = 0;
	
            result = SDL_ClearError();
        
	RETURN_BOOL(result);
}

