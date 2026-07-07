namespace Sdl3\SDL\Events;

%{
#include <SDL3/SDL.h>
#include <stdio.h>
}%

class SDLKeyboard
{
    public static function SDLHasKeyboard() -> bool
    {
        bool result;

        %{
            result = SDL_HasKeyboard();
        }%

        return result;
    }

    public static function SDLGetKeyboards() -> array
    {
        array result;

        %{
            int count = 0;
            SDL_KeyboardID *ids = SDL_GetKeyboards(&count);

            array_init(&result);
            if (ids != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) ids[i]);
                }
                SDL_free(ids);
            }
        }%

        return result;
    }

    public static function SDLGetKeyboardNameForID(int instance_id) -> string
    {
        string name;

        %{
            const char *keyboard_name = SDL_GetKeyboardNameForID((SDL_KeyboardID) instance_id);
            if (keyboard_name == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, keyboard_name);
            }
        }%

        return name;
    }

    public static function SDLGetKeyboardFocus() -> int
    {
        int ptr;

        %{
            SDL_Window *window = SDL_GetKeyboardFocus();
            ptr = (zend_long)(uintptr_t) window;
        }%

        return ptr;
    }

    public static function SDLGetKeyboardState() -> array
    {
        array result;

        %{
            int numkeys = 0;
            const bool *state = SDL_GetKeyboardState(&numkeys);

            array_init(&result);
            if (state != NULL) {
                for (int i = 0; i < numkeys; i++) {
                    add_index_bool(&result, i, state[i]);
                }
            }
        }%

        return result;
    }

    public static function SDLGetModState() -> int
    {
        int modstate;

        %{
            modstate = (zend_long) SDL_GetModState();
        }%

        return modstate;
    }

    public static function SDLSetModState(int modstate) -> void
    {
        %{
            SDL_SetModState((SDL_Keymod) modstate);
        }%
    }

    public static function SDLGetKeyFromScancode(int scancode, int modstate = 0, bool key_event = true) -> int
    {
        int keycode;

        %{
            keycode = (zend_long) SDL_GetKeyFromScancode((SDL_Scancode) scancode, (SDL_Keymod) modstate, key_event);
        }%

        return keycode;
    }

    public static function SDLGetScancodeFromKey(int key) -> array
    {
        int scancode;
        int modstate;

        %{
            SDL_Keymod mod = SDL_KMOD_NONE;
            SDL_Scancode scan = SDL_GetScancodeFromKey((SDL_Keycode) key, &mod);
            scancode = (zend_long) scan;
            modstate = (zend_long) mod;
        }%

        return ["scancode": scancode, "modstate": modstate];
    }

    public static function SDLSetScancodeName(int scancode, string name) -> bool
    {
        bool result;

        %{
            result = SDL_SetScancodeName((SDL_Scancode) scancode, Z_STRVAL(name));
        }%

        return result;
    }

    public static function SDLGetScancodeName(int scancode) -> string
    {
        string name;

        %{
            const char *scancode_name = SDL_GetScancodeName((SDL_Scancode) scancode);
            if (scancode_name == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, scancode_name);
            }
        }%

        return name;
    }

    public static function SDLGetScancodeFromName(string name) -> int
    {
        int scancode;

        %{
            scancode = (zend_long) SDL_GetScancodeFromName(Z_STRVAL(name));
        }%

        return scancode;
    }

    public static function SDLGetKeyName(int key) -> string
    {
        string name;

        %{
            const char *key_name = SDL_GetKeyName((SDL_Keycode) key);
            if (key_name == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, key_name);
            }
        }%

        return name;
    }

    public static function SDLGetKeyFromName(string name) -> int
    {
        int key;

        %{
            key = (zend_long) SDL_GetKeyFromName(Z_STRVAL(name));
        }%

        return key;
    }

    public static function SDLStartTextInput(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_StartTextInput(win);
        }%

        return result;
    }

    public static function SDLStartTextInputWithProperties(int window, int props) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_StartTextInputWithProperties(win, (SDL_PropertiesID) props);
        }%

        return result;
    }

    public static function SDLTextInputActive(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_TextInputActive(win);
        }%

        return result;
    }

    public static function SDLStopTextInput(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_StopTextInput(win);
        }%

        return result;
    }

    public static function SDLClearComposition(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_ClearComposition(win);
        }%

        return result;
    }

    public static function SDLSetTextInputArea(int window, var rect = null, int cursor = 0) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Rect area;
            const SDL_Rect *area_ptr = NULL;

            if (Z_TYPE_P(rect) == IS_ARRAY) {
                zval *rx = zend_hash_str_find(Z_ARRVAL_P(rect), "x", sizeof("x") - 1);
                zval *ry = zend_hash_str_find(Z_ARRVAL_P(rect), "y", sizeof("y") - 1);
                zval *rw = zend_hash_str_find(Z_ARRVAL_P(rect), "w", sizeof("w") - 1);
                zval *rh = zend_hash_str_find(Z_ARRVAL_P(rect), "h", sizeof("h") - 1);

                area.x = rx ? (int) zval_get_long(rx) : 0;
                area.y = ry ? (int) zval_get_long(ry) : 0;
                area.w = rw ? (int) zval_get_long(rw) : 0;
                area.h = rh ? (int) zval_get_long(rh) : 0;
                area_ptr = &area;
            }

            result = SDL_SetTextInputArea(win, area_ptr, (int) cursor);
        }%

        return result;
    }

    public static function SDLGetTextInputArea(int window) -> array | null
    {
        int x;
        int y;
        int w;
        int h;
        int cursor;
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Rect area = {0};
            int caret = 0;

            result = SDL_GetTextInputArea(win, &area, &caret);
            x = (zend_long) area.x;
            y = (zend_long) area.y;
            w = (zend_long) area.w;
            h = (zend_long) area.h;
            cursor = (zend_long) caret;
        }%

        if !result {
            return null;
        }

        return ["rect": ["x": x, "y": y, "w": w, "h": h], "cursor": cursor];
    }

    public static function SDLHasScreenKeyboardSupport() -> bool
    {
        bool result;

        %{
            result = SDL_HasScreenKeyboardSupport();
        }%

        return result;
    }

    public static function SDLScreenKeyboardShown(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_ScreenKeyboardShown(win);
        }%

        return result;
    }

    public static function SDLReadKeyboardEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_KeyboardEvent *kev = &event->key;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) kev->type);
            add_assoc_long(&result, "timestamp", (zend_long) kev->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) kev->windowID);
            add_assoc_long(&result, "which", (zend_long) kev->which);
            add_assoc_long(&result, "scancode", (zend_long) kev->scancode);
            add_assoc_long(&result, "key", (zend_long) kev->key);
            add_assoc_long(&result, "mod", (zend_long) kev->mod);
            add_assoc_long(&result, "raw", (zend_long) kev->raw);
            add_assoc_bool(&result, "down", kev->down);
            add_assoc_bool(&result, "repeat", kev->repeat);

            efree(event);
        }%

        return result;
    }

    public static function SDLReadTextInputEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_TextInputEvent *tev = &event->text;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) tev->type);
            add_assoc_long(&result, "timestamp", (zend_long) tev->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) tev->windowID);
            add_assoc_string(&result, "text", tev->text ? tev->text : "");

            efree(event);
        }%

        return result;
    }

    public static function SDLReadTextEditingEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_TextEditingEvent *eev = &event->edit;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) eev->type);
            add_assoc_long(&result, "timestamp", (zend_long) eev->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) eev->windowID);
            add_assoc_string(&result, "text", eev->text ? eev->text : "");
            add_assoc_long(&result, "start", (zend_long) eev->start);
            add_assoc_long(&result, "length", (zend_long) eev->length);

            efree(event);
        }%

        return result;
    }

    public static function SDLReadTextEditingCandidatesEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_TextEditingCandidatesEvent *cev = &event->edit_candidates;
            zval candidates;
            int i;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) cev->type);
            add_assoc_long(&result, "timestamp", (zend_long) cev->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) cev->windowID);
            add_assoc_long(&result, "selected_candidate", (zend_long) cev->selected_candidate);
            add_assoc_bool(&result, "horizontal", cev->horizontal);

            array_init(&candidates);
            if (cev->candidates != NULL) {
                for (i = 0; i < cev->num_candidates; i++) {
                    add_next_index_string(&candidates, cev->candidates[i] ? cev->candidates[i] : "");
                }
            }
            add_assoc_long(&result, "num_candidates", (zend_long) cev->num_candidates);
            add_assoc_zval(&result, "candidates", &candidates);

            efree(event);
        }%

        return result;
    }

    public static function SDLReadKeyboardDeviceEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_KeyboardDeviceEvent *kdev = &event->kdevice;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) kdev->type);
            add_assoc_long(&result, "timestamp", (zend_long) kdev->timestamp);
            add_assoc_long(&result, "which", (zend_long) kdev->which);

            efree(event);
        }%

        return result;
    }

}

