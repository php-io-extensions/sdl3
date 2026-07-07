namespace Sdl3\SDL\Events;

%{
#include <SDL3/SDL.h>
#include <stdio.h>
}%

/**
 * Mouse-related SDL_Event union arms. Agent boundary: decode-only helpers; SDL_mouse.h API comes later.
 */
class SDLMouse
{
    public static function SDLHasMouse() -> bool
    {
        bool result;

        %{
            result = SDL_HasMouse();
        }%

        return result;
    }

    public static function SDLGetMice() -> array
    {
        array result;

        %{
            int count = 0;
            SDL_MouseID *ids = SDL_GetMice(&count);

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

    public static function SDLGetMouseNameForID(int instance_id) -> string
    {
        string name;

        %{
            const char *mouse_name = SDL_GetMouseNameForID((SDL_MouseID) instance_id);
            if (mouse_name == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, mouse_name);
            }
        }%

        return name;
    }

    public static function SDLGetMouseFocus() -> int
    {
        int ptr;

        %{
            SDL_Window *window = SDL_GetMouseFocus();
            ptr = (zend_long)(uintptr_t) window;
        }%

        return ptr;
    }

    public static function SDLGetMouseState() -> array
    {
        int buttons;
        double x;
        double y;

        %{
            float xx = 0.0f;
            float yy = 0.0f;
            SDL_MouseButtonFlags state = SDL_GetMouseState(&xx, &yy);
            buttons = (zend_long) state;
            x = (double) xx;
            y = (double) yy;
        }%

        return ["buttons": buttons, "x": x, "y": y];
    }

    public static function SDLGetGlobalMouseState() -> array
    {
        int buttons;
        double x;
        double y;

        %{
            float xx = 0.0f;
            float yy = 0.0f;
            SDL_MouseButtonFlags state = SDL_GetGlobalMouseState(&xx, &yy);
            buttons = (zend_long) state;
            x = (double) xx;
            y = (double) yy;
        }%

        return ["buttons": buttons, "x": x, "y": y];
    }

    public static function SDLGetRelativeMouseState() -> array
    {
        int buttons;
        double x;
        double y;

        %{
            float xx = 0.0f;
            float yy = 0.0f;
            SDL_MouseButtonFlags state = SDL_GetRelativeMouseState(&xx, &yy);
            buttons = (zend_long) state;
            x = (double) xx;
            y = (double) yy;
        }%

        return ["buttons": buttons, "x": x, "y": y];
    }

    public static function SDLWarpMouseInWindow(int window = 0, double x, double y) -> void
    {
        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_WarpMouseInWindow(win, (float) x, (float) y);
        }%
    }

    public static function SDLWarpMouseGlobal(double x, double y) -> bool
    {
        bool result;

        %{
            result = SDL_WarpMouseGlobal((float) x, (float) y);
        }%

        return result;
    }

