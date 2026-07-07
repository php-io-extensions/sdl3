<?php

namespace Sdl3\SDL\Video;

class SDLVideo
{


    /**
     * @return int
     */
    public static function SDLGetNumVideoDrivers(): int
    {
    }

    /**
     * @param int $index
     * @return string
     */
    public static function SDLGetVideoDriver(int $index): string
    {
    }

    /**
     * @return string
     */
    public static function SDLGetCurrentVideoDriver(): string
    {
    }

    /**
     * @return int
     */
    public static function SDLGetSystemTheme(): int
    {
    }

    /**
     * @param int $display_id
     * @return int
     */
    public static function SDLGetDisplayProperties(int $display_id): int
    {
    }

    /**
     * @param int $display_id
     * @return array
     */
    public static function SDLGetDisplayUsableBounds(int $display_id): array
    {
    }

    /**
     * @param int $x
     * @param int $y
     * @return int
     */
    public static function SDLGetDisplayForPoint(int $x, int $y): int
    {
    }

    /**
     * @param array $rect
     * @return int
     */
    public static function SDLGetDisplayForRect(array $rect): int
    {
    }

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
     * @param int $parent
     * @param int $offset_x
     * @param int $offset_y
     * @param int $w
     * @param int $h
     * @param int $flags
     * @return int
     */
    public static function SDLCreatePopupWindow(int $parent, int $offset_x, int $offset_y, int $w, int $h, int $flags): int
    {
    }

    /**
     * @param int $props
     * @return int
     */
    public static function SDLCreateWindowWithProperties(int $props): int
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function SDLGetWindowID(int $window): int
    {
    }

    /**
     * @param int $id
     * @return int
     */
    public static function SDLGetWindowFromID(int $id): int
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function SDLGetWindowParent(int $window): int
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function SDLGetWindowProperties(int $window): int
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function SDLGetWindowFlags(int $window): int
    {
    }

    /**
     * @return array
     */
    public static function SDLGetWindows(): array
    {
    }

    /**
     * @param int $window
     * @return float
     */
    public static function SDLGetWindowPixelDensity(int $window): float
    {
    }

    /**
     * @param int $window
     * @return float
     */
    public static function SDLGetWindowDisplayScale(int $window): float
    {
    }

    /**
     * @param int $window
     * @param array $mode
     * @return bool
     */
    public static function SDLSetWindowFullscreenMode(int $window, array $mode): bool
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function SDLGetWindowFullscreenMode(int $window): array
    {
    }

    /**
     * @param int $window
     * @return string
     */
    public static function SDLGetWindowICCProfile(int $window): string
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function SDLGetWindowPixelFormat(int $window): int
    {
    }

    /**
     * @param int $window
     * @param string $title
     * @return bool
     */
    public static function SDLSetWindowTitle(int $window, string $title): bool
    {
    }

    /**
     * @param int $window
     * @return string
     */
    public static function SDLGetWindowTitle(int $window): string
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
     * @param int $x
     * @param int $y
     * @return bool
     */
    public static function SDLSetWindowPosition(int $window, int $x, int $y): bool
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
     * @param int $w
     * @param int $h
     * @return bool
     */
    public static function SDLSetWindowSize(int $window, int $w, int $h): bool
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
    public static function SDLGetWindowSafeArea(int $window): array
    {
    }

    /**
     * @param int $window
     * @param double $min_aspect
     * @param double $max_aspect
     * @return bool
     */
    public static function SDLSetWindowAspectRatio(int $window, float $min_aspect, float $max_aspect): bool
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
     * @return array
     */
    public static function SDLGetWindowBordersSize(int $window): array
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
     * @param int $min_w
     * @param int $min_h
     * @return bool
     */
    public static function SDLSetWindowMinimumSize(int $window, int $min_w, int $min_h): bool
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
     * @param int $max_w
     * @param int $max_h
     * @return bool
     */
    public static function SDLSetWindowMaximumSize(int $window, int $max_w, int $max_h): bool
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
     * @param bool $bordered
     * @return bool
     */
    public static function SDLSetWindowBordered(int $window, bool $bordered): bool
    {
    }

    /**
     * @param int $window
     * @param bool $resizable
     * @return bool
     */
    public static function SDLSetWindowResizable(int $window, bool $resizable): bool
    {
    }

