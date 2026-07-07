
extern zend_class_entry *sdl3_sdl_render_sdlrender_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Render_SDLRender);

PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLCreateRenderer);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLCreateSoftwareRenderer);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderClear);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderPresent);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderTexture);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderTextureRotated);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderDrawColor);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderDrawColorFloat);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLCreateTexture);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLCreateTextureFromSurface);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLLockTextureToSurface);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLUnlockTexture);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTextureColorModFloat);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTextureScaleMode);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureSize);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderLogicalPresentation);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLDestroyRenderer);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLDestroyTexture);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderFillRect);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderViewport);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderClipRect);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderReadPixels);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLUpdateTextureFromSurface);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderDebugText);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderScale);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderTextureAffine);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderFillRects);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderRects);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderLine);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderRect);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderPoints);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderGeometry);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderLines);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetNumRenderDrivers);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderDriver);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLCreateRendererWithProperties);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderer);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderWindow);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRendererName);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRendererProperties);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderOutputSize);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetCurrentRenderOutputSize);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLCreateTextureWithProperties);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRendererFromTexture);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTexturePalette);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTexturePalette);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTextureColorMod);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureColorMod);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureColorModFloat);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTextureAlphaMod);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTextureAlphaModFloat);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureAlphaMod);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureAlphaModFloat);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetTextureBlendMode);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureBlendMode);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetTextureScaleMode);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLUpdateTexture);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLUpdateYUVTexture);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLUpdateNVTexture);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLLockTexture);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderTarget);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderTarget);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderLogicalPresentation);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderLogicalPresentationRect);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderCoordinatesFromWindow);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderCoordinatesToWindow);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLConvertEventToRenderCoordinates);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderViewport);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderViewportSet);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderSafeArea);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderClipRect);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderClipEnabled);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderScale);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderDrawColor);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderDrawColorFloat);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderColorScale);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderColorScale);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderDrawBlendMode);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderDrawBlendMode);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderPoint);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderTextureTiled);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderTexture9Grid);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderTexture9GridTiled);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLRenderGeometryRaw);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderTextureAddressMode);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderTextureAddressMode);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLFlushRenderer);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderMetalLayer);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderMetalCommandEncoder);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLAddVulkanRenderSemaphores);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetRenderVSync);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetRenderVSync);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLSetDefaultTextureScaleMode);
PHP_METHOD(Sdl3_SDL_Render_SDLRender, SDLGetDefaultTextureScaleMode);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlcreaterenderer, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlcreatesoftwarerenderer, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderclear, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderpresent, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrendertexture, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_INFO(0, srcrect)
	ZEND_ARG_INFO(0, dstrect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrendertexturerotated, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, angle, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, flip, IS_LONG, 0)
	ZEND_ARG_INFO(0, srcrect)
	ZEND_ARG_INFO(0, dstrect)
	ZEND_ARG_INFO(0, center)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsetrenderdrawcolor, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsetrenderdrawcolorfloat, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlcreatetexture, 0, 5, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, access, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlcreatetexturefromsurface, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdllocktexturetosurface, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlunlocktexture, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsettexturecolormodfloat, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsettexturescalemode, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scaleMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgettexturesize, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsetrenderlogicalpresentation, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdldestroyrenderer, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdldestroytexture, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderfillrect, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsetrenderviewport, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsetrendercliprect, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderreadpixels, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlupdatetexturefromsurface, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderdebugtext, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsetrenderscale, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scaleX, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, scaleY, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrendertextureaffine, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_INFO(0, origin)
	ZEND_ARG_INFO(0, right)
	ZEND_ARG_INFO(0, down)
	ZEND_ARG_INFO(0, srcrect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderfillrects, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, rects, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderrects, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, rects, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderline, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y2, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderrect, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderpoints, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, points, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrendergeometry, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, vertices, 0)
	ZEND_ARG_TYPE_INFO(0, num_vertices, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, num_indices, IS_LONG, 0)
	ZEND_ARG_INFO(0, indices)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderlines, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, points, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetnumrenderdrivers, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderdriver, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlcreaterendererwithproperties, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderer, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderwindow, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderername, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrendererproperties, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderoutputsize, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetcurrentrenderoutputsize, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlcreatetexturewithproperties, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrendererfromtexture, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsettexturepalette, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, palette, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgettexturepalette, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsettexturecolormod, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgettexturecolormod, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgettexturecolormodfloat, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsettexturealphamod, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, alpha, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsettexturealphamodfloat, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, alpha, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgettexturealphamod, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgettexturealphamodfloat, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsettextureblendmode, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, blendMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgettextureblendmode, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgettexturescalemode, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlupdatetexture, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pixels, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, pitch, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlupdateyuvtexture, 0, 7, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, yplane, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, ypitch, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, uplane, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, upitch, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, vplane, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, vpitch, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlupdatenvtexture, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, yplane, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, ypitch, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, uvplane, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, uvpitch, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdllocktexture, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsetrendertarget, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrendertarget, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderlogicalpresentation, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderlogicalpresentationrect, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrendercoordinatesfromwindow, 0, 3, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, windowX, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, windowY, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrendercoordinatestowindow, 0, 3, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlconverteventtorendercoordinates, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, eventPtr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderviewport, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderviewportset, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrendersafearea, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrendercliprect, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderclipenabled, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderscale, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderdrawcolor, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderdrawcolorfloat, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsetrendercolorscale, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scale, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrendercolorscale, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsetrenderdrawblendmode, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, blendMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderdrawblendmode, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrenderpoint, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrendertexturetiled, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scale, IS_DOUBLE, 0)
	ZEND_ARG_INFO(0, srcrect)
	ZEND_ARG_INFO(0, dstrect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrendertexture9grid, 0, 7, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, leftWidth, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, rightWidth, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, topHeight, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, bottomHeight, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, scale, IS_DOUBLE, 0)
	ZEND_ARG_INFO(0, srcrect)
	ZEND_ARG_INFO(0, dstrect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrendertexture9gridtiled, 0, 8, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, leftWidth, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, rightWidth, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, topHeight, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, bottomHeight, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, scale, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, tileScale, IS_DOUBLE, 0)
	ZEND_ARG_INFO(0, srcrect)
	ZEND_ARG_INFO(0, dstrect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlrendergeometryraw, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, xy, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, xyStride, IS_LONG, 0)
	ZEND_ARG_INFO(0, color)
	ZEND_ARG_TYPE_INFO(0, colorStride, IS_LONG, 0)
	ZEND_ARG_INFO(0, uv)
	ZEND_ARG_TYPE_INFO(0, uvStride, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, numVertices, IS_LONG, 0)
	ZEND_ARG_INFO(0, indices)
	ZEND_ARG_TYPE_INFO(0, numIndices, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sizeIndices, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsetrendertextureaddressmode, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, uMode, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, vMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrendertextureaddressmode, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlflushrenderer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrendermetallayer, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrendermetalcommandencoder, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdladdvulkanrendersemaphores, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, waitStageMask, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, waitSemaphore, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, signalSemaphore, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsetrendervsync, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, vsync, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetrendervsync, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlsetdefaulttexturescalemode, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scaleMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_render_sdlrender_sdlgetdefaulttexturescalemode, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_render_sdlrender_method_entry) {
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLCreateRenderer, arginfo_sdl3_sdl_render_sdlrender_sdlcreaterenderer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLCreateSoftwareRenderer, arginfo_sdl3_sdl_render_sdlrender_sdlcreatesoftwarerenderer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderClear, arginfo_sdl3_sdl_render_sdlrender_sdlrenderclear, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderPresent, arginfo_sdl3_sdl_render_sdlrender_sdlrenderpresent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderTexture, arginfo_sdl3_sdl_render_sdlrender_sdlrendertexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderTextureRotated, arginfo_sdl3_sdl_render_sdlrender_sdlrendertexturerotated, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetRenderDrawColor, arginfo_sdl3_sdl_render_sdlrender_sdlsetrenderdrawcolor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetRenderDrawColorFloat, arginfo_sdl3_sdl_render_sdlrender_sdlsetrenderdrawcolorfloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLCreateTexture, arginfo_sdl3_sdl_render_sdlrender_sdlcreatetexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLCreateTextureFromSurface, arginfo_sdl3_sdl_render_sdlrender_sdlcreatetexturefromsurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLLockTextureToSurface, arginfo_sdl3_sdl_render_sdlrender_sdllocktexturetosurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLUnlockTexture, arginfo_sdl3_sdl_render_sdlrender_sdlunlocktexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetTextureColorModFloat, arginfo_sdl3_sdl_render_sdlrender_sdlsettexturecolormodfloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetTextureScaleMode, arginfo_sdl3_sdl_render_sdlrender_sdlsettexturescalemode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetTextureSize, arginfo_sdl3_sdl_render_sdlrender_sdlgettexturesize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetRenderLogicalPresentation, arginfo_sdl3_sdl_render_sdlrender_sdlsetrenderlogicalpresentation, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLDestroyRenderer, arginfo_sdl3_sdl_render_sdlrender_sdldestroyrenderer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLDestroyTexture, arginfo_sdl3_sdl_render_sdlrender_sdldestroytexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderFillRect, arginfo_sdl3_sdl_render_sdlrender_sdlrenderfillrect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetRenderViewport, arginfo_sdl3_sdl_render_sdlrender_sdlsetrenderviewport, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetRenderClipRect, arginfo_sdl3_sdl_render_sdlrender_sdlsetrendercliprect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderReadPixels, arginfo_sdl3_sdl_render_sdlrender_sdlrenderreadpixels, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLUpdateTextureFromSurface, arginfo_sdl3_sdl_render_sdlrender_sdlupdatetexturefromsurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderDebugText, arginfo_sdl3_sdl_render_sdlrender_sdlrenderdebugtext, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetRenderScale, arginfo_sdl3_sdl_render_sdlrender_sdlsetrenderscale, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderTextureAffine, arginfo_sdl3_sdl_render_sdlrender_sdlrendertextureaffine, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderFillRects, arginfo_sdl3_sdl_render_sdlrender_sdlrenderfillrects, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderRects, arginfo_sdl3_sdl_render_sdlrender_sdlrenderrects, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderLine, arginfo_sdl3_sdl_render_sdlrender_sdlrenderline, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderRect, arginfo_sdl3_sdl_render_sdlrender_sdlrenderrect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderPoints, arginfo_sdl3_sdl_render_sdlrender_sdlrenderpoints, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderGeometry, arginfo_sdl3_sdl_render_sdlrender_sdlrendergeometry, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderLines, arginfo_sdl3_sdl_render_sdlrender_sdlrenderlines, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetNumRenderDrivers, arginfo_sdl3_sdl_render_sdlrender_sdlgetnumrenderdrivers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderDriver, arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderdriver, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLCreateRendererWithProperties, arginfo_sdl3_sdl_render_sdlrender_sdlcreaterendererwithproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderer, arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderWindow, arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderwindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRendererName, arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderername, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRendererProperties, arginfo_sdl3_sdl_render_sdlrender_sdlgetrendererproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderOutputSize, arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderoutputsize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetCurrentRenderOutputSize, arginfo_sdl3_sdl_render_sdlrender_sdlgetcurrentrenderoutputsize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLCreateTextureWithProperties, arginfo_sdl3_sdl_render_sdlrender_sdlcreatetexturewithproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRendererFromTexture, arginfo_sdl3_sdl_render_sdlrender_sdlgetrendererfromtexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetTexturePalette, arginfo_sdl3_sdl_render_sdlrender_sdlsettexturepalette, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetTexturePalette, arginfo_sdl3_sdl_render_sdlrender_sdlgettexturepalette, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetTextureColorMod, arginfo_sdl3_sdl_render_sdlrender_sdlsettexturecolormod, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetTextureColorMod, arginfo_sdl3_sdl_render_sdlrender_sdlgettexturecolormod, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetTextureColorModFloat, arginfo_sdl3_sdl_render_sdlrender_sdlgettexturecolormodfloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetTextureAlphaMod, arginfo_sdl3_sdl_render_sdlrender_sdlsettexturealphamod, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetTextureAlphaModFloat, arginfo_sdl3_sdl_render_sdlrender_sdlsettexturealphamodfloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetTextureAlphaMod, arginfo_sdl3_sdl_render_sdlrender_sdlgettexturealphamod, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetTextureAlphaModFloat, arginfo_sdl3_sdl_render_sdlrender_sdlgettexturealphamodfloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetTextureBlendMode, arginfo_sdl3_sdl_render_sdlrender_sdlsettextureblendmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetTextureBlendMode, arginfo_sdl3_sdl_render_sdlrender_sdlgettextureblendmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetTextureScaleMode, arginfo_sdl3_sdl_render_sdlrender_sdlgettexturescalemode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLUpdateTexture, arginfo_sdl3_sdl_render_sdlrender_sdlupdatetexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLUpdateYUVTexture, arginfo_sdl3_sdl_render_sdlrender_sdlupdateyuvtexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLUpdateNVTexture, arginfo_sdl3_sdl_render_sdlrender_sdlupdatenvtexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLLockTexture, arginfo_sdl3_sdl_render_sdlrender_sdllocktexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetRenderTarget, arginfo_sdl3_sdl_render_sdlrender_sdlsetrendertarget, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderTarget, arginfo_sdl3_sdl_render_sdlrender_sdlgetrendertarget, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderLogicalPresentation, arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderlogicalpresentation, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderLogicalPresentationRect, arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderlogicalpresentationrect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderCoordinatesFromWindow, arginfo_sdl3_sdl_render_sdlrender_sdlrendercoordinatesfromwindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderCoordinatesToWindow, arginfo_sdl3_sdl_render_sdlrender_sdlrendercoordinatestowindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLConvertEventToRenderCoordinates, arginfo_sdl3_sdl_render_sdlrender_sdlconverteventtorendercoordinates, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderViewport, arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderviewport, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderViewportSet, arginfo_sdl3_sdl_render_sdlrender_sdlrenderviewportset, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderSafeArea, arginfo_sdl3_sdl_render_sdlrender_sdlgetrendersafearea, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderClipRect, arginfo_sdl3_sdl_render_sdlrender_sdlgetrendercliprect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderClipEnabled, arginfo_sdl3_sdl_render_sdlrender_sdlrenderclipenabled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderScale, arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderscale, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderDrawColor, arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderdrawcolor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderDrawColorFloat, arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderdrawcolorfloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetRenderColorScale, arginfo_sdl3_sdl_render_sdlrender_sdlsetrendercolorscale, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderColorScale, arginfo_sdl3_sdl_render_sdlrender_sdlgetrendercolorscale, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetRenderDrawBlendMode, arginfo_sdl3_sdl_render_sdlrender_sdlsetrenderdrawblendmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderDrawBlendMode, arginfo_sdl3_sdl_render_sdlrender_sdlgetrenderdrawblendmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderPoint, arginfo_sdl3_sdl_render_sdlrender_sdlrenderpoint, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderTextureTiled, arginfo_sdl3_sdl_render_sdlrender_sdlrendertexturetiled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderTexture9Grid, arginfo_sdl3_sdl_render_sdlrender_sdlrendertexture9grid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderTexture9GridTiled, arginfo_sdl3_sdl_render_sdlrender_sdlrendertexture9gridtiled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLRenderGeometryRaw, arginfo_sdl3_sdl_render_sdlrender_sdlrendergeometryraw, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetRenderTextureAddressMode, arginfo_sdl3_sdl_render_sdlrender_sdlsetrendertextureaddressmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderTextureAddressMode, arginfo_sdl3_sdl_render_sdlrender_sdlgetrendertextureaddressmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLFlushRenderer, arginfo_sdl3_sdl_render_sdlrender_sdlflushrenderer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderMetalLayer, arginfo_sdl3_sdl_render_sdlrender_sdlgetrendermetallayer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderMetalCommandEncoder, arginfo_sdl3_sdl_render_sdlrender_sdlgetrendermetalcommandencoder, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLAddVulkanRenderSemaphores, arginfo_sdl3_sdl_render_sdlrender_sdladdvulkanrendersemaphores, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetRenderVSync, arginfo_sdl3_sdl_render_sdlrender_sdlsetrendervsync, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetRenderVSync, arginfo_sdl3_sdl_render_sdlrender_sdlgetrendervsync, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLSetDefaultTextureScaleMode, arginfo_sdl3_sdl_render_sdlrender_sdlsetdefaulttexturescalemode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Render_SDLRender, SDLGetDefaultTextureScaleMode, arginfo_sdl3_sdl_render_sdlrender_sdlgetdefaulttexturescalemode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
