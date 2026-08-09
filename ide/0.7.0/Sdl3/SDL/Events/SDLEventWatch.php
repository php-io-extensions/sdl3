<?php

namespace Sdl3\SDL\Events;

class SDLEventWatch
{


    /**
     * @param mixed $callback
     * @return void
     */
    public static function SDLSetEventFilter($callback = null): void
    {
    }

    /**
     * @return bool
     */
    public static function SDLGetEventFilter(): bool
    {
    }

    /**
     * @param mixed $callback
     * @return int
     */
    public static function SDLAddEventWatch($callback): int
    {
    }

    /**
     * @param int $watch_id
     * @return bool
     */
    public static function SDLRemoveEventWatch(int $watch_id): bool
    {
    }

    /**
     * @param mixed $callback
     * @return void
     */
    public static function SDLFilterEvents($callback): void
    {
    }
}
