<?php

namespace Sdl3\SDL\Events;

class SDLDisplayEvents
{


    /**
     * @param int $ptr
     * @return array
     */
    public static function SDLReadDisplayEvent(int $ptr): array
    {
    }

    /**
     * @return array
     */
    public static function SDLGetDisplays(): array
    {
    }

    /**
     * @return int
     */
    public static function SDLGetPrimaryDisplay(): int
    {
    }

    /**
     * @param int $display_id
     * @return string
     */
    public static function SDLGetDisplayName(int $display_id): string
    {
    }

    /**
     * @param int $display_id
     * @return array
     */
    public static function SDLGetDisplayBounds(int $display_id): array
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function SDLGetDisplayForWindow(int $window): int
    {
    }

    /**
     * @param int $display_id
     * @return int
     */
    public static function SDLGetNaturalDisplayOrientation(int $display_id): int
    {
    }

    /**
     * @param int $display_id
     * @return int
     */
    public static function SDLGetCurrentDisplayOrientation(int $display_id): int
    {
    }

    /**
     * @param int $display_id
     * @return float
     */
    public static function SDLGetDisplayContentScale(int $display_id): float
    {
    }

    /**
     * @param int $display_id
     * @return array
     */
    public static function SDLGetFullscreenDisplayModes(int $display_id): array
    {
    }

    /**
     * @param int $display_id
     * @return array
     */
    public static function SDLGetDesktopDisplayMode(int $display_id): array
    {
    }

    /**
     * @param int $display_id
     * @return array
     */
    public static function SDLGetCurrentDisplayMode(int $display_id): array
    {
    }

    /**
     * @param int $display_id
     * @param int $w
     * @param int $h
     * @param double $refresh_rate
     * @param bool $include_high_density_modes
     * @return array
     */
    public static function SDLGetClosestFullscreenDisplayMode(int $display_id, int $w, int $h, float $refresh_rate = 0.0, bool $include_high_density_modes = false): array
    {
    }
}
