
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
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/array.h"

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



/**
 * SDL gamepad subsystem — mapping database, device enumeration, standard
 * button/axis queries, touchpads, sensors, rumble/LED, and bindings introspection.
 */
ZEPHIR_INIT_CLASS(Sdl3_SDL_Input_SDLGamepad)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Input, SDLGamepad, sdl3, sdl_input_sdlgamepad, sdl3_sdl_input_sdlgamepad_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLAddGamepadMapping)
{
	zend_long result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *mapping_param = NULL;
	zval mapping;

	ZVAL_UNDEF(&mapping);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(mapping)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &mapping_param);
	zephir_get_strval(&mapping, mapping_param);
	
            result = (zend_long) SDL_AddGamepadMapping(Z_STRVAL_P(&mapping));
        
	RETURN_MM_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLAddGamepadMappingsFromFile)
{
	zend_long result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *file_param = NULL;
	zval file;

	ZVAL_UNDEF(&file);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(file)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &file_param);
	zephir_get_strval(&file, file_param);
	
            result = (zend_long) SDL_AddGamepadMappingsFromFile(Z_STRVAL_P(&file));
        
	RETURN_MM_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLReloadGamepadMappings)
{
	zend_bool result = 0;
	
            result = SDL_ReloadGamepadMappings();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadMappings)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            int count = 0;
            char **mappings = SDL_GetGamepadMappings(&count);

            array_init(&result);
            if (mappings != NULL) {
                for (int i = 0; mappings[i] != NULL; i++) {
                    add_next_index_string(&result, mappings[i]);
                }
                SDL_free(mappings);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadMappingForGUID)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *guid_param = NULL;
	zval guid, mapping;

	ZVAL_UNDEF(&guid);
	ZVAL_UNDEF(&mapping);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(guid)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &guid_param);
	zephir_get_strval(&guid, guid_param);
	
            SDL_GUID g = php_sdl_gamepad_guid_from_string(Z_STRVAL_P(&guid));
            char *value = SDL_GetGamepadMappingForGUID(g);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&mapping);
            } else {
                ZVAL_STRING(&mapping, value);
                SDL_free(value);
            }
        
	RETURN_CTOR(&mapping);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadMapping)
{
	zval mapping;
	zval *gamepad_param = NULL;
	zend_long gamepad;

	ZVAL_UNDEF(&mapping);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            char *value = SDL_GetGamepadMapping(pad);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&mapping);
            } else {
                ZVAL_STRING(&mapping, value);
                SDL_free(value);
            }
        
	RETURN_CTORW(&mapping);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadMapping)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *instance_id_param = NULL, *mapping = NULL, mapping_sub, __$null, mapping_val;
	zend_long instance_id;

	ZVAL_UNDEF(&mapping_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&mapping_val);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(instance_id)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(mapping)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &instance_id_param, &mapping);
	if (!mapping) {
		mapping = &mapping_sub;
		mapping = &__$null;
	}
	ZEPHIR_CPY_WRT(&mapping_val, mapping);
	
            const char *mapping_str = NULL;
            if (Z_TYPE_P(&mapping_val) == IS_STRING) {
                mapping_str = Z_STRVAL_P(&mapping_val);
            }
            result = SDL_SetGamepadMapping((SDL_JoystickID) instance_id, mapping_str);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLHasGamepad)
{
	zend_bool result = 0;
	
            result = SDL_HasGamepad();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepads)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            int count = 0;
            SDL_JoystickID *ids = SDL_GetGamepads(&count);

            array_init(&result);
            if (ids != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) ids[i]);
                }
                SDL_free(ids);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLIsGamepad)
{
	zend_bool result = 0;
	zval *instance_id_param = NULL;
	zend_long instance_id;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = SDL_IsGamepad((SDL_JoystickID) instance_id);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadNameForID)
{
	zval name;
	zval *instance_id_param = NULL;
	zend_long instance_id;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            const char *value = SDL_GetGamepadNameForID((SDL_JoystickID) instance_id);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, value);
            }
        
	RETURN_CTORW(&name);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPathForID)
{
	zval path;
	zval *instance_id_param = NULL;
	zend_long instance_id;

	ZVAL_UNDEF(&path);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            const char *value = SDL_GetGamepadPathForID((SDL_JoystickID) instance_id);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&path);
            } else {
                ZVAL_STRING(&path, value);
            }
        
	RETURN_CTORW(&path);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPlayerIndexForID)
{
	zval *instance_id_param = NULL;
	zend_long instance_id, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = (zend_long) SDL_GetGamepadPlayerIndexForID((SDL_JoystickID) instance_id);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadGUIDForID)
{
	zval guid;
	zval *instance_id_param = NULL;
	zend_long instance_id;

	ZVAL_UNDEF(&guid);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            SDL_GUID value = SDL_GetGamepadGUIDForID((SDL_JoystickID) instance_id);
            php_sdl_gamepad_guid_to_string(value, &guid);
        
	RETURN_CTORW(&guid);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadVendorForID)
{
	zval *instance_id_param = NULL;
	zend_long instance_id, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = (zend_long) SDL_GetGamepadVendorForID((SDL_JoystickID) instance_id);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProductForID)
{
	zval *instance_id_param = NULL;
	zend_long instance_id, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = (zend_long) SDL_GetGamepadProductForID((SDL_JoystickID) instance_id);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProductVersionForID)
{
	zval *instance_id_param = NULL;
	zend_long instance_id, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = (zend_long) SDL_GetGamepadProductVersionForID((SDL_JoystickID) instance_id);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadTypeForID)
{
	zval *instance_id_param = NULL;
	zend_long instance_id, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = (zend_long) SDL_GetGamepadTypeForID((SDL_JoystickID) instance_id);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetRealGamepadTypeForID)
{
	zval *instance_id_param = NULL;
	zend_long instance_id, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            result = (zend_long) SDL_GetRealGamepadTypeForID((SDL_JoystickID) instance_id);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadMappingForID)
{
	zval mapping;
	zval *instance_id_param = NULL;
	zend_long instance_id;

	ZVAL_UNDEF(&mapping);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            char *value = SDL_GetGamepadMappingForID((SDL_JoystickID) instance_id);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&mapping);
            } else {
                ZVAL_STRING(&mapping, value);
                SDL_free(value);
            }
        
	RETURN_CTORW(&mapping);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLOpenGamepad)
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
	
            SDL_Gamepad *pad = SDL_OpenGamepad((SDL_JoystickID) instance_id);
            ptr = (zend_long)(uintptr_t) pad;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_OpenGamepad failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/input/sdlgamepad.zep", 359);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadFromID)
{
	zval *instance_id_param = NULL;
	zend_long instance_id, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(instance_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &instance_id_param);
	
            SDL_Gamepad *pad = SDL_GetGamepadFromID((SDL_JoystickID) instance_id);
            ptr = (zend_long)(uintptr_t) pad;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadFromPlayerIndex)
{
	zval *player_index_param = NULL;
	zend_long player_index, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(player_index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &player_index_param);
	
            SDL_Gamepad *pad = SDL_GetGamepadFromPlayerIndex((int) player_index);
            ptr = (zend_long)(uintptr_t) pad;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProperties)
{
	zval *gamepad_param = NULL;
	zend_long gamepad, props = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            props = (zend_long) SDL_GetGamepadProperties(pad);
        
	RETURN_LONG(props);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadID)
{
	zval *gamepad_param = NULL;
	zend_long gamepad, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadID(pad);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadName)
{
	zval name;
	zval *gamepad_param = NULL;
	zend_long gamepad;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            const char *value = SDL_GetGamepadName(pad);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, value);
            }
        
	RETURN_CTORW(&name);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPath)
{
	zval path;
	zval *gamepad_param = NULL;
	zend_long gamepad;

	ZVAL_UNDEF(&path);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            const char *value = SDL_GetGamepadPath(pad);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&path);
            } else {
                ZVAL_STRING(&path, value);
            }
        
	RETURN_CTORW(&path);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadType)
{
	zval *gamepad_param = NULL;
	zend_long gamepad, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadType(pad);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetRealGamepadType)
{
	zval *gamepad_param = NULL;
	zend_long gamepad, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetRealGamepadType(pad);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPlayerIndex)
{
	zval *gamepad_param = NULL;
	zend_long gamepad, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadPlayerIndex(pad);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadPlayerIndex)
{
	zend_bool result = 0;
	zval *gamepad_param = NULL, *player_index_param = NULL;
	zend_long gamepad, player_index;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(player_index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &gamepad_param, &player_index_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_SetGamepadPlayerIndex(pad, (int) player_index);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadVendor)
{
	zval *gamepad_param = NULL;
	zend_long gamepad, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadVendor(pad);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProduct)
{
	zval *gamepad_param = NULL;
	zend_long gamepad, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadProduct(pad);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProductVersion)
{
	zval *gamepad_param = NULL;
	zend_long gamepad, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadProductVersion(pad);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadFirmwareVersion)
{
	zval *gamepad_param = NULL;
	zend_long gamepad, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadFirmwareVersion(pad);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadSerial)
{
	zval serial;
	zval *gamepad_param = NULL;
	zend_long gamepad;

	ZVAL_UNDEF(&serial);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            const char *value = SDL_GetGamepadSerial(pad);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&serial);
            } else {
                ZVAL_STRING(&serial, value);
            }
        
	RETURN_CTORW(&serial);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadSteamHandle)
{
	zval *gamepad_param = NULL;
	zend_long gamepad, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadSteamHandle(pad);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadConnectionState)
{
	zval *gamepad_param = NULL;
	zend_long gamepad, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadConnectionState(pad);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPowerInfo)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *gamepad_param = NULL, _0;
	zend_long gamepad, state = 0, percent = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            int pct = 0;

            state = (zend_long) SDL_GetGamepadPowerInfo(pad, &pct);
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

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGamepadConnected)
{
	zend_bool result = 0;
	zval *gamepad_param = NULL;
	zend_long gamepad;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_GamepadConnected(pad);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadJoystick)
{
	zval *gamepad_param = NULL;
	zend_long gamepad, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            SDL_Joystick *joy = SDL_GetGamepadJoystick(pad);
            ptr = (zend_long)(uintptr_t) joy;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadEventsEnabled)
{
	zval *enabled_param = NULL;
	zend_bool enabled;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(enabled)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &enabled_param);
	
            SDL_SetGamepadEventsEnabled(enabled);
        
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGamepadEventsEnabled)
{
	zend_bool result = 0;
	
            result = SDL_GamepadEventsEnabled();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadBindings)
{
	zval result;
	zval *gamepad_param = NULL;
	zend_long gamepad;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
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
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLUpdateGamepads)
{

	
            SDL_UpdateGamepads();
        
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadTypeFromString)
{
	zend_long result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *str_param = NULL;
	zval str;

	ZVAL_UNDEF(&str);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(str)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &str_param);
	zephir_get_strval(&str, str_param);
	
            result = (zend_long) SDL_GetGamepadTypeFromString(Z_STRVAL_P(&str));
        
	RETURN_MM_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadStringForType)
{
	zval value;
	zval *type_param = NULL;
	zend_long type;

	ZVAL_UNDEF(&value);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(type)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &type_param);
	
            const char *str = SDL_GetGamepadStringForType((SDL_GamepadType) type);
            if (str == NULL) {
                ZVAL_EMPTY_STRING(&value);
            } else {
                ZVAL_STRING(&value, str);
            }
        
	RETURN_CTORW(&value);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadAxisFromString)
{
	zend_long result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *str_param = NULL;
	zval str;

	ZVAL_UNDEF(&str);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(str)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &str_param);
	zephir_get_strval(&str, str_param);
	
            result = (zend_long) SDL_GetGamepadAxisFromString(Z_STRVAL_P(&str));
        
	RETURN_MM_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadStringForAxis)
{
	zval value;
	zval *axis_param = NULL;
	zend_long axis;

	ZVAL_UNDEF(&value);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(axis)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &axis_param);
	
            const char *str = SDL_GetGamepadStringForAxis((SDL_GamepadAxis) axis);
            if (str == NULL) {
                ZVAL_EMPTY_STRING(&value);
            } else {
                ZVAL_STRING(&value, str);
            }
        
	RETURN_CTORW(&value);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGamepadHasAxis)
{
	zend_bool result = 0;
	zval *gamepad_param = NULL, *axis_param = NULL;
	zend_long gamepad, axis;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(axis)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &gamepad_param, &axis_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_GamepadHasAxis(pad, (SDL_GamepadAxis) axis);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadAxis)
{
	zval *gamepad_param = NULL, *axis_param = NULL;
	zend_long gamepad, axis, result = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(axis)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &gamepad_param, &axis_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadAxis(pad, (SDL_GamepadAxis) axis);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadButtonFromString)
{
	zend_long result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *str_param = NULL;
	zval str;

	ZVAL_UNDEF(&str);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(str)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &str_param);
	zephir_get_strval(&str, str_param);
	
            result = (zend_long) SDL_GetGamepadButtonFromString(Z_STRVAL_P(&str));
        
	RETURN_MM_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadStringForButton)
{
	zval value;
	zval *button_param = NULL;
	zend_long button;

	ZVAL_UNDEF(&value);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(button)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &button_param);
	
            const char *str = SDL_GetGamepadStringForButton((SDL_GamepadButton) button);
            if (str == NULL) {
                ZVAL_EMPTY_STRING(&value);
            } else {
                ZVAL_STRING(&value, str);
            }
        
	RETURN_CTORW(&value);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGamepadHasButton)
{
	zend_bool result = 0;
	zval *gamepad_param = NULL, *button_param = NULL;
	zend_long gamepad, button;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(button)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &gamepad_param, &button_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_GamepadHasButton(pad, (SDL_GamepadButton) button);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadButton)
{
	zend_bool result = 0;
	zval *gamepad_param = NULL, *button_param = NULL;
	zend_long gamepad, button;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(button)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &gamepad_param, &button_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_GetGamepadButton(pad, (SDL_GamepadButton) button);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadButtonLabelForType)
{
	zval *type_param = NULL, *button_param = NULL;
	zend_long type, button, result = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(type)
		Z_PARAM_LONG(button)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &type_param, &button_param);
	
            result = (zend_long) SDL_GetGamepadButtonLabelForType(
                (SDL_GamepadType) type,
                (SDL_GamepadButton) button
            );
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadButtonLabel)
{
	zval *gamepad_param = NULL, *button_param = NULL;
	zend_long gamepad, button, result = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(button)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &gamepad_param, &button_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetGamepadButtonLabel(pad, (SDL_GamepadButton) button);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetNumGamepadTouchpads)
{
	zval *gamepad_param = NULL;
	zend_long gamepad, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetNumGamepadTouchpads(pad);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetNumGamepadTouchpadFingers)
{
	zval *gamepad_param = NULL, *touchpad_param = NULL;
	zend_long gamepad, touchpad, result = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(touchpad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &gamepad_param, &touchpad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (zend_long) SDL_GetNumGamepadTouchpadFingers(pad, (int) touchpad);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadTouchpadFinger)
{
	double x = 0, y = 0, pressure = 0;
	zend_bool success = 0, down = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *gamepad_param = NULL, *touchpad_param = NULL, *finger_param = NULL, _0;
	zend_long gamepad, touchpad, finger;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(touchpad)
		Z_PARAM_LONG(finger)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &gamepad_param, &touchpad_param, &finger_param);
	
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
        
	zephir_create_array(return_value, 5, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_BOOL(&_0, success);
	zephir_array_update_string(return_value, SL("success"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_BOOL(&_0, down);
	zephir_array_update_string(return_value, SL("down"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, x);
	zephir_array_update_string(return_value, SL("x"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, y);
	zephir_array_update_string(return_value, SL("y"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, pressure);
	zephir_array_update_string(return_value, SL("pressure"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGamepadHasSensor)
{
	zend_bool result = 0;
	zval *gamepad_param = NULL, *type_param = NULL;
	zend_long gamepad, type;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(type)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &gamepad_param, &type_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_GamepadHasSensor(pad, (SDL_SensorType) type);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadSensorEnabled)
{
	zend_bool enabled, result = 0;
	zval *gamepad_param = NULL, *type_param = NULL, *enabled_param = NULL;
	zend_long gamepad, type;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(type)
		Z_PARAM_BOOL(enabled)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &gamepad_param, &type_param, &enabled_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_SetGamepadSensorEnabled(pad, (SDL_SensorType) type, enabled);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGamepadSensorEnabled)
{
	zend_bool result = 0;
	zval *gamepad_param = NULL, *type_param = NULL;
	zend_long gamepad, type;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(type)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &gamepad_param, &type_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_GamepadSensorEnabled(pad, (SDL_SensorType) type);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadSensorDataRate)
{
	double result = 0;
	zval *gamepad_param = NULL, *type_param = NULL;
	zend_long gamepad, type;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(type)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &gamepad_param, &type_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = (double) SDL_GetGamepadSensorDataRate(pad, (SDL_SensorType) type);
        
	RETURN_DOUBLE(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadSensorData)
{
	zval data;
	zend_bool success = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *gamepad_param = NULL, *type_param = NULL, *num_values_param = NULL, _0;
	zend_long gamepad, type, num_values;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(type)
		Z_PARAM_LONG(num_values)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &gamepad_param, &type_param, &num_values_param);
	
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
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_BOOL(&_0, success);
	zephir_array_update_string(return_value, SL("success"), &_0, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("data"), &data, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLRumbleGamepad)
{
	zend_bool result = 0;
	zval *gamepad_param = NULL, *low_frequency_rumble_param = NULL, *high_frequency_rumble_param = NULL, *duration_ms_param = NULL;
	zend_long gamepad, low_frequency_rumble, high_frequency_rumble, duration_ms;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(low_frequency_rumble)
		Z_PARAM_LONG(high_frequency_rumble)
		Z_PARAM_LONG(duration_ms)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &gamepad_param, &low_frequency_rumble_param, &high_frequency_rumble_param, &duration_ms_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_RumbleGamepad(
                pad,
                (Uint16) low_frequency_rumble,
                (Uint16) high_frequency_rumble,
                (Uint32) duration_ms
            );
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLRumbleGamepadTriggers)
{
	zend_bool result = 0;
	zval *gamepad_param = NULL, *left_rumble_param = NULL, *right_rumble_param = NULL, *duration_ms_param = NULL;
	zend_long gamepad, left_rumble, right_rumble, duration_ms;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(left_rumble)
		Z_PARAM_LONG(right_rumble)
		Z_PARAM_LONG(duration_ms)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &gamepad_param, &left_rumble_param, &right_rumble_param, &duration_ms_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_RumbleGamepadTriggers(
                pad,
                (Uint16) left_rumble,
                (Uint16) right_rumble,
                (Uint32) duration_ms
            );
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadLED)
{
	zend_bool result = 0;
	zval *gamepad_param = NULL, *red_param = NULL, *green_param = NULL, *blue_param = NULL;
	zend_long gamepad, red, green, blue;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(red)
		Z_PARAM_LONG(green)
		Z_PARAM_LONG(blue)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &gamepad_param, &red_param, &green_param, &blue_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_SetGamepadLED(pad, (Uint8) red, (Uint8) green, (Uint8) blue);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLSendGamepadEffect)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval data;
	zval *gamepad_param = NULL, *data_param = NULL;
	zend_long gamepad;

	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_STR(data)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &gamepad_param, &data_param);
	zephir_get_strval(&data, data_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            result = SDL_SendGamepadEffect(pad, Z_STRVAL_P(&data), (int) Z_STRLEN_P(&data));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLCloseGamepad)
{
	zval *gamepad_param = NULL;
	zend_long gamepad;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(gamepad)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &gamepad_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            SDL_CloseGamepad(pad);
        
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadAppleSFSymbolsNameForButton)
{
	zval name;
	zval *gamepad_param = NULL, *button_param = NULL;
	zend_long gamepad, button;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(button)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &gamepad_param, &button_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            const char *value = SDL_GetGamepadAppleSFSymbolsNameForButton(pad, (SDL_GamepadButton) button);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, value);
            }
        
	RETURN_CTORW(&name);
}

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadAppleSFSymbolsNameForAxis)
{
	zval name;
	zval *gamepad_param = NULL, *axis_param = NULL;
	zend_long gamepad, axis;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(gamepad)
		Z_PARAM_LONG(axis)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &gamepad_param, &axis_param);
	
            SDL_Gamepad *pad = php_sdl_gamepad_from_handle(gamepad);
            const char *value = SDL_GetGamepadAppleSFSymbolsNameForAxis(pad, (SDL_GamepadAxis) axis);
            if (value == NULL) {
                ZVAL_EMPTY_STRING(&name);
            } else {
                ZVAL_STRING(&name, value);
            }
        
	RETURN_CTORW(&name);
}

