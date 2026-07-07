
extern zend_class_entry *sdl3_sdl_events_sdldropevents_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLDropEvents);

PHP_METHOD(Sdl3_SDL_Events_SDLDropEvents, SDLReadDropEvent);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdldropevents_sdlreaddropevent, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_events_sdldropevents_method_entry) {
	PHP_ME(Sdl3_SDL_Events_SDLDropEvents, SDLReadDropEvent, arginfo_sdl3_sdl_events_sdldropevents_sdlreaddropevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