    /**
     * @param int $window
     * @param bool $on_top
     * @return bool
     */
    public static function SDLSetWindowAlwaysOnTop(int $window, bool $on_top): bool
    {
    }

    /**
     * @param int $window
     * @param bool $fill
     * @return bool
     */
    public static function SDLSetWindowFillDocument(int $window, bool $fill): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLShowWindow(int $window): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLHideWindow(int $window): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLRaiseWindow(int $window): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLMaximizeWindow(int $window): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLMinimizeWindow(int $window): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLRestoreWindow(int $window): bool
    {
    }

    /**
     * @param int $window
     * @param bool $fullscreen
     * @return bool
     */
    public static function SDLSetWindowFullscreen(int $window, bool $fullscreen): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLSyncWindow(int $window): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLWindowHasSurface(int $window): bool
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function SDLGetWindowSurface(int $window): int
    {
    }

    /**
     * @param int $window
     * @param int $vsync
     * @return bool
     */
    public static function SDLSetWindowSurfaceVSync(int $window, int $vsync): bool
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function SDLGetWindowSurfaceVSync(int $window): array
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLUpdateWindowSurface(int $window): bool
    {
    }

    /**
     * @param int $window
     * @param array $rects
     * @return bool
     */
    public static function SDLUpdateWindowSurfaceRects(int $window, array $rects): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLDestroyWindowSurface(int $window): bool
    {
    }

    /**
     * @param int $window
     * @param bool $grabbed
     * @return bool
     */
    public static function SDLSetWindowKeyboardGrab(int $window, bool $grabbed): bool
    {
    }

    /**
     * @param int $window
     * @param bool $grabbed
     * @return bool
     */
    public static function SDLSetWindowMouseGrab(int $window, bool $grabbed): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLGetWindowKeyboardGrab(int $window): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLGetWindowMouseGrab(int $window): bool
    {
    }

    /**
     * @return int
     */
    public static function SDLGetGrabbedWindow(): int
    {
    }

    /**
     * @param int $window
     * @param mixed $rect
     * @return bool
     */
    public static function SDLSetWindowMouseRect(int $window, $rect = null): bool
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function SDLGetWindowMouseRect(int $window): array
    {
    }

    /**
     * @param int $window
     * @param double $opacity
     * @return bool
     */
    public static function SDLSetWindowOpacity(int $window, float $opacity): bool
    {
    }

    /**
     * @param int $window
     * @return float
     */
    public static function SDLGetWindowOpacity(int $window): float
    {
    }

    /**
     * @param int $window
     * @param mixed $parent
     * @return bool
     */
    public static function SDLSetWindowParent(int $window, $parent = null): bool
    {
    }

    /**
     * @param int $window
     * @param bool $modal
     * @return bool
     */
    public static function SDLSetWindowModal(int $window, bool $modal): bool
    {
    }

    /**
     * @param int $window
     * @param bool $focusable
     * @return bool
     */
    public static function SDLSetWindowFocusable(int $window, bool $focusable): bool
    {
    }

    /**
     * @param int $window
     * @param int $x
     * @param int $y
     * @return bool
     */
    public static function SDLShowWindowSystemMenu(int $window, int $x, int $y): bool
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return bool
     */
    public static function SDLSetWindowHitTest(int $window, $callback = null): bool
    {
    }

    /**
     * @param int $window
     * @param mixed $shape
     * @return bool
     */
    public static function SDLSetWindowShape(int $window, $shape = null): bool
    {
    }

    /**
     * @param int $window
     * @param int $operation
     * @return bool
     */
    public static function SDLFlashWindow(int $window, int $operation): bool
    {
    }

    /**
     * @param int $window
     * @param int $state
     * @return bool
     */
    public static function SDLSetWindowProgressState(int $window, int $state): bool
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function SDLGetWindowProgressState(int $window): int
    {
    }

    /**
     * @param int $window
     * @param double $value
     * @return bool
     */
    public static function SDLSetWindowProgressValue(int $window, float $value): bool
    {
    }

    /**
     * @param int $window
     * @return float
     */
    public static function SDLGetWindowProgressValue(int $window): float
    {
    }

    /**
     * @return bool
     */
    public static function SDLScreenSaverEnabled(): bool
    {
    }

    /**
     * @return bool
     */
    public static function SDLEnableScreenSaver(): bool
    {
    }

    /**
     * @return bool
     */
    public static function SDLDisableScreenSaver(): bool
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
