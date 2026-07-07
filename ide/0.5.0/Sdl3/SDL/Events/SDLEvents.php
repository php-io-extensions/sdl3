<?php

namespace Sdl3\SDL\Events;

class SDLEvents
{


    /**
     * @param int $ptr
     * @param string $key
     * @return array
     */
    public static function SDLReadEvent(int $ptr, string $key): array
    {
    }

    /**
     * @return array|null
     */
    public static function SDLPollEvent(): array|null
    {
    }

    /**
     * @param int $timeout_ms
     * @return int
     */
    public static function SDLWaitEventTimeout(int $timeout_ms): int
    {
    }

    /**
     * @return array|null
     */
    public static function SDLWaitEvent(): array|null
    {
    }

    /**
     * @param int $action
     * @param int $min_type
     * @param int $max_type
     * @param int $numevents
     * @return array
     */
    public static function SDLPeepEvents(int $action, int $min_type, int $max_type, int $numevents = 1): array
    {
    }

    /**
     * @param int $type
     * @return bool
     */
    public static function SDLHasEvent(int $type): bool
    {
    }

    /**
     * @param int $min_type
     * @param int $max_type
     * @return bool
     */
    public static function SDLHasEvents(int $min_type, int $max_type): bool
    {
    }

    /**
     * @param int $type
     * @return void
     */
    public static function SDLFlushEvent(int $type): void
    {
    }

    /**
     * @param int $min_type
     * @param int $max_type
     * @return void
     */
    public static function SDLFlushEvents(int $min_type, int $max_type): void
    {
    }

    /**
     * @param int $event_ptr
     * @return bool
     */
    public static function SDLPushEvent(int $event_ptr): bool
    {
    }

    /**
     * @param int $ptr
     * @return void
     */
    public static function SDLFreeEvent(int $ptr): void
    {
    }

    /**
     * @return void
     */
    public static function SDLPumpEvents(): void
    {
    }

    /**
     * @return array
     */
    public static function SDLGetKeyboardState(): array
    {
    }
}
