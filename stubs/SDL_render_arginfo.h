/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 0c205e8a51b162058fe2297111d2b864a84d0935 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_CreateSoftwareRenderer, 0, 1, SDL_Renderer, 1)
	ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_DestroyRenderer, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_CreateTextureFromSurface, 0, 2, SDL_Texture, 1)
	ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_DestroyTexture, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, texture, SDL_Texture, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetTextureBlendMode, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, texture, SDL_Texture, 0)
	ZEND_ARG_TYPE_INFO(0, blendMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetTextureScaleMode, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, texture, SDL_Texture, 0)
	ZEND_ARG_TYPE_INFO(0, scaleMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetTextureAlphaMod, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, texture, SDL_Texture, 0)
	ZEND_ARG_TYPE_INFO(0, alpha, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetTextureColorMod, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, texture, SDL_Texture, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetRenderClipRect, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_RenderGeometry, 0, 6, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_OBJ_INFO(0, texture, SDL_Texture, 1)
	ZEND_ARG_TYPE_INFO(0, vertices, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, num_vertices, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, indices, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(0, num_indices, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_RenderGeometryRaw, 0, 12, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_OBJ_INFO(0, texture, SDL_Texture, 1)
	ZEND_ARG_TYPE_MASK(0, xy, MAY_BE_STRING|MAY_BE_LONG, NULL)
	ZEND_ARG_TYPE_INFO(0, xy_stride, IS_LONG, 0)
	ZEND_ARG_TYPE_MASK(0, color, MAY_BE_STRING|MAY_BE_LONG, NULL)
	ZEND_ARG_TYPE_INFO(0, color_stride, IS_LONG, 0)
	ZEND_ARG_TYPE_MASK(0, uv, MAY_BE_STRING|MAY_BE_LONG|MAY_BE_NULL, NULL)
	ZEND_ARG_TYPE_INFO(0, uv_stride, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, num_vertices, IS_LONG, 0)
	ZEND_ARG_TYPE_MASK(0, indices, MAY_BE_STRING|MAY_BE_LONG|MAY_BE_NULL, NULL)
	ZEND_ARG_TYPE_INFO(0, num_indices, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, size_indices, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_FlushRenderer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_Renderer___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Renderer_pointer, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Renderer_fromPointer, 0, 1, IS_STATIC, 1)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_SDL_Texture___construct arginfo_class_SDL_Renderer___construct

#define arginfo_class_SDL_Texture_pointer arginfo_class_SDL_Renderer_pointer

#define arginfo_class_SDL_Texture_fromPointer arginfo_class_SDL_Renderer_fromPointer

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_FPoint___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y, IS_DOUBLE, 0, "0.0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_Vertex___construct, 0, 0, 3)
	ZEND_ARG_OBJ_INFO(0, position, SDL_FPoint, 0)
	ZEND_ARG_OBJ_INFO(0, color, SDL_FColor, 0)
	ZEND_ARG_OBJ_INFO(0, tex_coord, SDL_FPoint, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(SDL_CreateSoftwareRenderer);
ZEND_FUNCTION(SDL_DestroyRenderer);
ZEND_FUNCTION(SDL_CreateTextureFromSurface);
ZEND_FUNCTION(SDL_DestroyTexture);
ZEND_FUNCTION(SDL_SetTextureBlendMode);
ZEND_FUNCTION(SDL_SetTextureScaleMode);
ZEND_FUNCTION(SDL_SetTextureAlphaMod);
ZEND_FUNCTION(SDL_SetTextureColorMod);
ZEND_FUNCTION(SDL_SetRenderClipRect);
ZEND_FUNCTION(SDL_RenderGeometry);
ZEND_FUNCTION(SDL_RenderGeometryRaw);
ZEND_FUNCTION(SDL_FlushRenderer);
ZEND_METHOD(SDL_Renderer, __construct);
ZEND_METHOD(SDL_Renderer, pointer);
ZEND_METHOD(SDL_Renderer, fromPointer);
ZEND_METHOD(SDL_Texture, __construct);
ZEND_METHOD(SDL_Texture, pointer);
ZEND_METHOD(SDL_Texture, fromPointer);
ZEND_METHOD(SDL_FPoint, __construct);
ZEND_METHOD(SDL_Vertex, __construct);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(SDL_CreateSoftwareRenderer, arginfo_SDL_CreateSoftwareRenderer)
	ZEND_FE(SDL_DestroyRenderer, arginfo_SDL_DestroyRenderer)
	ZEND_FE(SDL_CreateTextureFromSurface, arginfo_SDL_CreateTextureFromSurface)
	ZEND_FE(SDL_DestroyTexture, arginfo_SDL_DestroyTexture)
	ZEND_FE(SDL_SetTextureBlendMode, arginfo_SDL_SetTextureBlendMode)
	ZEND_FE(SDL_SetTextureScaleMode, arginfo_SDL_SetTextureScaleMode)
	ZEND_FE(SDL_SetTextureAlphaMod, arginfo_SDL_SetTextureAlphaMod)
	ZEND_FE(SDL_SetTextureColorMod, arginfo_SDL_SetTextureColorMod)
	ZEND_FE(SDL_SetRenderClipRect, arginfo_SDL_SetRenderClipRect)
	ZEND_FE(SDL_RenderGeometry, arginfo_SDL_RenderGeometry)
	ZEND_FE(SDL_RenderGeometryRaw, arginfo_SDL_RenderGeometryRaw)
	ZEND_FE(SDL_FlushRenderer, arginfo_SDL_FlushRenderer)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_Renderer_methods[] = {
	ZEND_ME(SDL_Renderer, __construct, arginfo_class_SDL_Renderer___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SDL_Renderer, pointer, arginfo_class_SDL_Renderer_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_Renderer, fromPointer, arginfo_class_SDL_Renderer_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_Texture_methods[] = {
	ZEND_ME(SDL_Texture, __construct, arginfo_class_SDL_Texture___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SDL_Texture, pointer, arginfo_class_SDL_Texture_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_Texture, fromPointer, arginfo_class_SDL_Texture_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_FPoint_methods[] = {
	ZEND_ME(SDL_FPoint, __construct, arginfo_class_SDL_FPoint___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_Vertex_methods[] = {
	ZEND_ME(SDL_Vertex, __construct, arginfo_class_SDL_Vertex___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_SDL_Renderer(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_Renderer", class_SDL_Renderer_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_SDL_Texture(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_Texture", class_SDL_Texture_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_SDL_FPoint(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_FPoint", class_SDL_FPoint_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_x_default_value;
	ZVAL_DOUBLE(&property_x_default_value, 0.0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_DOUBLE(&property_y_default_value, 0.0);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_y_name);

	return class_entry;
}

static zend_class_entry *register_class_SDL_Vertex(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_Vertex", class_SDL_Vertex_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_position_default_value;
	ZVAL_UNDEF(&property_position_default_value);
	zend_string *property_position_name = zend_string_init("position", sizeof("position") - 1, 1);
	zend_string *property_position_class_SDL_FPoint = zend_string_init("SDL_FPoint", sizeof("SDL_FPoint")-1, 1);
	zend_declare_typed_property(class_entry, property_position_name, &property_position_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_position_class_SDL_FPoint, 0, 0));
	zend_string_release(property_position_name);

	zval property_color_default_value;
	ZVAL_UNDEF(&property_color_default_value);
	zend_string *property_color_name = zend_string_init("color", sizeof("color") - 1, 1);
	zend_string *property_color_class_SDL_FColor = zend_string_init("SDL_FColor", sizeof("SDL_FColor")-1, 1);
	zend_declare_typed_property(class_entry, property_color_name, &property_color_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_color_class_SDL_FColor, 0, 0));
	zend_string_release(property_color_name);

	zval property_tex_coord_default_value;
	ZVAL_UNDEF(&property_tex_coord_default_value);
	zend_string *property_tex_coord_name = zend_string_init("tex_coord", sizeof("tex_coord") - 1, 1);
	zend_string *property_tex_coord_class_SDL_FPoint = zend_string_init("SDL_FPoint", sizeof("SDL_FPoint")-1, 1);
	zend_declare_typed_property(class_entry, property_tex_coord_name, &property_tex_coord_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_tex_coord_class_SDL_FPoint, 0, 0));
	zend_string_release(property_tex_coord_name);

	return class_entry;
}
