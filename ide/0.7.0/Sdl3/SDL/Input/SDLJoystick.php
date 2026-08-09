<?php

namespace Sdl3\SDL\Input;

/**
 * SDL joystick subsystem — device enumeration, state queries, rumble/LED,
 * and virtual joystick injection for headless testing.
 */
class SDLJoystick
{


    /**
     * @return void
     */
    public static function SDLLockJoysticks(): void
    {
    }

    /**
     * @return void
     */
    public static function SDLUnlockJoysticks(): void
    {
    }

    /**
     * @return bool
     */
    public static function SDLHasJoystick(): bool
    {
    }

    /**
     * @return array
     */
    public static function SDLGetJoysticks(): array
    {
    }

    /**
     * @param int $instance_id
     * @return string
     */
    public static function SDLGetJoystickNameForID(int $instance_id): string
    {
    }

    /**
     * @param int $instance_id
     * @return string
     */
    public static function SDLGetJoystickPathForID(int $instance_id): string
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLGetJoystickPlayerIndexForID(int $instance_id): int
    {
    }

    /**
     * @param int $instance_id
     * @return string
     */
    public static function SDLGetJoystickGUIDForID(int $instance_id): string
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLGetJoystickVendorForID(int $instance_id): int
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLGetJoystickProductForID(int $instance_id): int
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLGetJoystickProductVersionForID(int $instance_id): int
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLGetJoystickTypeForID(int $instance_id): int
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLOpenJoystick(int $instance_id): int
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLGetJoystickFromID(int $instance_id): int
    {
    }

    /**
     * @param int $player_index
     * @return int
     */
    public static function SDLGetJoystickFromPlayerIndex(int $player_index): int
    {
    }

    /**
     * @param array $desc
     * @return int
     */
    public static function SDLAttachVirtualJoystick(array $desc): int
    {
    }

    /**
     * @param int $instance_id
     * @return bool
     */
    public static function SDLDetachVirtualJoystick(int $instance_id): bool
    {
    }

    /**
     * @param int $instance_id
     * @return bool
     */
    public static function SDLIsJoystickVirtual(int $instance_id): bool
    {
    }

    /**
     * @param int $joystick
     * @param int $axis
     * @param int $value
     * @return bool
     */
    public static function SDLSetJoystickVirtualAxis(int $joystick, int $axis, int $value): bool
    {
    }

    /**
     * @param int $joystick
     * @param int $ball
     * @param int $xrel
     * @param int $yrel
     * @return bool
     */
    public static function SDLSetJoystickVirtualBall(int $joystick, int $ball, int $xrel, int $yrel): bool
    {
    }

    /**
     * @param int $joystick
     * @param int $button
     * @param bool $down
     * @return bool
     */
    public static function SDLSetJoystickVirtualButton(int $joystick, int $button, bool $down): bool
    {
    }

    /**
     * @param int $joystick
     * @param int $hat
     * @param int $value
     * @return bool
     */
    public static function SDLSetJoystickVirtualHat(int $joystick, int $hat, int $value): bool
    {
    }

    /**
     * @param int $joystick
     * @param int $touchpad
     * @param int $finger
     * @param bool $down
     * @param double $x
     * @param double $y
     * @param double $pressure
     * @return bool
     */
    public static function SDLSetJoystickVirtualTouchpad(int $joystick, int $touchpad, int $finger, bool $down, float $x, float $y, float $pressure): bool
    {
    }

    /**
     * @param int $joystick
     * @param int $type
     * @param int $sensor_timestamp
     * @param array $data
     * @return bool
     */
    public static function SDLSendJoystickVirtualSensorData(int $joystick, int $type, int $sensor_timestamp, array $data): bool
    {
    }

    /**
     * @param int $joystick
     * @return int
     */
    public static function SDLGetJoystickProperties(int $joystick): int
    {
    }

    /**
     * @param int $joystick
     * @return string
     */
    public static function SDLGetJoystickName(int $joystick): string
    {
    }

    /**
     * @param int $joystick
     * @return string
     */
    public static function SDLGetJoystickPath(int $joystick): string
    {
    }

    /**
     * @param int $joystick
     * @return int
     */
    public static function SDLGetJoystickPlayerIndex(int $joystick): int
    {
    }

    /**
     * @param int $joystick
     * @param int $player_index
     * @return bool
     */
    public static function SDLSetJoystickPlayerIndex(int $joystick, int $player_index): bool
    {
    }

    /**
     * @param int $joystick
     * @return string
     */
    public static function SDLGetJoystickGUID(int $joystick): string
    {
    }

