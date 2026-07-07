
extern zend_class_entry *sdl3_sdl_surface_sdlsurface_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Surface_SDLSurface);

PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLCreateSurface);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLDuplicateSurface);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLConvertSurface);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSurfaceToBlackAndWhite);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurface);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLFillSurfaceRect);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLMapRGB);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLLockSurface);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLUnlockSurface);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLDestroySurface);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLLoadPNG);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLLoadBMP);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLWriteSurfacePixelAt);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLWriteSurfacePixels);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLReadSurfacePixels);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfacePalette);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, buildSurfaceArray);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, packSurfaceFromPtr);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, buildPaletteArray);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, packPaletteFromPtr);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLCreateSurfaceFrom);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceProperties);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceColorspace);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceColorspace);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLCreateSurfacePalette);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfacePalette);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLAddSurfaceAlternateImage);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSurfaceHasAlternateImages);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceImages);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLRemoveSurfaceAlternateImages);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLLoadSurface);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSaveBMP);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSavePNG);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceRLE);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSurfaceHasRLE);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceColorKey);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSurfaceHasColorKey);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceColorKey);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceColorMod);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceColorMod);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceAlphaMod);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceAlphaMod);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceBlendMode);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceBlendMode);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceClipRect);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceClipRect);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLFlipSurface);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLRotateSurface);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLScaleSurface);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLConvertSurfaceAndColorspace);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLConvertPixels);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLConvertPixelsAndColorspace);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLPremultiplyAlpha);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLPremultiplySurfaceAlpha);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLClearSurface);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLFillSurfaceRects);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceUnchecked);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceScaled);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceUncheckedScaled);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLStretchSurface);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceTiled);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceTiledWithScale);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurface9Grid);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLMapSurfaceRGB);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLMapSurfaceRGBA);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLReadSurfacePixel);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLReadSurfacePixelFloat);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLWriteSurfacePixel);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLWriteSurfacePixelFloat);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLCreatePalette);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLDestroyPalette);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLSetPaletteColors);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetPixelFormatName);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetMasksForPixelFormat);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetPixelFormatForMasks);
PHP_METHOD(Sdl3_SDL_Surface_SDLSurface, SDLGetRGB);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlcreatesurface, 0, 3, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlduplicatesurface, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlconvertsurface, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsurfacetoblackandwhite, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurface, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst, IS_LONG, 0)
	ZEND_ARG_INFO(0, srcrect)
	ZEND_ARG_INFO(0, dstrect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlfillsurfacerect, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, color, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlmaprgb, 0, 5, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, palette, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdllocksurface, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlunlocksurface, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdldestroysurface, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlloadpng, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, file, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlloadbmp, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, file, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlwritesurfacepixelat, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pixel, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlwritesurfacepixels, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, data, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlreadsurfacepixels, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfacepalette, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_buildsurfacearray, 0, 9, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fmt, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pitch, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pixels_ptr, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, pixels_data, 0)
	ZEND_ARG_TYPE_INFO(0, refcount, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_packsurfacefromptr, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_buildpalettearray, 0, 5, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ncolors, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, colors, 0)
	ZEND_ARG_TYPE_INFO(0, version, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, refcount, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_packpalettefromptr, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, palette, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlcreatesurfacefrom, 0, 5, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pixels, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, pitch, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfaceproperties, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacecolorspace, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, colorspace, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfacecolorspace, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlcreatesurfacepalette, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacepalette, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, palette, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdladdsurfacealternateimage, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, image, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsurfacehasalternateimages, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfaceimages, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlremovesurfacealternateimages, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlloadsurface, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, file, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsavebmp, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, file, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsavepng, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, file, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacerle, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, enabled, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsurfacehasrle, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacecolorkey, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, enabled, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsurfacehascolorkey, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfacecolorkey, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacecolormod, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfacecolormod, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacealphamod, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, alpha, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfacealphamod, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfaceblendmode, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, blendMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfaceblendmode, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacecliprect, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfacecliprect, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlflipsurface, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flip, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlrotatesurface, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, angle, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlscalesurface, 0, 4, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scaleMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlconvertsurfaceandcolorspace, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_INFO(0, palette)
	ZEND_ARG_TYPE_INFO(0, colorspace, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlconvertpixels, 0, 7, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src_format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, src_pitch, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst_format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst_pitch, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlconvertpixelsandcolorspace, 0, 11, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src_format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src_colorspace, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src_properties, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, src_pitch, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst_format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst_colorspace, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst_properties, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst_pitch, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlpremultiplyalpha, 0, 8, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src_format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, src_pitch, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst_format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst_pitch, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, linear, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlpremultiplysurfacealpha, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, linear, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlclearsurface, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlfillsurfacerects, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, dst, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, rects, 0)
	ZEND_ARG_TYPE_INFO(0, color, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurfaceunchecked, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, srcrect, 0)
	ZEND_ARG_TYPE_INFO(0, dst, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, dstrect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurfacescaled, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst, IS_LONG, 0)
	ZEND_ARG_INFO(0, srcrect)
	ZEND_ARG_INFO(0, dstrect)
	ZEND_ARG_TYPE_INFO(0, scaleMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurfaceuncheckedscaled, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, srcrect, 0)
	ZEND_ARG_TYPE_INFO(0, dst, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, dstrect, 0)
	ZEND_ARG_TYPE_INFO(0, scaleMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlstretchsurface, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst, IS_LONG, 0)
	ZEND_ARG_INFO(0, srcrect)
	ZEND_ARG_INFO(0, dstrect)
	ZEND_ARG_TYPE_INFO(0, scaleMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurfacetiled, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst, IS_LONG, 0)
	ZEND_ARG_INFO(0, srcrect)
	ZEND_ARG_INFO(0, dstrect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurfacetiledwithscale, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scale, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, scaleMode, IS_LONG, 0)
	ZEND_ARG_INFO(0, srcrect)
	ZEND_ARG_INFO(0, dstrect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurface9grid, 0, 8, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, left_width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, right_width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, top_height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bottom_height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scale, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, scaleMode, IS_LONG, 0)
	ZEND_ARG_INFO(0, srcrect)
	ZEND_ARG_INFO(0, dstrect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlmapsurfacergb, 0, 4, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlmapsurfacergba, 0, 5, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlreadsurfacepixel, 0, 3, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlreadsurfacepixelfloat, 0, 3, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlwritesurfacepixel, 0, 7, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlwritesurfacepixelfloat, 0, 7, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlcreatepalette, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ncolors, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdldestroypalette, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, palette, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlsetpalettecolors, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, palette, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, colors, 0)
	ZEND_ARG_TYPE_INFO(0, firstcolor, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ncolors, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlgetpixelformatname, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlgetmasksforpixelformat, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlgetpixelformatformasks, 0, 5, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bpp, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, rmask, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gmask, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bmask, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, amask, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_surface_sdlsurface_sdlgetrgb, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, pixel, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format_ptr, IS_LONG, 0)
	ZEND_ARG_INFO(0, palette_ptr)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_surface_sdlsurface_method_entry) {
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLCreateSurface, arginfo_sdl3_sdl_surface_sdlsurface_sdlcreatesurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLDuplicateSurface, arginfo_sdl3_sdl_surface_sdlsurface_sdlduplicatesurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLConvertSurface, arginfo_sdl3_sdl_surface_sdlsurface_sdlconvertsurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSurfaceToBlackAndWhite, arginfo_sdl3_sdl_surface_sdlsurface_sdlsurfacetoblackandwhite, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurface, arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLFillSurfaceRect, arginfo_sdl3_sdl_surface_sdlsurface_sdlfillsurfacerect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLMapRGB, arginfo_sdl3_sdl_surface_sdlsurface_sdlmaprgb, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLLockSurface, arginfo_sdl3_sdl_surface_sdlsurface_sdllocksurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLUnlockSurface, arginfo_sdl3_sdl_surface_sdlsurface_sdlunlocksurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLDestroySurface, arginfo_sdl3_sdl_surface_sdlsurface_sdldestroysurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLLoadPNG, arginfo_sdl3_sdl_surface_sdlsurface_sdlloadpng, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLLoadBMP, arginfo_sdl3_sdl_surface_sdlsurface_sdlloadbmp, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLWriteSurfacePixelAt, arginfo_sdl3_sdl_surface_sdlsurface_sdlwritesurfacepixelat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLWriteSurfacePixels, arginfo_sdl3_sdl_surface_sdlsurface_sdlwritesurfacepixels, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLReadSurfacePixels, arginfo_sdl3_sdl_surface_sdlsurface_sdlreadsurfacepixels, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfacePalette, arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfacepalette, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, buildSurfaceArray, arginfo_sdl3_sdl_surface_sdlsurface_buildsurfacearray, ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, packSurfaceFromPtr, arginfo_sdl3_sdl_surface_sdlsurface_packsurfacefromptr, ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, buildPaletteArray, arginfo_sdl3_sdl_surface_sdlsurface_buildpalettearray, ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, packPaletteFromPtr, arginfo_sdl3_sdl_surface_sdlsurface_packpalettefromptr, ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLCreateSurfaceFrom, arginfo_sdl3_sdl_surface_sdlsurface_sdlcreatesurfacefrom, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceProperties, arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfaceproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceColorspace, arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacecolorspace, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceColorspace, arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfacecolorspace, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLCreateSurfacePalette, arginfo_sdl3_sdl_surface_sdlsurface_sdlcreatesurfacepalette, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfacePalette, arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacepalette, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLAddSurfaceAlternateImage, arginfo_sdl3_sdl_surface_sdlsurface_sdladdsurfacealternateimage, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSurfaceHasAlternateImages, arginfo_sdl3_sdl_surface_sdlsurface_sdlsurfacehasalternateimages, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceImages, arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfaceimages, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLRemoveSurfaceAlternateImages, arginfo_sdl3_sdl_surface_sdlsurface_sdlremovesurfacealternateimages, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLLoadSurface, arginfo_sdl3_sdl_surface_sdlsurface_sdlloadsurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSaveBMP, arginfo_sdl3_sdl_surface_sdlsurface_sdlsavebmp, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSavePNG, arginfo_sdl3_sdl_surface_sdlsurface_sdlsavepng, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceRLE, arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacerle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSurfaceHasRLE, arginfo_sdl3_sdl_surface_sdlsurface_sdlsurfacehasrle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceColorKey, arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacecolorkey, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSurfaceHasColorKey, arginfo_sdl3_sdl_surface_sdlsurface_sdlsurfacehascolorkey, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceColorKey, arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfacecolorkey, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceColorMod, arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacecolormod, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceColorMod, arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfacecolormod, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceAlphaMod, arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacealphamod, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceAlphaMod, arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfacealphamod, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceBlendMode, arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfaceblendmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceBlendMode, arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfaceblendmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSetSurfaceClipRect, arginfo_sdl3_sdl_surface_sdlsurface_sdlsetsurfacecliprect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLGetSurfaceClipRect, arginfo_sdl3_sdl_surface_sdlsurface_sdlgetsurfacecliprect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLFlipSurface, arginfo_sdl3_sdl_surface_sdlsurface_sdlflipsurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLRotateSurface, arginfo_sdl3_sdl_surface_sdlsurface_sdlrotatesurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLScaleSurface, arginfo_sdl3_sdl_surface_sdlsurface_sdlscalesurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLConvertSurfaceAndColorspace, arginfo_sdl3_sdl_surface_sdlsurface_sdlconvertsurfaceandcolorspace, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLConvertPixels, arginfo_sdl3_sdl_surface_sdlsurface_sdlconvertpixels, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLConvertPixelsAndColorspace, arginfo_sdl3_sdl_surface_sdlsurface_sdlconvertpixelsandcolorspace, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLPremultiplyAlpha, arginfo_sdl3_sdl_surface_sdlsurface_sdlpremultiplyalpha, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLPremultiplySurfaceAlpha, arginfo_sdl3_sdl_surface_sdlsurface_sdlpremultiplysurfacealpha, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLClearSurface, arginfo_sdl3_sdl_surface_sdlsurface_sdlclearsurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLFillSurfaceRects, arginfo_sdl3_sdl_surface_sdlsurface_sdlfillsurfacerects, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceUnchecked, arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurfaceunchecked, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceScaled, arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurfacescaled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceUncheckedScaled, arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurfaceuncheckedscaled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLStretchSurface, arginfo_sdl3_sdl_surface_sdlsurface_sdlstretchsurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceTiled, arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurfacetiled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurfaceTiledWithScale, arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurfacetiledwithscale, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLBlitSurface9Grid, arginfo_sdl3_sdl_surface_sdlsurface_sdlblitsurface9grid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLMapSurfaceRGB, arginfo_sdl3_sdl_surface_sdlsurface_sdlmapsurfacergb, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLMapSurfaceRGBA, arginfo_sdl3_sdl_surface_sdlsurface_sdlmapsurfacergba, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLReadSurfacePixel, arginfo_sdl3_sdl_surface_sdlsurface_sdlreadsurfacepixel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLReadSurfacePixelFloat, arginfo_sdl3_sdl_surface_sdlsurface_sdlreadsurfacepixelfloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLWriteSurfacePixel, arginfo_sdl3_sdl_surface_sdlsurface_sdlwritesurfacepixel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLWriteSurfacePixelFloat, arginfo_sdl3_sdl_surface_sdlsurface_sdlwritesurfacepixelfloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLCreatePalette, arginfo_sdl3_sdl_surface_sdlsurface_sdlcreatepalette, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLDestroyPalette, arginfo_sdl3_sdl_surface_sdlsurface_sdldestroypalette, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLSetPaletteColors, arginfo_sdl3_sdl_surface_sdlsurface_sdlsetpalettecolors, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLGetPixelFormatName, arginfo_sdl3_sdl_surface_sdlsurface_sdlgetpixelformatname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLGetMasksForPixelFormat, arginfo_sdl3_sdl_surface_sdlsurface_sdlgetmasksforpixelformat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLGetPixelFormatForMasks, arginfo_sdl3_sdl_surface_sdlsurface_sdlgetpixelformatformasks, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Surface_SDLSurface, SDLGetRGB, arginfo_sdl3_sdl_surface_sdlsurface_sdlgetrgb, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
