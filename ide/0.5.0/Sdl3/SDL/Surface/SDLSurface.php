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
     * @param int $dst
     * @param mixed $srcrect
     * @param mixed $dstrect
     * @return bool
     */
    public static function SDLBlitSurface(int $src, int $dst, $srcrect = null, $dstrect = null): bool
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

    /**
     * @param int $ptr
     * @param int $flags
     * @param int $fmt
     * @param int $w
     * @param int $h
     * @param int $pitch
     * @param int $pixels_ptr
     * @param array $pixels_data
     * @param int $refcount
     * @return array
     */
    private static function buildSurfaceArray(int $ptr, int $flags, int $fmt, int $w, int $h, int $pitch, int $pixels_ptr, array $pixels_data, int $refcount): array
    {
    }

    /**
     * @param int $surface
     * @return array
     */
    private static function packSurfaceFromPtr(int $surface): array
    {
    }

    /**
     * @param int $ptr
     * @param int $ncolors
     * @param array $colors
     * @param int $version
     * @param int $refcount
     * @return array
     */
    private static function buildPaletteArray(int $ptr, int $ncolors, array $colors, int $version, int $refcount): array
    {
    }

    /**
     * @param int $palette
     * @return array
     */
    private static function packPaletteFromPtr(int $palette): array
    {
    }

    /**
     * @param int $width
     * @param int $height
     * @param int $format
     * @param string $pixels
     * @param int $pitch
     * @return array
     */
    public static function SDLCreateSurfaceFrom(int $width, int $height, int $format, string $pixels, int $pitch): array
    {
    }

    /**
     * @param int $surface
     * @return int
     */
    public static function SDLGetSurfaceProperties(int $surface): int
    {
    }

    /**
     * @param int $surface
     * @param int $colorspace
     * @return bool
     */
    public static function SDLSetSurfaceColorspace(int $surface, int $colorspace): bool
    {
    }

    /**
     * @param int $surface
     * @return int
     */
    public static function SDLGetSurfaceColorspace(int $surface): int
    {
    }

    /**
     * @param int $surface
     * @return array
     */
    public static function SDLCreateSurfacePalette(int $surface): array
    {
    }

    /**
     * @param int $surface
     * @param int $palette
     * @return bool
     */
    public static function SDLSetSurfacePalette(int $surface, int $palette): bool
    {
    }

    /**
     * @param int $surface
     * @param int $image
     * @return bool
     */
    public static function SDLAddSurfaceAlternateImage(int $surface, int $image): bool
    {
    }

    /**
     * @param int $surface
     * @return bool
     */
    public static function SDLSurfaceHasAlternateImages(int $surface): bool
    {
    }

    /**
     * @param int $surface
     * @return array
     */
    public static function SDLGetSurfaceImages(int $surface): array
    {
    }

    /**
     * @param int $surface
     * @return void
     */
    public static function SDLRemoveSurfaceAlternateImages(int $surface): void
    {
    }

    /**
     * @param string $file
     * @return array
     */
    public static function SDLLoadSurface(string $file): array
    {
    }

    /**
     * @param int $surface
     * @param string $file
     * @return bool
     */
    public static function SDLSaveBMP(int $surface, string $file): bool
    {
    }

    /**
     * @param int $surface
     * @param string $file
     * @return bool
     */
    public static function SDLSavePNG(int $surface, string $file): bool
    {
    }

    /**
     * @param int $surface
     * @param bool $enabled
     * @return bool
     */
    public static function SDLSetSurfaceRLE(int $surface, bool $enabled): bool
    {
    }

    /**
     * @param int $surface
     * @return bool
     */
    public static function SDLSurfaceHasRLE(int $surface): bool
    {
    }

    /**
     * @param int $surface
     * @param bool $enabled
     * @param int $key
     * @return bool
     */
    public static function SDLSetSurfaceColorKey(int $surface, bool $enabled, int $key): bool
    {
    }

    /**
     * @param int $surface
     * @return bool
     */
    public static function SDLSurfaceHasColorKey(int $surface): bool
    {
    }

    /**
     * @param int $surface
     * @return array
     */
    public static function SDLGetSurfaceColorKey(int $surface): array
    {
    }

    /**
     * @param int $surface
     * @param int $r
     * @param int $g
     * @param int $b
     * @return bool
     */
    public static function SDLSetSurfaceColorMod(int $surface, int $r, int $g, int $b): bool
    {
    }

    /**
     * @param int $surface
     * @return array
     */
    public static function SDLGetSurfaceColorMod(int $surface): array
    {
    }

    /**
     * @param int $surface
     * @param int $alpha
     * @return bool
     */
    public static function SDLSetSurfaceAlphaMod(int $surface, int $alpha): bool
    {
    }

    /**
     * @param int $surface
     * @return array
     */
    public static function SDLGetSurfaceAlphaMod(int $surface): array
    {
    }

    /**
     * @param int $surface
     * @param int $blendMode
     * @return bool
     */
    public static function SDLSetSurfaceBlendMode(int $surface, int $blendMode): bool
    {
    }

    /**
     * @param int $surface
     * @return array
     */
    public static function SDLGetSurfaceBlendMode(int $surface): array
    {
    }

    /**
     * @param int $surface
     * @param mixed $rect
     * @return bool
     */
    public static function SDLSetSurfaceClipRect(int $surface, $rect = null): bool
    {
    }

    /**
     * @param int $surface
     * @return array
     */
    public static function SDLGetSurfaceClipRect(int $surface): array
    {
    }

    /**
     * @param int $surface
     * @param int $flip
     * @return bool
     */
    public static function SDLFlipSurface(int $surface, int $flip): bool
    {
    }

    /**
     * @param int $surface
     * @param double $angle
     * @return array
     */
    public static function SDLRotateSurface(int $surface, float $angle): array
    {
    }

    /**
     * @param int $surface
     * @param int $width
     * @param int $height
     * @param int $scaleMode
     * @return array
     */
    public static function SDLScaleSurface(int $surface, int $width, int $height, int $scaleMode): array
    {
    }

    /**
     * @param int $surface
     * @param int $format
     * @param mixed $palette
     * @param int $colorspace
     * @param int $props
     * @return array
     */
    public static function SDLConvertSurfaceAndColorspace(int $surface, int $format, $palette = null, int $colorspace = 0, int $props = 0): array
    {
    }

    /**
     * @param int $width
     * @param int $height
     * @param int $src_format
     * @param string $src
     * @param int $src_pitch
     * @param int $dst_format
     * @param int $dst_pitch
     * @return string
     */
    public static function SDLConvertPixels(int $width, int $height, int $src_format, string $src, int $src_pitch, int $dst_format, int $dst_pitch): string
    {
    }

    /**
     * @param int $width
     * @param int $height
     * @param int $src_format
     * @param int $src_colorspace
     * @param int $src_properties
     * @param string $src
     * @param int $src_pitch
     * @param int $dst_format
     * @param int $dst_colorspace
     * @param int $dst_properties
     * @param int $dst_pitch
     * @return string
     */
    public static function SDLConvertPixelsAndColorspace(int $width, int $height, int $src_format, int $src_colorspace, int $src_properties, string $src, int $src_pitch, int $dst_format, int $dst_colorspace, int $dst_properties, int $dst_pitch): string
    {
    }

    /**
     * @param int $width
     * @param int $height
     * @param int $src_format
     * @param string $src
     * @param int $src_pitch
     * @param int $dst_format
     * @param int $dst_pitch
     * @param bool $linear
     * @return string
     */
    public static function SDLPremultiplyAlpha(int $width, int $height, int $src_format, string $src, int $src_pitch, int $dst_format, int $dst_pitch, bool $linear): string
    {
    }

    /**
     * @param int $surface
     * @param bool $linear
     * @return bool
     */
    public static function SDLPremultiplySurfaceAlpha(int $surface, bool $linear): bool
    {
    }

    /**
     * @param int $surface
     * @param double $r
     * @param double $g
     * @param double $b
     * @param double $a
     * @return bool
     */
    public static function SDLClearSurface(int $surface, float $r, float $g, float $b, float $a): bool
    {
    }

    /**
     * @param int $dst
     * @param array $rects
     * @param int $color
     * @return bool
     */
    public static function SDLFillSurfaceRects(int $dst, array $rects, int $color): bool
    {
    }

    /**
     * @param int $src
     * @param array $srcrect
     * @param int $dst
     * @param array $dstrect
     * @return bool
     */
    public static function SDLBlitSurfaceUnchecked(int $src, array $srcrect, int $dst, array $dstrect): bool
    {
    }

    /**
     * @param int $src
     * @param int $dst
     * @param mixed $srcrect
     * @param mixed $dstrect
     * @param int $scaleMode
     * @return bool
     */
    public static function SDLBlitSurfaceScaled(int $src, int $dst, $srcrect = null, $dstrect = null, int $scaleMode = 0): bool
    {
    }

    /**
     * @param int $src
     * @param array $srcrect
     * @param int $dst
     * @param array $dstrect
     * @param int $scaleMode
     * @return bool
     */
    public static function SDLBlitSurfaceUncheckedScaled(int $src, array $srcrect, int $dst, array $dstrect, int $scaleMode): bool
    {
    }

    /**
     * @param int $src
     * @param int $dst
     * @param mixed $srcrect
     * @param mixed $dstrect
     * @param int $scaleMode
     * @return bool
     */
    public static function SDLStretchSurface(int $src, int $dst, $srcrect = null, $dstrect = null, int $scaleMode = 0): bool
    {
    }

    /**
     * @param int $src
     * @param int $dst
     * @param mixed $srcrect
     * @param mixed $dstrect
     * @return bool
     */
    public static function SDLBlitSurfaceTiled(int $src, int $dst, $srcrect = null, $dstrect = null): bool
    {
    }

    /**
     * @param int $src
     * @param int $dst
     * @param double $scale
     * @param int $scaleMode
     * @param mixed $srcrect
     * @param mixed $dstrect
     * @return bool
     */
    public static function SDLBlitSurfaceTiledWithScale(int $src, int $dst, float $scale, int $scaleMode, $srcrect = null, $dstrect = null): bool
    {
    }

    /**
     * @param int $src
     * @param int $dst
     * @param int $left_width
     * @param int $right_width
     * @param int $top_height
     * @param int $bottom_height
     * @param double $scale
     * @param int $scaleMode
     * @param mixed $srcrect
     * @param mixed $dstrect
     * @return bool
     */
    public static function SDLBlitSurface9Grid(int $src, int $dst, int $left_width, int $right_width, int $top_height, int $bottom_height, float $scale, int $scaleMode, $srcrect = null, $dstrect = null): bool
    {
    }

    /**
     * @param int $surface
     * @param int $r
     * @param int $g
     * @param int $b
     * @return int
     */
    public static function SDLMapSurfaceRGB(int $surface, int $r, int $g, int $b): int
    {
    }

    /**
     * @param int $surface
     * @param int $r
     * @param int $g
     * @param int $b
     * @param int $a
     * @return int
     */
    public static function SDLMapSurfaceRGBA(int $surface, int $r, int $g, int $b, int $a): int
    {
    }

    /**
     * @param int $surface
     * @param int $x
     * @param int $y
     * @return array
     */
    public static function SDLReadSurfacePixel(int $surface, int $x, int $y): array
    {
    }

    /**
     * @param int $surface
     * @param int $x
     * @param int $y
     * @return array
     */
    public static function SDLReadSurfacePixelFloat(int $surface, int $x, int $y): array
    {
    }

    /**
     * @param int $surface
     * @param int $x
     * @param int $y
     * @param int $r
     * @param int $g
     * @param int $b
     * @param int $a
     * @return bool
     */
    public static function SDLWriteSurfacePixel(int $surface, int $x, int $y, int $r, int $g, int $b, int $a): bool
    {
    }

    /**
     * @param int $surface
     * @param int $x
     * @param int $y
     * @param double $r
     * @param double $g
     * @param double $b
     * @param double $a
     * @return bool
     */
    public static function SDLWriteSurfacePixelFloat(int $surface, int $x, int $y, float $r, float $g, float $b, float $a): bool
    {
    }

    /**
     * @param int $ncolors
     * @return array
     */
    public static function SDLCreatePalette(int $ncolors): array
    {
    }

    /**
     * @param int $palette
     * @return void
     */
    public static function SDLDestroyPalette(int $palette): void
    {
    }

    /**
     * @param int $palette
     * @param array $colors
     * @param int $firstcolor
     * @param int $ncolors
     * @return bool
     */
    public static function SDLSetPaletteColors(int $palette, array $colors, int $firstcolor, int $ncolors): bool
    {
    }

    /**
     * @param int $format
     * @return string
     */
    public static function SDLGetPixelFormatName(int $format): string
    {
    }

    /**
     * @param int $format
     * @return array
     */
    public static function SDLGetMasksForPixelFormat(int $format): array
    {
    }

    /**
     * @param int $bpp
     * @param int $rmask
     * @param int $gmask
     * @param int $bmask
     * @param int $amask
     * @return int
     */
    public static function SDLGetPixelFormatForMasks(int $bpp, int $rmask, int $gmask, int $bmask, int $amask): int
    {
    }

    /**
     * @param int $pixel
     * @param int $format_ptr
     * @param mixed $palette_ptr
     * @return array
     */
    public static function SDLGetRGB(int $pixel, int $format_ptr, $palette_ptr = null): array
    {
    }
}
