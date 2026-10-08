/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: d47a98657e77d5fb4a299f4f6c6b5e3a8d637184 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_IOFromMem, 0, 2, SDL_IOStream, 1)
	ZEND_ARG_TYPE_INFO(0, mem, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_IOFromConstMem arginfo_SDL_IOFromMem

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_ReadIO, 0, 2, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, context, SDL_IOStream, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_WriteIO, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, context, SDL_IOStream, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_CloseIO, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, context, SDL_IOStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_GetWindowSurface, 0, 1, SDL_Surface, 1)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_UpdateWindowSurface, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_UpdateWindowSurfaceRects, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, rects, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_WindowHasSurface arginfo_SDL_UpdateWindowSurface

#define arginfo_SDL_DestroyWindowSurface arginfo_SDL_UpdateWindowSurface

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowSurfaceVSync, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, vsync, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetWindowSurfaceVSync, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(1, vsync, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_CreateSurfaceFrom, 0, 5, SDL_Surface, 1)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_MASK(0, pixels, MAY_BE_STRING|MAY_BE_LONG, NULL)
	ZEND_ARG_TYPE_INFO(0, pitch, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_DestroySurface, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_BlitSurface, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, src, SDL_Surface, 0)
	ZEND_ARG_OBJ_INFO(0, srcrect, SDL_Rect, 1)
	ZEND_ARG_OBJ_INFO(0, dst, SDL_Surface, 0)
	ZEND_ARG_OBJ_INFO(0, dstrect, SDL_Rect, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_BlitSurfaceScaled, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, src, SDL_Surface, 0)
	ZEND_ARG_OBJ_INFO(0, srcrect, SDL_Rect, 1)
	ZEND_ARG_OBJ_INFO(0, dst, SDL_Surface, 0)
	ZEND_ARG_OBJ_INFO(0, dstrect, SDL_Rect, 1)
	ZEND_ARG_TYPE_INFO(0, scaleMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_FillSurfaceRect, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, dst, SDL_Surface, 0)
	ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 1)
	ZEND_ARG_TYPE_INFO(0, color, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_IOStream___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_IOStream_pointer, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_IOStream_fromPointer, 0, 1, IS_STATIC, 0)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_SDL_Surface___construct arginfo_class_SDL_IOStream___construct

#define arginfo_class_SDL_Surface_pointer arginfo_class_SDL_IOStream_pointer

#define arginfo_class_SDL_Surface_fromPointer arginfo_class_SDL_IOStream_fromPointer

#define arginfo_class_SDL_Surface_flags arginfo_class_SDL_IOStream_pointer

#define arginfo_class_SDL_Surface_format arginfo_class_SDL_IOStream_pointer

#define arginfo_class_SDL_Surface_w arginfo_class_SDL_IOStream_pointer

#define arginfo_class_SDL_Surface_h arginfo_class_SDL_IOStream_pointer

#define arginfo_class_SDL_Surface_pitch arginfo_class_SDL_IOStream_pointer

