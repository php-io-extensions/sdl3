namespace Sdl3\SDL\Input;

%{
#include <SDL3/SDL.h>
#include <stdio.h>

static SDL_Gamepad *php_sdl_gamepad_from_handle(zend_long handle)
{
    return (SDL_Gamepad *)(uintptr_t) handle;
}

static void php_sdl_gamepad_guid_to_string(SDL_GUID guid, zval *out)
{
    char buf[33];

    SDL_GUIDToString(guid, buf, (int) sizeof(buf));
    ZVAL_STRING(out, buf);
}

static SDL_GUID php_sdl_gamepad_guid_from_string(const char *str)
{
    if (str == NULL) {
        SDL_GUID zero = {0};
        return zero;
    }

    return SDL_StringToGUID(str);
}

static void php_sdl_gamepad_binding_to_array(SDL_GamepadBinding *binding, zval *out)
{
    array_init(out);
    add_assoc_long(out, "input_type", (zend_long) binding->input_type);
    add_assoc_long(out, "output_type", (zend_long) binding->output_type);

    switch (binding->input_type) {
        case SDL_GAMEPAD_BINDTYPE_BUTTON:
            add_assoc_long(out, "input_button", (zend_long) binding->input.button);
            break;
        case SDL_GAMEPAD_BINDTYPE_AXIS:
            add_assoc_long(out, "input_axis", (zend_long) binding->input.axis.axis);
            add_assoc_long(out, "input_axis_min", (zend_long) binding->input.axis.axis_min);
            add_assoc_long(out, "input_axis_max", (zend_long) binding->input.axis.axis_max);
            break;
        case SDL_GAMEPAD_BINDTYPE_HAT:
            add_assoc_long(out, "input_hat", (zend_long) binding->input.hat.hat);
            add_assoc_long(out, "input_hat_mask", (zend_long) binding->input.hat.hat_mask);
            break;
        default:
            break;
    }

    switch (binding->output_type) {
        case SDL_GAMEPAD_BINDTYPE_BUTTON:
            add_assoc_long(out, "output_button", (zend_long) binding->output.button);
            break;
        case SDL_GAMEPAD_BINDTYPE_AXIS:
            add_assoc_long(out, "output_axis", (zend_long) binding->output.axis.axis);
            add_assoc_long(out, "output_axis_min", (zend_long) binding->output.axis.axis_min);
            add_assoc_long(out, "output_axis_max", (zend_long) binding->output.axis.axis_max);
            break;
        default:
            break;
    }
}
}%

/**
 * SDL gamepad subsystem — mapping database, device enumeration, standard
 * button/axis queries, touchpads, sensors, rumble/LED, and bindings introspection.
 */
