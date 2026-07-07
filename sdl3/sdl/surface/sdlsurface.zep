namespace Sdl3\SDL\Surface;

%{
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
}%

class SDLSurface
{
    public static function SDLCreateSurface(int width, int height, int format) -> array
    {
        int ptr;
        int flags;
        int fmt;
        int w;
        int h;
        int pitch;
        int pixels_ptr;
        array pixels_data;
        int refcount;

        %{
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
        }%

        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "flags": flags, "format": fmt, "w": w, "h": h, "pitch": pitch, "pixels": ["ptr": pixels_ptr, "data": pixels_data], "refcount": refcount];
    }

    public static function SDLDuplicateSurface(int surface) -> array
    {
        int ptr;
        int flags;
        int fmt;
        int w;
        int h;
        int pitch;
        int pixels_ptr;
        array pixels_data;
        int refcount;

        %{
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
        }%

        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "flags": flags, "format": fmt, "w": w, "h": h, "pitch": pitch, "pixels": ["ptr": pixels_ptr, "data": pixels_data], "refcount": refcount];
    }

    public static function SDLConvertSurface(int surface, int format) -> array
    {
        int ptr;
        int flags;
        int fmt;
        int w;
        int h;
        int pitch;
        int pixels_ptr;
        array pixels_data;
        int refcount;

        %{
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
        }%

        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "flags": flags, "format": fmt, "w": w, "h": h, "pitch": pitch, "pixels": ["ptr": pixels_ptr, "data": pixels_data], "refcount": refcount];
    }

    public static function SDLSurfaceToBlackAndWhite(int surface) -> void
    {
        %{
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
        }%
    }

    public static function SDLBlitSurface(int src, int dst, var srcrect = null, var dstrect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLFillSurfaceRect(int surface, int color, var rect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLMapRGB(int format, int palette, int r, int g, int b) -> int
    {
        int result;

        %{
            const SDL_PixelFormatDetails *fmt = (const SDL_PixelFormatDetails *)(uintptr_t) format;
            const SDL_Palette            *pal = palette ? (const SDL_Palette *)(uintptr_t) palette : NULL;
            result = (zend_long) SDL_MapRGB(fmt, pal, (Uint8) r, (Uint8) g, (Uint8) b);
        }%

        return result;
    }

    public static function SDLLockSurface(int surface) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_LockSurface(surf);
        }%

        return result;
    }

    public static function SDLUnlockSurface(int surface) -> void
    {
        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_UnlockSurface(surf);
        }%
    }

    public static function SDLDestroySurface(int surface) -> void
    {
        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_DestroySurface(surf);
        }%
    }

    public static function SDLLoadPNG(string file) -> array
    {
        int ptr;
        int flags;
        int format;
        int w;
        int h;
        int pitch;
        int pixels_ptr;
        array pixels_data;
        int refcount;

        %{
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
        }%

        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "flags": flags, "format": format, "w": w, "h": h, "pitch": pitch, "pixels": ["ptr": pixels_ptr, "data": pixels_data], "refcount": refcount];
    }

    public static function SDLLoadBMP(string file) -> array
    {
        int ptr;
        int flags;
        int format;
        int w;
        int h;
        int pitch;
        int pixels_ptr;
        array pixels_data;
        int refcount;

        %{
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
        }%

        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "flags": flags, "format": format, "w": w, "h": h, "pitch": pitch, "pixels": ["ptr": pixels_ptr, "data": pixels_data], "refcount": refcount];
    }

    public static function SDLWriteSurfacePixelAt(int surface, int x, int y, int pixel) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            if (!surf || !surf->pixels || x < 0 || y < 0 || x >= surf->w || y >= surf->h) {
                result = 0;
            } else {
                Uint32 *row = (Uint32 *)(((Uint8 *)surf->pixels) + y * surf->pitch);
                row[x] = (Uint32)(zend_ulong)pixel;
                result = 1;
            }
        }%

        return result;
    }

    public static function SDLWriteSurfacePixels(int surface, array data) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLReadSurfacePixels(int surface) -> array
    {
        int pixels_ptr;
        array pixels_data;

        %{
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
        }%

        return ["pixels_ptr": pixels_ptr, "pixels_data": pixels_data];
    }

    public static function SDLGetSurfacePalette(int surface) -> array
    {
        int ptr;
        int ncolors;
        int version;
        int refcount;
        array colors;

        %{
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
        }%

        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "ncolors": ncolors, "colors": colors, "version": version, "refcount": refcount];
    }

    private static function buildSurfaceArray(int ptr, int flags, int fmt, int w, int h, int pitch, int pixels_ptr, array pixels_data, int refcount) -> array
    {
        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "flags": flags, "format": fmt, "w": w, "h": h, "pitch": pitch, "pixels": ["ptr": pixels_ptr, "data": pixels_data], "refcount": refcount];
    }

    private static function packSurfaceFromPtr(int surface) -> array
    {
        int ptr;
        int flags;
        int fmt;
        int w;
        int h;
        int pitch;
        int pixels_ptr;
        array pixels_data;
        int refcount;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            sdl3_read_surface_fields(surf, &ptr, &flags, &fmt, &w, &h, &pitch, &pixels_ptr, &refcount);
            sdl3_copy_surface_pixels(surf, &pixels_data);
        }%

        return self::buildSurfaceArray(ptr, flags, fmt, w, h, pitch, pixels_ptr, pixels_data, refcount);
    }

    private static function buildPaletteArray(int ptr, int ncolors, array colors, int version, int refcount) -> array
    {
        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "ncolors": ncolors, "colors": colors, "version": version, "refcount": refcount];
    }

    private static function packPaletteFromPtr(int palette) -> array
    {
        int ptr;
        int ncolors;
        int version;
        int refcount;
        array colors;

        %{
            SDL_Palette *pal = (SDL_Palette *)(uintptr_t) palette;
            sdl3_read_palette_fields(pal, &ptr, &ncolors, &version, &refcount, &colors);
        }%

        return self::buildPaletteArray(ptr, ncolors, colors, version, refcount);
    }

    public static function SDLCreateSurfaceFrom(int width, int height, int format, string pixels, int pitch) -> array
    {
        int surf_ptr;

        %{
            SDL_Surface *surf = SDL_CreateSurfaceFrom(
                (int) width,
                (int) height,
                (SDL_PixelFormat) format,
                (void *) Z_STRVAL_P(&pixels),
                (int) pitch
            );
            surf_ptr = surf ? (zend_long)(uintptr_t) surf : 0;
        }%

        if surf_ptr == 0 {
            throw new \RuntimeException("SDL_CreateSurfaceFrom failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return self::packSurfaceFromPtr(surf_ptr);
    }

    public static function SDLGetSurfaceProperties(int surface) -> int
    {
        int result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = (zend_long) SDL_GetSurfaceProperties(surf);
        }%

        return result;
    }

    public static function SDLSetSurfaceColorspace(int surface, int colorspace) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetSurfaceColorspace(surf, (SDL_Colorspace) colorspace);
        }%

        return result;
    }

    public static function SDLGetSurfaceColorspace(int surface) -> int
    {
        int result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = (zend_long) SDL_GetSurfaceColorspace(surf);
        }%

        return result;
    }

    public static function SDLCreateSurfacePalette(int surface) -> array
    {
        int pal_ptr;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_Palette *pal  = SDL_CreateSurfacePalette(surf);
            pal_ptr = pal ? (zend_long)(uintptr_t) pal : 0;
        }%

        if pal_ptr == 0 {
            throw new \RuntimeException("SDL_CreateSurfacePalette failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return self::packPaletteFromPtr(pal_ptr);
    }

    public static function SDLSetSurfacePalette(int surface, int palette) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_Palette *pal  = (SDL_Palette *)(uintptr_t) palette;
            result = SDL_SetSurfacePalette(surf, pal);
        }%

        return result;
    }

    public static function SDLAddSurfaceAlternateImage(int surface, int image) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_Surface *img  = (SDL_Surface *)(uintptr_t) image;
            result = SDL_AddSurfaceAlternateImage(surf, img);
        }%

        return result;
    }

    public static function SDLSurfaceHasAlternateImages(int surface) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SurfaceHasAlternateImages(surf);
        }%

        return result;
    }

    public static function SDLGetSurfaceImages(int surface) -> array
    {
        int count;
        array images;

        %{
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
        }%

        return ["count": count, "images": images];
    }

    public static function SDLRemoveSurfaceAlternateImages(int surface) -> void
    {
        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_RemoveSurfaceAlternateImages(surf);
        }%
    }

    public static function SDLLoadSurface(string file) -> array
    {
        int surf_ptr;

        %{
            SDL_Surface *surf = SDL_LoadSurface(Z_STRVAL(file));
            surf_ptr = surf ? (zend_long)(uintptr_t) surf : 0;
        }%

        if surf_ptr == 0 {
            throw new \RuntimeException("SDL_LoadSurface failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return self::packSurfaceFromPtr(surf_ptr);
    }

    public static function SDLSaveBMP(int surface, string file) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SaveBMP(surf, Z_STRVAL(file));
        }%

        return result;
    }

    public static function SDLSavePNG(int surface, string file) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SavePNG(surf, Z_STRVAL(file));
        }%

        return result;
    }

    public static function SDLSetSurfaceRLE(int surface, bool enabled) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetSurfaceRLE(surf, (bool) enabled);
        }%

        return result;
    }

    public static function SDLSurfaceHasRLE(int surface) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SurfaceHasRLE(surf);
        }%

        return result;
    }

    public static function SDLSetSurfaceColorKey(int surface, bool enabled, int key) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetSurfaceColorKey(surf, (bool) enabled, (Uint32) key);
        }%

        return result;
    }

    public static function SDLSurfaceHasColorKey(int surface) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SurfaceHasColorKey(surf);
        }%

        return result;
    }

    public static function SDLGetSurfaceColorKey(int surface) -> array
    {
        int key;
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            Uint32 k = 0;
            result = SDL_GetSurfaceColorKey(surf, &k);
            key = (zend_long) k;
        }%

        return ["result": result, "key": key];
    }

    public static function SDLSetSurfaceColorMod(int surface, int r, int g, int b) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetSurfaceColorMod(surf, (Uint8) r, (Uint8) g, (Uint8) b);
        }%

        return result;
    }

    public static function SDLGetSurfaceColorMod(int surface) -> array
    {
        int r;
        int g;
        int b;
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            Uint8 rr = 0, gg = 0, bb = 0;
            result = SDL_GetSurfaceColorMod(surf, &rr, &gg, &bb);
            r = (zend_long) rr;
            g = (zend_long) gg;
            b = (zend_long) bb;
        }%

        return ["result": result, "r": r, "g": g, "b": b];
    }

    public static function SDLSetSurfaceAlphaMod(int surface, int alpha) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetSurfaceAlphaMod(surf, (Uint8) alpha);
        }%

        return result;
    }

    public static function SDLGetSurfaceAlphaMod(int surface) -> array
    {
        int alpha;
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            Uint8 a = 0;
            result = SDL_GetSurfaceAlphaMod(surf, &a);
            alpha = (zend_long) a;
        }%

        return ["result": result, "alpha": alpha];
    }

    public static function SDLSetSurfaceBlendMode(int surface, int blendMode) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_SetSurfaceBlendMode(surf, (SDL_BlendMode) blendMode);
        }%

        return result;
    }

    public static function SDLGetSurfaceBlendMode(int surface) -> array
    {
        int blendMode;
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_BlendMode mode = SDL_BLENDMODE_INVALID;
            result = SDL_GetSurfaceBlendMode(surf, &mode);
            blendMode = (zend_long) mode;
        }%

        return ["result": result, "blend_mode": blendMode];
    }

    public static function SDLSetSurfaceClipRect(int surface, var rect = null) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_Rect r_buf;
            const SDL_Rect *rp = sdl3_rect_from_zval(rect, &r_buf);
            result = SDL_SetSurfaceClipRect(surf, rp);
        }%

        return result;
    }

    public static function SDLGetSurfaceClipRect(int surface) -> array
    {
        int x;
        int y;
        int w;
        int h;
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            SDL_Rect r = {0, 0, 0, 0};
            result = SDL_GetSurfaceClipRect(surf, &r);
            x = (zend_long) r.x;
            y = (zend_long) r.y;
            w = (zend_long) r.w;
            h = (zend_long) r.h;
        }%

        return ["result": result, "x": x, "y": y, "w": w, "h": h];
    }

    public static function SDLFlipSurface(int surface, int flip) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_FlipSurface(surf, (SDL_FlipMode) flip);
        }%

        return result;
    }

    public static function SDLRotateSurface(int surface, double angle) -> array
    {
        int surf_ptr;

        %{
            SDL_Surface *src  = (SDL_Surface *)(uintptr_t) surface;
            SDL_Surface *surf = SDL_RotateSurface(src, (float) angle);
            surf_ptr = surf ? (zend_long)(uintptr_t) surf : 0;
        }%

        if surf_ptr == 0 {
            throw new \RuntimeException("SDL_RotateSurface failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return self::packSurfaceFromPtr(surf_ptr);
    }

    public static function SDLScaleSurface(int surface, int width, int height, int scaleMode) -> array
    {
        int surf_ptr;

        %{
            SDL_Surface *src  = (SDL_Surface *)(uintptr_t) surface;
            SDL_Surface *surf = SDL_ScaleSurface(src, (int) width, (int) height, (SDL_ScaleMode) scaleMode);
            surf_ptr = surf ? (zend_long)(uintptr_t) surf : 0;
        }%

        if surf_ptr == 0 {
            throw new \RuntimeException("SDL_ScaleSurface failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return self::packSurfaceFromPtr(surf_ptr);
    }

    public static function SDLConvertSurfaceAndColorspace(int surface, int format, var palette = null, int colorspace = 0, int props = 0) -> array
    {
        int surf_ptr;

        %{
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
        }%

        if surf_ptr == 0 {
            throw new \RuntimeException("SDL_ConvertSurfaceAndColorspace failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return self::packSurfaceFromPtr(surf_ptr);
    }

    public static function SDLConvertPixels(int width, int height, int src_format, string src, int src_pitch, int dst_format, int dst_pitch) -> string
    {
        string result = "";

        %{
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
        }%

        return result;
    }

    public static function SDLConvertPixelsAndColorspace(int width, int height, int src_format, int src_colorspace, int src_properties, string src, int src_pitch, int dst_format, int dst_colorspace, int dst_properties, int dst_pitch) -> string
    {
        string result = "";

        %{
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
        }%

        return result;
    }

    public static function SDLPremultiplyAlpha(int width, int height, int src_format, string src, int src_pitch, int dst_format, int dst_pitch, bool linear) -> string
    {
        string result = "";

        %{
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
        }%

        return result;
    }

    public static function SDLPremultiplySurfaceAlpha(int surface, bool linear) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_PremultiplySurfaceAlpha(surf, (bool) linear);
        }%

        return result;
    }

    public static function SDLClearSurface(int surface, double r, double g, double b, double a) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_ClearSurface(surf, (float) r, (float) g, (float) b, (float) a);
        }%

        return result;
    }

    public static function SDLFillSurfaceRects(int dst, array rects, int color) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLBlitSurfaceUnchecked(int src, array srcrect, int dst, array dstrect) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLBlitSurfaceScaled(int src, int dst, var srcrect = null, var dstrect = null, int scaleMode = 0) -> bool
    {
        bool result;

        %{
            SDL_Surface *src_surf = (SDL_Surface *)(uintptr_t) src;
            SDL_Surface *dst_surf = (SDL_Surface *)(uintptr_t) dst;
            SDL_Rect src_buf = {0}, dst_buf = {0};
            const SDL_Rect *src_ptr = sdl3_rect_from_zval(srcrect, &src_buf);
            const SDL_Rect *dst_ptr = sdl3_rect_from_zval(dstrect, &dst_buf);
            result = SDL_BlitSurfaceScaled(src_surf, src_ptr, dst_surf, dst_ptr, (SDL_ScaleMode) scaleMode);
        }%

        return result;
    }

    public static function SDLBlitSurfaceUncheckedScaled(int src, array srcrect, int dst, array dstrect, int scaleMode) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLStretchSurface(int src, int dst, var srcrect = null, var dstrect = null, int scaleMode = 0) -> bool
    {
        bool result;

        %{
            SDL_Surface *src_surf = (SDL_Surface *)(uintptr_t) src;
            SDL_Surface *dst_surf = (SDL_Surface *)(uintptr_t) dst;
            SDL_Rect src_buf = {0}, dst_buf = {0};
            const SDL_Rect *src_ptr = sdl3_rect_from_zval(srcrect, &src_buf);
            const SDL_Rect *dst_ptr = sdl3_rect_from_zval(dstrect, &dst_buf);
            result = SDL_StretchSurface(src_surf, src_ptr, dst_surf, dst_ptr, (SDL_ScaleMode) scaleMode);
        }%

        return result;
    }

    public static function SDLBlitSurfaceTiled(int src, int dst, var srcrect = null, var dstrect = null) -> bool
    {
        bool result;

        %{
            SDL_Surface *src_surf = (SDL_Surface *)(uintptr_t) src;
            SDL_Surface *dst_surf = (SDL_Surface *)(uintptr_t) dst;
            SDL_Rect src_buf = {0}, dst_buf = {0};
            const SDL_Rect *src_ptr = sdl3_rect_from_zval(srcrect, &src_buf);
            const SDL_Rect *dst_ptr = sdl3_rect_from_zval(dstrect, &dst_buf);
            result = SDL_BlitSurfaceTiled(src_surf, src_ptr, dst_surf, dst_ptr);
        }%

        return result;
    }

    public static function SDLBlitSurfaceTiledWithScale(int src, int dst, double scale, int scaleMode, var srcrect = null, var dstrect = null) -> bool
    {
        bool result;

        %{
            SDL_Surface *src_surf = (SDL_Surface *)(uintptr_t) src;
            SDL_Surface *dst_surf = (SDL_Surface *)(uintptr_t) dst;
            SDL_Rect src_buf = {0}, dst_buf = {0};
            const SDL_Rect *src_ptr = sdl3_rect_from_zval(srcrect, &src_buf);
            const SDL_Rect *dst_ptr = sdl3_rect_from_zval(dstrect, &dst_buf);
            result = SDL_BlitSurfaceTiledWithScale(src_surf, src_ptr, (float) scale, (SDL_ScaleMode) scaleMode, dst_surf, dst_ptr);
        }%

        return result;
    }

    public static function SDLBlitSurface9Grid(int src, int dst, int left_width, int right_width, int top_height, int bottom_height, double scale, int scaleMode, var srcrect = null, var dstrect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLMapSurfaceRGB(int surface, int r, int g, int b) -> int
    {
        int result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = (zend_long) SDL_MapSurfaceRGB(surf, (Uint8) r, (Uint8) g, (Uint8) b);
        }%

        return result;
    }

    public static function SDLMapSurfaceRGBA(int surface, int r, int g, int b, int a) -> int
    {
        int result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = (zend_long) SDL_MapSurfaceRGBA(surf, (Uint8) r, (Uint8) g, (Uint8) b, (Uint8) a);
        }%

        return result;
    }

    public static function SDLReadSurfacePixel(int surface, int x, int y) -> array
    {
        int r;
        int g;
        int b;
        int a;
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            Uint8 rr = 0, gg = 0, bb = 0, aa = 0;
            result = SDL_ReadSurfacePixel(surf, (int) x, (int) y, &rr, &gg, &bb, &aa);
            r = (zend_long) rr;
            g = (zend_long) gg;
            b = (zend_long) bb;
            a = (zend_long) aa;
        }%

        return ["result": result, "r": r, "g": g, "b": b, "a": a];
    }

    public static function SDLReadSurfacePixelFloat(int surface, int x, int y) -> array
    {
        double r;
        double g;
        double b;
        double a;
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            float rr = 0.0f, gg = 0.0f, bb = 0.0f, aa = 0.0f;
            result = SDL_ReadSurfacePixelFloat(surf, (int) x, (int) y, &rr, &gg, &bb, &aa);
            r = (double) rr;
            g = (double) gg;
            b = (double) bb;
            a = (double) aa;
        }%

        return ["result": result, "r": r, "g": g, "b": b, "a": a];
    }

    public static function SDLWriteSurfacePixel(int surface, int x, int y, int r, int g, int b, int a) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_WriteSurfacePixel(surf, (int) x, (int) y, (Uint8) r, (Uint8) g, (Uint8) b, (Uint8) a);
        }%

        return result;
    }

    public static function SDLWriteSurfacePixelFloat(int surface, int x, int y, double r, double g, double b, double a) -> bool
    {
        bool result;

        %{
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_WriteSurfacePixelFloat(surf, (int) x, (int) y, (float) r, (float) g, (float) b, (float) a);
        }%

        return result;
    }

    public static function SDLCreatePalette(int ncolors) -> array
    {
        int pal_ptr;

        %{
            SDL_Palette *pal = SDL_CreatePalette((int) ncolors);
            pal_ptr = pal ? (zend_long)(uintptr_t) pal : 0;
        }%

        if pal_ptr == 0 {
            throw new \RuntimeException("SDL_CreatePalette failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return self::packPaletteFromPtr(pal_ptr);
    }

    public static function SDLDestroyPalette(int palette) -> void
    {
        %{
            SDL_Palette *pal = (SDL_Palette *)(uintptr_t) palette;
            SDL_DestroyPalette(pal);
        }%
    }

    public static function SDLSetPaletteColors(int palette, array colors, int firstcolor, int ncolors) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLGetPixelFormatName(int format) -> string
    {
        string result = "";

        %{
            const char *name = SDL_GetPixelFormatName((SDL_PixelFormat) format);
            if (name) {
                ZVAL_STRING(&result, name);
            }
        }%

        return result;
    }

    public static function SDLGetMasksForPixelFormat(int format) -> array
    {
        int bpp;
        int rmask;
        int gmask;
        int bmask;
        int amask;
        bool result;

        %{
            int b = 0;
            Uint32 rm = 0, gm = 0, bm = 0, am = 0;
            result = SDL_GetMasksForPixelFormat((SDL_PixelFormat) format, &b, &rm, &gm, &bm, &am);
            bpp = (zend_long) b;
            rmask = (zend_long) rm;
            gmask = (zend_long) gm;
            bmask = (zend_long) bm;
            amask = (zend_long) am;
        }%

        return ["result": result, "bpp": bpp, "rmask": rmask, "gmask": gmask, "bmask": bmask, "amask": amask];
    }

    public static function SDLGetPixelFormatForMasks(int bpp, int rmask, int gmask, int bmask, int amask) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetPixelFormatForMasks(
                (int) bpp,
                (Uint32) rmask,
                (Uint32) gmask,
                (Uint32) bmask,
                (Uint32) amask
            );
        }%

        return result;
    }

    public static function SDLGetRGB(int pixel, int format_ptr, var palette_ptr = null) -> array
    {
        int r;
        int g;
        int b;

        %{
            const SDL_PixelFormatDetails *fmt = (const SDL_PixelFormatDetails *)(uintptr_t) format_ptr;
            const SDL_Palette *pal = (Z_TYPE_P(palette_ptr) == IS_NULL) ? NULL : (const SDL_Palette *)(uintptr_t)(zend_long)Z_LVAL_P(palette_ptr);
            Uint8 cr = 0, cg = 0, cb = 0;
            SDL_GetRGB((Uint32) pixel, fmt, pal, &cr, &cg, &cb);
            r = (zend_long) cr;
            g = (zend_long) cg;
            b = (zend_long) cb;
        }%

        return ["r": r, "g": g, "b": b];
    }
}
