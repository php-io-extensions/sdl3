#include "runtime.h"
#include <SDL3/SDL_metal.h>
#include <SDL3/SDL_vulkan.h>
#include "../stubs/SDL_hooks_arginfo.h"

zend_class_entry *sdl3_ce_SDL_GLContext;
zend_class_entry *sdl3_ce_SDL_MetalView;

SDL3_POINTER_METHODS(SDL_GLContext)
SDL3_POINTER_METHODS(SDL_MetalView)

static void *sdl3_address(zend_long value, bool is_null, uint32_t arg_num, bool optional)
{
	if (is_null || value == 0) {
		if (optional) {
			return NULL;
		}
		zend_argument_value_error(arg_num, "must not be a null address");
		return NULL;
	}

	return (void *) (uintptr_t) value;
}

ZEND_FUNCTION(SDL_GL_SetAttribute)
{
	zend_long attr, value;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(attr)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_GL_SetAttribute((SDL_GLAttr) attr, (int) value));
}

ZEND_FUNCTION(SDL_GL_CreateContext)
{
	zval *window_zv;
	SDL_Window *window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	sdl3_box(return_value, SDL_GL_CreateContext(window), sdl3_ce_SDL_GLContext);
}

ZEND_FUNCTION(SDL_GL_MakeCurrent)
{
	zval *window_zv;
	zend_object *context = NULL;
	SDL_Window *window;
	SDL_GLContext native = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(context, sdl3_ce_SDL_GLContext)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}
	if (context != NULL) {
		zval context_zv;
		ZVAL_OBJ(&context_zv, context);
		native = sdl3_handle_ptr(&context_zv, sdl3_ce_SDL_GLContext, 2);
		if (native == NULL) {
			RETURN_THROWS();
		}
	}

	RETURN_BOOL(SDL_GL_MakeCurrent(window, native));
}

ZEND_FUNCTION(SDL_GL_SwapWindow)
{
	zval *window_zv;
	SDL_Window *window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_GL_SwapWindow(window));
}

ZEND_FUNCTION(SDL_GL_SetSwapInterval)
{
	zend_long interval;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(interval)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_GL_SetSwapInterval((int) interval));
}

ZEND_FUNCTION(SDL_GL_DestroyContext)
{
	zval *context_zv;
	SDL_GLContext context;
	bool destroyed;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(context_zv, sdl3_ce_SDL_GLContext)
	ZEND_PARSE_PARAMETERS_END();

	context = sdl3_handle_ptr(context_zv, sdl3_ce_SDL_GLContext, 1);
	if (context == NULL) {
		RETURN_THROWS();
	}

	destroyed = SDL_GL_DestroyContext(context);
	sdl3_release(Z_OBJ_P(context_zv));
	RETURN_BOOL(destroyed);
}

ZEND_FUNCTION(SDL_Metal_CreateView)
{
	zval *window_zv;
	SDL_Window *window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	sdl3_box(return_value, SDL_Metal_CreateView(window), sdl3_ce_SDL_MetalView);
}

ZEND_FUNCTION(SDL_Metal_GetLayer)
{
	zval *view_zv;
	SDL_MetalView view;
	void *layer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(view_zv, sdl3_ce_SDL_MetalView)
	ZEND_PARSE_PARAMETERS_END();

	view = sdl3_handle_ptr(view_zv, sdl3_ce_SDL_MetalView, 1);
	if (view == NULL) {
		RETURN_THROWS();
	}

	layer = SDL_Metal_GetLayer(view);
	RETURN_LONG((zend_long) (uintptr_t) layer);
}

ZEND_FUNCTION(SDL_Metal_DestroyView)
{
	zval *view_zv;
	SDL_MetalView view;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(view_zv, sdl3_ce_SDL_MetalView)
	ZEND_PARSE_PARAMETERS_END();

	view = sdl3_handle_ptr(view_zv, sdl3_ce_SDL_MetalView, 1);
	if (view == NULL) {
		RETURN_THROWS();
	}

	SDL_Metal_DestroyView(view);
	sdl3_release(Z_OBJ_P(view_zv));
}

ZEND_FUNCTION(SDL_Vulkan_GetInstanceExtensions)
{
	Uint32 count = 0;
	char const * const *extensions;
	uint32_t i;

	ZEND_PARSE_PARAMETERS_NONE();

	extensions = SDL_Vulkan_GetInstanceExtensions(&count);
	if (extensions == NULL) {
		RETURN_NULL();
	}

	array_init_size(return_value, count);
	for (i = 0; i < count; i++) {
		add_next_index_string(return_value, extensions[i] != NULL ? extensions[i] : "");
	}
}

ZEND_FUNCTION(SDL_Vulkan_CreateSurface)
{
	zval *window_zv, *surface_zv;
	zend_long instance, allocator_value;
	bool allocator_null;
	SDL_Window *window;
	void *instance_ptr, *allocator;
	VkSurfaceKHR surface = (VkSurfaceKHR) 0;
	bool created;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_LONG(instance)
		Z_PARAM_LONG_OR_NULL(allocator_value, allocator_null)
		Z_PARAM_ZVAL(surface_zv)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	instance_ptr = sdl3_address(instance, false, 2, false);
	allocator = sdl3_address(allocator_value, allocator_null, 3, true);
	if (window == NULL || EG(exception)) {
		RETURN_THROWS();
	}

	created = SDL_Vulkan_CreateSurface(window, (VkInstance) instance_ptr,
		(const struct VkAllocationCallbacks *) allocator, &surface);
	if (created) {
		ZEND_TRY_ASSIGN_REF_LONG(surface_zv, (zend_long) (uintptr_t) surface);
		if (EG(exception)) {
			RETURN_THROWS();
		}
	}
	RETURN_BOOL(created);
}

ZEND_FUNCTION(SDL_Vulkan_DestroySurface)
{
	zend_long instance, surface, allocator_value;
	bool allocator_null;
	void *instance_ptr, *allocator;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(instance)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG_OR_NULL(allocator_value, allocator_null)
	ZEND_PARSE_PARAMETERS_END();

	instance_ptr = sdl3_address(instance, false, 1, false);
	allocator = sdl3_address(allocator_value, allocator_null, 3, true);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	if (surface == 0) {
		zend_argument_value_error(2, "must not be a null address");
		RETURN_THROWS();
	}

	SDL_Vulkan_DestroySurface((VkInstance) instance_ptr, (VkSurfaceKHR) (uintptr_t) surface,
		(const struct VkAllocationCallbacks *) allocator);
}

void sdl3_register_SDL_hooks(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	register_SDL_hooks_symbols(module_number);

	sdl3_ce_SDL_GLContext = register_class_SDL_GLContext();
	sdl3_handle_setup(sdl3_ce_SDL_GLContext);
	sdl3_ce_SDL_MetalView = register_class_SDL_MetalView();
	sdl3_handle_setup(sdl3_ce_SDL_MetalView);
}
