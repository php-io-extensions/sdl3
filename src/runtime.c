#include "runtime.h"

static zend_object_handlers sdl3_handle_handlers;
static zend_object_handlers sdl3_struct_handlers;

static zend_object *sdl3_create_object(zend_class_entry *ce)
{
	sdl3_handle *intern = zend_object_alloc(sizeof(sdl3_handle), ce);

	zend_object_std_init(&intern->std, ce);
	object_properties_init(&intern->std, ce);
	intern->std.handlers = &sdl3_handle_handlers;
	intern->ptr = NULL;
	intern->opens = 0;
	ZVAL_UNDEF(&intern->keep);

	return &intern->std;
}

static void sdl3_free_object(zend_object *object)
{
	sdl3_handle *intern = sdl3_handle_from(object);

	if (intern->ptr != NULL) {
		zend_hash_index_del(&SDL3_G(boxes), (zend_ulong) (uintptr_t) intern->ptr);
		intern->ptr = NULL;
	}

	zval_ptr_dtor(&intern->keep);
	ZVAL_UNDEF(&intern->keep);
	zend_object_std_dtor(object);
}

void sdl3_handle_setup(zend_class_entry *ce)
{
	static bool handlers_ready = false;

	if (!handlers_ready) {
		memcpy(&sdl3_handle_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
		sdl3_handle_handlers.offset = XtOffsetOf(sdl3_handle, std);
		sdl3_handle_handlers.free_obj = sdl3_free_object;
		sdl3_handle_handlers.clone_obj = NULL;
		handlers_ready = true;
	}

	ce->create_object = sdl3_create_object;
	ce->default_object_handlers = &sdl3_handle_handlers;
	ce->ce_flags |= ZEND_ACC_NOT_SERIALIZABLE | ZEND_ACC_FINAL;
}

void sdl3_struct_setup(zend_class_entry *ce)
{
	static bool handlers_ready = false;

	if (!handlers_ready) {
		memcpy(&sdl3_struct_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
		sdl3_struct_handlers.clone_obj = NULL;
		handlers_ready = true;
	}

	ce->default_object_handlers = &sdl3_struct_handlers;
	ce->ce_flags |= ZEND_ACC_NOT_SERIALIZABLE | ZEND_ACC_FINAL;
}

static void sdl3_release_kept(sdl3_handle *intern)
{
	if (Z_TYPE(intern->keep) == IS_ARRAY) {
		zval *zv;

		ZEND_HASH_FOREACH_VAL(Z_ARRVAL(intern->keep), zv) {
			if (Z_TYPE_P(zv) == IS_OBJECT && Z_OBJ_P(zv)->handlers == &sdl3_handle_handlers) {
				sdl3_release(Z_OBJ_P(zv));
			}
		} ZEND_HASH_FOREACH_END();
	} else if (Z_TYPE(intern->keep) == IS_OBJECT && Z_OBJ(intern->keep)->handlers == &sdl3_handle_handlers) {
		sdl3_release(Z_OBJ(intern->keep));
	}
}

void sdl3_release(zend_object *obj)
{
	sdl3_handle *intern = sdl3_handle_from(obj);
	intern->opens = 0;

	if (intern->ptr != NULL) {
		zend_hash_index_del(&SDL3_G(boxes), (zend_ulong) (uintptr_t) intern->ptr);
		intern->ptr = NULL;
	}

	sdl3_release_kept(intern);
	zval_ptr_dtor(&intern->keep);
	ZVAL_UNDEF(&intern->keep);
}

void sdl3_drop_kept(zend_object *owner)
{
	sdl3_handle *intern = sdl3_handle_from(owner);

	sdl3_release_kept(intern);
	zval_ptr_dtor(&intern->keep);
	ZVAL_UNDEF(&intern->keep);
}

void sdl3_keep_string(zend_object *obj, zend_string *str)
{
	sdl3_handle *intern = sdl3_handle_from(obj);

	zval_ptr_dtor(&intern->keep);
	ZVAL_STR_COPY(&intern->keep, str);
}

void sdl3_keep_handle(zend_object *owner, zend_object *child)
{
	sdl3_handle *intern = sdl3_handle_from(owner);
	zval *existing;

	if (Z_TYPE(intern->keep) != IS_ARRAY) {
		zval_ptr_dtor(&intern->keep);
		array_init(&intern->keep);
	}

	ZEND_HASH_FOREACH_VAL(Z_ARRVAL(intern->keep), existing) {
		if (Z_TYPE_P(existing) == IS_OBJECT && Z_OBJ_P(existing) == child) {
			return;
		}
	} ZEND_HASH_FOREACH_END();

	zval copy;
	ZVAL_OBJ_COPY(&copy, child);
	zend_hash_next_index_insert(Z_ARRVAL(intern->keep), &copy);
}

void sdl3_box(zval *rv, void *ptr, zend_class_entry *ce)
{
	zend_object *existing;

	if (ptr == NULL) {
		ZVAL_NULL(rv);
		return;
	}

	existing = zend_hash_index_find_ptr(&SDL3_G(boxes), (zend_ulong) (uintptr_t) ptr);
	if (existing != NULL && instanceof_function(existing->ce, ce)) {
		ZVAL_OBJ_COPY(rv, existing);
		return;
	}

	if (existing != NULL) {
		/* A different class already boxed this address. Detach it so its free_obj cannot drop the new entry. */
		sdl3_handle_from(existing)->ptr = NULL;
	}

	object_init_ex(rv, ce);
	sdl3_handle_from(Z_OBJ_P(rv))->ptr = ptr;
	zend_hash_index_update_ptr(&SDL3_G(boxes), (zend_ulong) (uintptr_t) ptr, Z_OBJ_P(rv));
}

void *sdl3_handle_ptr(zval *zv, zend_class_entry *ce, uint32_t arg_num)
{
	sdl3_handle *intern;

	if (Z_TYPE_P(zv) != IS_OBJECT || !instanceof_function(Z_OBJCE_P(zv), ce)) {
		if (arg_num == 0) {
			zend_type_error("must be an instance of %s", ZSTR_VAL(ce->name));
		} else {
			zend_argument_type_error(arg_num, "must be of type %s", ZSTR_VAL(ce->name));
		}
		return NULL;
	}

	intern = sdl3_handle_from(Z_OBJ_P(zv));
	if (intern->ptr == NULL) {
		if (arg_num == 0) {
			zend_value_error("%s has been destroyed", ZSTR_VAL(ce->name));
		} else {
			zend_argument_value_error(arg_num, "%s has been destroyed", ZSTR_VAL(ce->name));
		}
		return NULL;
	}

	return intern->ptr;
}

void sdl3_scratch_init(sdl3_scratch *scratch)
{
	scratch->head = NULL;
}

void *sdl3_scratch_alloc(sdl3_scratch *scratch, size_t bytes)
{
	sdl3_scratch_block *block = emalloc(sizeof(sdl3_scratch_block));

	block->ptr = emalloc(bytes);
	block->next = scratch->head;
	scratch->head = block;
	memset(block->ptr, 0, bytes);

	return block->ptr;
}

void sdl3_scratch_free(sdl3_scratch *scratch)
{
	sdl3_scratch_block *block = scratch->head;

	while (block != NULL) {
		sdl3_scratch_block *next = block->next;
		efree(block->ptr);
		efree(block);
		block = next;
	}

	scratch->head = NULL;
}

static zval *sdl3_read_prop(zend_object *obj, const char *name)
{
	zval *zv = zend_read_property(obj->ce, obj, name, strlen(name), 0, NULL);

	if (EG(exception) != NULL) {
		return NULL;
	}

	return zv;
}

bool sdl3_prop_long(zend_object *obj, const char *name, zend_long *out)
{
	zval *zv = sdl3_read_prop(obj, name);

	if (zv == NULL) {
		return false;
	}
	if (Z_TYPE_P(zv) != IS_LONG) {
		zend_type_error("%s::$%s must be an int", ZSTR_VAL(obj->ce->name), name);
		return false;
	}

	*out = Z_LVAL_P(zv);
	return true;
}

bool sdl3_prop_double(zend_object *obj, const char *name, double *out)
{
	zval *zv = sdl3_read_prop(obj, name);

	if (zv == NULL) {
		return false;
	}
	if (Z_TYPE_P(zv) != IS_DOUBLE) {
		zend_type_error("%s::$%s must be a float", ZSTR_VAL(obj->ce->name), name);
		return false;
	}

	*out = Z_DVAL_P(zv);
	return true;
}

bool sdl3_prop_bool(zend_object *obj, const char *name, bool *out)
{
	zval *zv = sdl3_read_prop(obj, name);

	if (zv == NULL) {
		return false;
	}
	if (Z_TYPE_P(zv) != IS_TRUE && Z_TYPE_P(zv) != IS_FALSE) {
		zend_type_error("%s::$%s must be a bool", ZSTR_VAL(obj->ce->name), name);
		return false;
	}

	*out = Z_TYPE_P(zv) == IS_TRUE;
	return true;
}

bool sdl3_prop_string(zend_object *obj, const char *name, zend_string **out)
{
	zval *zv = sdl3_read_prop(obj, name);

	if (zv == NULL) {
		return false;
	}
	if (Z_TYPE_P(zv) != IS_STRING) {
		zend_type_error("%s::$%s must be a string", ZSTR_VAL(obj->ce->name), name);
		return false;
	}

	*out = Z_STR_P(zv);
	return true;
}

bool sdl3_prop_handle(zend_object *obj, const char *name, zend_class_entry *ce, void **out)
{
	zval *zv = sdl3_read_prop(obj, name);

	if (zv == NULL) {
		return false;
	}
	if (Z_TYPE_P(zv) == IS_NULL) {
		*out = NULL;
		return true;
	}
	if (Z_TYPE_P(zv) != IS_OBJECT || !instanceof_function(Z_OBJCE_P(zv), ce)) {
		zend_type_error("%s::$%s must be null or an instance of %s", ZSTR_VAL(obj->ce->name), name, ZSTR_VAL(ce->name));
		return false;
	}

	*out = sdl3_handle_ptr(zv, ce, 0);
	return *out != NULL;
}

bool sdl3_prop_object(zend_object *obj, const char *name, zend_class_entry *ce, zend_object **out)
{
	zval *zv = sdl3_read_prop(obj, name);

	if (zv == NULL) {
		return false;
	}
	if (Z_TYPE_P(zv) != IS_OBJECT || !instanceof_function(Z_OBJCE_P(zv), ce)) {
		zend_type_error("%s::$%s must be an instance of %s", ZSTR_VAL(obj->ce->name), name, ZSTR_VAL(ce->name));
		return false;
	}

	*out = Z_OBJ_P(zv);
	return true;
}

bool sdl3_prop_list(zend_object *obj, const char *name, zend_class_entry *ce, zend_object ***items, uint32_t *count, sdl3_scratch *scratch)
{
	zval *zv = sdl3_read_prop(obj, name);
	zval *item;
	uint32_t n, i;
	zend_object **stored;

	if (zv == NULL) {
		return false;
	}
	if (Z_TYPE_P(zv) != IS_ARRAY) {
		zend_type_error("%s::$%s must be a list of %s", ZSTR_VAL(obj->ce->name), name, ZSTR_VAL(ce->name));
		return false;
	}

	n = zend_hash_num_elements(Z_ARRVAL_P(zv));
	*count = n;
	if (n == 0) {
		*items = NULL;
		return true;
	}

	stored = sdl3_scratch_alloc(scratch, sizeof(zend_object *) * n);
	i = 0;
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(zv), item) {
		if (Z_TYPE_P(item) != IS_OBJECT || !instanceof_function(Z_OBJCE_P(item), ce)) {
			zend_type_error("%s::$%s must be a list of %s", ZSTR_VAL(obj->ce->name), name, ZSTR_VAL(ce->name));
			return false;
		}
		stored[i++] = Z_OBJ_P(item);
	} ZEND_HASH_FOREACH_END();

	*items = stored;
	return true;
}

void sdl3_init_nested(zend_object *obj, const char *name, zend_class_entry *ce)
{
	zval nested;

	object_init_ex(&nested, ce);
	if (ce->constructor != NULL) {
		zend_call_known_instance_method_with_0_params(ce->constructor, Z_OBJ(nested), NULL);
		if (EG(exception) != NULL) {
			zval_ptr_dtor(&nested);
			return;
		}
	}
	zend_update_property(obj->ce, obj, name, strlen(name), &nested);
	zval_ptr_dtor(&nested);
}

void sdl3_release_all(zend_class_entry *ce)
{
	zend_object *obj;
	zend_object **found;
	uint32_t count = 0, i = 0;

	ZEND_HASH_FOREACH_PTR(&SDL3_G(boxes), obj) {
		if (obj->ce == ce) {
			count++;
		}
	} ZEND_HASH_FOREACH_END();

	if (count == 0) {
		return;
	}

	/* Collected first: releasing drops entries from the table being walked. */
	found = emalloc(sizeof(zend_object *) * count);
	ZEND_HASH_FOREACH_PTR(&SDL3_G(boxes), obj) {
		if (obj->ce == ce) {
			found[i++] = obj;
		}
	} ZEND_HASH_FOREACH_END();

	for (i = 0; i < count; i++) {
		sdl3_release(found[i]);
	}
	efree(found);
}
