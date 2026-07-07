namespace Sdl3\SDL\Events;

%{
#include <SDL3/SDL.h>
#include <stdio.h>
}%

class SDLCategories
{
    public static function SDLSetEventEnabled(int type, bool enabled) -> void
    {
        %{
            SDL_SetEventEnabled((Uint32) type, (bool) enabled);
        }%
    }

    public static function SDLEventEnabled(int type) -> bool
    {
        bool result;

        %{
            result = SDL_EventEnabled((Uint32) type);
        }%

        return result;
    }

    public static function SDLRegisterEvents(int numevents) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_RegisterEvents((int) numevents);
        }%

        return result;
    }

    public static function SDLGetWindowFromEvent(int event_ptr) -> int
    {
        int result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) event_ptr;
            SDL_Window *window = SDL_GetWindowFromEvent((const SDL_Event *) event);
            result = (zend_long) (uintptr_t) window;
        }%

        return result;
    }

    public static function SDLGetEventDescription(int event_ptr, int buflen = 256) -> string
    {
        string result = "";

        %{
            int len = (int) buflen;

            if (len > 0) {
                char *buf = emalloc((size_t) len);
                if (buf != NULL) {
#if SDL_VERSION_ATLEAST(3, 4, 0)
                    SDL_Event *event = (SDL_Event *)(uintptr_t) event_ptr;
                    SDL_GetEventDescription((const SDL_Event *) event, buf, len);
                    ZVAL_STRING(&result, buf);
#else
                    snprintf(buf, (size_t) len, "SDL_GetEventDescription unavailable: SDL < 3.4.0");
                    ZVAL_STRING(&result, buf);
#endif
                    efree(buf);
                }
            }
        }%

        return result;
    }
}

