
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
#include "kernel/array.h"

#include <SDL3/SDL.h>
#include <stdio.h>



ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLDisplayEvents)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Events, SDLDisplayEvents, sdl3, sdl_events_sdldisplayevents, sdl3_sdl_events_sdldisplayevents_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Events_SDLDisplayEvents, SDLReadDisplayEvent)
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
            SDL_DisplayEvent *dev = &event->display;

            array_init(&result);
            add_assoc_long(&result, "type",       (zend_long) dev->type);
            add_assoc_long(&result, "timestamp",  (zend_long) dev->timestamp);
            add_assoc_long(&result, "display_id", (zend_long) dev->displayID);
            add_assoc_long(&result, "data1",      (zend_long) dev->data1);
            add_assoc_long(&result, "data2",      (zend_long) dev->data2);

            efree(event);
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLDisplayEvents, SDLGetDisplays)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            int count = 0;
            SDL_DisplayID *displays = SDL_GetDisplays(&count);

            array_init(&result);
            if (displays != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) displays[i]);
                }
                SDL_free(displays);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLDisplayEvents, SDLGetPrimaryDisplay)
{
	zend_long result = 0;
	
            result = (zend_long) SDL_GetPrimaryDisplay();
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLDisplayEvents, SDLGetDisplayName)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *display_id_param = NULL;
	zend_long display_id;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display_id)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &display_id_param);
	ZEPHIR_INIT_VAR(&result);
	
            const char *name = SDL_GetDisplayName((SDL_DisplayID) display_id);
            if (name) {
                ZVAL_STRING(&result, name);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLDisplayEvents, SDLGetDisplayBounds)
{
	zend_bool ok = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *display_id_param = NULL, _0;
	zend_long display_id, x, y, w, h;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display_id)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &display_id_param);
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	
            SDL_Rect rect;
            ok = SDL_GetDisplayBounds((SDL_DisplayID) display_id, &rect);
            if (ok) {
                x = (zend_long) rect.x;
                y = (zend_long) rect.y;
                w = (zend_long) rect.w;
                h = (zend_long) rect.h;
            }
        
	if (!(ok)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 4, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, x);
	zephir_array_update_string(return_value, SL("x"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, y);
	zephir_array_update_string(return_value, SL("y"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Events_SDLDisplayEvents, SDLGetDisplayForWindow)
{
	zval *window_param = NULL;
	zend_long window, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (zend_long) SDL_GetDisplayForWindow(win);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLDisplayEvents, SDLGetNaturalDisplayOrientation)
{
	zval *display_id_param = NULL;
	zend_long display_id, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &display_id_param);
	
            result = (zend_long) SDL_GetNaturalDisplayOrientation((SDL_DisplayID) display_id);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLDisplayEvents, SDLGetCurrentDisplayOrientation)
{
	zval *display_id_param = NULL;
	zend_long display_id, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &display_id_param);
	
            result = (zend_long) SDL_GetCurrentDisplayOrientation((SDL_DisplayID) display_id);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLDisplayEvents, SDLGetDisplayContentScale)
{
	double result = 0;
	zval *display_id_param = NULL;
	zend_long display_id;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &display_id_param);
	
            result = (double) SDL_GetDisplayContentScale((SDL_DisplayID) display_id);
        
	RETURN_DOUBLE(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLDisplayEvents, SDLGetFullscreenDisplayModes)
{
	zval result;
	zval *display_id_param = NULL;
	zend_long display_id;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &display_id_param);
	
            int count = 0;
            SDL_DisplayMode **modes = SDL_GetFullscreenDisplayModes((SDL_DisplayID) display_id, &count);

            array_init(&result);
            if (modes != NULL) {
                for (int i = 0; i < count; i++) {
                    SDL_DisplayMode *mode = modes[i];
                    if (mode != NULL) {
                        zval mode_array;
                        array_init(&mode_array);
                        add_assoc_long(&mode_array, "display_id",                (zend_long) mode->displayID);
                        add_assoc_long(&mode_array, "format",                    (zend_long) mode->format);
                        add_assoc_long(&mode_array, "w",                         (zend_long) mode->w);
                        add_assoc_long(&mode_array, "h",                         (zend_long) mode->h);
                        add_assoc_double(&mode_array, "pixel_density",           (double) mode->pixel_density);
                        add_assoc_double(&mode_array, "refresh_rate",            (double) mode->refresh_rate);
                        add_assoc_long(&mode_array, "refresh_rate_numerator",    (zend_long) mode->refresh_rate_numerator);
                        add_assoc_long(&mode_array, "refresh_rate_denominator",  (zend_long) mode->refresh_rate_denominator);
                        add_next_index_zval(&result, &mode_array);
                    }
                }
                SDL_free(modes);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLDisplayEvents, SDLGetDesktopDisplayMode)
{
	zend_bool found = 0;
	double mode_pixel_density, mode_refresh_rate;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *display_id_param = NULL, _0;
	zend_long display_id, mode_display_id, mode_format, mode_w, mode_h, mode_refresh_rate_numerator, mode_refresh_rate_denominator;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display_id)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &display_id_param);
	mode_display_id = 0;
	mode_format = 0;
	mode_w = 0;
	mode_h = 0;
	mode_pixel_density =  (0.0);
	mode_refresh_rate =  (0.0);
	mode_refresh_rate_numerator = 0;
	mode_refresh_rate_denominator = 0;
	
            const SDL_DisplayMode *mode = SDL_GetDesktopDisplayMode((SDL_DisplayID) display_id);
            found = (mode != NULL);

            if (found) {
                mode_display_id = (zend_long) mode->displayID;
                mode_format = (zend_long) mode->format;
                mode_w = (zend_long) mode->w;
                mode_h = (zend_long) mode->h;
                mode_pixel_density = (double) mode->pixel_density;
                mode_refresh_rate = (double) mode->refresh_rate;
                mode_refresh_rate_numerator = (zend_long) mode->refresh_rate_numerator;
                mode_refresh_rate_denominator = (zend_long) mode->refresh_rate_denominator;
            }
        
	if (!(found)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 8, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, mode_display_id);
	zephir_array_update_string(return_value, SL("display_id"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_format);
	zephir_array_update_string(return_value, SL("format"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, mode_pixel_density);
	zephir_array_update_string(return_value, SL("pixel_density"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, mode_refresh_rate);
	zephir_array_update_string(return_value, SL("refresh_rate"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_refresh_rate_numerator);
	zephir_array_update_string(return_value, SL("refresh_rate_numerator"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_refresh_rate_denominator);
	zephir_array_update_string(return_value, SL("refresh_rate_denominator"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Events_SDLDisplayEvents, SDLGetCurrentDisplayMode)
{
	zend_bool found = 0;
	double mode_pixel_density, mode_refresh_rate;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *display_id_param = NULL, _0;
	zend_long display_id, mode_display_id, mode_format, mode_w, mode_h, mode_refresh_rate_numerator, mode_refresh_rate_denominator;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display_id)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &display_id_param);
	mode_display_id = 0;
	mode_format = 0;
	mode_w = 0;
	mode_h = 0;
	mode_pixel_density =  (0.0);
	mode_refresh_rate =  (0.0);
	mode_refresh_rate_numerator = 0;
	mode_refresh_rate_denominator = 0;
	
            const SDL_DisplayMode *mode = SDL_GetCurrentDisplayMode((SDL_DisplayID) display_id);
            found = (mode != NULL);

            if (found) {
                mode_display_id = (zend_long) mode->displayID;
                mode_format = (zend_long) mode->format;
                mode_w = (zend_long) mode->w;
                mode_h = (zend_long) mode->h;
                mode_pixel_density = (double) mode->pixel_density;
                mode_refresh_rate = (double) mode->refresh_rate;
                mode_refresh_rate_numerator = (zend_long) mode->refresh_rate_numerator;
                mode_refresh_rate_denominator = (zend_long) mode->refresh_rate_denominator;
            }
        
	if (!(found)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 8, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, mode_display_id);
	zephir_array_update_string(return_value, SL("display_id"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_format);
	zephir_array_update_string(return_value, SL("format"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, mode_pixel_density);
	zephir_array_update_string(return_value, SL("pixel_density"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, mode_refresh_rate);
	zephir_array_update_string(return_value, SL("refresh_rate"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_refresh_rate_numerator);
	zephir_array_update_string(return_value, SL("refresh_rate_numerator"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_refresh_rate_denominator);
	zephir_array_update_string(return_value, SL("refresh_rate_denominator"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Events_SDLDisplayEvents, SDLGetClosestFullscreenDisplayMode)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool include_high_density_modes, found = 0;
	double refresh_rate, mode_pixel_density, mode_refresh_rate;
	zval *display_id_param = NULL, *w_param = NULL, *h_param = NULL, *refresh_rate_param = NULL, *include_high_density_modes_param = NULL, _0;
	zend_long display_id, w, h, mode_display_id, mode_format, mode_w, mode_h, mode_refresh_rate_numerator, mode_refresh_rate_denominator;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 5)
		Z_PARAM_LONG(display_id)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(refresh_rate)
		Z_PARAM_BOOL(include_high_density_modes)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 2, &display_id_param, &w_param, &h_param, &refresh_rate_param, &include_high_density_modes_param);
	if (!refresh_rate_param) {
		refresh_rate = 0.0;
	} else {
		refresh_rate = zephir_get_doubleval(refresh_rate_param);
	}
	if (!include_high_density_modes_param) {
		include_high_density_modes = 0;
	} else {
		}
	mode_display_id = 0;
	mode_format = 0;
	mode_w = 0;
	mode_h = 0;
	mode_pixel_density =  (0.0);
	mode_refresh_rate =  (0.0);
	mode_refresh_rate_numerator = 0;
	mode_refresh_rate_denominator = 0;
	
            SDL_DisplayMode closest;
            found = SDL_GetClosestFullscreenDisplayMode(
                (SDL_DisplayID) display_id,
                (int) w,
                (int) h,
                (float) refresh_rate,
                (bool) include_high_density_modes,
                &closest
            );

            if (found) {
                mode_display_id = (zend_long) closest.displayID;
                mode_format = (zend_long) closest.format;
                mode_w = (zend_long) closest.w;
                mode_h = (zend_long) closest.h;
                mode_pixel_density = (double) closest.pixel_density;
                mode_refresh_rate = (double) closest.refresh_rate;
                mode_refresh_rate_numerator = (zend_long) closest.refresh_rate_numerator;
                mode_refresh_rate_denominator = (zend_long) closest.refresh_rate_denominator;
            }
        
	if (!(found)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 8, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, mode_display_id);
	zephir_array_update_string(return_value, SL("display_id"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_format);
	zephir_array_update_string(return_value, SL("format"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, mode_pixel_density);
	zephir_array_update_string(return_value, SL("pixel_density"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, mode_refresh_rate);
	zephir_array_update_string(return_value, SL("refresh_rate"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_refresh_rate_numerator);
	zephir_array_update_string(return_value, SL("refresh_rate_numerator"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode_refresh_rate_denominator);
	zephir_array_update_string(return_value, SL("refresh_rate_denominator"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

