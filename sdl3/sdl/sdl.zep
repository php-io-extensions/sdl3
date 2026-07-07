namespace Sdl3\SDL;

%{
#include <SDL3/SDL.h>
#include <stdio.h>
}%

class SDL
{
    public static function SDLInit(int flags) -> bool
    {
        bool result;

        %{
            result = SDL_Init((Uint32) flags);
        }%

        return result;
    }

    public static function SDLInitSubSystem(int flags) -> bool
    {
        bool result;

        %{
            result = SDL_InitSubSystem((Uint32) flags);
        }%

        return result;
    }

    public static function SDLWasInit(int flags) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_WasInit((Uint32) flags);
        }%

        return result;
    }

    public static function SDLQuit() -> void
    {
        %{
            SDL_Quit();
        }%
    }

    public static function SDLQuitSubSystem(int flags) -> void
    {
        %{
            SDL_QuitSubSystem((SDL_InitFlags) flags);
        }%
    }

    public static function SDLExitProcess(int exitcode) -> void
    {
        %{
            exit((int) exitcode);
        }%
    }

    public static function SDLGetPixelFormatDetails(int format) -> array
    {
        int ptr;
        int fmt;
        int bits_per_pixel;
        int bytes_per_pixel;
        int rmask;
        int gmask;
        int bmask;
        int amask;
        int rbits;
        int gbits;
        int bbits;
        int abits;
        int rshift;
        int gshift;
        int bshift;
        int ashift;

        %{
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
        }%

        if fmt == 0 {
            return [];
        }

        return [
            "ptr":             ptr,
            "format":          fmt,
            "bits_per_pixel":  bits_per_pixel,
            "bytes_per_pixel": bytes_per_pixel,
            "rmask":           rmask,
            "gmask":           gmask,
            "bmask":           bmask,
            "amask":           amask,
            "rbits":           rbits,
            "gbits":           gbits,
            "bbits":           bbits,
            "abits":           abits,
            "rshift":          rshift,
            "gshift":          gshift,
            "bshift":          bshift,
            "ashift":          ashift
        ];
    }

    public static function SDLGetRGBA(int pixel, int format_ptr, var palette_ptr = null) -> array
    {
        int r;
        int g;
        int b;
        int a;

        %{
            const SDL_PixelFormatDetails *fmt = (const SDL_PixelFormatDetails *)(uintptr_t) format_ptr;
            const SDL_Palette *pal = (Z_TYPE_P(palette_ptr) == IS_NULL) ? NULL : (const SDL_Palette *)(uintptr_t)(zend_long)Z_LVAL_P(palette_ptr);

            Uint8 cr = 0, cg = 0, cb = 0, ca = 0;
            SDL_GetRGBA((Uint32) pixel, fmt, pal, &cr, &cg, &cb, &ca);

            r = (zend_long) cr;
            g = (zend_long) cg;
            b = (zend_long) cb;
            a = (zend_long) ca;
        }%

        return ["r": r, "g": g, "b": b, "a": a];
    }

    public static function SDLMapRGBA(int format_ptr, var palette_ptr = null, int r, int g, int b, int a) -> int
    {
        int result;

        %{
            const SDL_PixelFormatDetails *fmt = (const SDL_PixelFormatDetails *)(uintptr_t) format_ptr;
            const SDL_Palette *pal = (Z_TYPE_P(palette_ptr) == IS_NULL) ? NULL : (const SDL_Palette *)(uintptr_t)(zend_long)Z_LVAL_P(palette_ptr);

            result = (zend_long) SDL_MapRGBA(fmt, pal, (Uint8) r, (Uint8) g, (Uint8) b, (Uint8) a);
        }%

        return result;
    }

    public static function SDLGetSandbox() -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetSandbox();
        }%

        return result;
    }

    public static function SDLGetVersion() -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetVersion();
        }%

        return result;
    }

    public static function SDLGetRevision() -> string
    {
        string result = "";

        %{
            const char *rev = SDL_GetRevision();
            if (rev) {
                ZVAL_STRING(&result, rev);
            }
        }%

        return result;
    }

    public static function SDLGetPlatform() -> string
    {
        string result = "";

        %{
            const char *plat = SDL_GetPlatform();
            if (plat) {
                ZVAL_STRING(&result, plat);
            }
        }%

        return result;
    }

    public static function SDLIsTablet() -> bool
    {
        bool result;

        %{
            result = SDL_IsTablet();
        }%

        return result;
    }

    public static function SDLIsTV() -> bool
    {
        bool result;

        %{
            result = SDL_IsTV();
        }%

        return result;
    }

    public static function SDLSetAppMetadata(string appname, string appversion, string appidentifier) -> bool
    {
        bool result;

        %{
            result = SDL_SetAppMetadata(Z_STRVAL(appname), Z_STRVAL(appversion), Z_STRVAL(appidentifier));
        }%

        return result;
    }

    public static function SDLSetAppMetadataProperty(string name, string value) -> bool
    {
        bool result;

        %{
            result = SDL_SetAppMetadataProperty(Z_STRVAL(name), Z_STRVAL(value));
        }%

        return result;
    }

    public static function SDLGetAppMetadataProperty(string name) -> string
    {
        string result = "";

        %{
            const char *prop = SDL_GetAppMetadataProperty(Z_STRVAL(name));
            if (prop) {
                ZVAL_STRING(&result, prop);
            }
        }%

        return result;
    }

    public static function SDLSetMainReady() -> void
    {
        %{
            extern void SDL_SetMainReady(void);
            SDL_SetMainReady();
        }%
    }

    public static function SDLIsMainThread() -> bool
    {
        bool result;

        %{
            result = SDL_IsMainThread();
        }%

        return result;
    }

    public static function SDLRand(int n) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_rand((Sint32) n);
        }%

        return result;
    }

    public static function SDLRandf() -> double
    {
        double result;

        %{
            result = (double) SDL_randf();
        }%

        return result;
    }
}