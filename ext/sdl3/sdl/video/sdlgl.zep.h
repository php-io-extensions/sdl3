
extern zend_class_entry *sdl3_sdl_video_sdlgl_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Video_SDLGL);

PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLLoadLibrary);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLGetProcAddress);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLUnloadLibrary);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLExtensionSupported);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLResetAttributes);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLSetAttribute);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLGetAttribute);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLCreateContext);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLMakeCurrent);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLGetCurrentWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLGetCurrentContext);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLSetSwapInterval);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLGetSwapInterval);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLSwapWindow);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLGLDestroyContext);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLEGLGetProcAddress);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLEGLGetCurrentDisplay);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLEGLGetCurrentConfig);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLEGLGetWindowSurface);
PHP_METHOD(Sdl3_SDL_Video_SDLGL, SDLEGLSetAttributeCallbacks);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglloadlibrary, 0, 0, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglgetprocaddress, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, proc, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglunloadlibrary, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglextensionsupported, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, extension, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglresetattributes, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglsetattribute, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, attr, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglgetattribute, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, attr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglcreatecontext, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglmakecurrent, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, context, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglgetcurrentwindow, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglgetcurrentcontext, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglsetswapinterval, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, interval, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglgetswapinterval, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlglswapwindow, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdlgldestroycontext, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, context, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdleglgetprocaddress, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, proc, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdleglgetcurrentdisplay, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdleglgetcurrentconfig, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdleglgetwindowsurface, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlgl_sdleglsetattributecallbacks, 0, 0, IS_VOID, 0)

	ZEND_ARG_INFO(0, platformCallback)
	ZEND_ARG_INFO(0, surfaceCallback)
	ZEND_ARG_INFO(0, contextCallback)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_video_sdlgl_method_entry) {
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLLoadLibrary, arginfo_sdl3_sdl_video_sdlgl_sdlglloadlibrary, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLGetProcAddress, arginfo_sdl3_sdl_video_sdlgl_sdlglgetprocaddress, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLUnloadLibrary, arginfo_sdl3_sdl_video_sdlgl_sdlglunloadlibrary, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLExtensionSupported, arginfo_sdl3_sdl_video_sdlgl_sdlglextensionsupported, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLResetAttributes, arginfo_sdl3_sdl_video_sdlgl_sdlglresetattributes, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLSetAttribute, arginfo_sdl3_sdl_video_sdlgl_sdlglsetattribute, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLGetAttribute, arginfo_sdl3_sdl_video_sdlgl_sdlglgetattribute, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLCreateContext, arginfo_sdl3_sdl_video_sdlgl_sdlglcreatecontext, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLMakeCurrent, arginfo_sdl3_sdl_video_sdlgl_sdlglmakecurrent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLGetCurrentWindow, arginfo_sdl3_sdl_video_sdlgl_sdlglgetcurrentwindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLGetCurrentContext, arginfo_sdl3_sdl_video_sdlgl_sdlglgetcurrentcontext, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLSetSwapInterval, arginfo_sdl3_sdl_video_sdlgl_sdlglsetswapinterval, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLGetSwapInterval, arginfo_sdl3_sdl_video_sdlgl_sdlglgetswapinterval, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLSwapWindow, arginfo_sdl3_sdl_video_sdlgl_sdlglswapwindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLGLDestroyContext, arginfo_sdl3_sdl_video_sdlgl_sdlgldestroycontext, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLEGLGetProcAddress, arginfo_sdl3_sdl_video_sdlgl_sdleglgetprocaddress, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLEGLGetCurrentDisplay, arginfo_sdl3_sdl_video_sdlgl_sdleglgetcurrentdisplay, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLEGLGetCurrentConfig, arginfo_sdl3_sdl_video_sdlgl_sdleglgetcurrentconfig, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLEGLGetWindowSurface, arginfo_sdl3_sdl_video_sdlgl_sdleglgetwindowsurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLGL, SDLEGLSetAttributeCallbacks, arginfo_sdl3_sdl_video_sdlgl_sdleglsetattributecallbacks, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
