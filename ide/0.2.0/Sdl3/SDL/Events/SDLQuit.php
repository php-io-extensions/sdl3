<?php

namespace Sdl3\SDL\Events;

/**
 * Quit event payload (SDL_EVENT_QUIT). Agent boundary: only SDL_QuitEvent decoding here.
 */
class SDLQuit
{


    /**
     * @param int $ptr
     * @return array
     */
    public static function SDLReadQuitEvent(int $ptr): array
    {
    }
}
