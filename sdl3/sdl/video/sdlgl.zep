namespace Sdl3\SDL\Video;

%{
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
}%

class SDLGL
{
    public static function SDLGLLoadLibrary(var path = null) -> bool
    {
        bool result;
        var p;

        let p = path;

        %{
            const char *libpath = (Z_TYPE_P(&p) == IS_NULL) ? NULL : Z_STRVAL(p);
            result = SDL_GL_LoadLibrary(libpath);
        }%

        return result;
    }

    public static function SDLGLGetProcAddress(string proc) -> int
    {
        int ptr;

        %{
            SDL_FunctionPointer fn = SDL_GL_GetProcAddress(Z_STRVAL(proc));
            ptr = (zend_long)(uintptr_t) fn;
        }%

        return ptr;
    }

    public static function SDLGLUnloadLibrary() -> void
    {
        %{
            SDL_GL_UnloadLibrary();
        }%
    }

    public static function SDLGLExtensionSupported(string extension) -> bool
    {
        bool result;

        %{
            result = SDL_GL_ExtensionSupported(Z_STRVAL(extension));
        }%

        return result;
    }

    public static function SDLGLResetAttributes() -> void
    {
        %{
            php_sdl_egl_callbacks_clear();
            SDL_GL_ResetAttributes();
        }%
    }

    public static function SDLGLSetAttribute(int attr, int value) -> bool
    {
        bool result;

        %{
            result = SDL_GL_SetAttribute((SDL_GLAttr) attr, (int) value);
        }%

        return result;
    }

    public static function SDLGLGetAttribute(int attr) -> array
    {
        int value = 0;
        bool ok;

        %{
            int v = 0;
            ok = SDL_GL_GetAttribute((SDL_GLAttr) attr, &v);
            value = (zend_long) v;
        }%

        if !ok {
            return [];
        }

        return ["value": value];
    }

    public static function SDLGLCreateContext(int window) -> int
    {
        int ptr;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_GLContext ctx = SDL_GL_CreateContext(win);
            ptr = (zend_long)(uintptr_t) ctx;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_GL_CreateContext failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLGLMakeCurrent(int window, int context) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (window == 0) ? NULL : (SDL_Window *)(uintptr_t) window;
            SDL_GLContext ctx = (context == 0) ? NULL : (SDL_GLContext)(uintptr_t) context;
            result = SDL_GL_MakeCurrent(win, ctx);
        }%

        return result;
    }

    public static function SDLGLGetCurrentWindow() -> int
    {
        int ptr;

        %{
            SDL_Window *win = SDL_GL_GetCurrentWindow();
            ptr = (zend_long)(uintptr_t) win;
        }%

        return ptr;
    }

    public static function SDLGLGetCurrentContext() -> int
    {
        int ptr;

        %{
            SDL_GLContext ctx = SDL_GL_GetCurrentContext();
            ptr = (zend_long)(uintptr_t) ctx;
        }%

        return ptr;
    }

    public static function SDLGLSetSwapInterval(int interval) -> bool
    {
        bool result;

        %{
            result = SDL_GL_SetSwapInterval((int) interval);
        }%

        return result;
    }

    public static function SDLGLGetSwapInterval() -> array
    {
        int interval = 0;
        bool ok;

        %{
            int v = 0;
            ok = SDL_GL_GetSwapInterval(&v);
            interval = (zend_long) v;
        }%

        if !ok {
            return [];
        }

        return ["interval": interval];
    }

    public static function SDLGLSwapWindow(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_GL_SwapWindow(win);
        }%

        return result;
    }

    public static function SDLGLDestroyContext(int context) -> bool
    {
        bool result;

        %{
            SDL_GLContext ctx = (SDL_GLContext)(uintptr_t) context;
            result = SDL_GL_DestroyContext(ctx);
        }%

        return result;
    }

    public static function SDLEGLGetProcAddress(string proc) -> int
    {
        int ptr;

        %{
            SDL_FunctionPointer fn = SDL_EGL_GetProcAddress(Z_STRVAL(proc));
            ptr = (zend_long)(uintptr_t) fn;
        }%

        return ptr;
    }

    public static function SDLEGLGetCurrentDisplay() -> int
    {
        int ptr;

        %{
            SDL_EGLDisplay display = SDL_EGL_GetCurrentDisplay();
            ptr = (zend_long)(uintptr_t) display;
        }%

        return ptr;
    }

    public static function SDLEGLGetCurrentConfig() -> int
    {
        int ptr;

        %{
            SDL_EGLConfig config = SDL_EGL_GetCurrentConfig();
            ptr = (zend_long)(uintptr_t) config;
        }%

        return ptr;
    }

    public static function SDLEGLGetWindowSurface(int window) -> int
    {
        int ptr;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_EGLSurface surface = SDL_EGL_GetWindowSurface(win);
            ptr = (zend_long)(uintptr_t) surface;
        }%

        return ptr;
    }

    public static function SDLEGLSetAttributeCallbacks(var platformCallback = null, var surfaceCallback = null, var contextCallback = null) -> void
    {
        var platformCb;
        var surfaceCb;
        var contextCb;

        let platformCb = platformCallback;
        let surfaceCb = surfaceCallback;
        let contextCb = contextCallback;

        %{
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
        }%
    }
}