#define arginfo_class_SDL_Surface_pixels arginfo_class_SDL_IOStream_pointer

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_Rect___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, w, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, h, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_Point___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_FUNCTION(SDL_IOFromMem);
ZEND_FUNCTION(SDL_IOFromConstMem);
ZEND_FUNCTION(SDL_ReadIO);
ZEND_FUNCTION(SDL_WriteIO);
ZEND_FUNCTION(SDL_CloseIO);
ZEND_FUNCTION(SDL_GetWindowSurface);
ZEND_FUNCTION(SDL_UpdateWindowSurface);
ZEND_FUNCTION(SDL_UpdateWindowSurfaceRects);
ZEND_FUNCTION(SDL_WindowHasSurface);
ZEND_FUNCTION(SDL_DestroyWindowSurface);
ZEND_FUNCTION(SDL_SetWindowSurfaceVSync);
ZEND_FUNCTION(SDL_GetWindowSurfaceVSync);
ZEND_FUNCTION(SDL_CreateSurfaceFrom);
ZEND_FUNCTION(SDL_DestroySurface);
ZEND_FUNCTION(SDL_BlitSurface);
ZEND_FUNCTION(SDL_BlitSurfaceScaled);
ZEND_FUNCTION(SDL_FillSurfaceRect);
ZEND_METHOD(SDL_IOStream, __construct);
ZEND_METHOD(SDL_IOStream, pointer);
ZEND_METHOD(SDL_IOStream, fromPointer);
ZEND_METHOD(SDL_Surface, __construct);
ZEND_METHOD(SDL_Surface, pointer);
ZEND_METHOD(SDL_Surface, fromPointer);
ZEND_METHOD(SDL_Surface, flags);
ZEND_METHOD(SDL_Surface, format);
ZEND_METHOD(SDL_Surface, w);
ZEND_METHOD(SDL_Surface, h);
ZEND_METHOD(SDL_Surface, pitch);
ZEND_METHOD(SDL_Surface, pixels);
ZEND_METHOD(SDL_Rect, __construct);
ZEND_METHOD(SDL_Point, __construct);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(SDL_IOFromMem, arginfo_SDL_IOFromMem)
	ZEND_FE(SDL_IOFromConstMem, arginfo_SDL_IOFromConstMem)
	ZEND_FE(SDL_ReadIO, arginfo_SDL_ReadIO)
	ZEND_FE(SDL_WriteIO, arginfo_SDL_WriteIO)
	ZEND_FE(SDL_CloseIO, arginfo_SDL_CloseIO)
	ZEND_FE(SDL_GetWindowSurface, arginfo_SDL_GetWindowSurface)
	ZEND_FE(SDL_UpdateWindowSurface, arginfo_SDL_UpdateWindowSurface)
	ZEND_FE(SDL_UpdateWindowSurfaceRects, arginfo_SDL_UpdateWindowSurfaceRects)
	ZEND_FE(SDL_WindowHasSurface, arginfo_SDL_WindowHasSurface)
	ZEND_FE(SDL_DestroyWindowSurface, arginfo_SDL_DestroyWindowSurface)
	ZEND_FE(SDL_SetWindowSurfaceVSync, arginfo_SDL_SetWindowSurfaceVSync)
	ZEND_FE(SDL_GetWindowSurfaceVSync, arginfo_SDL_GetWindowSurfaceVSync)
	ZEND_FE(SDL_CreateSurfaceFrom, arginfo_SDL_CreateSurfaceFrom)
	ZEND_FE(SDL_DestroySurface, arginfo_SDL_DestroySurface)
	ZEND_FE(SDL_BlitSurface, arginfo_SDL_BlitSurface)
	ZEND_FE(SDL_BlitSurfaceScaled, arginfo_SDL_BlitSurfaceScaled)
	ZEND_FE(SDL_FillSurfaceRect, arginfo_SDL_FillSurfaceRect)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_IOStream_methods[] = {
	ZEND_ME(SDL_IOStream, __construct, arginfo_class_SDL_IOStream___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SDL_IOStream, pointer, arginfo_class_SDL_IOStream_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_IOStream, fromPointer, arginfo_class_SDL_IOStream_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_Surface_methods[] = {
	ZEND_ME(SDL_Surface, __construct, arginfo_class_SDL_Surface___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SDL_Surface, pointer, arginfo_class_SDL_Surface_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_Surface, fromPointer, arginfo_class_SDL_Surface_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(SDL_Surface, flags, arginfo_class_SDL_Surface_flags, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_Surface, format, arginfo_class_SDL_Surface_format, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_Surface, w, arginfo_class_SDL_Surface_w, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_Surface, h, arginfo_class_SDL_Surface_h, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_Surface, pitch, arginfo_class_SDL_Surface_pitch, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_Surface, pixels, arginfo_class_SDL_Surface_pixels, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_Rect_methods[] = {
	ZEND_ME(SDL_Rect, __construct, arginfo_class_SDL_Rect___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_Point_methods[] = {
	ZEND_ME(SDL_Point, __construct, arginfo_class_SDL_Point___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static void register_SDL_surface_symbols(int module_number)
{
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_RGBA32", SDL_PIXELFORMAT_RGBA32, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_BGRA32", SDL_PIXELFORMAT_BGRA32, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_SCALEMODE_NEAREST", SDL_SCALEMODE_NEAREST, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_SCALEMODE_LINEAR", SDL_SCALEMODE_LINEAR, CONST_PERSISTENT);
}

static zend_class_entry *register_class_SDL_IOStream(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_IOStream", class_SDL_IOStream_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_SDL_Surface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_Surface", class_SDL_Surface_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_SDL_Rect(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_Rect", class_SDL_Rect_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_x_default_value;
	ZVAL_LONG(&property_x_default_value, 0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_LONG(&property_y_default_value, 0);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y_name);

	zval property_w_default_value;
	ZVAL_LONG(&property_w_default_value, 0);
	zend_string *property_w_name = zend_string_init("w", sizeof("w") - 1, 1);
	zend_declare_typed_property(class_entry, property_w_name, &property_w_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_w_name);

	zval property_h_default_value;
	ZVAL_LONG(&property_h_default_value, 0);
	zend_string *property_h_name = zend_string_init("h", sizeof("h") - 1, 1);
	zend_declare_typed_property(class_entry, property_h_name, &property_h_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_h_name);

	return class_entry;
}

static zend_class_entry *register_class_SDL_Point(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_Point", class_SDL_Point_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_x_default_value;
	ZVAL_LONG(&property_x_default_value, 0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_LONG(&property_y_default_value, 0);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y_name);

	return class_entry;
}
