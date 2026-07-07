namespace Sdl3\SDL;

%{
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
}%

class SDLProperties
{
    public static function SDLGetGlobalProperties() -> int
    {
        int props;

        %{
            props = (zend_long) SDL_GetGlobalProperties();
        }%

        return props;
    }

    public static function SDLCreateProperties() -> int
    {
        int props;

        %{
            props = (zend_long) SDL_CreateProperties();
        }%

        if props == 0 {
            throw new \RuntimeException("SDL_CreateProperties failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return props;
    }

    public static function SDLCopyProperties(int src, int dst) -> bool
    {
        bool result;

        %{
            result = SDL_CopyProperties((SDL_PropertiesID) src, (SDL_PropertiesID) dst);
        }%

        return result;
    }

    public static function SDLLockProperties(int props) -> bool
    {
        bool result;

        %{
            result = SDL_LockProperties((SDL_PropertiesID) props);
        }%

        return result;
    }

    public static function SDLUnlockProperties(int props) -> void
    {
        %{
            SDL_UnlockProperties((SDL_PropertiesID) props);
        }%
    }

    public static function SDLSetPointerProperty(int props, string name, var value = null) -> bool
    {
        bool result;

        %{
            void *ptr = NULL;

            if (Z_TYPE_P(value) != IS_NULL) {
                ptr = (void *)(uintptr_t) Z_LVAL_P(value);
            }

            result = SDL_SetPointerProperty((SDL_PropertiesID) props, Z_STRVAL(name), ptr);
        }%

        return result;
    }

    public static function SDLSetStringProperty(int props, string name, var value = null) -> bool
    {
        bool result;

        %{
            const char *str_val = NULL;

            if (Z_TYPE_P(value) != IS_NULL) {
                str_val = Z_STRVAL_P(value);
            }

            result = SDL_SetStringProperty((SDL_PropertiesID) props, Z_STRVAL(name), str_val);
        }%

        return result;
    }

    public static function SDLSetNumberProperty(int props, string name, int value) -> bool
    {
        bool result;

        %{
            result = SDL_SetNumberProperty((SDL_PropertiesID) props, Z_STRVAL(name), (Sint64) value);
        }%

        return result;
    }

    public static function SDLSetFloatProperty(int props, string name, double value) -> bool
    {
        bool result;

        %{
            result = SDL_SetFloatProperty((SDL_PropertiesID) props, Z_STRVAL(name), (float) value);
        }%

        return result;
    }

    public static function SDLSetBooleanProperty(int props, string name, bool value) -> bool
    {
        bool result;

        %{
            result = SDL_SetBooleanProperty((SDL_PropertiesID) props, Z_STRVAL(name), value);
        }%

        return result;
    }

    public static function SDLHasProperty(int props, string name) -> bool
    {
        bool result;

        %{
            result = SDL_HasProperty((SDL_PropertiesID) props, Z_STRVAL(name));
        }%

        return result;
    }

    public static function SDLGetPropertyType(int props, string name) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetPropertyType((SDL_PropertiesID) props, Z_STRVAL(name));
        }%

        return result;
    }

    public static function SDLGetPointerProperty(int props, string name, var defaultValue = null) -> int
    {
        int result;

        %{
            void *default_ptr = NULL;
            void *ptr;

            if (Z_TYPE_P(defaultValue) != IS_NULL) {
                default_ptr = (void *)(uintptr_t) Z_LVAL_P(defaultValue);
            }

            ptr = SDL_GetPointerProperty((SDL_PropertiesID) props, Z_STRVAL(name), default_ptr);
            result = (zend_long)(uintptr_t) ptr;
        }%

        return result;
    }

    public static function SDLGetStringProperty(int props, string name, var defaultValue = null) -> string
    {
        string result;

        %{
            const char *default_str = NULL;
            const char *str;

            if (Z_TYPE_P(defaultValue) != IS_NULL) {
                default_str = Z_STRVAL_P(defaultValue);
            }

            str = SDL_GetStringProperty((SDL_PropertiesID) props, Z_STRVAL(name), default_str);
            ZVAL_STRING(&result, str ? str : "");
        }%

        return result;
    }

    public static function SDLGetNumberProperty(int props, string name, int defaultValue) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetNumberProperty(
                (SDL_PropertiesID) props,
                Z_STRVAL(name),
                (Sint64) defaultValue
            );
        }%

        return result;
    }

    public static function SDLGetFloatProperty(int props, string name, double defaultValue) -> double
    {
        double result;

        %{
            result = (double) SDL_GetFloatProperty(
                (SDL_PropertiesID) props,
                Z_STRVAL(name),
                (float) defaultValue
            );
        }%

        return result;
    }

    public static function SDLGetBooleanProperty(int props, string name, bool defaultValue) -> bool
    {
        bool result;

        %{
            result = SDL_GetBooleanProperty((SDL_PropertiesID) props, Z_STRVAL(name), defaultValue);
        }%

        return result;
    }

    public static function SDLClearProperty(int props, string name) -> bool
    {
        bool result;

        %{
            result = SDL_ClearProperty((SDL_PropertiesID) props, Z_STRVAL(name));
        }%

        return result;
    }

    public static function SDLEnumerateProperties(int props, var callback) -> bool
    {
        bool result;
        var cb;

        let cb = callback;

        %{
            php_sdl_properties_enum_context *ctx = php_sdl_properties_enum_context_alloc(&cb);

            result = SDL_EnumerateProperties(
                (SDL_PropertiesID) props,
                php_sdl_enumerate_properties_bridge,
                ctx
            );
            php_sdl_properties_enum_context_free(ctx);
        }%

        return result;
    }

    public static function SDLDestroyProperties(int props) -> void
    {
        %{
            SDL_DestroyProperties((SDL_PropertiesID) props);
        }%
    }
}
