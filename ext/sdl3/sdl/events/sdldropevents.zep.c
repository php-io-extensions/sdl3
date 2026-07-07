
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



/**
 * Drag-and-drop event payload (event.drop.*). Agent boundary: only SDL_DropEvent decoding here.
 */
ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLDropEvents)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Events, SDLDropEvents, sdl3, sdl_events_sdldropevents, sdl3_sdl_events_sdldropevents_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Events_SDLDropEvents, SDLReadDropEvent)
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
            SDL_DropEvent *dev = &event->drop;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) dev->type);
            add_assoc_long(&result, "timestamp", (zend_long) dev->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) dev->windowID);
            add_assoc_double(&result, "x", (double) dev->x);
            add_assoc_double(&result, "y", (double) dev->y);
            add_assoc_string(&result, "source", dev->source ? dev->source : "");
            add_assoc_string(&result, "data", dev->data ? dev->data : "");

            efree(event);
        
	RETURN_CTORW(&result);
}

