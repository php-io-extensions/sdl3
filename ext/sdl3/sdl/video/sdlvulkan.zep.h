
extern zend_class_entry *sdl3_sdl_video_sdlvulkan_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Video_SDLVulkan);

PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanLoadLibrary);
PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanUnloadLibrary);
PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanGetVkGetInstanceProcAddr);
PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanGetInstanceExtensions);
PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanCreateSurface);
PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanDestroySurface);
PHP_METHOD(Sdl3_SDL_Video_SDLVulkan, SDLVulkanGetPresentationSupport);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkanloadlibrary, 0, 0, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkanunloadlibrary, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkangetvkgetinstanceprocaddr, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkangetinstanceextensions, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkancreatesurface, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, allocator, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkandestroysurface, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, instance, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, allocator, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkangetpresentationsupport, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, instance, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, physical_device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, queue_family_index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_video_sdlvulkan_method_entry) {
	PHP_ME(Sdl3_SDL_Video_SDLVulkan, SDLVulkanLoadLibrary, arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkanloadlibrary, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVulkan, SDLVulkanUnloadLibrary, arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkanunloadlibrary, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVulkan, SDLVulkanGetVkGetInstanceProcAddr, arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkangetvkgetinstanceprocaddr, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVulkan, SDLVulkanGetInstanceExtensions, arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkangetinstanceextensions, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVulkan, SDLVulkanCreateSurface, arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkancreatesurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVulkan, SDLVulkanDestroySurface, arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkandestroysurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Video_SDLVulkan, SDLVulkanGetPresentationSupport, arginfo_sdl3_sdl_video_sdlvulkan_sdlvulkangetpresentationsupport, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
