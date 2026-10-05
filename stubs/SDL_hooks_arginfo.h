/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 52647254c4461791a10246d031bc29342fd8c765 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GL_SetAttribute, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, attr, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_GL_CreateContext, 0, 1, SDL_GLContext, 1)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GL_MakeCurrent, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_OBJ_INFO(0, context, SDL_GLContext, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GL_SwapWindow, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GL_SetSwapInterval, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, interval, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GL_DestroyContext, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, context, SDL_GLContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_Metal_CreateView, 0, 1, SDL_MetalView, 1)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_Metal_GetLayer, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, view, SDL_MetalView, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_Metal_DestroyView, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, view, SDL_MetalView, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_Vulkan_GetInstanceExtensions, 0, 0, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_Vulkan_CreateSurface, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, instance, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, allocator, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, surface, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_Vulkan_DestroySurface, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, instance, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, allocator, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_GLContext___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_GLContext_pointer, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_GLContext_fromPointer, 0, 1, IS_STATIC, 0)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_SDL_MetalView___construct arginfo_class_SDL_GLContext___construct

#define arginfo_class_SDL_MetalView_pointer arginfo_class_SDL_GLContext_pointer

#define arginfo_class_SDL_MetalView_fromPointer arginfo_class_SDL_GLContext_fromPointer

ZEND_FUNCTION(SDL_GL_SetAttribute);
ZEND_FUNCTION(SDL_GL_CreateContext);
ZEND_FUNCTION(SDL_GL_MakeCurrent);
ZEND_FUNCTION(SDL_GL_SwapWindow);
ZEND_FUNCTION(SDL_GL_SetSwapInterval);
ZEND_FUNCTION(SDL_GL_DestroyContext);
ZEND_FUNCTION(SDL_Metal_CreateView);
ZEND_FUNCTION(SDL_Metal_GetLayer);
ZEND_FUNCTION(SDL_Metal_DestroyView);
ZEND_FUNCTION(SDL_Vulkan_GetInstanceExtensions);
ZEND_FUNCTION(SDL_Vulkan_CreateSurface);
ZEND_FUNCTION(SDL_Vulkan_DestroySurface);
ZEND_METHOD(SDL_GLContext, __construct);
ZEND_METHOD(SDL_GLContext, pointer);
ZEND_METHOD(SDL_GLContext, fromPointer);
ZEND_METHOD(SDL_MetalView, __construct);
ZEND_METHOD(SDL_MetalView, pointer);
ZEND_METHOD(SDL_MetalView, fromPointer);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(SDL_GL_SetAttribute, arginfo_SDL_GL_SetAttribute)
	ZEND_FE(SDL_GL_CreateContext, arginfo_SDL_GL_CreateContext)
	ZEND_FE(SDL_GL_MakeCurrent, arginfo_SDL_GL_MakeCurrent)
	ZEND_FE(SDL_GL_SwapWindow, arginfo_SDL_GL_SwapWindow)
	ZEND_FE(SDL_GL_SetSwapInterval, arginfo_SDL_GL_SetSwapInterval)
	ZEND_FE(SDL_GL_DestroyContext, arginfo_SDL_GL_DestroyContext)
	ZEND_FE(SDL_Metal_CreateView, arginfo_SDL_Metal_CreateView)
	ZEND_FE(SDL_Metal_GetLayer, arginfo_SDL_Metal_GetLayer)
	ZEND_FE(SDL_Metal_DestroyView, arginfo_SDL_Metal_DestroyView)
	ZEND_FE(SDL_Vulkan_GetInstanceExtensions, arginfo_SDL_Vulkan_GetInstanceExtensions)
	ZEND_FE(SDL_Vulkan_CreateSurface, arginfo_SDL_Vulkan_CreateSurface)
	ZEND_FE(SDL_Vulkan_DestroySurface, arginfo_SDL_Vulkan_DestroySurface)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_GLContext_methods[] = {
	ZEND_ME(SDL_GLContext, __construct, arginfo_class_SDL_GLContext___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SDL_GLContext, pointer, arginfo_class_SDL_GLContext_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_GLContext, fromPointer, arginfo_class_SDL_GLContext_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_MetalView_methods[] = {
	ZEND_ME(SDL_MetalView, __construct, arginfo_class_SDL_MetalView___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SDL_MetalView, pointer, arginfo_class_SDL_MetalView_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_MetalView, fromPointer, arginfo_class_SDL_MetalView_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static void register_SDL_hooks_symbols(int module_number)
{
	REGISTER_LONG_CONSTANT("SDL_GL_RED_SIZE", SDL_GL_RED_SIZE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_GREEN_SIZE", SDL_GL_GREEN_SIZE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_BLUE_SIZE", SDL_GL_BLUE_SIZE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_ALPHA_SIZE", SDL_GL_ALPHA_SIZE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_DEPTH_SIZE", SDL_GL_DEPTH_SIZE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_STENCIL_SIZE", SDL_GL_STENCIL_SIZE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_DOUBLEBUFFER", SDL_GL_DOUBLEBUFFER, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_MULTISAMPLEBUFFERS", SDL_GL_MULTISAMPLEBUFFERS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_MULTISAMPLESAMPLES", SDL_GL_MULTISAMPLESAMPLES, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_CONTEXT_MAJOR_VERSION", SDL_GL_CONTEXT_MAJOR_VERSION, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_CONTEXT_MINOR_VERSION", SDL_GL_CONTEXT_MINOR_VERSION, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_CONTEXT_PROFILE_MASK", SDL_GL_CONTEXT_PROFILE_MASK, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_CONTEXT_FLAGS", SDL_GL_CONTEXT_FLAGS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_CONTEXT_PROFILE_CORE", SDL_GL_CONTEXT_PROFILE_CORE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_CONTEXT_PROFILE_ES", SDL_GL_CONTEXT_PROFILE_ES, CONST_PERSISTENT);
}

static zend_class_entry *register_class_SDL_GLContext(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_GLContext", class_SDL_GLContext_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_SDL_MetalView(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_MetalView", class_SDL_MetalView_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}
