<?php

namespace Sdl3\SDL;

class SDL
{


    /**
     * @param int $flags
     * @return bool
     */
    public static function SDLInit(int $flags): bool
    {
    }

    /**
     * @param int $flags
     * @return bool
     */
    public static function SDLInitSubSystem(int $flags): bool
    {
    }

    /**
     * @param int $flags
     * @return int
     */
    public static function SDLWasInit(int $flags): int
    {
    }

    /**
     * @return void
     */
    public static function SDLQuit(): void
    {
    }

    /**
     * @param int $flags
     * @return void
     */
    public static function SDLQuitSubSystem(int $flags): void
    {
    }

    /**
     * @param int $exitcode
     * @return void
     */
    public static function SDLExitProcess(int $exitcode): void
    {
    }

    /**
     * @param int $format
     * @return array
     */
    public static function SDLGetPixelFormatDetails(int $format): array
    {
    }

    /**
     * @param int $pixel
     * @param int $format_ptr
     * @param mixed $palette_ptr
     * @return array
     */
    public static function SDLGetRGBA(int $pixel, int $format_ptr, $palette_ptr = null): array
    {
    }

    /**
     * @param int $format_ptr
     * @param mixed $palette_ptr
     * @param int $r
     * @param int $g
     * @param int $b
     * @param int $a
     * @return int
     */
    public static function SDLMapRGBA(int $format_ptr, $palette_ptr = null, int $r, int $g, int $b, int $a): int
    {
    }

    /**
     * @return int
     */
    public static function SDLGetSandbox(): int
    {
    }

    /**
     * @return int
     */
    public static function SDLGetVersion(): int
    {
    }

    /**
     * @return string
     */
    public static function SDLGetRevision(): string
    {
    }

    /**
     * @return string
     */
    public static function SDLGetPlatform(): string
    {
    }

    /**
     * @return bool
     */
    public static function SDLIsTablet(): bool
    {
    }

    /**
     * @return bool
     */
    public static function SDLIsTV(): bool
    {
    }

    /**
     * @param string $appname
     * @param string $appversion
     * @param string $appidentifier
     * @return bool
     */
    public static function SDLSetAppMetadata(string $appname, string $appversion, string $appidentifier): bool
    {
    }

    /**
     * @param string $name
     * @param string $value
     * @return bool
     */
    public static function SDLSetAppMetadataProperty(string $name, string $value): bool
    {
    }

    /**
     * @param string $name
     * @return string
     */
    public static function SDLGetAppMetadataProperty(string $name): string
    {
    }

    /**
     * @return void
     */
    public static function SDLSetMainReady(): void
    {
    }

    /**
     * @return bool
     */
    public static function SDLIsMainThread(): bool
    {
    }

    /**
     * @param int $n
     * @return int
     */
    public static function SDLRand(int $n): int
    {
    }

    /**
     * @return float
     */
    public static function SDLRandf(): float
    {
    }
}
