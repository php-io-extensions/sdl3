#include "runtime.h"
#include "SDL_gpu_types.h"
#include "../stubs/SDL_render_arginfo.h"

zend_class_entry *sdl3_ce_SDL_Renderer;
zend_class_entry *sdl3_ce_SDL_Texture;
zend_class_entry *sdl3_ce_SDL_FPoint;
zend_class_entry *sdl3_ce_SDL_Vertex;

/* The address hand-off every handle class has: pointer() reads the native address, fromPointer() boxes one (0 is null). */
ZEND_METHOD(SDL_Renderer, __construct)
{
	ZEND_PARSE_PARAMETERS_NONE();
}

ZEND_METHOD(SDL_Renderer, pointer)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG((zend_long) (uintptr_t) sdl3_handle_from(Z_OBJ_P(ZEND_THIS))->ptr);
}

ZEND_METHOD(SDL_Renderer, fromPointer)
{
	zend_long address;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(address)
	ZEND_PARSE_PARAMETERS_END();

	sdl3_box(return_value, (void *) (uintptr_t) address, zend_get_called_scope(execute_data));
}

ZEND_METHOD(SDL_Texture, __construct)
{
	ZEND_PARSE_PARAMETERS_NONE();
}

ZEND_METHOD(SDL_Texture, pointer)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG((zend_long) (uintptr_t) sdl3_handle_from(Z_OBJ_P(ZEND_THIS))->ptr);
}

ZEND_METHOD(SDL_Texture, fromPointer)
{
	zend_long address;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(address)
	ZEND_PARSE_PARAMETERS_END();

	sdl3_box(return_value, (void *) (uintptr_t) address, zend_get_called_scope(execute_data));
}

ZEND_METHOD(SDL_FPoint, __construct)
{
	double x = 0.0, y = 0.0;

	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property_double(sdl3_ce_SDL_FPoint, Z_OBJ_P(ZEND_THIS), "x", sizeof("x") - 1, x);
	zend_update_property_double(sdl3_ce_SDL_FPoint, Z_OBJ_P(ZEND_THIS), "y", sizeof("y") - 1, y);
}

ZEND_METHOD(SDL_Vertex, __construct)
{
	zval *position, *color, *tex_coord;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(position, sdl3_ce_SDL_FPoint)
		Z_PARAM_OBJECT_OF_CLASS(color, sdl3_ce_SDL_FColor)
		Z_PARAM_OBJECT_OF_CLASS(tex_coord, sdl3_ce_SDL_FPoint)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property(sdl3_ce_SDL_Vertex, Z_OBJ_P(ZEND_THIS), "position", sizeof("position") - 1, position);
	zend_update_property(sdl3_ce_SDL_Vertex, Z_OBJ_P(ZEND_THIS), "color", sizeof("color") - 1, color);
	zend_update_property(sdl3_ce_SDL_Vertex, Z_OBJ_P(ZEND_THIS), "tex_coord", sizeof("tex_coord") - 1, tex_coord);
}

