
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



ZEPHIR_INIT_CLASS(Sdl3_SDL_Timer_SDLTimer)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Timer, SDLTimer, sdl3, sdl_timer_sdltimer, sdl3_sdl_timer_sdltimer_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Timer_SDLTimer, SDLDelay)
{
	zval *ms_param = NULL;
	zend_long ms;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(ms)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ms_param);
	
            SDL_Delay((Uint32) ms);
        
}

PHP_METHOD(Sdl3_SDL_Timer_SDLTimer, SDLGetTicks)
{
	zend_long result = 0;
	
            result = (zend_long) SDL_GetTicks();
        
	RETURN_LONG(result);
}

