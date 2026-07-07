
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/array.h"

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



/**
 * SDL joystick subsystem — device enumeration, state queries, rumble/LED,
 * and virtual joystick injection for headless testing.
 */
ZEPHIR_INIT_CLASS(Sdl3_SDL_Input_SDLJoystick)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Input, SDLJoystick, sdl3, sdl_input_sdljoystick, sdl3_sdl_input_sdljoystick_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLLockJoysticks)
{

	
            SDL_LockJoysticks();
        
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLUnlockJoysticks)
{

	
            SDL_UnlockJoysticks();
        
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLHasJoystick)
{
	zend_bool result = 0;
	
            result = SDL_HasJoystick();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoysticks)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            int count = 0;
            SDL_JoystickID *ids = SDL_GetJoysticks(&count);

            array_init(&result);
            if (ids != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) ids[i]);
                }
                SDL_free(ids);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickNameForID)
{
	zval name;
	zval *instance_id_param = NULL;
	zend_long instance_id;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            const char *value = SDL_GetJoystickNameForID((SDL_JoystickID) instance_id);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, value);
            }
        
	RETURN_CTORW(&name);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPathForID)
{
	zval path;
	zval *instance_id_param = NULL;
	zend_long instance_id;

	ZVAL_UNDEF(&path);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            const char *value = SDL_GetJoystickPathForID((SDL_JoystickID) instance_id);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&path);
            } else {
                ZVAL_STRING(&path, value);
            }
        
	RETURN_CTORW(&path);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPlayerIndexForID)
{
	zval *instance_id_param = NULL;
	zend_long instance_id, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = (zend_long) SDL_GetJoystickPlayerIndexForID((SDL_JoystickID) instance_id);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickGUIDForID)
{
	zval guid;
	zval *instance_id_param = NULL;
	zend_long instance_id;

	ZVAL_UNDEF(&guid);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            SDL_GUID value = SDL_GetJoystickGUIDForID((SDL_JoystickID) instance_id);
            php_sdl_guid_to_string(value, &guid);
        
	RETURN_CTORW(&guid);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickVendorForID)
{
	zval *instance_id_param = NULL;
	zend_long instance_id, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = (zend_long) SDL_GetJoystickVendorForID((SDL_JoystickID) instance_id);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProductForID)
{
	zval *instance_id_param = NULL;
	zend_long instance_id, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = (zend_long) SDL_GetJoystickProductForID((SDL_JoystickID) instance_id);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProductVersionForID)
{
	zval *instance_id_param = NULL;
	zend_long instance_id, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = (zend_long) SDL_GetJoystickProductVersionForID((SDL_JoystickID) instance_id);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickTypeForID)
{
	zval *instance_id_param = NULL;
	zend_long instance_id, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = (zend_long) SDL_GetJoystickTypeForID((SDL_JoystickID) instance_id);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLOpenJoystick)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *instance_id_param = NULL, _0$$3, _1$$3, _2$$3;
	zend_long instance_id, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &instance_id_param);
	
            SDL_Joystick *joystick = SDL_OpenJoystick((SDL_JoystickID) instance_id);
            ptr = (zend_long)(uintptr_t) joystick;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_OpenJoystick failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/input/sdljoystick.zep", 302);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickFromID)
{
	zval *instance_id_param = NULL;
	zend_long instance_id, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            SDL_Joystick *joystick = SDL_GetJoystickFromID((SDL_JoystickID) instance_id);
            ptr = (zend_long)(uintptr_t) joystick;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickFromPlayerIndex)
{
	zval *player_index_param = NULL;
	zend_long player_index, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(player_index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &player_index_param);
	
            SDL_Joystick *joystick = SDL_GetJoystickFromPlayerIndex((int) player_index);
            ptr = (zend_long)(uintptr_t) joystick;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLAttachVirtualJoystick)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, instance_id = 0;
	zval *desc_param = NULL, desc_arr, _0$$3, _1$$3, _2$$3;
	zval desc;

	ZVAL_UNDEF(&desc);
	ZVAL_UNDEF(&desc_arr);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ARRAY(desc)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &desc_param);
	zephir_get_arrval(&desc, desc_param);
	ZEPHIR_CPY_WRT(&desc_arr, &desc);
	
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
        
	if (instance_id == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_AttachVirtualJoystick failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/input/sdljoystick.zep", 363);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(instance_id);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLDetachVirtualJoystick)
{
	zend_bool result = 0;
	zval *instance_id_param = NULL;
	zend_long instance_id;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = SDL_DetachVirtualJoystick((SDL_JoystickID) instance_id);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLIsJoystickVirtual)
{
	zend_bool result = 0;
	zval *instance_id_param = NULL;
	zend_long instance_id;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = SDL_IsJoystickVirtual((SDL_JoystickID) instance_id);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualAxis)
{
	zend_bool result = 0;
	zval *joystick_param = NULL, *axis_param = NULL, *value_param = NULL;
	zend_long joystick, axis, value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(axis)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &joystick_param, &axis_param, &value_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickVirtualAxis(joy, (int) axis, (Sint16) value);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualBall)
{
	zend_bool result = 0;
	zval *joystick_param = NULL, *ball_param = NULL, *xrel_param = NULL, *yrel_param = NULL;
	zend_long joystick, ball, xrel, yrel;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(ball)
		Z_PARAM_LONG(xrel)
		Z_PARAM_LONG(yrel)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &joystick_param, &ball_param, &xrel_param, &yrel_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickVirtualBall(joy, (int) ball, (Sint16) xrel, (Sint16) yrel);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualButton)
{
	zend_bool down, result = 0;
	zval *joystick_param = NULL, *button_param = NULL, *down_param = NULL;
	zend_long joystick, button;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(button)
		Z_PARAM_BOOL(down)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &joystick_param, &button_param, &down_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickVirtualButton(joy, (int) button, down);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualHat)
{
	zend_bool result = 0;
	zval *joystick_param = NULL, *hat_param = NULL, *value_param = NULL;
	zend_long joystick, hat, value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(hat)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &joystick_param, &hat_param, &value_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickVirtualHat(joy, (int) hat, (Uint8) value);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualTouchpad)
{
	double x, y, pressure;
	zend_bool down, result = 0;
	zval *joystick_param = NULL, *touchpad_param = NULL, *finger_param = NULL, *down_param = NULL, *x_param = NULL, *y_param = NULL, *pressure_param = NULL;
	zend_long joystick, touchpad, finger;

	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(touchpad)
		Z_PARAM_LONG(finger)
		Z_PARAM_BOOL(down)
		Z_PARAM_ZVAL(x)
		Z_PARAM_ZVAL(y)
		Z_PARAM_ZVAL(pressure)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(7, 0, &joystick_param, &touchpad_param, &finger_param, &down_param, &x_param, &y_param, &pressure_param);
	x = zephir_get_doubleval(x_param);
	y = zephir_get_doubleval(y_param);
	pressure = zephir_get_doubleval(pressure_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickVirtualTouchpad(joy, (int) touchpad, (int) finger, down, (float) x, (float) y, (float) pressure);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSendJoystickVirtualSensorData)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval data;
	zval *joystick_param = NULL, *type_param = NULL, *sensor_timestamp_param = NULL, *data_param = NULL, data_arr;
	zend_long joystick, type, sensor_timestamp;

	ZVAL_UNDEF(&data_arr);
	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(type)
		Z_PARAM_LONG(sensor_timestamp)
		Z_PARAM_ARRAY(data)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &joystick_param, &type_param, &sensor_timestamp_param, &data_param);
	zephir_get_arrval(&data, data_param);
	ZEPHIR_CPY_WRT(&data_arr, &data);
	
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
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProperties)
{
	zval *joystick_param = NULL;
	zend_long joystick, props = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            props = (zend_long) SDL_GetJoystickProperties(joy);
        
	RETURN_LONG(props);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickName)
{
	zval name;
	zval *joystick_param = NULL;
	zend_long joystick;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            const char *value = SDL_GetJoystickName(joy);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, value);
            }
        
	RETURN_CTORW(&name);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPath)
{
	zval path;
	zval *joystick_param = NULL;
	zend_long joystick;

	ZVAL_UNDEF(&path);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            const char *value = SDL_GetJoystickPath(joy);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&path);
            } else {
                ZVAL_STRING(&path, value);
            }
        
	RETURN_CTORW(&path);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPlayerIndex)
{
	zval *joystick_param = NULL;
	zend_long joystick, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickPlayerIndex(joy);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickPlayerIndex)
{
	zend_bool result = 0;
	zval *joystick_param = NULL, *player_index_param = NULL;
	zend_long joystick, player_index;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(player_index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &joystick_param, &player_index_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickPlayerIndex(joy, (int) player_index);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickGUID)
{
	zval guid;
	zval *joystick_param = NULL;
	zend_long joystick;

	ZVAL_UNDEF(&guid);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            SDL_GUID value = SDL_GetJoystickGUID(joy);
            php_sdl_guid_to_string(value, &guid);
        
	RETURN_CTORW(&guid);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickVendor)
{
	zval *joystick_param = NULL;
	zend_long joystick, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickVendor(joy);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProduct)
{
	zval *joystick_param = NULL;
	zend_long joystick, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickProduct(joy);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProductVersion)
{
	zval *joystick_param = NULL;
	zend_long joystick, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickProductVersion(joy);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickFirmwareVersion)
{
	zval *joystick_param = NULL;
	zend_long joystick, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickFirmwareVersion(joy);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickSerial)
{
	zval serial;
	zval *joystick_param = NULL;
	zend_long joystick;

	ZVAL_UNDEF(&serial);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            const char *value = SDL_GetJoystickSerial(joy);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&serial);
            } else {
                ZVAL_STRING(&serial, value);
            }
        
	RETURN_CTORW(&serial);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickType)
{
	zval *joystick_param = NULL;
	zend_long joystick, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickType(joy);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickGUIDInfo)
{
	zend_long vendor = 0, product = 0, version = 0, crc16 = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *guid_param = NULL, _0;
	zval guid;

	ZVAL_UNDEF(&guid);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(guid)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &guid_param);
	zephir_get_strval(&guid, guid_param);
	
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
        
	zephir_create_array(return_value, 4, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, vendor);
	zephir_array_update_string(return_value, SL("vendor"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, product);
	zephir_array_update_string(return_value, SL("product"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, version);
	zephir_array_update_string(return_value, SL("version"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, crc16);
	zephir_array_update_string(return_value, SL("crc16"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLJoystickConnected)
{
	zend_bool result = 0;
	zval *joystick_param = NULL;
	zend_long joystick;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_JoystickConnected(joy);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickID)
{
	zval *joystick_param = NULL;
	zend_long joystick, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickID(joy);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetNumJoystickAxes)
{
	zval *joystick_param = NULL;
	zend_long joystick, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetNumJoystickAxes(joy);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetNumJoystickBalls)
{
	zval *joystick_param = NULL;
	zend_long joystick, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetNumJoystickBalls(joy);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetNumJoystickHats)
{
	zval *joystick_param = NULL;
	zend_long joystick, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetNumJoystickHats(joy);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetNumJoystickButtons)
{
	zval *joystick_param = NULL;
	zend_long joystick, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetNumJoystickButtons(joy);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickEventsEnabled)
{
	zval *enabled_param = NULL;
	zend_bool enabled;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(enabled)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &enabled_param);
	
            SDL_SetJoystickEventsEnabled(enabled);
        
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLJoystickEventsEnabled)
{
	zend_bool result = 0;
	
            result = SDL_JoystickEventsEnabled();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLUpdateJoysticks)
{

	
            SDL_UpdateJoysticks();
        
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickAxis)
{
	zval *joystick_param = NULL, *axis_param = NULL;
	zend_long joystick, axis, result = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(axis)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &joystick_param, &axis_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickAxis(joy, (int) axis);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickAxisInitialState)
{
	zend_bool has_initial = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *joystick_param = NULL, *axis_param = NULL, _0;
	zend_long joystick, axis, state = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(axis)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &joystick_param, &axis_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            Sint16 axis_state = 0;

            has_initial = SDL_GetJoystickAxisInitialState(joy, (int) axis, &axis_state);
            state = (zend_long) axis_state;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_BOOL(&_0, has_initial);
	zephir_array_update_string(return_value, SL("has_initial"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, state);
	zephir_array_update_string(return_value, SL("state"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickBall)
{
	zend_bool success = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *joystick_param = NULL, *ball_param = NULL, _0;
	zend_long joystick, ball, dx = 0, dy = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(ball)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &joystick_param, &ball_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            int dx_val = 0;
            int dy_val = 0;

            success = SDL_GetJoystickBall(joy, (int) ball, &dx_val, &dy_val);
            dx = (zend_long) dx_val;
            dy = (zend_long) dy_val;
        
	zephir_create_array(return_value, 3, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_BOOL(&_0, success);
	zephir_array_update_string(return_value, SL("success"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, dx);
	zephir_array_update_string(return_value, SL("dx"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, dy);
	zephir_array_update_string(return_value, SL("dy"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickHat)
{
	zval *joystick_param = NULL, *hat_param = NULL;
	zend_long joystick, hat, result = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(hat)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &joystick_param, &hat_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickHat(joy, (int) hat);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickButton)
{
	zend_bool result = 0;
	zval *joystick_param = NULL, *button_param = NULL;
	zend_long joystick, button;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(button)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &joystick_param, &button_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_GetJoystickButton(joy, (int) button);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLRumbleJoystick)
{
	zend_bool result = 0;
	zval *joystick_param = NULL, *low_frequency_rumble_param = NULL, *high_frequency_rumble_param = NULL, *duration_ms_param = NULL;
	zend_long joystick, low_frequency_rumble, high_frequency_rumble, duration_ms;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(low_frequency_rumble)
		Z_PARAM_LONG(high_frequency_rumble)
		Z_PARAM_LONG(duration_ms)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &joystick_param, &low_frequency_rumble_param, &high_frequency_rumble_param, &duration_ms_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_RumbleJoystick(
                joy,
                (Uint16) low_frequency_rumble,
                (Uint16) high_frequency_rumble,
                (Uint32) duration_ms
            );
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLRumbleJoystickTriggers)
{
	zend_bool result = 0;
	zval *joystick_param = NULL, *left_rumble_param = NULL, *right_rumble_param = NULL, *duration_ms_param = NULL;
	zend_long joystick, left_rumble, right_rumble, duration_ms;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(left_rumble)
		Z_PARAM_LONG(right_rumble)
		Z_PARAM_LONG(duration_ms)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &joystick_param, &left_rumble_param, &right_rumble_param, &duration_ms_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_RumbleJoystickTriggers(
                joy,
                (Uint16) left_rumble,
                (Uint16) right_rumble,
                (Uint32) duration_ms
            );
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickLED)
{
	zend_bool result = 0;
	zval *joystick_param = NULL, *red_param = NULL, *green_param = NULL, *blue_param = NULL;
	zend_long joystick, red, green, blue;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(joystick)
		Z_PARAM_LONG(red)
		Z_PARAM_LONG(green)
		Z_PARAM_LONG(blue)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &joystick_param, &red_param, &green_param, &blue_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SetJoystickLED(joy, (Uint8) red, (Uint8) green, (Uint8) blue);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSendJoystickEffect)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval data;
	zval *joystick_param = NULL, *data_param = NULL;
	zend_long joystick;

	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(joystick)
		Z_PARAM_STR(data)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &joystick_param, &data_param);
	zephir_get_strval(&data, data_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = SDL_SendJoystickEffect(joy, Z_STRVAL_P(&data), (int) Z_STRLEN_P(&data));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLCloseJoystick)
{
	zval *joystick_param = NULL;
	zend_long joystick;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            SDL_CloseJoystick(joy);
        
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickConnectionState)
{
	zval *joystick_param = NULL;
	zend_long joystick, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            result = (zend_long) SDL_GetJoystickConnectionState(joy);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPowerInfo)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *joystick_param = NULL, _0;
	zend_long joystick, state = 0, percent = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(joystick)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &joystick_param);
	
            SDL_Joystick *joy = php_sdl_joystick_from_handle(joystick);
            int pct = 0;

            state = (zend_long) SDL_GetJoystickPowerInfo(joy, &pct);
            percent = (zend_long) pct;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, state);
	zephir_array_update_string(return_value, SL("state"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, percent);
	zephir_array_update_string(return_value, SL("percent"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

