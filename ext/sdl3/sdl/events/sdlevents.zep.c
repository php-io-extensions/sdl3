
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
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/concat.h"
#include "kernel/object.h"
#include "kernel/array.h"

#include <SDL3/SDL.h>
#include <stdio.h>



ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLEvents)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Events, SDLEvents, sdl3, sdl_events_sdlevents, sdl3_sdl_events_sdlevents_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLReadEvent)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval key, _13$$15;
	zval *ptr_param = NULL, *key_param = NULL, result, _0$$3, _1$$4, _2$$5, _3$$6, _4$$7, _5$$8, _6$$9, _7$$10, _8$$11, _9$$12, _10$$13, _11$$14, _12$$15;
	zend_long ptr, ZEPHIR_LAST_CALL_STATUS;

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_5$$8);
	ZVAL_UNDEF(&_6$$9);
	ZVAL_UNDEF(&_7$$10);
	ZVAL_UNDEF(&_8$$11);
	ZVAL_UNDEF(&_9$$12);
	ZVAL_UNDEF(&_10$$13);
	ZVAL_UNDEF(&_11$$14);
	ZVAL_UNDEF(&_12$$15);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_13$$15);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(ptr)
		Z_PARAM_STR(key)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &ptr_param, &key_param);
	zephir_get_strval(&key, key_param);
	do {
		if (ZEPHIR_IS_STRING(&key, "key")) {
			ZVAL_LONG(&_0$$3, ptr);
			ZEPHIR_CALL_CE_STATIC(&result, sdl3_sdl_events_sdlkeyboard_ce, "sdlreadkeyboardevent", NULL, 0, &_0$$3);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_STRING(&key, "text")) {
			ZVAL_LONG(&_1$$4, ptr);
			ZEPHIR_CALL_CE_STATIC(&result, sdl3_sdl_events_sdlkeyboard_ce, "sdlreadtextinputevent", NULL, 0, &_1$$4);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_STRING(&key, "edit")) {
			ZVAL_LONG(&_2$$5, ptr);
			ZEPHIR_CALL_CE_STATIC(&result, sdl3_sdl_events_sdlkeyboard_ce, "sdlreadtexteditingevent", NULL, 0, &_2$$5);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_STRING(&key, "edit_candidates")) {
			ZVAL_LONG(&_3$$6, ptr);
			ZEPHIR_CALL_CE_STATIC(&result, sdl3_sdl_events_sdlkeyboard_ce, "sdlreadtexteditingcandidatesevent", NULL, 0, &_3$$6);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_STRING(&key, "kdevice")) {
			ZVAL_LONG(&_4$$7, ptr);
			ZEPHIR_CALL_CE_STATIC(&result, sdl3_sdl_events_sdlkeyboard_ce, "sdlreadkeyboarddeviceevent", NULL, 0, &_4$$7);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_STRING(&key, "display")) {
			ZVAL_LONG(&_5$$8, ptr);
			ZEPHIR_CALL_CE_STATIC(&result, sdl3_sdl_events_sdldisplayevents_ce, "sdlreaddisplayevent", NULL, 0, &_5$$8);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_STRING(&key, "quit")) {
			ZVAL_LONG(&_6$$9, ptr);
			ZEPHIR_CALL_CE_STATIC(&result, sdl3_sdl_events_sdlquit_ce, "sdlreadquitevent", NULL, 0, &_6$$9);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_STRING(&key, "drop")) {
			ZVAL_LONG(&_7$$10, ptr);
			ZEPHIR_CALL_CE_STATIC(&result, sdl3_sdl_events_sdldropevents_ce, "sdlreaddropevent", NULL, 0, &_7$$10);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_STRING(&key, "mdevice")) {
			ZVAL_LONG(&_8$$11, ptr);
			ZEPHIR_CALL_CE_STATIC(&result, sdl3_sdl_events_sdlmouse_ce, "sdlreadmousedeviceevent", NULL, 0, &_8$$11);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_STRING(&key, "motion")) {
			ZVAL_LONG(&_9$$12, ptr);
			ZEPHIR_CALL_CE_STATIC(&result, sdl3_sdl_events_sdlmouse_ce, "sdlreadmousemotionevent", NULL, 0, &_9$$12);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_STRING(&key, "button")) {
			ZVAL_LONG(&_10$$13, ptr);
			ZEPHIR_CALL_CE_STATIC(&result, sdl3_sdl_events_sdlmouse_ce, "sdlreadmousebuttonevent", NULL, 0, &_10$$13);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_STRING(&key, "wheel")) {
			ZVAL_LONG(&_11$$14, ptr);
			ZEPHIR_CALL_CE_STATIC(&result, sdl3_sdl_events_sdlmouse_ce, "sdlreadmousewheelevent", NULL, 0, &_11$$14);
			zephir_check_call_status();
			break;
		}
		
                    efree((SDL_Event *)(uintptr_t) ptr);
                
		ZEPHIR_INIT_VAR(&_12$$15);
		object_init_ex(&_12$$15, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(&_13$$15);
		ZEPHIR_CONCAT_SVS(&_13$$15, "SDL event property '", &key, "' is not supported yet");
		ZEPHIR_CALL_METHOD(NULL, &_12$$15, "__construct", NULL, 1, &_13$$15);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_12$$15, "sdl3/sdl/events/sdlevents.zep", 55);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	RETURN_CCTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLPollEvent)
{
	zval _0;
	zend_long ptr = 0, event_type = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	
            SDL_Event *event = emalloc(sizeof(SDL_Event));
            bool has_event = SDL_WaitEventTimeout(event, 0);

            if (has_event) {
                ptr        = (zend_long)(uintptr_t) event;
                event_type = (zend_long) event->type;

            } else {
                efree(event);
                ptr        = 0;
                event_type = 0;
            }
        
	if (ptr == 0) {
		RETURN_MM_NULL();
	}
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, ptr);
	zephir_array_update_string(return_value, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, event_type);
	zephir_array_update_string(return_value, SL("event_type"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLWaitEventTimeout)
{
	zval *timeout_ms_param = NULL;
	zend_long timeout_ms, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(timeout_ms)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &timeout_ms_param);
	
            SDL_Event *event = emalloc(sizeof(SDL_Event));
            bool has_event = SDL_WaitEventTimeout(event, (Sint32) timeout_ms);

            if (has_event) {
                ptr = (zend_long)(uintptr_t) event;
            } else {
                efree(event);
                ptr = 0;
            }
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLWaitEvent)
{
	zval _0;
	zend_long ptr = 0, event_type = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	
            SDL_Event *event = emalloc(sizeof(SDL_Event));
            bool has_event = SDL_WaitEvent(event);

            if (has_event) {
                ptr        = (zend_long)(uintptr_t) event;
                event_type = (zend_long) event->type;
            } else {
                efree(event);
                ptr        = 0;
                event_type = 0;
            }
        
	if (ptr == 0) {
		RETURN_MM_NULL();
	}
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, ptr);
	zephir_array_update_string(return_value, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, event_type);
	zephir_array_update_string(return_value, SL("event_type"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLPeepEvents)
{
	zval result;
	zval *action_param = NULL, *min_type_param = NULL, *max_type_param = NULL, *numevents_param = NULL;
	zend_long action, min_type, max_type, numevents;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_LONG(action)
		Z_PARAM_LONG(min_type)
		Z_PARAM_LONG(max_type)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(numevents)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 1, &action_param, &min_type_param, &max_type_param, &numevents_param);
	if (!numevents_param) {
		numevents = 1;
	} else {
		}
	
            int requested = (int) numevents;
            SDL_EventAction event_action = (SDL_EventAction) action;

            array_init(&result);

            if (requested > 0 && event_action != SDL_ADDEVENT) {
                SDL_Event *events = emalloc(sizeof(SDL_Event) * requested);
                int count = SDL_PeepEvents(
                    events,
                    requested,
                    event_action,
                    (Uint32) min_type,
                    (Uint32) max_type
                );

                if (count > 0) {
                    for (int i = 0; i < count; i++) {
                        SDL_Event *event_copy = emalloc(sizeof(SDL_Event));
                        zval event_data;

                        *event_copy = events[i];

                        array_init(&event_data);
                        add_assoc_long(&event_data, "ptr", (zend_long) (uintptr_t) event_copy);
                        add_assoc_long(&event_data, "event_type", (zend_long) event_copy->type);
                        add_next_index_zval(&result, &event_data);
                    }
                }

                efree(events);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLHasEvent)
{
	zend_bool result = 0;
	zval *type_param = NULL;
	zend_long type;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(type)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &type_param);
	
            result = SDL_HasEvent((Uint32) type);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLHasEvents)
{
	zend_bool result = 0;
	zval *min_type_param = NULL, *max_type_param = NULL;
	zend_long min_type, max_type;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(min_type)
		Z_PARAM_LONG(max_type)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &min_type_param, &max_type_param);
	
            result = SDL_HasEvents((Uint32) min_type, (Uint32) max_type);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLFlushEvent)
{
	zval *type_param = NULL;
	zend_long type;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(type)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &type_param);
	
            SDL_FlushEvent((Uint32) type);
        
}

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLFlushEvents)
{
	zval *min_type_param = NULL, *max_type_param = NULL;
	zend_long min_type, max_type;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(min_type)
		Z_PARAM_LONG(max_type)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &min_type_param, &max_type_param);
	
            SDL_FlushEvents((Uint32) min_type, (Uint32) max_type);
        
}

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLPushEvent)
{
	zend_bool result = 0;
	zval *event_ptr_param = NULL;
	zend_long event_ptr;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(event_ptr)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &event_ptr_param);
	
            SDL_Event *event = (SDL_Event *)(uintptr_t) event_ptr;
            result = SDL_PushEvent((const SDL_Event *) event);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLFreeEvent)
{
	zval *ptr_param = NULL;
	zend_long ptr;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(ptr)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ptr_param);
	
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            efree(event);
        
}

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLPumpEvents)
{

	
            SDL_PumpEvents();
        
}

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLGetKeyboardState)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_RETURN_CALL_CE_STATIC(sdl3_sdl_events_sdlkeyboard_ce, "sdlgetkeyboardstate", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

