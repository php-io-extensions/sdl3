
extern zend_class_entry *sdl3_sdl_sdl_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_SDL);

PHP_METHOD(Sdl3_SDL_SDL, SDLInit);
PHP_METHOD(Sdl3_SDL_SDL, SDLInitSubSystem);
PHP_METHOD(Sdl3_SDL_SDL, SDLWasInit);
PHP_METHOD(Sdl3_SDL_SDL, SDLQuit);
PHP_METHOD(Sdl3_SDL_SDL, SDLQuitSubSystem);
PHP_METHOD(Sdl3_SDL_SDL, SDLExitProcess);
PHP_METHOD(Sdl3_SDL_SDL, SDLGetPixelFormatDetails);
PHP_METHOD(Sdl3_SDL_SDL, SDLGetRGBA);
PHP_METHOD(Sdl3_SDL_SDL, SDLMapRGBA);
PHP_METHOD(Sdl3_SDL_SDL, SDLGetSandbox);
PHP_METHOD(Sdl3_SDL_SDL, SDLGetVersion);
PHP_METHOD(Sdl3_SDL_SDL, SDLGetRevision);
PHP_METHOD(Sdl3_SDL_SDL, SDLGetPlatform);
PHP_METHOD(Sdl3_SDL_SDL, SDLIsTablet);
PHP_METHOD(Sdl3_SDL_SDL, SDLIsTV);
PHP_METHOD(Sdl3_SDL_SDL, SDLSetAppMetadata);
PHP_METHOD(Sdl3_SDL_SDL, SDLSetAppMetadataProperty);
PHP_METHOD(Sdl3_SDL_SDL, SDLGetAppMetadataProperty);
PHP_METHOD(Sdl3_SDL_SDL, SDLSetMainReady);
PHP_METHOD(Sdl3_SDL_SDL, SDLIsMainThread);
PHP_METHOD(Sdl3_SDL_SDL, SDLRand);
PHP_METHOD(Sdl3_SDL_SDL, SDLRandf);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlinit, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlinitsubsystem, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlwasinit, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlquit, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlquitsubsystem, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlexitprocess, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, exitcode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlgetpixelformatdetails, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlgetrgba, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, pixel, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format_ptr, IS_LONG, 0)
	ZEND_ARG_INFO(0, palette_ptr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlmaprgba, 0, 5, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format_ptr, IS_LONG, 0)
	ZEND_ARG_INFO(0, palette_ptr)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlgetsandbox, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlgetversion, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlgetrevision, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlgetplatform, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlistablet, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlistv, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlsetappmetadata, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, appname, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, appversion, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, appidentifier, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlsetappmetadataproperty, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlgetappmetadataproperty, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlsetmainready, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlismainthread, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlrand, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdl_sdlrandf, 0, 0, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_sdl_method_entry) {
	PHP_ME(Sdl3_SDL_SDL, SDLInit, arginfo_sdl3_sdl_sdl_sdlinit, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLInitSubSystem, arginfo_sdl3_sdl_sdl_sdlinitsubsystem, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLWasInit, arginfo_sdl3_sdl_sdl_sdlwasinit, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLQuit, arginfo_sdl3_sdl_sdl_sdlquit, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLQuitSubSystem, arginfo_sdl3_sdl_sdl_sdlquitsubsystem, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLExitProcess, arginfo_sdl3_sdl_sdl_sdlexitprocess, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLGetPixelFormatDetails, arginfo_sdl3_sdl_sdl_sdlgetpixelformatdetails, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLGetRGBA, arginfo_sdl3_sdl_sdl_sdlgetrgba, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLMapRGBA, arginfo_sdl3_sdl_sdl_sdlmaprgba, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLGetSandbox, arginfo_sdl3_sdl_sdl_sdlgetsandbox, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLGetVersion, arginfo_sdl3_sdl_sdl_sdlgetversion, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLGetRevision, arginfo_sdl3_sdl_sdl_sdlgetrevision, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLGetPlatform, arginfo_sdl3_sdl_sdl_sdlgetplatform, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLIsTablet, arginfo_sdl3_sdl_sdl_sdlistablet, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLIsTV, arginfo_sdl3_sdl_sdl_sdlistv, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLSetAppMetadata, arginfo_sdl3_sdl_sdl_sdlsetappmetadata, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLSetAppMetadataProperty, arginfo_sdl3_sdl_sdl_sdlsetappmetadataproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLGetAppMetadataProperty, arginfo_sdl3_sdl_sdl_sdlgetappmetadataproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLSetMainReady, arginfo_sdl3_sdl_sdl_sdlsetmainready, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLIsMainThread, arginfo_sdl3_sdl_sdl_sdlismainthread, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLRand, arginfo_sdl3_sdl_sdl_sdlrand, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDL, SDLRandf, arginfo_sdl3_sdl_sdl_sdlrandf, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
