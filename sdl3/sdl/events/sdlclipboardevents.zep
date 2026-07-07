namespace Sdl3\SDL\Events;

%{
#include <SDL3/SDL.h>
#include <stdio.h>
}%

class SDLClipboardEvents
{
    public static function SDLReadClipboardEvent(int ptr) -> array
    {
        array result;

        %{
            SDL_Event *event = (SDL_Event *)(uintptr_t) ptr;
            SDL_ClipboardEvent *cev = &event->clipboard;

            array_init(&result);
            add_assoc_long(&result, "type",           (zend_long) cev->type);
            add_assoc_long(&result, "timestamp",      (zend_long) cev->timestamp);
            add_assoc_long(&result, "owner",          (zend_long) cev->owner);
            add_assoc_long(&result, "num_mime_types", (zend_long) cev->num_mime_types);

            if (cev->num_mime_types > 0 && cev->mime_types != NULL) {
                zval mime_array;
                array_init(&mime_array);
                for (int i = 0; i < (int) cev->num_mime_types; i++) {
                    if (cev->mime_types[i] != NULL) {
                        add_next_index_string(&mime_array, cev->mime_types[i]);
                    }
                }
                add_assoc_zval(&result, "mime_types", &mime_array);
            } else {
                zval empty_array;
                array_init(&empty_array);
                add_assoc_zval(&result, "mime_types", &empty_array);
            }

            efree(event);
        }%

        return result;
    }

    public static function SDLSetClipboardText(string text) -> bool
    {
        bool result;

        %{
            result = SDL_SetClipboardText((const char *) Z_STRVAL(text));
        }%

        return result;
    }

    public static function SDLGetClipboardText() -> string
    {
        string result = "";

        %{
            const char *text = SDL_GetClipboardText();
            if (text) {
                ZVAL_STRING(&result, text);
                SDL_free((void *) text);
            }
        }%

        return result;
    }

    public static function SDLHasClipboardText() -> bool
    {
        bool result;

        %{
            result = SDL_HasClipboardText();
        }%

        return result;
    }

    public static function SDLSetPrimarySelectionText(string text) -> bool
    {
        bool result;

        %{
            result = SDL_SetPrimarySelectionText((const char *) Z_STRVAL(text));
        }%

        return result;
    }

    public static function SDLGetPrimarySelectionText() -> string
    {
        string result = "";

        %{
            const char *text = SDL_GetPrimarySelectionText();
            if (text) {
                ZVAL_STRING(&result, text);
                SDL_free((void *) text);
            }
        }%

        return result;
    }

    public static function SDLHasPrimarySelectionText() -> bool
    {
        bool result;

        %{
            result = SDL_HasPrimarySelectionText();
        }%

        return result;
    }

    public static function SDLGetClipboardMimeTypes() -> array
    {
        array result;

        %{
            const char **mime_types = SDL_GetClipboardMimeTypes(NULL);

            array_init(&result);
            if (mime_types != NULL) {
                for (int i = 0; mime_types[i] != NULL; i++) {
                    add_next_index_string(&result, mime_types[i]);
                }
                SDL_free(mime_types);
            }
        }%

        return result;
    }

    public static function SDLHasClipboardData(string mime_type) -> bool
    {
        bool result;

        %{
            result = SDL_HasClipboardData((const char *) Z_STRVAL(mime_type));
        }%

        return result;
    }

    public static function SDLClearClipboardData() -> void
    {
        %{
            SDL_ClearClipboardData();
        }%
    }
}

