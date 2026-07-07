namespace Sdl3\SDL\Events;

%{
#include <SDL3/SDL.h>
#include <stdio.h>
}%

/**
 * Quit event payload (SDL_EVENT_QUIT). Agent boundary: only SDL_QuitEvent decoding here.
 */
class SDLQuit
{
    public static function SDLReadQuitEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_QuitEvent *qev = &event->quit;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) qev->type);
            add_assoc_long(&result, "timestamp", (zend_long) qev->timestamp);

            efree(event);
        }%

        return result;
    }
}
