#include "runtime.h"
#include "../stubs/SDL_video_arginfo.h"

zend_class_entry *sdl3_ce_SDL_Window;
zend_class_entry *sdl3_ce_SDL_DisplayMode;

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
	sdl3_hit_tests_forget(window);
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

ZEND_FUNCTION(SDL_SetFloatProperty)
{
	zend_long props;
	zend_string *name;
	double value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_DOUBLE(value)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_SetFloatProperty((SDL_PropertiesID) props, ZSTR_VAL(name), (float) value));
}

ZEND_FUNCTION(SDL_GetStringProperty)
{
	zend_long props;
	zend_string *name, *fallback = NULL;
	const char *value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_STR_OR_NULL(fallback)
	ZEND_PARSE_PARAMETERS_END();

	value = SDL_GetStringProperty((SDL_PropertiesID) props, ZSTR_VAL(name),
		fallback == NULL ? NULL : ZSTR_VAL(fallback));
	if (value == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(value);
}

ZEND_FUNCTION(SDL_GetFloatProperty)
{
	zend_long props;
	zend_string *name;
	double fallback;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_DOUBLE(fallback)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_DOUBLE(SDL_GetFloatProperty((SDL_PropertiesID) props, ZSTR_VAL(name), (float) fallback));
}

ZEND_FUNCTION(SDL_GetBooleanProperty)
{
	zend_long props;
	zend_string *name;
	bool fallback;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(props)
		Z_PARAM_STR(name)
		Z_PARAM_BOOL(fallback)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_GetBooleanProperty((SDL_PropertiesID) props, ZSTR_VAL(name), fallback));
}

/* fn(window) → bool */
#define SDL3_WINDOW_CALL(fn) \
	ZEND_FUNCTION(fn) \
	{ \
		zval *window_zv; \
		SDL_Window *window; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window) \
		ZEND_PARSE_PARAMETERS_END(); \
		window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1); \
		if (window == NULL) { \
			RETURN_THROWS(); \
		} \
		RETURN_BOOL(fn(window)); \
	}

/* fn(window, bool) → bool */
#define SDL3_WINDOW_SET_BOOL(fn) \
	ZEND_FUNCTION(fn) \
	{ \
		zval *window_zv; \
		SDL_Window *window; \
		bool value; \
		ZEND_PARSE_PARAMETERS_START(2, 2) \
			Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window) \
			Z_PARAM_BOOL(value) \
		ZEND_PARSE_PARAMETERS_END(); \
		window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1); \
		if (window == NULL) { \
			RETURN_THROWS(); \
		} \
		RETURN_BOOL(fn(window, value)); \
	}

/* fn(window, int, int) → bool */
#define SDL3_WINDOW_SET_INT2(fn) \
	ZEND_FUNCTION(fn) \
	{ \
		zval *window_zv; \
		SDL_Window *window; \
		zend_long a, b; \
		ZEND_PARSE_PARAMETERS_START(3, 3) \
			Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window) \
			Z_PARAM_LONG(a) \
			Z_PARAM_LONG(b) \
		ZEND_PARSE_PARAMETERS_END(); \
		window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1); \
		if (window == NULL) { \
			RETURN_THROWS(); \
		} \
		RETURN_BOOL(fn(window, (int) a, (int) b)); \
	}

/* fn(window, int *, int *) → bool, the ints written through references */
#define SDL3_WINDOW_GET_INT2(fn) \
	ZEND_FUNCTION(fn) \
	{ \
		zval *window_zv, *a_zv, *b_zv; \
		SDL_Window *window; \
		int a = 0, b = 0; \
		ZEND_PARSE_PARAMETERS_START(3, 3) \
			Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window) \
			Z_PARAM_ZVAL(a_zv) \
			Z_PARAM_ZVAL(b_zv) \
		ZEND_PARSE_PARAMETERS_END(); \
		window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1); \
		if (window == NULL) { \
			RETURN_THROWS(); \
		} \
		if (!fn(window, &a, &b)) { \
			RETURN_FALSE; \
		} \
		if (!sdl3_assign_wh(a_zv, b_zv, a, b)) { \
			RETURN_THROWS(); \
		} \
		RETURN_TRUE; \
	}

SDL3_WINDOW_CALL(SDL_MaximizeWindow)
SDL3_WINDOW_CALL(SDL_MinimizeWindow)
SDL3_WINDOW_CALL(SDL_RestoreWindow)
SDL3_WINDOW_CALL(SDL_SyncWindow)

SDL3_WINDOW_SET_BOOL(SDL_SetWindowFullscreen)
SDL3_WINDOW_SET_BOOL(SDL_SetWindowBordered)
SDL3_WINDOW_SET_BOOL(SDL_SetWindowResizable)
SDL3_WINDOW_SET_BOOL(SDL_SetWindowAlwaysOnTop)
SDL3_WINDOW_SET_BOOL(SDL_SetWindowFocusable)

