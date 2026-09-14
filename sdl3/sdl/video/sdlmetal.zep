namespace Sdl3\SDL\Video;

%{
#include <SDL3/SDL.h>
}%

/**
 * SDL_metal.h: a CAMetalLayer-backed view on an SDL window. The layer
 * crosses as raw pointer bits — the only currency between extensions.
 * Compiles everywhere; on a non-Apple box CreateView fails and throws.
 */
class SDLMetal
{
    public static function SDLMetalCreateView(int window) -> int
    {
        int ptr;

        %{
            SDL_MetalView view = SDL_Metal_CreateView((SDL_Window *)(uintptr_t) window);
            ptr = (zend_long)(uintptr_t) view;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_Metal_CreateView failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLMetalDestroyView(int view) -> void
    {
        %{
            SDL_Metal_DestroyView((SDL_MetalView)(uintptr_t) view);
        }%
    }

    public static function SDLMetalGetLayer(int view) -> int
    {
        int ptr;

        %{
            void *layer = SDL_Metal_GetLayer((SDL_MetalView)(uintptr_t) view);
            ptr = (zend_long)(uintptr_t) layer;
        }%

        return ptr;
    }
}
