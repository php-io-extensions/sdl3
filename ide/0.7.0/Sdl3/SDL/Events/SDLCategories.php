<?php

namespace Sdl3\SDL\Events;

class SDLCategories
{


    /**
     * @param int $type
     * @param bool $enabled
     * @return void
     */
    public static function SDLSetEventEnabled(int $type, bool $enabled): void
    {
    }

    /**
     * @param int $type
     * @return bool
     */
    public static function SDLEventEnabled(int $type): bool
    {
    }

    /**
     * @param int $numevents
     * @return int
     */
    public static function SDLRegisterEvents(int $numevents): int
    {
    }

    /**
     * @param int $event_ptr
     * @return int
     */
    public static function SDLGetWindowFromEvent(int $event_ptr): int
    {
    }

    /**
     * @param int $event_ptr
     * @param int $buflen
     * @return string
     */
    public static function SDLGetEventDescription(int $event_ptr, int $buflen = 256): string
    {
    }
}