SDL3_WINDOW_SET_INT2(SDL_SetWindowPosition)
SDL3_WINDOW_SET_INT2(SDL_SetWindowSize)
SDL3_WINDOW_SET_INT2(SDL_SetWindowMinimumSize)
SDL3_WINDOW_SET_INT2(SDL_SetWindowMaximumSize)

SDL3_WINDOW_GET_INT2(SDL_GetWindowPosition)
SDL3_WINDOW_GET_INT2(SDL_GetWindowMinimumSize)
SDL3_WINDOW_GET_INT2(SDL_GetWindowMaximumSize)

ZEND_FUNCTION(SDL_SetWindowIcon)
{
	zval *window_zv, *icon_zv;
	SDL_Window *window;
	SDL_Surface *icon;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_OBJECT_OF_CLASS(icon_zv, sdl3_ce_SDL_Surface)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	icon = window != NULL ? sdl3_handle_ptr(icon_zv, sdl3_ce_SDL_Surface, 2) : NULL;
	if (window == NULL || icon == NULL) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_SetWindowIcon(window, icon));
}

ZEND_FUNCTION(SDL_GetWindowSafeArea)
{
	zval *window_zv;
	zend_object *rect_obj;
	SDL_Window *window;
	SDL_Rect rect;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_OBJ_OF_CLASS(rect_obj, sdl3_ce_SDL_Rect)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	if (!SDL_GetWindowSafeArea(window, &rect)) {
		RETURN_FALSE;
	}
	sdl3_rect_write(rect_obj, &rect);
	RETURN_TRUE;
}

ZEND_FUNCTION(SDL_SetWindowAspectRatio)
{
	zval *window_zv;
	SDL_Window *window;
	double min_aspect, max_aspect;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_DOUBLE(min_aspect)
		Z_PARAM_DOUBLE(max_aspect)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_SetWindowAspectRatio(window, (float) min_aspect, (float) max_aspect));
}

ZEND_FUNCTION(SDL_GetWindowAspectRatio)
{
	zval *window_zv, *min_zv, *max_zv;
	SDL_Window *window;
	float min_aspect = 0.0f, max_aspect = 0.0f;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_ZVAL(min_zv)
		Z_PARAM_ZVAL(max_zv)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	if (!SDL_GetWindowAspectRatio(window, &min_aspect, &max_aspect)) {
		RETURN_FALSE;
	}
	ZEND_TRY_ASSIGN_REF_DOUBLE(min_zv, (double) min_aspect);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	ZEND_TRY_ASSIGN_REF_DOUBLE(max_zv, (double) max_aspect);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_TRUE;
}

ZEND_FUNCTION(SDL_GetWindowBordersSize)
{
	zval *window_zv, *top_zv, *left_zv, *bottom_zv, *right_zv;
	SDL_Window *window;
	int top = 0, left = 0, bottom = 0, right = 0;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_ZVAL(top_zv)
		Z_PARAM_ZVAL(left_zv)
		Z_PARAM_ZVAL(bottom_zv)
		Z_PARAM_ZVAL(right_zv)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	if (!SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right)) {
		RETURN_FALSE;
	}
	if (!sdl3_assign_wh(top_zv, left_zv, top, left) || !sdl3_assign_wh(bottom_zv, right_zv, bottom, right)) {
		RETURN_THROWS();
	}
	RETURN_TRUE;
}

ZEND_FUNCTION(SDL_SetWindowOpacity)
{
	zval *window_zv;
	SDL_Window *window;
	double opacity;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_DOUBLE(opacity)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_SetWindowOpacity(window, (float) opacity));
}

ZEND_FUNCTION(SDL_GetWindowOpacity)
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

	RETURN_DOUBLE(SDL_GetWindowOpacity(window));
}

ZEND_FUNCTION(SDL_FlashWindow)
{
	zval *window_zv;
	SDL_Window *window;
	zend_long operation;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_LONG(operation)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_FlashWindow(window, (SDL_FlashOperation) operation));
}

/* A PHP hit test. SDL holds the entry as callback_data; refs covers a callback that replaces itself mid-call. */
typedef struct {
	zend_fcall_info_cache fcc;
	zval data;
	uint32_t refs;
} sdl3_hit_test;

static void sdl3_hit_test_unref(sdl3_hit_test *entry)
{
	if (--entry->refs > 0) {
		return;
	}
	zend_fcc_dtor(&entry->fcc);
	zval_ptr_dtor(&entry->data);
	efree(entry);
}

static void sdl3_hit_test_entry_dtor(zval *zv)
{
	sdl3_hit_test_unref(Z_PTR_P(zv));
}

