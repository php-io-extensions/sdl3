#include "runtime.h"
#include "../stubs/SDL_surface_arginfo.h"

zend_class_entry *sdl3_ce_SDL_IOStream;
zend_class_entry *sdl3_ce_SDL_Surface;
zend_class_entry *sdl3_ce_SDL_Rect;
zend_class_entry *sdl3_ce_SDL_Point;

SDL3_POINTER_METHODS(SDL_IOStream)
SDL3_POINTER_METHODS(SDL_Surface)

#define SURFACE_LONG(method, expr) \
	ZEND_METHOD(SDL_Surface, method) \
	{ \
		SDL_Surface *surface; \
		ZEND_PARSE_PARAMETERS_NONE(); \
		surface = sdl3_handle_ptr(ZEND_THIS, sdl3_ce_SDL_Surface, 0); \
		if (surface == NULL) { \
			RETURN_THROWS(); \
		} \
		RETURN_LONG((zend_long) (expr)); \
	}

SURFACE_LONG(flags, surface->flags)
SURFACE_LONG(format, surface->format)
SURFACE_LONG(w, surface->w)
SURFACE_LONG(h, surface->h)
SURFACE_LONG(pitch, surface->pitch)
SURFACE_LONG(pixels, (uintptr_t) surface->pixels)

bool sdl3_rect_read(zend_object *obj, SDL_Rect *rect)
{
	zend_long x, y, w, h;

	if (!sdl3_prop_long(obj, "x", &x) || !sdl3_prop_long(obj, "y", &y)
		|| !sdl3_prop_long(obj, "w", &w) || !sdl3_prop_long(obj, "h", &h)) {
		return false;
	}
	rect->x = (int) x;
	rect->y = (int) y;
	rect->w = (int) w;
	rect->h = (int) h;
	return true;
}

void sdl3_rect_write(zend_object *obj, const SDL_Rect *rect)
{
	zend_update_property_long(sdl3_ce_SDL_Rect, obj, "x", sizeof("x") - 1, rect->x);
	zend_update_property_long(sdl3_ce_SDL_Rect, obj, "y", sizeof("y") - 1, rect->y);
	zend_update_property_long(sdl3_ce_SDL_Rect, obj, "w", sizeof("w") - 1, rect->w);
	zend_update_property_long(sdl3_ce_SDL_Rect, obj, "h", sizeof("h") - 1, rect->h);
}

static bool sdl3_bytes_needed(zend_long pitch, zend_long height, size_t *need)
{
	if (pitch < 0 || height < 0 || (height > 0 && (size_t) pitch > SIZE_MAX / (size_t) height)) {
		return false;
	}

	*need = (size_t) pitch * (size_t) height;
	return true;
}

static SDL_IOStream *sdl3_io_from(zend_long mem, zend_long size, bool constant)
{
	if (mem == 0) {
		zend_argument_value_error(1, "must not be a null address");
		return NULL;
	}
	if (size < 0) {
		zend_argument_value_error(2, "must be greater than or equal to 0");
		return NULL;
	}

	return constant
		? SDL_IOFromConstMem((const void *) (uintptr_t) mem, (size_t) size)
		: SDL_IOFromMem((void *) (uintptr_t) mem, (size_t) size);
}

ZEND_METHOD(SDL_Rect, __construct)
{
	zend_long x = 0, y = 0, w = 0, h = 0;

	ZEND_PARSE_PARAMETERS_START(0, 4)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property_long(sdl3_ce_SDL_Rect, Z_OBJ_P(ZEND_THIS), "x", sizeof("x") - 1, x);
	zend_update_property_long(sdl3_ce_SDL_Rect, Z_OBJ_P(ZEND_THIS), "y", sizeof("y") - 1, y);
	zend_update_property_long(sdl3_ce_SDL_Rect, Z_OBJ_P(ZEND_THIS), "w", sizeof("w") - 1, w);
	zend_update_property_long(sdl3_ce_SDL_Rect, Z_OBJ_P(ZEND_THIS), "h", sizeof("h") - 1, h);
}

ZEND_METHOD(SDL_Point, __construct)
{
	zend_long x = 0, y = 0;

	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property_long(sdl3_ce_SDL_Point, Z_OBJ_P(ZEND_THIS), "x", sizeof("x") - 1, x);
	zend_update_property_long(sdl3_ce_SDL_Point, Z_OBJ_P(ZEND_THIS), "y", sizeof("y") - 1, y);
}

