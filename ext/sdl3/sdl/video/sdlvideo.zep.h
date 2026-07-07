
extern zend_class_entry *sdl3_sdl_video_sdlvideo_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Video_SDLVideo);

PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetNumVideoDrivers);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetVideoDriver);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetCurrentVideoDriver);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetSystemTheme);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetDisplayProperties);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetDisplayUsableBounds);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetDisplayForPoint);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetDisplayForRect);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLCreateWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLCreatePopupWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLCreateWindowWithProperties);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowID);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowFromID);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowParent);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowProperties);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowFlags);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindows);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowPixelDensity);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowDisplayScale);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowFullscreenMode);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowFullscreenMode);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowICCProfile);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowPixelFormat);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowTitle);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowTitle);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowIcon);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowPosition);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowPosition);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowSize);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSize);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSafeArea);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowAspectRatio);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowAspectRatio);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowBordersSize);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSizeInPixels);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowMinimumSize);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowMinimumSize);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowMaximumSize);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowMaximumSize);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowBordered);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowResizable);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowAlwaysOnTop);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowFillDocument);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLShowWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLHideWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLRaiseWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLMaximizeWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLMinimizeWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLRestoreWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowFullscreen);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSyncWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLWindowHasSurface);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSurface);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowSurfaceVSync);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSurfaceVSync);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLUpdateWindowSurface);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLUpdateWindowSurfaceRects);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLDestroyWindowSurface);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowKeyboardGrab);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowMouseGrab);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowKeyboardGrab);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowMouseGrab);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetGrabbedWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowMouseRect);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowMouseRect);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowOpacity);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowOpacity);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowParent);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowModal);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowFocusable);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLShowWindowSystemMenu);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowHitTest);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowShape);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLFlashWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowProgressState);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowProgressState);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLSetWindowProgressValue);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLGetWindowProgressValue);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLScreenSaverEnabled);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLEnableScreenSaver);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLDisableScreenSaver);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLDestroyWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLVideo, SDLCreateWindowAndRenderer);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetnumvideodrivers, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetvideodriver, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetcurrentvideodriver, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetsystemtheme, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetdisplayproperties, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, display_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetdisplayusablebounds, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, display_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetdisplayforpoint, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetdisplayforrect, 0, 1, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlcreatewindow, 0, 4, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlcreatepopupwindow, 0, 6, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, parent, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlcreatewindowwithproperties, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowfromid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowparent, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowproperties, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowflags, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindows, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowpixeldensity, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowdisplayscale, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowfullscreenmode, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, mode, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowfullscreenmode, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowiccprofile, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowpixelformat, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowtitle, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowtitle, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowicon, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowposition, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowposition, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowsize, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowsize, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowsafearea, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowaspectratio, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, min_aspect, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, max_aspect, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowaspectratio, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowborderssize, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowsizeinpixels, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowminimumsize, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, min_w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, min_h, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowminimumsize, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowmaximumsize, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, max_w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, max_h, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowmaximumsize, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowbordered, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bordered, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowresizable, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, resizable, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowalwaysontop, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, on_top, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowfilldocument, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fill, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlshowwindow, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlhidewindow, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlraisewindow, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlmaximizewindow, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlminimizewindow, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlrestorewindow, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowfullscreen, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fullscreen, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsyncwindow, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlwindowhassurface, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowsurface, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowsurfacevsync, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, vsync, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowsurfacevsync, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlupdatewindowsurface, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlupdatewindowsurfacerects, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, rects, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdldestroywindowsurface, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowkeyboardgrab, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, grabbed, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowmousegrab, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, grabbed, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowkeyboardgrab, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowmousegrab, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetgrabbedwindow, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowmouserect, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowmouserect, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowopacity, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, opacity, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowopacity, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowparent, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, parent)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowmodal, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, modal, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowfocusable, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, focusable, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlshowwindowsystemmenu, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowhittest, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowshape, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, shape)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlflashwindow, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, operation, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowprogressstate, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, state, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowprogressstate, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowprogressvalue, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowprogressvalue, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlscreensaverenabled, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlenablescreensaver, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdldisablescreensaver, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdldestroywindow, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvideo_sdlcreatewindowandrenderer, 0, 4, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_video_sdlvideo_method_entry) {
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetNumVideoDrivers, arginfo_sdl3_sdl_video_sdlvideo_sdlgetnumvideodrivers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetVideoDriver, arginfo_sdl3_sdl_video_sdlvideo_sdlgetvideodriver, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetCurrentVideoDriver, arginfo_sdl3_sdl_video_sdlvideo_sdlgetcurrentvideodriver, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetSystemTheme, arginfo_sdl3_sdl_video_sdlvideo_sdlgetsystemtheme, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetDisplayProperties, arginfo_sdl3_sdl_video_sdlvideo_sdlgetdisplayproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetDisplayUsableBounds, arginfo_sdl3_sdl_video_sdlvideo_sdlgetdisplayusablebounds, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetDisplayForPoint, arginfo_sdl3_sdl_video_sdlvideo_sdlgetdisplayforpoint, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetDisplayForRect, arginfo_sdl3_sdl_video_sdlvideo_sdlgetdisplayforrect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLCreateWindow, arginfo_sdl3_sdl_video_sdlvideo_sdlcreatewindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLCreatePopupWindow, arginfo_sdl3_sdl_video_sdlvideo_sdlcreatepopupwindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLCreateWindowWithProperties, arginfo_sdl3_sdl_video_sdlvideo_sdlcreatewindowwithproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowID, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowFromID, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowfromid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowParent, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowparent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowProperties, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowFlags, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowflags, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindows, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindows, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowPixelDensity, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowpixeldensity, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowDisplayScale, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowdisplayscale, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowFullscreenMode, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowfullscreenmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowFullscreenMode, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowfullscreenmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowICCProfile, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowiccprofile, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowPixelFormat, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowpixelformat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowTitle, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowtitle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowTitle, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowtitle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowIcon, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowicon, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowPosition, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowposition, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowPosition, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowposition, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowSize, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowsize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSize, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowsize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSafeArea, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowsafearea, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowAspectRatio, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowaspectratio, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowAspectRatio, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowaspectratio, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowBordersSize, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowborderssize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSizeInPixels, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowsizeinpixels, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowMinimumSize, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowminimumsize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowMinimumSize, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowminimumsize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowMaximumSize, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowmaximumsize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowMaximumSize, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowmaximumsize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowBordered, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowbordered, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowResizable, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowresizable, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowAlwaysOnTop, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowalwaysontop, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowFillDocument, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowfilldocument, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLShowWindow, arginfo_sdl3_sdl_video_sdlvideo_sdlshowwindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLHideWindow, arginfo_sdl3_sdl_video_sdlvideo_sdlhidewindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLRaiseWindow, arginfo_sdl3_sdl_video_sdlvideo_sdlraisewindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLMaximizeWindow, arginfo_sdl3_sdl_video_sdlvideo_sdlmaximizewindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLMinimizeWindow, arginfo_sdl3_sdl_video_sdlvideo_sdlminimizewindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLRestoreWindow, arginfo_sdl3_sdl_video_sdlvideo_sdlrestorewindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowFullscreen, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowfullscreen, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSyncWindow, arginfo_sdl3_sdl_video_sdlvideo_sdlsyncwindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLWindowHasSurface, arginfo_sdl3_sdl_video_sdlvideo_sdlwindowhassurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSurface, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowsurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowSurfaceVSync, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowsurfacevsync, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowSurfaceVSync, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowsurfacevsync, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLUpdateWindowSurface, arginfo_sdl3_sdl_video_sdlvideo_sdlupdatewindowsurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLUpdateWindowSurfaceRects, arginfo_sdl3_sdl_video_sdlvideo_sdlupdatewindowsurfacerects, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLDestroyWindowSurface, arginfo_sdl3_sdl_video_sdlvideo_sdldestroywindowsurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowKeyboardGrab, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowkeyboardgrab, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowMouseGrab, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowmousegrab, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowKeyboardGrab, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowkeyboardgrab, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowMouseGrab, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowmousegrab, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetGrabbedWindow, arginfo_sdl3_sdl_video_sdlvideo_sdlgetgrabbedwindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowMouseRect, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowmouserect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowMouseRect, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowmouserect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowOpacity, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowopacity, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowOpacity, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowopacity, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowParent, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowparent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowModal, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowmodal, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowFocusable, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowfocusable, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLShowWindowSystemMenu, arginfo_sdl3_sdl_video_sdlvideo_sdlshowwindowsystemmenu, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowHitTest, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowhittest, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowShape, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowshape, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLFlashWindow, arginfo_sdl3_sdl_video_sdlvideo_sdlflashwindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowProgressState, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowprogressstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowProgressState, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowprogressstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLSetWindowProgressValue, arginfo_sdl3_sdl_video_sdlvideo_sdlsetwindowprogressvalue, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLGetWindowProgressValue, arginfo_sdl3_sdl_video_sdlvideo_sdlgetwindowprogressvalue, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLScreenSaverEnabled, arginfo_sdl3_sdl_video_sdlvideo_sdlscreensaverenabled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLEnableScreenSaver, arginfo_sdl3_sdl_video_sdlvideo_sdlenablescreensaver, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLDisableScreenSaver, arginfo_sdl3_sdl_video_sdlvideo_sdldisablescreensaver, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLDestroyWindow, arginfo_sdl3_sdl_video_sdlvideo_sdldestroywindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVideo, SDLCreateWindowAndRenderer, arginfo_sdl3_sdl_video_sdlvideo_sdlcreatewindowandrenderer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
