
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/operators.h"

#include <SDL3/SDL.h>
#include <stdio.h>

typedef struct _php_sdl_properties_enum_context {
    zval callback;
} php_sdl_properties_enum_context;

static php_sdl_properties_enum_context *php_sdl_properties_enum_context_alloc(zval *callback)
{
    php_sdl_properties_enum_context *ctx = emalloc(sizeof(php_sdl_properties_enum_context));

    ZVAL_UNDEF(&ctx->callback);
    ZVAL_COPY(&ctx->callback, callback);

    return ctx;
}

static void php_sdl_properties_enum_context_free(php_sdl_properties_enum_context *ctx)
{
    if (!ctx) {
        return;
    }

    zval_ptr_dtor(&ctx->callback);
    efree(ctx);
}

static void SDLCALL php_sdl_enumerate_properties_bridge(void *userdata, SDL_PropertiesID props, const char *name)
{
    php_sdl_properties_enum_context *ctx = (php_sdl_properties_enum_context *) userdata;
    zval retval;
    zval params[2];

    if (ctx == NULL || name == NULL) {
        return;
    }

    ZVAL_LONG(&params[0], (zend_long) props);
    ZVAL_STRING(&params[1], (char *) name);
    ZVAL_UNDEF(&retval);

    call_user_function(EG(function_table), NULL, &ctx->callback, &retval, 2, params);

    if (!Z_ISUNDEF(retval)) {
        zval_ptr_dtor(&retval);
    }

    zval_ptr_dtor(&params[1]);
}



