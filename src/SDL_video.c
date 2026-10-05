#include "runtime.h"
#include "../stubs/SDL_video_arginfo.h"

zend_class_entry *sdl3_ce_SDL_Window;

SDL3_POINTER_METHODS(SDL_Window)

static bool sdl3_assign_wh(zval *w, zval *h, int width, int height)
{
	ZEND_TRY_ASSIGN_REF_LONG(w, width);
	if (EG(exception)) {
		return false;
	}
	ZEND_TRY_ASSIGN_REF_LONG(h, height);
	return EG(exception) == NULL;
}

ZEND_FUNCTION(SDL_CreateWindow)
{
	zend_string *title;
	zend_long w, h, flags;
	SDL_Window *window;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_STR(title)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();

	window = SDL_CreateWindow(ZSTR_VAL(title), (int) w, (int) h, (SDL_WindowFlags) flags);
	sdl3_box(return_value, window, sdl3_ce_SDL_Window);
}

ZEND_FUNCTION(SDL_CreateWindowWithProperties)
{
	zend_long props;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(props)
	ZEND_PARSE_PARAMETERS_END();

	sdl3_box(return_value, SDL_CreateWindowWithProperties((SDL_PropertiesID) props), sdl3_ce_SDL_Window);
}

ZEND_FUNCTION(SDL_DestroyWindow)
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

	SDL_DestroyWindow(window);
	sdl3_release(Z_OBJ_P(window_zv));
}

ZEND_FUNCTION(SDL_GetWindowID)
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

	RETURN_LONG(SDL_GetWindowID(window));
}

ZEND_FUNCTION(SDL_GetWindowFromID)
{
	zend_long id;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(id)
	ZEND_PARSE_PARAMETERS_END();

	sdl3_box(return_value, SDL_GetWindowFromID((SDL_WindowID) id), sdl3_ce_SDL_Window);
}

ZEND_FUNCTION(SDL_SetWindowTitle)
{
	zval *window_zv;
	zend_string *title;
	SDL_Window *window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_STR(title)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_SetWindowTitle(window, ZSTR_VAL(title)));
}

ZEND_FUNCTION(SDL_GetWindowTitle)
{
	zval *window_zv;
	SDL_Window *window;
	const char *title;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	title = SDL_GetWindowTitle(window);
	RETURN_STRING(title != NULL ? title : "");
}

ZEND_FUNCTION(SDL_GetWindowSize)
{
	zval *window_zv, *w, *h;
	SDL_Window *window;
	int width = 0, height = 0;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_ZVAL(w)
		Z_PARAM_ZVAL(h)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	if (!SDL_GetWindowSize(window, &width, &height)) {
		RETURN_FALSE;
	}
	if (!sdl3_assign_wh(w, h, width, height)) {
		RETURN_THROWS();
	}
	RETURN_TRUE;
}

ZEND_FUNCTION(SDL_GetWindowSizeInPixels)
{
	zval *window_zv, *w, *h;
	SDL_Window *window;
	int width = 0, height = 0;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_ZVAL(w)
		Z_PARAM_ZVAL(h)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	if (!SDL_GetWindowSizeInPixels(window, &width, &height)) {
		RETURN_FALSE;
	}
	if (!sdl3_assign_wh(w, h, width, height)) {
		RETURN_THROWS();
	}
	RETURN_TRUE;
}

ZEND_FUNCTION(SDL_GetWindowPixelDensity)
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

	RETURN_DOUBLE(SDL_GetWindowPixelDensity(window));
}

ZEND_FUNCTION(SDL_GetWindowDisplayScale)
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

	RETURN_DOUBLE(SDL_GetWindowDisplayScale(window));
}

ZEND_FUNCTION(SDL_ShowWindow)
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

	RETURN_BOOL(SDL_ShowWindow(window));
}

ZEND_FUNCTION(SDL_HideWindow)
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

	RETURN_BOOL(SDL_HideWindow(window));
}

ZEND_FUNCTION(SDL_RaiseWindow)
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

	RETURN_BOOL(SDL_RaiseWindow(window));
}

ZEND_FUNCTION(SDL_GetWindowFlags)
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

	RETURN_LONG(SDL_GetWindowFlags(window));
}

ZEND_FUNCTION(SDL_GetWindowProperties)
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

	RETURN_LONG(SDL_GetWindowProperties(window));
}

ZEND_FUNCTION(SDL_CreateProperties)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG(SDL_CreateProperties());
}

ZEND_FUNCTION(SDL_DestroyProperties)
{
	zend_long props;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(props)
	ZEND_PARSE_PARAMETERS_END();

	SDL_DestroyProperties((SDL_PropertiesID) props);
}

ZEND_FUNCTION(SDL_SetPointerProperty)
{
	zend_long props, value;
	bool value_null;
	zend_string *name;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_LONG_OR_NULL(value, value_null)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_SetPointerProperty((SDL_PropertiesID) props, ZSTR_VAL(name),
		value_null ? NULL : (void *) (uintptr_t) value));
}

ZEND_FUNCTION(SDL_SetNumberProperty)
{
	zend_long props, value;
	zend_string *name;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_SetNumberProperty((SDL_PropertiesID) props, ZSTR_VAL(name), (Sint64) value));
}

ZEND_FUNCTION(SDL_SetStringProperty)
{
	zend_long props;
	zend_string *name, *value = NULL;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_STR_OR_NULL(value)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_SetStringProperty((SDL_PropertiesID) props, ZSTR_VAL(name),
		value == NULL ? NULL : ZSTR_VAL(value)));
}

ZEND_FUNCTION(SDL_SetBooleanProperty)
{
	zend_long props;
	zend_string *name;
	bool value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_BOOL(value)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_SetBooleanProperty((SDL_PropertiesID) props, ZSTR_VAL(name), value));
}

ZEND_FUNCTION(SDL_GetPointerProperty)
{
	zend_long props, fallback;
	bool fallback_null;
	zend_string *name;
	void *value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_LONG_OR_NULL(fallback, fallback_null)
	ZEND_PARSE_PARAMETERS_END();

	value = SDL_GetPointerProperty((SDL_PropertiesID) props, ZSTR_VAL(name),
		fallback_null ? NULL : (void *) (uintptr_t) fallback);
	if (value == NULL) {
		RETURN_NULL();
	}
	RETURN_LONG((zend_long) (uintptr_t) value);
}

ZEND_FUNCTION(SDL_GetNumberProperty)
{
	zend_long props, fallback;
	zend_string *name;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_LONG(fallback)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(SDL_GetNumberProperty((SDL_PropertiesID) props, ZSTR_VAL(name), (Sint64) fallback));
}

void sdl3_register_SDL_video(int module_number)
{
	(void) module_number;

	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	register_SDL_video_symbols(module_number);

	sdl3_ce_SDL_Window = register_class_SDL_Window();
	sdl3_handle_setup(sdl3_ce_SDL_Window);
}
