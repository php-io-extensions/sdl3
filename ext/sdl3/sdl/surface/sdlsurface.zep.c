
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
#include "kernel/array.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/concat.h"

#include <SDL3/SDL.h>
#include <stdio.h>

static const SDL_Rect *sdl3_rect_from_zval(zval *rect_zv, SDL_Rect *buf)
{
    if (Z_TYPE_P(rect_zv) == IS_ARRAY) {
        zval *x = zend_hash_index_find(Z_ARRVAL_P(rect_zv), 0);
        zval *y = zend_hash_index_find(Z_ARRVAL_P(rect_zv), 1);
        zval *w = zend_hash_index_find(Z_ARRVAL_P(rect_zv), 2);
        zval *h = zend_hash_index_find(Z_ARRVAL_P(rect_zv), 3);
        if (x && y && w && h) {
            buf->x = (int) zval_get_long(x);
            buf->y = (int) zval_get_long(y);
            buf->w = (int) zval_get_long(w);
            buf->h = (int) zval_get_long(h);
            return buf;
        }
    }
    return NULL;
}

static void sdl3_copy_surface_pixels(SDL_Surface *surf, zval *pixels_data)
{
    array_init(pixels_data);
    if (surf && surf->pixels) {
        for (int py = 0; py < surf->h; py++) {
            Uint32 *row = (Uint32 *)(((Uint8 *)surf->pixels) + py * surf->pitch);
            for (int px = 0; px < surf->w; px++) {
                add_next_index_long(pixels_data, (zend_long)(zend_ulong)row[px]);
            }
        }
    }
}

static void sdl3_read_surface_fields(SDL_Surface *surf, zend_long *ptr, zend_long *flags, zend_long *fmt,
    zend_long *w, zend_long *h, zend_long *pitch, zend_long *pixels_ptr, zend_long *refcount)
{
    if (!surf) {
        *ptr = 0; *flags = 0; *fmt = 0; *w = 0; *h = 0; *pitch = 0; *pixels_ptr = 0; *refcount = 0;
        return;
    }
    *ptr        = (zend_long)(uintptr_t) surf;
    *flags      = (zend_long) surf->flags;
    *fmt        = (zend_long) surf->format;
    *w          = (zend_long) surf->w;
    *h          = (zend_long) surf->h;
    *pitch      = (zend_long) surf->pitch;
    *pixels_ptr = surf->pixels ? (zend_long)(uintptr_t) surf->pixels : 0;
    *refcount   = (zend_long) surf->refcount;
}

static void sdl3_read_palette_fields(SDL_Palette *pal, zend_long *ptr, zend_long *ncolors, zend_long *version,
    zend_long *refcount, zval *colors)
{
    if (!pal) {
        *ptr = 0; *ncolors = 0; *version = 0; *refcount = 0;
        array_init(colors);
        return;
    }
    *ptr      = (zend_long)(uintptr_t) pal;
    *ncolors  = (zend_long) pal->ncolors;
    *version  = (zend_long) pal->version;
    *refcount = (zend_long) pal->refcount;
    array_init(colors);
    for (int i = 0; i < pal->ncolors; i++) {
        zval entry;
        array_init(&entry);
        add_assoc_long(&entry, "r", (zend_long) pal->colors[i].r);
        add_assoc_long(&entry, "g", (zend_long) pal->colors[i].g);
        add_assoc_long(&entry, "b", (zend_long) pal->colors[i].b);
        add_assoc_long(&entry, "a", (zend_long) pal->colors[i].a);
        add_next_index_zval(colors, &entry);
    }
}