ZEPHIR_INIT_CLASS(Sdl3_SDL_SDLProperties)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL, SDLProperties, sdl3, sdl_sdlproperties, sdl3_sdl_sdlproperties_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetGlobalProperties)
{
	zend_long props = 0;
	
            props = (zend_long) SDL_GetGlobalProperties();
        
	RETURN_LONG(props);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLCreateProperties)
{
	zval _0$$3, _1$$3, _2$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, props = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	
            props = (zend_long) SDL_CreateProperties();
        
	if (props == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateProperties failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/sdlproperties.zep", 76);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(props);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLCopyProperties)
{
	zend_bool result = 0;
	zval *src_param = NULL, *dst_param = NULL;
	zend_long src, dst;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(src)
		Z_PARAM_LONG(dst)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &src_param, &dst_param);
	
            result = SDL_CopyProperties((SDL_PropertiesID) src, (SDL_PropertiesID) dst);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLLockProperties)
{
	zend_bool result = 0;
	zval *props_param = NULL;
	zend_long props;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(props)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &props_param);
	
            result = SDL_LockProperties((SDL_PropertiesID) props);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLUnlockProperties)
{
	zval *props_param = NULL;
	zend_long props;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(props)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &props_param);
	
            SDL_UnlockProperties((SDL_PropertiesID) props);
        
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLSetPointerProperty)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval name;
	zval *props_param = NULL, *name_param = NULL, *value = NULL, value_sub, __$null;
	zend_long props;

	ZVAL_UNDEF(&value_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&name);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &props_param, &name_param, &value);
	zephir_get_strval(&name, name_param);
	if (!value) {
		value = &value_sub;
		value = &__$null;
	}
	
            void *ptr = NULL;

            if (Z_TYPE_P(value) != IS_NULL) {
                ptr = (void *)(uintptr_t) Z_LVAL_P(value);
            }

            result = SDL_SetPointerProperty((SDL_PropertiesID) props, Z_STRVAL(name), ptr);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLSetStringProperty)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval name;
	zval *props_param = NULL, *name_param = NULL, *value = NULL, value_sub, __$null;
	zend_long props;

	ZVAL_UNDEF(&value_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&name);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &props_param, &name_param, &value);
	zephir_get_strval(&name, name_param);
	if (!value) {
		value = &value_sub;
		value = &__$null;
	}
	
            const char *str_val = NULL;

            if (Z_TYPE_P(value) != IS_NULL) {
                str_val = Z_STRVAL_P(value);
            }

            result = SDL_SetStringProperty((SDL_PropertiesID) props, Z_STRVAL(name), str_val);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLSetNumberProperty)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval name;
	zval *props_param = NULL, *name_param = NULL, *value_param = NULL;
	zend_long props, value;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &props_param, &name_param, &value_param);
	zephir_get_strval(&name, name_param);
	
            result = SDL_SetNumberProperty((SDL_PropertiesID) props, Z_STRVAL(name), (Sint64) value);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLSetFloatProperty)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	double value;
	zval name;
	zval *props_param = NULL, *name_param = NULL, *value_param = NULL;
	zend_long props;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &props_param, &name_param, &value_param);
	zephir_get_strval(&name, name_param);
	value = zephir_get_doubleval(value_param);
	
            result = SDL_SetFloatProperty((SDL_PropertiesID) props, Z_STRVAL(name), (float) value);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLSetBooleanProperty)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool value, result = 0;
	zval name;
	zval *props_param = NULL, *name_param = NULL, *value_param = NULL;
	zend_long props;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_BOOL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &props_param, &name_param, &value_param);
	zephir_get_strval(&name, name_param);
	
            result = SDL_SetBooleanProperty((SDL_PropertiesID) props, Z_STRVAL(name), value);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLHasProperty)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval name;
	zval *props_param = NULL, *name_param = NULL;
	zend_long props;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &props_param, &name_param);
	zephir_get_strval(&name, name_param);
	
            result = SDL_HasProperty((SDL_PropertiesID) props, Z_STRVAL(name));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetPropertyType)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval name;
	zval *props_param = NULL, *name_param = NULL;
	zend_long props, result = 0;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &props_param, &name_param);
	zephir_get_strval(&name, name_param);
	
            result = (zend_long) SDL_GetPropertyType((SDL_PropertiesID) props, Z_STRVAL(name));
        
	RETURN_MM_LONG(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetPointerProperty)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval name;
	zval *props_param = NULL, *name_param = NULL, *defaultValue = NULL, defaultValue_sub, __$null;
	zend_long props, result = 0;

	ZVAL_UNDEF(&defaultValue_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&name);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(defaultValue)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &props_param, &name_param, &defaultValue);
	zephir_get_strval(&name, name_param);
	if (!defaultValue) {
		defaultValue = &defaultValue_sub;
		defaultValue = &__$null;
	}
	
            void *default_ptr = NULL;
            void *ptr;

            if (Z_TYPE_P(defaultValue) != IS_NULL) {
                default_ptr = (void *)(uintptr_t) Z_LVAL_P(defaultValue);
            }

            ptr = SDL_GetPointerProperty((SDL_PropertiesID) props, Z_STRVAL(name), default_ptr);
            result = (zend_long)(uintptr_t) ptr;
        
	RETURN_MM_LONG(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetStringProperty)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval name, result;
	zval *props_param = NULL, *name_param = NULL, *defaultValue = NULL, defaultValue_sub, __$null;
	zend_long props;

	ZVAL_UNDEF(&defaultValue_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&result);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(defaultValue)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &props_param, &name_param, &defaultValue);
	zephir_get_strval(&name, name_param);
	if (!defaultValue) {
		defaultValue = &defaultValue_sub;
		defaultValue = &__$null;
	}
	
            const char *default_str = NULL;
            const char *str;

            if (Z_TYPE_P(defaultValue) != IS_NULL) {
                default_str = Z_STRVAL_P(defaultValue);
            }

            str = SDL_GetStringProperty((SDL_PropertiesID) props, Z_STRVAL(name), default_str);
            ZVAL_STRING(&result, str ? str : "");
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetNumberProperty)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval name;
	zval *props_param = NULL, *name_param = NULL, *defaultValue_param = NULL;
	zend_long props, defaultValue, result = 0;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_LONG(defaultValue)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &props_param, &name_param, &defaultValue_param);
	zephir_get_strval(&name, name_param);
	
            result = (zend_long) SDL_GetNumberProperty(
                (SDL_PropertiesID) props,
                Z_STRVAL(name),
                (Sint64) defaultValue
            );
        
	RETURN_MM_LONG(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetFloatProperty)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	double defaultValue, result = 0;
	zval name;
	zval *props_param = NULL, *name_param = NULL, *defaultValue_param = NULL;
	zend_long props;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_ZVAL(defaultValue)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &props_param, &name_param, &defaultValue_param);
	zephir_get_strval(&name, name_param);
	defaultValue = zephir_get_doubleval(defaultValue_param);
	
            result = (double) SDL_GetFloatProperty(
                (SDL_PropertiesID) props,
                Z_STRVAL(name),
                (float) defaultValue
            );
        
	RETURN_MM_DOUBLE(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetBooleanProperty)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool defaultValue, result = 0;
	zval name;
	zval *props_param = NULL, *name_param = NULL, *defaultValue_param = NULL;
	zend_long props;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_BOOL(defaultValue)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &props_param, &name_param, &defaultValue_param);
	zephir_get_strval(&name, name_param);
	
            result = SDL_GetBooleanProperty((SDL_PropertiesID) props, Z_STRVAL(name), defaultValue);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLClearProperty)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval name;
	zval *props_param = NULL, *name_param = NULL;
	zend_long props;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &props_param, &name_param);
	zephir_get_strval(&name, name_param);
	
            result = SDL_ClearProperty((SDL_PropertiesID) props, Z_STRVAL(name));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLEnumerateProperties)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *props_param = NULL, *callback, callback_sub, cb;
	zend_long props;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&cb);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(props)
		Z_PARAM_ZVAL(callback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &props_param, &callback);
	ZEPHIR_CPY_WRT(&cb, callback);
	
            php_sdl_properties_enum_context *ctx = php_sdl_properties_enum_context_alloc(&cb);

            result = SDL_EnumerateProperties(
                (SDL_PropertiesID) props,
                php_sdl_enumerate_properties_bridge,
                ctx
            );
            php_sdl_properties_enum_context_free(ctx);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLDestroyProperties)
{
	zval *props_param = NULL;
	zend_long props;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(props)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &props_param);
	
            SDL_DestroyProperties((SDL_PropertiesID) props);
        
}

