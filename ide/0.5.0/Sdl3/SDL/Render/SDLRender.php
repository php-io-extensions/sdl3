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

    /**
     * @return int
     */
    public static function SDLGetNumRenderDrivers(): int
    {
    }

    /**
     * @param int $index
     * @return string
     */
    public static function SDLGetRenderDriver(int $index): string
    {
    }

    /**
     * @param int $props
     * @return int
     */
    public static function SDLCreateRendererWithProperties(int $props): int
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function SDLGetRenderer(int $window): int
    {
    }

    /**
     * @param int $renderer
     * @return int
     */
    public static function SDLGetRenderWindow(int $renderer): int
    {
    }

    /**
     * @param int $renderer
     * @return string
     */
    public static function SDLGetRendererName(int $renderer): string
    {
    }

    /**
     * @param int $renderer
     * @return int
     */
    public static function SDLGetRendererProperties(int $renderer): int
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetRenderOutputSize(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetCurrentRenderOutputSize(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @param int $props
     * @return array
     */
    public static function SDLCreateTextureWithProperties(int $renderer, int $props): array
    {
    }

    /**
     * @param int $texture
     * @return int
     */
    public static function SDLGetRendererFromTexture(int $texture): int
    {
    }

    /**
     * @param int $texture
     * @param int $palette
     * @return bool
     */
    public static function SDLSetTexturePalette(int $texture, int $palette): bool
    {
    }

    /**
     * @param int $texture
     * @return int
     */
    public static function SDLGetTexturePalette(int $texture): int
    {
    }

    /**
     * @param int $texture
     * @param int $r
     * @param int $g
     * @param int $b
     * @return bool
     */
    public static function SDLSetTextureColorMod(int $texture, int $r, int $g, int $b): bool
    {
    }

    /**
     * @param int $texture
     * @return array
     */
    public static function SDLGetTextureColorMod(int $texture): array
    {
    }

    /**
     * @param int $texture
     * @return array
     */
    public static function SDLGetTextureColorModFloat(int $texture): array
    {
    }

    /**
     * @param int $texture
     * @param int $alpha
     * @return bool
     */
    public static function SDLSetTextureAlphaMod(int $texture, int $alpha): bool
    {
    }

    /**
     * @param int $texture
     * @param double $alpha
     * @return bool
     */
    public static function SDLSetTextureAlphaModFloat(int $texture, float $alpha): bool
    {
    }

    /**
     * @param int $texture
     * @return array
     */
    public static function SDLGetTextureAlphaMod(int $texture): array
    {
    }

    /**
     * @param int $texture
     * @return array
     */
    public static function SDLGetTextureAlphaModFloat(int $texture): array
    {
    }

    /**
     * @param int $texture
     * @param int $blendMode
     * @return bool
     */
    public static function SDLSetTextureBlendMode(int $texture, int $blendMode): bool
    {
    }

    /**
     * @param int $texture
     * @return array
     */
    public static function SDLGetTextureBlendMode(int $texture): array
    {
    }

    /**
     * @param int $texture
     * @return array
     */
    public static function SDLGetTextureScaleMode(int $texture): array
    {
    }

    /**
     * @param int $texture
     * @param string $pixels
     * @param int $pitch
     * @param mixed $rect
     * @return bool
     */
    public static function SDLUpdateTexture(int $texture, string $pixels, int $pitch, $rect = null): bool
    {
    }

    /**
     * @param int $texture
     * @param string $yplane
     * @param int $ypitch
     * @param string $uplane
     * @param int $upitch
     * @param string $vplane
     * @param int $vpitch
     * @param mixed $rect
     * @return bool
     */
    public static function SDLUpdateYUVTexture(int $texture, string $yplane, int $ypitch, string $uplane, int $upitch, string $vplane, int $vpitch, $rect = null): bool
    {
    }

    /**
     * @param int $texture
     * @param string $yplane
     * @param int $ypitch
     * @param string $uvplane
     * @param int $uvpitch
     * @param mixed $rect
     * @return bool
     */
    public static function SDLUpdateNVTexture(int $texture, string $yplane, int $ypitch, string $uvplane, int $uvpitch, $rect = null): bool
    {
    }

    /**
     * @param int $texture
     * @param mixed $rect
     * @return array
     */
    public static function SDLLockTexture(int $texture, $rect = null): array
    {
    }

    /**
     * @param int $renderer
     * @param mixed $texture
     * @return bool
     */
    public static function SDLSetRenderTarget(int $renderer, $texture = null): bool
    {
    }

    /**
     * @param int $renderer
     * @return int
     */
    public static function SDLGetRenderTarget(int $renderer): int
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetRenderLogicalPresentation(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetRenderLogicalPresentationRect(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @param double $windowX
     * @param double $windowY
     * @return array
     */
    public static function SDLRenderCoordinatesFromWindow(int $renderer, float $windowX, float $windowY): array
    {
    }

    /**
     * @param int $renderer
     * @param double $x
     * @param double $y
     * @return array
     */
    public static function SDLRenderCoordinatesToWindow(int $renderer, float $x, float $y): array
    {
    }

    /**
     * @param int $renderer
     * @param int $eventPtr
     * @return bool
     */
    public static function SDLConvertEventToRenderCoordinates(int $renderer, int $eventPtr): bool
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetRenderViewport(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @return bool
     */
    public static function SDLRenderViewportSet(int $renderer): bool
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetRenderSafeArea(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetRenderClipRect(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @return bool
     */
    public static function SDLRenderClipEnabled(int $renderer): bool
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetRenderScale(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetRenderDrawColor(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetRenderDrawColorFloat(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @param double $scale
     * @return bool
     */
    public static function SDLSetRenderColorScale(int $renderer, float $scale): bool
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetRenderColorScale(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @param int $blendMode
     * @return bool
     */
    public static function SDLSetRenderDrawBlendMode(int $renderer, int $blendMode): bool
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetRenderDrawBlendMode(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @param double $x
     * @param double $y
     * @return bool
     */
    public static function SDLRenderPoint(int $renderer, float $x, float $y): bool
    {
    }

    /**
     * @param int $renderer
     * @param int $texture
     * @param double $scale
     * @param mixed $srcrect
     * @param mixed $dstrect
     * @return bool
     */
    public static function SDLRenderTextureTiled(int $renderer, int $texture, float $scale, $srcrect = null, $dstrect = null): bool
    {
    }

    /**
     * @param int $renderer
     * @param int $texture
     * @param double $leftWidth
     * @param double $rightWidth
     * @param double $topHeight
     * @param double $bottomHeight
     * @param double $scale
     * @param mixed $srcrect
     * @param mixed $dstrect
     * @return bool
     */
    public static function SDLRenderTexture9Grid(int $renderer, int $texture, float $leftWidth, float $rightWidth, float $topHeight, float $bottomHeight, float $scale, $srcrect = null, $dstrect = null): bool
    {
    }

    /**
     * @param int $renderer
     * @param int $texture
     * @param double $leftWidth
     * @param double $rightWidth
     * @param double $topHeight
     * @param double $bottomHeight
     * @param double $scale
     * @param double $tileScale
     * @param mixed $srcrect
     * @param mixed $dstrect
     * @return bool
     */
    public static function SDLRenderTexture9GridTiled(int $renderer, int $texture, float $leftWidth, float $rightWidth, float $topHeight, float $bottomHeight, float $scale, float $tileScale, $srcrect = null, $dstrect = null): bool
    {
    }

    /**
     * @param int $renderer
     * @param int $texture
     * @param string $xy
     * @param int $xyStride
     * @param mixed $color
     * @param int $colorStride
     * @param mixed $uv
     * @param int $uvStride
     * @param int $numVertices
     * @param mixed $indices
     * @param int $numIndices
     * @param int $sizeIndices
     * @return bool
     */
    public static function SDLRenderGeometryRaw(int $renderer, int $texture, string $xy, int $xyStride, $color = null, int $colorStride = 0, $uv = null, int $uvStride = 0, int $numVertices = 0, $indices = null, int $numIndices = 0, int $sizeIndices = 4): bool
    {
    }

    /**
     * @param int $renderer
     * @param int $uMode
     * @param int $vMode
     * @return bool
     */
    public static function SDLSetRenderTextureAddressMode(int $renderer, int $uMode, int $vMode): bool
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetRenderTextureAddressMode(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @return bool
     */
    public static function SDLFlushRenderer(int $renderer): bool
    {
    }

    /**
     * @param int $renderer
     * @return int
     */
    public static function SDLGetRenderMetalLayer(int $renderer): int
    {
    }

    /**
     * @param int $renderer
     * @return int
     */
    public static function SDLGetRenderMetalCommandEncoder(int $renderer): int
    {
    }

    /**
     * @param int $renderer
     * @param int $waitStageMask
     * @param int $waitSemaphore
     * @param int $signalSemaphore
     * @return bool
     */
    public static function SDLAddVulkanRenderSemaphores(int $renderer, int $waitStageMask, int $waitSemaphore, int $signalSemaphore): bool
    {
    }

    /**
     * @param int $renderer
     * @param int $vsync
     * @return bool
     */
    public static function SDLSetRenderVSync(int $renderer, int $vsync): bool
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetRenderVSync(int $renderer): array
    {
    }

    /**
     * @param int $renderer
     * @param int $scaleMode
     * @return bool
     */
    public static function SDLSetDefaultTextureScaleMode(int $renderer, int $scaleMode): bool
    {
    }

    /**
     * @param int $renderer
     * @return array
     */
    public static function SDLGetDefaultTextureScaleMode(int $renderer): array
    {
    }
}
