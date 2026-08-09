<?php

namespace Sdl3\SDL\Events;

class SDLKeyboard
{


    /**
     * @return bool
     */
    public static function SDLHasKeyboard(): bool
    {
    }

    /**
     * @return array
     */
    public static function SDLGetKeyboards(): array
    {
    }

    /**
     * @param int $instance_id
     * @return string
     */
    public static function SDLGetKeyboardNameForID(int $instance_id): string
    {
    }

    /**
     * @return int
     */
    public static function SDLGetKeyboardFocus(): int
    {
    }

    /**
     * @return array
     */
    public static function SDLGetKeyboardState(): array
    {
    }

    /**
     * @return int
     */
    public static function SDLGetModState(): int
    {
    }

    /**
     * @param int $modstate
     * @return void
     */
    public static function SDLSetModState(int $modstate): void
    {
    }

    /**
     * @param int $scancode
     * @param int $modstate
     * @param bool $key_event
     * @return int
     */
    public static function SDLGetKeyFromScancode(int $scancode, int $modstate = 0, bool $key_event = true): int
    {
    }

    /**
     * @param int $key
     * @return array
     */
    public static function SDLGetScancodeFromKey(int $key): array
    {
    }

    /**
     * @param int $scancode
     * @param string $name
     * @return bool
     */
    public static function SDLSetScancodeName(int $scancode, string $name): bool
    {
    }

    /**
     * @param int $scancode
     * @return string
     */
    public static function SDLGetScancodeName(int $scancode): string
    {
    }

    /**
     * @param string $name
     * @return int
     */
    public static function SDLGetScancodeFromName(string $name): int
    {
    }

    /**
     * @param int $key
     * @return string
     */
    public static function SDLGetKeyName(int $key): string
    {
    }

    /**
     * @param string $name
     * @return int
     */
    public static function SDLGetKeyFromName(string $name): int
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLStartTextInput(int $window): bool
    {
    }

    /**
     * @param int $window
     * @param int $props
     * @return bool
     */
    public static function SDLStartTextInputWithProperties(int $window, int $props): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLTextInputActive(int $window): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLStopTextInput(int $window): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLClearComposition(int $window): bool
    {
    }

    /**
     * @param int $window
     * @param mixed $rect
     * @param int $cursor
     * @return bool
     */
    public static function SDLSetTextInputArea(int $window, $rect = null, int $cursor = 0): bool
    {
    }

    /**
     * @param int $window
     * @return array|null
     */
    public static function SDLGetTextInputArea(int $window): array|null
    {
    }

    /**
     * @return bool
     */
    public static function SDLHasScreenKeyboardSupport(): bool
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function SDLScreenKeyboardShown(int $window): bool
    {
    }

    /**
     * @param int $ptr
     * @return array
     */
    public static function SDLReadKeyboardEvent(int $ptr): array
    {
    }

    /**
     * @param int $ptr
     * @return array
     */
    public static function SDLReadTextInputEvent(int $ptr): array
    {
    }

    /**
     * @param int $ptr
     * @return array
     */
    public static function SDLReadTextEditingEvent(int $ptr): array
    {
    }

    /**
     * @param int $ptr
     * @return array
     */
    public static function SDLReadTextEditingCandidatesEvent(int $ptr): array
    {
    }

    /**
     * @param int $ptr
     * @return array
     */
    public static function SDLReadKeyboardDeviceEvent(int $ptr): array
    {
    }
}
