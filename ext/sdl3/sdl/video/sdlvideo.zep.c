
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
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"

#include <SDL3/SDL.h>
#include <stdio.h>

typedef struct _php_sdl_hit_test_context {
    zval callback;
    zend_long window_ptr;
} php_sdl_hit_test_context;

static HashTable php_sdl_hit_test_map;
static bool php_sdl_hit_test_map_initialized = false;

static void php_sdl_hit_test_ensure_map(void)
{
    if (!php_sdl_hit_test_map_initialized) {
        zend_hash_init(&php_sdl_hit_test_map, 4, NULL, ZVAL_PTR_DTOR, 0);
        php_sdl_hit_test_map_initialized = true;
    }
}

static php_sdl_hit_test_context *php_sdl_hit_test_context_alloc(zval *callback, zend_long window_ptr)
{
    php_sdl_hit_test_context *ctx = emalloc(sizeof(php_sdl_hit_test_context));
    ZVAL_UNDEF(&ctx->callback);
    ZVAL_COPY(&ctx->callback, callback);
    ctx->window_ptr = window_ptr;
    return ctx;
}

static void php_sdl_hit_test_context_free(php_sdl_hit_test_context *ctx)
{
    if (!ctx) {
        return;
    }
    zval_ptr_dtor(&ctx->callback);
    efree(ctx);
}

static SDL_HitTestResult SDLCALL php_sdl_hit_test_bridge(SDL_Window *win, const SDL_Point *area, void *data)
{
    php_sdl_hit_test_context *ctx = (php_sdl_hit_test_context *) data;
    zval retval;
    zval params[3];
    SDL_HitTestResult result = SDL_HITTEST_NORMAL;

    if (ctx == NULL || area == NULL) {
        return SDL_HITTEST_NORMAL;
    }

    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) win);
    ZVAL_LONG(&params[1], (zend_long) area->x);
    ZVAL_LONG(&params[2], (zend_long) area->y);
    ZVAL_UNDEF(&retval);

    if (call_user_function(EG(function_table), NULL, &ctx->callback, &retval, 3, params) == SUCCESS) {
        result = (SDL_HitTestResult) zval_get_long(&retval);
    }

    if (!Z_ISUNDEF(retval)) {
        zval_ptr_dtor(&retval);
    }

    return result;
}

static bool php_sdl_display_mode_from_array(zval *mode_arr, SDL_DisplayMode *mode)
{
    zval *entry;

    if (Z_TYPE_P(mode_arr) != IS_ARRAY) {
        return false;
    }

    memset(mode, 0, sizeof(SDL_DisplayMode));

    entry = zend_hash_str_find(Z_ARRVAL_P(mode_arr), "display_id", sizeof("display_id") - 1);
    if (entry) {
        mode->displayID = (SDL_DisplayID) zval_get_long(entry);
    }

    entry = zend_hash_str_find(Z_ARRVAL_P(mode_arr), "format", sizeof("format") - 1);
    if (entry) {
        mode->format = (SDL_PixelFormat) zval_get_long(entry);
    }

    entry = zend_hash_str_find(Z_ARRVAL_P(mode_arr), "w", sizeof("w") - 1);
    if (entry) {
        mode->w = (int) zval_get_long(entry);
    }

    entry = zend_hash_str_find(Z_ARRVAL_P(mode_arr), "h", sizeof("h") - 1);
    if (entry) {
        mode->h = (int) zval_get_long(entry);
    }

    entry = zend_hash_str_find(Z_ARRVAL_P(mode_arr), "pixel_density", sizeof("pixel_density") - 1);
    if (entry) {
        mode->pixel_density = (float) zval_get_double(entry);
    }

    entry = zend_hash_str_find(Z_ARRVAL_P(mode_arr), "refresh_rate", sizeof("refresh_rate") - 1);
    if (entry) {
        mode->refresh_rate = (float) zval_get_double(entry);
    }

    entry = zend_hash_str_find(Z_ARRVAL_P(mode_arr), "refresh_rate_numerator", sizeof("refresh_rate_numerator") - 1);
    if (entry) {
        mode->refresh_rate_numerator = (int) zval_get_long(entry);
    }

    entry = zend_hash_str_find(Z_ARRVAL_P(mode_arr), "refresh_rate_denominator", sizeof("refresh_rate_denominator") - 1);
    if (entry) {
        mode->refresh_rate_denominator = (int) zval_get_long(entry);
    }

    return true;
}

