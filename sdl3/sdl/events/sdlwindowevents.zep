namespace Sdl3\SDL\Events;

%{
#include <SDL3/SDL.h>
}%

/**
 * Window event payload (SDL_EVENT_WINDOW_*). Agent boundary: only
 * SDL_WindowEvent decoding here. Like every SDLReadEvent reader, it frees
 * the event it decodes.
 */
class SDLWindowEvents
{
    public static function SDLReadWindowEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_WindowEvent *wev = &event->window;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) wev->type);
            add_assoc_long(&result, "timestamp", (zend_long) wev->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) wev->windowID);
            add_assoc_long(&result, "data1", (zend_long) wev->data1);
            add_assoc_long(&result, "data2", (zend_long) wev->data2);

            efree(event);
        }%

        return result;
    }
}