static SDL_HitTestResult SDLCALL sdl3_hit_test_call(SDL_Window *win, const SDL_Point *area, void *data)
{
	sdl3_hit_test *entry = data;
	SDL_HitTestResult result = SDL_HITTEST_NORMAL;
	zval args[3], rv;

	if (EG(exception) != NULL) {
		return SDL_HITTEST_NORMAL;
	}

	entry->refs++;
	sdl3_box(&args[0], win, sdl3_ce_SDL_Window);
	object_init_ex(&args[1], sdl3_ce_SDL_Point);
	zend_update_property_long(sdl3_ce_SDL_Point, Z_OBJ(args[1]), "x", sizeof("x") - 1, area->x);
	zend_update_property_long(sdl3_ce_SDL_Point, Z_OBJ(args[1]), "y", sizeof("y") - 1, area->y);
	ZVAL_COPY(&args[2], &entry->data);
	ZVAL_UNDEF(&rv);

	zend_call_known_fcc(&entry->fcc, &rv, 3, args, NULL);

	if (Z_TYPE(rv) == IS_LONG) {
		result = (SDL_HitTestResult) Z_LVAL(rv);
	} else if (EG(exception) == NULL) {
		zend_type_error("SDL_SetWindowHitTest(): Argument #2 ($callback) must return int, %s returned", zend_zval_value_name(&rv));
	}

	zval_ptr_dtor(&rv);
	zval_ptr_dtor(&args[0]);
	zval_ptr_dtor(&args[1]);
	zval_ptr_dtor(&args[2]);
	sdl3_hit_test_unref(entry);

	return result;
}

void sdl3_hit_tests_init(HashTable *table)
{
	zend_hash_init(table, 8, NULL, sdl3_hit_test_entry_dtor, 1);
}

void sdl3_hit_tests_forget(SDL_Window *window)
{
	zend_hash_index_del(&SDL3_G(hit_tests), (zend_ulong) (uintptr_t) window);
}

void sdl3_hit_tests_clear(void)
{
	zend_ulong key;

	ZEND_HASH_FOREACH_NUM_KEY(&SDL3_G(hit_tests), key) {
		/* A window SDL already destroyed fails SDL's own validity check here. */
		SDL_SetWindowHitTest((SDL_Window *) (uintptr_t) key, NULL, NULL);
	} ZEND_HASH_FOREACH_END();
	zend_hash_clean(&SDL3_G(hit_tests));
}

ZEND_FUNCTION(SDL_SetWindowHitTest)
{
	zval *window_zv, *data = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	SDL_Window *window;
	sdl3_hit_test *entry;
	bool set;

	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_FUNC_NO_TRAMPOLINE_FREE_OR_NULL(fci, fcc)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(data)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		if (ZEND_FCI_INITIALIZED(fci)) {
			zend_release_fcall_info_cache(&fcc);
		}
		RETURN_THROWS();
	}

	if (!ZEND_FCI_INITIALIZED(fci)) {
		set = SDL_SetWindowHitTest(window, NULL, NULL);
		if (set) {
			sdl3_hit_tests_forget(window);
		}
		RETURN_BOOL(set);
	}

	entry = emalloc(sizeof(sdl3_hit_test));
	zend_fcc_dup(&entry->fcc, &fcc);
	if (data != NULL) {
		ZVAL_COPY(&entry->data, data);
	} else {
		ZVAL_NULL(&entry->data);
	}
	entry->refs = 1;

	set = SDL_SetWindowHitTest(window, sdl3_hit_test_call, entry);
	if (!set) {
		sdl3_hit_test_unref(entry);
		RETURN_FALSE;
	}
	zend_hash_index_update_ptr(&SDL3_G(hit_tests), (zend_ulong) (uintptr_t) window, entry);
	RETURN_TRUE;
}

ZEND_FUNCTION(SDL_ScreenSaverEnabled)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_BOOL(SDL_ScreenSaverEnabled());
}

ZEND_FUNCTION(SDL_EnableScreenSaver)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_BOOL(SDL_EnableScreenSaver());
}

ZEND_FUNCTION(SDL_DisableScreenSaver)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_BOOL(SDL_DisableScreenSaver());
}

ZEND_FUNCTION(SDL_GetCurrentVideoDriver)
{
	const char *driver;

	ZEND_PARSE_PARAMETERS_NONE();

	driver = SDL_GetCurrentVideoDriver();
	if (driver == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(driver);
}

void sdl3_register_SDL_video(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	register_SDL_video_symbols(module_number);

	sdl3_ce_SDL_Window = register_class_SDL_Window();
	sdl3_handle_setup(sdl3_ce_SDL_Window);
	sdl3_ce_SDL_DisplayMode = register_class_SDL_DisplayMode();
	sdl3_struct_setup(sdl3_ce_SDL_DisplayMode);
}
