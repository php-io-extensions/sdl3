
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
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/array.h"

#include <SDL3/SDL.h>
#include <stdio.h>



ZEPHIR_INIT_CLASS(Sdl3_SDL_SDL)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL, SDL, sdl3, sdl_sdl, sdl3_sdl_sdl_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_SDL, SDLInit)
{
	zend_bool result = 0;
	zval *flags_param = NULL;
	zend_long flags;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &flags_param);
	
            result = SDL_Init((Uint32) flags);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLInitSubSystem)
{
	zend_bool result = 0;
	zval *flags_param = NULL;
	zend_long flags;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &flags_param);
	
            result = SDL_InitSubSystem((Uint32) flags);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLWasInit)
{
	zval *flags_param = NULL;
	zend_long flags, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &flags_param);
	
            result = (zend_long) SDL_WasInit((Uint32) flags);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLQuit)
{

	
            SDL_Quit();
        
}

PHP_METHOD(Sdl3_SDL_SDL, SDLQuitSubSystem)
{
	zval *flags_param = NULL;
	zend_long flags;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &flags_param);
	
            SDL_QuitSubSystem((SDL_InitFlags) flags);
        
}

PHP_METHOD(Sdl3_SDL_SDL, SDLExitProcess)
{
	zval *exitcode_param = NULL;
	zend_long exitcode;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(exitcode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &exitcode_param);
	
            exit((int) exitcode);
        
}

