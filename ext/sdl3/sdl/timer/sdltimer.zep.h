
extern zend_class_entry *sdl3_sdl_timer_sdltimer_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Timer_SDLTimer);

PHP_METHOD(Sdl3_SDL_Timer_SDLTimer, SDLDelay);
PHP_METHOD(Sdl3_SDL_Timer_SDLTimer, SDLGetTicks);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_timer_sdltimer_sdldelay, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, ms, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_timer_sdltimer_sdlgetticks, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_timer_sdltimer_method_entry) {
	PHP_ME(Sdl3_SDL_Timer_SDLTimer, SDLDelay, arginfo_sdl3_sdl_timer_sdltimer_sdldelay, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Timer_SDLTimer, SDLGetTicks, arginfo_sdl3_sdl_timer_sdltimer_sdlgetticks, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
