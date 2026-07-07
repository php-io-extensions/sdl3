<?php

namespace Sdl3\SDL\Input;

/**
 * SDL gamepad subsystem — mapping database, device enumeration, standard
 * button/axis queries, touchpads, sensors, rumble/LED, and bindings introspection.
 */
class SDLGamepad
{


    /**
     * @param string $mapping
     * @return int
     */
    public static function SDLAddGamepadMapping(string $mapping): int
    {
    }

    /**
     * @param string $file
     * @return int
     */
    public static function SDLAddGamepadMappingsFromFile(string $file): int
    {
    }

    /**
     * @return bool
     */
    public static function SDLReloadGamepadMappings(): bool
    {
    }

    /**
     * @return array
     */
    public static function SDLGetGamepadMappings(): array
    {
    }

    /**
     * @param string $guid
     * @return string
     */
    public static function SDLGetGamepadMappingForGUID(string $guid): string
    {
    }

    /**
     * @param int $gamepad
     * @return string
     */
    public static function SDLGetGamepadMapping(int $gamepad): string
    {
    }

    /**
     * @param int $instance_id
     * @param mixed $mapping
     * @return bool
     */
    public static function SDLSetGamepadMapping(int $instance_id, $mapping = null): bool
    {
    }

    /**
     * @return bool
     */
    public static function SDLHasGamepad(): bool
    {
    }

    /**
     * @return array
     */
    public static function SDLGetGamepads(): array
    {
    }

    /**
     * @param int $instance_id
     * @return bool
     */
    public static function SDLIsGamepad(int $instance_id): bool
    {
    }

    /**
     * @param int $instance_id
     * @return string
     */
    public static function SDLGetGamepadNameForID(int $instance_id): string
    {
    }

    /**
     * @param int $instance_id
     * @return string
     */
    public static function SDLGetGamepadPathForID(int $instance_id): string
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLGetGamepadPlayerIndexForID(int $instance_id): int
    {
    }

    /**
     * @param int $instance_id
     * @return string
     */
    public static function SDLGetGamepadGUIDForID(int $instance_id): string
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLGetGamepadVendorForID(int $instance_id): int
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLGetGamepadProductForID(int $instance_id): int
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLGetGamepadProductVersionForID(int $instance_id): int
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLGetGamepadTypeForID(int $instance_id): int
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLGetRealGamepadTypeForID(int $instance_id): int
    {
    }

    /**
     * @param int $instance_id
     * @return string
     */
    public static function SDLGetGamepadMappingForID(int $instance_id): string
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLOpenGamepad(int $instance_id): int
    {
    }

    /**
     * @param int $instance_id
     * @return int
     */
    public static function SDLGetGamepadFromID(int $instance_id): int
    {
    }

    /**
     * @param int $player_index
     * @return int
     */
    public static function SDLGetGamepadFromPlayerIndex(int $player_index): int
    {
    }

    /**
     * @param int $gamepad
     * @return int
     */
    public static function SDLGetGamepadProperties(int $gamepad): int
    {
    }

    /**
     * @param int $gamepad
     * @return int
     */
    public static function SDLGetGamepadID(int $gamepad): int
    {
    }

    /**
     * @param int $gamepad
     * @return string
     */
    public static function SDLGetGamepadName(int $gamepad): string
    {
    }

    /**
     * @param int $gamepad
     * @return string
     */
    public static function SDLGetGamepadPath(int $gamepad): string
    {
    }

    /**
     * @param int $gamepad
     * @return int
     */
    public static function SDLGetGamepadType(int $gamepad): int
    {
    }

    /**
     * @param int $gamepad
     * @return int
     */
    public static function SDLGetRealGamepadType(int $gamepad): int
    {
    }

    /**
     * @param int $gamepad
     * @return int
     */
    public static function SDLGetGamepadPlayerIndex(int $gamepad): int
    {
    }

    /**
     * @param int $gamepad
     * @param int $player_index
     * @return bool
     */
    public static function SDLSetGamepadPlayerIndex(int $gamepad, int $player_index): bool
    {
    }

    /**
     * @param int $gamepad
     * @return int
     */
    public static function SDLGetGamepadVendor(int $gamepad): int
    {
    }

    /**
     * @param int $gamepad
     * @return int
     */
    public static function SDLGetGamepadProduct(int $gamepad): int
    {
    }

    /**
     * @param int $gamepad
     * @return int
     */
    public static function SDLGetGamepadProductVersion(int $gamepad): int
    {
    }

    /**
     * @param int $gamepad
     * @return int
     */
    public static function SDLGetGamepadFirmwareVersion(int $gamepad): int
    {
    }

    /**
     * @param int $gamepad
     * @return string
     */
    public static function SDLGetGamepadSerial(int $gamepad): string
    {
    }

    /**
     * @param int $gamepad
     * @return int
     */
    public static function SDLGetGamepadSteamHandle(int $gamepad): int
    {
    }

    /**
     * @param int $gamepad
     * @return int
     */
    public static function SDLGetGamepadConnectionState(int $gamepad): int
    {
    }

    /**
     * @param int $gamepad
     * @return array
     */
    public static function SDLGetGamepadPowerInfo(int $gamepad): array
    {
    }

    /**
     * @param int $gamepad
     * @return bool
     */
    public static function SDLGamepadConnected(int $gamepad): bool
    {
    }

    /**
     * @param int $gamepad
     * @return int
     */
    public static function SDLGetGamepadJoystick(int $gamepad): int
    {
    }

