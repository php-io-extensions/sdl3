
extern zend_class_entry *sdl3_sdl_events_sdlevents_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLEvents);

PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLReadEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLPollEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLWaitEventTimeout);
PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLWaitEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLPeepEvents);
PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLHasEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLHasEvents);
PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLFlushEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLFlushEvents);
PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLPushEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLFreeEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLPumpEvents);
PHP_METHOD(Sdl3_SDL_Events_SDLEvents, SDLGetKeyboardState);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlevents_sdlreadevent, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlevents_sdlpollevent, 0, 0, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlevents_sdlwaiteventtimeout, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, timeout_ms, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlevents_sdlwaitevent, 0, 0, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlevents_sdlpeepevents, 0, 3, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, action, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, min_type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, max_type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, numevents, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlevents_sdlhasevent, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlevents_sdlhasevents, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, min_type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, max_type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlevents_sdlflushevent, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlevents_sdlflushevents, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, min_type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, max_type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlevents_sdlpushevent, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, event_ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlevents_sdlfreeevent, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlevents_sdlpumpevents, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlevents_sdlgetkeyboardstate, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_events_sdlevents_method_entry) {
	PHP_ME(Sdl3_SDL_Events_SDLEvents, SDLReadEvent, arginfo_sdl3_sdl_events_sdlevents_sdlreadevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEvents, SDLPollEvent, arginfo_sdl3_sdl_events_sdlevents_sdlpollevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEvents, SDLWaitEventTimeout, arginfo_sdl3_sdl_events_sdlevents_sdlwaiteventtimeout, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEvents, SDLWaitEvent, arginfo_sdl3_sdl_events_sdlevents_sdlwaitevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEvents, SDLPeepEvents, arginfo_sdl3_sdl_events_sdlevents_sdlpeepevents, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEvents, SDLHasEvent, arginfo_sdl3_sdl_events_sdlevents_sdlhasevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEvents, SDLHasEvents, arginfo_sdl3_sdl_events_sdlevents_sdlhasevents, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEvents, SDLFlushEvent, arginfo_sdl3_sdl_events_sdlevents_sdlflushevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEvents, SDLFlushEvents, arginfo_sdl3_sdl_events_sdlevents_sdlflushevents, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEvents, SDLPushEvent, arginfo_sdl3_sdl_events_sdlevents_sdlpushevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEvents, SDLFreeEvent, arginfo_sdl3_sdl_events_sdlevents_sdlfreeevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEvents, SDLPumpEvents, arginfo_sdl3_sdl_events_sdlevents_sdlpumpevents, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLEvents, SDLGetKeyboardState, arginfo_sdl3_sdl_events_sdlevents_sdlgetkeyboardstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
