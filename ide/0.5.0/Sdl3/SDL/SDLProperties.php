<?php

namespace Sdl3\SDL;

class SDLProperties
{


    /**
     * @return int
     */
    public static function SDLGetGlobalProperties(): int
    {
    }

    /**
     * @return int
     */
    public static function SDLCreateProperties(): int
    {
    }

    /**
     * @param int $src
     * @param int $dst
     * @return bool
     */
    public static function SDLCopyProperties(int $src, int $dst): bool
    {
    }

    /**
     * @param int $props
     * @return bool
     */
    public static function SDLLockProperties(int $props): bool
    {
    }

    /**
     * @param int $props
     * @return void
     */
    public static function SDLUnlockProperties(int $props): void
    {
    }

    /**
     * @param int $props
     * @param string $name
     * @param mixed $value
     * @return bool
     */
    public static function SDLSetPointerProperty(int $props, string $name, $value = null): bool
    {
    }

    /**
     * @param int $props
     * @param string $name
     * @param mixed $value
     * @return bool
     */
    public static function SDLSetStringProperty(int $props, string $name, $value = null): bool
    {
    }

    /**
     * @param int $props
     * @param string $name
     * @param int $value
     * @return bool
     */
    public static function SDLSetNumberProperty(int $props, string $name, int $value): bool
    {
    }

    /**
     * @param int $props
     * @param string $name
     * @param double $value
     * @return bool
     */
    public static function SDLSetFloatProperty(int $props, string $name, float $value): bool
    {
    }

    /**
     * @param int $props
     * @param string $name
     * @param bool $value
     * @return bool
     */
    public static function SDLSetBooleanProperty(int $props, string $name, bool $value): bool
    {
    }

    /**
     * @param int $props
     * @param string $name
     * @return bool
     */
    public static function SDLHasProperty(int $props, string $name): bool
    {
    }

    /**
     * @param int $props
     * @param string $name
     * @return int
     */
    public static function SDLGetPropertyType(int $props, string $name): int
    {
    }

    /**
     * @param int $props
     * @param string $name
     * @param mixed $defaultValue
     * @return int
     */
    public static function SDLGetPointerProperty(int $props, string $name, $defaultValue = null): int
    {
    }

    /**
     * @param int $props
     * @param string $name
     * @param mixed $defaultValue
     * @return string
     */
    public static function SDLGetStringProperty(int $props, string $name, $defaultValue = null): string
    {
    }

    /**
     * @param int $props
     * @param string $name
     * @param int $defaultValue
     * @return int
     */
    public static function SDLGetNumberProperty(int $props, string $name, int $defaultValue): int
    {
    }

    /**
     * @param int $props
     * @param string $name
     * @param double $defaultValue
     * @return float
     */
    public static function SDLGetFloatProperty(int $props, string $name, float $defaultValue): float
    {
    }

    /**
     * @param int $props
     * @param string $name
     * @param bool $defaultValue
     * @return bool
     */
    public static function SDLGetBooleanProperty(int $props, string $name, bool $defaultValue): bool
    {
    }

    /**
     * @param int $props
     * @param string $name
     * @return bool
     */
    public static function SDLClearProperty(int $props, string $name): bool
    {
    }

    /**
     * @param int $props
     * @param mixed $callback
     * @return bool
     */
    public static function SDLEnumerateProperties(int $props, $callback): bool
    {
    }

    /**
     * @param int $props
     * @return void
     */
    public static function SDLDestroyProperties(int $props): void
    {
    }
}
