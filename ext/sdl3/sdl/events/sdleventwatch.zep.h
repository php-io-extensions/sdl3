
extern zend_class_entry *sdl3_sdl_events_sdleventwatch_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLEventWatch);

PHP_METHOD(Sdl3_SDL_Events_SDLEventWatch, SDLSetEventFilter);
PHP_METHOD(Sdl3_SDL_Events_SDLEventWatch, SDLGetEventFilter);
PHP_METHOD(Sdl3_SDL_Events_SDLEventWatch, SDLAddEventWatch);
PHP_METHOD(Sdl3_SDL_Events_SDLEventWatch, SDLRemoveEventWatch);
PHP_METHOD(Sdl3_SDL_Events_SDLEventWatch, SDLFilterEvents);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdleventwatch_sdlseteventfilter, 0, 0, IS_VOID, 0)

	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdleventwatch_sdlgeteventfilter, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdleventwatch_sdladdeventwatch, 0, 1, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdleventwatch_sdlremoveeventwatch, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, watch_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdleventwatch_sdlfilterevents, 0, 1, IS_VOID, 0)

	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_events_sdleventwatch_method_entry) {
	PHP_ME(Sdl3_SDL_Events_SDLEventWatch, SDLSetEventFilter, arginfo_sdl3_sdl_events_sdleventwatch_sdlseteventfilter, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEventWatch, SDLGetEventFilter, arginfo_sdl3_sdl_events_sdleventwatch_sdlgeteventfilter, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEventWatch, SDLAddEventWatch, arginfo_sdl3_sdl_events_sdleventwatch_sdladdeventwatch, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEventWatch, SDLRemoveEventWatch, arginfo_sdl3_sdl_events_sdleventwatch_sdlremoveeventwatch, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEventWatch, SDLFilterEvents, arginfo_sdl3_sdl_events_sdleventwatch_sdlfilterevents, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
