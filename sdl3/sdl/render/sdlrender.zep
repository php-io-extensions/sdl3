namespace Sdl3\SDL\Render;

%{
#include <SDL3/SDL.h>
#include <stdio.h>
}%
class SDLRender
{
    public static function SDLCreateRenderer(int window, var name = null) -> int
    {
        int ptr;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            const char *renderer_name = (Z_TYPE_P(name) == IS_NULL) ? NULL : Z_STRVAL_P(name);
            SDL_Renderer *renderer = SDL_CreateRenderer(win, renderer_name);
            ptr = (zend_long)(uintptr_t) renderer;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateRenderer failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLCreateSoftwareRenderer(int surface) -> int
    {
        int ptr;

        %{
            SDL_Surface  *surf     = (SDL_Surface *)(uintptr_t) surface;
            SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surf);
            ptr = (zend_long)(uintptr_t) renderer;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateSoftwareRenderer failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLRenderClear(int renderer) -> void
    {
        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_RenderClear(ren);
        }%
    }

    public static function SDLRenderPresent(int renderer) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_RenderPresent(ren);
        }%

        return result;
    }

    public static function SDLRenderTexture(int renderer, int texture, var srcrect = null, var dstrect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLRenderTextureRotated(int renderer, int texture, double angle, int flip, var srcrect = null, var dstrect = null, var center = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLSetRenderDrawColor(int renderer, int r, int g, int b, int a) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderDrawColor(ren, r, g, b, a);
        }%

        return result;
    }

    public static function SDLSetRenderDrawColorFloat(int renderer, double r, double g, double b, double a) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderDrawColorFloat(ren, (float) r, (float) g, (float) b, (float) a);
        }%

        return result;
    }

    public static function SDLCreateTexture(int renderer, int format, int access, int w, int h) -> array
    {
        int ptr;
        int tex_format;
        int tex_w;
        int tex_h;

        %{
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
        }%

        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "format": tex_format, "w": tex_w, "h": tex_h, "refcount": 1];
    }

    public static function SDLCreateTextureFromSurface(int renderer, int surface) -> array
    {
        int ptr;
        int format;
        int w;
        int h;

        %{
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
        }%

        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "format": format, "w": w, "h": h, "refcount": 1];
    }

    public static function SDLLockTextureToSurface(int texture, var rect = null) -> array
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
        }%

        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "flags": flags, "format": fmt, "w": w, "h": h, "pitch": pitch, "pixels": ["ptr": pixels_ptr, "data": pixels_data], "refcount": refcount];
    }

    public static function SDLUnlockTexture(int texture) -> void
    {
        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            SDL_UnlockTexture(te);
        }%
    }

    public static function SDLSetTextureColorModFloat(int texture, double r, double g, double b) -> bool
    {
        bool result;

        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            result = SDL_SetTextureColorModFloat(te, (float) r, (float) g, (float) b);
        }%

        return result;
    }

    public static function SDLSetTextureScaleMode(int texture, int scaleMode) -> bool
    {
        bool result;

        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            result = SDL_SetTextureScaleMode(te, (SDL_ScaleMode) scaleMode);
        }%

        return result;
    }

    public static function SDLGetTextureSize(int texture) -> array
    {
        int w;
        int h;
        bool result;

        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            float fw = 0.0f, fh = 0.0f;
            result = SDL_GetTextureSize(te, &fw, &fh);
            w = (zend_long) fw;
            h = (zend_long) fh;
        }%

        if !result {
            return [];
        }

        return ["w": w, "h": h];
    }

    public static function SDLSetRenderLogicalPresentation(int renderer, int w, int h, int mode) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderLogicalPresentation(ren, (int) w, (int) h, (SDL_RendererLogicalPresentation) mode);
        }%

        return result;
    }

    public static function SDLDestroyRenderer(int renderer) -> void
    {
        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_DestroyRenderer(ren);
        }%
    }

    public static function SDLDestroyTexture(int texture) -> void
    {
        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            SDL_DestroyTexture(te);
        }%
    }

    public static function SDLRenderFillRect(int renderer, var rect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLSetRenderViewport(int renderer, var rect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLSetRenderClipRect(int renderer, var rect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLRenderReadPixels(int renderer, var rect = null) -> array
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
        }%

        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "flags": flags, "format": format, "w": w, "h": h, "pitch": pitch, "pixels": ["ptr": pixels_ptr, "data": pixels_data], "refcount": refcount];
    }

    public static function SDLUpdateTextureFromSurface(int texture, int surface) -> bool
    {
        bool result;

        %{
            SDL_Texture *tex  = (SDL_Texture *)(uintptr_t) texture;
            SDL_Surface *surf = (SDL_Surface *)(uintptr_t) surface;
            result = SDL_UpdateTexture(tex, NULL, surf->pixels, surf->pitch);
        }%

        return result;
    }

    public static function SDLRenderDebugText(int renderer, double x, double y, string str) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_RenderDebugText(ren, (float) x, (float) y, Z_STRVAL(str));
        }%

        return result;
    }

    public static function SDLSetRenderScale(int renderer, double scaleX, double scaleY) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderScale(ren, (float) scaleX, (float) scaleY);
        }%

        return result;
    }

    public static function SDLRenderTextureAffine(int renderer, int texture, var origin, var right, var down, var srcrect = null) -> bool
    {
        bool result;

        if typeof origin != "array" || typeof right != "array" || typeof down != "array" {
            return false;
        }

        %{
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
        }%

        return result;
    }

    public static function SDLRenderFillRects(int renderer, array rects, int count) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLRenderRects(int renderer, array rects, int count) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLRenderLine(int renderer, double x1, double y1, double x2, double y2) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_RenderLine(ren, (float) x1, (float) y1, (float) x2, (float) y2);
        }%

        return result;
    }

    public static function SDLRenderRect(int renderer, var rect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLRenderPoints(int renderer, array points, int count) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLRenderGeometry(int renderer, int texture, array vertices, int num_vertices, int num_indices, var indices = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLRenderLines(int renderer, array points, int count) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLGetNumRenderDrivers() -> int
    {
        int count;

        %{
            count = (zend_long) SDL_GetNumRenderDrivers();
        }%

        return count;
    }

    public static function SDLGetRenderDriver(int index) -> string
    {
        string name = "";

        %{
            const char *driver = SDL_GetRenderDriver((int) index);
            if (driver) {
                ZVAL_STRING(&name, (char *) driver);
            }
        }%

        return name;
    }

    public static function SDLCreateRendererWithProperties(int props) -> int
    {
        int ptr;

        %{
            SDL_Renderer *renderer = SDL_CreateRendererWithProperties((SDL_PropertiesID) props);
            ptr = (zend_long)(uintptr_t) renderer;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateRendererWithProperties failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLGetRenderer(int window) -> int
    {
        int ptr;

        %{
            SDL_Window *win = (SDL_Window *)(uintptr_t) window;
            SDL_Renderer *renderer = SDL_GetRenderer(win);
            ptr = renderer ? (zend_long)(uintptr_t) renderer : 0;
        }%

        return ptr;
    }

    public static function SDLGetRenderWindow(int renderer) -> int
    {
        int ptr;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Window *win = SDL_GetRenderWindow(ren);
            ptr = win ? (zend_long)(uintptr_t) win : 0;
        }%

        return ptr;
    }

    public static function SDLGetRendererName(int renderer) -> string
    {
        string name = "";

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            const char *n = SDL_GetRendererName(ren);
            if (n) {
                ZVAL_STRING(&name, (char *) n);
            }
        }%

        return name;
    }

    public static function SDLGetRendererProperties(int renderer) -> int
    {
        int props;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            props = (zend_long) SDL_GetRendererProperties(ren);
        }%

        return props;
    }

    public static function SDLGetRenderOutputSize(int renderer) -> array
    {
        int w;
        int h;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            int ww = 0, hh = 0;
            result = SDL_GetRenderOutputSize(ren, &ww, &hh);
            w = (zend_long) ww;
            h = (zend_long) hh;
        }%

        if !result {
            return [];
        }

        return ["w": w, "h": h];
    }

    public static function SDLGetCurrentRenderOutputSize(int renderer) -> array
    {
        int w;
        int h;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            int ww = 0, hh = 0;
            result = SDL_GetCurrentRenderOutputSize(ren, &ww, &hh);
            w = (zend_long) ww;
            h = (zend_long) hh;
        }%

        if !result {
            return [];
        }

        return ["w": w, "h": h];
    }

    public static function SDLCreateTextureWithProperties(int renderer, int props) -> array
    {
        int ptr;
        int tex_format;
        int tex_w;
        int tex_h;

        %{
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
        }%

        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "format": tex_format, "w": tex_w, "h": tex_h, "refcount": 1];
    }

    public static function SDLGetRendererFromTexture(int texture) -> int
    {
        int ptr;

        %{
            SDL_Texture  *tex = (SDL_Texture *)(uintptr_t) texture;
            SDL_Renderer *ren = SDL_GetRendererFromTexture(tex);
            ptr = ren ? (zend_long)(uintptr_t) ren : 0;
        }%

        return ptr;
    }

    public static function SDLSetTexturePalette(int texture, int palette) -> bool
    {
        bool result;

        %{
            SDL_Texture *tex = (SDL_Texture *)(uintptr_t) texture;
            SDL_Palette *pal = (SDL_Palette *)(uintptr_t) palette;
            result = SDL_SetTexturePalette(tex, pal);
        }%

        return result;
    }

    public static function SDLGetTexturePalette(int texture) -> int
    {
        int ptr;

        %{
            SDL_Texture *tex = (SDL_Texture *)(uintptr_t) texture;
            SDL_Palette *pal = SDL_GetTexturePalette(tex);
            ptr = pal ? (zend_long)(uintptr_t) pal : 0;
        }%

        return ptr;
    }

    public static function SDLSetTextureColorMod(int texture, int r, int g, int b) -> bool
    {
        bool result;

        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            result = SDL_SetTextureColorMod(te, (Uint8) r, (Uint8) g, (Uint8) b);
        }%

        return result;
    }

    public static function SDLGetTextureColorMod(int texture) -> array
    {
        int r;
        int g;
        int b;
        bool result;

        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            Uint8 rr = 0, gg = 0, bb = 0;
            result = SDL_GetTextureColorMod(te, &rr, &gg, &bb);
            r = (zend_long) rr;
            g = (zend_long) gg;
            b = (zend_long) bb;
        }%

        if !result {
            return [];
        }

        return ["r": r, "g": g, "b": b];
    }

    public static function SDLGetTextureColorModFloat(int texture) -> array
    {
        double r;
        double g;
        double b;
        bool result;

        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            float rr = 0.0f, gg = 0.0f, bb = 0.0f;
            result = SDL_GetTextureColorModFloat(te, &rr, &gg, &bb);
            r = (double) rr;
            g = (double) gg;
            b = (double) bb;
        }%

        if !result {
            return [];
        }

        return ["r": r, "g": g, "b": b];
    }

    public static function SDLSetTextureAlphaMod(int texture, int alpha) -> bool
    {
        bool result;

        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            result = SDL_SetTextureAlphaMod(te, (Uint8) alpha);
        }%

        return result;
    }

    public static function SDLSetTextureAlphaModFloat(int texture, double alpha) -> bool
    {
        bool result;

        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            result = SDL_SetTextureAlphaModFloat(te, (float) alpha);
        }%

        return result;
    }

    public static function SDLGetTextureAlphaMod(int texture) -> array
    {
        int alpha;
        bool result;

        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            Uint8 aa = 0;
            result = SDL_GetTextureAlphaMod(te, &aa);
            alpha = (zend_long) aa;
        }%

        if !result {
            return [];
        }

        return ["alpha": alpha];
    }

    public static function SDLGetTextureAlphaModFloat(int texture) -> array
    {
        double alpha;
        bool result;

        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            float aa = 0.0f;
            result = SDL_GetTextureAlphaModFloat(te, &aa);
            alpha = (double) aa;
        }%

        if !result {
            return [];
        }

        return ["alpha": alpha];
    }

    public static function SDLSetTextureBlendMode(int texture, int blendMode) -> bool
    {
        bool result;

        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            result = SDL_SetTextureBlendMode(te, (SDL_BlendMode) blendMode);
        }%

        return result;
    }

    public static function SDLGetTextureBlendMode(int texture) -> array
    {
        int blendMode;
        bool result;

        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            SDL_BlendMode mode = SDL_BLENDMODE_INVALID;
            result = SDL_GetTextureBlendMode(te, &mode);
            blendMode = (zend_long) mode;
        }%

        if !result {
            return [];
        }

        return ["blend_mode": blendMode];
    }

    public static function SDLGetTextureScaleMode(int texture) -> array
    {
        int scaleMode;
        bool result;

        %{
            SDL_Texture *te = (SDL_Texture *)(uintptr_t) texture;
            SDL_ScaleMode mode = SDL_SCALEMODE_NEAREST;
            result = SDL_GetTextureScaleMode(te, &mode);
            scaleMode = (zend_long) mode;
        }%

        if !result {
            return [];
        }

        return ["scale_mode": scaleMode];
    }

    public static function SDLUpdateTexture(int texture, string pixels, int pitch, var rect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLUpdateYUVTexture(int texture, string yplane, int ypitch, string uplane, int upitch, string vplane, int vpitch, var rect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLUpdateNVTexture(int texture, string yplane, int ypitch, string uvplane, int uvpitch, var rect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLLockTexture(int texture, var rect = null) -> array
    {
        int pitch;
        int lock_w;
        int lock_h;
        int pixels_ptr;

        %{
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
        }%

        if pixels_ptr == 0 {
            return [];
        }

        return ["pitch": pitch, "w": lock_w, "h": lock_h, "pixels_ptr": pixels_ptr];
    }

    public static function SDLSetRenderTarget(int renderer, var texture = null) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *tex = NULL;

            if (Z_TYPE_P(texture) != IS_NULL && zval_get_long(texture) != 0) {
                tex = (SDL_Texture *)(uintptr_t) zval_get_long(texture);
            }

            result = SDL_SetRenderTarget(ren, tex);
        }%

        return result;
    }

    public static function SDLGetRenderTarget(int renderer) -> int
    {
        int ptr;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *tex = SDL_GetRenderTarget(ren);
            ptr = tex ? (zend_long)(uintptr_t) tex : 0;
        }%

        return ptr;
    }

    public static function SDLGetRenderLogicalPresentation(int renderer) -> array
    {
        int w;
        int h;
        int mode;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            int ww = 0, hh = 0;
            SDL_RendererLogicalPresentation pres = SDL_LOGICAL_PRESENTATION_DISABLED;
            result = SDL_GetRenderLogicalPresentation(ren, &ww, &hh, &pres);
            w = (zend_long) ww;
            h = (zend_long) hh;
            mode = (zend_long) pres;
        }%

        if !result {
            return [];
        }

        return ["w": w, "h": h, "mode": mode];
    }

    public static function SDLGetRenderLogicalPresentationRect(int renderer) -> array
    {
        double x;
        double y;
        double w;
        double h;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_FRect rect = {0};
            result = SDL_GetRenderLogicalPresentationRect(ren, &rect);
            x = (double) rect.x;
            y = (double) rect.y;
            w = (double) rect.w;
            h = (double) rect.h;
        }%

        if !result {
            return [];
        }

        return [0: x, 1: y, 2: w, 3: h];
    }

    public static function SDLRenderCoordinatesFromWindow(int renderer, double windowX, double windowY) -> array
    {
        double x;
        double y;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            float rx = 0.0f, ry = 0.0f;
            result = SDL_RenderCoordinatesFromWindow(ren, (float) windowX, (float) windowY, &rx, &ry);
            x = (double) rx;
            y = (double) ry;
        }%

        if !result {
            return [];
        }

        return ["x": x, "y": y];
    }

    public static function SDLRenderCoordinatesToWindow(int renderer, double x, double y) -> array
    {
        double windowX;
        double windowY;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            float wx = 0.0f, wy = 0.0f;
            result = SDL_RenderCoordinatesToWindow(ren, (float) x, (float) y, &wx, &wy);
            windowX = (double) wx;
            windowY = (double) wy;
        }%

        if !result {
            return [];
        }

        return ["window_x": windowX, "window_y": windowY];
    }

    public static function SDLConvertEventToRenderCoordinates(int renderer, int eventPtr) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Event *event = (SDL_Event *)(uintptr_t) eventPtr;
            result = SDL_ConvertEventToRenderCoordinates(ren, event);
        }%

        return result;
    }

    public static function SDLGetRenderViewport(int renderer) -> array
    {
        int x;
        int y;
        int w;
        int h;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Rect rect = {0};
            result = SDL_GetRenderViewport(ren, &rect);
            x = (zend_long) rect.x;
            y = (zend_long) rect.y;
            w = (zend_long) rect.w;
            h = (zend_long) rect.h;
        }%

        if !result {
            return [];
        }

        return [0: x, 1: y, 2: w, 3: h];
    }

    public static function SDLRenderViewportSet(int renderer) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_RenderViewportSet(ren);
        }%

        return result;
    }

    public static function SDLGetRenderSafeArea(int renderer) -> array
    {
        int x;
        int y;
        int w;
        int h;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Rect rect = {0};
            result = SDL_GetRenderSafeArea(ren, &rect);
            x = (zend_long) rect.x;
            y = (zend_long) rect.y;
            w = (zend_long) rect.w;
            h = (zend_long) rect.h;
        }%

        if !result {
            return [];
        }

        return [0: x, 1: y, 2: w, 3: h];
    }

    public static function SDLGetRenderClipRect(int renderer) -> array
    {
        int x;
        int y;
        int w;
        int h;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Rect rect = {0};
            result = SDL_GetRenderClipRect(ren, &rect);
            x = (zend_long) rect.x;
            y = (zend_long) rect.y;
            w = (zend_long) rect.w;
            h = (zend_long) rect.h;
        }%

        if !result {
            return [];
        }

        return [0: x, 1: y, 2: w, 3: h];
    }

    public static function SDLRenderClipEnabled(int renderer) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_RenderClipEnabled(ren);
        }%

        return result;
    }

    public static function SDLGetRenderScale(int renderer) -> array
    {
        double scaleX;
        double scaleY;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            float sx = 0.0f, sy = 0.0f;
            result = SDL_GetRenderScale(ren, &sx, &sy);
            scaleX = (double) sx;
            scaleY = (double) sy;
        }%

        if !result {
            return [];
        }

        return ["scale_x": scaleX, "scale_y": scaleY];
    }

    public static function SDLGetRenderDrawColor(int renderer) -> array
    {
        int r;
        int g;
        int b;
        int a;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            Uint8 rr = 0, gg = 0, bb = 0, aa = 0;
            result = SDL_GetRenderDrawColor(ren, &rr, &gg, &bb, &aa);
            r = (zend_long) rr;
            g = (zend_long) gg;
            b = (zend_long) bb;
            a = (zend_long) aa;
        }%

        if !result {
            return [];
        }

        return ["r": r, "g": g, "b": b, "a": a];
    }

    public static function SDLGetRenderDrawColorFloat(int renderer) -> array
    {
        double r;
        double g;
        double b;
        double a;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            float rr = 0.0f, gg = 0.0f, bb = 0.0f, aa = 0.0f;
            result = SDL_GetRenderDrawColorFloat(ren, &rr, &gg, &bb, &aa);
            r = (double) rr;
            g = (double) gg;
            b = (double) bb;
            a = (double) aa;
        }%

        if !result {
            return [];
        }

        return ["r": r, "g": g, "b": b, "a": a];
    }

    public static function SDLSetRenderColorScale(int renderer, double scale) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderColorScale(ren, (float) scale);
        }%

        return result;
    }

    public static function SDLGetRenderColorScale(int renderer) -> array
    {
        double scale;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            float sc = 0.0f;
            result = SDL_GetRenderColorScale(ren, &sc);
            scale = (double) sc;
        }%

        if !result {
            return [];
        }

        return ["scale": scale];
    }

    public static function SDLSetRenderDrawBlendMode(int renderer, int blendMode) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderDrawBlendMode(ren, (SDL_BlendMode) blendMode);
        }%

        return result;
    }

    public static function SDLGetRenderDrawBlendMode(int renderer) -> array
    {
        int blendMode;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_BlendMode mode = SDL_BLENDMODE_INVALID;
            result = SDL_GetRenderDrawBlendMode(ren, &mode);
            blendMode = (zend_long) mode;
        }%

        if !result {
            return [];
        }

        return ["blend_mode": blendMode];
    }

    public static function SDLRenderPoint(int renderer, double x, double y) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_RenderPoint(ren, (float) x, (float) y);
        }%

        return result;
    }

    public static function SDLRenderTextureTiled(int renderer, int texture, double scale, var srcrect = null, var dstrect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLRenderTexture9Grid(int renderer, int texture, double leftWidth, double rightWidth, double topHeight, double bottomHeight, double scale, var srcrect = null, var dstrect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLRenderTexture9GridTiled(int renderer, int texture, double leftWidth, double rightWidth, double topHeight, double bottomHeight, double scale, double tileScale, var srcrect = null, var dstrect = null) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLRenderGeometryRaw(int renderer, int texture, string xy, int xyStride, var color = null, int colorStride = 0, var uv = null, int uvStride = 0, int numVertices = 0, var indices = null, int numIndices = 0, int sizeIndices = 4) -> bool
    {
        bool result;

        %{
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
        }%

        return result;
    }

    public static function SDLSetRenderTextureAddressMode(int renderer, int uMode, int vMode) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderTextureAddressMode(ren, (SDL_TextureAddressMode) uMode, (SDL_TextureAddressMode) vMode);
        }%

        return result;
    }

    public static function SDLGetRenderTextureAddressMode(int renderer) -> array
    {
        int uMode;
        int vMode;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_TextureAddressMode um = SDL_TEXTURE_ADDRESS_INVALID;
            SDL_TextureAddressMode vm = SDL_TEXTURE_ADDRESS_INVALID;
            result = SDL_GetRenderTextureAddressMode(ren, &um, &vm);
            uMode = (zend_long) um;
            vMode = (zend_long) vm;
        }%

        if !result {
            return [];
        }

        return ["u_mode": uMode, "v_mode": vMode];
    }

    public static function SDLFlushRenderer(int renderer) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_FlushRenderer(ren);
        }%

        return result;
    }

    public static function SDLGetRenderMetalLayer(int renderer) -> int
    {
        int ptr;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            void *layer = SDL_GetRenderMetalLayer(ren);
            ptr = layer ? (zend_long)(uintptr_t) layer : 0;
        }%

        return ptr;
    }

    public static function SDLGetRenderMetalCommandEncoder(int renderer) -> int
    {
        int ptr;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            void *encoder = SDL_GetRenderMetalCommandEncoder(ren);
            ptr = encoder ? (zend_long)(uintptr_t) encoder : 0;
        }%

        return ptr;
    }

    public static function SDLAddVulkanRenderSemaphores(int renderer, int waitStageMask, int waitSemaphore, int signalSemaphore) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_AddVulkanRenderSemaphores(
                ren,
                (Uint32) waitStageMask,
                (Sint64) waitSemaphore,
                (Sint64) signalSemaphore
            );
        }%

        return result;
    }

    public static function SDLSetRenderVSync(int renderer, int vsync) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetRenderVSync(ren, (int) vsync);
        }%

        return result;
    }

    public static function SDLGetRenderVSync(int renderer) -> array
    {
        int vsync;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            int vs = 0;
            result = SDL_GetRenderVSync(ren, &vs);
            vsync = (zend_long) vs;
        }%

        if !result {
            return [];
        }

        return ["vsync": vsync];
    }

    public static function SDLSetDefaultTextureScaleMode(int renderer, int scaleMode) -> bool
    {
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            result = SDL_SetDefaultTextureScaleMode(ren, (SDL_ScaleMode) scaleMode);
        }%

        return result;
    }

    public static function SDLGetDefaultTextureScaleMode(int renderer) -> array
    {
        int scaleMode;
        bool result;

        %{
            SDL_Renderer *ren = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_ScaleMode mode = SDL_SCALEMODE_NEAREST;
            result = SDL_GetDefaultTextureScaleMode(ren, &mode);
            scaleMode = (zend_long) mode;
        }%

        if !result {
            return [];
        }

        return ["scale_mode": scaleMode];
    }
}
