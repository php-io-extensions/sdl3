namespace Sdl3\SDL;

%{
#include <SDL3/SDL.h>
#include <stdio.h>
}%

class SDLError
{
    public static function SDLGetError() -> string
    {
        string result;

        %{
            ZVAL_STRING(&result, SDL_GetError());
        }%

        return result;
    }

    public static function SDLSetError(string message) -> bool
    {
        bool result;

        %{
            result = SDL_SetError("%s", Z_STRVAL(message));
        }%

        return result;
    }

    public static function SDLOutOfMemory() -> bool
    {
        bool result;

        %{
            result = SDL_OutOfMemory();
        }%

        return result;
    }

    public static function SDLClearError() -> bool
    {
        bool result;

        %{
            result = SDL_ClearError();
        }%

        return result;
    }
}