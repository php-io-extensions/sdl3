<?php

namespace Sdl3\SDL\Events;

/**
 * Mouse-related SDL_Event union arms. Agent boundary: decode-only helpers; SDL_mouse.h API comes later.
 */
class SDLMouse
{


    /**
     * @return bool
     */
    public static function SDLHasMouse(): bool
    {
    }

    /**
     * @return array
     */
    public static function SDLGetMice(): array
    {
    }

    /**
     * @param int $instance_id
     * @return string
     */
    public static function SDLGetMouseNameForID(int $instance_id): string
    {
    }

    /**
     * @return int
     */
    public static function SDLGetMouseFocus(): int
    {
    }

    /**
     * @return array
     */
    public static function SDLGetMouseState(): array
    {
    }

    /**
     * @return array
     */
    public static function SDLGetGlobalMouseState(): array
    {
    }

    /**
     * @return array
     */
    public static function SDLGetRelativeMouseState(): array
    {
    }

    /**
     * @param int $window
     * @param double $x
     * @param double $y
     * @return void
     */
    public static function SDLWarpMouseInWindow(int $window = 0, float $x, float $y): void
    {
    }

    /**
     * @param double $x
     * @param double $y
     * @return bool
     */
    public static function SDLWarpMouseGlobal(float $x, float $y): bool
    {
    }

    /**
     * @param int $window
     * @param bool $enabled
     * @return bool
     */
    public static function SDLSetWindowRelativeMouseMode(int $window, bool $enabled): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLGetWindowRelativeMouseMode(int $window): bool
    {
    }

    /**
     * @param bool $enabled
     * @return bool
     */
    public static function SDLCaptureMouse(bool $enabled): bool
    {
    }

    /**
     * @param string $data
     * @param string $mask
     * @param int $w
     * @param int $h
     * @param int $hot_x
     * @param int $hot_y
     * @return int
     */
    public static function SDLCreateCursor(string $data, string $mask, int $w, int $h, int $hot_x, int $hot_y): int
    {
    }

    /**
     * @param int $surface
     * @param int $hot_x
     * @param int $hot_y
     * @return int
     */
    public static function SDLCreateColorCursor(int $surface, int $hot_x, int $hot_y): int
    {
    }

    /**
     * @param array $frames
     * @param int $hot_x
     * @param int $hot_y
     * @return int
     */
    public static function SDLCreateAnimatedCursor(array $frames, int $hot_x, int $hot_y): int
    {
    }

    /**
     * @param int $id
     * @return int
     */
    public static function SDLCreateSystemCursor(int $id): int
    {
    }

    /**
     * @param mixed $cursor
     * @return bool
     */
    public static function SDLSetCursor($cursor = null): bool
    {
    }

    /**
     * @return int
     */
    public static function SDLGetCursor(): int
    {
    }

    /**
     * @return int
     */
    public static function SDLGetDefaultCursor(): int
    {
    }

    /**
     * @param int $cursor
     * @return void
     */
    public static function SDLDestroyCursor(int $cursor): void
    {
    }

    /**
     * @return bool
     */
    public static function SDLShowCursor(): bool
    {
    }

    /**
     * @return bool
     */
    public static function SDLHideCursor(): bool
    {
    }

    /**
     * @return bool
     */
    public static function SDLCursorVisible(): bool
    {
    }

    /**
     * @param int $ptr
     * @return array
     */
    public static function SDLReadMouseDeviceEvent(int $ptr): array
    {
    }

    /**
     * @param int $ptr
     * @return array
     */
    public static function SDLReadMouseMotionEvent(int $ptr): array
    {
    }

    /**
     * @param int $ptr
     * @return array
     */
    public static function SDLReadMouseButtonEvent(int $ptr): array
    {
    }

    /**
     * @param int $ptr
     * @return array
     */
    public static function SDLReadMouseWheelEvent(int $ptr): array
    {
    }
}
