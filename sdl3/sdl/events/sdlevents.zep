namespace Sdl3\SDL\Events;

%{
#include <SDL3/SDL.h>
#include <stdio.h>
}%

class SDLEvents
{
    public static function SDLReadEvent(int ptr, string key) -> array
    {
        var result;

        switch key {
            case "key":
                let result = SDLKeyboard::SDLReadKeyboardEvent(ptr);
                break;
            case "text":
                let result = SDLKeyboard::SDLReadTextInputEvent(ptr);
                break;
            case "edit":
                let result = SDLKeyboard::SDLReadTextEditingEvent(ptr);
                break;
            case "edit_candidates":
                let result = SDLKeyboard::SDLReadTextEditingCandidatesEvent(ptr);
                break;
            case "kdevice":
                let result = SDLKeyboard::SDLReadKeyboardDeviceEvent(ptr);
                break;
            case "display":
                let result = SDLDisplayEvents::SDLReadDisplayEvent(ptr);
                break;
            case "quit":
                let result = SDLQuit::SDLReadQuitEvent(ptr);
                break;
            case "drop":
                let result = SDLDropEvents::SDLReadDropEvent(ptr);
                break;
            case "mdevice":
                let result = SDLMouse::SDLReadMouseDeviceEvent(ptr);
                break;
            case "motion":
                let result = SDLMouse::SDLReadMouseMotionEvent(ptr);
                break;
            case "button":
                let result = SDLMouse::SDLReadMouseButtonEvent(ptr);
                break;
            case "wheel":
                let result = SDLMouse::SDLReadMouseWheelEvent(ptr);
                break;

            default:
                %{
                    efree((SDL_Event *)(uintptr_t) ptr);
                }%
                throw new \RuntimeException("SDL event property '" . key . "' is not supported yet");
        }

        return result;
    }

    public static function SDLPollEvent() -> array | null
    {
        int ptr;
        int event_type;

        %{
            SDL_Event *event = emalloc(sizeof(SDL_Event));
            bool has_event = SDL_WaitEventTimeout(event, 0);

            if (has_event) {
                ptr        = (zend_long)(uintptr_t) event;
                event_type = (zend_long) event->type;

            } else {
                efree(event);
                ptr        = 0;
                event_type = 0;
            }
        }%

        if ptr == 0 {
            return null;
        }

        return ["ptr": ptr, "event_type": event_type];
    }

    public static function SDLWaitEventTimeout(int timeout_ms) -> int
    {
        int ptr;

        %{
            SDL_Event *event = emalloc(sizeof(SDL_Event));
            bool has_event = SDL_WaitEventTimeout(event, (Sint32) timeout_ms);

            if (has_event) {
                ptr = (zend_long)(uintptr_t) event;
            } else {
                efree(event);
                ptr = 0;
            }
        }%

        return ptr;
    }

    public static function SDLWaitEvent() -> array | null
    {
        int ptr;
        int event_type;

        %{
            SDL_Event *event = emalloc(sizeof(SDL_Event));
            bool has_event = SDL_WaitEvent(event);

            if (has_event) {
                ptr        = (zend_long)(uintptr_t) event;
                event_type = (zend_long) event->type;
            } else {
                efree(event);
                ptr        = 0;
                event_type = 0;
            }
        }%

        if ptr == 0 {
            return null;
        }

        return ["ptr": ptr, "event_type": event_type];
    }

    public static function SDLPeepEvents(int action, int min_type, int max_type, int numevents = 1) -> array
    {
        array result;

        %{
            int requested = (int) numevents;
            SDL_EventAction event_action = (SDL_EventAction) action;

            array_init(&result);

            if (requested > 0 && event_action != SDL_ADDEVENT) {
                SDL_Event *events = emalloc(sizeof(SDL_Event) * requested);
                int count = SDL_PeepEvents(
                    events,
                    requested,
                    event_action,
                    (Uint32) min_type,
                    (Uint32) max_type
                );

                if (count > 0) {
                    for (int i = 0; i < count; i++) {
                        SDL_Event *event_copy = emalloc(sizeof(SDL_Event));
                        zval event_data;

                        *event_copy = events[i];

                        array_init(&event_data);
                        add_assoc_long(&event_data, "ptr", (zend_long) (uintptr_t) event_copy);
                        add_assoc_long(&event_data, "event_type", (zend_long) event_copy->type);
                        add_next_index_zval(&result, &event_data);
                    }
                }

                efree(events);
            }
        }%

        return result;
    }

    public static function SDLHasEvent(int type) -> bool
    {
        bool result;

        %{
            result = SDL_HasEvent((Uint32) type);
        }%

        return result;
    }

    public static function SDLHasEvents(int min_type, int max_type) -> bool
    {
        bool result;

        %{
            result = SDL_HasEvents((Uint32) min_type, (Uint32) max_type);
        }%

        return result;
    }

    public static function SDLFlushEvent(int type) -> void
    {
        %{
            SDL_FlushEvent((Uint32) type);
        }%
    }

    public static function SDLFlushEvents(int min_type, int max_type) -> void
    {
        %{
            SDL_FlushEvents((Uint32) min_type, (Uint32) max_type);
        }%
    }

    public static function SDLPushEvent(int event_ptr) -> bool
    {
        bool result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) event_ptr;
            result = SDL_PushEvent((const SDL_Event *) event);
        }%

        return result;
    }

    public static function SDLFreeEvent(int ptr) -> void
    {
        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            efree(event);
        }%
    }

    public static function SDLPumpEvents() -> void
    {
        %{
            SDL_PumpEvents();
        }%
    }

    public static function SDLGetKeyboardState() -> array
    {
        return SDLKeyboard::SDLGetKeyboardState();
    }
}
