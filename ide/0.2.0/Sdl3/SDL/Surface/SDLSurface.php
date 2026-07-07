<?php

namespace Sdl3\SDL\Surface;

class SDLSurface
{


    /**
     * @param int $width
     * @param int $height
     * @param int $format
     * @return array
     */
    public static function SDLCreateSurface(int $width, int $height, int $format): array
    {
    }

    /**
     * @param int $surface
     * @return array
     */
    public static function SDLDuplicateSurface(int $surface): array
    {
    }

    /**
     * @param int $surface
     * @param int $format
     * @return array
     */
    public static function SDLConvertSurface(int $surface, int $format): array
    {
    }

    /**
     * @param int $surface
     * @return void
     */
    public static function SDLSurfaceToBlackAndWhite(int $surface): void
    {
    }

    /**
     * @param int $src
     * @param mixed $srcrect
     * @param int $dst
     * @param mixed $dstrect
     * @return bool
     */
    public static function SDLBlitSurface(int $src, $srcrect = null, int $dst, $dstrect = null): bool
    {
    }

    /**
     * @param int $surface
     * @param int $color
     * @param mixed $rect
     * @return bool
     */
    public static function SDLFillSurfaceRect(int $surface, int $color, $rect = null): bool
    {
    }

    /**
     * @param int $format
     * @param int $palette
     * @param int $r
     * @param int $g
     * @param int $b
     * @return int
     */
    public static function SDLMapRGB(int $format, int $palette, int $r, int $g, int $b): int
    {
    }

    /**
     * @param int $surface
     * @return bool
     */
    public static function SDLLockSurface(int $surface): bool
    {
    }

    /**
     * @param int $surface
     * @return void
     */
    public static function SDLUnlockSurface(int $surface): void
    {
    }

    /**
     * @param int $surface
     * @return void
     */
    public static function SDLDestroySurface(int $surface): void
    {
    }

    /**
     * @param string $file
     * @return array
     */
    public static function SDLLoadPNG(string $file): array
    {
    }

    /**
     * @param string $file
     * @return array
     */
    public static function SDLLoadBMP(string $file): array
    {
    }

    /**
     * @param int $surface
     * @param int $x
     * @param int $y
     * @param int $pixel
     * @return bool
     */
    public static function SDLWriteSurfacePixelAt(int $surface, int $x, int $y, int $pixel): bool
    {
    }

    /**
     * @param int $surface
     * @param array $data
     * @return bool
     */
    public static function SDLWriteSurfacePixels(int $surface, array $data): bool
    {
    }

    /**
     * @param int $surface
     * @return array
     */
    public static function SDLReadSurfacePixels(int $surface): array
    {
    }

    /**
     * @param int $surface
     * @return array
     */
    public static function SDLGetSurfacePalette(int $surface): array
    {
    }
}
