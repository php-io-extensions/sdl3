
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
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"

#include <SDL3/SDL.h>
#include <stdio.h>

#ifndef EGL_NONE
#define EGL_NONE 0x3038
#endif

typedef struct _php_sdl_egl_callbacks {
    zval platform_callback;
    zval surface_callback;
    zval context_callback;
    bool platform_set;
    bool surface_set;
    bool context_set;
} php_sdl_egl_callbacks;

static php_sdl_egl_callbacks php_sdl_egl_callbacks_state;

static void php_sdl_egl_callbacks_clear(void)
{
    if (php_sdl_egl_callbacks_state.platform_set) {
        zval_ptr_dtor(&php_sdl_egl_callbacks_state.platform_callback);
        ZVAL_UNDEF(&php_sdl_egl_callbacks_state.platform_callback);
        php_sdl_egl_callbacks_state.platform_set = false;
    }
    if (php_sdl_egl_callbacks_state.surface_set) {
        zval_ptr_dtor(&php_sdl_egl_callbacks_state.surface_callback);
        ZVAL_UNDEF(&php_sdl_egl_callbacks_state.surface_callback);
        php_sdl_egl_callbacks_state.surface_set = false;
    }
    if (php_sdl_egl_callbacks_state.context_set) {
        zval_ptr_dtor(&php_sdl_egl_callbacks_state.context_callback);
        ZVAL_UNDEF(&php_sdl_egl_callbacks_state.context_callback);
        php_sdl_egl_callbacks_state.context_set = false;
    }
}

static SDL_EGLAttrib *php_sdl_egl_attrib_array_from_zval(zval *retval)
{
    HashTable *ht;
    zend_ulong num_key;
    zend_string *str_key;
    zval *entry;
    SDL_EGLAttrib *attrs;
    int count = 0;
    int i = 0;

    if (retval == NULL || Z_TYPE_P(retval) != IS_ARRAY) {
        return NULL;
    }

    ht = Z_ARRVAL_P(retval);
    count = (int) zend_hash_num_elements(ht);
    if (count <= 0) {
        return NULL;
    }

    attrs = (SDL_EGLAttrib *) SDL_malloc((size_t) (count + 1) * sizeof(SDL_EGLAttrib));
    if (attrs == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_KEY_VAL(ht, num_key, str_key, entry) {
        if (i < count) {
            attrs[i++] = (SDL_EGLAttrib) zval_get_long(entry);
        }
    } ZEND_HASH_FOREACH_END();

    attrs[i] = (SDL_EGLAttrib) EGL_NONE;
    return attrs;
}

static SDL_EGLint *php_sdl_egl_int_array_from_zval(zval *retval)
{
    HashTable *ht;
    zend_ulong num_key;
    zend_string *str_key;
    zval *entry;
    SDL_EGLint *attrs;
    int count = 0;
    int i = 0;

    if (retval == NULL || Z_TYPE_P(retval) != IS_ARRAY) {
        return NULL;
    }

    ht = Z_ARRVAL_P(retval);
    count = (int) zend_hash_num_elements(ht);
    if (count <= 0) {
        return NULL;
    }

    attrs = (SDL_EGLint *) SDL_malloc((size_t) (count + 1) * sizeof(SDL_EGLint));
    if (attrs == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_KEY_VAL(ht, num_key, str_key, entry) {
        if (i < count) {
            attrs[i++] = (SDL_EGLint) zval_get_long(entry);
        }
    } ZEND_HASH_FOREACH_END();

    attrs[i] = (SDL_EGLint) EGL_NONE;
    return attrs;
}

static SDL_EGLAttrib *SDLCALL php_sdl_egl_platform_attrib_bridge(void *userdata)
{
    zval retval;
    SDL_EGLAttrib *attrs = NULL;

    (void) userdata;

    if (!php_sdl_egl_callbacks_state.platform_set) {
        return NULL;
    }

    ZVAL_UNDEF(&retval);
    if (call_user_function(EG(function_table), NULL, &php_sdl_egl_callbacks_state.platform_callback, &retval, 0, NULL) == SUCCESS) {
        attrs = php_sdl_egl_attrib_array_from_zval(&retval);
    }

    if (!Z_ISUNDEF(retval)) {
        zval_ptr_dtor(&retval);
    }

    return attrs;
}

static SDL_EGLint *SDLCALL php_sdl_egl_surface_attrib_bridge(void *userdata, SDL_EGLDisplay display, SDL_EGLConfig config)
{
    zval retval;
    zval params[2];
    SDL_EGLint *attrs = NULL;

    (void) userdata;

    if (!php_sdl_egl_callbacks_state.surface_set) {
        return NULL;
    }

    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) display);
    ZVAL_LONG(&params[1], (zend_long)(uintptr_t) config);
    ZVAL_UNDEF(&retval);

    if (call_user_function(EG(function_table), NULL, &php_sdl_egl_callbacks_state.surface_callback, &retval, 2, params) == SUCCESS) {
        attrs = php_sdl_egl_int_array_from_zval(&retval);
    }

    if (!Z_ISUNDEF(retval)) {
        zval_ptr_dtor(&retval);
    }

    return attrs;
}

