namespace Sdl3\SDL\Events;

%{
#include <SDL3/SDL.h>
#include <stdio.h>
}%

class SDLDisplayEvents
{
    public static function SDLReadDisplayEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_DisplayEvent *dev = &event->display;

            array_init(&result);
            add_assoc_long(&result, "type",       (zend_long) dev->type);
            add_assoc_long(&result, "timestamp",  (zend_long) dev->timestamp);
            add_assoc_long(&result, "display_id", (zend_long) dev->displayID);
            add_assoc_long(&result, "data1",      (zend_long) dev->data1);
            add_assoc_long(&result, "data2",      (zend_long) dev->data2);

            efree(event);
        }%

        return result;
    }

    public static function SDLGetDisplays() -> array
    {
        array result;

        %{
            int count = 0;
            SDL_DisplayID *displays = SDL_GetDisplays(&count);

            array_init(&result);
            if (displays != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) displays[i]);
                }
                SDL_free(displays);
            }
        }%

        return result;
    }

    public static function SDLGetPrimaryDisplay() -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetPrimaryDisplay();
        }%

        return result;
    }

    public static function SDLGetDisplayName(int display_id) -> string
    {
        string result = "";

        %{
            const char *name = SDL_GetDisplayName((SDL_DisplayID) display_id);
            if (name) {
                ZVAL_STRING(&result, name);
            }
        }%

        return result;
    }

    public static function SDLGetDisplayBounds(int display_id) -> array
    {
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;
        bool ok;

        %{
            SDL_Rect rect;
            ok = SDL_GetDisplayBounds((SDL_DisplayID) display_id, &rect);
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

        return [
            "x": x,
            "y": y,
            "w": w,
            "h": h
        ];
    }

    public static function SDLGetDisplayForWindow(int window) -> int
    {
        int result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = (zend_long) SDL_GetDisplayForWindow(win);
        }%

        return result;
    }

    public static function SDLGetNaturalDisplayOrientation(int display_id) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetNaturalDisplayOrientation((SDL_DisplayID) display_id);
        }%

        return result;
    }

    public static function SDLGetCurrentDisplayOrientation(int display_id) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetCurrentDisplayOrientation((SDL_DisplayID) display_id);
        }%

        return result;
    }

    public static function SDLGetDisplayContentScale(int display_id) -> double
    {
        double result;

        %{
            result = (double) SDL_GetDisplayContentScale((SDL_DisplayID) display_id);
        }%

        return result;
    }

    public static function SDLGetFullscreenDisplayModes(int display_id) -> array
    {
        array result;

        %{
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
        }%

        return result;
    }

    public static function SDLGetDesktopDisplayMode(int display_id) -> array
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

    public static function SDLGetCurrentDisplayMode(int display_id) -> array
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

    public static function SDLGetClosestFullscreenDisplayMode(int display_id, int w, int h, double refresh_rate = 0.0, bool include_high_density_modes = false) -> array
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
}

