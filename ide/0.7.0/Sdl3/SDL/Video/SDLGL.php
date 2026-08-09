<?php

namespace Sdl3\SDL\Video;

class SDLGL
{


    /**
     * @param mixed $path
     * @return bool
     */
    public static function SDLGLLoadLibrary($path = null): bool
    {
    }

    /**
     * @param string $proc
     * @return int
     */
    public static function SDLGLGetProcAddress(string $proc): int
    {
    }

    /**
     * @return void
     */
    public static function SDLGLUnloadLibrary(): void
    {
    }

    /**
     * @param string $extension
     * @return bool
     */
    public static function SDLGLExtensionSupported(string $extension): bool
    {
    }

    /**
     * @return void
     */
    public static function SDLGLResetAttributes(): void
    {
    }

    /**
     * @param int $attr
     * @param int $value
     * @return bool
     */
    public static function SDLGLSetAttribute(int $attr, int $value): bool
    {
    }

    /**
     * @param int $attr
     * @return array
     */
    public static function SDLGLGetAttribute(int $attr): array
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function SDLGLCreateContext(int $window): int
    {
    }

    /**
     * @param int $window
     * @param int $context
     * @return bool
     */
    public static function SDLGLMakeCurrent(int $window, int $context): bool
    {
    }

    /**
     * @return int
     */
    public static function SDLGLGetCurrentWindow(): int
    {
    }

    /**
     * @return int
     */
    public static function SDLGLGetCurrentContext(): int
    {
    }

    /**
     * @param int $interval
     * @return bool
     */
    public static function SDLGLSetSwapInterval(int $interval): bool
    {
    }

    /**
     * @return array
     */
    public static function SDLGLGetSwapInterval(): array
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLGLSwapWindow(int $window): bool
    {
    }

    /**
     * @param int $context
     * @return bool
     */
    public static function SDLGLDestroyContext(int $context): bool
    {
    }

    /**
     * @param string $proc
     * @return int
     */
    public static function SDLEGLGetProcAddress(string $proc): int
    {
    }

    /**
     * @return int
     */
    public static function SDLEGLGetCurrentDisplay(): int
    {
    }

    /**
     * @return int
     */
    public static function SDLEGLGetCurrentConfig(): int
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function SDLEGLGetWindowSurface(int $window): int
    {
    }

    /**
     * @param mixed $platformCallback
     * @param mixed $surfaceCallback
     * @param mixed $contextCallback
     * @return void
     */
    public static function SDLEGLSetAttributeCallbacks($platformCallback = null, $surfaceCallback = null, $contextCallback = null): void
    {
    }
}
