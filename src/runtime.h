#ifndef SDL3_RUNTIME_H
#define SDL3_RUNTIME_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "zend_exceptions.h"
#include "php_sdl3.h"
#include <SDL3/SDL.h>

ZEND_BEGIN_MODULE_GLOBALS(sdl3)
	HashTable boxes;               /* native address => zend_object*, live handles only, not refcounted */
	HashTable hit_tests;           /* SDL_Window address => the PHP hit test SDL holds */
ZEND_END_MODULE_GLOBALS(sdl3)

ZEND_EXTERN_MODULE_GLOBALS(sdl3)
#define SDL3_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(sdl3, v)

typedef struct {
	void *ptr;                     /* the native handle; NULL once released */
	zval keep;                     /* what the native object borrows from PHP: a string, one handle, or a list of handles */
	zend_object std;
} sdl3_handle;

static zend_always_inline sdl3_handle *sdl3_handle_from(zend_object *obj)
{
	return (sdl3_handle *) ((char *) obj - XtOffsetOf(sdl3_handle, std));
}

/* The PHP object holding ptr, or a new one of class ce. NULL ptr → null. */
void sdl3_box(zval *rv, void *ptr, zend_class_entry *ce);
/* The live pointer in a handle parameter; throws ValueError ("SDL_Window has been destroyed") and answers NULL when released. */
void *sdl3_handle_ptr(zval *zv, zend_class_entry *ce, uint32_t arg_num);
/* Marks a handle released: pointer cleared, identity entry dropped, borrowed value let go. Kept handles are released too. */
void sdl3_release(zend_object *obj);
/* Releases the handles owner keeps and lets go of them; owner stays live. */
void sdl3_drop_kept(zend_object *owner);
/* Replaces keep with a copy of a PHP string the native object borrows. */
void sdl3_keep_string(zend_object *obj, zend_string *str);
/* Remembers a handle whose native lifetime ends with owner's. A second keep of the same object is a no-op. */
void sdl3_keep_handle(zend_object *owner, zend_object *child);
void sdl3_handle_setup(zend_class_entry *ce);
void sdl3_struct_setup(zend_class_entry *ce);

/* Scratch allocations that live until the caller finishes the SDL call. */
typedef struct sdl3_scratch_block {
	void *ptr;
	struct sdl3_scratch_block *next;
} sdl3_scratch_block;

typedef struct {
	sdl3_scratch_block *head;
} sdl3_scratch;

void sdl3_scratch_init(sdl3_scratch *scratch);
void *sdl3_scratch_alloc(sdl3_scratch *scratch, size_t bytes);
void sdl3_scratch_free(sdl3_scratch *scratch);

/* Property readers for struct classes. False means an exception is already set. */
bool sdl3_prop_long(zend_object *obj, const char *name, zend_long *out);
bool sdl3_prop_double(zend_object *obj, const char *name, double *out);
bool sdl3_prop_bool(zend_object *obj, const char *name, bool *out);
bool sdl3_prop_string(zend_object *obj, const char *name, zend_string **out);
bool sdl3_prop_handle(zend_object *obj, const char *name, zend_class_entry *ce, void **out);
bool sdl3_prop_object(zend_object *obj, const char *name, zend_class_entry *ce, zend_object **out);
bool sdl3_prop_list(zend_object *obj, const char *name, zend_class_entry *ce, zend_object ***items, uint32_t *count, sdl3_scratch *scratch);
void sdl3_init_nested(zend_object *obj, const char *name, zend_class_entry *ce);

/* pointer() and fromPointer() for a handle class. An address other than 0 is trusted. */
#define SDL3_POINTER_METHODS(cls) \
	ZEND_METHOD(cls, pointer) { ZEND_PARSE_PARAMETERS_NONE(); void *p = sdl3_handle_ptr(ZEND_THIS, Z_OBJCE_P(ZEND_THIS), 0); if (!p) RETURN_THROWS(); RETURN_LONG((zend_long) (uintptr_t) p); } \
	ZEND_METHOD(cls, fromPointer) { zend_long p; ZEND_PARSE_PARAMETERS_START(1, 1) Z_PARAM_LONG(p) ZEND_PARSE_PARAMETERS_END(); \
		if (p == 0) { zend_argument_value_error(1, "must not be a null address"); RETURN_THROWS(); } \
		sdl3_box(return_value, (void *) (uintptr_t) p, zend_get_called_scope(execute_data)); } \
	ZEND_METHOD(cls, __construct) { ZEND_PARSE_PARAMETERS_NONE(); zend_throw_error(NULL, "%s cannot be constructed", #cls); RETURN_THROWS(); }

extern zend_class_entry *sdl3_ce_SDL_Event;
extern zend_class_entry *sdl3_ce_SDL_WindowEvent;
extern zend_class_entry *sdl3_ce_SDL_DisplayEvent;
extern zend_class_entry *sdl3_ce_SDL_Window;
extern zend_class_entry *sdl3_ce_SDL_DisplayMode;
extern zend_class_entry *sdl3_ce_SDL_Point;
extern zend_class_entry *sdl3_ce_SDL_IOStream;
extern zend_class_entry *sdl3_ce_SDL_Surface;
extern zend_class_entry *sdl3_ce_SDL_Rect;
extern zend_class_entry *sdl3_ce_SDL_GLContext;
extern zend_class_entry *sdl3_ce_SDL_MetalView;

/* SDL_Rect <-> its PHP class. Reading false means an exception is already set. */
bool sdl3_rect_read(zend_object *obj, SDL_Rect *rect);
void sdl3_rect_write(zend_object *obj, const SDL_Rect *rect);

/* PHP hit tests: the table in GINIT, one window's on SDL_DestroyWindow, all on SDL_Quit and RSHUTDOWN. */
void sdl3_hit_tests_init(HashTable *table);
void sdl3_hit_tests_forget(SDL_Window *window);
void sdl3_hit_tests_clear(void);

void sdl3_register_SDL_init(int module_number);
void sdl3_register_SDL_video(int module_number);
void sdl3_register_SDL_surface(int module_number);
void sdl3_register_SDL_hooks(int module_number);
void sdl3_register_SDL_messagebox(int module_number);

#endif
