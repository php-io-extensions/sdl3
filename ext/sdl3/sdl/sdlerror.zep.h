
extern zend_class_entry *sdl3_sdl_sdlerror_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_SDLError);

PHP_METHOD(Sdl3_SDL_SDLError, SDLGetError);
PHP_METHOD(Sdl3_SDL_SDLError, SDLSetError);
PHP_METHOD(Sdl3_SDL_SDLError, SDLOutOfMemory);
PHP_METHOD(Sdl3_SDL_SDLError, SDLClearError);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlerror_sdlgeterror, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlerror_sdlseterror, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, message, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlerror_sdloutofmemory, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlerror_sdlclearerror, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_sdlerror_method_entry) {
	PHP_ME(Sdl3_SDL_SDLError, SDLGetError, arginfo_sdl3_sdl_sdlerror_sdlgeterror, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLError, SDLSetError, arginfo_sdl3_sdl_sdlerror_sdlseterror, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLError, SDLOutOfMemory, arginfo_sdl3_sdl_sdlerror_sdloutofmemory, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLError, SDLClearError, arginfo_sdl3_sdl_sdlerror_sdlclearerror, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