    /**
     * @param int $joystick
     * @return int
     */
    public static function SDLGetJoystickVendor(int $joystick): int
    {
    }

    /**
     * @param int $joystick
     * @return int
     */
    public static function SDLGetJoystickProduct(int $joystick): int
    {
    }

    /**
     * @param int $joystick
     * @return int
     */
    public static function SDLGetJoystickProductVersion(int $joystick): int
    {
    }

    /**
     * @param int $joystick
     * @return int
     */
    public static function SDLGetJoystickFirmwareVersion(int $joystick): int
    {
    }

    /**
     * @param int $joystick
     * @return string
     */
    public static function SDLGetJoystickSerial(int $joystick): string
    {
    }

    /**
     * @param int $joystick
     * @return int
     */
    public static function SDLGetJoystickType(int $joystick): int
    {
    }

    /**
     * @param string $guid
     * @return array
     */
    public static function SDLGetJoystickGUIDInfo(string $guid): array
    {
    }

    /**
     * @param int $joystick
     * @return bool
     */
    public static function SDLJoystickConnected(int $joystick): bool
    {
    }

    /**
     * @param int $joystick
     * @return int
     */
    public static function SDLGetJoystickID(int $joystick): int
    {
    }

    /**
     * @param int $joystick
     * @return int
     */
    public static function SDLGetNumJoystickAxes(int $joystick): int
    {
    }

    /**
     * @param int $joystick
     * @return int
     */
    public static function SDLGetNumJoystickBalls(int $joystick): int
    {
    }

    /**
     * @param int $joystick
     * @return int
     */
    public static function SDLGetNumJoystickHats(int $joystick): int
    {
    }

    /**
     * @param int $joystick
     * @return int
     */
    public static function SDLGetNumJoystickButtons(int $joystick): int
    {
    }

    /**
     * @param bool $enabled
     * @return void
     */
    public static function SDLSetJoystickEventsEnabled(bool $enabled): void
    {
    }

    /**
     * @return bool
     */
    public static function SDLJoystickEventsEnabled(): bool
    {
    }

    /**
     * @return void
     */
    public static function SDLUpdateJoysticks(): void
    {
    }

    /**
     * @param int $joystick
     * @param int $axis
     * @return int
     */
    public static function SDLGetJoystickAxis(int $joystick, int $axis): int
    {
    }

    /**
     * @param int $joystick
     * @param int $axis
     * @return array
     */
    public static function SDLGetJoystickAxisInitialState(int $joystick, int $axis): array
    {
    }

    /**
     * @param int $joystick
     * @param int $ball
     * @return array
     */
    public static function SDLGetJoystickBall(int $joystick, int $ball): array
    {
    }

    /**
     * @param int $joystick
     * @param int $hat
     * @return int
     */
    public static function SDLGetJoystickHat(int $joystick, int $hat): int
    {
    }

    /**
     * @param int $joystick
     * @param int $button
     * @return bool
     */
    public static function SDLGetJoystickButton(int $joystick, int $button): bool
    {
    }

    /**
     * @param int $joystick
     * @param int $low_frequency_rumble
     * @param int $high_frequency_rumble
     * @param int $duration_ms
     * @return bool
     */
    public static function SDLRumbleJoystick(int $joystick, int $low_frequency_rumble, int $high_frequency_rumble, int $duration_ms): bool
    {
    }

    /**
     * @param int $joystick
     * @param int $left_rumble
     * @param int $right_rumble
     * @param int $duration_ms
     * @return bool
     */
    public static function SDLRumbleJoystickTriggers(int $joystick, int $left_rumble, int $right_rumble, int $duration_ms): bool
    {
    }

    /**
     * @param int $joystick
     * @param int $red
     * @param int $green
     * @param int $blue
     * @return bool
     */
    public static function SDLSetJoystickLED(int $joystick, int $red, int $green, int $blue): bool
    {
    }

    /**
     * @param int $joystick
     * @param string $data
     * @return bool
     */
    public static function SDLSendJoystickEffect(int $joystick, string $data): bool
    {
    }

    /**
     * @param int $joystick
     * @return void
     */
    public static function SDLCloseJoystick(int $joystick): void
    {
    }

    /**
     * @param int $joystick
     * @return int
     */
    public static function SDLGetJoystickConnectionState(int $joystick): int
    {
    }

    /**
     * @param int $joystick
     * @return array
     */
    public static function SDLGetJoystickPowerInfo(int $joystick): array
    {
    }
}