static void php_sdl_display_mode_to_zvals(const SDL_DisplayMode *mode,
    zend_long *mode_display_id, zend_long *mode_format, zend_long *mode_w, zend_long *mode_h,
    double *mode_pixel_density, double *mode_refresh_rate,
    zend_long *mode_refresh_rate_numerator, zend_long *mode_refresh_rate_denominator)
{
    *mode_display_id = (zend_long) mode->displayID;
    *mode_format = (zend_long) mode->format;
    *mode_w = (zend_long) mode->w;
    *mode_h = (zend_long) mode->h;
    *mode_pixel_density = (double) mode->pixel_density;
    *mode_refresh_rate = (double) mode->refresh_rate;
    *mode_refresh_rate_numerator = (zend_long) mode->refresh_rate_numerator;
    *mode_refresh_rate_denominator = (zend_long) mode->refresh_rate_denominator;
}



ZEPHIR_INIT_CLASS(Sdl3_SDL_Video_SDLVideo)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Video, SDLVideo, sdl3, sdl_video_sdlvideo, sdl3_sdl_video_sdlvideo_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetNumVideoDrivers)
{
	zend_long result = 0;
	
            result = (zend_long) SDL_GetNumVideoDrivers();
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetVideoDriver)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *index_param = NULL;
	zend_long index;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &index_param);
	ZEPHIR_INIT_VAR(&result);
	
            const char *driver = SDL_GetVideoDriver((int) index);
            if (driver) {
                ZVAL_STRING(&result, driver);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetCurrentVideoDriver)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&result);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&result);
	
            const char *driver = SDL_GetCurrentVideoDriver();
            if (driver) {
                ZVAL_STRING(&result, driver);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetSystemTheme)
{
	zend_long result = 0;
	
            result = (zend_long) SDL_GetSystemTheme();
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetDisplayProperties)
{
	zval *display_id_param = NULL;
	zend_long display_id, props = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &display_id_param);
	
            props = (zend_long) SDL_GetDisplayProperties((SDL_DisplayID) display_id);
        
	RETURN_LONG(props);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetDisplayUsableBounds)
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
            ok = SDL_GetDisplayUsableBounds((SDL_DisplayID) display_id, &rect);
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

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetDisplayForPoint)
{
	zval *x_param = NULL, *y_param = NULL;
	zend_long x, y, result = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &x_param, &y_param);
	
            SDL_Point point = { (int) x, (int) y };
            result = (zend_long) SDL_GetDisplayForPoint(&point);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetDisplayForRect)
{
	zend_long result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *rect_param = NULL;
	zval rect;

	ZVAL_UNDEF(&rect);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ARRAY(rect)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &rect_param);
	zephir_get_arrval(&rect, rect_param);
	
            SDL_Rect r = {0};
            zval *zx = zend_hash_index_find(Z_ARRVAL_P(&rect), 0);
            zval *zy = zend_hash_index_find(Z_ARRVAL_P(&rect), 1);
            zval *zw = zend_hash_index_find(Z_ARRVAL_P(&rect), 2);
            zval *zh = zend_hash_index_find(Z_ARRVAL_P(&rect), 3);
            r.x = zx ? (int) zval_get_long(zx) : 0;
            r.y = zy ? (int) zval_get_long(zy) : 0;
            r.w = zw ? (int) zval_get_long(zw) : 0;
            r.h = zh ? (int) zval_get_long(zh) : 0;
            result = (zend_long) SDL_GetDisplayForRect(&r);
        
	RETURN_MM_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLCreateWindow)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long width, height, flags, ZEPHIR_LAST_CALL_STATUS, ptr = 0;
	zval *title_param = NULL, *width_param = NULL, *height_param = NULL, *flags_param = NULL, _0$$3, _1$$3, _2$$3;
	zval title;

	ZVAL_UNDEF(&title);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_STR(title)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &title_param, &width_param, &height_param, &flags_param);
	zephir_get_strval(&title, title_param);
	
            SDL_Window *window = SDL_CreateWindow(Z_STRVAL(title), (int) width, (int) height, (SDL_WindowFlags) flags);
            ptr = (zend_long)(uintptr_t) window;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateWindow failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/video/sdlvideo.zep", 267);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLCreatePopupWindow)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *parent_param = NULL, *offset_x_param = NULL, *offset_y_param = NULL, *w_param = NULL, *h_param = NULL, *flags_param = NULL, _0$$3, _1$$3, _2$$3;
	zend_long parent, offset_x, offset_y, w, h, flags, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_LONG(parent)
		Z_PARAM_LONG(offset_x)
		Z_PARAM_LONG(offset_y)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 6, 0, &parent_param, &offset_x_param, &offset_y_param, &w_param, &h_param, &flags_param);
	
            SDL_Window *parent_win = (SDL_Window *)(uintptr_t) parent;
            SDL_Window *window = SDL_CreatePopupWindow(parent_win, (int) offset_x, (int) offset_y, (int) w, (int) h, (SDL_WindowFlags) flags);
            ptr = (zend_long)(uintptr_t) window;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreatePopupWindow failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/video/sdlvideo.zep", 284);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLCreateWindowWithProperties)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *props_param = NULL, _0$$3, _1$$3, _2$$3;
	zend_long props, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(props)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &props_param);
	
            SDL_Window *window = SDL_CreateWindowWithProperties((SDL_PropertiesID) props);
            ptr = (zend_long)(uintptr_t) window;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateWindowWithProperties failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/video/sdlvideo.zep", 300);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowID)
{
	zval *window_param = NULL;
	zend_long window, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (zend_long) SDL_GetWindowID(win);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowFromID)
{
	zval *id_param = NULL;
	zend_long id, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &id_param);
	
            SDL_Window *win = SDL_GetWindowFromID((SDL_WindowID) id);
            ptr = (zend_long)(uintptr_t) win;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowParent)
{
	zval *window_param = NULL;
	zend_long window, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Window *parent = SDL_GetWindowParent(win);
            ptr = (zend_long)(uintptr_t) parent;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowProperties)
{
	zval *window_param = NULL;
	zend_long window, props = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            props = (zend_long) SDL_GetWindowProperties(win);
        
	RETURN_LONG(props);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowFlags)
{
	zval *window_param = NULL;
	zend_long window, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (zend_long) SDL_GetWindowFlags(win);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindows)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            int count = 0;
            SDL_Window **windows = SDL_GetWindows(&count);

            array_init(&result);
            if (windows != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long)(uintptr_t) windows[i]);
                }
                SDL_free(windows);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowPixelDensity)
{
	double result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (double) SDL_GetWindowPixelDensity(win);
        
	RETURN_DOUBLE(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowDisplayScale)
{
	double result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (double) SDL_GetWindowDisplayScale(win);
        
	RETURN_DOUBLE(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowFullscreenMode)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval mode;
	zval *window_param = NULL, *mode_param = NULL;
	zend_long window;

	ZVAL_UNDEF(&mode);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_ARRAY(mode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &window_param, &mode_param);
	zephir_get_arrval(&mode, mode_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_DisplayMode dm;
            if (php_sdl_display_mode_from_array(&mode, &dm)) {
                result = SDL_SetWindowFullscreenMode(win, &dm);
            } else {
                result = false;
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowFullscreenMode)
{
	zend_bool found = 0;
	double mode_pixel_density, mode_refresh_rate;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, mode_display_id, mode_format, mode_w, mode_h, mode_refresh_rate_numerator, mode_refresh_rate_denominator;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	mode_display_id = 0;
	mode_format = 0;
	mode_w = 0;
	mode_h = 0;
	mode_pixel_density =  (0.0);
	mode_refresh_rate =  (0.0);
	mode_refresh_rate_numerator = 0;
	mode_refresh_rate_denominator = 0;
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            const SDL_DisplayMode *mode = SDL_GetWindowFullscreenMode(win);
            found = (mode != NULL);
            if (found) {
                php_sdl_display_mode_to_zvals(mode,
                    &mode_display_id, &mode_format, &mode_w, &mode_h,
                    &mode_pixel_density, &mode_refresh_rate,
                    &mode_refresh_rate_numerator, &mode_refresh_rate_denominator);
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

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowICCProfile)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL;
	zend_long window;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	ZEPHIR_INIT_VAR(&result);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            size_t size = 0;
            void *data = SDL_GetWindowICCProfile(win, &size);
            if (data != NULL && size > 0) {
                ZVAL_STRINGL(&result, (char *) data, (size_t) size);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowPixelFormat)
{
	zval *window_param = NULL;
	zend_long window, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (zend_long) SDL_GetWindowPixelFormat(win);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowTitle)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval title;
	zval *window_param = NULL, *title_param = NULL;
	zend_long window;

	ZVAL_UNDEF(&title);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_STR(title)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &window_param, &title_param);
	zephir_get_strval(&title, title_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowTitle(win, Z_STRVAL(title));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowTitle)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL;
	zend_long window;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	ZEPHIR_INIT_VAR(&result);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            const char *title = SDL_GetWindowTitle(win);
            if (title) {
                ZVAL_STRING(&result, title);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowIcon)
{
	zend_bool result = 0;
	zval *window_param = NULL, *surface_param = NULL;
	zend_long window, surface;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &surface_param);
	
            SDL_Window  *win  = (SDL_Window *)(uintptr_t) window;
            SDL_Surface *icon = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetWindowIcon(win, icon);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowPosition)
{
	zend_bool result = 0;
	zval *window_param = NULL, *x_param = NULL, *y_param = NULL;
	zend_long window, x, y;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &window_param, &x_param, &y_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowPosition(win, (int) x, (int) y);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowPosition)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, x = 0, y = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int wx = 0, wy = 0;
            SDL_GetWindowPosition(win, &wx, &wy);
            x = (zend_long) wx;
            y = (zend_long) wy;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, x);
	zephir_array_fast_append(return_value, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, y);
	zephir_array_fast_append(return_value, &_0);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowSize)
{
	zend_bool result = 0;
	zval *window_param = NULL, *w_param = NULL, *h_param = NULL;
	zend_long window, w, h;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &window_param, &w_param, &h_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowSize(win, (int) w, (int) h);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, w = 0, h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int ww = 0, wh = 0;
            SDL_GetWindowSize(win, &ww, &wh);
            w = (zend_long) ww;
            h = (zend_long) wh;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_fast_append(return_value, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_fast_append(return_value, &_0);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSafeArea)
{
	zend_bool ok = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, x, y, w, h;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Rect rect;
            ok = SDL_GetWindowSafeArea(win, &rect);
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

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowAspectRatio)
{
	zend_bool result = 0;
	double min_aspect, max_aspect;
	zval *window_param = NULL, *min_aspect_param = NULL, *max_aspect_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_ZVAL(min_aspect)
		Z_PARAM_ZVAL(max_aspect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &window_param, &min_aspect_param, &max_aspect_param);
	min_aspect = zephir_get_doubleval(min_aspect_param);
	max_aspect = zephir_get_doubleval(max_aspect_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowAspectRatio(win, (float) min_aspect, (float) max_aspect);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowAspectRatio)
{
	double min_aspect = 0, max_aspect = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            float mn = 0.0f, mx = 0.0f;
            SDL_GetWindowAspectRatio(win, &mn, &mx);
            min_aspect = (double) mn;
            max_aspect = (double) mx;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_DOUBLE(&_0, min_aspect);
	zephir_array_fast_append(return_value, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, max_aspect);
	zephir_array_fast_append(return_value, &_0);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowBordersSize)
{
	zend_bool ok = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, top, left, bottom, right;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	top = 0;
	left = 0;
	bottom = 0;
	right = 0;
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int t = 0, l = 0, b = 0, r = 0;
            ok = SDL_GetWindowBordersSize(win, &t, &l, &b, &r);
            if (ok) {
                top = (zend_long) t;
                left = (zend_long) l;
                bottom = (zend_long) b;
                right = (zend_long) r;
            }
        
	if (!(ok)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 4, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, top);
	zephir_array_update_string(return_value, SL("top"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, left);
	zephir_array_update_string(return_value, SL("left"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, bottom);
	zephir_array_update_string(return_value, SL("bottom"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, right);
	zephir_array_update_string(return_value, SL("right"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSizeInPixels)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, w = 0, h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int pw = 0, ph = 0;
            SDL_GetWindowSizeInPixels(win, &pw, &ph);
            w = (zend_long) pw;
            h = (zend_long) ph;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_fast_append(return_value, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_fast_append(return_value, &_0);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowMinimumSize)
{
	zend_bool result = 0;
	zval *window_param = NULL, *min_w_param = NULL, *min_h_param = NULL;
	zend_long window, min_w, min_h;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(min_w)
		Z_PARAM_LONG(min_h)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &window_param, &min_w_param, &min_h_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowMinimumSize(win, (int) min_w, (int) min_h);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowMinimumSize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, min_w = 0, min_h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int pw = 0, ph = 0;
            SDL_GetWindowMinimumSize(win, &pw, &ph);
            min_w = (zend_long) pw;
            min_h = (zend_long) ph;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, min_w);
	zephir_array_fast_append(return_value, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, min_h);
	zephir_array_fast_append(return_value, &_0);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowMaximumSize)
{
	zend_bool result = 0;
	zval *window_param = NULL, *max_w_param = NULL, *max_h_param = NULL;
	zend_long window, max_w, max_h;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(max_w)
		Z_PARAM_LONG(max_h)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &window_param, &max_w_param, &max_h_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowMaximumSize(win, (int) max_w, (int) max_h);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowMaximumSize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, max_w = 0, max_h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int pw = 0, ph = 0;
            SDL_GetWindowMaximumSize(win, &pw, &ph);
            max_w = (zend_long) pw;
            max_h = (zend_long) ph;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, max_w);
	zephir_array_fast_append(return_value, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, max_h);
	zephir_array_fast_append(return_value, &_0);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowBordered)
{
	zend_bool bordered, result = 0;
	zval *window_param = NULL, *bordered_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_BOOL(bordered)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &bordered_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowBordered(win, bordered);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowResizable)
{
	zend_bool resizable, result = 0;
	zval *window_param = NULL, *resizable_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_BOOL(resizable)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &resizable_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowResizable(win, resizable);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowAlwaysOnTop)
{
	zend_bool on_top, result = 0;
	zval *window_param = NULL, *on_top_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_BOOL(on_top)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &on_top_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowAlwaysOnTop(win, on_top);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowFillDocument)
{
	zend_bool fill, result = 0;
	zval *window_param = NULL, *fill_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_BOOL(fill)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &fill_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowFillDocument(win, fill);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLShowWindow)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_ShowWindow(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLHideWindow)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_HideWindow(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLRaiseWindow)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_RaiseWindow(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLMaximizeWindow)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_MaximizeWindow(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLMinimizeWindow)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_MinimizeWindow(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLRestoreWindow)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_RestoreWindow(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowFullscreen)
{
	zend_bool fullscreen, result = 0;
	zval *window_param = NULL, *fullscreen_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_BOOL(fullscreen)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &fullscreen_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowFullscreen(win, fullscreen);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSyncWindow)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SyncWindow(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLWindowHasSurface)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_WindowHasSurface(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSurface)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0$$3, _1$$3, _2$$3;
	zend_long window, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Surface *surf = SDL_GetWindowSurface(win);
            ptr = (zend_long)(uintptr_t) surf;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_GetWindowSurface failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/video/sdlvideo.zep", 913);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowSurfaceVSync)
{
	zend_bool result = 0;
	zval *window_param = NULL, *vsync_param = NULL;
	zend_long window, vsync;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(vsync)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &vsync_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowSurfaceVSync(win, (int) vsync);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSurfaceVSync)
{
	zend_bool ok = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, vsync;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	vsync = 0;
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int v = 0;
            ok = SDL_GetWindowSurfaceVSync(win, &v);
            vsync = (zend_long) v;
        
	if (!(ok)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 1, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, vsync);
	zephir_array_update_string(return_value, SL("vsync"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLUpdateWindowSurface)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_UpdateWindowSurface(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLUpdateWindowSurfaceRects)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval rects;
	zval *window_param = NULL, *rects_param = NULL;
	zend_long window;

	ZVAL_UNDEF(&rects);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_ARRAY(rects)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &window_param, &rects_param);
	zephir_get_arrval(&rects, rects_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int count = (int) zend_hash_num_elements(Z_ARRVAL_P(&rects));
            SDL_Rect *rect_array = NULL;
            zval *entry;
            int i = 0;

            if (count > 0) {
                rect_array = (SDL_Rect *) emalloc(sizeof(SDL_Rect) * count);
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rects), entry) {
                    if (Z_TYPE_P(entry) == IS_ARRAY && i < count) {
                        zval *x = zend_hash_index_find(Z_ARRVAL_P(entry), 0);
                        zval *y = zend_hash_index_find(Z_ARRVAL_P(entry), 1);
                        zval *w = zend_hash_index_find(Z_ARRVAL_P(entry), 2);
                        zval *h = zend_hash_index_find(Z_ARRVAL_P(entry), 3);
                        rect_array[i].x = x ? (int) zval_get_long(x) : 0;
                        rect_array[i].y = y ? (int) zval_get_long(y) : 0;
                        rect_array[i].w = w ? (int) zval_get_long(w) : 0;
                        rect_array[i].h = h ? (int) zval_get_long(h) : 0;
                        i++;
                    }
                } ZEND_HASH_FOREACH_END();
            }

            result = SDL_UpdateWindowSurfaceRects(win, rect_array, i);
            if (rect_array) {
                efree(rect_array);
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLDestroyWindowSurface)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_DestroyWindowSurface(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowKeyboardGrab)
{
	zend_bool grabbed, result = 0;
	zval *window_param = NULL, *grabbed_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_BOOL(grabbed)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &grabbed_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowKeyboardGrab(win, grabbed);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowMouseGrab)
{
	zend_bool grabbed, result = 0;
	zval *window_param = NULL, *grabbed_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_BOOL(grabbed)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &grabbed_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowMouseGrab(win, grabbed);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowKeyboardGrab)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_GetWindowKeyboardGrab(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowMouseGrab)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_GetWindowMouseGrab(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetGrabbedWindow)
{
	zend_long ptr = 0;
	
            SDL_Window *win = SDL_GetGrabbedWindow();
            ptr = (zend_long)(uintptr_t) win;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowMouseRect)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, *rect = NULL, rect_sub, __$null, r;
	zend_long window;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&r);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &window_param, &rect);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	ZEPHIR_CPY_WRT(&r, rect);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Rect rect_buf, *rp = NULL;

            if (Z_TYPE_P(&r) != IS_NULL && Z_TYPE_P(&r) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(&r), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(&r), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(&r), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(&r), 3);
                rect_buf.x = x ? (int) zval_get_long(x) : 0;
                rect_buf.y = y ? (int) zval_get_long(y) : 0;
                rect_buf.w = w ? (int) zval_get_long(w) : 0;
                rect_buf.h = h ? (int) zval_get_long(h) : 0;
                rp = &rect_buf;
            }

            result = SDL_SetWindowMouseRect(win, rp);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowMouseRect)
{
	zend_bool found = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, x, y, w, h;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            const SDL_Rect *rect = SDL_GetWindowMouseRect(win);
            found = (rect != NULL);
            if (found) {
                x = (zend_long) rect->x;
                y = (zend_long) rect->y;
                w = (zend_long) rect->w;
                h = (zend_long) rect->h;
            }
        
	if (!(found)) {
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

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowOpacity)
{
	zend_bool result = 0;
	double opacity;
	zval *window_param = NULL, *opacity_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_ZVAL(opacity)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &opacity_param);
	opacity = zephir_get_doubleval(opacity_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowOpacity(win, (float) opacity);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowOpacity)
{
	double result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (double) SDL_GetWindowOpacity(win);
        
	RETURN_DOUBLE(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowParent)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, *parent = NULL, parent_sub, __$null, p;
	zend_long window;

	ZVAL_UNDEF(&parent_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&p);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(parent)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &window_param, &parent);
	if (!parent) {
		parent = &parent_sub;
		parent = &__$null;
	}
	ZEPHIR_CPY_WRT(&p, parent);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Window *parent_win = (Z_TYPE_P(&p) == IS_NULL) ? NULL : (SDL_Window *)(uintptr_t) zval_get_long(&p);
            result = SDL_SetWindowParent(win, parent_win);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowModal)
{
	zend_bool modal, result = 0;
	zval *window_param = NULL, *modal_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_BOOL(modal)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &modal_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowModal(win, modal);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowFocusable)
{
	zend_bool focusable, result = 0;
	zval *window_param = NULL, *focusable_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_BOOL(focusable)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &focusable_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowFocusable(win, focusable);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLShowWindowSystemMenu)
{
	zend_bool result = 0;
	zval *window_param = NULL, *x_param = NULL, *y_param = NULL;
	zend_long window, x, y;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &window_param, &x_param, &y_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_ShowWindowSystemMenu(win, (int) x, (int) y);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowHitTest)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, *callback = NULL, callback_sub, __$null, cb;
	zend_long window;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&cb);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &window_param, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	ZEPHIR_CPY_WRT(&cb, callback);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            zend_long win_ptr = (zend_long)(uintptr_t) win;
            php_sdl_hit_test_context *ctx = NULL;
            zval *zv = NULL;

            php_sdl_hit_test_ensure_map();
            zv = zend_hash_index_find(&php_sdl_hit_test_map, (zend_ulong) win_ptr);
            if (zv != NULL) {
                ctx = (php_sdl_hit_test_context *) Z_PTR_P(zv);
                SDL_SetWindowHitTest(win, NULL, NULL);
                php_sdl_hit_test_context_free(ctx);
                zend_hash_index_del(&php_sdl_hit_test_map, (zend_ulong) win_ptr);
            }

            if (Z_TYPE_P(&cb) == IS_NULL) {
                result = SDL_SetWindowHitTest(win, NULL, NULL);
            } else {
                ctx = php_sdl_hit_test_context_alloc(&cb, win_ptr);
                result = SDL_SetWindowHitTest(win, php_sdl_hit_test_bridge, ctx);
                if (result) {
                    zval zstore;
                    ZVAL_PTR(&zstore, ctx);
                    zend_hash_index_update(&php_sdl_hit_test_map, (zend_ulong) win_ptr, &zstore);
                } else {
                    php_sdl_hit_test_context_free(ctx);
                }
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowShape)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, *shape = NULL, shape_sub, __$null, s;
	zend_long window;

	ZVAL_UNDEF(&shape_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&s);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(shape)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &window_param, &shape);
	if (!shape) {
		shape = &shape_sub;
		shape = &__$null;
	}
	ZEPHIR_CPY_WRT(&s, shape);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Surface *shape_surf = (Z_TYPE_P(&s) == IS_NULL) ? NULL : (SDL_Surface *)(uintptr_t) zval_get_long(&s);
            result = SDL_SetWindowShape(win, shape_surf);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLFlashWindow)
{
	zend_bool result = 0;
	zval *window_param = NULL, *operation_param = NULL;
	zend_long window, operation;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(operation)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &operation_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_FlashWindow(win, (SDL_FlashOperation) operation);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowProgressState)
{
	zend_bool result = 0;
	zval *window_param = NULL, *state_param = NULL;
	zend_long window, state;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(state)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &state_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowProgressState(win, (SDL_ProgressState) state);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowProgressState)
{
	zval *window_param = NULL;
	zend_long window, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (zend_long) SDL_GetWindowProgressState(win);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowProgressValue)
{
	zend_bool result = 0;
	double value;
	zval *window_param = NULL, *value_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &value_param);
	value = zephir_get_doubleval(value_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowProgressValue(win, (float) value);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowProgressValue)
{
	double result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (double) SDL_GetWindowProgressValue(win);
        
	RETURN_DOUBLE(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLScreenSaverEnabled)
{
	zend_bool result = 0;
	
            result = SDL_ScreenSaverEnabled();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLEnableScreenSaver)
{
	zend_bool result = 0;
	
            result = SDL_EnableScreenSaver();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLDisableScreenSaver)
{
	zend_bool result = 0;
	
            result = SDL_DisableScreenSaver();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLDestroyWindow)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            zend_long win_ptr = (zend_long)(uintptr_t) win;
            zval *zv = NULL;

            if (php_sdl_hit_test_map_initialized) {
                zv = zend_hash_index_find(&php_sdl_hit_test_map, (zend_ulong) win_ptr);
                if (zv != NULL) {
                    php_sdl_hit_test_context *ctx = (php_sdl_hit_test_context *) Z_PTR_P(zv);
                    php_sdl_hit_test_context_free(ctx);
                    zend_hash_index_del(&php_sdl_hit_test_map, (zend_ulong) win_ptr);
                }
            }

            SDL_DestroyWindow(win);
        
}

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLCreateWindowAndRenderer)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long w, h, flags, window_ptr = 0, renderer_ptr = 0;
	zval *title_param = NULL, *w_param = NULL, *h_param = NULL, *flags_param = NULL, _0;
	zval title;

	ZVAL_UNDEF(&title);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_STR(title)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &title_param, &w_param, &h_param, &flags_param);
	zephir_get_strval(&title, title_param);
	
            SDL_Window   *win = NULL;
            SDL_Renderer *ren = NULL;
            result = SDL_CreateWindowAndRenderer(Z_STRVAL(title), (int) w, (int) h, (SDL_WindowFlags) flags, &win, &ren);
            window_ptr   = (zend_long)(uintptr_t) win;
            renderer_ptr = (zend_long)(uintptr_t) ren;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, window_ptr);
	zephir_array_update_string(return_value, SL("window"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, renderer_ptr);
	zephir_array_update_string(return_value, SL("renderer"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

