<?php

namespace Sdl3\SDL\Events;

class SDLClipboardEvents
{


    /**
     * @param int $ptr
     * @return array
     */
    public static function SDLReadClipboardEvent(int $ptr): array
    {
    }

    /**
     * @param string $text
     * @return bool
     */
    public static function SDLSetClipboardText(string $text): bool
    {
    }

    /**
     * @return string
     */
    public static function SDLGetClipboardText(): string
    {
    }

    /**
     * @return bool
     */
    public static function SDLHasClipboardText(): bool
    {
    }

    /**
     * @param string $text
     * @return bool
     */
    public static function SDLSetPrimarySelectionText(string $text): bool
    {
    }

    /**
     * @return string
     */
    public static function SDLGetPrimarySelectionText(): string
    {
    }

    /**
     * @return bool
     */
    public static function SDLHasPrimarySelectionText(): bool
    {
    }

    /**
     * @return array
     */
    public static function SDLGetClipboardMimeTypes(): array
    {
    }

    /**
     * @param string $mime_type
     * @return bool
     */
    public static function SDLHasClipboardData(string $mime_type): bool
    {
    }

    /**
     * @return void
     */
    public static function SDLClearClipboardData(): void
    {
    }
}