PHP_METHOD(Sdl3_SDL_SDL, SDLGetPixelFormatDetails)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *format_param = NULL, _0;
	zend_long format, ptr = 0, fmt = 0, bits_per_pixel = 0, bytes_per_pixel = 0, rmask = 0, gmask = 0, bmask = 0, amask = 0, rbits = 0, gbits = 0, bbits = 0, abits = 0, rshift = 0, gshift = 0, bshift = 0, ashift = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &format_param);
	
            const SDL_PixelFormatDetails *details = SDL_GetPixelFormatDetails((SDL_PixelFormat) format);

            if (!details) {
                ptr = 0; fmt = 0; bits_per_pixel = 0; bytes_per_pixel = 0;
                rmask = 0; gmask = 0; bmask = 0; amask = 0;
                rbits = 0; gbits = 0; bbits = 0; abits = 0;
                rshift = 0; gshift = 0; bshift = 0; ashift = 0;
            } else {
                ptr            = (zend_long)(uintptr_t) details;
                fmt            = (zend_long) details->format;
                bits_per_pixel = (zend_long) details->bits_per_pixel;
                bytes_per_pixel= (zend_long) details->bytes_per_pixel;
                rmask          = (zend_long) details->Rmask;
                gmask          = (zend_long) details->Gmask;
                bmask          = (zend_long) details->Bmask;
                amask          = (zend_long) details->Amask;
                rbits          = (zend_long) details->Rbits;
                gbits          = (zend_long) details->Gbits;
                bbits          = (zend_long) details->Bbits;
                abits          = (zend_long) details->Abits;
                rshift         = (zend_long) details->Rshift;
                gshift         = (zend_long) details->Gshift;
                bshift         = (zend_long) details->Bshift;
                ashift         = (zend_long) details->Ashift;
            }
        
	if (fmt == 0) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 16, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, ptr);
	zephir_array_update_string(return_value, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, fmt);
	zephir_array_update_string(return_value, SL("format"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, bits_per_pixel);
	zephir_array_update_string(return_value, SL("bits_per_pixel"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, bytes_per_pixel);
	zephir_array_update_string(return_value, SL("bytes_per_pixel"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, rmask);
	zephir_array_update_string(return_value, SL("rmask"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, gmask);
	zephir_array_update_string(return_value, SL("gmask"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, bmask);
	zephir_array_update_string(return_value, SL("bmask"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, amask);
	zephir_array_update_string(return_value, SL("amask"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, rbits);
	zephir_array_update_string(return_value, SL("rbits"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, gbits);
	zephir_array_update_string(return_value, SL("gbits"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, bbits);
	zephir_array_update_string(return_value, SL("bbits"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, abits);
	zephir_array_update_string(return_value, SL("abits"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, rshift);
	zephir_array_update_string(return_value, SL("rshift"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, gshift);
	zephir_array_update_string(return_value, SL("gshift"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, bshift);
	zephir_array_update_string(return_value, SL("bshift"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, ashift);
	zephir_array_update_string(return_value, SL("ashift"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_SDL, SDLGetRGBA)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *pixel_param = NULL, *format_ptr_param = NULL, *palette_ptr = NULL, palette_ptr_sub, __$null, _0;
	zend_long pixel, format_ptr, r = 0, g = 0, b = 0, a = 0;

	ZVAL_UNDEF(&palette_ptr_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(pixel)
		Z_PARAM_LONG(format_ptr)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(palette_ptr)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &pixel_param, &format_ptr_param, &palette_ptr);
	if (!palette_ptr) {
		palette_ptr = &palette_ptr_sub;
		palette_ptr = &__$null;
	}
	
            const SDL_PixelFormatDetails *fmt = (const SDL_PixelFormatDetails *)(uintptr_t) format_ptr;
            const SDL_Palette *pal = (Z_TYPE_P(palette_ptr) == IS_NULL) ? NULL : (const SDL_Palette *)(uintptr_t)(zend_long)Z_LVAL_P(palette_ptr);

            Uint8 cr = 0, cg = 0, cb = 0, ca = 0;
            SDL_GetRGBA((Uint32) pixel, fmt, pal, &cr, &cg, &cb, &ca);

            r = (zend_long) cr;
            g = (zend_long) cg;
            b = (zend_long) cb;
            a = (zend_long) ca;
        
	zephir_create_array(return_value, 4, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, r);
	zephir_array_update_string(return_value, SL("r"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, g);
	zephir_array_update_string(return_value, SL("g"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, b);
	zephir_array_update_string(return_value, SL("b"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, a);
	zephir_array_update_string(return_value, SL("a"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_SDL, SDLMapRGBA)
{
	zval *format_ptr_param = NULL, *palette_ptr = NULL, palette_ptr_sub, *r_param = NULL, *g_param = NULL, *b_param = NULL, *a_param = NULL, __$null;
	zend_long format_ptr, r, g, b, a, result = 0;

	ZVAL_UNDEF(&palette_ptr_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(5, 6)
		Z_PARAM_LONG(format_ptr)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
		Z_PARAM_LONG(a)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(palette_ptr)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 1, &format_ptr_param, &palette_ptr, &r_param, &g_param, &b_param, &a_param);
	if (!palette_ptr) {
		palette_ptr = &palette_ptr_sub;
		palette_ptr = &__$null;
	}
	
            const SDL_PixelFormatDetails *fmt = (const SDL_PixelFormatDetails *)(uintptr_t) format_ptr;
            const SDL_Palette *pal = (Z_TYPE_P(palette_ptr) == IS_NULL) ? NULL : (const SDL_Palette *)(uintptr_t)(zend_long)Z_LVAL_P(palette_ptr);

            result = (zend_long) SDL_MapRGBA(fmt, pal, (Uint8) r, (Uint8) g, (Uint8) b, (Uint8) a);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLGetSandbox)
{
	zend_long result = 0;
	
            result = (zend_long) SDL_GetSandbox();
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLGetVersion)
{
	zend_long result = 0;
	
            result = (zend_long) SDL_GetVersion();
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLGetRevision)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&result);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&result);
	
            const char *rev = SDL_GetRevision();
            if (rev) {
                ZVAL_STRING(&result, rev);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLGetPlatform)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&result);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&result);
	
            const char *plat = SDL_GetPlatform();
            if (plat) {
                ZVAL_STRING(&result, plat);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLIsTablet)
{
	zend_bool result = 0;
	
            result = SDL_IsTablet();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLIsTV)
{
	zend_bool result = 0;
	
            result = SDL_IsTV();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLSetAppMetadata)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *appname_param = NULL, *appversion_param = NULL, *appidentifier_param = NULL;
	zval appname, appversion, appidentifier;

	ZVAL_UNDEF(&appname);
	ZVAL_UNDEF(&appversion);
	ZVAL_UNDEF(&appidentifier);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(appname)
		Z_PARAM_STR(appversion)
		Z_PARAM_STR(appidentifier)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &appname_param, &appversion_param, &appidentifier_param);
	zephir_get_strval(&appname, appname_param);
	zephir_get_strval(&appversion, appversion_param);
	zephir_get_strval(&appidentifier, appidentifier_param);
	
            result = SDL_SetAppMetadata(Z_STRVAL(appname), Z_STRVAL(appversion), Z_STRVAL(appidentifier));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLSetAppMetadataProperty)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *name_param = NULL, *value_param = NULL;
	zval name, value;

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&value);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(name)
		Z_PARAM_STR(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &name_param, &value_param);
	zephir_get_strval(&name, name_param);
	zephir_get_strval(&value, value_param);
	
            result = SDL_SetAppMetadataProperty(Z_STRVAL(name), Z_STRVAL(value));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLGetAppMetadataProperty)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *name_param = NULL;
	zval name, result;

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &name_param);
	zephir_get_strval(&name, name_param);
	ZEPHIR_INIT_VAR(&result);
	
            const char *prop = SDL_GetAppMetadataProperty(Z_STRVAL(name));
            if (prop) {
                ZVAL_STRING(&result, prop);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLSetMainReady)
{

	
            extern void SDL_SetMainReady(void);
            SDL_SetMainReady();
        
}

PHP_METHOD(Sdl3_SDL_SDL, SDLIsMainThread)
{
	zend_bool result = 0;
	
            result = SDL_IsMainThread();
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLRand)
{
	zval *n_param = NULL;
	zend_long n, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &n_param);
	
            result = (zend_long) SDL_rand((Sint32) n);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_SDL, SDLRandf)
{
	double result = 0;
	
            result = (double) SDL_randf();
        
	RETURN_DOUBLE(result);
}

