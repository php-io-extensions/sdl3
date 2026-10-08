/* Displays, display modes and fullscreen modes. Declared by SDL_video.stub.php. */

#include "runtime.h"

#define MODE_LONG(name, value) \
	zend_update_property_long(sdl3_ce_SDL_DisplayMode, obj, name, sizeof(name) - 1, (zend_long) (value))
#define MODE_DOUBLE(name, value) \
	zend_update_property_double(sdl3_ce_SDL_DisplayMode, obj, name, sizeof(name) - 1, (double) (value))

static void sdl3_display_mode_write(zend_object *obj, const SDL_DisplayMode *mode)
{
	MODE_LONG("displayID", mode->displayID);
	MODE_LONG("format", mode->format);
	MODE_LONG("w", mode->w);
	MODE_LONG("h", mode->h);
	MODE_DOUBLE("pixel_density", mode->pixel_density);
	MODE_DOUBLE("refresh_rate", mode->refresh_rate);
	MODE_LONG("refresh_rate_numerator", mode->refresh_rate_numerator);
	MODE_LONG("refresh_rate_denominator", mode->refresh_rate_denominator);
}

static void sdl3_display_mode_box(zval *rv, const SDL_DisplayMode *mode)
{
	if (mode == NULL) {
		ZVAL_NULL(rv);
		return;
	}
	object_init_ex(rv, sdl3_ce_SDL_DisplayMode);
	sdl3_display_mode_write(Z_OBJ_P(rv), mode);
}

static bool sdl3_display_mode_read(zend_object *obj, SDL_DisplayMode *mode)
{
	zend_long display, format, w, h, num, den;
	double density, rate;

	if (!sdl3_prop_long(obj, "displayID", &display)
		|| !sdl3_prop_long(obj, "format", &format)
		|| !sdl3_prop_long(obj, "w", &w)
		|| !sdl3_prop_long(obj, "h", &h)
		|| !sdl3_prop_double(obj, "pixel_density", &density)
		|| !sdl3_prop_double(obj, "refresh_rate", &rate)
		|| !sdl3_prop_long(obj, "refresh_rate_numerator", &num)
		|| !sdl3_prop_long(obj, "refresh_rate_denominator", &den)) {
		return false;
	}

	memset(mode, 0, sizeof(*mode));
	mode->displayID = (SDL_DisplayID) display;
	mode->format = (SDL_PixelFormat) format;
	mode->w = (int) w;
	mode->h = (int) h;
	mode->pixel_density = (float) density;
	mode->refresh_rate = (float) rate;
	mode->refresh_rate_numerator = (int) num;
	mode->refresh_rate_denominator = (int) den;
	return true;
}

ZEND_FUNCTION(SDL_GetDisplays)
{
	int count = 0, i;
	SDL_DisplayID *displays;

	ZEND_PARSE_PARAMETERS_NONE();

	displays = SDL_GetDisplays(&count);
	if (displays == NULL) {
		RETURN_NULL();
	}

	array_init_size(return_value, (uint32_t) count);
	for (i = 0; i < count; i++) {
		add_next_index_long(return_value, (zend_long) displays[i]);
	}
	SDL_free(displays);
}

ZEND_FUNCTION(SDL_GetPrimaryDisplay)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG(SDL_GetPrimaryDisplay());
}

ZEND_FUNCTION(SDL_GetDisplayProperties)
{
	zend_long display;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(SDL_GetDisplayProperties((SDL_DisplayID) display));
}

ZEND_FUNCTION(SDL_GetDisplayName)
{
	zend_long display;
	const char *name;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display)
	ZEND_PARSE_PARAMETERS_END();

	name = SDL_GetDisplayName((SDL_DisplayID) display);
	if (name == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(name);
}

ZEND_FUNCTION(SDL_GetDisplayBounds)
{
	zend_long display;
	zend_object *rect_obj;
	SDL_Rect rect;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(display)
		Z_PARAM_OBJ_OF_CLASS(rect_obj, sdl3_ce_SDL_Rect)
	ZEND_PARSE_PARAMETERS_END();

	if (!SDL_GetDisplayBounds((SDL_DisplayID) display, &rect)) {
		RETURN_FALSE;
	}
	sdl3_rect_write(rect_obj, &rect);
	RETURN_TRUE;
}

ZEND_FUNCTION(SDL_GetDisplayUsableBounds)
{
	zend_long display;
	zend_object *rect_obj;
	SDL_Rect rect;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(display)
		Z_PARAM_OBJ_OF_CLASS(rect_obj, sdl3_ce_SDL_Rect)
	ZEND_PARSE_PARAMETERS_END();

	if (!SDL_GetDisplayUsableBounds((SDL_DisplayID) display, &rect)) {
		RETURN_FALSE;
	}
	sdl3_rect_write(rect_obj, &rect);
	RETURN_TRUE;
}

