namespace Sdl3\SDL\Input;

%{
#include <SDL3/SDL.h>
#include <stdio.h>

static SDL_Joystick *php_sdl_joystick_from_handle(zend_long handle)
{
    return (SDL_Joystick *)(uintptr_t) handle;
}

static zend_long php_sdl_joystick_assoc_long(zval *arr, const char *key, size_t key_len, zend_long def)
{
    zval *entry;

    if (Z_TYPE_P(arr) != IS_ARRAY) {
        return def;
    }

    entry = zend_hash_str_find(Z_ARRVAL_P(arr), key, key_len);
    return entry ? zval_get_long(entry) : def;
}

static double php_sdl_joystick_assoc_double(zval *arr, const char *key, size_t key_len, double def)
{
    zval *entry;

    if (Z_TYPE_P(arr) != IS_ARRAY) {
        return def;
    }

    entry = zend_hash_str_find(Z_ARRVAL_P(arr), key, key_len);
    return entry ? zval_get_double(entry) : def;
}

static zval *php_sdl_joystick_assoc_zval(zval *arr, const char *key, size_t key_len)
{
    if (Z_TYPE_P(arr) != IS_ARRAY) {
        return NULL;
    }

    return zend_hash_str_find(Z_ARRVAL_P(arr), key, key_len);
}

static void php_sdl_guid_to_string(SDL_GUID guid, zval *out)
{
    char buf[33];

    SDL_GUIDToString(guid, buf, (int) sizeof(buf));
    ZVAL_STRING(out, buf);
}

static SDL_GUID php_sdl_guid_from_string(const char *str)
{
    if (str == NULL) {
        SDL_GUID zero = {0};
        return zero;
    }

    return SDL_StringToGUID(str);
}

static bool php_sdl_virtual_joystick_desc_from_array(
    zval *desc_arr,
    SDL_VirtualJoystickDesc *desc,
    SDL_VirtualJoystickTouchpadDesc **touchpads_out,
    SDL_VirtualJoystickSensorDesc **sensors_out,
    char **name_copy_out
)
{
    zval *entry;
    zval *touchpads_arr;
    zval *sensors_arr;
    zend_ulong idx;
    zval *item;
    int touchpad_count = 0;
    int sensor_count = 0;

    if (Z_TYPE_P(desc_arr) != IS_ARRAY) {
        return false;
    }

    SDL_INIT_INTERFACE(desc);

    desc->type = (Uint16) php_sdl_joystick_assoc_long(desc_arr, "type", sizeof("type") - 1, SDL_JOYSTICK_TYPE_UNKNOWN);
    desc->vendor_id = (Uint16) php_sdl_joystick_assoc_long(desc_arr, "vendor_id", sizeof("vendor_id") - 1, 0);
    desc->product_id = (Uint16) php_sdl_joystick_assoc_long(desc_arr, "product_id", sizeof("product_id") - 1, 0);
    desc->naxes = (Uint16) php_sdl_joystick_assoc_long(desc_arr, "naxes", sizeof("naxes") - 1, 0);
    desc->nbuttons = (Uint16) php_sdl_joystick_assoc_long(desc_arr, "nbuttons", sizeof("nbuttons") - 1, 0);
    desc->nballs = (Uint16) php_sdl_joystick_assoc_long(desc_arr, "nballs", sizeof("nballs") - 1, 0);
    desc->nhats = (Uint16) php_sdl_joystick_assoc_long(desc_arr, "nhats", sizeof("nhats") - 1, 0);
    desc->ntouchpads = (Uint16) php_sdl_joystick_assoc_long(desc_arr, "ntouchpads", sizeof("ntouchpads") - 1, 0);
    desc->nsensors = (Uint16) php_sdl_joystick_assoc_long(desc_arr, "nsensors", sizeof("nsensors") - 1, 0);
    desc->button_mask = (Uint32) php_sdl_joystick_assoc_long(desc_arr, "button_mask", sizeof("button_mask") - 1, 0);
    desc->axis_mask = (Uint32) php_sdl_joystick_assoc_long(desc_arr, "axis_mask", sizeof("axis_mask") - 1, 0);

    entry = php_sdl_joystick_assoc_zval(desc_arr, "name", sizeof("name") - 1);
    if (entry && Z_TYPE_P(entry) == IS_STRING) {
        size_t len = Z_STRLEN_P(entry);
        *name_copy_out = emalloc(len + 1);
        memcpy(*name_copy_out, Z_STRVAL_P(entry), len);
        (*name_copy_out)[len] = '\0';
        desc->name = *name_copy_out;
    }

    touchpads_arr = php_sdl_joystick_assoc_zval(desc_arr, "touchpads", sizeof("touchpads") - 1);
    if (touchpads_arr && Z_TYPE_P(touchpads_arr) == IS_ARRAY) {
        touchpad_count = (int) zend_hash_num_elements(Z_ARRVAL_P(touchpads_arr));
        if (touchpad_count > 0) {
            *touchpads_out = ecalloc((size_t) touchpad_count, sizeof(SDL_VirtualJoystickTouchpadDesc));
            ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(touchpads_arr), idx, item) {
                if ((int) idx >= touchpad_count) {
                    break;
                }
                (*touchpads_out)[idx].nfingers = (Uint16) php_sdl_joystick_assoc_long(item, "nfingers", sizeof("nfingers") - 1, 0);
            } ZEND_HASH_FOREACH_END();
            desc->touchpads = *touchpads_out;
            desc->ntouchpads = (Uint16) touchpad_count;
        }
    }

    sensors_arr = php_sdl_joystick_assoc_zval(desc_arr, "sensors", sizeof("sensors") - 1);
    if (sensors_arr && Z_TYPE_P(sensors_arr) == IS_ARRAY) {
        sensor_count = (int) zend_hash_num_elements(Z_ARRVAL_P(sensors_arr));
        if (sensor_count > 0) {
            *sensors_out = ecalloc((size_t) sensor_count, sizeof(SDL_VirtualJoystickSensorDesc));
            ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(sensors_arr), idx, item) {
                if ((int) idx >= sensor_count) {
                    break;
                }
                (*sensors_out)[idx].type = (SDL_SensorType) php_sdl_joystick_assoc_long(item, "type", sizeof("type") - 1, 0);
                (*sensors_out)[idx].rate = (float) php_sdl_joystick_assoc_double(item, "rate", sizeof("rate") - 1, 0.0);
            } ZEND_HASH_FOREACH_END();
            desc->sensors = *sensors_out;
            desc->nsensors = (Uint16) sensor_count;
        }
    }

    return true;
}
}%