    public static function SDLSetWindowRelativeMouseMode(int window, bool enabled) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_SetWindowRelativeMouseMode(win, enabled);
        }%

        return result;
    }

    public static function SDLGetWindowRelativeMouseMode(int window) -> bool
    {
        bool result;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            result = SDL_GetWindowRelativeMouseMode(win);
        }%

        return result;
    }

    public static function SDLCaptureMouse(bool enabled) -> bool
    {
        bool result;

        %{
            result = SDL_CaptureMouse(enabled);
        }%

        return result;
    }

    public static function SDLCreateCursor(string data, string mask, int w, int h, int hot_x, int hot_y) -> int
    {
        int ptr;

        %{
            const Uint8 *data_ptr = (const Uint8 *) Z_STRVAL(data);
            const Uint8 *mask_ptr = (const Uint8 *) Z_STRVAL(mask);
            SDL_Cursor *cursor = SDL_CreateCursor(data_ptr, mask_ptr, (int) w, (int) h, (int) hot_x, (int) hot_y);
            ptr = (zend_long)(uintptr_t) cursor;
        }%

        return ptr;
    }

    public static function SDLCreateColorCursor(int surface, int hot_x, int hot_y) -> int
    {
        int ptr;

        %{
            SDL_Surface *sur = (SDL_Surface *)(uintptr_t) surface;
            SDL_Cursor *cursor = SDL_CreateColorCursor(sur, (int) hot_x, (int) hot_y);
            ptr = (zend_long)(uintptr_t) cursor;
        }%

        return ptr;
    }

    public static function SDLCreateAnimatedCursor(array frames, int hot_x, int hot_y) -> int
    {
        int ptr;

        %{
            int frame_count = zend_hash_num_elements(Z_ARRVAL_P(&frames));
            SDL_CursorFrameInfo *frame_infos = NULL;
            SDL_Cursor *cursor = NULL;
            int i = 0;
            zval *entry;

            if (frame_count > 0) {
                frame_infos = (SDL_CursorFrameInfo *) emalloc(sizeof(SDL_CursorFrameInfo) * frame_count);
                memset(frame_infos, 0, sizeof(SDL_CursorFrameInfo) * frame_count);

                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&frames), entry) {
                    if (i >= frame_count) {
                        break;
                    }
                    if (Z_TYPE_P(entry) == IS_ARRAY) {
                        zval *surface = zend_hash_str_find(Z_ARRVAL_P(entry), "surface", sizeof("surface") - 1);
                        zval *duration = zend_hash_str_find(Z_ARRVAL_P(entry), "duration", sizeof("duration") - 1);
                        frame_infos[i].surface = (SDL_Surface *)(uintptr_t) (surface ? zval_get_long(surface) : 0);
                        frame_infos[i].duration = (Uint32) (duration ? zval_get_long(duration) : 0);
                        i++;
                    }
                } ZEND_HASH_FOREACH_END();

                cursor = SDL_CreateAnimatedCursor(frame_infos, i, (int) hot_x, (int) hot_y);
                efree(frame_infos);
            }

            ptr = (zend_long)(uintptr_t) cursor;
        }%

        return ptr;
    }

    public static function SDLCreateSystemCursor(int id) -> int
    {
        int ptr;

        %{
            SDL_Cursor *cursor = SDL_CreateSystemCursor((SDL_SystemCursor) id);
            ptr = (zend_long)(uintptr_t) cursor;
        }%

        return ptr;
    }

    public static function SDLSetCursor(var cursor = null) -> bool
    {
        bool result;

        %{
            SDL_Cursor *cur = NULL;
            if (Z_TYPE_P(cursor) != IS_NULL) {
                cur = (SDL_Cursor *)(uintptr_t) zval_get_long(cursor);
            }
            result = SDL_SetCursor(cur);
        }%

        return result;
    }

    public static function SDLGetCursor() -> int
    {
        int ptr;

        %{
            SDL_Cursor *cursor = SDL_GetCursor();
            ptr = (zend_long)(uintptr_t) cursor;
        }%

        return ptr;
    }

    public static function SDLGetDefaultCursor() -> int
    {
        int ptr;

        %{
            SDL_Cursor *cursor = SDL_GetDefaultCursor();
            ptr = (zend_long)(uintptr_t) cursor;
        }%

        return ptr;
    }

    public static function SDLDestroyCursor(int cursor) -> void
    {
        %{
            SDL_Cursor *cur = (SDL_Cursor *)(uintptr_t) cursor;
            SDL_DestroyCursor(cur);
        }%
    }

    public static function SDLShowCursor() -> bool
    {
        bool result;

        %{
            result = SDL_ShowCursor();
        }%

        return result;
    }

    public static function SDLHideCursor() -> bool
    {
        bool result;

        %{
            result = SDL_HideCursor();
        }%

        return result;
    }

    public static function SDLCursorVisible() -> bool
    {
        bool result;

        %{
            result = SDL_CursorVisible();
        }%

        return result;
    }

    public static function SDLReadMouseDeviceEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_MouseDeviceEvent *mdev = &event->mdevice;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) mdev->type);
            add_assoc_long(&result, "timestamp", (zend_long) mdev->timestamp);
            add_assoc_long(&result, "which", (zend_long) mdev->which);

            efree(event);
        }%

        return result;
    }

    public static function SDLReadMouseMotionEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_MouseMotionEvent *mov = &event->motion;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) mov->type);
            add_assoc_long(&result, "timestamp", (zend_long) mov->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) mov->windowID);
            add_assoc_long(&result, "which", (zend_long) mov->which);
            add_assoc_long(&result, "state", (zend_long) mov->state);
            add_assoc_double(&result, "x", (double) mov->x);
            add_assoc_double(&result, "y", (double) mov->y);
            add_assoc_double(&result, "xrel", (double) mov->xrel);
            add_assoc_double(&result, "yrel", (double) mov->yrel);

            efree(event);
        }%

        return result;
    }

    public static function SDLReadMouseButtonEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_MouseButtonEvent *btn = &event->button;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) btn->type);
            add_assoc_long(&result, "timestamp", (zend_long) btn->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) btn->windowID);
            add_assoc_long(&result, "which", (zend_long) btn->which);
            add_assoc_long(&result, "button", (zend_long) btn->button);
            add_assoc_bool(&result, "down", btn->down);
            add_assoc_long(&result, "clicks", (zend_long) btn->clicks);
            add_assoc_double(&result, "x", (double) btn->x);
            add_assoc_double(&result, "y", (double) btn->y);

            efree(event);
        }%

        return result;
    }

    public static function SDLReadMouseWheelEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_MouseWheelEvent *whl = &event->wheel;

            array_init(&result);
            add_assoc_long(&result, "type", (zend_long) whl->type);
            add_assoc_long(&result, "timestamp", (zend_long) whl->timestamp);
            add_assoc_long(&result, "window_id", (zend_long) whl->windowID);
            add_assoc_long(&result, "which", (zend_long) whl->which);
            add_assoc_double(&result, "x", (double) whl->x);
            add_assoc_double(&result, "y", (double) whl->y);
            add_assoc_long(&result, "direction", (zend_long) whl->direction);
            add_assoc_double(&result, "mouse_x", (double) whl->mouse_x);
            add_assoc_double(&result, "mouse_y", (double) whl->mouse_y);
            add_assoc_long(&result, "integer_x", (zend_long) whl->integer_x);
            add_assoc_long(&result, "integer_y", (zend_long) whl->integer_y);

            efree(event);
        }%

        return result;
    }
}