ZEND_FUNCTION(SDL_IOFromMem)
{
	zend_long mem, size;
	SDL_IOStream *io;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(mem)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();

	io = sdl3_io_from(mem, size, false);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	sdl3_box(return_value, io, sdl3_ce_SDL_IOStream);
}

ZEND_FUNCTION(SDL_IOFromConstMem)
{
	zend_long mem, size;
	SDL_IOStream *io;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(mem)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();

	io = sdl3_io_from(mem, size, true);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	sdl3_box(return_value, io, sdl3_ce_SDL_IOStream);
}

ZEND_FUNCTION(SDL_ReadIO)
{
	zval *context_zv;
	zend_long size;
	SDL_IOStream *context;
	zend_string *out;
	size_t got;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(context_zv, sdl3_ce_SDL_IOStream)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();

	if (size < 0) {
		zend_argument_value_error(2, "must be greater than or equal to 0");
		RETURN_THROWS();
	}

	context = sdl3_handle_ptr(context_zv, sdl3_ce_SDL_IOStream, 1);
	if (context == NULL) {
		RETURN_THROWS();
	}

	out = zend_string_alloc((size_t) size, 0);
	got = SDL_ReadIO(context, ZSTR_VAL(out), (size_t) size);
	ZSTR_LEN(out) = got;
	ZSTR_VAL(out)[got] = '\0';
	RETURN_NEW_STR(out);
}

ZEND_FUNCTION(SDL_WriteIO)
{
	zval *context_zv;
	zend_string *ptr;
	zend_long size;
	SDL_IOStream *context;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(context_zv, sdl3_ce_SDL_IOStream)
		Z_PARAM_STR(ptr)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();

	if (size < 0 || (size_t) size > ZSTR_LEN(ptr)) {
		zend_argument_value_error(2, "must hold " ZEND_LONG_FMT " bytes, %zu given", size, ZSTR_LEN(ptr));
		RETURN_THROWS();
	}

	context = sdl3_handle_ptr(context_zv, sdl3_ce_SDL_IOStream, 1);
	if (context == NULL) {
		RETURN_THROWS();
	}

	RETURN_LONG((zend_long) SDL_WriteIO(context, ZSTR_VAL(ptr), (size_t) size));
}

ZEND_FUNCTION(SDL_CloseIO)
{
	zval *context_zv;
	SDL_IOStream *context;
	bool closed;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(context_zv, sdl3_ce_SDL_IOStream)
	ZEND_PARSE_PARAMETERS_END();

	context = sdl3_handle_ptr(context_zv, sdl3_ce_SDL_IOStream, 1);
	if (context == NULL) {
		RETURN_THROWS();
	}

	closed = SDL_CloseIO(context);
	sdl3_release(Z_OBJ_P(context_zv));
	RETURN_BOOL(closed);
}

ZEND_FUNCTION(SDL_GetWindowSurface)
{
	zval *window_zv;
	SDL_Window *window;
	SDL_Surface *surface;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	surface = SDL_GetWindowSurface(window);
	sdl3_box(return_value, surface, sdl3_ce_SDL_Surface);
	if (surface != NULL) {
		sdl3_keep_handle(Z_OBJ_P(window_zv), Z_OBJ_P(return_value));
	}
}

ZEND_FUNCTION(SDL_UpdateWindowSurface)
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

	RETURN_BOOL(SDL_UpdateWindowSurface(window));
}

ZEND_FUNCTION(SDL_UpdateWindowSurfaceRects)
{
	zval *window_zv, *item;
	HashTable *rects;
	SDL_Window *window;
	SDL_Rect *native;
	uint32_t count, i = 0;
	bool updated;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_ARRAY_HT(rects)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	count = zend_hash_num_elements(rects);
	native = safe_emalloc(count == 0 ? 1 : count, sizeof(SDL_Rect), 0);
	ZEND_HASH_FOREACH_VAL(rects, item) {
		ZVAL_DEREF(item);
		if (Z_TYPE_P(item) != IS_OBJECT || !instanceof_function(Z_OBJCE_P(item), sdl3_ce_SDL_Rect)) {
			efree(native);
			zend_argument_type_error(2, "must be a list of SDL_Rect, %s found", zend_zval_value_name(item));
			RETURN_THROWS();
		}
		if (!sdl3_rect_read(Z_OBJ_P(item), &native[i++])) {
			efree(native);
			RETURN_THROWS();
		}
	} ZEND_HASH_FOREACH_END();

	updated = SDL_UpdateWindowSurfaceRects(window, native, (int) count);
	efree(native);
	RETURN_BOOL(updated);
}