static SDL_EGLint *SDLCALL php_sdl_egl_context_attrib_bridge(void *userdata, SDL_EGLDisplay display, SDL_EGLConfig config)
{
    zval retval;
    zval params[2];
    SDL_EGLint *attrs = NULL;

    (void) userdata;

    if (!php_sdl_egl_callbacks_state.context_set) {
        return NULL;
    }

    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) display);
    ZVAL_LONG(&params[1], (zend_long)(uintptr_t) config);
    ZVAL_UNDEF(&retval);

    if (call_user_function(EG(function_table), NULL, &php_sdl_egl_callbacks_state.context_callback, &retval, 2, params) == SUCCESS) {
        attrs = php_sdl_egl_int_array_from_zval(&retval);
    }

    if (!Z_ISUNDEF(retval)) {
        zval_ptr_dtor(&retval);
    }

    return attrs;
}



ZEPHIR_INIT_CLASS(Sdl3_SDL_Video_SDLGL)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Video, SDLGL, sdl3, sdl_video_sdlgl, sdl3_sdl_video_sdlgl_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLLoadLibrary)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *path = NULL, path_sub, __$null, p;

	ZVAL_UNDEF(&path_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&p);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &path);
	if (!path) {
		path = &path_sub;
		path = &__$null;
	}
	ZEPHIR_CPY_WRT(&p, path);
	
            const char *libpath = (Z_TYPE_P(&p) == IS_NULL) ? NULL : Z_STRVAL(p);
            result = SDL_GL_LoadLibrary(libpath);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLGetProcAddress)
{
	zend_long ptr = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *proc_param = NULL;
	zval proc;

	ZVAL_UNDEF(&proc);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(proc)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &proc_param);
	zephir_get_strval(&proc, proc_param);
	
            SDL_FunctionPointer fn = SDL_GL_GetProcAddress(Z_STRVAL(proc));
            ptr = (zend_long)(uintptr_t) fn;
        
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLUnloadLibrary)
{

	
            SDL_GL_UnloadLibrary();
        
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLExtensionSupported)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *extension_param = NULL;
	zval extension;

	ZVAL_UNDEF(&extension);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(extension)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &extension_param);
	zephir_get_strval(&extension, extension_param);
	
            result = SDL_GL_ExtensionSupported(Z_STRVAL(extension));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLResetAttributes)
{

	
            php_sdl_egl_callbacks_clear();
            SDL_GL_ResetAttributes();
        
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLSetAttribute)
{
	zend_bool result = 0;
	zval *attr_param = NULL, *value_param = NULL;
	zend_long attr, value;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(attr)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &attr_param, &value_param);
	
            result = SDL_GL_SetAttribute((SDL_GLAttr) attr, (int) value);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLGetAttribute)
{
	zend_bool ok = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *attr_param = NULL, _0;
	zend_long attr, value;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(attr)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &attr_param);
	value = 0;
	
            int v = 0;
            ok = SDL_GL_GetAttribute((SDL_GLAttr) attr, &v);
            value = (zend_long) v;
        
	if (!(ok)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 1, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, value);
	zephir_array_update_string(return_value, SL("value"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLCreateContext)
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
            SDL_GLContext ctx = SDL_GL_CreateContext(win);
            ptr = (zend_long)(uintptr_t) ctx;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_GL_CreateContext failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/video/sdlgl.zep", 283);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLMakeCurrent)
{
	zend_bool result = 0;
	zval *window_param = NULL, *context_param = NULL;
	zend_long window, context;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(context)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &context_param);
	
            SDL_Window *win = (window == 0) ? NULL : (SDL_Window *)(uintptr_t) window;
            SDL_GLContext ctx = (context == 0) ? NULL : (SDL_GLContext)(uintptr_t) context;
            result = SDL_GL_MakeCurrent(win, ctx);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLGetCurrentWindow)
{
	zend_long ptr = 0;
	
            SDL_Window *win = SDL_GL_GetCurrentWindow();
            ptr = (zend_long)(uintptr_t) win;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLGetCurrentContext)
{
	zend_long ptr = 0;
	
            SDL_GLContext ctx = SDL_GL_GetCurrentContext();
            ptr = (zend_long)(uintptr_t) ctx;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLSetSwapInterval)
{
	zend_bool result = 0;
	zval *interval_param = NULL;
	zend_long interval;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(interval)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &interval_param);
	
            result = SDL_GL_SetSwapInterval((int) interval);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLGetSwapInterval)
{
	zval _0;
	zend_bool ok = 0;
	zend_long interval;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	interval = 0;
	
            int v = 0;
            ok = SDL_GL_GetSwapInterval(&v);
            interval = (zend_long) v;
        
	if (!(ok)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 1, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, interval);
	zephir_array_update_string(return_value, SL("interval"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLSwapWindow)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_GL_SwapWindow(win);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLDestroyContext)
{
	zend_bool result = 0;
	zval *context_param = NULL;
	zend_long context;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(context)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &context_param);
	
            SDL_GLContext ctx = (SDL_GLContext)(uintptr_t) context;
            result = SDL_GL_DestroyContext(ctx);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLEGLGetProcAddress)
{
	zend_long ptr = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *proc_param = NULL;
	zval proc;

	ZVAL_UNDEF(&proc);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(proc)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &proc_param);
	zephir_get_strval(&proc, proc_param);
	
            SDL_FunctionPointer fn = SDL_EGL_GetProcAddress(Z_STRVAL(proc));
            ptr = (zend_long)(uintptr_t) fn;
        
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLEGLGetCurrentDisplay)
{
	zend_long ptr = 0;
	
            SDL_EGLDisplay display = SDL_EGL_GetCurrentDisplay();
            ptr = (zend_long)(uintptr_t) display;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLEGLGetCurrentConfig)
{
	zend_long ptr = 0;
	
            SDL_EGLConfig config = SDL_EGL_GetCurrentConfig();
            ptr = (zend_long)(uintptr_t) config;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLEGLGetWindowSurface)
{
	zval *window_param = NULL;
	zend_long window, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_EGLSurface surface = SDL_EGL_GetWindowSurface(win);
            ptr = (zend_long)(uintptr_t) surface;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLEGLSetAttributeCallbacks)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *platformCallback = NULL, platformCallback_sub, *surfaceCallback = NULL, surfaceCallback_sub, *contextCallback = NULL, contextCallback_sub, __$null, platformCb, surfaceCb, contextCb;

	ZVAL_UNDEF(&platformCallback_sub);
	ZVAL_UNDEF(&surfaceCallback_sub);
	ZVAL_UNDEF(&contextCallback_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&platformCb);
	ZVAL_UNDEF(&surfaceCb);
	ZVAL_UNDEF(&contextCb);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 3)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(platformCallback)
		Z_PARAM_ZVAL_OR_NULL(surfaceCallback)
		Z_PARAM_ZVAL_OR_NULL(contextCallback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 3, &platformCallback, &surfaceCallback, &contextCallback);
	if (!platformCallback) {
		platformCallback = &platformCallback_sub;
		platformCallback = &__$null;
	}
	if (!surfaceCallback) {
		surfaceCallback = &surfaceCallback_sub;
		surfaceCallback = &__$null;
	}
	if (!contextCallback) {
		contextCallback = &contextCallback_sub;
		contextCallback = &__$null;
	}
	ZEPHIR_CPY_WRT(&platformCb, platformCallback);
	ZEPHIR_CPY_WRT(&surfaceCb, surfaceCallback);
	ZEPHIR_CPY_WRT(&contextCb, contextCallback);
	
            SDL_EGLAttribArrayCallback platform_cb = NULL;
            SDL_EGLIntArrayCallback surface_cb = NULL;
            SDL_EGLIntArrayCallback context_cb = NULL;

            php_sdl_egl_callbacks_clear();

            if (Z_TYPE_P(&platformCb) != IS_NULL) {
                ZVAL_COPY(&php_sdl_egl_callbacks_state.platform_callback, &platformCb);
                php_sdl_egl_callbacks_state.platform_set = true;
                platform_cb = php_sdl_egl_platform_attrib_bridge;
            }

            if (Z_TYPE_P(&surfaceCb) != IS_NULL) {
                ZVAL_COPY(&php_sdl_egl_callbacks_state.surface_callback, &surfaceCb);
                php_sdl_egl_callbacks_state.surface_set = true;
                surface_cb = php_sdl_egl_surface_attrib_bridge;
            }

            if (Z_TYPE_P(&contextCb) != IS_NULL) {
                ZVAL_COPY(&php_sdl_egl_callbacks_state.context_callback, &contextCb);
                php_sdl_egl_callbacks_state.context_set = true;
                context_cb = php_sdl_egl_context_attrib_bridge;
            }

            SDL_EGL_SetAttributeCallbacks(platform_cb, surface_cb, context_cb, NULL);
        
	ZEPHIR_MM_RESTORE();
}