class SDLGamepad
{
    public static function SDLAddGamepadMapping(string mapping) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_AddGamepadMapping(Z_STRVAL_P(&mapping));
        }%

        return result;
    }

    public static function SDLAddGamepadMappingsFromFile(string file) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_AddGamepadMappingsFromFile(Z_STRVAL_P(&file));
        }%

        return result;
    }

    public static function SDLReloadGamepadMappings() -> bool
    {
        bool result;

        %{
            result = SDL_ReloadGamepadMappings();
        }%

        return result;
    }

    public static function SDLGetGamepadMappings() -> array
    {
        array result;

        %{
            int count = 0;
            char **mappings = SDL_GetGamepadMappings(&count);

            array_init(&result);
            if (mappings != NULL) {
                for (int i = 0; mappings[i] != NULL; i++) {
                    add_next_index_string(&result, mappings[i]);
                }
                SDL_free(mappings);
            }
        }%

        return result;
    }

    public static function SDLGetGamepadMappingForGUID(string guid) -> string
    {
        string mapping;

        %{
            SDL_GUID g = php_sdl_gamepad_guid_from_string(Z_STRVAL_P(&guid));
            char *value = SDL_GetGamepadMappingForGUID(g);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&mapping);
            } else {
                ZVAL_STRING(&mapping, value);
                SDL_free(value);
            }
        }%

        return mapping;
    }

    public static function SDLGetGamepadMapping(int gamepad) -> string
    {
        string mapping;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            char *value = SDL_GetGamepadMapping(pad);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&mapping);
            } else {
                ZVAL_STRING(&mapping, value);
                SDL_free(value);
            }
        }%

        return mapping;
    }

    public static function SDLSetGamepadMapping(int instance_id, var mapping = null) -> bool
    {
        bool result;
        var mapping_val;

        let mapping_val = mapping;

        %{
            const char *mapping_str = NULL;
            if (Z_TYPE_P(&mapping_val) == IS_STRING) {
                mapping_str = Z_STRVAL_P(&mapping_val);
            }
            result = SDL_SetGamepadMapping((SDL_JoystickID) instance_id, mapping_str);
        }%

        return result;
    }

    public static function SDLHasGamepad() -> bool
    {
        bool result;

        %{
            result = SDL_HasGamepad();
        }%

        return result;
    }

    public static function SDLGetGamepads() -> array
    {
        array result;

        %{
            int count = 0;
            SDL_JoystickID *ids = SDL_GetGamepads(&count);

            array_init(&result);
            if (ids != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) ids[i]);
                }
                SDL_free(ids);
            }
        }%

        return result;
    }

    public static function SDLIsGamepad(int instance_id) -> bool
    {
        bool result;

        %{
            result = SDL_IsGamepad((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLGetGamepadNameForID(int instance_id) -> string
    {
        string name;

        %{
            const char *value = SDL_GetGamepadNameForID((SDL_JoystickID) instance_id);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, value);
            }
        }%

        return name;
    }

    public static function SDLGetGamepadPathForID(int instance_id) -> string
    {
        string path;

        %{
            const char *value = SDL_GetGamepadPathForID((SDL_JoystickID) instance_id);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&path);
            } else {
                ZVAL_STRING(&path, value);
            }
        }%

        return path;
    }

    public static function SDLGetGamepadPlayerIndexForID(int instance_id) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetGamepadPlayerIndexForID((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLGetGamepadGUIDForID(int instance_id) -> string
    {
        string guid;

        %{
            SDL_GUID value = SDL_GetGamepadGUIDForID((SDL_JoystickID) instance_id);
            php_sdl_gamepad_guid_to_string(value, &guid);
        }%

        return guid;
    }

    public static function SDLGetGamepadVendorForID(int instance_id) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetGamepadVendorForID((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLGetGamepadProductForID(int instance_id) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetGamepadProductForID((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLGetGamepadProductVersionForID(int instance_id) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetGamepadProductVersionForID((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLGetGamepadTypeForID(int instance_id) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetGamepadTypeForID((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLGetRealGamepadTypeForID(int instance_id) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetRealGamepadTypeForID((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLGetGamepadMappingForID(int instance_id) -> string
    {
        string mapping;

        %{
            char *value = SDL_GetGamepadMappingForID((SDL_JoystickID) instance_id);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&mapping);
            } else {
                ZVAL_STRING(&mapping, value);
                SDL_free(value);
            }
        }%

        return mapping;
    }

    public static function SDLOpenGamepad(int instance_id) -> int
    {
        int ptr;

        %{
            SDL_Gamepad *pad = SDL_OpenGamepad((SDL_JoystickID) instance_id);
            ptr = (zend_long)(uintptr_t) pad;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_OpenGamepad failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLGetGamepadFromID(int instance_id) -> int
    {
        int ptr;

        %{
            SDL_Gamepad *pad = SDL_GetGamepadFromID((SDL_JoystickID) instance_id);
            ptr = (zend_long)(uintptr_t) pad;
        }%

        return ptr;
    }

    public static function SDLGetGamepadFromPlayerIndex(int player_index) -> int
    {
        int ptr;

        %{
            SDL_Gamepad *pad = SDL_GetGamepadFromPlayerIndex((int) player_index);
            ptr = (zend_long)(uintptr_t) pad;
        }%

        return ptr;
    }

    public static function SDLGetGamepadProperties(int gamepad) -> int
    {
        int props;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            props = (zend_long) SDL_GetGamepadProperties(pad);
        }%

        return props;
    }

    public static function SDLGetGamepadID(int gamepad) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadID(pad);
        }%

        return result;
    }

    public static function SDLGetGamepadName(int gamepad) -> string
    {
        string name;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            const char *value = SDL_GetGamepadName(pad);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, value);
            }
        }%

        return name;
    }

    public static function SDLGetGamepadPath(int gamepad) -> string
    {
        string path;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            const char *value = SDL_GetGamepadPath(pad);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&path);
            } else {
                ZVAL_STRING(&path, value);
            }
        }%

        return path;
    }

    public static function SDLGetGamepadType(int gamepad) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadType(pad);
        }%

        return result;
    }

    public static function SDLGetRealGamepadType(int gamepad) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetRealGamepadType(pad);
        }%

        return result;
    }

    public static function SDLGetGamepadPlayerIndex(int gamepad) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadPlayerIndex(pad);
        }%

        return result;
    }

    public static function SDLSetGamepadPlayerIndex(int gamepad, int player_index) -> bool
    {
        bool result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_SetGamepadPlayerIndex(pad, (int) player_index);
        }%

        return result;
    }

    public static function SDLGetGamepadVendor(int gamepad) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadVendor(pad);
        }%

        return result;
    }

    public static function SDLGetGamepadProduct(int gamepad) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadProduct(pad);
        }%

        return result;
    }

    public static function SDLGetGamepadProductVersion(int gamepad) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadProductVersion(pad);
        }%

        return result;
    }

    public static function SDLGetGamepadFirmwareVersion(int gamepad) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadFirmwareVersion(pad);
        }%

        return result;
    }

    public static function SDLGetGamepadSerial(int gamepad) -> string
    {
        string serial;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            const char *value = SDL_GetGamepadSerial(pad);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&serial);
            } else {
                ZVAL_STRING(&serial, value);
            }
        }%

        return serial;
    }

    public static function SDLGetGamepadSteamHandle(int gamepad) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadSteamHandle(pad);
        }%

        return result;
    }

    public static function SDLGetGamepadConnectionState(int gamepad) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadConnectionState(pad);
        }%

        return result;
    }

    public static function SDLGetGamepadPowerInfo(int gamepad) -> array
    {
        int state;
        int percent;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            int pct = 0;

            state = (zend_long) SDL_GetGamepadPowerInfo(pad, &pct);
            percent = (zend_long) pct;
        }%

        return ["state": state, "percent": percent];
    }

    public static function SDLGamepadConnected(int gamepad) -> bool
    {
        bool result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_GamepadConnected(pad);
        }%

        return result;
    }

    public static function SDLGetGamepadJoystick(int gamepad) -> int
    {
        int ptr;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            SDL_Joystick *joy = SDL_GetGamepadJoystick(pad);
            ptr = (zend_long)(uintptr_t) joy;
        }%

        return ptr;
    }

    public static function SDLSetGamepadEventsEnabled(bool enabled) -> void
    {
        %{
            SDL_SetGamepadEventsEnabled(enabled);
        }%
    }

    public static function SDLGamepadEventsEnabled() -> bool
    {
        bool result;

        %{
            result = SDL_GamepadEventsEnabled();
        }%

        return result;
    }

    public static function SDLGetGamepadBindings(int gamepad) -> array
    {
        array result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            int count = 0;
            SDL_GamepadBinding **bindings = SDL_GetGamepadBindings(pad, &count);
            zval item;

            array_init(&result);
            if (bindings != NULL) {
                for (int i = 0; i < count; i++) {
                    if (bindings[i] != NULL) {
                        php_sdl_gamepad_binding_to_array(bindings[i], &item);
                        add_next_index_zval(&result, &item);
                    }
                }
                SDL_free(bindings);
            }
        }%

        return result;
    }

    public static function SDLUpdateGamepads() -> void
    {
        %{
            SDL_UpdateGamepads();
        }%
    }

    public static function SDLGetGamepadTypeFromString(string str) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetGamepadTypeFromString(Z_STRVAL_P(&str));
        }%

        return result;
    }

    public static function SDLGetGamepadStringForType(int type) -> string
    {
        string value;

        %{
            const char *str = SDL_GetGamepadStringForType((SDL_GamepadType) type);
            if (str == NULL) {
                ZVAL_EMPTY_STRING(&value);
            } else {
                ZVAL_STRING(&value, str);
            }
        }%

        return value;
    }

    public static function SDLGetGamepadAxisFromString(string str) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetGamepadAxisFromString(Z_STRVAL_P(&str));
        }%

        return result;
    }

    public static function SDLGetGamepadStringForAxis(int axis) -> string
    {
        string value;

        %{
            const char *str = SDL_GetGamepadStringForAxis((SDL_GamepadAxis) axis);
            if (str == NULL) {
                ZVAL_EMPTY_STRING(&value);
            } else {
                ZVAL_STRING(&value, str);
            }
        }%

        return value;
    }

    public static function SDLGamepadHasAxis(int gamepad, int axis) -> bool
    {
        bool result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_GamepadHasAxis(pad, (SDL_GamepadAxis) axis);
        }%

        return result;
    }

    public static function SDLGetGamepadAxis(int gamepad, int axis) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadAxis(pad, (SDL_GamepadAxis) axis);
        }%

        return result;
    }

    public static function SDLGetGamepadButtonFromString(string str) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetGamepadButtonFromString(Z_STRVAL_P(&str));
        }%

        return result;
    }

    public static function SDLGetGamepadStringForButton(int button) -> string
    {
        string value;

        %{
            const char *str = SDL_GetGamepadStringForButton((SDL_GamepadButton) button);
            if (str == NULL) {
                ZVAL_EMPTY_STRING(&value);
            } else {
                ZVAL_STRING(&value, str);
            }
        }%

        return value;
    }

    public static function SDLGamepadHasButton(int gamepad, int button) -> bool
    {
        bool result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_GamepadHasButton(pad, (SDL_GamepadButton) button);
        }%

        return result;
    }

    public static function SDLGetGamepadButton(int gamepad, int button) -> bool
    {
        bool result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_GetGamepadButton(pad, (SDL_GamepadButton) button);
        }%

        return result;
    }

    public static function SDLGetGamepadButtonLabelForType(int type, int button) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetGamepadButtonLabelForType(
                (SDL_GamepadType) type,
                (SDL_GamepadButton) button
            );
        }%

        return result;
    }

    public static function SDLGetGamepadButtonLabel(int gamepad, int button) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadButtonLabel(pad, (SDL_GamepadButton) button);
        }%

        return result;
    }

    public static function SDLGetNumGamepadTouchpads(int gamepad) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetNumGamepadTouchpads(pad);
        }%

        return result;
    }

    public static function SDLGetNumGamepadTouchpadFingers(int gamepad, int touchpad) -> int
    {
        int result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetNumGamepadTouchpadFingers(pad, (int) touchpad);
        }%

        return result;
    }

    public static function SDLGetGamepadTouchpadFinger(int gamepad, int touchpad, int finger) -> array
    {
        bool success;
        bool down;
        double x;
        double y;
        double pressure;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            bool down_val = false;
            float x_val = 0.0f;
            float y_val = 0.0f;
            float pressure_val = 0.0f;

            success = SDL_GetGamepadTouchpadFinger(
                pad,
                (int) touchpad,
                (int) finger,
                &down_val,
                &x_val,
                &y_val,
                &pressure_val
            );
            down = down_val;
            x = (double) x_val;
            y = (double) y_val;
            pressure = (double) pressure_val;
        }%

        return ["success": success, "down": down, "x": x, "y": y, "pressure": pressure];
    }

    public static function SDLGamepadHasSensor(int gamepad, int type) -> bool
    {
        bool result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_GamepadHasSensor(pad, (SDL_SensorType) type);
        }%

        return result;
    }

    public static function SDLSetGamepadSensorEnabled(int gamepad, int type, bool enabled) -> bool
    {
        bool result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_SetGamepadSensorEnabled(pad, (SDL_SensorType) type, enabled);
        }%

        return result;
    }

    public static function SDLGamepadSensorEnabled(int gamepad, int type) -> bool
    {
        bool result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_GamepadSensorEnabled(pad, (SDL_SensorType) type);
        }%

        return result;
    }

    public static function SDLGetGamepadSensorDataRate(int gamepad, int type) -> double
    {
        double result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (double) SDL_GetGamepadSensorDataRate(pad, (SDL_SensorType) type);
        }%

        return result;
    }

    public static function SDLGetGamepadSensorData(int gamepad, int type, int num_values) -> array
    {
        bool success;
        array data;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            float *values = NULL;
            int count = (int) num_values;

            array_init(&data);
            if (count > 0) {
                values = emalloc((size_t) count * sizeof(float));
                success = SDL_GetGamepadSensorData(pad, (SDL_SensorType) type, values, count);
                if (success) {
                    for (int i = 0; i < count; i++) {
                        add_next_index_double(&data, (double) values[i]);
                    }
                }
                efree(values);
            } else {
                success = false;
            }
        }%

        return ["success": success, "data": data];
    }

    public static function SDLRumbleGamepad(int gamepad, int low_frequency_rumble, int high_frequency_rumble, int duration_ms) -> bool
    {
        bool result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_RumbleGamepad(
                pad,
                (Uint16) low_frequency_rumble,
                (Uint16) high_frequency_rumble,
                (Uint32) duration_ms
            );
        }%

        return result;
    }

    public static function SDLRumbleGamepadTriggers(int gamepad, int left_rumble, int right_rumble, int duration_ms) -> bool
    {
        bool result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_RumbleGamepadTriggers(
                pad,
                (Uint16) left_rumble,
                (Uint16) right_rumble,
                (Uint32) duration_ms
            );
        }%

        return result;
    }

    public static function SDLSetGamepadLED(int gamepad, int red, int green, int blue) -> bool
    {
        bool result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_SetGamepadLED(pad, (Uint8) red, (Uint8) green, (Uint8) blue);
        }%

        return result;
    }

    public static function SDLSendGamepadEffect(int gamepad, string data) -> bool
    {
        bool result;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_SendGamepadEffect(pad, Z_STRVAL_P(&data), (int) Z_STRLEN_P(&data));
        }%

        return result;
    }

    public static function SDLCloseGamepad(int gamepad) -> void
    {
        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            SDL_CloseGamepad(pad);
        }%
    }

    public static function SDLGetGamepadAppleSFSymbolsNameForButton(int gamepad, int button) -> string
    {
        string name;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            const char *value = SDL_GetGamepadAppleSFSymbolsNameForButton(pad, (SDL_GamepadButton) button);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, value);
            }
        }%

        return name;
    }

    public static function SDLGetGamepadAppleSFSymbolsNameForAxis(int gamepad, int axis) -> string
    {
        string name;

        %{
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            const char *value = SDL_GetGamepadAppleSFSymbolsNameForAxis(pad, (SDL_GamepadAxis) axis);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, value);
            }
        }%

        return name;
    }
}
