
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
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/array.h"

#include <SDL3/SDL.h>
#include <stdio.h>



ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLKeyboard)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Events, SDLKeyboard, sdl3, sdl_events_sdlkeyboard, sdl3_sdl_events_sdlkeyboard_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLHasKeyboard)
{
	zend_bool result = 0;
	
            result = SDL_HasKeyboard();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyboards)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            int count = 0;
            SDL_KeyboardID *ids = SDL_GetKeyboards(&count);

            array_init(&result);
            if (ids != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) ids[i]);
                }
                SDL_free(ids);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyboardNameForID)
{
	zval name;
	zval *instance_id_param = NULL;
	zend_long instance_id;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            const char *keyboard_name = SDL_GetKeyboardNameForID((SDL_KeyboardID) instance_id);
            if (keyboard_name == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, keyboard_name);
            }
        
	RETURN_CTORW(&name);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyboardFocus)
{
	zend_long ptr = 0;
	
            SDL_Window *window = SDL_GetKeyboardFocus();
            ptr = (zend_long)(uintptr_t) window;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyboardState)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            int numkeys = 0;
            const bool *state = SDL_GetKeyboardState(&numkeys);

            array_init(&result);
            if (state != NULL) {
                for (int i = 0; i < numkeys; i++) {
                    add_index_bool(&result, i, state[i]);
                }
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetModState)
{
	zend_long modstate = 0;
	
            modstate = (zend_long) SDL_GetModState();
        
	RETURN_LONG(modstate);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLSetModState)
{
	zval *modstate_param = NULL;
	zend_long modstate;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(modstate)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &modstate_param);
	
            SDL_SetModState((SDL_Keymod) modstate);
        
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyFromScancode)
{
	zend_bool key_event;
	zval *scancode_param = NULL, *modstate_param = NULL, *key_event_param = NULL;
	zend_long scancode, modstate, keycode = 0;

	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_LONG(scancode)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(modstate)
		Z_PARAM_BOOL(key_event)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 2, &scancode_param, &modstate_param, &key_event_param);
	if (!modstate_param) {
		modstate = 0;
	} else {
		}
	if (!key_event_param) {
		key_event = 1;
	} else {
		}
	
            keycode = (zend_long) SDL_GetKeyFromScancode((SDL_Scancode) scancode, (SDL_Keymod) modstate, key_event);
        
	RETURN_LONG(keycode);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetScancodeFromKey)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *key_param = NULL, _0;
	zend_long key, scancode = 0, modstate = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(key)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &key_param);
	
            SDL_Keymod mod = SDL_KMOD_NONE;
            SDL_Scancode scan = SDL_GetScancodeFromKey((SDL_Keycode) key, &mod);
            scancode = (zend_long) scan;
            modstate = (zend_long) mod;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, scancode);
	zephir_array_update_string(return_value, SL("scancode"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, modstate);
	zephir_array_update_string(return_value, SL("modstate"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLSetScancodeName)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval name;
	zval *scancode_param = NULL, *name_param = NULL;
	zend_long scancode;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(scancode)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &scancode_param, &name_param);
	zephir_get_strval(&name, name_param);
	
            result = SDL_SetScancodeName((SDL_Scancode) scancode, Z_STRVAL(name));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetScancodeName)
{
	zval name;
	zval *scancode_param = NULL;
	zend_long scancode;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(scancode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &scancode_param);
	
            const char *scancode_name = SDL_GetScancodeName((SDL_Scancode) scancode);
            if (scancode_name == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, scancode_name);
            }
        
	RETURN_CTORW(&name);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetScancodeFromName)
{
	zend_long scancode = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *name_param = NULL;
	zval name;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &name_param);
	zephir_get_strval(&name, name_param);
	
            scancode = (zend_long) SDL_GetScancodeFromName(Z_STRVAL(name));
        
	RETURN_MM_LONG(scancode);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyName)
{
	zval name;
	zval *key_param = NULL;
	zend_long key;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(key)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &key_param);
	
            const char *key_name = SDL_GetKeyName((SDL_Keycode) key);
            if (key_name == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, key_name);
            }
        
	RETURN_CTORW(&name);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyFromName)
{
	zend_long key = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *name_param = NULL;
	zval name;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &name_param);
	zephir_get_strval(&name, name_param);
	
            key = (zend_long) SDL_GetKeyFromName(Z_STRVAL(name));
        
	RETURN_MM_LONG(key);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLStartTextInput)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_StartTextInput(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLStartTextInputWithProperties)
{
	zend_bool result = 0;
	zval *window_param = NULL, *props_param = NULL;
	zend_long window, props;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(props)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &props_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_StartTextInputWithProperties(win, (SDL_PropertiesID) props);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLTextInputActive)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_TextInputActive(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLStopTextInput)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_StopTextInput(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLClearComposition)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_ClearComposition(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLSetTextInputArea)
{
	zend_bool result = 0;
	zval *window_param = NULL, *rect = NULL, rect_sub, *cursor_param = NULL, __$null;
	zend_long window, cursor;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
		Z_PARAM_LONG(cursor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 2, &window_param, &rect, &cursor_param);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	if (!cursor_param) {
		cursor = 0;
	} else {
		}
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Rect area;
            const SDL_Rect *area_ptr = NULL;

            if (Z_TYPE_P(rect) == IS_ARRAY) {
                zval *rx = zend_hash_str_find(Z_ARRVAL_P(rect), "x", sizeof("x") - 1);
                zval *ry = zend_hash_str_find(Z_ARRVAL_P(rect), "y", sizeof("y") - 1);
                zval *rw = zend_hash_str_find(Z_ARRVAL_P(rect), "w", sizeof("w") - 1);
                zval *rh = zend_hash_str_find(Z_ARRVAL_P(rect), "h", sizeof("h") - 1);

                area.x = rx ? (int) zval_get_long(rx) : 0;
                area.y = ry ? (int) zval_get_long(ry) : 0;
                area.w = rw ? (int) zval_get_long(rw) : 0;
                area.h = rh ? (int) zval_get_long(rh) : 0;
                area_ptr = &area;
            }

            result = SDL_SetTextInputArea(win, area_ptr, (int) cursor);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetTextInputArea)
{
	zval _0;
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _1;
	zend_long window, x = 0, y = 0, w = 0, h = 0, cursor = 0;

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Rect area = {0};
            int caret = 0;

            result = SDL_GetTextInputArea(win, &area, &caret);
            x = (zend_long) area.x;
            y = (zend_long) area.y;
            w = (zend_long) area.w;
            h = (zend_long) area.h;
            cursor = (zend_long) caret;
        
	if (!(result)) {
		RETURN_MM_NULL();
	}
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 4, 0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_LONG(&_1, x);
	zephir_array_update_string(&_0, SL("x"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, y);
	zephir_array_update_string(&_0, SL("y"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, w);
	zephir_array_update_string(&_0, SL("w"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, h);
	zephir_array_update_string(&_0, SL("h"), &_1, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("rect"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, cursor);
	zephir_array_update_string(return_value, SL("cursor"), &_1, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLHasScreenKeyboardSupport)
{
	zend_bool result = 0;
	
            result = SDL_HasScreenKeyboardSupport();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLScreenKeyboardShown)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_ScreenKeyboardShown(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLReadKeyboardEvent)
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
            SDL_KeyboardEvent *kev = &event->key;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) kev->type);
            add_assoc_long(&result, "timestamp", (zend_long) kev->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) kev->windowID);
            add_assoc_long(&result, "which", (zend_long) kev->which);
            add_assoc_long(&result, "scancode", (zend_long) kev->scancode);
            add_assoc_long(&result, "key", (zend_long) kev->key);
            add_assoc_long(&result, "mod", (zend_long) kev->mod);
            add_assoc_long(&result, "raw", (zend_long) kev->raw);
            add_assoc_bool(&result, "down", kev->down);
            add_assoc_bool(&result, "repeat", kev->repeat);

            efree(event);
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLReadTextInputEvent)
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
            SDL_TextInputEvent *tev = &event->text;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) tev->type);
            add_assoc_long(&result, "timestamp", (zend_long) tev->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) tev->windowID);
            add_assoc_string(&result, "text", tev->text ? tev->text : "");

            efree(event);
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLReadTextEditingEvent)
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
            SDL_TextEditingEvent *eev = &event->edit;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) eev->type);
            add_assoc_long(&result, "timestamp", (zend_long) eev->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) eev->windowID);
            add_assoc_string(&result, "text", eev->text ? eev->text : "");
            add_assoc_long(&result, "start", (zend_long) eev->start);
            add_assoc_long(&result, "length", (zend_long) eev->length);

            efree(event);
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLReadTextEditingCandidatesEvent)
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
            SDL_TextEditingCandidatesEvent *cev = &event->edit_candidates;
            zval candidates;
            int i;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) cev->type);
            add_assoc_long(&result, "timestamp", (zend_long) cev->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) cev->windowID);
            add_assoc_long(&result, "selected_candidate", (zend_long) cev->selected_candidate);
            add_assoc_bool(&result, "horizontal", cev->horizontal);

            array_init(&candidates);
            if (cev->candidates != NULL) {
                for (i = 0; i < cev->num_candidates; i++) {
                    add_next_index_string(&candidates, cev->candidates[i] ? cev->candidates[i] : "");
                }
            }
            add_assoc_long(&result, "num_candidates", (zend_long) cev->num_candidates);
            add_assoc_zval(&result, "candidates", &candidates);

            efree(event);
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLReadKeyboardDeviceEvent)
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
            SDL_KeyboardDeviceEvent *kdev = &event->kdevice;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) kdev->type);
            add_assoc_long(&result, "timestamp", (zend_long) kdev->timestamp);
            add_assoc_long(&result, "which", (zend_long) kdev->which);

            efree(event);
        
	RETURN_CTORW(&result);
}