ZEND_FUNCTION(SDL_WindowHasSurface)
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

	RETURN_BOOL(SDL_WindowHasSurface(window));
}

ZEND_FUNCTION(SDL_DestroyWindowSurface)
{
	zval *window_zv;
	SDL_Window *window;
	bool destroyed;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	destroyed = SDL_DestroyWindowSurface(window);
	if (destroyed) {
		/* The window keeps only its surface; that SDL_Surface object is now destroyed. */
		sdl3_drop_kept(Z_OBJ_P(window_zv));
	}
	RETURN_BOOL(destroyed);
}

ZEND_FUNCTION(SDL_SetWindowSurfaceVSync)
{
	zval *window_zv;
	SDL_Window *window;
	zend_long vsync;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_LONG(vsync)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_SetWindowSurfaceVSync(window, (int) vsync));
}

ZEND_FUNCTION(SDL_GetWindowSurfaceVSync)
{
	zval *window_zv, *vsync_zv;
	SDL_Window *window;
	int vsync = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(window_zv, sdl3_ce_SDL_Window)
		Z_PARAM_ZVAL(vsync_zv)
	ZEND_PARSE_PARAMETERS_END();

	window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 1);
	if (window == NULL) {
		RETURN_THROWS();
	}

	if (!SDL_GetWindowSurfaceVSync(window, &vsync)) {
		RETURN_FALSE;
	}
	ZEND_TRY_ASSIGN_REF_LONG(vsync_zv, vsync);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_TRUE;
}

ZEND_FUNCTION(SDL_CreateSurfaceFrom)
{
	zend_long width, height, format, pitch, address = 0;
	zend_string *pixels = NULL;
	size_t need = 0;
	SDL_Surface *surface;
	void *bytes;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(format)
		Z_PARAM_STR_OR_LONG(pixels, address)
		Z_PARAM_LONG(pitch)
	ZEND_PARSE_PARAMETERS_END();

	if (pixels != NULL) {
		if (!sdl3_bytes_needed(pitch, height, &need) || ZSTR_LEN(pixels) < need) {
			zend_argument_value_error(4, "must hold %zu bytes, %zu given", need, pixels != NULL ? ZSTR_LEN(pixels) : 0);
			RETURN_THROWS();
		}
		bytes = ZSTR_VAL(pixels);
	} else {
		if (address == 0) {
			zend_argument_value_error(4, "must not be a null address");
			RETURN_THROWS();
		}
		bytes = (void *) (uintptr_t) address;
	}

	surface = SDL_CreateSurfaceFrom((int) width, (int) height, (SDL_PixelFormat) format, bytes, (int) pitch);
	sdl3_box(return_value, surface, sdl3_ce_SDL_Surface);
	if (surface != NULL && pixels != NULL) {
		sdl3_keep_string(Z_OBJ_P(return_value), pixels);
	}
}

ZEND_FUNCTION(SDL_DestroySurface)
{
	zval *surface_zv;
	SDL_Surface *surface;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(surface_zv, sdl3_ce_SDL_Surface)
	ZEND_PARSE_PARAMETERS_END();

	surface = sdl3_handle_ptr(surface_zv, sdl3_ce_SDL_Surface, 1);
	if (surface == NULL) {
		RETURN_THROWS();
	}

	SDL_DestroySurface(surface);
	sdl3_release(Z_OBJ_P(surface_zv));
}

