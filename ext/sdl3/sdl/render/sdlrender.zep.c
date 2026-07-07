
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
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/array.h"

#include <SDL3/SDL.h>
#include <stdio.h>



ZEPHIR_INIT_CLASS(Sdl3_SDL_Render_SDLRender)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Render, SDLRender, sdl3, sdl_render_sdlrender, sdl3_sdl_render_sdlrender_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLCreateRenderer)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, *name = NULL, name_sub, __$null, _0$$3, _1$$3, _2$$3;
	zend_long window, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&name_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &window_param, &name);
	if (!name) {
		name = &name_sub;
		name = &__$null;
	}
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            const char *renderer_name = (Z_TYPE_P(name) == IS_NULL) ? NULL : Z_STRVAL_P(name);
            SDL_Renderer *renderer = SDL_CreateRenderer(win, renderer_name);
            ptr = (zend_long)(uintptr_t) renderer;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateRenderer failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/render/sdlrender.zep", 20);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLCreateSoftwareRenderer)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *surface_param = NULL, _0$$3, _1$$3, _2$$3;
	zend_long surface, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &surface_param);
	
            SDL_Surface  *surf     = (SDL_Surface *)(uintptr_t) surface;
            SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surf);
            ptr = (zend_long)(uintptr_t) renderer;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateSoftwareRenderer failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/render/sdlrender.zep", 37);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderClear)
{
	zval *renderer_param = NULL;
	zend_long renderer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_RenderClear(ren);
        
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderPresent)
{
	zend_bool result = 0;
	zval *renderer_param = NULL;
	zend_long renderer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_RenderPresent(ren);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderTexture)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *texture_param = NULL, *srcrect = NULL, srcrect_sub, *dstrect = NULL, dstrect_sub, __$null;
	zend_long renderer, texture;

	ZVAL_UNDEF(&srcrect_sub);
	ZVAL_UNDEF(&dstrect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(texture)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(srcrect)
		Z_PARAM_ZVAL_OR_NULL(dstrect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 2, &renderer_param, &texture_param, &srcrect, &dstrect);
	if (!srcrect) {
		srcrect = &srcrect_sub;
		srcrect = &__$null;
	}
	if (!dstrect) {
		dstrect = &dstrect_sub;
		dstrect = &__$null;
	}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *te  = (SDL_Texture *)(uintptr_t) texture;

            SDL_FRect src_buf = {0}, dst_buf = {0};
            const SDL_FRect *src_ptr = NULL;
            const SDL_FRect *dst_ptr = NULL;

            if (Z_TYPE_P(srcrect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(srcrect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(srcrect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(srcrect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(srcrect), 3);
                if (x && y && w && h) {
                    src_buf.x = (float) zval_get_double(x);
                    src_buf.y = (float) zval_get_double(y);
                    src_buf.w = (float) zval_get_double(w);
                    src_buf.h = (float) zval_get_double(h);
                    src_ptr = &src_buf;
                }
            }

            if (Z_TYPE_P(dstrect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(dstrect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(dstrect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(dstrect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(dstrect), 3);
                if (x && y && w && h) {
                    dst_buf.x = (float) zval_get_double(x);
                    dst_buf.y = (float) zval_get_double(y);
                    dst_buf.w = (float) zval_get_double(w);
                    dst_buf.h = (float) zval_get_double(h);
                    dst_ptr = &dst_buf;
                }
            }

            result = SDL_RenderTexture(ren, te, src_ptr, dst_ptr);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderTextureRotated)
{
	zend_bool result = 0;
	double angle;
	zval *renderer_param = NULL, *texture_param = NULL, *angle_param = NULL, *flip_param = NULL, *srcrect = NULL, srcrect_sub, *dstrect = NULL, dstrect_sub, *center = NULL, center_sub, __$null;
	zend_long renderer, texture, flip;

	ZVAL_UNDEF(&srcrect_sub);
	ZVAL_UNDEF(&dstrect_sub);
	ZVAL_UNDEF(&center_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(4, 7)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(texture)
		Z_PARAM_ZVAL(angle)
		Z_PARAM_LONG(flip)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(srcrect)
		Z_PARAM_ZVAL_OR_NULL(dstrect)
		Z_PARAM_ZVAL_OR_NULL(center)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 3, &renderer_param, &texture_param, &angle_param, &flip_param, &srcrect, &dstrect, &center);
	angle = zephir_get_doubleval(angle_param);
	if (!srcrect) {
		srcrect = &srcrect_sub;
		srcrect = &__$null;
	}
	if (!dstrect) {
		dstrect = &dstrect_sub;
		dstrect = &__$null;
	}
	if (!center) {
		center = &center_sub;
		center = &__$null;
	}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *te  = (SDL_Texture *)(uintptr_t) texture;

            SDL_FRect src_buf = {0}, dst_buf = {0};
            const SDL_FRect *src_ptr = NULL;
            const SDL_FRect *dst_ptr = NULL;

            if (Z_TYPE_P(srcrect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(srcrect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(srcrect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(srcrect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(srcrect), 3);
                if (x && y && w && h) {
                    src_buf.x = (float) zval_get_double(x);
                    src_buf.y = (float) zval_get_double(y);
                    src_buf.w = (float) zval_get_double(w);
                    src_buf.h = (float) zval_get_double(h);
                    src_ptr = &src_buf;
                }
            }

            if (Z_TYPE_P(dstrect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(dstrect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(dstrect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(dstrect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(dstrect), 3);
                if (x && y && w && h) {
                    dst_buf.x = (float) zval_get_double(x);
                    dst_buf.y = (float) zval_get_double(y);
                    dst_buf.w = (float) zval_get_double(w);
                    dst_buf.h = (float) zval_get_double(h);
                    dst_ptr = &dst_buf;
                }
            }

            SDL_FPoint cp, *cpp = NULL;
            if (Z_TYPE_P(center) == IS_ARRAY) {
                zval *cx = zend_hash_index_find(Z_ARRVAL_P(center), 0);
                zval *cy = zend_hash_index_find(Z_ARRVAL_P(center), 1);
                if (cx && cy) {
                    cp.x = (float) zval_get_double(cx);
                    cp.y = (float) zval_get_double(cy);
                    cpp = &cp;
                }
            }

            result = SDL_RenderTextureRotated(ren, te, src_ptr, dst_ptr, angle, cpp, (SDL_FlipMode) flip);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderDrawColor)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL, *a_param = NULL;
	zend_long renderer, r, g, b, a;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
		Z_PARAM_LONG(a)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &renderer_param, &r_param, &g_param, &b_param, &a_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderDrawColor(ren, r, g, b, a);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderDrawColorFloat)
{
	zend_bool result = 0;
	double r, g, b, a;
	zval *renderer_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL, *a_param = NULL;
	zend_long renderer;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(renderer)
		Z_PARAM_ZVAL(r)
		Z_PARAM_ZVAL(g)
		Z_PARAM_ZVAL(b)
		Z_PARAM_ZVAL(a)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &renderer_param, &r_param, &g_param, &b_param, &a_param);
	r = zephir_get_doubleval(r_param);
	g = zephir_get_doubleval(g_param);
	b = zephir_get_doubleval(b_param);
	a = zephir_get_doubleval(a_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderDrawColorFloat(ren, (float) r, (float) g, (float) b, (float) a);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLCreateTexture)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, *format_param = NULL, *access_param = NULL, *w_param = NULL, *h_param = NULL, _0;
	zend_long renderer, format, access, w, h, ptr = 0, tex_format = 0, tex_w = 0, tex_h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(format)
		Z_PARAM_LONG(access)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 5, 0, &renderer_param, &format_param, &access_param, &w_param, &h_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *tex = SDL_CreateTexture(ren, (SDL_PixelFormat) format, (SDL_TextureAccess) access, (int) w, (int) h);

            if (!tex) {
                ptr = 0; tex_format = 0; tex_w = 0; tex_h = 0;
            } else {
                ptr        = (zend_long)(uintptr_t) tex;
                tex_format = (zend_long) format;
                tex_w      = (zend_long) w;
                tex_h      = (zend_long) h;
            }
        
	if (ptr == 0) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 5, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, ptr);
	zephir_array_update_string(return_value, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, tex_format);
	zephir_array_update_string(return_value, SL("format"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, tex_w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, tex_h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	add_assoc_long_ex(return_value, SL("refcount"), 1);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLCreateTextureFromSurface)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, *surface_param = NULL, _0;
	zend_long renderer, surface, ptr = 0, format = 0, w = 0, h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &renderer_param, &surface_param);
	
            SDL_Renderer *ren     = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Surface  *sur     = (SDL_Surface *)(uintptr_t) surface;
            SDL_Texture  *texture = SDL_CreateTextureFromSurface(ren, sur);

            if (!texture) {
                ptr = 0; format = 0; w = 0; h = 0;
            } else {
                ptr = (zend_long)(uintptr_t) texture;

                float fw = 0.0f, fh = 0.0f;
                SDL_GetTextureSize(texture, &fw, &fh);
                w = (zend_long) fw;
                h = (zend_long) fh;

                SDL_PropertiesID props = SDL_GetTextureProperties(texture);
                format = (zend_long) SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_FORMAT_NUMBER, SDL_PIXELFORMAT_UNKNOWN);
            }
        
	if (ptr == 0) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 5, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, ptr);
	zephir_array_update_string(return_value, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, format);
	zephir_array_update_string(return_value, SL("format"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	add_assoc_long_ex(return_value, SL("refcount"), 1);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLLockTextureToSurface)
{
	zval pixels_data, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *texture_param = NULL, *rect = NULL, rect_sub, __$null, _0;
	zend_long texture, ptr = 0, flags = 0, fmt = 0, w = 0, h = 0, pitch = 0, pixels_ptr = 0, refcount = 0;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&pixels_data);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(texture)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &texture_param, &rect);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	
            SDL_Texture *tex  = (SDL_Texture *)(uintptr_t) texture;
            SDL_Surface *surf = NULL;

            SDL_Rect rect_buf = {0};
            const SDL_Rect *rect_ptr = NULL;

            if (Z_TYPE_P(rect) == IS_ARRAY) {
                zval *rx = zend_hash_index_find(Z_ARRVAL_P(rect), 0);
                zval *ry = zend_hash_index_find(Z_ARRVAL_P(rect), 1);
                zval *rw = zend_hash_index_find(Z_ARRVAL_P(rect), 2);
                zval *rh = zend_hash_index_find(Z_ARRVAL_P(rect), 3);
                if (rx && ry && rw && rh) {
                    rect_buf.x = (int) zval_get_long(rx);
                    rect_buf.y = (int) zval_get_long(ry);
                    rect_buf.w = (int) zval_get_long(rw);
                    rect_buf.h = (int) zval_get_long(rh);
                    rect_ptr = &rect_buf;
                }
            }

            bool ok = SDL_LockTextureToSurface(tex, rect_ptr, &surf);

            if (!ok || !surf) {
                ptr = 0; flags = 0; fmt = 0; w = 0; h = 0; pitch = 0; pixels_ptr = 0; refcount = 0;
                array_init(&pixels_data);
            } else {
                ptr        = (zend_long)(uintptr_t) surf;
                flags      = (zend_long) surf->flags;
                fmt        = (zend_long) surf->format;
                w          = (zend_long) surf->w;
                h          = (zend_long) surf->h;
                pitch      = (zend_long) surf->pitch;
                pixels_ptr = surf->pixels ? (zend_long)(uintptr_t) surf->pixels : 0;
                refcount   = (zend_long) surf->refcount;
                array_init(&pixels_data);
                if (surf->pixels) {
                    for (int py = 0; py < surf->h; py++) {
                        Uint32 *row = (Uint32 *)(((Uint8 *)surf->pixels) + py * surf->pitch);
                        for (int px = 0; px < surf->w; px++) {
                            add_next_index_long(&pixels_data, (zend_long)(zend_ulong)row[px]);
                        }
                    }
                }
            }
        
	if (ptr == 0) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 8, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, ptr);
	zephir_array_update_string(return_value, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, flags);
	zephir_array_update_string(return_value, SL("flags"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, fmt);
	zephir_array_update_string(return_value, SL("format"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, pitch);
	zephir_array_update_string(return_value, SL("pitch"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 2, 0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, pixels_ptr);
	zephir_array_update_string(&_1, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_1, SL("data"), &pixels_data, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("pixels"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, refcount);
	zephir_array_update_string(return_value, SL("refcount"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLUnlockTexture)
{
	zval *texture_param = NULL;
	zend_long texture;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &texture_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            SDL_UnlockTexture(te);
        
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTextureColorModFloat)
{
	zend_bool result = 0;
	double r, g, b;
	zval *texture_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL;
	zend_long texture;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(texture)
		Z_PARAM_ZVAL(r)
		Z_PARAM_ZVAL(g)
		Z_PARAM_ZVAL(b)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &texture_param, &r_param, &g_param, &b_param);
	r = zephir_get_doubleval(r_param);
	g = zephir_get_doubleval(g_param);
	b = zephir_get_doubleval(b_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            result = SDL_SetTextureColorModFloat(te, (float) r, (float) g, (float) b);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTextureScaleMode)
{
	zend_bool result = 0;
	zval *texture_param = NULL, *scaleMode_param = NULL;
	zend_long texture, scaleMode;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(texture)
		Z_PARAM_LONG(scaleMode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &texture_param, &scaleMode_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            result = SDL_SetTextureScaleMode(te, (SDL_ScaleMode) scaleMode);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureSize)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *texture_param = NULL, _0;
	zend_long texture, w = 0, h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &texture_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            float fw = 0.0f, fh = 0.0f;
            result = SDL_GetTextureSize(te, &fw, &fh);
            w = (zend_long) fw;
            h = (zend_long) fh;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderLogicalPresentation)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *w_param = NULL, *h_param = NULL, *mode_param = NULL;
	zend_long renderer, w, h, mode;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(mode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &renderer_param, &w_param, &h_param, &mode_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderLogicalPresentation(ren, (int) w, (int) h, (SDL_RendererLogicalPresentation) mode);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLDestroyRenderer)
{
	zval *renderer_param = NULL;
	zend_long renderer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_DestroyRenderer(ren);
        
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLDestroyTexture)
{
	zval *texture_param = NULL;
	zend_long texture;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &texture_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            SDL_DestroyTexture(te);
        
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderFillRect)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *rect = NULL, rect_sub, __$null;
	zend_long renderer;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &renderer_param, &rect);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_FRect r, *rp = NULL;

            if (Z_TYPE_P(rect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(rect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(rect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(rect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(rect), 3);
                r.x = x ? (float)zval_get_double(x) : 0.0f;
                r.y = y ? (float)zval_get_double(y) : 0.0f;
                r.w = w ? (float)zval_get_double(w) : 0.0f;
                r.h = h ? (float)zval_get_double(h) : 0.0f;
                rp = &r;
            }

            result = SDL_RenderFillRect(ren, rp);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderViewport)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *rect = NULL, rect_sub, __$null;
	zend_long renderer;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &renderer_param, &rect);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Rect r, *rp = NULL;

            if (Z_TYPE_P(rect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(rect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(rect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(rect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(rect), 3);
                r.x = x ? (int)zval_get_long(x) : 0;
                r.y = y ? (int)zval_get_long(y) : 0;
                r.w = w ? (int)zval_get_long(w) : 0;
                r.h = h ? (int)zval_get_long(h) : 0;
                rp = &r;
            }

            result = SDL_SetRenderViewport(ren, rp);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderClipRect)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *rect = NULL, rect_sub, __$null;
	zend_long renderer;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &renderer_param, &rect);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Rect r, *rp = NULL;

            if (Z_TYPE_P(rect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(rect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(rect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(rect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(rect), 3);
                r.x = x ? (int)zval_get_long(x) : 0;
                r.y = y ? (int)zval_get_long(y) : 0;
                r.w = w ? (int)zval_get_long(w) : 0;
                r.h = h ? (int)zval_get_long(h) : 0;
                rp = &r;
            }

            result = SDL_SetRenderClipRect(ren, rp);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderReadPixels)
{
	zval pixels_data, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, *rect = NULL, rect_sub, __$null, _0;
	zend_long renderer, ptr = 0, flags = 0, format = 0, w = 0, h = 0, pitch = 0, pixels_ptr = 0, refcount = 0;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&pixels_data);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &renderer_param, &rect);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;

            SDL_Rect r, *rp = NULL;
            if (Z_TYPE_P(rect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(rect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(rect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(rect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(rect), 3);
                r.x = x ? (int)zval_get_long(x) : 0;
                r.y = y ? (int)zval_get_long(y) : 0;
                r.w = w ? (int)zval_get_long(w) : 0;
                r.h = h ? (int)zval_get_long(h) : 0;
                rp = &r;
            }

            SDL_Surface *surf = SDL_RenderReadPixels(ren, rp);
            if (!surf) {
                ptr = 0; flags = 0; format = 0; w = 0; h = 0; pitch = 0; pixels_ptr = 0; refcount = 0;
                array_init(&pixels_data);
            } else {
                ptr        = (zend_long)(uintptr_t) surf;
                flags      = (zend_long) surf->flags;
                format     = (zend_long) surf->format;
                w          = (zend_long) surf->w;
                h          = (zend_long) surf->h;
                pitch      = (zend_long) surf->pitch;
                pixels_ptr = surf->pixels ? (zend_long)(uintptr_t) surf->pixels : 0;
                refcount   = (zend_long) surf->refcount;
                array_init(&pixels_data);
                if (surf->pixels) {
                    for (int py = 0; py < surf->h; py++) {
                        Uint32 *row = (Uint32 *)(((Uint8 *)surf->pixels) + py * surf->pitch);
                        for (int px = 0; px < surf->w; px++) {
                            add_next_index_long(&pixels_data, (zend_long)(zend_ulong)row[px]);
                        }
                    }
                }
            }
        
	if (ptr == 0) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 8, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, ptr);
	zephir_array_update_string(return_value, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, flags);
	zephir_array_update_string(return_value, SL("flags"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, format);
	zephir_array_update_string(return_value, SL("format"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, pitch);
	zephir_array_update_string(return_value, SL("pitch"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 2, 0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, pixels_ptr);
	zephir_array_update_string(&_1, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_1, SL("data"), &pixels_data, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("pixels"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, refcount);
	zephir_array_update_string(return_value, SL("refcount"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLUpdateTextureFromSurface)
{
	zend_bool result = 0;
	zval *texture_param = NULL, *surface_param = NULL;
	zend_long texture, surface;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(texture)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &texture_param, &surface_param);
	
            SDL_Texture *tex  = (SDL_Texture *)(uintptr_t) texture;
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_UpdateTexture(tex, NULL, surf->pixels, surf->pitch);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderDebugText)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval str;
	double x, y;
	zval *renderer_param = NULL, *x_param = NULL, *y_param = NULL, *str_param = NULL;
	zend_long renderer;

	ZVAL_UNDEF(&str);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(renderer)
		Z_PARAM_ZVAL(x)
		Z_PARAM_ZVAL(y)
		Z_PARAM_STR(str)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &renderer_param, &x_param, &y_param, &str_param);
	x = zephir_get_doubleval(x_param);
	y = zephir_get_doubleval(y_param);
	zephir_get_strval(&str, str_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_RenderDebugText(ren, (float) x, (float) y, Z_STRVAL(str));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderScale)
{
	zend_bool result = 0;
	double scaleX, scaleY;
	zval *renderer_param = NULL, *scaleX_param = NULL, *scaleY_param = NULL;
	zend_long renderer;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(renderer)
		Z_PARAM_ZVAL(scaleX)
		Z_PARAM_ZVAL(scaleY)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &renderer_param, &scaleX_param, &scaleY_param);
	scaleX = zephir_get_doubleval(scaleX_param);
	scaleY = zephir_get_doubleval(scaleY_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderScale(ren, (float) scaleX, (float) scaleY);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderTextureAffine)
{
	zend_bool result = 0, _0, _1;
	zval *renderer_param = NULL, *texture_param = NULL, *origin, origin_sub, *right, right_sub, *down, down_sub, *srcrect = NULL, srcrect_sub, __$null;
	zend_long renderer, texture;

	ZVAL_UNDEF(&origin_sub);
	ZVAL_UNDEF(&right_sub);
	ZVAL_UNDEF(&down_sub);
	ZVAL_UNDEF(&srcrect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(5, 6)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(texture)
		Z_PARAM_ZVAL(origin)
		Z_PARAM_ZVAL(right)
		Z_PARAM_ZVAL(down)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(srcrect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 1, &renderer_param, &texture_param, &origin, &right, &down, &srcrect);
	if (!srcrect) {
		srcrect = &srcrect_sub;
		srcrect = &__$null;
	}
	_0 = Z_TYPE_P(origin) != IS_ARRAY;
	if (!(_0)) {
		_0 = Z_TYPE_P(right) != IS_ARRAY;
	}
	_1 = _0;
	if (!(_1)) {
		_1 = Z_TYPE_P(down) != IS_ARRAY;
	}
	if (_1) {
		RETURN_BOOL(0);
	}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *tex = (SDL_Texture  *)(uintptr_t) texture;

            SDL_FRect sr, *srp = NULL;
            if (Z_TYPE_P(srcrect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(srcrect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(srcrect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(srcrect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(srcrect), 3);
                sr.x = x ? (float)zval_get_double(x) : 0.0f;
                sr.y = y ? (float)zval_get_double(y) : 0.0f;
                sr.w = w ? (float)zval_get_double(w) : 0.0f;
                sr.h = h ? (float)zval_get_double(h) : 0.0f;
                srp = &sr;
            }

            SDL_FPoint orig_pt = { 0.0f, 0.0f };
            SDL_FPoint right_pt = { 0.0f, 0.0f };
            SDL_FPoint down_pt  = { 0.0f, 0.0f };

            if (Z_TYPE_P(origin) == IS_ARRAY) {
                zval *ox = zend_hash_index_find(Z_ARRVAL_P(origin), 0);
                zval *oy = zend_hash_index_find(Z_ARRVAL_P(origin), 1);
                orig_pt.x = ox ? (float)zval_get_double(ox) : 0.0f;
                orig_pt.y = oy ? (float)zval_get_double(oy) : 0.0f;
            }
            if (Z_TYPE_P(right) == IS_ARRAY) {
                zval *rx = zend_hash_index_find(Z_ARRVAL_P(right), 0);
                zval *ry = zend_hash_index_find(Z_ARRVAL_P(right), 1);
                right_pt.x = rx ? (float)zval_get_double(rx) : 0.0f;
                right_pt.y = ry ? (float)zval_get_double(ry) : 0.0f;
            }
            if (Z_TYPE_P(down) == IS_ARRAY) {
                zval *dx = zend_hash_index_find(Z_ARRVAL_P(down), 0);
                zval *dy = zend_hash_index_find(Z_ARRVAL_P(down), 1);
                down_pt.x = dx ? (float)zval_get_double(dx) : 0.0f;
                down_pt.y = dy ? (float)zval_get_double(dy) : 0.0f;
            }

            result = SDL_RenderTextureAffine(ren, tex, srp, &orig_pt, &right_pt, &down_pt);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderFillRects)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval rects;
	zval *renderer_param = NULL, *rects_param = NULL, *count_param = NULL;
	zend_long renderer, count;

	ZVAL_UNDEF(&rects);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(renderer)
		Z_PARAM_ARRAY(rects)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &renderer_param, &rects_param, &count_param);
	zephir_get_arrval(&rects, rects_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_FRect *frects = (SDL_FRect *) emalloc(sizeof(SDL_FRect) * count);
            zval *entry;
            int i = 0;

            ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rects), entry) {
                if (Z_TYPE_P(entry) == IS_ARRAY && i < count) {
                    zval *x = zend_hash_index_find(Z_ARRVAL_P(entry), 0);
                    zval *y = zend_hash_index_find(Z_ARRVAL_P(entry), 1);
                    zval *w = zend_hash_index_find(Z_ARRVAL_P(entry), 2);
                    zval *h = zend_hash_index_find(Z_ARRVAL_P(entry), 3);
                    frects[i].x = x ? (float)zval_get_double(x) : 0.0f;
                    frects[i].y = y ? (float)zval_get_double(y) : 0.0f;
                    frects[i].w = w ? (float)zval_get_double(w) : 0.0f;
                    frects[i].h = h ? (float)zval_get_double(h) : 0.0f;
                    i++;
                }
            } ZEND_HASH_FOREACH_END();

            result = SDL_RenderFillRects(ren, frects, i);
            efree(frects);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderRects)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval rects;
	zval *renderer_param = NULL, *rects_param = NULL, *count_param = NULL;
	zend_long renderer, count;

	ZVAL_UNDEF(&rects);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(renderer)
		Z_PARAM_ARRAY(rects)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &renderer_param, &rects_param, &count_param);
	zephir_get_arrval(&rects, rects_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_FRect *frects = (SDL_FRect *) emalloc(sizeof(SDL_FRect) * count);
            zval *entry;
            int i = 0;

            ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rects), entry) {
                if (Z_TYPE_P(entry) == IS_ARRAY && i < count) {
                    zval *x = zend_hash_index_find(Z_ARRVAL_P(entry), 0);
                    zval *y = zend_hash_index_find(Z_ARRVAL_P(entry), 1);
                    zval *w = zend_hash_index_find(Z_ARRVAL_P(entry), 2);
                    zval *h = zend_hash_index_find(Z_ARRVAL_P(entry), 3);
                    frects[i].x = x ? (float)zval_get_double(x) : 0.0f;
                    frects[i].y = y ? (float)zval_get_double(y) : 0.0f;
                    frects[i].w = w ? (float)zval_get_double(w) : 0.0f;
                    frects[i].h = h ? (float)zval_get_double(h) : 0.0f;
                    i++;
                }
            } ZEND_HASH_FOREACH_END();

            result = SDL_RenderRects(ren, frects, i);
            efree(frects);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderLine)
{
	zend_bool result = 0;
	double x1, y1, x2, y2;
	zval *renderer_param = NULL, *x1_param = NULL, *y1_param = NULL, *x2_param = NULL, *y2_param = NULL;
	zend_long renderer;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(renderer)
		Z_PARAM_ZVAL(x1)
		Z_PARAM_ZVAL(y1)
		Z_PARAM_ZVAL(x2)
		Z_PARAM_ZVAL(y2)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &renderer_param, &x1_param, &y1_param, &x2_param, &y2_param);
	x1 = zephir_get_doubleval(x1_param);
	y1 = zephir_get_doubleval(y1_param);
	x2 = zephir_get_doubleval(x2_param);
	y2 = zephir_get_doubleval(y2_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_RenderLine(ren, (float) x1, (float) y1, (float) x2, (float) y2);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderRect)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *rect = NULL, rect_sub, __$null;
	zend_long renderer;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &renderer_param, &rect);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_FRect r, *rp = NULL;

            if (Z_TYPE_P(rect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(rect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(rect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(rect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(rect), 3);
                r.x = x ? (float)zval_get_double(x) : 0.0f;
                r.y = y ? (float)zval_get_double(y) : 0.0f;
                r.w = w ? (float)zval_get_double(w) : 0.0f;
                r.h = h ? (float)zval_get_double(h) : 0.0f;
                rp = &r;
            }

            result = SDL_RenderRect(ren, rp);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderPoints)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval points;
	zval *renderer_param = NULL, *points_param = NULL, *count_param = NULL;
	zend_long renderer, count;

	ZVAL_UNDEF(&points);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(renderer)
		Z_PARAM_ARRAY(points)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &renderer_param, &points_param, &count_param);
	zephir_get_arrval(&points, points_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_FPoint *fpoints = (SDL_FPoint *) emalloc(sizeof(SDL_FPoint) * count);
            zval *entry;
            int i = 0;

            ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&points), entry) {
                if (Z_TYPE_P(entry) == IS_ARRAY && i < count) {
                    zval *x = zend_hash_index_find(Z_ARRVAL_P(entry), 0);
                    zval *y = zend_hash_index_find(Z_ARRVAL_P(entry), 1);
                    fpoints[i].x = x ? (float)zval_get_double(x) : 0.0f;
                    fpoints[i].y = y ? (float)zval_get_double(y) : 0.0f;
                    i++;
                }
            } ZEND_HASH_FOREACH_END();

            result = SDL_RenderPoints(ren, fpoints, i);
            efree(fpoints);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderGeometry)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval vertices;
	zval *renderer_param = NULL, *texture_param = NULL, *vertices_param = NULL, *num_vertices_param = NULL, *num_indices_param = NULL, *indices = NULL, indices_sub, __$null;
	zend_long renderer, texture, num_vertices, num_indices;

	ZVAL_UNDEF(&indices_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&vertices);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(5, 6)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(texture)
		Z_PARAM_ARRAY(vertices)
		Z_PARAM_LONG(num_vertices)
		Z_PARAM_LONG(num_indices)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(indices)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 5, 1, &renderer_param, &texture_param, &vertices_param, &num_vertices_param, &num_indices_param, &indices);
	zephir_get_arrval(&vertices, vertices_param);
	if (!indices) {
		indices = &indices_sub;
		indices = &__$null;
	}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *tex = texture ? (SDL_Texture *)(uintptr_t) texture : NULL;

            SDL_Vertex *verts = (SDL_Vertex *) emalloc(sizeof(SDL_Vertex) * (size_t) num_vertices);
            memset(verts, 0, sizeof(SDL_Vertex) * (size_t) num_vertices);

            zval *item;
            zend_long idx = 0;
            ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&vertices), item) {
                if (idx >= num_vertices) break;
                if (Z_TYPE_P(item) == IS_ARRAY) {
                    zval *v0 = zend_hash_index_find(Z_ARRVAL_P(item), 0);
                    zval *v1 = zend_hash_index_find(Z_ARRVAL_P(item), 1);
                    zval *v2 = zend_hash_index_find(Z_ARRVAL_P(item), 2);
                    zval *v3 = zend_hash_index_find(Z_ARRVAL_P(item), 3);
                    zval *v4 = zend_hash_index_find(Z_ARRVAL_P(item), 4);
                    zval *v5 = zend_hash_index_find(Z_ARRVAL_P(item), 5);
                    zval *v6 = zend_hash_index_find(Z_ARRVAL_P(item), 6);
                    zval *v7 = zend_hash_index_find(Z_ARRVAL_P(item), 7);
                    if (v0) verts[idx].position.x  = (float) zval_get_double(v0);
                    if (v1) verts[idx].position.y  = (float) zval_get_double(v1);
                    if (v2) verts[idx].color.r     = (float) zval_get_double(v2);
                    if (v3) verts[idx].color.g     = (float) zval_get_double(v3);
                    if (v4) verts[idx].color.b     = (float) zval_get_double(v4);
                    if (v5) verts[idx].color.a     = (float) zval_get_double(v5);
                    if (v6) verts[idx].tex_coord.x = (float) zval_get_double(v6);
                    if (v7) verts[idx].tex_coord.y = (float) zval_get_double(v7);
                }
                idx++;
            } ZEND_HASH_FOREACH_END();

            int *idx_buf = NULL;
            if (num_indices > 0 && Z_TYPE_P(indices) == IS_ARRAY) {
                idx_buf = (int *) emalloc(sizeof(int) * (size_t) num_indices);
                zend_long ii = 0;
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(indices), item) {
                    if (ii >= num_indices) break;
                    idx_buf[ii++] = (int) zval_get_long(item);
                } ZEND_HASH_FOREACH_END();
            }

            result = SDL_RenderGeometry(ren, tex, verts, (int) num_vertices, idx_buf, (int) num_indices);

            efree(verts);
            if (idx_buf) efree(idx_buf);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderLines)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval points;
	zval *renderer_param = NULL, *points_param = NULL, *count_param = NULL;
	zend_long renderer, count;

	ZVAL_UNDEF(&points);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(renderer)
		Z_PARAM_ARRAY(points)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &renderer_param, &points_param, &count_param);
	zephir_get_arrval(&points, points_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_FPoint *fpoints = (SDL_FPoint *) emalloc(sizeof(SDL_FPoint) * count);
            zval *entry;
            int i = 0;

            ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&points), entry) {
                if (Z_TYPE_P(entry) == IS_ARRAY && i < count) {
                    zval *x = zend_hash_index_find(Z_ARRVAL_P(entry), 0);
                    zval *y = zend_hash_index_find(Z_ARRVAL_P(entry), 1);
                    fpoints[i].x = x ? (float)zval_get_double(x) : 0.0f;
                    fpoints[i].y = y ? (float)zval_get_double(y) : 0.0f;
                    i++;
                }
            } ZEND_HASH_FOREACH_END();

            result = SDL_RenderLines(ren, fpoints, i);
            efree(fpoints);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetNumRenderDrivers)
{
	zend_long count = 0;
	
            count = (zend_long) SDL_GetNumRenderDrivers();
        
	RETURN_LONG(count);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderDriver)
{
	zval name;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *index_param = NULL;
	zend_long index;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &index_param);
	ZEPHIR_INIT_VAR(&name);
	
            const char *driver = SDL_GetRenderDriver((int) index);
            if (driver) {
                ZVAL_STRING(&name, (char *) driver);
            }
        
	RETURN_CTOR(&name);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLCreateRendererWithProperties)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *props_param = NULL, _0$$3, _1$$3, _2$$3;
	zend_long props, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(props)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &props_param);
	
            SDL_Renderer *renderer = SDL_CreateRendererWithProperties((SDL_PropertiesID) props);
            ptr = (zend_long)(uintptr_t) renderer;
        
	if (ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateRendererWithProperties failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/render/sdlrender.zep", 872);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderer)
{
	zval *window_param = NULL;
	zend_long window, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Renderer *renderer = SDL_GetRenderer(win);
            ptr = renderer ? (zend_long)(uintptr_t) renderer : 0;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderWindow)
{
	zval *renderer_param = NULL;
	zend_long renderer, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Window *win = SDL_GetRenderWindow(ren);
            ptr = win ? (zend_long)(uintptr_t) win : 0;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRendererName)
{
	zval name;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL;
	zend_long renderer;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	ZEPHIR_INIT_VAR(&name);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            const char *n = SDL_GetRendererName(ren);
            if (n) {
                ZVAL_STRING(&name, (char *) n);
            }
        
	RETURN_CTOR(&name);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRendererProperties)
{
	zval *renderer_param = NULL;
	zend_long renderer, props = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            props = (zend_long) SDL_GetRendererProperties(ren);
        
	RETURN_LONG(props);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderOutputSize)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer, w = 0, h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            int ww = 0, hh = 0;
            result = SDL_GetRenderOutputSize(ren, &ww, &hh);
            w = (zend_long) ww;
            h = (zend_long) hh;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetCurrentRenderOutputSize)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer, w = 0, h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            int ww = 0, hh = 0;
            result = SDL_GetCurrentRenderOutputSize(ren, &ww, &hh);
            w = (zend_long) ww;
            h = (zend_long) hh;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLCreateTextureWithProperties)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, *props_param = NULL, _0;
	zend_long renderer, props, ptr = 0, tex_format = 0, tex_w = 0, tex_h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(props)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &renderer_param, &props_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *tex = SDL_CreateTextureWithProperties(ren, (SDL_PropertiesID) props);

            if (!tex) {
                ptr = 0; tex_format = 0; tex_w = 0; tex_h = 0;
            } else {
                ptr = (zend_long)(uintptr_t) tex;
                float fw = 0.0f, fh = 0.0f;
                SDL_GetTextureSize(tex, &fw, &fh);
                tex_w = (zend_long) fw;
                tex_h = (zend_long) fh;
                SDL_PropertiesID tprops = SDL_GetTextureProperties(tex);
                tex_format = (zend_long) SDL_GetNumberProperty(tprops, SDL_PROP_TEXTURE_FORMAT_NUMBER, SDL_PIXELFORMAT_UNKNOWN);
            }
        
	if (ptr == 0) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 5, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, ptr);
	zephir_array_update_string(return_value, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, tex_format);
	zephir_array_update_string(return_value, SL("format"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, tex_w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, tex_h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	add_assoc_long_ex(return_value, SL("refcount"), 1);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRendererFromTexture)
{
	zval *texture_param = NULL;
	zend_long texture, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &texture_param);
	
            SDL_Texture  *tex = (SDL_Texture *)(uintptr_t) texture;
            SDL_Renderer *ren = SDL_GetRendererFromTexture(tex);
            ptr = ren ? (zend_long)(uintptr_t) ren : 0;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTexturePalette)
{
	zend_bool result = 0;
	zval *texture_param = NULL, *palette_param = NULL;
	zend_long texture, palette;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(texture)
		Z_PARAM_LONG(palette)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &texture_param, &palette_param);
	
            SDL_Texture *tex = (SDL_Texture *)(uintptr_t) texture;
            SDL_Palette *pal = (SDL_Palette *)(uintptr_t) palette;
            result = SDL_SetTexturePalette(tex, pal);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTexturePalette)
{
	zval *texture_param = NULL;
	zend_long texture, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &texture_param);
	
            SDL_Texture *tex = (SDL_Texture *)(uintptr_t) texture;
            SDL_Palette *pal = SDL_GetTexturePalette(tex);
            ptr = pal ? (zend_long)(uintptr_t) pal : 0;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTextureColorMod)
{
	zend_bool result = 0;
	zval *texture_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL;
	zend_long texture, r, g, b;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(texture)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &texture_param, &r_param, &g_param, &b_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            result = SDL_SetTextureColorMod(te, (Uint8) r, (Uint8) g, (Uint8) b);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureColorMod)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *texture_param = NULL, _0;
	zend_long texture, r = 0, g = 0, b = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &texture_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            Uint8 rr = 0, gg = 0, bb = 0;
            result = SDL_GetTextureColorMod(te, &rr, &gg, &bb);
            r = (zend_long) rr;
            g = (zend_long) gg;
            b = (zend_long) bb;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 3, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, r);
	zephir_array_update_string(return_value, SL("r"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, g);
	zephir_array_update_string(return_value, SL("g"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, b);
	zephir_array_update_string(return_value, SL("b"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureColorModFloat)
{
	zend_bool result = 0;
	double r = 0, g = 0, b = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *texture_param = NULL, _0;
	zend_long texture;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &texture_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            float rr = 0.0f, gg = 0.0f, bb = 0.0f;
            result = SDL_GetTextureColorModFloat(te, &rr, &gg, &bb);
            r = (double) rr;
            g = (double) gg;
            b = (double) bb;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 3, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_DOUBLE(&_0, r);
	zephir_array_update_string(return_value, SL("r"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, g);
	zephir_array_update_string(return_value, SL("g"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, b);
	zephir_array_update_string(return_value, SL("b"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTextureAlphaMod)
{
	zend_bool result = 0;
	zval *texture_param = NULL, *alpha_param = NULL;
	zend_long texture, alpha;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(texture)
		Z_PARAM_LONG(alpha)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &texture_param, &alpha_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            result = SDL_SetTextureAlphaMod(te, (Uint8) alpha);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTextureAlphaModFloat)
{
	zend_bool result = 0;
	double alpha;
	zval *texture_param = NULL, *alpha_param = NULL;
	zend_long texture;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(texture)
		Z_PARAM_ZVAL(alpha)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &texture_param, &alpha_param);
	alpha = zephir_get_doubleval(alpha_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            result = SDL_SetTextureAlphaModFloat(te, (float) alpha);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureAlphaMod)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *texture_param = NULL, _0;
	zend_long texture, alpha = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &texture_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            Uint8 aa = 0;
            result = SDL_GetTextureAlphaMod(te, &aa);
            alpha = (zend_long) aa;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 1, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, alpha);
	zephir_array_update_string(return_value, SL("alpha"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureAlphaModFloat)
{
	zend_bool result = 0;
	double alpha = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *texture_param = NULL, _0;
	zend_long texture;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &texture_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            float aa = 0.0f;
            result = SDL_GetTextureAlphaModFloat(te, &aa);
            alpha = (double) aa;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 1, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_DOUBLE(&_0, alpha);
	zephir_array_update_string(return_value, SL("alpha"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTextureBlendMode)
{
	zend_bool result = 0;
	zval *texture_param = NULL, *blendMode_param = NULL;
	zend_long texture, blendMode;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(texture)
		Z_PARAM_LONG(blendMode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &texture_param, &blendMode_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            result = SDL_SetTextureBlendMode(te, (SDL_BlendMode) blendMode);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureBlendMode)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *texture_param = NULL, _0;
	zend_long texture, blendMode = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &texture_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            SDL_BlendMode mode = SDL_BLENDMODE_INVALID;
            result = SDL_GetTextureBlendMode(te, &mode);
            blendMode = (zend_long) mode;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 1, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, blendMode);
	zephir_array_update_string(return_value, SL("blend_mode"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureScaleMode)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *texture_param = NULL, _0;
	zend_long texture, scaleMode = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &texture_param);
	
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            SDL_ScaleMode mode = SDL_SCALEMODE_NEAREST;
            result = SDL_GetTextureScaleMode(te, &mode);
            scaleMode = (zend_long) mode;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 1, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, scaleMode);
	zephir_array_update_string(return_value, SL("scale_mode"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLUpdateTexture)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval pixels;
	zval *texture_param = NULL, *pixels_param = NULL, *pitch_param = NULL, *rect = NULL, rect_sub, __$null;
	zend_long texture, pitch;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&pixels);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_LONG(texture)
		Z_PARAM_STR(pixels)
		Z_PARAM_LONG(pitch)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 1, &texture_param, &pixels_param, &pitch_param, &rect);
	zephir_get_strval(&pixels, pixels_param);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	
            SDL_Texture *tex = (SDL_Texture *)(uintptr_t) texture;

            SDL_Rect rect_buf = {0};
            const SDL_Rect *rect_ptr = NULL;

            if (Z_TYPE_P(rect) == IS_ARRAY) {
                zval *rx = zend_hash_index_find(Z_ARRVAL_P(rect), 0);
                zval *ry = zend_hash_index_find(Z_ARRVAL_P(rect), 1);
                zval *rw = zend_hash_index_find(Z_ARRVAL_P(rect), 2);
                zval *rh = zend_hash_index_find(Z_ARRVAL_P(rect), 3);
                if (rx && ry && rw && rh) {
                    rect_buf.x = (int) zval_get_long(rx);
                    rect_buf.y = (int) zval_get_long(ry);
                    rect_buf.w = (int) zval_get_long(rw);
                    rect_buf.h = (int) zval_get_long(rh);
                    rect_ptr = &rect_buf;
                }
            }

            result = SDL_UpdateTexture(tex, rect_ptr, Z_STRVAL(pixels), (int) pitch);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLUpdateYUVTexture)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval yplane, uplane, vplane;
	zval *texture_param = NULL, *yplane_param = NULL, *ypitch_param = NULL, *uplane_param = NULL, *upitch_param = NULL, *vplane_param = NULL, *vpitch_param = NULL, *rect = NULL, rect_sub, __$null;
	zend_long texture, ypitch, upitch, vpitch;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&yplane);
	ZVAL_UNDEF(&uplane);
	ZVAL_UNDEF(&vplane);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(7, 8)
		Z_PARAM_LONG(texture)
		Z_PARAM_STR(yplane)
		Z_PARAM_LONG(ypitch)
		Z_PARAM_STR(uplane)
		Z_PARAM_LONG(upitch)
		Z_PARAM_STR(vplane)
		Z_PARAM_LONG(vpitch)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 7, 1, &texture_param, &yplane_param, &ypitch_param, &uplane_param, &upitch_param, &vplane_param, &vpitch_param, &rect);
	zephir_get_strval(&yplane, yplane_param);
	zephir_get_strval(&uplane, uplane_param);
	zephir_get_strval(&vplane, vplane_param);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	
            SDL_Texture *tex = (SDL_Texture *)(uintptr_t) texture;

            SDL_Rect rect_buf = {0};
            const SDL_Rect *rect_ptr = NULL;

            if (Z_TYPE_P(rect) == IS_ARRAY) {
                zval *rx = zend_hash_index_find(Z_ARRVAL_P(rect), 0);
                zval *ry = zend_hash_index_find(Z_ARRVAL_P(rect), 1);
                zval *rw = zend_hash_index_find(Z_ARRVAL_P(rect), 2);
                zval *rh = zend_hash_index_find(Z_ARRVAL_P(rect), 3);
                if (rx && ry && rw && rh) {
                    rect_buf.x = (int) zval_get_long(rx);
                    rect_buf.y = (int) zval_get_long(ry);
                    rect_buf.w = (int) zval_get_long(rw);
                    rect_buf.h = (int) zval_get_long(rh);
                    rect_ptr = &rect_buf;
                }
            }

            result = SDL_UpdateYUVTexture(
                tex, rect_ptr,
                (const Uint8 *) Z_STRVAL(yplane), (int) ypitch,
                (const Uint8 *) Z_STRVAL(uplane), (int) upitch,
                (const Uint8 *) Z_STRVAL(vplane), (int) vpitch
            );
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLUpdateNVTexture)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval yplane, uvplane;
	zval *texture_param = NULL, *yplane_param = NULL, *ypitch_param = NULL, *uvplane_param = NULL, *uvpitch_param = NULL, *rect = NULL, rect_sub, __$null;
	zend_long texture, ypitch, uvpitch;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&yplane);
	ZVAL_UNDEF(&uvplane);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(5, 6)
		Z_PARAM_LONG(texture)
		Z_PARAM_STR(yplane)
		Z_PARAM_LONG(ypitch)
		Z_PARAM_STR(uvplane)
		Z_PARAM_LONG(uvpitch)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 5, 1, &texture_param, &yplane_param, &ypitch_param, &uvplane_param, &uvpitch_param, &rect);
	zephir_get_strval(&yplane, yplane_param);
	zephir_get_strval(&uvplane, uvplane_param);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	
            SDL_Texture *tex = (SDL_Texture *)(uintptr_t) texture;

            SDL_Rect rect_buf = {0};
            const SDL_Rect *rect_ptr = NULL;

            if (Z_TYPE_P(rect) == IS_ARRAY) {
                zval *rx = zend_hash_index_find(Z_ARRVAL_P(rect), 0);
                zval *ry = zend_hash_index_find(Z_ARRVAL_P(rect), 1);
                zval *rw = zend_hash_index_find(Z_ARRVAL_P(rect), 2);
                zval *rh = zend_hash_index_find(Z_ARRVAL_P(rect), 3);
                if (rx && ry && rw && rh) {
                    rect_buf.x = (int) zval_get_long(rx);
                    rect_buf.y = (int) zval_get_long(ry);
                    rect_buf.w = (int) zval_get_long(rw);
                    rect_buf.h = (int) zval_get_long(rh);
                    rect_ptr = &rect_buf;
                }
            }

            result = SDL_UpdateNVTexture(
                tex, rect_ptr,
                (const Uint8 *) Z_STRVAL(yplane), (int) ypitch,
                (const Uint8 *) Z_STRVAL(uvplane), (int) uvpitch
            );
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLLockTexture)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *texture_param = NULL, *rect = NULL, rect_sub, __$null, _0;
	zend_long texture, pitch = 0, lock_w = 0, lock_h = 0, pixels_ptr = 0;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(texture)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &texture_param, &rect);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	
            SDL_Texture *tex = (SDL_Texture *)(uintptr_t) texture;
            SDL_Rect rect_buf = {0};
            const SDL_Rect *rect_ptr = NULL;

            if (Z_TYPE_P(rect) == IS_ARRAY) {
                zval *rx = zend_hash_index_find(Z_ARRVAL_P(rect), 0);
                zval *ry = zend_hash_index_find(Z_ARRVAL_P(rect), 1);
                zval *rw = zend_hash_index_find(Z_ARRVAL_P(rect), 2);
                zval *rh = zend_hash_index_find(Z_ARRVAL_P(rect), 3);
                if (rx && ry && rw && rh) {
                    rect_buf.x = (int) zval_get_long(rx);
                    rect_buf.y = (int) zval_get_long(ry);
                    rect_buf.w = (int) zval_get_long(rw);
                    rect_buf.h = (int) zval_get_long(rh);
                    rect_ptr = &rect_buf;
                }
            }

            void *pixels = NULL;
            int pitch_local = 0;
            bool ok = SDL_LockTexture(tex, rect_ptr, &pixels, &pitch_local);

            if (!ok || !pixels) {
                pitch = 0; lock_w = 0; lock_h = 0; pixels_ptr = 0;
            } else {
                pitch = (zend_long) pitch_local;
                pixels_ptr = (zend_long)(uintptr_t) pixels;
                if (rect_ptr) {
                    lock_w = (zend_long) rect_ptr->w;
                    lock_h = (zend_long) rect_ptr->h;
                } else {
                    float fw = 0.0f, fh = 0.0f;
                    SDL_GetTextureSize(tex, &fw, &fh);
                    lock_w = (zend_long) fw;
                    lock_h = (zend_long) fh;
                }
            }
        
	if (pixels_ptr == 0) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 4, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, pitch);
	zephir_array_update_string(return_value, SL("pitch"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, lock_w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, lock_h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, pixels_ptr);
	zephir_array_update_string(return_value, SL("pixels_ptr"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderTarget)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *texture = NULL, texture_sub, __$null;
	zend_long renderer;

	ZVAL_UNDEF(&texture_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(texture)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &renderer_param, &texture);
	if (!texture) {
		texture = &texture_sub;
		texture = &__$null;
	}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *tex = NULL;

            if (Z_TYPE_P(texture) != IS_NULL && zval_get_long(texture) != 0) {
                tex = (SDL_Texture *)(uintptr_t) zval_get_long(texture);
            }

            result = SDL_SetRenderTarget(ren, tex);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderTarget)
{
	zval *renderer_param = NULL;
	zend_long renderer, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *tex = SDL_GetRenderTarget(ren);
            ptr = tex ? (zend_long)(uintptr_t) tex : 0;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderLogicalPresentation)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer, w = 0, h = 0, mode = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            int ww = 0, hh = 0;
            SDL_RendererLogicalPresentation pres = SDL_LOGICAL_PRESENTATION_DISABLED;
            result = SDL_GetRenderLogicalPresentation(ren, &ww, &hh, &pres);
            w = (zend_long) ww;
            h = (zend_long) hh;
            mode = (zend_long) pres;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 3, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, mode);
	zephir_array_update_string(return_value, SL("mode"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderLogicalPresentationRect)
{
	zend_bool result = 0;
	double x = 0, y = 0, w = 0, h = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_FRect rect = {0};
            result = SDL_GetRenderLogicalPresentationRect(ren, &rect);
            x = (double) rect.x;
            y = (double) rect.y;
            w = (double) rect.w;
            h = (double) rect.h;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 4, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_DOUBLE(&_0, x);
	zephir_array_update_long(return_value, 0, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, y);
	zephir_array_update_long(return_value, 1, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, w);
	zephir_array_update_long(return_value, 2, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, h);
	zephir_array_update_long(return_value, 3, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderCoordinatesFromWindow)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	double windowX, windowY, x = 0, y = 0;
	zval *renderer_param = NULL, *windowX_param = NULL, *windowY_param = NULL, _0;
	zend_long renderer;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(renderer)
		Z_PARAM_ZVAL(windowX)
		Z_PARAM_ZVAL(windowY)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &renderer_param, &windowX_param, &windowY_param);
	windowX = zephir_get_doubleval(windowX_param);
	windowY = zephir_get_doubleval(windowY_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            float rx = 0.0f, ry = 0.0f;
            result = SDL_RenderCoordinatesFromWindow(ren, (float) windowX, (float) windowY, &rx, &ry);
            x = (double) rx;
            y = (double) ry;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_DOUBLE(&_0, x);
	zephir_array_update_string(return_value, SL("x"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, y);
	zephir_array_update_string(return_value, SL("y"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderCoordinatesToWindow)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	double x, y, windowX = 0, windowY = 0;
	zval *renderer_param = NULL, *x_param = NULL, *y_param = NULL, _0;
	zend_long renderer;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(renderer)
		Z_PARAM_ZVAL(x)
		Z_PARAM_ZVAL(y)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &renderer_param, &x_param, &y_param);
	x = zephir_get_doubleval(x_param);
	y = zephir_get_doubleval(y_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            float wx = 0.0f, wy = 0.0f;
            result = SDL_RenderCoordinatesToWindow(ren, (float) x, (float) y, &wx, &wy);
            windowX = (double) wx;
            windowY = (double) wy;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_DOUBLE(&_0, windowX);
	zephir_array_update_string(return_value, SL("window_x"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, windowY);
	zephir_array_update_string(return_value, SL("window_y"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLConvertEventToRenderCoordinates)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *eventPtr_param = NULL;
	zend_long renderer, eventPtr;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(eventPtr)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &renderer_param, &eventPtr_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Event *event = (SDL_Event *)(uintptr_t) eventPtr;
            result = SDL_ConvertEventToRenderCoordinates(ren, event);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderViewport)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer, x = 0, y = 0, w = 0, h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Rect rect = {0};
            result = SDL_GetRenderViewport(ren, &rect);
            x = (zend_long) rect.x;
            y = (zend_long) rect.y;
            w = (zend_long) rect.w;
            h = (zend_long) rect.h;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 4, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, x);
	zephir_array_update_long(return_value, 0, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, y);
	zephir_array_update_long(return_value, 1, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_long(return_value, 2, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_long(return_value, 3, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderViewportSet)
{
	zend_bool result = 0;
	zval *renderer_param = NULL;
	zend_long renderer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_RenderViewportSet(ren);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderSafeArea)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer, x = 0, y = 0, w = 0, h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Rect rect = {0};
            result = SDL_GetRenderSafeArea(ren, &rect);
            x = (zend_long) rect.x;
            y = (zend_long) rect.y;
            w = (zend_long) rect.w;
            h = (zend_long) rect.h;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 4, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, x);
	zephir_array_update_long(return_value, 0, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, y);
	zephir_array_update_long(return_value, 1, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_long(return_value, 2, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_long(return_value, 3, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderClipRect)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer, x = 0, y = 0, w = 0, h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Rect rect = {0};
            result = SDL_GetRenderClipRect(ren, &rect);
            x = (zend_long) rect.x;
            y = (zend_long) rect.y;
            w = (zend_long) rect.w;
            h = (zend_long) rect.h;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 4, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, x);
	zephir_array_update_long(return_value, 0, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, y);
	zephir_array_update_long(return_value, 1, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_long(return_value, 2, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_long(return_value, 3, &_0, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderClipEnabled)
{
	zend_bool result = 0;
	zval *renderer_param = NULL;
	zend_long renderer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_RenderClipEnabled(ren);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderScale)
{
	zend_bool result = 0;
	double scaleX = 0, scaleY = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            float sx = 0.0f, sy = 0.0f;
            result = SDL_GetRenderScale(ren, &sx, &sy);
            scaleX = (double) sx;
            scaleY = (double) sy;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_DOUBLE(&_0, scaleX);
	zephir_array_update_string(return_value, SL("scale_x"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, scaleY);
	zephir_array_update_string(return_value, SL("scale_y"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderDrawColor)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer, r = 0, g = 0, b = 0, a = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            Uint8 rr = 0, gg = 0, bb = 0, aa = 0;
            result = SDL_GetRenderDrawColor(ren, &rr, &gg, &bb, &aa);
            r = (zend_long) rr;
            g = (zend_long) gg;
            b = (zend_long) bb;
            a = (zend_long) aa;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
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

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderDrawColorFloat)
{
	zend_bool result = 0;
	double r = 0, g = 0, b = 0, a = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            float rr = 0.0f, gg = 0.0f, bb = 0.0f, aa = 0.0f;
            result = SDL_GetRenderDrawColorFloat(ren, &rr, &gg, &bb, &aa);
            r = (double) rr;
            g = (double) gg;
            b = (double) bb;
            a = (double) aa;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 4, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_DOUBLE(&_0, r);
	zephir_array_update_string(return_value, SL("r"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, g);
	zephir_array_update_string(return_value, SL("g"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, b);
	zephir_array_update_string(return_value, SL("b"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, a);
	zephir_array_update_string(return_value, SL("a"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderColorScale)
{
	zend_bool result = 0;
	double scale;
	zval *renderer_param = NULL, *scale_param = NULL;
	zend_long renderer;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_ZVAL(scale)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &renderer_param, &scale_param);
	scale = zephir_get_doubleval(scale_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderColorScale(ren, (float) scale);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderColorScale)
{
	zend_bool result = 0;
	double scale = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            float sc = 0.0f;
            result = SDL_GetRenderColorScale(ren, &sc);
            scale = (double) sc;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 1, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_DOUBLE(&_0, scale);
	zephir_array_update_string(return_value, SL("scale"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderDrawBlendMode)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *blendMode_param = NULL;
	zend_long renderer, blendMode;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(blendMode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &renderer_param, &blendMode_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderDrawBlendMode(ren, (SDL_BlendMode) blendMode);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderDrawBlendMode)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer, blendMode = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_BlendMode mode = SDL_BLENDMODE_INVALID;
            result = SDL_GetRenderDrawBlendMode(ren, &mode);
            blendMode = (zend_long) mode;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 1, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, blendMode);
	zephir_array_update_string(return_value, SL("blend_mode"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderPoint)
{
	zend_bool result = 0;
	double x, y;
	zval *renderer_param = NULL, *x_param = NULL, *y_param = NULL;
	zend_long renderer;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(renderer)
		Z_PARAM_ZVAL(x)
		Z_PARAM_ZVAL(y)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &renderer_param, &x_param, &y_param);
	x = zephir_get_doubleval(x_param);
	y = zephir_get_doubleval(y_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_RenderPoint(ren, (float) x, (float) y);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderTextureTiled)
{
	zend_bool result = 0;
	double scale;
	zval *renderer_param = NULL, *texture_param = NULL, *scale_param = NULL, *srcrect = NULL, srcrect_sub, *dstrect = NULL, dstrect_sub, __$null;
	zend_long renderer, texture;

	ZVAL_UNDEF(&srcrect_sub);
	ZVAL_UNDEF(&dstrect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(3, 5)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(texture)
		Z_PARAM_ZVAL(scale)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(srcrect)
		Z_PARAM_ZVAL_OR_NULL(dstrect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 2, &renderer_param, &texture_param, &scale_param, &srcrect, &dstrect);
	scale = zephir_get_doubleval(scale_param);
	if (!srcrect) {
		srcrect = &srcrect_sub;
		srcrect = &__$null;
	}
	if (!dstrect) {
		dstrect = &dstrect_sub;
		dstrect = &__$null;
	}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *te  = (SDL_Texture *)(uintptr_t) texture;

            SDL_FRect src_buf = {0}, dst_buf = {0};
            const SDL_FRect *src_ptr = NULL;
            const SDL_FRect *dst_ptr = NULL;

            if (Z_TYPE_P(srcrect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(srcrect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(srcrect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(srcrect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(srcrect), 3);
                if (x && y && w && h) {
                    src_buf.x = (float) zval_get_double(x);
                    src_buf.y = (float) zval_get_double(y);
                    src_buf.w = (float) zval_get_double(w);
                    src_buf.h = (float) zval_get_double(h);
                    src_ptr = &src_buf;
                }
            }

            if (Z_TYPE_P(dstrect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(dstrect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(dstrect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(dstrect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(dstrect), 3);
                if (x && y && w && h) {
                    dst_buf.x = (float) zval_get_double(x);
                    dst_buf.y = (float) zval_get_double(y);
                    dst_buf.w = (float) zval_get_double(w);
                    dst_buf.h = (float) zval_get_double(h);
                    dst_ptr = &dst_buf;
                }
            }

            result = SDL_RenderTextureTiled(ren, te, src_ptr, (float) scale, dst_ptr);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderTexture9Grid)
{
	zend_bool result = 0;
	double leftWidth, rightWidth, topHeight, bottomHeight, scale;
	zval *renderer_param = NULL, *texture_param = NULL, *leftWidth_param = NULL, *rightWidth_param = NULL, *topHeight_param = NULL, *bottomHeight_param = NULL, *scale_param = NULL, *srcrect = NULL, srcrect_sub, *dstrect = NULL, dstrect_sub, __$null;
	zend_long renderer, texture;

	ZVAL_UNDEF(&srcrect_sub);
	ZVAL_UNDEF(&dstrect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(7, 9)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(texture)
		Z_PARAM_ZVAL(leftWidth)
		Z_PARAM_ZVAL(rightWidth)
		Z_PARAM_ZVAL(topHeight)
		Z_PARAM_ZVAL(bottomHeight)
		Z_PARAM_ZVAL(scale)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(srcrect)
		Z_PARAM_ZVAL_OR_NULL(dstrect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(7, 2, &renderer_param, &texture_param, &leftWidth_param, &rightWidth_param, &topHeight_param, &bottomHeight_param, &scale_param, &srcrect, &dstrect);
	leftWidth = zephir_get_doubleval(leftWidth_param);
	rightWidth = zephir_get_doubleval(rightWidth_param);
	topHeight = zephir_get_doubleval(topHeight_param);
	bottomHeight = zephir_get_doubleval(bottomHeight_param);
	scale = zephir_get_doubleval(scale_param);
	if (!srcrect) {
		srcrect = &srcrect_sub;
		srcrect = &__$null;
	}
	if (!dstrect) {
		dstrect = &dstrect_sub;
		dstrect = &__$null;
	}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *te  = (SDL_Texture *)(uintptr_t) texture;

            SDL_FRect src_buf = {0}, dst_buf = {0};
            const SDL_FRect *src_ptr = NULL;
            const SDL_FRect *dst_ptr = NULL;

            if (Z_TYPE_P(srcrect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(srcrect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(srcrect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(srcrect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(srcrect), 3);
                if (x && y && w && h) {
                    src_buf.x = (float) zval_get_double(x);
                    src_buf.y = (float) zval_get_double(y);
                    src_buf.w = (float) zval_get_double(w);
                    src_buf.h = (float) zval_get_double(h);
                    src_ptr = &src_buf;
                }
            }

            if (Z_TYPE_P(dstrect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(dstrect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(dstrect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(dstrect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(dstrect), 3);
                if (x && y && w && h) {
                    dst_buf.x = (float) zval_get_double(x);
                    dst_buf.y = (float) zval_get_double(y);
                    dst_buf.w = (float) zval_get_double(w);
                    dst_buf.h = (float) zval_get_double(h);
                    dst_ptr = &dst_buf;
                }
            }

            result = SDL_RenderTexture9Grid(
                ren, te, src_ptr,
                (float) leftWidth, (float) rightWidth, (float) topHeight, (float) bottomHeight,
                (float) scale, dst_ptr
            );
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderTexture9GridTiled)
{
	zend_bool result = 0;
	double leftWidth, rightWidth, topHeight, bottomHeight, scale, tileScale;
	zval *renderer_param = NULL, *texture_param = NULL, *leftWidth_param = NULL, *rightWidth_param = NULL, *topHeight_param = NULL, *bottomHeight_param = NULL, *scale_param = NULL, *tileScale_param = NULL, *srcrect = NULL, srcrect_sub, *dstrect = NULL, dstrect_sub, __$null;
	zend_long renderer, texture;

	ZVAL_UNDEF(&srcrect_sub);
	ZVAL_UNDEF(&dstrect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(8, 10)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(texture)
		Z_PARAM_ZVAL(leftWidth)
		Z_PARAM_ZVAL(rightWidth)
		Z_PARAM_ZVAL(topHeight)
		Z_PARAM_ZVAL(bottomHeight)
		Z_PARAM_ZVAL(scale)
		Z_PARAM_ZVAL(tileScale)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(srcrect)
		Z_PARAM_ZVAL_OR_NULL(dstrect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(8, 2, &renderer_param, &texture_param, &leftWidth_param, &rightWidth_param, &topHeight_param, &bottomHeight_param, &scale_param, &tileScale_param, &srcrect, &dstrect);
	leftWidth = zephir_get_doubleval(leftWidth_param);
	rightWidth = zephir_get_doubleval(rightWidth_param);
	topHeight = zephir_get_doubleval(topHeight_param);
	bottomHeight = zephir_get_doubleval(bottomHeight_param);
	scale = zephir_get_doubleval(scale_param);
	tileScale = zephir_get_doubleval(tileScale_param);
	if (!srcrect) {
		srcrect = &srcrect_sub;
		srcrect = &__$null;
	}
	if (!dstrect) {
		dstrect = &dstrect_sub;
		dstrect = &__$null;
	}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *te  = (SDL_Texture *)(uintptr_t) texture;

            SDL_FRect src_buf = {0}, dst_buf = {0};
            const SDL_FRect *src_ptr = NULL;
            const SDL_FRect *dst_ptr = NULL;

            if (Z_TYPE_P(srcrect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(srcrect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(srcrect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(srcrect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(srcrect), 3);
                if (x && y && w && h) {
                    src_buf.x = (float) zval_get_double(x);
                    src_buf.y = (float) zval_get_double(y);
                    src_buf.w = (float) zval_get_double(w);
                    src_buf.h = (float) zval_get_double(h);
                    src_ptr = &src_buf;
                }
            }

            if (Z_TYPE_P(dstrect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(dstrect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(dstrect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(dstrect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(dstrect), 3);
                if (x && y && w && h) {
                    dst_buf.x = (float) zval_get_double(x);
                    dst_buf.y = (float) zval_get_double(y);
                    dst_buf.w = (float) zval_get_double(w);
                    dst_buf.h = (float) zval_get_double(h);
                    dst_ptr = &dst_buf;
                }
            }

            result = SDL_RenderTexture9GridTiled(
                ren, te, src_ptr,
                (float) leftWidth, (float) rightWidth, (float) topHeight, (float) bottomHeight,
                (float) scale, dst_ptr, (float) tileScale
            );
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderGeometryRaw)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval xy;
	zval *renderer_param = NULL, *texture_param = NULL, *xy_param = NULL, *xyStride_param = NULL, *color = NULL, color_sub, *colorStride_param = NULL, *uv = NULL, uv_sub, *uvStride_param = NULL, *numVertices_param = NULL, *indices = NULL, indices_sub, *numIndices_param = NULL, *sizeIndices_param = NULL, __$null;
	zend_long renderer, texture, xyStride, colorStride, uvStride, numVertices, numIndices, sizeIndices;

	ZVAL_UNDEF(&color_sub);
	ZVAL_UNDEF(&uv_sub);
	ZVAL_UNDEF(&indices_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&xy);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(4, 12)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(texture)
		Z_PARAM_STR(xy)
		Z_PARAM_LONG(xyStride)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(color)
		Z_PARAM_LONG(colorStride)
		Z_PARAM_ZVAL_OR_NULL(uv)
		Z_PARAM_LONG(uvStride)
		Z_PARAM_LONG(numVertices)
		Z_PARAM_ZVAL_OR_NULL(indices)
		Z_PARAM_LONG(numIndices)
		Z_PARAM_LONG(sizeIndices)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 8, &renderer_param, &texture_param, &xy_param, &xyStride_param, &color, &colorStride_param, &uv, &uvStride_param, &numVertices_param, &indices, &numIndices_param, &sizeIndices_param);
	zephir_get_strval(&xy, xy_param);
	if (!color) {
		color = &color_sub;
		color = &__$null;
	}
	if (!colorStride_param) {
		colorStride = 0;
	} else {
		}
	if (!uv) {
		uv = &uv_sub;
		uv = &__$null;
	}
	if (!uvStride_param) {
		uvStride = 0;
	} else {
		}
	if (!numVertices_param) {
		numVertices = 0;
	} else {
		}
	if (!indices) {
		indices = &indices_sub;
		indices = &__$null;
	}
	if (!numIndices_param) {
		numIndices = 0;
	} else {
		}
	if (!sizeIndices_param) {
		sizeIndices = 4;
	} else {
		}
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *tex = texture ? (SDL_Texture *)(uintptr_t) texture : NULL;

            const SDL_FColor *color_ptr = NULL;
            const float *uv_ptr = NULL;
            const void *indices_ptr = NULL;

            if (Z_TYPE_P(color) == IS_STRING && Z_STRLEN_P(color) > 0) {
                color_ptr = (const SDL_FColor *) Z_STRVAL_P(color);
            }

            if (Z_TYPE_P(uv) == IS_STRING && Z_STRLEN_P(uv) > 0) {
                uv_ptr = (const float *) Z_STRVAL_P(uv);
            }

            if (Z_TYPE_P(indices) == IS_STRING && Z_STRLEN_P(indices) > 0) {
                indices_ptr = (const void *) Z_STRVAL_P(indices);
            }

            result = SDL_RenderGeometryRaw(
                ren, tex,
                (const float *) Z_STRVAL(xy), (int) xyStride,
                color_ptr, (int) colorStride,
                uv_ptr, (int) uvStride,
                (int) numVertices,
                indices_ptr, (int) numIndices, (int) sizeIndices
            );
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderTextureAddressMode)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *uMode_param = NULL, *vMode_param = NULL;
	zend_long renderer, uMode, vMode;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(uMode)
		Z_PARAM_LONG(vMode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &renderer_param, &uMode_param, &vMode_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderTextureAddressMode(ren, (SDL_TextureAddressMode) uMode, (SDL_TextureAddressMode) vMode);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderTextureAddressMode)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer, uMode = 0, vMode = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_TextureAddressMode um = SDL_TEXTURE_ADDRESS_INVALID;
            SDL_TextureAddressMode vm = SDL_TEXTURE_ADDRESS_INVALID;
            result = SDL_GetRenderTextureAddressMode(ren, &um, &vm);
            uMode = (zend_long) um;
            vMode = (zend_long) vm;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, uMode);
	zephir_array_update_string(return_value, SL("u_mode"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, vMode);
	zephir_array_update_string(return_value, SL("v_mode"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLFlushRenderer)
{
	zend_bool result = 0;
	zval *renderer_param = NULL;
	zend_long renderer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_FlushRenderer(ren);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderMetalLayer)
{
	zval *renderer_param = NULL;
	zend_long renderer, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            void *layer = SDL_GetRenderMetalLayer(ren);
            ptr = layer ? (zend_long)(uintptr_t) layer : 0;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderMetalCommandEncoder)
{
	zval *renderer_param = NULL;
	zend_long renderer, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            void *encoder = SDL_GetRenderMetalCommandEncoder(ren);
            ptr = encoder ? (zend_long)(uintptr_t) encoder : 0;
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLAddVulkanRenderSemaphores)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *waitStageMask_param = NULL, *waitSemaphore_param = NULL, *signalSemaphore_param = NULL;
	zend_long renderer, waitStageMask, waitSemaphore, signalSemaphore;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(waitStageMask)
		Z_PARAM_LONG(waitSemaphore)
		Z_PARAM_LONG(signalSemaphore)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &renderer_param, &waitStageMask_param, &waitSemaphore_param, &signalSemaphore_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_AddVulkanRenderSemaphores(
                ren,
                (Uint32) waitStageMask,
                (Sint64) waitSemaphore,
                (Sint64) signalSemaphore
            );
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderVSync)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *vsync_param = NULL;
	zend_long renderer, vsync;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(vsync)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &renderer_param, &vsync_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderVSync(ren, (int) vsync);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderVSync)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer, vsync = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            int vs = 0;
            result = SDL_GetRenderVSync(ren, &vs);
            vsync = (zend_long) vs;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 1, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, vsync);
	zephir_array_update_string(return_value, SL("vsync"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetDefaultTextureScaleMode)
{
	zend_bool result = 0;
	zval *renderer_param = NULL, *scaleMode_param = NULL;
	zend_long renderer, scaleMode;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_LONG(scaleMode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &renderer_param, &scaleMode_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetDefaultTextureScaleMode(ren, (SDL_ScaleMode) scaleMode);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetDefaultTextureScaleMode)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderer_param = NULL, _0;
	zend_long renderer, scaleMode = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(renderer)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderer_param);
	
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_ScaleMode mode = SDL_SCALEMODE_NEAREST;
            result = SDL_GetDefaultTextureScaleMode(ren, &mode);
            scaleMode = (zend_long) mode;
        
	if (!(result)) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 1, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, scaleMode);
	zephir_array_update_string(return_value, SL("scale_mode"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

