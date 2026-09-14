
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



/**
 * Window event payload (SDL_EVENT_WINDOW_*). Agent boundary: only
 * SDL_WindowEvent decoding here. Like every SDLReadEvent reader, it frees
 * the event it decodes.
 */
ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLWindowEvents)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Events, SDLWindowEvents, sdl3, sdl_events_sdlwindowevents, sdl3_sdl_events_sdlwindowevents_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Events_SDLWindowEvents, SDLReadWindowEvent)
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
            SDL_WindowEvent *wev = &event->window;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) wev->type);
            add_assoc_long(&result, "timestamp", (zend_long) wev->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) wev->windowID);
            add_assoc_long(&result, "data1", (zend_long) wev->data1);
            add_assoc_long(&result, "data2", (zend_long) wev->data2);

            efree(event);
        
	RETURN_CTORW(&result);
}