ZEND_FUNCTION(SDL_GetNaturalDisplayOrientation)
{
	zend_long display;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(SDL_GetNaturalDisplayOrientation((SDL_DisplayID) display));
}

ZEND_FUNCTION(SDL_GetCurrentDisplayOrientation)
{
	zend_long display;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(SDL_GetCurrentDisplayOrientation((SDL_DisplayID) display));
}

ZEND_FUNCTION(SDL_GetDisplayContentScale)
{
	zend_long display;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_DOUBLE(SDL_GetDisplayContentScale((SDL_DisplayID) display));
}

ZEND_FUNCTION(SDL_GetFullscreenDisplayModes)
{
	zend_long display;
	int count = 0, i;
	SDL_DisplayMode **modes;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display)
	ZEND_PARSE_PARAMETERS_END();

	modes = SDL_GetFullscreenDisplayModes((SDL_DisplayID) display, &count);
	if (modes == NULL) {
		RETURN_NULL();
	}

	array_init_size(return_value, (uint32_t) count);
	for (i = 0; i < count; i++) {
		zval mode;
		sdl3_display_mode_box(&mode, modes[i]);
		add_next_index_zval(return_value, &mode);
	}
	SDL_free(modes);
}

ZEND_FUNCTION(SDL_GetClosestFullscreenDisplayMode)
{
	zend_long display, w, h;
	double refresh_rate;
	bool high_density;
	zend_object *closest_obj;
	SDL_DisplayMode closest;

	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_LONG(display)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_DOUBLE(refresh_rate)
		Z_PARAM_BOOL(high_density)
		Z_PARAM_OBJ_OF_CLASS(closest_obj, sdl3_ce_SDL_DisplayMode)
	ZEND_PARSE_PARAMETERS_END();

	if (!SDL_GetClosestFullscreenDisplayMode((SDL_DisplayID) display, (int) w, (int) h,
			(float) refresh_rate, high_density, &closest)) {
		RETURN_FALSE;
	}
	sdl3_display_mode_write(closest_obj, &closest);
	RETURN_TRUE;
}

ZEND_FUNCTION(SDL_GetDesktopDisplayMode)
{
	zend_long display;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display)
	ZEND_PARSE_PARAMETERS_END();

	sdl3_display_mode_box(return_value, SDL_GetDesktopDisplayMode((SDL_DisplayID) display));
}

ZEND_FUNCTION(SDL_GetCurrentDisplayMode)
{
	zend_long display;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(display)
	ZEND_PARSE_PARAMETERS_END();

	sdl3_display_mode_box(return_value, SDL_GetCurrentDisplayMode((SDL_DisplayID) display));
}

ZEND_FUNCTION(SDL_GetDisplayForPoint)
{
	zend_object *point_obj;
	SDL_Point point;
	zend_long x, y;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(point_obj, sdl3_ce_SDL_Point)
	ZEND_PARSE_PARAMETERS_END();

	if (!sdl3_prop_long(point_obj, "x", &x) || !sdl3_prop_long(point_obj, "y", &y)) {
		RETURN_THROWS();
	}
	point.x = (int) x;
	point.y = (int) y;

	RETURN_LONG(SDL_GetDisplayForPoint(&point));
}

ZEND_FUNCTION(SDL_GetDisplayForRect)
{
	zend_object *rect_obj;
	SDL_Rect rect;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(rect_obj, sdl3_ce_SDL_Rect)
	ZEND_PARSE_PARAMETERS_END();

	if (!sdl3_rect_read(rect_obj, &rect)) {
		RETURN_THROWS();
	}

	RETURN_LONG(SDL_GetDisplayForRect(&rect));
}

ZEND_FUNCTION(SDL_GetDisplayForWindow)
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

	RETURN_LONG(SDL_GetDisplayForWindow(window));
}

ZEND_FUNCTION(SDL_SetWindowFullscreenMode)
{
	zval *window_zv;
	zend_object *mode_obj = NULL;
	SDL_Window *window;
	SDL_DisplayMode mode;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(mode_obj, sdl3_ce_SDL_DisplayMode)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}
	if (mode_obj != NULL && !sdl3_display_mode_read(mode_obj, &mode)) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_SetWindowFullscreenMode(window, mode_obj == NULL ? NULL : &mode));
}

ZEND_FUNCTION(SDL_GetWindowFullscreenMode)
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

	sdl3_display_mode_box(return_value, SDL_GetWindowFullscreenMode(window));
}
