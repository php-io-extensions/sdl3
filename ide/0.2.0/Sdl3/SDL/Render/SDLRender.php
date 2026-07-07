<?php

namespace Sdl3\SDL\Render;

class SDLRender
{


    /**
     * @param int $window
     * @param mixed $name
     * @return int
     */
    public static function SDLCreateRenderer(int $window, $name = null): int
    {
    }

    /**
     * @param int $surface
     * @return int
     */
    public static function SDLCreateSoftwareRenderer(int $surface): int
    {
    }

    /**
     * @param int $renderer
     * @return void
     */
    public static function SDLRenderClear(int $renderer): void
    {
    }

    /**
     * @param int $renderer
     * @return bool
     */
    public static function SDLRenderPresent(int $renderer): bool
    {
    }

    /**
     * @param int $renderer
     * @param int $texture
     * @param mixed $srcrect
     * @param mixed $dstrect
     * @return bool
     */
    public static function SDLRenderTexture(int $renderer, int $texture, $srcrect = null, $dstrect = null): bool
    {
    }

    /**
     * @param int $renderer
     * @param int $texture
     * @param double $angle
     * @param int $flip
     * @param mixed $srcrect
     * @param mixed $dstrect
     * @param mixed $center
     * @return bool
     */
    public static function SDLRenderTextureRotated(int $renderer, int $texture, float $angle, int $flip, $srcrect = null, $dstrect = null, $center = null): bool
    {
    }

    /**
     * @param int $renderer
     * @param int $r
     * @param int $g
     * @param int $b
     * @param int $a
     * @return bool
     */
    public static function SDLSetRenderDrawColor(int $renderer, int $r, int $g, int $b, int $a): bool
    {
    }

    /**
     * @param int $renderer
     * @param double $r
     * @param double $g
     * @param double $b
     * @param double $a
     * @return bool
     */
    public static function SDLSetRenderDrawColorFloat(int $renderer, float $r, float $g, float $b, float $a): bool
    {
    }

    /**
     * @param int $renderer
     * @param int $format
     * @param int $access
     * @param int $w
     * @param int $h
     * @return array
     */
    public static function SDLCreateTexture(int $renderer, int $format, int $access, int $w, int $h): array
    {
    }

    /**
     * @param int $renderer
     * @param int $surface
     * @return array
     */
    public static function SDLCreateTextureFromSurface(int $renderer, int $surface): array
    {
    }

    /**
     * @param int $texture
     * @param mixed $rect
     * @return array
     */
    public static function SDLLockTextureToSurface(int $texture, $rect = null): array
    {
    }

    /**
     * @param int $texture
     * @return void
     */
    public static function SDLUnlockTexture(int $texture): void
    {
    }

    /**
     * @param int $texture
     * @param double $r
     * @param double $g
     * @param double $b
     * @return bool
     */
    public static function SDLSetTextureColorModFloat(int $texture, float $r, float $g, float $b): bool
    {
    }

    /**
     * @param int $texture
     * @param int $scaleMode
     * @return bool
     */
    public static function SDLSetTextureScaleMode(int $texture, int $scaleMode): bool
    {
    }

    /**
     * @param int $texture
     * @return array
     */
    public static function SDLGetTextureSize(int $texture): array
    {
    }

    /**
     * @param int $renderer
     * @param int $w
     * @param int $h
     * @param int $mode
     * @return bool
     */
    public static function SDLSetRenderLogicalPresentation(int $renderer, int $w, int $h, int $mode): bool
    {
    }

    /**
     * @param int $renderer
     * @return void
     */
    public static function SDLDestroyRenderer(int $renderer): void
    {
    }

    /**
     * @param int $texture
     * @return void
     */
    public static function SDLDestroyTexture(int $texture): void
    {
    }

    /**
     * @param int $renderer
     * @param mixed $rect
     * @return bool
     */
    public static function SDLRenderFillRect(int $renderer, $rect = null): bool
    {
    }

    /**
     * @param int $renderer
     * @param mixed $rect
     * @return bool
     */
    public static function SDLSetRenderViewport(int $renderer, $rect = null): bool
    {
    }

    /**
     * @param int $renderer
     * @param mixed $rect
     * @return bool
     */
    public static function SDLSetRenderClipRect(int $renderer, $rect = null): bool
    {
    }

    /**
     * @param int $renderer
     * @param mixed $rect
     * @return array
     */
    public static function SDLRenderReadPixels(int $renderer, $rect = null): array
    {
    }

    /**
     * @param int $texture
     * @param int $surface
     * @return bool
     */
    public static function SDLUpdateTextureFromSurface(int $texture, int $surface): bool
    {
    }

    /**
     * @param int $renderer
     * @param double $x
     * @param double $y
     * @param string $str
     * @return bool
     */
    public static function SDLRenderDebugText(int $renderer, float $x, float $y, string $str): bool
    {
    }

    /**
     * @param int $renderer
     * @param double $scaleX
     * @param double $scaleY
     * @return bool
     */
    public static function SDLSetRenderScale(int $renderer, float $scaleX, float $scaleY): bool
    {
    }

    /**
     * @param int $renderer
     * @param int $texture
     * @param mixed $origin
     * @param mixed $right
     * @param mixed $down
     * @param mixed $srcrect
     * @return bool
     */
    public static function SDLRenderTextureAffine(int $renderer, int $texture, $origin, $right, $down, $srcrect = null): bool
    {
    }

    /**
     * @param int $renderer
     * @param array $rects
     * @param int $count
     * @return bool
     */
    public static function SDLRenderFillRects(int $renderer, array $rects, int $count): bool
    {
    }

    /**
     * @param int $renderer
     * @param array $rects
     * @param int $count
     * @return bool
     */
    public static function SDLRenderRects(int $renderer, array $rects, int $count): bool
    {
    }

    /**
     * @param int $renderer
     * @param double $x1
     * @param double $y1
     * @param double $x2
     * @param double $y2
     * @return bool
     */
    public static function SDLRenderLine(int $renderer, float $x1, float $y1, float $x2, float $y2): bool
    {
    }

    /**
     * @param int $renderer
     * @param mixed $rect
     * @return bool
     */
    public static function SDLRenderRect(int $renderer, $rect = null): bool
    {
    }

    /**
     * @param int $renderer
     * @param array $points
     * @param int $count
     * @return bool
     */
    public static function SDLRenderPoints(int $renderer, array $points, int $count): bool
    {
    }

    /**
     * @param int $renderer
     * @param int $texture
     * @param array $vertices
     * @param int $num_vertices
     * @param int $num_indices
     * @param mixed $indices
     * @return bool
     */
    public static function SDLRenderGeometry(int $renderer, int $texture, array $vertices, int $num_vertices, int $num_indices, $indices = null): bool
    {
    }

    /**
     * @param int $renderer
     * @param array $points
     * @param int $count
     * @return bool
     */
    public static function SDLRenderLines(int $renderer, array $points, int $count): bool
    {
    }
}