ZEPHIR_INIT_CLASS(Sdl3_SDL_Surface_SDLSurface)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Surface, SDLSurface, sdl3, sdl_surface_sdlsurface, sdl3_sdl_surface_sdlsurface_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLCreateSurface)
{
	zval pixels_data, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *width_param = NULL, *height_param = NULL, *format_param = NULL, _0;
	zend_long width, height, format, ptr = 0, flags = 0, fmt = 0, w = 0, h = 0, pitch = 0, pixels_ptr = 0, refcount = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&pixels_data);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &width_param, &height_param, &format_param);
	
            SDL_Surface *surf = SDL_CreateSurface((int) width, (int) height, (SDL_PixelFormat) format);

            if (!surf) {
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

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLDuplicateSurface)
{
	zval pixels_data, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *surface_param = NULL, _0;
	zend_long surface, ptr = 0, flags = 0, fmt = 0, w = 0, h = 0, pitch = 0, pixels_ptr = 0, refcount = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&pixels_data);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &surface_param);
	
            SDL_Surface *src  = (SDL_Surface *)(uintptr_t) surface;
            SDL_Surface *surf = SDL_DuplicateSurface(src);

            if (!surf) {
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

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLConvertSurface)
{
	zval pixels_data, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *surface_param = NULL, *format_param = NULL, _0;
	zend_long surface, format, ptr = 0, flags = 0, fmt = 0, w = 0, h = 0, pitch = 0, pixels_ptr = 0, refcount = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&pixels_data);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &surface_param, &format_param);
	
            SDL_Surface *src  = (SDL_Surface *)(uintptr_t) surface;
            SDL_Surface *surf = SDL_ConvertSurface(src, (SDL_PixelFormat) format);

            if (!surf) {
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

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSurfaceToBlackAndWhite)
{
	zval *surface_param = NULL;
	zend_long surface;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            int x, y;
            for (y = 0; y < surf->h; y++) {
                Uint32 *pixels = (Uint32 *)(((Uint8 *) surf->pixels) + (y * surf->pitch));
                for (x = 0; x < surf->w; x++) {
                    Uint8 *p = (Uint8 *)(&pixels[x]);
                    const Uint32 average = (((Uint32) p[1]) + ((Uint32) p[2]) + ((Uint32) p[3])) / 3;
                    if (average == 0) {
                        p[0] = p[3] = 0xFF; p[1] = p[2] = 0;
                    } else {
                        p[1] = p[2] = p[3] = (average > 50) ? 0xFF : 0x00;
                    }
                }
            }
        
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurface)
{
	zend_bool result = 0;
	zval *src_param = NULL, *dst_param = NULL, *srcrect = NULL, srcrect_sub, *dstrect = NULL, dstrect_sub, __$null;
	zend_long src, dst;

	ZVAL_UNDEF(&srcrect_sub);
	ZVAL_UNDEF(&dstrect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_LONG(src)
		Z_PARAM_LONG(dst)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(srcrect)
		Z_PARAM_ZVAL_OR_NULL(dstrect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 2, &src_param, &dst_param, &srcrect, &dstrect);
	if (!srcrect) {
		srcrect = &srcrect_sub;
		srcrect = &__$null;
	}
	if (!dstrect) {
		dstrect = &dstrect_sub;
		dstrect = &__$null;
	}
	
            SDL_Surface *src_surf = (SDL_Surface *)(uintptr_t) src;
            SDL_Surface *dst_surf = (SDL_Surface *)(uintptr_t) dst;

            SDL_Rect src_buf = {0}, dst_buf = {0};
            const SDL_Rect *src_ptr = NULL;
            const SDL_Rect *dst_ptr = NULL;

            if (Z_TYPE_P(srcrect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(srcrect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(srcrect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(srcrect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(srcrect), 3);
                if (x && y && w && h) {
                    src_buf.x = (int) zval_get_long(x);
                    src_buf.y = (int) zval_get_long(y);
                    src_buf.w = (int) zval_get_long(w);
                    src_buf.h = (int) zval_get_long(h);
                    src_ptr = &src_buf;
                }
            }

            if (Z_TYPE_P(dstrect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(dstrect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(dstrect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(dstrect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(dstrect), 3);
                if (x && y && w && h) {
                    dst_buf.x = (int) zval_get_long(x);
                    dst_buf.y = (int) zval_get_long(y);
                    dst_buf.w = (int) zval_get_long(w);
                    dst_buf.h = (int) zval_get_long(h);
                    dst_ptr = &dst_buf;
                }
            }

            result = SDL_BlitSurface(src_surf, src_ptr, dst_surf, dst_ptr);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLFillSurfaceRect)
{
	zend_bool result = 0;
	zval *surface_param = NULL, *color_param = NULL, *rect = NULL, rect_sub, __$null;
	zend_long surface, color;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(color)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 1, &surface_param, &color_param, &rect);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_Rect r, *rp = NULL;

            if (Z_TYPE_P(rect) == IS_ARRAY) {
                zval *x = zend_hash_index_find(Z_ARRVAL_P(rect), 0);
                zval *y = zend_hash_index_find(Z_ARRVAL_P(rect), 1);
                zval *w = zend_hash_index_find(Z_ARRVAL_P(rect), 2);
                zval *h = zend_hash_index_find(Z_ARRVAL_P(rect), 3);
                if (x && y && w && h) {
                    r.x = (int) zval_get_long(x);
                    r.y = (int) zval_get_long(y);
                    r.w = (int) zval_get_long(w);
                    r.h = (int) zval_get_long(h);
                    rp = &r;
                }
            }

            result = SDL_FillSurfaceRect(surf, rp, (Uint32) color);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLMapRGB)
{
	zval *format_param = NULL, *palette_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL;
	zend_long format, palette, r, g, b, result = 0;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(format)
		Z_PARAM_LONG(palette)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &format_param, &palette_param, &r_param, &g_param, &b_param);
	
            const SDL_PixelFormatDetails *fmt = (const SDL_PixelFormatDetails *)(uintptr_t) format;
            const SDL_Palette            *pal = palette ? (const SDL_Palette *)(uintptr_t) palette : NULL;
            result = (zend_long) SDL_MapRGB(fmt, pal, (Uint8) r, (Uint8) g, (Uint8) b);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLLockSurface)
{
	zend_bool result = 0;
	zval *surface_param = NULL;
	zend_long surface;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_LockSurface(surf);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLUnlockSurface)
{
	zval *surface_param = NULL;
	zend_long surface;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_UnlockSurface(surf);
        
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLDestroySurface)
{
	zval *surface_param = NULL;
	zend_long surface;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_DestroySurface(surf);
        
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLLoadPNG)
{
	zval pixels_data, _1;
	zend_long ptr = 0, flags = 0, format = 0, w = 0, h = 0, pitch = 0, pixels_ptr = 0, refcount = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *file_param = NULL, _0;
	zval file;

	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&pixels_data);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(file)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &file_param);
	zephir_get_strval(&file, file_param);
	
            SDL_Surface *surface = SDL_LoadPNG(Z_STRVAL(file));
            if (!surface) {
                ptr = 0; flags = 0; format = 0; w = 0; h = 0; pitch = 0; pixels_ptr = 0; refcount = 0;
                array_init(&pixels_data);
            } else {
                ptr        = (zend_long)(uintptr_t) surface;
                flags      = (zend_long) surface->flags;
                format     = (zend_long) surface->format;
                w          = (zend_long) surface->w;
                h          = (zend_long) surface->h;
                pitch      = (zend_long) surface->pitch;
                pixels_ptr = surface->pixels ? (zend_long)(uintptr_t) surface->pixels : 0;
                refcount   = (zend_long) surface->refcount;
                array_init(&pixels_data);
                if (surface->pixels) {
                    for (int py = 0; py < surface->h; py++) {
                        Uint32 *row = (Uint32 *)(((Uint8 *)surface->pixels) + py * surface->pitch);
                        for (int px = 0; px < surface->w; px++) {
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

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLLoadBMP)
{
	zval pixels_data, _1;
	zend_long ptr = 0, flags = 0, format = 0, w = 0, h = 0, pitch = 0, pixels_ptr = 0, refcount = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *file_param = NULL, _0;
	zval file;

	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&pixels_data);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(file)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &file_param);
	zephir_get_strval(&file, file_param);
	
            SDL_Surface *surface = SDL_LoadBMP(Z_STRVAL(file));
            if (!surface) {
                ptr = 0; flags = 0; format = 0; w = 0; h = 0; pitch = 0; pixels_ptr = 0; refcount = 0;
                array_init(&pixels_data);
            } else {
                ptr        = (zend_long)(uintptr_t) surface;
                flags      = (zend_long) surface->flags;
                format     = (zend_long) surface->format;
                w          = (zend_long) surface->w;
                h          = (zend_long) surface->h;
                pitch      = (zend_long) surface->pitch;
                pixels_ptr = surface->pixels ? (zend_long)(uintptr_t) surface->pixels : 0;
                refcount   = (zend_long) surface->refcount;
                array_init(&pixels_data);
                if (surface->pixels) {
                    for (int py = 0; py < surface->h; py++) {
                        Uint32 *row = (Uint32 *)(((Uint8 *)surface->pixels) + py * surface->pitch);
                        for (int px = 0; px < surface->w; px++) {
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

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLWriteSurfacePixelAt)
{
	zend_bool result = 0;
	zval *surface_param = NULL, *x_param = NULL, *y_param = NULL, *pixel_param = NULL;
	zend_long surface, x, y, pixel;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(pixel)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &surface_param, &x_param, &y_param, &pixel_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            if (!surf || !surf->pixels || x < 0 || y < 0 || x >= surf->w || y >= surf->h) {
                result = 0;
            } else {
                Uint32 *row = (Uint32 *)(((Uint8 *)surf->pixels) + y * surf->pitch);
                row[x] = (Uint32)(zend_ulong)pixel;
                result = 1;
            }
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLWriteSurfacePixels)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval data;
	zval *surface_param = NULL, *data_param = NULL;
	zend_long surface;

	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_ARRAY(data)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &surface_param, &data_param);
	zephir_get_arrval(&data, data_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            if (!surf || !surf->pixels) {
                result = 0;
            } else {
                zval *entry;
                zend_ulong index;
                ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(&data), index, entry) {
                    int py = (int)index / surf->w;
                    int px = (int)index % surf->w;
                    if (py < surf->h && px < surf->w) {
                        Uint32 *row = (Uint32 *)(((Uint8 *)surf->pixels) + py * surf->pitch);
                        row[px] = (Uint32)(zend_ulong)zval_get_long(entry);
                    }
                } ZEND_HASH_FOREACH_END();
                result = 1;
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLReadSurfacePixels)
{
	zval pixels_data;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *surface_param = NULL, _0;
	zend_long surface, pixels_ptr = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&pixels_data);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            array_init(&pixels_data);
            if (surf && surf->pixels) {
                pixels_ptr = (zend_long)(uintptr_t) surf->pixels;
                for (int py = 0; py < surf->h; py++) {
                    Uint32 *row = (Uint32 *)(((Uint8 *)surf->pixels) + py * surf->pitch);
                    for (int px = 0; px < surf->w; px++) {
                        add_next_index_long(&pixels_data, (zend_long)(zend_ulong)row[px]);
                    }
                }
            } else {
                pixels_ptr = 0;
            }
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, pixels_ptr);
	zephir_array_update_string(return_value, SL("pixels_ptr"), &_0, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("pixels_data"), &pixels_data, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfacePalette)
{
	zval colors;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *surface_param = NULL, _0;
	zend_long surface, ptr = 0, ncolors = 0, version = 0, refcount = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&colors);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_Palette *pal  = SDL_GetSurfacePalette(surf);

            if (!pal) {
                ptr = 0; ncolors = 0; version = 0; refcount = 0;
                array_init(&colors);
            } else {
                ptr      = (zend_long)(uintptr_t) pal;
                ncolors  = (zend_long) pal->ncolors;
                version  = (zend_long) pal->version;
                refcount = (zend_long) pal->refcount;

                array_init(&colors);
                for (int i = 0; i < pal->ncolors; i++) {
                    zval entry;
                    array_init(&entry);
                    add_assoc_long(&entry, "r", (zend_long) pal->colors[i].r);
                    add_assoc_long(&entry, "g", (zend_long) pal->colors[i].g);
                    add_assoc_long(&entry, "b", (zend_long) pal->colors[i].b);
                    add_assoc_long(&entry, "a", (zend_long) pal->colors[i].a);
                    add_next_index_zval(&colors, &entry);
                }
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
	ZVAL_LONG(&_0, ncolors);
	zephir_array_update_string(return_value, SL("ncolors"), &_0, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("colors"), &colors, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, version);
	zephir_array_update_string(return_value, SL("version"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, refcount);
	zephir_array_update_string(return_value, SL("refcount"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, buildSurfaceArray)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval pixels_data, _1;
	zval *ptr_param = NULL, *flags_param = NULL, *fmt_param = NULL, *w_param = NULL, *h_param = NULL, *pitch_param = NULL, *pixels_ptr_param = NULL, *pixels_data_param = NULL, *refcount_param = NULL, _0;
	zend_long ptr, flags, fmt, w, h, pitch, pixels_ptr, refcount;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&pixels_data);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(9, 9)
		Z_PARAM_LONG(ptr)
		Z_PARAM_LONG(flags)
		Z_PARAM_LONG(fmt)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(pitch)
		Z_PARAM_LONG(pixels_ptr)
		Z_PARAM_ARRAY(pixels_data)
		Z_PARAM_LONG(refcount)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 9, 0, &ptr_param, &flags_param, &fmt_param, &w_param, &h_param, &pitch_param, &pixels_ptr_param, &pixels_data_param, &refcount_param);
	zephir_get_arrval(&pixels_data, pixels_data_param);
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

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, packSurfaceFromPtr)
{
	zval pixels_data;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *surface_param = NULL, _1, _2, _3, _4, _5, _6, _7, _8;
	zend_long surface, ZEPHIR_LAST_CALL_STATUS, ptr = 0, flags = 0, fmt = 0, w = 0, h = 0, pitch = 0, pixels_ptr = 0, refcount = 0;

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&pixels_data);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            sdl3_read_surface_fields(surf, &ptr, &flags, &fmt, &w, &h, &pitch, &pixels_ptr, &refcount);
            sdl3_copy_surface_pixels(surf, &pixels_data);
        
	ZVAL_LONG(&_1, ptr);
	ZVAL_LONG(&_2, flags);
	ZVAL_LONG(&_3, fmt);
	ZVAL_LONG(&_4, w);
	ZVAL_LONG(&_5, h);
	ZVAL_LONG(&_6, pitch);
	ZVAL_LONG(&_7, pixels_ptr);
	ZVAL_LONG(&_8, refcount);
	ZEPHIR_RETURN_CALL_SELF("buildsurfacearray", &_0, 2, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &pixels_data, &_8);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, buildPaletteArray)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval colors;
	zval *ptr_param = NULL, *ncolors_param = NULL, *colors_param = NULL, *version_param = NULL, *refcount_param = NULL, _0;
	zend_long ptr, ncolors, version, refcount;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&colors);
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(ptr)
		Z_PARAM_LONG(ncolors)
		Z_PARAM_ARRAY(colors)
		Z_PARAM_LONG(version)
		Z_PARAM_LONG(refcount)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 5, 0, &ptr_param, &ncolors_param, &colors_param, &version_param, &refcount_param);
	zephir_get_arrval(&colors, colors_param);
	if (ptr == 0) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 5, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, ptr);
	zephir_array_update_string(return_value, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, ncolors);
	zephir_array_update_string(return_value, SL("ncolors"), &_0, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("colors"), &colors, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, version);
	zephir_array_update_string(return_value, SL("version"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, refcount);
	zephir_array_update_string(return_value, SL("refcount"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, packPaletteFromPtr)
{
	zval colors;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *palette_param = NULL, _1, _2, _3, _4;
	zend_long palette, ZEPHIR_LAST_CALL_STATUS, ptr = 0, ncolors = 0, version = 0, refcount = 0;

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&colors);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(palette)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &palette_param);
	
            SDL_Palette *pal = (SDL_Palette *)(uintptr_t) palette;
            sdl3_read_palette_fields(pal, &ptr, &ncolors, &version, &refcount, &colors);
        
	ZVAL_LONG(&_1, ptr);
	ZVAL_LONG(&_2, ncolors);
	ZVAL_LONG(&_3, version);
	ZVAL_LONG(&_4, refcount);
	ZEPHIR_RETURN_CALL_SELF("buildpalettearray", &_0, 3, &_1, &_2, &colors, &_3, &_4);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLCreateSurfaceFrom)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL;
	zval pixels;
	zval *width_param = NULL, *height_param = NULL, *format_param = NULL, *pixels_param = NULL, *pitch_param = NULL, _4, _0$$3, _1$$3, _2$$3;
	zend_long width, height, format, pitch, ZEPHIR_LAST_CALL_STATUS, surf_ptr = 0;

	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&pixels);
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(format)
		Z_PARAM_STR(pixels)
		Z_PARAM_LONG(pitch)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 5, 0, &width_param, &height_param, &format_param, &pixels_param, &pitch_param);
	zephir_get_strval(&pixels, pixels_param);
	
            SDL_Surface *surf = SDL_CreateSurfaceFrom(
                (int) width,
                (int) height,
                (SDL_PixelFormat) format,
                (void *) Z_STRVAL_P(&pixels),
                (int) pitch
            );
            surf_ptr = surf ? (zend_long)(uintptr_t) surf : 0;
        
	if (surf_ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateSurfaceFrom failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/surface/sdlsurface.zep", 626);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_4, surf_ptr);
	ZEPHIR_RETURN_CALL_SELF("packsurfacefromptr", &_3, 4, &_4);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceProperties)
{
	zval *surface_param = NULL;
	zend_long surface, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = (zend_long) SDL_GetSurfaceProperties(surf);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceColorspace)
{
	zend_bool result = 0;
	zval *surface_param = NULL, *colorspace_param = NULL;
	zend_long surface, colorspace;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(colorspace)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &surface_param, &colorspace_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetSurfaceColorspace(surf, (SDL_Colorspace) colorspace);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceColorspace)
{
	zval *surface_param = NULL;
	zend_long surface, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = (zend_long) SDL_GetSurfaceColorspace(surf);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLCreateSurfacePalette)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL;
	zval *surface_param = NULL, _4, _0$$3, _1$$3, _2$$3;
	zend_long surface, ZEPHIR_LAST_CALL_STATUS, pal_ptr = 0;

	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_Palette *pal  = SDL_CreateSurfacePalette(surf);
            pal_ptr = pal ? (zend_long)(uintptr_t) pal : 0;
        
	if (pal_ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateSurfacePalette failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/surface/sdlsurface.zep", 679);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_4, pal_ptr);
	ZEPHIR_RETURN_CALL_SELF("packpalettefromptr", &_3, 5, &_4);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfacePalette)
{
	zend_bool result = 0;
	zval *surface_param = NULL, *palette_param = NULL;
	zend_long surface, palette;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(palette)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &surface_param, &palette_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_Palette *pal  = (SDL_Palette *)(uintptr_t) palette;
            result = SDL_SetSurfacePalette(surf, pal);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLAddSurfaceAlternateImage)
{
	zend_bool result = 0;
	zval *surface_param = NULL, *image_param = NULL;
	zend_long surface, image;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(image)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &surface_param, &image_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_Surface *img  = (SDL_Surface *)(uintptr_t) image;
            result = SDL_AddSurfaceAlternateImage(surf, img);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSurfaceHasAlternateImages)
{
	zend_bool result = 0;
	zval *surface_param = NULL;
	zend_long surface;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SurfaceHasAlternateImages(surf);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceImages)
{
	zval images;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *surface_param = NULL, _0;
	zend_long surface, count = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&images);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            int c = 0;
            SDL_Surface **imgs = SDL_GetSurfaceImages(surf, &c);
            count = (zend_long) c;
            array_init(&images);
            if (imgs) {
                for (int i = 0; i < c; i++) {
                    add_next_index_long(&images, (zend_long)(uintptr_t) imgs[i]);
                }
                SDL_free(imgs);
            }
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, count);
	zephir_array_update_string(return_value, SL("count"), &_0, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("images"), &images, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLRemoveSurfaceAlternateImages)
{
	zval *surface_param = NULL;
	zend_long surface;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_RemoveSurfaceAlternateImages(surf);
        
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLLoadSurface)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, surf_ptr = 0;
	zval *file_param = NULL, _4, _0$$3, _1$$3, _2$$3;
	zval file;

	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(file)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &file_param);
	zephir_get_strval(&file, file_param);
	
            SDL_Surface *surf = SDL_LoadSurface(Z_STRVAL(file));
            surf_ptr = surf ? (zend_long)(uintptr_t) surf : 0;
        
	if (surf_ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_LoadSurface failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/surface/sdlsurface.zep", 763);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_4, surf_ptr);
	ZEPHIR_RETURN_CALL_SELF("packsurfacefromptr", &_3, 4, &_4);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSaveBMP)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval file;
	zval *surface_param = NULL, *file_param = NULL;
	zend_long surface;

	ZVAL_UNDEF(&file);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_STR(file)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &surface_param, &file_param);
	zephir_get_strval(&file, file_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SaveBMP(surf, Z_STRVAL(file));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSavePNG)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval file;
	zval *surface_param = NULL, *file_param = NULL;
	zend_long surface;

	ZVAL_UNDEF(&file);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_STR(file)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &surface_param, &file_param);
	zephir_get_strval(&file, file_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SavePNG(surf, Z_STRVAL(file));
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceRLE)
{
	zend_bool enabled, result = 0;
	zval *surface_param = NULL, *enabled_param = NULL;
	zend_long surface;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_BOOL(enabled)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &surface_param, &enabled_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetSurfaceRLE(surf, (bool) enabled);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSurfaceHasRLE)
{
	zend_bool result = 0;
	zval *surface_param = NULL;
	zend_long surface;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SurfaceHasRLE(surf);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceColorKey)
{
	zend_bool enabled, result = 0;
	zval *surface_param = NULL, *enabled_param = NULL, *key_param = NULL;
	zend_long surface, key;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(surface)
		Z_PARAM_BOOL(enabled)
		Z_PARAM_LONG(key)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &surface_param, &enabled_param, &key_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetSurfaceColorKey(surf, (bool) enabled, (Uint32) key);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSurfaceHasColorKey)
{
	zend_bool result = 0;
	zval *surface_param = NULL;
	zend_long surface;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SurfaceHasColorKey(surf);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceColorKey)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *surface_param = NULL, _0;
	zend_long surface, key = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            Uint32 k = 0;
            result = SDL_GetSurfaceColorKey(surf, &k);
            key = (zend_long) k;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_BOOL(&_0, result);
	zephir_array_update_string(return_value, SL("result"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, key);
	zephir_array_update_string(return_value, SL("key"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceColorMod)
{
	zend_bool result = 0;
	zval *surface_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL;
	zend_long surface, r, g, b;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &surface_param, &r_param, &g_param, &b_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetSurfaceColorMod(surf, (Uint8) r, (Uint8) g, (Uint8) b);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceColorMod)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *surface_param = NULL, _0;
	zend_long surface, r = 0, g = 0, b = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            Uint8 rr = 0, gg = 0, bb = 0;
            result = SDL_GetSurfaceColorMod(surf, &rr, &gg, &bb);
            r = (zend_long) rr;
            g = (zend_long) gg;
            b = (zend_long) bb;
        
	zephir_create_array(return_value, 4, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_BOOL(&_0, result);
	zephir_array_update_string(return_value, SL("result"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
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

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceAlphaMod)
{
	zend_bool result = 0;
	zval *surface_param = NULL, *alpha_param = NULL;
	zend_long surface, alpha;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(alpha)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &surface_param, &alpha_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetSurfaceAlphaMod(surf, (Uint8) alpha);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceAlphaMod)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *surface_param = NULL, _0;
	zend_long surface, alpha = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            Uint8 a = 0;
            result = SDL_GetSurfaceAlphaMod(surf, &a);
            alpha = (zend_long) a;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_BOOL(&_0, result);
	zephir_array_update_string(return_value, SL("result"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, alpha);
	zephir_array_update_string(return_value, SL("alpha"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceBlendMode)
{
	zend_bool result = 0;
	zval *surface_param = NULL, *blendMode_param = NULL;
	zend_long surface, blendMode;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(blendMode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &surface_param, &blendMode_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetSurfaceBlendMode(surf, (SDL_BlendMode) blendMode);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceBlendMode)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *surface_param = NULL, _0;
	zend_long surface, blendMode = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_BlendMode mode = SDL_BLENDMODE_INVALID;
            result = SDL_GetSurfaceBlendMode(surf, &mode);
            blendMode = (zend_long) mode;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_BOOL(&_0, result);
	zephir_array_update_string(return_value, SL("result"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, blendMode);
	zephir_array_update_string(return_value, SL("blend_mode"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceClipRect)
{
	zend_bool result = 0;
	zval *surface_param = NULL, *rect = NULL, rect_sub, __$null;
	zend_long surface;

	ZVAL_UNDEF(&rect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(rect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &surface_param, &rect);
	if (!rect) {
		rect = &rect_sub;
		rect = &__$null;
	}
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_Rect r_buf;
            const SDL_Rect *rp = sdl3_rect_from_zval(rect, &r_buf);
            result = SDL_SetSurfaceClipRect(surf, rp);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceClipRect)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *surface_param = NULL, _0;
	zend_long surface, x = 0, y = 0, w = 0, h = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(surface)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &surface_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_Rect r = {0, 0, 0, 0};
            result = SDL_GetSurfaceClipRect(surf, &r);
            x = (zend_long) r.x;
            y = (zend_long) r.y;
            w = (zend_long) r.w;
            h = (zend_long) r.h;
        
	zephir_create_array(return_value, 5, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_BOOL(&_0, result);
	zephir_array_update_string(return_value, SL("result"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, x);
	zephir_array_update_string(return_value, SL("x"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, y);
	zephir_array_update_string(return_value, SL("y"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLFlipSurface)
{
	zend_bool result = 0;
	zval *surface_param = NULL, *flip_param = NULL;
	zend_long surface, flip;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(flip)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &surface_param, &flip_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_FlipSurface(surf, (SDL_FlipMode) flip);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLRotateSurface)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL;
	double angle;
	zval *surface_param = NULL, *angle_param = NULL, _4, _0$$3, _1$$3, _2$$3;
	zend_long surface, ZEPHIR_LAST_CALL_STATUS, surf_ptr = 0;

	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_ZVAL(angle)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &surface_param, &angle_param);
	angle = zephir_get_doubleval(angle_param);
	
            SDL_Surface *src  = (SDL_Surface *)(uintptr_t) surface;
            SDL_Surface *surf = SDL_RotateSurface(src, (float) angle);
            surf_ptr = surf ? (zend_long)(uintptr_t) surf : 0;
        
	if (surf_ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_RotateSurface failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/surface/sdlsurface.zep", 999);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_4, surf_ptr);
	ZEPHIR_RETURN_CALL_SELF("packsurfacefromptr", &_3, 4, &_4);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLScaleSurface)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL;
	zval *surface_param = NULL, *width_param = NULL, *height_param = NULL, *scaleMode_param = NULL, _4, _0$$3, _1$$3, _2$$3;
	zend_long surface, width, height, scaleMode, ZEPHIR_LAST_CALL_STATUS, surf_ptr = 0;

	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(scaleMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &surface_param, &width_param, &height_param, &scaleMode_param);
	
            SDL_Surface *src  = (SDL_Surface *)(uintptr_t) surface;
            SDL_Surface *surf = SDL_ScaleSurface(src, (int) width, (int) height, (SDL_ScaleMode) scaleMode);
            surf_ptr = surf ? (zend_long)(uintptr_t) surf : 0;
        
	if (surf_ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_ScaleSurface failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/surface/sdlsurface.zep", 1016);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_4, surf_ptr);
	ZEPHIR_RETURN_CALL_SELF("packsurfacefromptr", &_3, 4, &_4);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLConvertSurfaceAndColorspace)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL;
	zval *surface_param = NULL, *format_param = NULL, *palette = NULL, palette_sub, *colorspace_param = NULL, *props_param = NULL, __$null, _4, _0$$3, _1$$3, _2$$3;
	zend_long surface, format, colorspace, props, ZEPHIR_LAST_CALL_STATUS, surf_ptr = 0;

	ZVAL_UNDEF(&palette_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 5)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(format)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(palette)
		Z_PARAM_LONG(colorspace)
		Z_PARAM_LONG(props)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 3, &surface_param, &format_param, &palette, &colorspace_param, &props_param);
	if (!palette) {
		palette = &palette_sub;
		palette = &__$null;
	}
	if (!colorspace_param) {
		colorspace = 0;
	} else {
		}
	if (!props_param) {
		props = 0;
	} else {
		}
	
            SDL_Surface *src = (SDL_Surface *)(uintptr_t) surface;
            SDL_Palette *pal = (Z_TYPE_P(palette) == IS_NULL) ? NULL : (SDL_Palette *)(uintptr_t)(zend_long)Z_LVAL_P(palette);
            SDL_Surface *surf = SDL_ConvertSurfaceAndColorspace(
                src,
                (SDL_PixelFormat) format,
                pal,
                (SDL_Colorspace) colorspace,
                (SDL_PropertiesID) props
            );
            surf_ptr = surf ? (zend_long)(uintptr_t) surf : 0;
        
	if (surf_ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_ConvertSurfaceAndColorspace failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/surface/sdlsurface.zep", 1040);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_4, surf_ptr);
	ZEPHIR_RETURN_CALL_SELF("packsurfacefromptr", &_3, 4, &_4);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLConvertPixels)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval src, result;
	zval *width_param = NULL, *height_param = NULL, *src_format_param = NULL, *src_param = NULL, *src_pitch_param = NULL, *dst_format_param = NULL, *dst_pitch_param = NULL;
	zend_long width, height, src_format, src_pitch, dst_format, dst_pitch;

	ZVAL_UNDEF(&src);
	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(src_format)
		Z_PARAM_STR(src)
		Z_PARAM_LONG(src_pitch)
		Z_PARAM_LONG(dst_format)
		Z_PARAM_LONG(dst_pitch)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 7, 0, &width_param, &height_param, &src_format_param, &src_param, &src_pitch_param, &dst_format_param, &dst_pitch_param);
	zephir_get_strval(&src, src_param);
	ZEPHIR_INIT_VAR(&result);
	
            size_t dst_size = (size_t) dst_pitch * (size_t) height;
            void *dst_buf = emalloc(dst_size);
            bool ok = SDL_ConvertPixels(
                (int) width,
                (int) height,
                (SDL_PixelFormat) src_format,
                (const void *) Z_STRVAL_P(&src),
                (int) src_pitch,
                (SDL_PixelFormat) dst_format,
                dst_buf,
                (int) dst_pitch
            );
            if (ok) {
                ZVAL_STRINGL(&result, (char *) dst_buf, dst_size);
            }
            efree(dst_buf);
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLConvertPixelsAndColorspace)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval src, result;
	zval *width_param = NULL, *height_param = NULL, *src_format_param = NULL, *src_colorspace_param = NULL, *src_properties_param = NULL, *src_param = NULL, *src_pitch_param = NULL, *dst_format_param = NULL, *dst_colorspace_param = NULL, *dst_properties_param = NULL, *dst_pitch_param = NULL;
	zend_long width, height, src_format, src_colorspace, src_properties, src_pitch, dst_format, dst_colorspace, dst_properties, dst_pitch;

	ZVAL_UNDEF(&src);
	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(11, 11)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(src_format)
		Z_PARAM_LONG(src_colorspace)
		Z_PARAM_LONG(src_properties)
		Z_PARAM_STR(src)
		Z_PARAM_LONG(src_pitch)
		Z_PARAM_LONG(dst_format)
		Z_PARAM_LONG(dst_colorspace)
		Z_PARAM_LONG(dst_properties)
		Z_PARAM_LONG(dst_pitch)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 11, 0, &width_param, &height_param, &src_format_param, &src_colorspace_param, &src_properties_param, &src_param, &src_pitch_param, &dst_format_param, &dst_colorspace_param, &dst_properties_param, &dst_pitch_param);
	zephir_get_strval(&src, src_param);
	ZEPHIR_INIT_VAR(&result);
	
            size_t dst_size = (size_t) dst_pitch * (size_t) height;
            void *dst_buf = emalloc(dst_size);
            bool ok = SDL_ConvertPixelsAndColorspace(
                (int) width,
                (int) height,
                (SDL_PixelFormat) src_format,
                (SDL_Colorspace) src_colorspace,
                (SDL_PropertiesID) src_properties,
                (const void *) Z_STRVAL_P(&src),
                (int) src_pitch,
                (SDL_PixelFormat) dst_format,
                (SDL_Colorspace) dst_colorspace,
                (SDL_PropertiesID) dst_properties,
                dst_buf,
                (int) dst_pitch
            );
            if (ok) {
                ZVAL_STRINGL(&result, (char *) dst_buf, dst_size);
            }
            efree(dst_buf);
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLPremultiplyAlpha)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool linear;
	zval src, result;
	zval *width_param = NULL, *height_param = NULL, *src_format_param = NULL, *src_param = NULL, *src_pitch_param = NULL, *dst_format_param = NULL, *dst_pitch_param = NULL, *linear_param = NULL;
	zend_long width, height, src_format, src_pitch, dst_format, dst_pitch;

	ZVAL_UNDEF(&src);
	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(8, 8)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(src_format)
		Z_PARAM_STR(src)
		Z_PARAM_LONG(src_pitch)
		Z_PARAM_LONG(dst_format)
		Z_PARAM_LONG(dst_pitch)
		Z_PARAM_BOOL(linear)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 8, 0, &width_param, &height_param, &src_format_param, &src_param, &src_pitch_param, &dst_format_param, &dst_pitch_param, &linear_param);
	zephir_get_strval(&src, src_param);
	ZEPHIR_INIT_VAR(&result);
	
            size_t dst_size = (size_t) dst_pitch * (size_t) height;
            void *dst_buf = emalloc(dst_size);
            bool ok = SDL_PremultiplyAlpha(
                (int) width,
                (int) height,
                (SDL_PixelFormat) src_format,
                (const void *) Z_STRVAL_P(&src),
                (int) src_pitch,
                (SDL_PixelFormat) dst_format,
                dst_buf,
                (int) dst_pitch,
                (bool) linear
            );
            if (ok) {
                ZVAL_STRINGL(&result, (char *) dst_buf, dst_size);
            }
            efree(dst_buf);
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLPremultiplySurfaceAlpha)
{
	zend_bool linear, result = 0;
	zval *surface_param = NULL, *linear_param = NULL;
	zend_long surface;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(surface)
		Z_PARAM_BOOL(linear)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &surface_param, &linear_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_PremultiplySurfaceAlpha(surf, (bool) linear);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLClearSurface)
{
	zend_bool result = 0;
	double r, g, b, a;
	zval *surface_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL, *a_param = NULL;
	zend_long surface;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(surface)
		Z_PARAM_ZVAL(r)
		Z_PARAM_ZVAL(g)
		Z_PARAM_ZVAL(b)
		Z_PARAM_ZVAL(a)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &surface_param, &r_param, &g_param, &b_param, &a_param);
	r = zephir_get_doubleval(r_param);
	g = zephir_get_doubleval(g_param);
	b = zephir_get_doubleval(b_param);
	a = zephir_get_doubleval(a_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_ClearSurface(surf, (float) r, (float) g, (float) b, (float) a);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLFillSurfaceRects)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval rects;
	zval *dst_param = NULL, *rects_param = NULL, *color_param = NULL;
	zend_long dst, color;

	ZVAL_UNDEF(&rects);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(dst)
		Z_PARAM_ARRAY(rects)
		Z_PARAM_LONG(color)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &dst_param, &rects_param, &color_param);
	zephir_get_arrval(&rects, rects_param);
	
            SDL_Surface *dst_surf = (SDL_Surface *)(uintptr_t) dst;
            zend_ulong num = zend_hash_num_elements(Z_ARRVAL_P(&rects));
            SDL_Rect *rect_array = NULL;
            int count = 0;

            if (num > 0) {
                rect_array = (SDL_Rect *) emalloc(sizeof(SDL_Rect) * num);
                zval *entry;
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rects), entry) {
                    if (Z_TYPE_P(entry) == IS_ARRAY) {
                        zval *x = zend_hash_index_find(Z_ARRVAL_P(entry), 0);
                        zval *y = zend_hash_index_find(Z_ARRVAL_P(entry), 1);
                        zval *w = zend_hash_index_find(Z_ARRVAL_P(entry), 2);
                        zval *h = zend_hash_index_find(Z_ARRVAL_P(entry), 3);
                        if (x && y && w && h) {
                            rect_array[count].x = (int) zval_get_long(x);
                            rect_array[count].y = (int) zval_get_long(y);
                            rect_array[count].w = (int) zval_get_long(w);
                            rect_array[count].h = (int) zval_get_long(h);
                            count++;
                        }
                    }
                } ZEND_HASH_FOREACH_END();
            }

            result = SDL_FillSurfaceRects(dst_surf, rect_array, count, (Uint32) color);
            if (rect_array) {
                efree(rect_array);
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceUnchecked)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval srcrect, dstrect;
	zval *src_param = NULL, *srcrect_param = NULL, *dst_param = NULL, *dstrect_param = NULL;
	zend_long src, dst;

	ZVAL_UNDEF(&srcrect);
	ZVAL_UNDEF(&dstrect);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(src)
		Z_PARAM_ARRAY(srcrect)
		Z_PARAM_LONG(dst)
		Z_PARAM_ARRAY(dstrect)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &src_param, &srcrect_param, &dst_param, &dstrect_param);
	zephir_get_arrval(&srcrect, srcrect_param);
	zephir_get_arrval(&dstrect, dstrect_param);
	
            SDL_Surface *src_surf = (SDL_Surface *)(uintptr_t) src;
            SDL_Surface *dst_surf = (SDL_Surface *)(uintptr_t) dst;
            SDL_Rect src_buf = {0}, dst_buf = {0};
            const SDL_Rect *src_ptr = sdl3_rect_from_zval(&srcrect, &src_buf);
            const SDL_Rect *dst_ptr = sdl3_rect_from_zval(&dstrect, &dst_buf);
            if (src_ptr && dst_ptr) {
                result = SDL_BlitSurfaceUnchecked(src_surf, src_ptr, dst_surf, dst_ptr);
            } else {
                result = 0;
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceScaled)
{
	zend_bool result = 0;
	zval *src_param = NULL, *dst_param = NULL, *srcrect = NULL, srcrect_sub, *dstrect = NULL, dstrect_sub, *scaleMode_param = NULL, __$null;
	zend_long src, dst, scaleMode;

	ZVAL_UNDEF(&srcrect_sub);
	ZVAL_UNDEF(&dstrect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 5)
		Z_PARAM_LONG(src)
		Z_PARAM_LONG(dst)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(srcrect)
		Z_PARAM_ZVAL_OR_NULL(dstrect)
		Z_PARAM_LONG(scaleMode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 3, &src_param, &dst_param, &srcrect, &dstrect, &scaleMode_param);
	if (!srcrect) {
		srcrect = &srcrect_sub;
		srcrect = &__$null;
	}
	if (!dstrect) {
		dstrect = &dstrect_sub;
		dstrect = &__$null;
	}
	if (!scaleMode_param) {
		scaleMode = 0;
	} else {
		}
	
            SDL_Surface *src_surf = (SDL_Surface *)(uintptr_t) src;
            SDL_Surface *dst_surf = (SDL_Surface *)(uintptr_t) dst;
            SDL_Rect src_buf = {0}, dst_buf = {0};
            const SDL_Rect *src_ptr = sdl3_rect_from_zval(srcrect, &src_buf);
            const SDL_Rect *dst_ptr = sdl3_rect_from_zval(dstrect, &dst_buf);
            result = SDL_BlitSurfaceScaled(src_surf, src_ptr, dst_surf, dst_ptr, (SDL_ScaleMode) scaleMode);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceUncheckedScaled)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval srcrect, dstrect;
	zval *src_param = NULL, *srcrect_param = NULL, *dst_param = NULL, *dstrect_param = NULL, *scaleMode_param = NULL;
	zend_long src, dst, scaleMode;

	ZVAL_UNDEF(&srcrect);
	ZVAL_UNDEF(&dstrect);
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(src)
		Z_PARAM_ARRAY(srcrect)
		Z_PARAM_LONG(dst)
		Z_PARAM_ARRAY(dstrect)
		Z_PARAM_LONG(scaleMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 5, 0, &src_param, &srcrect_param, &dst_param, &dstrect_param, &scaleMode_param);
	zephir_get_arrval(&srcrect, srcrect_param);
	zephir_get_arrval(&dstrect, dstrect_param);
	
            SDL_Surface *src_surf = (SDL_Surface *)(uintptr_t) src;
            SDL_Surface *dst_surf = (SDL_Surface *)(uintptr_t) dst;
            SDL_Rect src_buf = {0}, dst_buf = {0};
            const SDL_Rect *src_ptr = sdl3_rect_from_zval(&srcrect, &src_buf);
            const SDL_Rect *dst_ptr = sdl3_rect_from_zval(&dstrect, &dst_buf);
            if (src_ptr && dst_ptr) {
                result = SDL_BlitSurfaceUncheckedScaled(src_surf, src_ptr, dst_surf, dst_ptr, (SDL_ScaleMode) scaleMode);
            } else {
                result = 0;
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLStretchSurface)
{
	zend_bool result = 0;
	zval *src_param = NULL, *dst_param = NULL, *srcrect = NULL, srcrect_sub, *dstrect = NULL, dstrect_sub, *scaleMode_param = NULL, __$null;
	zend_long src, dst, scaleMode;

	ZVAL_UNDEF(&srcrect_sub);
	ZVAL_UNDEF(&dstrect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 5)
		Z_PARAM_LONG(src)
		Z_PARAM_LONG(dst)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(srcrect)
		Z_PARAM_ZVAL_OR_NULL(dstrect)
		Z_PARAM_LONG(scaleMode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 3, &src_param, &dst_param, &srcrect, &dstrect, &scaleMode_param);
	if (!srcrect) {
		srcrect = &srcrect_sub;
		srcrect = &__$null;
	}
	if (!dstrect) {
		dstrect = &dstrect_sub;
		dstrect = &__$null;
	}
	if (!scaleMode_param) {
		scaleMode = 0;
	} else {
		}
	
            SDL_Surface *src_surf = (SDL_Surface *)(uintptr_t) src;
            SDL_Surface *dst_surf = (SDL_Surface *)(uintptr_t) dst;
            SDL_Rect src_buf = {0}, dst_buf = {0};
            const SDL_Rect *src_ptr = sdl3_rect_from_zval(srcrect, &src_buf);
            const SDL_Rect *dst_ptr = sdl3_rect_from_zval(dstrect, &dst_buf);
            result = SDL_StretchSurface(src_surf, src_ptr, dst_surf, dst_ptr, (SDL_ScaleMode) scaleMode);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceTiled)
{
	zend_bool result = 0;
	zval *src_param = NULL, *dst_param = NULL, *srcrect = NULL, srcrect_sub, *dstrect = NULL, dstrect_sub, __$null;
	zend_long src, dst;

	ZVAL_UNDEF(&srcrect_sub);
	ZVAL_UNDEF(&dstrect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_LONG(src)
		Z_PARAM_LONG(dst)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(srcrect)
		Z_PARAM_ZVAL_OR_NULL(dstrect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 2, &src_param, &dst_param, &srcrect, &dstrect);
	if (!srcrect) {
		srcrect = &srcrect_sub;
		srcrect = &__$null;
	}
	if (!dstrect) {
		dstrect = &dstrect_sub;
		dstrect = &__$null;
	}
	
            SDL_Surface *src_surf = (SDL_Surface *)(uintptr_t) src;
            SDL_Surface *dst_surf = (SDL_Surface *)(uintptr_t) dst;
            SDL_Rect src_buf = {0}, dst_buf = {0};
            const SDL_Rect *src_ptr = sdl3_rect_from_zval(srcrect, &src_buf);
            const SDL_Rect *dst_ptr = sdl3_rect_from_zval(dstrect, &dst_buf);
            result = SDL_BlitSurfaceTiled(src_surf, src_ptr, dst_surf, dst_ptr);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceTiledWithScale)
{
	zend_bool result = 0;
	double scale;
	zval *src_param = NULL, *dst_param = NULL, *scale_param = NULL, *scaleMode_param = NULL, *srcrect = NULL, srcrect_sub, *dstrect = NULL, dstrect_sub, __$null;
	zend_long src, dst, scaleMode;

	ZVAL_UNDEF(&srcrect_sub);
	ZVAL_UNDEF(&dstrect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(4, 6)
		Z_PARAM_LONG(src)
		Z_PARAM_LONG(dst)
		Z_PARAM_ZVAL(scale)
		Z_PARAM_LONG(scaleMode)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(srcrect)
		Z_PARAM_ZVAL_OR_NULL(dstrect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 2, &src_param, &dst_param, &scale_param, &scaleMode_param, &srcrect, &dstrect);
	scale = zephir_get_doubleval(scale_param);
	if (!srcrect) {
		srcrect = &srcrect_sub;
		srcrect = &__$null;
	}
	if (!dstrect) {
		dstrect = &dstrect_sub;
		dstrect = &__$null;
	}
	
            SDL_Surface *src_surf = (SDL_Surface *)(uintptr_t) src;
            SDL_Surface *dst_surf = (SDL_Surface *)(uintptr_t) dst;
            SDL_Rect src_buf = {0}, dst_buf = {0};
            const SDL_Rect *src_ptr = sdl3_rect_from_zval(srcrect, &src_buf);
            const SDL_Rect *dst_ptr = sdl3_rect_from_zval(dstrect, &dst_buf);
            result = SDL_BlitSurfaceTiledWithScale(src_surf, src_ptr, (float) scale, (SDL_ScaleMode) scaleMode, dst_surf, dst_ptr);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurface9Grid)
{
	zend_bool result = 0;
	double scale;
	zval *src_param = NULL, *dst_param = NULL, *left_width_param = NULL, *right_width_param = NULL, *top_height_param = NULL, *bottom_height_param = NULL, *scale_param = NULL, *scaleMode_param = NULL, *srcrect = NULL, srcrect_sub, *dstrect = NULL, dstrect_sub, __$null;
	zend_long src, dst, left_width, right_width, top_height, bottom_height, scaleMode;

	ZVAL_UNDEF(&srcrect_sub);
	ZVAL_UNDEF(&dstrect_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(8, 10)
		Z_PARAM_LONG(src)
		Z_PARAM_LONG(dst)
		Z_PARAM_LONG(left_width)
		Z_PARAM_LONG(right_width)
		Z_PARAM_LONG(top_height)
		Z_PARAM_LONG(bottom_height)
		Z_PARAM_ZVAL(scale)
		Z_PARAM_LONG(scaleMode)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(srcrect)
		Z_PARAM_ZVAL_OR_NULL(dstrect)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(8, 2, &src_param, &dst_param, &left_width_param, &right_width_param, &top_height_param, &bottom_height_param, &scale_param, &scaleMode_param, &srcrect, &dstrect);
	scale = zephir_get_doubleval(scale_param);
	if (!srcrect) {
		srcrect = &srcrect_sub;
		srcrect = &__$null;
	}
	if (!dstrect) {
		dstrect = &dstrect_sub;
		dstrect = &__$null;
	}
	
            SDL_Surface *src_surf = (SDL_Surface *)(uintptr_t) src;
            SDL_Surface *dst_surf = (SDL_Surface *)(uintptr_t) dst;
            SDL_Rect src_buf = {0}, dst_buf = {0};
            const SDL_Rect *src_ptr = sdl3_rect_from_zval(srcrect, &src_buf);
            const SDL_Rect *dst_ptr = sdl3_rect_from_zval(dstrect, &dst_buf);
            result = SDL_BlitSurface9Grid(
                src_surf, src_ptr,
                (int) left_width, (int) right_width, (int) top_height, (int) bottom_height,
                (float) scale, (SDL_ScaleMode) scaleMode,
                dst_surf, dst_ptr
            );
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLMapSurfaceRGB)
{
	zval *surface_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL;
	zend_long surface, r, g, b, result = 0;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &surface_param, &r_param, &g_param, &b_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = (zend_long) SDL_MapSurfaceRGB(surf, (Uint8) r, (Uint8) g, (Uint8) b);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLMapSurfaceRGBA)
{
	zval *surface_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL, *a_param = NULL;
	zend_long surface, r, g, b, a, result = 0;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
		Z_PARAM_LONG(a)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &surface_param, &r_param, &g_param, &b_param, &a_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = (zend_long) SDL_MapSurfaceRGBA(surf, (Uint8) r, (Uint8) g, (Uint8) b, (Uint8) a);
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLReadSurfacePixel)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *surface_param = NULL, *x_param = NULL, *y_param = NULL, _0;
	zend_long surface, x, y, r = 0, g = 0, b = 0, a = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &surface_param, &x_param, &y_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            Uint8 rr = 0, gg = 0, bb = 0, aa = 0;
            result = SDL_ReadSurfacePixel(surf, (int) x, (int) y, &rr, &gg, &bb, &aa);
            r = (zend_long) rr;
            g = (zend_long) gg;
            b = (zend_long) bb;
            a = (zend_long) aa;
        
	zephir_create_array(return_value, 5, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_BOOL(&_0, result);
	zephir_array_update_string(return_value, SL("result"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
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

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLReadSurfacePixelFloat)
{
	zend_bool result = 0;
	double r = 0, g = 0, b = 0, a = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *surface_param = NULL, *x_param = NULL, *y_param = NULL, _0;
	zend_long surface, x, y;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &surface_param, &x_param, &y_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            float rr = 0.0f, gg = 0.0f, bb = 0.0f, aa = 0.0f;
            result = SDL_ReadSurfacePixelFloat(surf, (int) x, (int) y, &rr, &gg, &bb, &aa);
            r = (double) rr;
            g = (double) gg;
            b = (double) bb;
            a = (double) aa;
        
	zephir_create_array(return_value, 5, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_BOOL(&_0, result);
	zephir_array_update_string(return_value, SL("result"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
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

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLWriteSurfacePixel)
{
	zend_bool result = 0;
	zval *surface_param = NULL, *x_param = NULL, *y_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL, *a_param = NULL;
	zend_long surface, x, y, r, g, b, a;

	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
		Z_PARAM_LONG(a)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(7, 0, &surface_param, &x_param, &y_param, &r_param, &g_param, &b_param, &a_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_WriteSurfacePixel(surf, (int) x, (int) y, (Uint8) r, (Uint8) g, (Uint8) b, (Uint8) a);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLWriteSurfacePixelFloat)
{
	zend_bool result = 0;
	double r, g, b, a;
	zval *surface_param = NULL, *x_param = NULL, *y_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL, *a_param = NULL;
	zend_long surface, x, y;

	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_ZVAL(r)
		Z_PARAM_ZVAL(g)
		Z_PARAM_ZVAL(b)
		Z_PARAM_ZVAL(a)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(7, 0, &surface_param, &x_param, &y_param, &r_param, &g_param, &b_param, &a_param);
	r = zephir_get_doubleval(r_param);
	g = zephir_get_doubleval(g_param);
	b = zephir_get_doubleval(b_param);
	a = zephir_get_doubleval(a_param);
	
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_WriteSurfacePixelFloat(surf, (int) x, (int) y, (float) r, (float) g, (float) b, (float) a);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLCreatePalette)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL;
	zval *ncolors_param = NULL, _4, _0$$3, _1$$3, _2$$3;
	zend_long ncolors, ZEPHIR_LAST_CALL_STATUS, pal_ptr = 0;

	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(ncolors)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &ncolors_param);
	
            SDL_Palette *pal = SDL_CreatePalette((int) ncolors);
            pal_ptr = pal ? (zend_long)(uintptr_t) pal : 0;
        
	if (pal_ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreatePalette failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/surface/sdlsurface.zep", 1417);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_4, pal_ptr);
	ZEPHIR_RETURN_CALL_SELF("packpalettefromptr", &_3, 5, &_4);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLDestroyPalette)
{
	zval *palette_param = NULL;
	zend_long palette;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(palette)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &palette_param);
	
            SDL_Palette *pal = (SDL_Palette *)(uintptr_t) palette;
            SDL_DestroyPalette(pal);
        
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetPaletteColors)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval colors;
	zval *palette_param = NULL, *colors_param = NULL, *firstcolor_param = NULL, *ncolors_param = NULL;
	zend_long palette, firstcolor, ncolors;

	ZVAL_UNDEF(&colors);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(palette)
		Z_PARAM_ARRAY(colors)
		Z_PARAM_LONG(firstcolor)
		Z_PARAM_LONG(ncolors)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &palette_param, &colors_param, &firstcolor_param, &ncolors_param);
	zephir_get_arrval(&colors, colors_param);
	
            SDL_Palette *pal = (SDL_Palette *)(uintptr_t) palette;
            SDL_Color *color_array = (SDL_Color *) emalloc(sizeof(SDL_Color) * ncolors);
            zval *entry;
            int idx = 0;
            ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&colors), entry) {
                if (idx >= ncolors) {
                    break;
                }
                if (Z_TYPE_P(entry) == IS_ARRAY) {
                    zval *rv = zend_hash_str_find(Z_ARRVAL_P(entry), "r", 1);
                    zval *gv = zend_hash_str_find(Z_ARRVAL_P(entry), "g", 1);
                    zval *bv = zend_hash_str_find(Z_ARRVAL_P(entry), "b", 1);
                    zval *av = zend_hash_str_find(Z_ARRVAL_P(entry), "a", 1);
                    color_array[idx].r = rv ? (Uint8) zval_get_long(rv) : 0;
                    color_array[idx].g = gv ? (Uint8) zval_get_long(gv) : 0;
                    color_array[idx].b = bv ? (Uint8) zval_get_long(bv) : 0;
                    color_array[idx].a = av ? (Uint8) zval_get_long(av) : 255;
                } else {
                    color_array[idx].r = 0;
                    color_array[idx].g = 0;
                    color_array[idx].b = 0;
                    color_array[idx].a = 255;
                }
                idx++;
            } ZEND_HASH_FOREACH_END();

            result = SDL_SetPaletteColors(pal, color_array, (int) firstcolor, (int) ncolors);
            efree(color_array);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetPixelFormatName)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *format_param = NULL;
	zend_long format;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &format_param);
	ZEPHIR_INIT_VAR(&result);
	
            const char *name = SDL_GetPixelFormatName((SDL_PixelFormat) format);
            if (name) {
                ZVAL_STRING(&result, name);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetMasksForPixelFormat)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *format_param = NULL, _0;
	zend_long format, bpp = 0, rmask = 0, gmask = 0, bmask = 0, amask = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &format_param);
	
            int b = 0;
            Uint32 rm = 0, gm = 0, bm = 0, am = 0;
            result = SDL_GetMasksForPixelFormat((SDL_PixelFormat) format, &b, &rm, &gm, &bm, &am);
            bpp = (zend_long) b;
            rmask = (zend_long) rm;
            gmask = (zend_long) gm;
            bmask = (zend_long) bm;
            amask = (zend_long) am;
        
	zephir_create_array(return_value, 6, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_BOOL(&_0, result);
	zephir_array_update_string(return_value, SL("result"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, bpp);
	zephir_array_update_string(return_value, SL("bpp"), &_0, PH_COPY | PH_SEPARATE);
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
	RETURN_MM();
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetPixelFormatForMasks)
{
	zval *bpp_param = NULL, *rmask_param = NULL, *gmask_param = NULL, *bmask_param = NULL, *amask_param = NULL;
	zend_long bpp, rmask, gmask, bmask, amask, result = 0;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(bpp)
		Z_PARAM_LONG(rmask)
		Z_PARAM_LONG(gmask)
		Z_PARAM_LONG(bmask)
		Z_PARAM_LONG(amask)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &bpp_param, &rmask_param, &gmask_param, &bmask_param, &amask_param);
	
            result = (zend_long) SDL_GetPixelFormatForMasks(
                (int) bpp,
                (Uint32) rmask,
                (Uint32) gmask,
                (Uint32) bmask,
                (Uint32) amask
            );
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetRGB)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *pixel_param = NULL, *format_ptr_param = NULL, *palette_ptr = NULL, palette_ptr_sub, __$null, _0;
	zend_long pixel, format_ptr, r = 0, g = 0, b = 0;

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
            Uint8 cr = 0, cg = 0, cb = 0;
            SDL_GetRGB((Uint32) pixel, fmt, pal, &cr, &cg, &cb);
            r = (zend_long) cr;
            g = (zend_long) cg;
            b = (zend_long) cb;
        
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

