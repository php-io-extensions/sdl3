namespace Sdl3\SDL\Events;

%{
#include <SDL3/SDL.h>
#include <stdio.h>
}%

/**
 * Drag-and-drop event payload (event.drop.*). Agent boundary: only SDL_DropEvent decoding here.
 */
class SDLDropEvents
{
    public static function SDLReadDropEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_DropEvent *dev = &event->drop;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) dev->type);
            add_assoc_long(&result, "timestamp", (zend_long) dev->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) dev->windowID);
            add_assoc_double(&result, "x", (double) dev->x);
            add_assoc_double(&result, "y", (double) dev->y);
            add_assoc_string(&result, "source", dev->source ? dev->source : "");
            add_assoc_string(&result, "data", dev->data ? dev->data : "");

            efree(event);
        }%

        return result;
    }
}
