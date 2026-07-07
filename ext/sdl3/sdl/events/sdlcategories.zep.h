
extern zend_class_entry *sdl3_sdl_events_sdlcategories_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLCategories);

PHP_METHOD(Sdl3_SDL_Events_SDLCategories, SDLSetEventEnabled);
PHP_METHOD(Sdl3_SDL_Events_SDLCategories, SDLEventEnabled);
PHP_METHOD(Sdl3_SDL_Events_SDLCategories, SDLRegisterEvents);
PHP_METHOD(Sdl3_SDL_Events_SDLCategories, SDLGetWindowFromEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLCategories, SDLGetEventDescription);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlcategories_sdlseteventenabled, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, enabled, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlcategories_sdleventenabled, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlcategories_sdlregisterevents, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, numevents, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlcategories_sdlgetwindowfromevent, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, event_ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlcategories_sdlgeteventdescription, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, event_ptr, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buflen, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_events_sdlcategories_method_entry) {
	PHP_ME(Sdl3_SDL_Events_SDLCategories, SDLSetEventEnabled, arginfo_sdl3_sdl_events_sdlcategories_sdlseteventenabled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLCategories, SDLEventEnabled, arginfo_sdl3_sdl_events_sdlcategories_sdleventenabled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLCategories, SDLRegisterEvents, arginfo_sdl3_sdl_events_sdlcategories_sdlregisterevents, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLCategories, SDLGetWindowFromEvent, arginfo_sdl3_sdl_events_sdlcategories_sdlgetwindowfromevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLCategories, SDLGetEventDescription, arginfo_sdl3_sdl_events_sdlcategories_sdlgeteventdescription, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