    /**
     * @param bool $enabled
     * @return void
     */
    public static function SDLSetGamepadEventsEnabled(bool $enabled): void
    {
    }

    /**
     * @return bool
     */
    public static function SDLGamepadEventsEnabled(): bool
    {
    }

    /**
     * @param int $gamepad
     * @return array
     */
    public static function SDLGetGamepadBindings(int $gamepad): array
    {
    }

    /**
     * @return void
     */
    public static function SDLUpdateGamepads(): void
    {
    }

    /**
     * @param string $str
     * @return int
     */
    public static function SDLGetGamepadTypeFromString(string $str): int
    {
    }

    /**
     * @param int $type
     * @return string
     */
    public static function SDLGetGamepadStringForType(int $type): string
    {
    }

    /**
     * @param string $str
     * @return int
     */
    public static function SDLGetGamepadAxisFromString(string $str): int
    {
    }

    /**
     * @param int $axis
     * @return string
     */
    public static function SDLGetGamepadStringForAxis(int $axis): string
    {
    }

    /**
     * @param int $gamepad
     * @param int $axis
     * @return bool
     */
    public static function SDLGamepadHasAxis(int $gamepad, int $axis): bool
    {
    }

    /**
     * @param int $gamepad
     * @param int $axis
     * @return int
     */
    public static function SDLGetGamepadAxis(int $gamepad, int $axis): int
    {
    }

    /**
     * @param string $str
     * @return int
     */
    public static function SDLGetGamepadButtonFromString(string $str): int
    {
    }

    /**
     * @param int $button
     * @return string
     */
    public static function SDLGetGamepadStringForButton(int $button): string
    {
    }

    /**
     * @param int $gamepad
     * @param int $button
     * @return bool
     */
    public static function SDLGamepadHasButton(int $gamepad, int $button): bool
    {
    }

    /**
     * @param int $gamepad
     * @param int $button
     * @return bool
     */
    public static function SDLGetGamepadButton(int $gamepad, int $button): bool
    {
    }

    /**
     * @param int $type
     * @param int $button
     * @return int
     */
    public static function SDLGetGamepadButtonLabelForType(int $type, int $button): int
    {
    }

    /**
     * @param int $gamepad
     * @param int $button
     * @return int
     */
    public static function SDLGetGamepadButtonLabel(int $gamepad, int $button): int
    {
    }

    /**
     * @param int $gamepad
     * @return int
     */
    public static function SDLGetNumGamepadTouchpads(int $gamepad): int
    {
    }

    /**
     * @param int $gamepad
     * @param int $touchpad
     * @return int
     */
    public static function SDLGetNumGamepadTouchpadFingers(int $gamepad, int $touchpad): int
    {
    }

    /**
     * @param int $gamepad
     * @param int $touchpad
     * @param int $finger
     * @return array
     */
    public static function SDLGetGamepadTouchpadFinger(int $gamepad, int $touchpad, int $finger): array
    {
    }

    /**
     * @param int $gamepad
     * @param int $type
     * @return bool
     */
    public static function SDLGamepadHasSensor(int $gamepad, int $type): bool
    {
    }

    /**
     * @param int $gamepad
     * @param int $type
     * @param bool $enabled
     * @return bool
     */
    public static function SDLSetGamepadSensorEnabled(int $gamepad, int $type, bool $enabled): bool
    {
    }

    /**
     * @param int $gamepad
     * @param int $type
     * @return bool
     */
    public static function SDLGamepadSensorEnabled(int $gamepad, int $type): bool
    {
    }

    /**
     * @param int $gamepad
     * @param int $type
     * @return float
     */
    public static function SDLGetGamepadSensorDataRate(int $gamepad, int $type): float
    {
    }

    /**
     * @param int $gamepad
     * @param int $type
     * @param int $num_values
     * @return array
     */
    public static function SDLGetGamepadSensorData(int $gamepad, int $type, int $num_values): array
    {
    }

    /**
     * @param int $gamepad
     * @param int $low_frequency_rumble
     * @param int $high_frequency_rumble
     * @param int $duration_ms
     * @return bool
     */
    public static function SDLRumbleGamepad(int $gamepad, int $low_frequency_rumble, int $high_frequency_rumble, int $duration_ms): bool
    {
    }

    /**
     * @param int $gamepad
     * @param int $left_rumble
     * @param int $right_rumble
     * @param int $duration_ms
     * @return bool
     */
    public static function SDLRumbleGamepadTriggers(int $gamepad, int $left_rumble, int $right_rumble, int $duration_ms): bool
    {
    }

    /**
     * @param int $gamepad
     * @param int $red
     * @param int $green
     * @param int $blue
     * @return bool
     */
    public static function SDLSetGamepadLED(int $gamepad, int $red, int $green, int $blue): bool
    {
    }

    /**
     * @param int $gamepad
     * @param string $data
     * @return bool
     */
    public static function SDLSendGamepadEffect(int $gamepad, string $data): bool
    {
    }

    /**
     * @param int $gamepad
     * @return void
     */
    public static function SDLCloseGamepad(int $gamepad): void
    {
    }

    /**
     * @param int $gamepad
     * @param int $button
     * @return string
     */
    public static function SDLGetGamepadAppleSFSymbolsNameForButton(int $gamepad, int $button): string
    {
    }

    /**
     * @param int $gamepad
     * @param int $axis
     * @return string
     */
    public static function SDLGetGamepadAppleSFSymbolsNameForAxis(int $gamepad, int $axis): string
    {
    }
}
