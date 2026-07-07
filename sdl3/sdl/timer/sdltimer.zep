namespace Sdl3\SDL\Timer;

%{
#include <SDL3/SDL.h>
#include <stdio.h>
}%
class SDLTimer
{
    public static function SDLDelay(int ms) -> void
    {
        %{
            SDL_Delay((Uint32) ms);
        }%
    }

    public static function SDLGetTicks() -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetTicks();
        }%

        return result;
    }
}
