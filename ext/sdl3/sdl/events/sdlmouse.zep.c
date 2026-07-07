
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



/**
 * Mouse-related SDL_Event union arms. Agent boundary: decode-only helpers; SDL_mouse.h API comes later.
 */
ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLMouse)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Events, SDLMouse, sdl3, sdl_events_sdlmouse, sdl3_sdl_events_sdlmouse_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLHasMouse)
{
	zend_bool result = 0;
	
            result = SDL_HasMouse();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetMice)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            int count = 0;
            SDL_MouseID *ids = SDL_GetMice(&count);

            array_init(&result);
            if (ids != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) ids[i]);
                }
                SDL_free(ids);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetMouseNameForID)
{
	zval name;
	zval *instance_id_param = NULL;
	zend_long instance_id;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            const char *mouse_name = SDL_GetMouseNameForID((SDL_MouseID) instance_id);
            if (mouse_name == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, mouse_name);
            }
        
	RETURN_CTORW(&name);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetMouseFocus)
{
	zend_long ptr = 0;
	
            SDL_Window *window = SDL_GetMouseFocus();
            ptr = (zend_long)(uintptr_t) window;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetMouseState)
{
	zval _0;
	double x = 0, y = 0;
	zend_long buttons = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	
            float xx = 0.0f;
            float yy = 0.0f;
            SDL_MouseButtonFlags state = SDL_GetMouseState(&xx, &yy);
            buttons = (zend_long) state;
            x = (double) xx;
            y = (double) yy;
        
	zephir_create_array(return_value, 3, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, buttons);
	zephir_array_update_string(return_value, SL("buttons"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, x);
	zephir_array_update_string(return_value, SL("x"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, y);
	zephir_array_update_string(return_value, SL("y"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetGlobalMouseState)
{
	zval _0;
	double x = 0, y = 0;
	zend_long buttons = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	
            float xx = 0.0f;
            float yy = 0.0f;
            SDL_MouseButtonFlags state = SDL_GetGlobalMouseState(&xx, &yy);
            buttons = (zend_long) state;
            x = (double) xx;
            y = (double) yy;
        
	zephir_create_array(return_value, 3, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, buttons);
	zephir_array_update_string(return_value, SL("buttons"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, x);
	zephir_array_update_string(return_value, SL("x"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, y);
	zephir_array_update_string(return_value, SL("y"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetRelativeMouseState)
{
	zval _0;
	double x = 0, y = 0;
	zend_long buttons = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	
            float xx = 0.0f;
            float yy = 0.0f;
            SDL_MouseButtonFlags state = SDL_GetRelativeMouseState(&xx, &yy);
            buttons = (zend_long) state;
            x = (double) xx;
            y = (double) yy;
        
	zephir_create_array(return_value, 3, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, buttons);
	zephir_array_update_string(return_value, SL("buttons"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, x);
	zephir_array_update_string(return_value, SL("x"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, y);
	zephir_array_update_string(return_value, SL("y"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLWarpMouseInWindow)
{
	double x, y;
	zval *window_param = NULL, *x_param = NULL, *y_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_ZVAL(x)
		Z_PARAM_ZVAL(y)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 1, &window_param, &x_param, &y_param);
	x = zephir_get_doubleval(x_param);
	y = zephir_get_doubleval(y_param);
	if (!window_param) {
		window = 0;
	} else {
		}
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_WarpMouseInWindow(win, (float) x, (float) y);
        
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLWarpMouseGlobal)
{
	zend_bool result = 0;
	zval *x_param = NULL, *y_param = NULL;
	double x, y;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(x)
		Z_PARAM_ZVAL(y)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &x_param, &y_param);
	x = zephir_get_doubleval(x_param);
	y = zephir_get_doubleval(y_param);
	
            result = SDL_WarpMouseGlobal((float) x, (float) y);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLSetWindowRelativeMouseMode)
{
	zend_bool enabled, result = 0;
	zval *window_param = NULL, *enabled_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_BOOL(enabled)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &enabled_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowRelativeMouseMode(win, enabled);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetWindowRelativeMouseMode)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_GetWindowRelativeMouseMode(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLCaptureMouse)
{
	zval *enabled_param = NULL;
	zend_bool enabled, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(enabled)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &enabled_param);
	
            result = SDL_CaptureMouse(enabled);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLCreateCursor)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long w, h, hot_x, hot_y, ptr = 0;
	zval *data_param = NULL, *mask_param = NULL, *w_param = NULL, *h_param = NULL, *hot_x_param = NULL, *hot_y_param = NULL;
	zval data, mask;

	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&mask);
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_STR(data)
		Z_PARAM_STR(mask)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(hot_x)
		Z_PARAM_LONG(hot_y)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 6, 0, &data_param, &mask_param, &w_param, &h_param, &hot_x_param, &hot_y_param);
	zephir_get_strval(&data, data_param);
	zephir_get_strval(&mask, mask_param);
	
            const Uint8 *data_ptr = (const Uint8 *) Z_STRVAL(data);
            const Uint8 *mask_ptr = (const Uint8 *) Z_STRVAL(mask);
            SDL_Cursor *cursor = SDL_CreateCursor(data_ptr, mask_ptr, (int) w, (int) h, (int) hot_x, (int) hot_y);
            ptr = (zend_long)(uintptr_t) cursor;
        
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLCreateColorCursor)
{
	zval *surface_param = NULL, *hot_x_param = NULL, *hot_y_param = NULL;
	zend_long surface, hot_x, hot_y, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(hot_x)
		Z_PARAM_LONG(hot_y)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &surface_param, &hot_x_param, &hot_y_param);
	
            SDL_Surface *sur = (SDL_Surface *)(uintptr_t) surface;
            SDL_Cursor *cursor = SDL_CreateColorCursor(sur, (int) hot_x, (int) hot_y);
            ptr = (zend_long)(uintptr_t) cursor;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLCreateAnimatedCursor)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long hot_x, hot_y, ptr = 0;
	zval *frames_param = NULL, *hot_x_param = NULL, *hot_y_param = NULL;
	zval frames;

	ZVAL_UNDEF(&frames);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_ARRAY(frames)
		Z_PARAM_LONG(hot_x)
		Z_PARAM_LONG(hot_y)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &frames_param, &hot_x_param, &hot_y_param);
	zephir_get_arrval(&frames, frames_param);
	
            int frame_count = zend_hash_num_elements(Z_ARRVAL_P(&frames));
            SDL_CursorFrameInfo *frame_infos = NULL;
            SDL_Cursor *cursor = NULL;
            int i = 0;
            zval *entry;

            if (frame_count > 0) {
                frame_infos = (SDL_CursorFrameInfo *) emalloc(sizeof(SDL_CursorFrameInfo) * frame_count);
                memset(frame_infos, 0, sizeof(SDL_CursorFrameInfo) * frame_count);

                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&frames), entry) {
                    if (i >= frame_count) {
                        break;
                    }
                    if (Z_TYPE_P(entry) == IS_ARRAY) {
                        zval *surface = zend_hash_str_find(Z_ARRVAL_P(entry), "surface", sizeof("surface") - 1);
                        zval *duration = zend_hash_str_find(Z_ARRVAL_P(entry), "duration", sizeof("duration") - 1);
                        frame_infos[i].surface = (SDL_Surface *)(uintptr_t) (surface ? zval_get_long(surface) : 0);
                        frame_infos[i].duration = (Uint32) (duration ? zval_get_long(duration) : 0);
                        i++;
                    }
                } ZEND_HASH_FOREACH_END();

                cursor = SDL_CreateAnimatedCursor(frame_infos, i, (int) hot_x, (int) hot_y);
                efree(frame_infos);
            }

            ptr = (zend_long)(uintptr_t) cursor;
        
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLCreateSystemCursor)
{
	zval *id_param = NULL;
	zend_long id, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &id_param);
	
            SDL_Cursor *cursor = SDL_CreateSystemCursor((SDL_SystemCursor) id);
            ptr = (zend_long)(uintptr_t) cursor;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLSetCursor)
{
	zend_bool result = 0;
	zval *cursor = NULL, cursor_sub, __$null;

	ZVAL_UNDEF(&cursor_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(cursor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(0, 1, &cursor);
	if (!cursor) {
		cursor = &cursor_sub;
		cursor = &__$null;
	}
	
            SDL_Cursor *cur = NULL;
            if (Z_TYPE_P(cursor) != IS_NULL) {
                cur = (SDL_Cursor *)(uintptr_t) zval_get_long(cursor);
            }
            result = SDL_SetCursor(cur);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetCursor)
{
	zend_long ptr = 0;
	
            SDL_Cursor *cursor = SDL_GetCursor();
            ptr = (zend_long)(uintptr_t) cursor;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetDefaultCursor)
{
	zend_long ptr = 0;
	
            SDL_Cursor *cursor = SDL_GetDefaultCursor();
            ptr = (zend_long)(uintptr_t) cursor;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLDestroyCursor)
{
	zval *cursor_param = NULL;
	zend_long cursor;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(cursor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &cursor_param);
	
            SDL_Cursor *cur = (SDL_Cursor *)(uintptr_t) cursor;
            SDL_DestroyCursor(cur);
        
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLShowCursor)
{
	zend_bool result = 0;
	
            result = SDL_ShowCursor();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLHideCursor)
{
	zend_bool result = 0;
	
            result = SDL_HideCursor();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLCursorVisible)
{
	zend_bool result = 0;
	
            result = SDL_CursorVisible();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLReadMouseDeviceEvent)
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
            SDL_MouseDeviceEvent *mdev = &event->mdevice;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) mdev->type);
            add_assoc_long(&result, "timestamp", (zend_long) mdev->timestamp);
            add_assoc_long(&result, "which", (zend_long) mdev->which);

            efree(event);
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLReadMouseMotionEvent)
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
            SDL_MouseMotionEvent *mov = &event->motion;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) mov->type);
            add_assoc_long(&result, "timestamp", (zend_long) mov->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) mov->windowID);
            add_assoc_long(&result, "which", (zend_long) mov->which);
            add_assoc_long(&result, "state", (zend_long) mov->state);
            add_assoc_double(&result, "x", (double) mov->x);
            add_assoc_double(&result, "y", (double) mov->y);
            add_assoc_double(&result, "xrel", (double) mov->xrel);
            add_assoc_double(&result, "yrel", (double) mov->yrel);

            efree(event);
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLReadMouseButtonEvent)
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
            SDL_MouseButtonEvent *btn = &event->button;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) btn->type);
            add_assoc_long(&result, "timestamp", (zend_long) btn->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) btn->windowID);
            add_assoc_long(&result, "which", (zend_long) btn->which);
            add_assoc_long(&result, "button", (zend_long) btn->button);
            add_assoc_bool(&result, "down", btn->down);
            add_assoc_long(&result, "clicks", (zend_long) btn->clicks);
            add_assoc_double(&result, "x", (double) btn->x);
            add_assoc_double(&result, "y", (double) btn->y);

            efree(event);
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLReadMouseWheelEvent)
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
            SDL_MouseWheelEvent *whl = &event->wheel;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) whl->type);
            add_assoc_long(&result, "timestamp", (zend_long) whl->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) whl->windowID);
            add_assoc_long(&result, "which", (zend_long) whl->which);
            add_assoc_double(&result, "x", (double) whl->x);
            add_assoc_double(&result, "y", (double) whl->y);
            add_assoc_long(&result, "direction", (zend_long) whl->direction);
            add_assoc_double(&result, "mouse_x", (double) whl->mouse_x);
            add_assoc_double(&result, "mouse_y", (double) whl->mouse_y);
            add_assoc_long(&result, "integer_x", (zend_long) whl->integer_x);
            add_assoc_long(&result, "integer_y", (zend_long) whl->integer_y);

            efree(event);
        
	RETURN_CTORW(&result);
}

