<?php

namespace Sdl3\SDL\Video;

class SDLVideo
{


    /**
     * @param string $title
     * @param int $width
     * @param int $height
     * @param int $flags
     * @return int
     */
    public static function SDLCreateWindow(string $title, int $width, int $height, int $flags): int
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function SDLGetWindowSize(int $window): array
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function SDLGetWindowPosition(int $window): array
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function SDLGetWindowSizeInPixels(int $window): array
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function SDLGetWindowMinimumSize(int $window): array
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function SDLGetWindowMaximumSize(int $window): array
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function SDLGetWindowAspectRatio(int $window): array
    {
    }

    /**
     * @param int $window
     * @param int $surface
     * @return bool
     */
    public static function SDLSetWindowIcon(int $window, int $surface): bool
    {
    }

    /**
     * @param int $window
     * @return void
     */
    public static function SDLDestroyWindow(int $window): void
    {
    }

    /**
     * @param string $title
     * @param int $w
     * @param int $h
     * @param int $flags
     * @return array
     */
    public static function SDLCreateWindowAndRenderer(string $title, int $w, int $h, int $flags): array
    {
    }
}
