<?php

namespace Sdl3\SDL\Events;

/**
 * Drag-and-drop event payload (event.drop.). Agent boundary: only SDL_DropEvent decoding here.
 */
class SDLDropEvents
{


    /**
     * @param int $ptr
     * @return array
     */
    public static function SDLReadDropEvent(int $ptr): array
    {
    }
}