ZEND_FUNCTION(SDL_BlitSurface)
{
	zval *src_zv, *dst_zv;
	zend_object *srcrect = NULL, *dstrect = NULL;
	SDL_Surface *src, *dst;
	SDL_Rect src_rect, dst_rect;
	const SDL_Rect *src_ptr = NULL, *dst_ptr = NULL;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(src_zv, sdl3_ce_SDL_Surface)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(srcrect, sdl3_ce_SDL_Rect)
		Z_PARAM_OBJECT_OF_CLASS(dst_zv, sdl3_ce_SDL_Surface)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(dstrect, sdl3_ce_SDL_Rect)
	ZEND_PARSE_PARAMETERS_END();

	src = sdl3_handle_ptr(src_zv, sdl3_ce_SDL_Surface, 1);
	dst = src != NULL ? sdl3_handle_ptr(dst_zv, sdl3_ce_SDL_Surface, 3) : NULL;
	if (src == NULL || dst == NULL) {
		RETURN_THROWS();
	}
	if (srcrect != NULL) {
		if (!sdl3_rect_read(srcrect, &src_rect)) {
			RETURN_THROWS();
		}
		src_ptr = &src_rect;
	}
	if (dstrect != NULL) {
		if (!sdl3_rect_read(dstrect, &dst_rect)) {
			RETURN_THROWS();
		}
		dst_ptr = &dst_rect;
	}

	RETURN_BOOL(SDL_BlitSurface(src, src_ptr, dst, dst_ptr));
}

ZEND_FUNCTION(SDL_BlitSurfaceScaled)
{
	zval *src_zv, *dst_zv;
	zend_object *srcrect = NULL, *dstrect = NULL;
	zend_long scale_mode;
	SDL_Surface *src, *dst;
	SDL_Rect src_rect, dst_rect;
	const SDL_Rect *src_ptr = NULL, *dst_ptr = NULL;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(src_zv, sdl3_ce_SDL_Surface)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(srcrect, sdl3_ce_SDL_Rect)
		Z_PARAM_OBJECT_OF_CLASS(dst_zv, sdl3_ce_SDL_Surface)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(dstrect, sdl3_ce_SDL_Rect)
		Z_PARAM_LONG(scale_mode)
	ZEND_PARSE_PARAMETERS_END();

	src = sdl3_handle_ptr(src_zv, sdl3_ce_SDL_Surface, 1);
	dst = src != NULL ? sdl3_handle_ptr(dst_zv, sdl3_ce_SDL_Surface, 3) : NULL;
	if (src == NULL || dst == NULL) {
		RETURN_THROWS();
	}
	if (srcrect != NULL) {
		if (!sdl3_rect_read(srcrect, &src_rect)) {
			RETURN_THROWS();
		}
		src_ptr = &src_rect;
	}
	if (dstrect != NULL) {
		if (!sdl3_rect_read(dstrect, &dst_rect)) {
			RETURN_THROWS();
		}
		dst_ptr = &dst_rect;
	}

	RETURN_BOOL(SDL_BlitSurfaceScaled(src, src_ptr, dst, dst_ptr, (SDL_ScaleMode) scale_mode));
}

ZEND_FUNCTION(SDL_FillSurfaceRect)
{
	zval *dst_zv;
	zend_object *rect = NULL;
	zend_long color;
	SDL_Surface *dst;
	SDL_Rect native;
	const SDL_Rect *rect_ptr = NULL;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(dst_zv, sdl3_ce_SDL_Surface)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(rect, sdl3_ce_SDL_Rect)
		Z_PARAM_LONG(color)
	ZEND_PARSE_PARAMETERS_END();

	dst = sdl3_handle_ptr(dst_zv, sdl3_ce_SDL_Surface, 1);
	if (dst == NULL) {
		RETURN_THROWS();
	}
	if (rect != NULL) {
		if (!sdl3_rect_read(rect, &native)) {
			RETURN_THROWS();
		}
		rect_ptr = &native;
	}

	RETURN_BOOL(SDL_FillSurfaceRect(dst, rect_ptr, (Uint32) color));
}

void sdl3_register_SDL_surface(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	register_SDL_surface_symbols(module_number);

	sdl3_ce_SDL_IOStream = register_class_SDL_IOStream();
	sdl3_handle_setup(sdl3_ce_SDL_IOStream);
	sdl3_ce_SDL_Surface = register_class_SDL_Surface();
	sdl3_handle_setup(sdl3_ce_SDL_Surface);
	sdl3_ce_SDL_Rect = register_class_SDL_Rect();
	sdl3_struct_setup(sdl3_ce_SDL_Rect);
	sdl3_ce_SDL_Point = register_class_SDL_Point();
	sdl3_struct_setup(sdl3_ce_SDL_Point);
}