ZEND_FUNCTION(SDL_CreateSoftwareRenderer)
{
	zval *surface_zv;
	SDL_Surface *surface;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(surface_zv, sdl3_ce_SDL_Surface)
	ZEND_PARSE_PARAMETERS_END();

	surface = sdl3_handle_ptr(surface_zv, sdl3_ce_SDL_Surface, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	sdl3_box(return_value, SDL_CreateSoftwareRenderer(surface), sdl3_ce_SDL_Renderer);
}

ZEND_FUNCTION(SDL_DestroyRenderer)
{
	zval *renderer_zv;
	SDL_Renderer *renderer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(renderer_zv, sdl3_ce_SDL_Renderer)
	ZEND_PARSE_PARAMETERS_END();

	renderer = sdl3_handle_ptr(renderer_zv, sdl3_ce_SDL_Renderer, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	/* SDL destroys the renderer's textures with it: releasing the renderer releases the textures it keeps. */
	SDL_DestroyRenderer(renderer);
	sdl3_release(Z_OBJ_P(renderer_zv));
}

ZEND_FUNCTION(SDL_CreateTextureFromSurface)
{
	zval *renderer_zv, *surface_zv;
	SDL_Renderer *renderer;
	SDL_Surface *surface;
	SDL_Texture *texture;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(renderer_zv, sdl3_ce_SDL_Renderer)
		Z_PARAM_OBJECT_OF_CLASS(surface_zv, sdl3_ce_SDL_Surface)
	ZEND_PARSE_PARAMETERS_END();

	renderer = sdl3_handle_ptr(renderer_zv, sdl3_ce_SDL_Renderer, 1);
	surface = !EG(exception) ? sdl3_handle_ptr(surface_zv, sdl3_ce_SDL_Surface, 2) : NULL;
	if (EG(exception)) {
		RETURN_THROWS();
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	sdl3_box(return_value, texture, sdl3_ce_SDL_Texture);
	if (texture != NULL) {
		/* SDL destroys a renderer's textures with it, so the renderer's handle owns theirs. */
		sdl3_keep_handle(Z_OBJ_P(renderer_zv), Z_OBJ_P(return_value));
	}
}

/* Drops a destroyed texture from its renderer's kept list, so textures made and destroyed every frame do not pile up. */
static void sdl3_forget_texture(SDL_Texture *texture, zend_object *texture_obj)
{
	SDL_Renderer *native = SDL_GetRendererFromTexture(texture);
	zend_object *owner;
	sdl3_handle *intern;
	zend_ulong index;
	zval *zv;

	if (native == NULL) {
		return;
	}
	owner = zend_hash_index_find_ptr(&SDL3_G(boxes), (zend_ulong) (uintptr_t) native);
	if (owner == NULL) {
		return;
	}
	intern = sdl3_handle_from(owner);
	if (Z_TYPE(intern->keep) != IS_ARRAY) {
		return;
	}
	ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL(intern->keep), index, zv) {
		if (Z_TYPE_P(zv) == IS_OBJECT && Z_OBJ_P(zv) == texture_obj) {
			zend_hash_index_del(Z_ARRVAL(intern->keep), index);
			break;
		}
	} ZEND_HASH_FOREACH_END();
}

ZEND_FUNCTION(SDL_DestroyTexture)
{
	zval *texture_zv;
	SDL_Texture *texture;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(texture_zv, sdl3_ce_SDL_Texture)
	ZEND_PARSE_PARAMETERS_END();

	texture = sdl3_handle_ptr(texture_zv, sdl3_ce_SDL_Texture, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	/* The caller's argument holds the object for the call, so the kept list's reference may go first. */
	sdl3_forget_texture(texture, Z_OBJ_P(texture_zv));
	SDL_DestroyTexture(texture);
	sdl3_release(Z_OBJ_P(texture_zv));
}

ZEND_FUNCTION(SDL_SetTextureBlendMode)
{
	zval *texture_zv;
	zend_long blend_mode;
	SDL_Texture *texture;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(texture_zv, sdl3_ce_SDL_Texture)
		Z_PARAM_LONG(blend_mode)
	ZEND_PARSE_PARAMETERS_END();

	texture = sdl3_handle_ptr(texture_zv, sdl3_ce_SDL_Texture, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_SetTextureBlendMode(texture, (SDL_BlendMode) blend_mode));
}

ZEND_FUNCTION(SDL_SetTextureScaleMode)
{
	zval *texture_zv;
	zend_long scale_mode;
	SDL_Texture *texture;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(texture_zv, sdl3_ce_SDL_Texture)
		Z_PARAM_LONG(scale_mode)
	ZEND_PARSE_PARAMETERS_END();

	texture = sdl3_handle_ptr(texture_zv, sdl3_ce_SDL_Texture, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_SetTextureScaleMode(texture, (SDL_ScaleMode) scale_mode));
}

ZEND_FUNCTION(SDL_SetTextureAlphaMod)
{
	zval *texture_zv;
	zend_long alpha;
	SDL_Texture *texture;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(texture_zv, sdl3_ce_SDL_Texture)
		Z_PARAM_LONG(alpha)
	ZEND_PARSE_PARAMETERS_END();

	texture = sdl3_handle_ptr(texture_zv, sdl3_ce_SDL_Texture, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_SetTextureAlphaMod(texture, (Uint8) alpha));
}

ZEND_FUNCTION(SDL_SetTextureColorMod)
{
	zval *texture_zv;
	zend_long r, g, b;
	SDL_Texture *texture;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(texture_zv, sdl3_ce_SDL_Texture)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
	ZEND_PARSE_PARAMETERS_END();

	texture = sdl3_handle_ptr(texture_zv, sdl3_ce_SDL_Texture, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_SetTextureColorMod(texture, (Uint8) r, (Uint8) g, (Uint8) b));
}

ZEND_FUNCTION(SDL_SetRenderClipRect)
{
	zval *renderer_zv;
	zend_object *rect = NULL;
	SDL_Renderer *renderer;
	SDL_Rect native;
	const SDL_Rect *rect_ptr = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(renderer_zv, sdl3_ce_SDL_Renderer)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(rect, sdl3_ce_SDL_Rect)
	ZEND_PARSE_PARAMETERS_END();

	renderer = sdl3_handle_ptr(renderer_zv, sdl3_ce_SDL_Renderer, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	if (rect != NULL) {
		if (!sdl3_rect_read(rect, &native)) {
			RETURN_THROWS();
		}
		rect_ptr = &native;
	}

	RETURN_BOOL(SDL_SetRenderClipRect(renderer, rect_ptr));
}

static bool sdl3_SDL_FPoint_from(zend_object *obj, SDL_FPoint *out)
{
	double x, y;

	if (!sdl3_prop_double(obj, "x", &x) || !sdl3_prop_double(obj, "y", &y)) {
		return false;
	}
	out->x = (float) x;
	out->y = (float) y;
	return true;
}

/* Fills the C vertex from the PHP one. False means an exception is already set. */
static bool sdl3_SDL_Vertex_from(zend_object *obj, SDL_Vertex *out, sdl3_scratch *scratch)
{
	zend_object *child;

	memset(out, 0, sizeof(*out));
	if (!sdl3_prop_object(obj, "position", sdl3_ce_SDL_FPoint, &child) || !sdl3_SDL_FPoint_from(child, &out->position)) {
		return false;
	}
	if (!sdl3_prop_object(obj, "color", sdl3_ce_SDL_FColor, &child) || !sdl3_SDL_FColor_from(child, &out->color, scratch)) {
		return false;
	}
	if (!sdl3_prop_object(obj, "tex_coord", sdl3_ce_SDL_FPoint, &child) || !sdl3_SDL_FPoint_from(child, &out->tex_coord)) {
		return false;
	}
	return true;
}

ZEND_FUNCTION(SDL_RenderGeometry)
{
	zval *renderer_zv, *texture_zv = NULL, *item;
	HashTable *vertices, *indices = NULL;
	zend_long num_vertices, num_indices;
	SDL_Renderer *renderer;
	SDL_Texture *texture = NULL;
	SDL_Vertex *native_vertices;
	int *native_indices = NULL;
	uint32_t count, i = 0;
	sdl3_scratch scratch;
	bool drawn;

	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(renderer_zv, sdl3_ce_SDL_Renderer)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(texture_zv, sdl3_ce_SDL_Texture)
		Z_PARAM_ARRAY_HT(vertices)
		Z_PARAM_LONG(num_vertices)
		Z_PARAM_ARRAY_HT_OR_NULL(indices)
		Z_PARAM_LONG(num_indices)
	ZEND_PARSE_PARAMETERS_END();

	renderer = sdl3_handle_ptr(renderer_zv, sdl3_ce_SDL_Renderer, 1);
	if (!EG(exception) && texture_zv != NULL) {
		texture = sdl3_handle_ptr(texture_zv, sdl3_ce_SDL_Texture, 2);
	}
	if (EG(exception)) {
		RETURN_THROWS();
	}

	count = zend_hash_num_elements(vertices);
	if (!sdl3_list_count(num_vertices, count, 4, 3)) {
		RETURN_THROWS();
	}
	if (indices != NULL && !sdl3_list_count(num_indices, zend_hash_num_elements(indices), 6, 5)) {
		RETURN_THROWS();
	}

	sdl3_scratch_init(&scratch);
	native_vertices = sdl3_scratch_alloc(&scratch, sizeof(SDL_Vertex) * (count == 0 ? 1 : count));
	ZEND_HASH_FOREACH_VAL(vertices, item) {
		if (!sdl3_list_element(item, sdl3_ce_SDL_Vertex, 3)
			|| !sdl3_SDL_Vertex_from(Z_OBJ_P(item), &native_vertices[i++], &scratch)) {
			sdl3_scratch_free(&scratch);
			RETURN_THROWS();
		}
	} ZEND_HASH_FOREACH_END();

	if (indices != NULL) {
		uint32_t n = zend_hash_num_elements(indices), j = 0;

		native_indices = sdl3_scratch_alloc(&scratch, sizeof(int) * (n == 0 ? 1 : n));
		ZEND_HASH_FOREACH_VAL(indices, item) {
			native_indices[j++] = (int) zval_get_long(item);
		} ZEND_HASH_FOREACH_END();
	}

	drawn = SDL_RenderGeometry(renderer, texture, native_vertices, (int) num_vertices, native_indices, (int) num_indices);
	sdl3_scratch_free(&scratch);
	RETURN_BOOL(drawn);
}

ZEND_FUNCTION(SDL_FlushRenderer)
{
	zval *renderer_zv;
	SDL_Renderer *renderer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(renderer_zv, sdl3_ce_SDL_Renderer)
	ZEND_PARSE_PARAMETERS_END();

	renderer = sdl3_handle_ptr(renderer_zv, sdl3_ce_SDL_Renderer, 1);
	if (EG(exception)) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_FlushRenderer(renderer));
}

void sdl3_register_SDL_render(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	(void) module_number;

	sdl3_ce_SDL_Renderer = register_class_SDL_Renderer();
	sdl3_handle_setup(sdl3_ce_SDL_Renderer);
	sdl3_ce_SDL_Texture = register_class_SDL_Texture();
	sdl3_handle_setup(sdl3_ce_SDL_Texture);
	sdl3_ce_SDL_FPoint = register_class_SDL_FPoint();
	sdl3_struct_setup(sdl3_ce_SDL_FPoint);
	sdl3_ce_SDL_Vertex = register_class_SDL_Vertex();
	sdl3_struct_setup(sdl3_ce_SDL_Vertex);
}
