namespace Sdl3\SDL\Video;

%{
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
}%

class SDLVideo
{
    public static function SDLGetNumVideoDrivers() -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetNumVideoDrivers();
        }%

        return result;
    }

    public static function SDLGetVideoDriver(int index) -> string
    {
        string result = "";

        %{
            const char *driver = SDL_GetVideoDriver((int) index);
            if (driver) {
                ZVAL_STRING(&result, driver);
            }
        }%

        return result;
    }

    public static function SDLGetCurrentVideoDriver() -> string
    {
        string result = "";

        %{
            const char *driver = SDL_GetCurrentVideoDriver();
            if (driver) {
                ZVAL_STRING(&result, driver);
            }
        }%

        return result;
    }

    public static function SDLGetSystemTheme() -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetSystemTheme();
        }%

        return result;
    }

    public static function SDLGetDisplayProperties(int display_id) -> int
    {
        int props;

        %{
            props = (zend_long) SDL_GetDisplayProperties((SDL_DisplayID) display_id);
        }%

        return props;
    }

    public static function SDLGetDisplayUsableBounds(int display_id) -> array
    {
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;
        bool ok;

        %{
            SDL_Rect rect;
            ok = SDL_GetDisplayUsableBounds((SDL_DisplayID) display_id, &rect);
            if (ok) {
                x = (zend_long) rect.x;
                y = (zend_long) rect.y;
                w = (zend_long) rect.w;
                h = (zend_long) rect.h;
            }
        }%

        if !ok {
            return [];
        }

        return ["x": x, "y": y, "w": w, "h": h];
    }

    public static function SDLGetDisplayForPoint(int x, int y) -> int
    {
        int result;

        %{
            SDL_Point point = { (int) x, (int) y };
            result = (zend_long) SDL_GetDisplayForPoint(&point);
        }%

        return result;
    }

    public static function SDLGetDisplayForRect(array rect) -> int
    {
        int result;

        %{
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
        }%

        return result;
    }

    public static function SDLCreateWindow(string title, int width, int height, int flags) -> int
    {
        int ptr;

        %{
            SDL_Window *window = SDL_CreateWindow(Z_STRVAL(title), (int) width, (int) height, (SDL_WindowFlags) flags);
            ptr = (zend_long)(uintptr_t) window;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateWindow failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLCreatePopupWindow(int parent, int offset_x, int offset_y, int w, int h, int flags) -> int
    {
        int ptr;

        %{
            SDL_Window *parent_win = (SDL_Window *)(uintptr_t) parent;
            SDL_Window *window = SDL_CreatePopupWindow(parent_win, (int) offset_x, (int) offset_y, (int) w, (int) h, (SDL_WindowFlags) flags);
            ptr = (zend_long)(uintptr_t) window;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreatePopupWindow failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLCreateWindowWithProperties(int props) -> int
    {
        int ptr;

        %{
            SDL_Window *window = SDL_CreateWindowWithProperties((SDL_PropertiesID) props);
            ptr = (zend_long)(uintptr_t) window;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateWindowWithProperties failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLGetWindowID(int window) -> int
    {
        int result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (zend_long) SDL_GetWindowID(win);
        }%

        return result;
    }

    public static function SDLGetWindowFromID(int id) -> int
    {
        int ptr;

        %{
            SDL_Window *win = SDL_GetWindowFromID((SDL_WindowID) id);
            ptr = (zend_long)(uintptr_t) win;
        }%

        return ptr;
    }

    public static function SDLGetWindowParent(int window) -> int
    {
        int ptr;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Window *parent = SDL_GetWindowParent(win);
            ptr = (zend_long)(uintptr_t) parent;
        }%

        return ptr;
    }

    public static function SDLGetWindowProperties(int window) -> int
    {
        int props;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            props = (zend_long) SDL_GetWindowProperties(win);
        }%

        return props;
    }

    public static function SDLGetWindowFlags(int window) -> int
    {
        int result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (zend_long) SDL_GetWindowFlags(win);
        }%

        return result;
    }

    public static function SDLGetWindows() -> array
    {
        array result;

        %{
            int count = 0;
            SDL_Window **windows = SDL_GetWindows(&count);

            array_init(&result);
            if (windows != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long)(uintptr_t) windows[i]);
                }
                SDL_free(windows);
            }
        }%

        return result;
    }

    public static function SDLGetWindowPixelDensity(int window) -> double
    {
        double result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (double) SDL_GetWindowPixelDensity(win);
        }%

        return result;
    }

    public static function SDLGetWindowDisplayScale(int window) -> double
    {
        double result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (double) SDL_GetWindowDisplayScale(win);
        }%

        return result;
    }

    public static function SDLSetWindowFullscreenMode(int window, array mode) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_DisplayMode dm;
            if (php_sdl_display_mode_from_array(&mode, &dm)) {
                result = SDL_SetWindowFullscreenMode(win, &dm);
            } else {
                result = false;
            }
        }%

        return result;
    }

    public static function SDLGetWindowFullscreenMode(int window) -> array
    {
        int mode_display_id = 0;
        int mode_format = 0;
        int mode_w = 0;
        int mode_h = 0;
        double mode_pixel_density = 0.0;
        double mode_refresh_rate = 0.0;
        int mode_refresh_rate_numerator = 0;
        int mode_refresh_rate_denominator = 0;
        bool found;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            const SDL_DisplayMode *mode = SDL_GetWindowFullscreenMode(win);
            found = (mode != NULL);
            if (found) {
                php_sdl_display_mode_to_zvals(mode,
                    &mode_display_id, &mode_format, &mode_w, &mode_h,
                    &mode_pixel_density, &mode_refresh_rate,
                    &mode_refresh_rate_numerator, &mode_refresh_rate_denominator);
            }
        }%

        if !found {
            return [];
        }

        return [
            "display_id": mode_display_id,
            "format": mode_format,
            "w": mode_w,
            "h": mode_h,
            "pixel_density": mode_pixel_density,
            "refresh_rate": mode_refresh_rate,
            "refresh_rate_numerator": mode_refresh_rate_numerator,
            "refresh_rate_denominator": mode_refresh_rate_denominator
        ];
    }

    public static function SDLGetWindowICCProfile(int window) -> string
    {
        string result = "";

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            size_t size = 0;
            void *data = SDL_GetWindowICCProfile(win, &size);
            if (data != NULL && size > 0) {
                ZVAL_STRINGL(&result, (char *) data, (size_t) size);
            }
        }%

        return result;
    }

    public static function SDLGetWindowPixelFormat(int window) -> int
    {
        int result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (zend_long) SDL_GetWindowPixelFormat(win);
        }%

        return result;
    }

    public static function SDLSetWindowTitle(int window, string title) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowTitle(win, Z_STRVAL(title));
        }%

        return result;
    }

    public static function SDLGetWindowTitle(int window) -> string
    {
        string result = "";

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            const char *title = SDL_GetWindowTitle(win);
            if (title) {
                ZVAL_STRING(&result, title);
            }
        }%

        return result;
    }

    public static function SDLSetWindowIcon(int window, int surface) -> bool
    {
        bool result;

        %{
            SDL_Window  *win  = (SDL_Window *)(uintptr_t) window;
            SDL_Surface *icon = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetWindowIcon(win, icon);
        }%

        return result;
    }

    public static function SDLSetWindowPosition(int window, int x, int y) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowPosition(win, (int) x, (int) y);
        }%

        return result;
    }

    public static function SDLGetWindowPosition(int window) -> array
    {
        int x;
        int y;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int wx = 0, wy = 0;
            SDL_GetWindowPosition(win, &wx, &wy);
            x = (zend_long) wx;
            y = (zend_long) wy;
        }%

        return [x, y];
    }

    public static function SDLSetWindowSize(int window, int w, int h) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowSize(win, (int) w, (int) h);
        }%

        return result;
    }

    public static function SDLGetWindowSize(int window) -> array
    {
        int w;
        int h;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int ww = 0, wh = 0;
            SDL_GetWindowSize(win, &ww, &wh);
            w = (zend_long) ww;
            h = (zend_long) wh;
        }%

        return [w, h];
    }

    public static function SDLGetWindowSafeArea(int window) -> array
    {
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;
        bool ok;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Rect rect;
            ok = SDL_GetWindowSafeArea(win, &rect);
            if (ok) {
                x = (zend_long) rect.x;
                y = (zend_long) rect.y;
                w = (zend_long) rect.w;
                h = (zend_long) rect.h;
            }
        }%

        if !ok {
            return [];
        }

        return ["x": x, "y": y, "w": w, "h": h];
    }

    public static function SDLSetWindowAspectRatio(int window, double min_aspect, double max_aspect) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowAspectRatio(win, (float) min_aspect, (float) max_aspect);
        }%

        return result;
    }

    public static function SDLGetWindowAspectRatio(int window) -> array
    {
        double min_aspect;
        double max_aspect;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            float mn = 0.0f, mx = 0.0f;
            SDL_GetWindowAspectRatio(win, &mn, &mx);
            min_aspect = (double) mn;
            max_aspect = (double) mx;
        }%

        return [min_aspect, max_aspect];
    }

    public static function SDLGetWindowBordersSize(int window) -> array
    {
        int top = 0;
        int left = 0;
        int bottom = 0;
        int right = 0;
        bool ok;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int t = 0, l = 0, b = 0, r = 0;
            ok = SDL_GetWindowBordersSize(win, &t, &l, &b, &r);
            if (ok) {
                top = (zend_long) t;
                left = (zend_long) l;
                bottom = (zend_long) b;
                right = (zend_long) r;
            }
        }%

        if !ok {
            return [];
        }

        return ["top": top, "left": left, "bottom": bottom, "right": right];
    }

    public static function SDLGetWindowSizeInPixels(int window) -> array
    {
        int w;
        int h;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int pw = 0, ph = 0;
            SDL_GetWindowSizeInPixels(win, &pw, &ph);
            w = (zend_long) pw;
            h = (zend_long) ph;
        }%

        return [w, h];
    }

    public static function SDLSetWindowMinimumSize(int window, int min_w, int min_h) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowMinimumSize(win, (int) min_w, (int) min_h);
        }%

        return result;
    }

    public static function SDLGetWindowMinimumSize(int window) -> array
    {
        int min_w;
        int min_h;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int pw = 0, ph = 0;
            SDL_GetWindowMinimumSize(win, &pw, &ph);
            min_w = (zend_long) pw;
            min_h = (zend_long) ph;
        }%

        return [min_w, min_h];
    }

    public static function SDLSetWindowMaximumSize(int window, int max_w, int max_h) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowMaximumSize(win, (int) max_w, (int) max_h);
        }%

        return result;
    }

    public static function SDLGetWindowMaximumSize(int window) -> array
    {
        int max_w;
        int max_h;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int pw = 0, ph = 0;
            SDL_GetWindowMaximumSize(win, &pw, &ph);
            max_w = (zend_long) pw;
            max_h = (zend_long) ph;
        }%

        return [max_w, max_h];
    }

    public static function SDLSetWindowBordered(int window, bool bordered) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowBordered(win, bordered);
        }%

        return result;
    }

    public static function SDLSetWindowResizable(int window, bool resizable) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowResizable(win, resizable);
        }%

        return result;
    }

    public static function SDLSetWindowAlwaysOnTop(int window, bool on_top) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowAlwaysOnTop(win, on_top);
        }%

        return result;
    }

    public static function SDLSetWindowFillDocument(int window, bool fill) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowFillDocument(win, fill);
        }%

        return result;
    }

    public static function SDLShowWindow(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_ShowWindow(win);
        }%

        return result;
    }

    public static function SDLHideWindow(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_HideWindow(win);
        }%

        return result;
    }

    public static function SDLRaiseWindow(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_RaiseWindow(win);
        }%

        return result;
    }

    public static function SDLMaximizeWindow(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_MaximizeWindow(win);
        }%

        return result;
    }

    public static function SDLMinimizeWindow(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_MinimizeWindow(win);
        }%

        return result;
    }

    public static function SDLRestoreWindow(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_RestoreWindow(win);
        }%

        return result;
    }

    public static function SDLSetWindowFullscreen(int window, bool fullscreen) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowFullscreen(win, fullscreen);
        }%

        return result;
    }

    public static function SDLSyncWindow(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SyncWindow(win);
        }%

        return result;
    }

    public static function SDLWindowHasSurface(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_WindowHasSurface(win);
        }%

        return result;
    }

    public static function SDLGetWindowSurface(int window) -> int
    {
        int ptr;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Surface *surf = SDL_GetWindowSurface(win);
            ptr = (zend_long)(uintptr_t) surf;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_GetWindowSurface failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLSetWindowSurfaceVSync(int window, int vsync) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowSurfaceVSync(win, (int) vsync);
        }%

        return result;
    }

    public static function SDLGetWindowSurfaceVSync(int window) -> array
    {
        int vsync = 0;
        bool ok;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            int v = 0;
            ok = SDL_GetWindowSurfaceVSync(win, &v);
            vsync = (zend_long) v;
        }%

        if !ok {
            return [];
        }

        return ["vsync": vsync];
    }

    public static function SDLUpdateWindowSurface(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_UpdateWindowSurface(win);
        }%

        return result;
    }

    public static function SDLUpdateWindowSurfaceRects(int window, array rects) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLDestroyWindowSurface(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_DestroyWindowSurface(win);
        }%

        return result;
    }

    public static function SDLSetWindowKeyboardGrab(int window, bool grabbed) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowKeyboardGrab(win, grabbed);
        }%

        return result;
    }

    public static function SDLSetWindowMouseGrab(int window, bool grabbed) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowMouseGrab(win, grabbed);
        }%

        return result;
    }

    public static function SDLGetWindowKeyboardGrab(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_GetWindowKeyboardGrab(win);
        }%

        return result;
    }

    public static function SDLGetWindowMouseGrab(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_GetWindowMouseGrab(win);
        }%

        return result;
    }

    public static function SDLGetGrabbedWindow() -> int
    {
        int ptr;

        %{
            SDL_Window *win = SDL_GetGrabbedWindow();
            ptr = (zend_long)(uintptr_t) win;
        }%

        return ptr;
    }

    public static function SDLSetWindowMouseRect(int window, var rect = null) -> bool
    {
        bool result;
        var r;

        let r = rect;

        %{
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
        }%

        return result;
    }

    public static function SDLGetWindowMouseRect(int window) -> array
    {
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;
        bool found;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            const SDL_Rect *rect = SDL_GetWindowMouseRect(win);
            found = (rect != NULL);
            if (found) {
                x = (zend_long) rect->x;
                y = (zend_long) rect->y;
                w = (zend_long) rect->w;
                h = (zend_long) rect->h;
            }
        }%

        if !found {
            return [];
        }

        return ["x": x, "y": y, "w": w, "h": h];
    }

    public static function SDLSetWindowOpacity(int window, double opacity) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowOpacity(win, (float) opacity);
        }%

        return result;
    }

    public static function SDLGetWindowOpacity(int window) -> double
    {
        double result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (double) SDL_GetWindowOpacity(win);
        }%

        return result;
    }

    public static function SDLSetWindowParent(int window, var parent = null) -> bool
    {
        bool result;
        var p;

        let p = parent;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Window *parent_win = (Z_TYPE_P(&p) == IS_NULL) ? NULL : (SDL_Window *)(uintptr_t) zval_get_long(&p);
            result = SDL_SetWindowParent(win, parent_win);
        }%

        return result;
    }

    public static function SDLSetWindowModal(int window, bool modal) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowModal(win, modal);
        }%

        return result;
    }

    public static function SDLSetWindowFocusable(int window, bool focusable) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowFocusable(win, focusable);
        }%

        return result;
    }

    public static function SDLShowWindowSystemMenu(int window, int x, int y) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_ShowWindowSystemMenu(win, (int) x, (int) y);
        }%

        return result;
    }

    public static function SDLSetWindowHitTest(int window, var callback = null) -> bool
    {
        bool result;
        var cb;

        let cb = callback;

        %{
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
        }%

        return result;
    }

    public static function SDLSetWindowShape(int window, var shape = null) -> bool
    {
        bool result;
        var s;

        let s = shape;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Surface *shape_surf = (Z_TYPE_P(&s) == IS_NULL) ? NULL : (SDL_Surface *)(uintptr_t) zval_get_long(&s);
            result = SDL_SetWindowShape(win, shape_surf);
        }%

        return result;
    }

    public static function SDLFlashWindow(int window, int operation) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_FlashWindow(win, (SDL_FlashOperation) operation);
        }%

        return result;
    }

    public static function SDLSetWindowProgressState(int window, int state) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowProgressState(win, (SDL_ProgressState) state);
        }%

        return result;
    }

    public static function SDLGetWindowProgressState(int window) -> int
    {
        int result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (zend_long) SDL_GetWindowProgressState(win);
        }%

        return result;
    }

    public static function SDLSetWindowProgressValue(int window, double value) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowProgressValue(win, (float) value);
        }%

        return result;
    }

    public static function SDLGetWindowProgressValue(int window) -> double
    {
        double result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (double) SDL_GetWindowProgressValue(win);
        }%

        return result;
    }

    public static function SDLScreenSaverEnabled() -> bool
    {
        bool result;

        %{
            result = SDL_ScreenSaverEnabled();
        }%

        return result;
    }

    public static function SDLEnableScreenSaver() -> bool
    {
        bool result;

        %{
            result = SDL_EnableScreenSaver();
        }%

        return result;
    }

    public static function SDLDisableScreenSaver() -> bool
    {
        bool result;

        %{
            result = SDL_DisableScreenSaver();
        }%

        return result;
    }

    public static function SDLDestroyWindow(int window) -> void
    {
        %{
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
        }%
    }

    public static function SDLCreateWindowAndRenderer(string title, int w, int h, int flags) -> array
    {
        int window_ptr;
        int renderer_ptr;
        bool result;

        %{
            SDL_Window   *win = NULL;
            SDL_Renderer *ren = NULL;
            result = SDL_CreateWindowAndRenderer(Z_STRVAL(title), (int) w, (int) h, (SDL_WindowFlags) flags, &win, &ren);
            window_ptr   = (zend_long)(uintptr_t) win;
            renderer_ptr = (zend_long)(uintptr_t) ren;
        }%

        if !result {
            return [];
        }

        return ["window": window_ptr, "renderer": renderer_ptr];
    }
}