/**
 * SDL joystick subsystem — device enumeration, state queries, rumble/LED,
 * and virtual joystick injection for headless testing.
 */
class SDLJoystick
{
    public static function SDLLockJoysticks() -> void
    {
        %{
            SDL_LockJoysticks();
        }%
    }

    public static function SDLUnlockJoysticks() -> void
    {
        %{
            SDL_UnlockJoysticks();
        }%
    }

    public static function SDLHasJoystick() -> bool
    {
        bool result;

        %{
            result = SDL_HasJoystick();
        }%

        return result;
    }

    public static function SDLGetJoysticks() -> array
    {
        array result;

        %{
            int count = 0;
            SDL_JoystickID *ids = SDL_GetJoysticks(&count);

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

    public static function SDLGetJoystickNameForID(int instance_id) -> string
    {
        string name;

        %{
            const char *value = SDL_GetJoystickNameForID((SDL_JoystickID) instance_id);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, value);
            }
        }%

        return name;
    }

    public static function SDLGetJoystickPathForID(int instance_id) -> string
    {
        string path;

        %{
            const char *value = SDL_GetJoystickPathForID((SDL_JoystickID) instance_id);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&path);
            } else {
                ZVAL_STRING(&path, value);
            }
        }%

        return path;
    }

    public static function SDLGetJoystickPlayerIndexForID(int instance_id) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetJoystickPlayerIndexForID((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLGetJoystickGUIDForID(int instance_id) -> string
    {
        string guid;

        %{
            SDL_GUID value = SDL_GetJoystickGUIDForID((SDL_JoystickID) instance_id);
            php_sdl_guid_to_string(value, &guid);
        }%

        return guid;
    }

    public static function SDLGetJoystickVendorForID(int instance_id) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetJoystickVendorForID((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLGetJoystickProductForID(int instance_id) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetJoystickProductForID((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLGetJoystickProductVersionForID(int instance_id) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetJoystickProductVersionForID((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLGetJoystickTypeForID(int instance_id) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetJoystickTypeForID((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLOpenJoystick(int instance_id) -> int
    {
        int ptr;

        %{
            SDL_Joystick *joystick = SDL_OpenJoystick((SDL_JoystickID) instance_id);
            ptr = (zend_long)(uintptr_t) joystick;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_OpenJoystick failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLGetJoystickFromID(int instance_id) -> int
    {
        int ptr;

        %{
            SDL_Joystick *joystick = SDL_GetJoystickFromID((SDL_JoystickID) instance_id);
            ptr = (zend_long)(uintptr_t) joystick;
        }%

        return ptr;
    }

    public static function SDLGetJoystickFromPlayerIndex(int player_index) -> int
    {
        int ptr;

        %{
            SDL_Joystick *joystick = SDL_GetJoystickFromPlayerIndex((int) player_index);
            ptr = (zend_long)(uintptr_t) joystick;
        }%

        return ptr;
    }

    public static function SDLAttachVirtualJoystick(array desc) -> int
    {
        int instance_id;
        var desc_arr;

        let desc_arr = desc;

        %{
            SDL_VirtualJoystickDesc vdesc;
            SDL_VirtualJoystickTouchpadDesc *touchpads = NULL;
            SDL_VirtualJoystickSensorDesc *sensors = NULL;
            char *name_copy = NULL;

            if (!php_sdl_virtual_joystick_desc_from_array(&desc_arr, &vdesc, &touchpads, &sensors, &name_copy)) {
                instance_id = 0;
            } else {
                instance_id = (zend_long) SDL_AttachVirtualJoystick(&vdesc);
            }

            if (name_copy != NULL) {
                efree(name_copy);
            }
            if (touchpads != NULL) {
                efree(touchpads);
            }
            if (sensors != NULL) {
                efree(sensors);
            }
        }%

        if instance_id == 0 {
            throw new \RuntimeException("SDL_AttachVirtualJoystick failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return instance_id;
    }

    public static function SDLDetachVirtualJoystick(int instance_id) -> bool
    {
        bool result;

        %{
            result = SDL_DetachVirtualJoystick((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLIsJoystickVirtual(int instance_id) -> bool
    {
        bool result;

        %{
            result = SDL_IsJoystickVirtual((SDL_JoystickID) instance_id);
        }%

        return result;
    }

    public static function SDLSetJoystickVirtualAxis(int joystick, int axis, int value) -> bool
    {
        bool result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickVirtualAxis(joy, (int) axis, (Sint16) value);
        }%

        return result;
    }

    public static function SDLSetJoystickVirtualBall(int joystick, int ball, int xrel, int yrel) -> bool
    {
        bool result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickVirtualBall(joy, (int) ball, (Sint16) xrel, (Sint16) yrel);
        }%

        return result;
    }

    public static function SDLSetJoystickVirtualButton(int joystick, int button, bool down) -> bool
    {
        bool result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickVirtualButton(joy, (int) button, down);
        }%

        return result;
    }

    public static function SDLSetJoystickVirtualHat(int joystick, int hat, int value) -> bool
    {
        bool result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickVirtualHat(joy, (int) hat, (Uint8) value);
        }%

        return result;
    }

    public static function SDLSetJoystickVirtualTouchpad(int joystick, int touchpad, int finger, bool down, float x, float y, float pressure) -> bool
    {
        bool result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickVirtualTouchpad(joy, (int) touchpad, (int) finger, down, (float) x, (float) y, (float) pressure);
        }%

        return result;
    }

    public static function SDLSendJoystickVirtualSensorData(int joystick, int type, int sensor_timestamp, array data) -> bool
    {
        bool result;
        var data_arr;

        let data_arr = data;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            int num_values = 0;
            float *values = NULL;
            zend_ulong idx;
            zval *item;

            if (Z_TYPE_P(&data_arr) == IS_ARRAY) {
                num_values = (int) zend_hash_num_elements(Z_ARRVAL_P(&data_arr));
                if (num_values > 0) {
                    values = emalloc((size_t) num_values * sizeof(float));
                    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(&data_arr), idx, item) {
                        if ((int) idx < num_values) {
                            values[idx] = (float) zval_get_double(item);
                        }
                    } ZEND_HASH_FOREACH_END();
                }
            }

            result = SDL_SendJoystickVirtualSensorData(
                joy,
                (SDL_SensorType) type,
                (Uint64) sensor_timestamp,
                values,
                num_values
            );

            if (values != NULL) {
                efree(values);
            }
        }%

        return result;
    }

    public static function SDLGetJoystickProperties(int joystick) -> int
    {
        int props;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            props = (zend_long) SDL_GetJoystickProperties(joy);
        }%

        return props;
    }

    public static function SDLGetJoystickName(int joystick) -> string
    {
        string name;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            const char *value = SDL_GetJoystickName(joy);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, value);
            }
        }%

        return name;
    }

    public static function SDLGetJoystickPath(int joystick) -> string
    {
        string path;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            const char *value = SDL_GetJoystickPath(joy);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&path);
            } else {
                ZVAL_STRING(&path, value);
            }
        }%

        return path;
    }

    public static function SDLGetJoystickPlayerIndex(int joystick) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickPlayerIndex(joy);
        }%

        return result;
    }

    public static function SDLSetJoystickPlayerIndex(int joystick, int player_index) -> bool
    {
        bool result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickPlayerIndex(joy, (int) player_index);
        }%

        return result;
    }

    public static function SDLGetJoystickGUID(int joystick) -> string
    {
        string guid;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            SDL_GUID value = SDL_GetJoystickGUID(joy);
            php_sdl_guid_to_string(value, &guid);
        }%

        return guid;
    }

    public static function SDLGetJoystickVendor(int joystick) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickVendor(joy);
        }%

        return result;
    }

    public static function SDLGetJoystickProduct(int joystick) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickProduct(joy);
        }%

        return result;
    }

    public static function SDLGetJoystickProductVersion(int joystick) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickProductVersion(joy);
        }%

        return result;
    }

    public static function SDLGetJoystickFirmwareVersion(int joystick) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickFirmwareVersion(joy);
        }%

        return result;
    }

    public static function SDLGetJoystickSerial(int joystick) -> string
    {
        string serial;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            const char *value = SDL_GetJoystickSerial(joy);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&serial);
            } else {
                ZVAL_STRING(&serial, value);
            }
        }%

        return serial;
    }

    public static function SDLGetJoystickType(int joystick) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickType(joy);
        }%

        return result;
    }

    public static function SDLGetJoystickGUIDInfo(string guid) -> array
    {
        int vendor;
        int product;
        int version;
        int crc16;

        %{
            SDL_GUID g = php_sdl_guid_from_string(Z_STRVAL_P(&guid));
            Uint16 v = 0;
            Uint16 p = 0;
            Uint16 ver = 0;
            Uint16 crc = 0;

            SDL_GetJoystickGUIDInfo(g, &v, &p, &ver, &crc);
            vendor = (zend_long) v;
            product = (zend_long) p;
            version = (zend_long) ver;
            crc16 = (zend_long) crc;
        }%

        return ["vendor": vendor, "product": product, "version": version, "crc16": crc16];
    }

    public static function SDLJoystickConnected(int joystick) -> bool
    {
        bool result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_JoystickConnected(joy);
        }%

        return result;
    }

    public static function SDLGetJoystickID(int joystick) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickID(joy);
        }%

        return result;
    }

    public static function SDLGetNumJoystickAxes(int joystick) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetNumJoystickAxes(joy);
        }%

        return result;
    }

    public static function SDLGetNumJoystickBalls(int joystick) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetNumJoystickBalls(joy);
        }%

        return result;
    }

    public static function SDLGetNumJoystickHats(int joystick) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetNumJoystickHats(joy);
        }%

        return result;
    }

    public static function SDLGetNumJoystickButtons(int joystick) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetNumJoystickButtons(joy);
        }%

        return result;
    }

    public static function SDLSetJoystickEventsEnabled(bool enabled) -> void
    {
        %{
            SDL_SetJoystickEventsEnabled(enabled);
        }%
    }

    public static function SDLJoystickEventsEnabled() -> bool
    {
        bool result;

        %{
            result = SDL_JoystickEventsEnabled();
        }%

        return result;
    }

    public static function SDLUpdateJoysticks() -> void
    {
        %{
            SDL_UpdateJoysticks();
        }%
    }

    public static function SDLGetJoystickAxis(int joystick, int axis) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickAxis(joy, (int) axis);
        }%

        return result;
    }

    public static function SDLGetJoystickAxisInitialState(int joystick, int axis) -> array
    {
        bool has_initial;
        int state;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            Sint16 axis_state = 0;

            has_initial = SDL_GetJoystickAxisInitialState(joy, (int) axis, &axis_state);
            state = (zend_long) axis_state;
        }%

        return ["has_initial": has_initial, "state": state];
    }

    public static function SDLGetJoystickBall(int joystick, int ball) -> array
    {
        bool success;
        int dx;
        int dy;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            int dx_val = 0;
            int dy_val = 0;

            success = SDL_GetJoystickBall(joy, (int) ball, &dx_val, &dy_val);
            dx = (zend_long) dx_val;
            dy = (zend_long) dy_val;
        }%

        return ["success": success, "dx": dx, "dy": dy];
    }

    public static function SDLGetJoystickHat(int joystick, int hat) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickHat(joy, (int) hat);
        }%

        return result;
    }

    public static function SDLGetJoystickButton(int joystick, int button) -> bool
    {
        bool result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_GetJoystickButton(joy, (int) button);
        }%

        return result;
    }

    public static function SDLRumbleJoystick(int joystick, int low_frequency_rumble, int high_frequency_rumble, int duration_ms) -> bool
    {
        bool result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_RumbleJoystick(
                joy,
                (Uint16) low_frequency_rumble,
                (Uint16) high_frequency_rumble,
                (Uint32) duration_ms
            );
        }%

        return result;
    }

    public static function SDLRumbleJoystickTriggers(int joystick, int left_rumble, int right_rumble, int duration_ms) -> bool
    {
        bool result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_RumbleJoystickTriggers(
                joy,
                (Uint16) left_rumble,
                (Uint16) right_rumble,
                (Uint32) duration_ms
            );
        }%

        return result;
    }

    public static function SDLSetJoystickLED(int joystick, int red, int green, int blue) -> bool
    {
        bool result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickLED(joy, (Uint8) red, (Uint8) green, (Uint8) blue);
        }%

        return result;
    }

    public static function SDLSendJoystickEffect(int joystick, string data) -> bool
    {
        bool result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SendJoystickEffect(joy, Z_STRVAL_P(&data), (int) Z_STRLEN_P(&data));
        }%

        return result;
    }

    public static function SDLCloseJoystick(int joystick) -> void
    {
        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            SDL_CloseJoystick(joy);
        }%
    }

    public static function SDLGetJoystickConnectionState(int joystick) -> int
    {
        int result;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickConnectionState(joy);
        }%

        return result;
    }

    public static function SDLGetJoystickPowerInfo(int joystick) -> array
    {
        int state;
        int percent;

        %{
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            int pct = 0;

            state = (zend_long) SDL_GetJoystickPowerInfo(joy, &pct);
            percent = (zend_long) pct;
        }%

        return ["state": state, "percent": percent];
    }
}
