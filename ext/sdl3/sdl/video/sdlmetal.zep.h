
extern zend_class_entry *sdl3_sdl_video_sdlmetal_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Video_SDLMetal);

PHP_METHOD(Sdl3_SDL_Video_SDLMetal, SDLMetalCreateView);
PHP_METHOD(Sdl3_SDL_Video_SDLMetal, SDLMetalDestroyView);
PHP_METHOD(Sdl3_SDL_Video_SDLMetal, SDLMetalGetLayer);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlmetal_sdlmetalcreateview, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlmetal_sdlmetaldestroyview, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, view, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlmetal_sdlmetalgetlayer, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, view, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_video_sdlmetal_method_entry) {
	PHP_ME(Sdl3_SDL_Video_SDLMetal, SDLMetalCreateView, arginfo_sdl3_sdl_video_sdlmetal_sdlmetalcreateview, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLMetal, SDLMetalDestroyView, arginfo_sdl3_sdl_video_sdlmetal_sdlmetaldestroyview, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLMetal, SDLMetalGetLayer, arginfo_sdl3_sdl_video_sdlmetal_sdlmetalgetlayer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
