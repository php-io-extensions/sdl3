
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"

#include <SDL3/SDL.h>
#include <stdio.h>

typedef struct _php_sdl_dialog_context {
    zval callback;
    SDL_DialogFileFilter *filters;
    int nfilters;
} php_sdl_dialog_context;

static bool php_sdl_dialog_filters_from_array(zval *filters_arr, SDL_DialogFileFilter **filters_out, int *nfilters_out)
{
    int count;
    int i = 0;
    zval *item;
    zval *name_entry;
    zval *pattern_entry;
    SDL_DialogFileFilter *filters;

    *filters_out = NULL;
    *nfilters_out = 0;

    if (Z_TYPE_P(filters_arr) != IS_ARRAY) {
        return true;
    }

    count = (int) zend_hash_num_elements(Z_ARRVAL_P(filters_arr));
    if (count <= 0) {
        return true;
    }

    filters = ecalloc((size_t) count, sizeof(SDL_DialogFileFilter));
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(filters_arr), item) {
        if (i >= count) {
            break;
        }
        if (Z_TYPE_P(item) != IS_ARRAY) {
            continue;
        }
        name_entry = zend_hash_str_find(Z_ARRVAL_P(item), "name", sizeof("name") - 1);
        pattern_entry = zend_hash_str_find(Z_ARRVAL_P(item), "pattern", sizeof("pattern") - 1);
        if (name_entry && Z_TYPE_P(name_entry) == IS_STRING) {
            size_t len = Z_STRLEN_P(name_entry);
            char *copy = emalloc(len + 1);
            memcpy(copy, Z_STRVAL_P(name_entry), len);
            copy[len] = '\0';
            filters[i].name = copy;
        }
        if (pattern_entry && Z_TYPE_P(pattern_entry) == IS_STRING) {
            size_t len = Z_STRLEN_P(pattern_entry);
            char *copy = emalloc(len + 1);
            memcpy(copy, Z_STRVAL_P(pattern_entry), len);
            copy[len] = '\0';
            filters[i].pattern = copy;
        }
        i++;
    } ZEND_HASH_FOREACH_END();

    *filters_out = filters;
    *nfilters_out = count;
    return true;
}

static void php_sdl_dialog_filters_free(SDL_DialogFileFilter *filters, int nfilters)
{
    if (!filters) {
        return;
    }
    for (int i = 0; i < nfilters; i++) {
        if (filters[i].name) {
            efree((void *) filters[i].name);
        }
        if (filters[i].pattern) {
            efree((void *) filters[i].pattern);
        }
    }
    efree(filters);
}

static php_sdl_dialog_context *php_sdl_dialog_context_alloc(zval *callback, zval *filters_arr)
{
    php_sdl_dialog_context *ctx = emalloc(sizeof(php_sdl_dialog_context));

    ZVAL_UNDEF(&ctx->callback);
    ZVAL_COPY(&ctx->callback, callback);
    ctx->filters = NULL;
    ctx->nfilters = 0;

    if (filters_arr != NULL && Z_TYPE_P(filters_arr) == IS_ARRAY) {
        php_sdl_dialog_filters_from_array(filters_arr, &ctx->filters, &ctx->nfilters);
    }

    return ctx;
}

static void php_sdl_dialog_context_free(php_sdl_dialog_context *ctx)
{
    if (!ctx) {
        return;
    }
    zval_ptr_dtor(&ctx->callback);
    php_sdl_dialog_filters_free(ctx->filters, ctx->nfilters);
    efree(ctx);
}

static void SDLCALL php_sdl_dialog_file_callback_bridge(void *userdata, const char * const *filelist, int filter)
{
    php_sdl_dialog_context *ctx = (php_sdl_dialog_context *) userdata;
    zval retval;
    zval params[2];
    zval files_arr;

    if (ctx == NULL) {
        return;
    }

    if (filelist == NULL) {
        ZVAL_NULL(&params[0]);
    } else if (*filelist == NULL) {
        array_init(&files_arr);
        ZVAL_COPY_VALUE(&params[0], &files_arr);
    } else {
        array_init(&files_arr);
        for (int i = 0; filelist[i] != NULL; i++) {
            add_next_index_string(&files_arr, (char *) filelist[i]);
        }
        ZVAL_COPY_VALUE(&params[0], &files_arr);
    }

    ZVAL_LONG(&params[1], (zend_long) filter);
    ZVAL_UNDEF(&retval);

    call_user_function(EG(function_table), NULL, &ctx->callback, &retval, 2, params);

    if (!Z_ISUNDEF(retval)) {
        zval_ptr_dtor(&retval);
    }
    if (filelist != NULL && *filelist != NULL) {
        zval_ptr_dtor(&params[0]);
    }

    php_sdl_dialog_context_free(ctx);
}



/**
 * SDL file dialog subsystem — async native dialogs with PHP callback bridge.
 *
 * Callbacks fire during event pumping; callers must run an event loop
 * (e.g. SDL_PollEvent / SDL_PumpEvents) for results to arrive.
 */
ZEPHIR_INIT_CLASS(Sdl3_SDL_Dialog_SDLDialog)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Dialog, SDLDialog, sdl3, sdl_dialog_sdldialog, sdl3_sdl_dialog_sdldialog_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Dialog_SDLDialog, SDLShowOpenFileDialog)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool allow_many;
	zend_long window;
	zval *callback, callback_sub, *window_param = NULL, *filters = NULL, filters_sub, *default_location = NULL, default_location_sub, *allow_many_param = NULL, __$null, cb, flt, loc;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&filters_sub);
	ZVAL_UNDEF(&default_location_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&cb);
	ZVAL_UNDEF(&flt);
	ZVAL_UNDEF(&loc);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 5)
		Z_PARAM_ZVAL(callback)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(window)
		Z_PARAM_ZVAL_OR_NULL(filters)
		Z_PARAM_ZVAL_OR_NULL(default_location)
		Z_PARAM_BOOL(allow_many)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 4, &callback, &window_param, &filters, &default_location, &allow_many_param);
	if (!window_param) {
		window = 0;
	} else {
		}
	if (!filters) {
		filters = &filters_sub;
		filters = &__$null;
	}
	if (!default_location) {
		default_location = &default_location_sub;
		default_location = &__$null;
	}
	if (!allow_many_param) {
		allow_many = 0;
	} else {
		}
	ZEPHIR_CPY_WRT(&cb, callback);
	ZEPHIR_CPY_WRT(&flt, filters);
	ZEPHIR_CPY_WRT(&loc, default_location);
	
            php_sdl_dialog_context *ctx = php_sdl_dialog_context_alloc(&cb, &flt);
            SDL_Window *win = (window != 0) ? (SDL_Window *)(uintptr_t) window : NULL;
            const char *location = (Z_TYPE_P(&loc) == IS_NULL) ? NULL : Z_STRVAL_P(&loc);

            SDL_ShowOpenFileDialog(
                php_sdl_dialog_file_callback_bridge,
                ctx,
                win,
                ctx->filters,
                ctx->nfilters,
                location,
                allow_many
            );
        
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Sdl3_SDL_Dialog_SDLDialog, SDLShowSaveFileDialog)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long window;
	zval *callback, callback_sub, *window_param = NULL, *filters = NULL, filters_sub, *default_location = NULL, default_location_sub, __$null, cb, flt, loc;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&filters_sub);
	ZVAL_UNDEF(&default_location_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&cb);
	ZVAL_UNDEF(&flt);
	ZVAL_UNDEF(&loc);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_ZVAL(callback)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(window)
		Z_PARAM_ZVAL_OR_NULL(filters)
		Z_PARAM_ZVAL_OR_NULL(default_location)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 3, &callback, &window_param, &filters, &default_location);
	if (!window_param) {
		window = 0;
	} else {
		}
	if (!filters) {
		filters = &filters_sub;
		filters = &__$null;
	}
	if (!default_location) {
		default_location = &default_location_sub;
		default_location = &__$null;
	}
	ZEPHIR_CPY_WRT(&cb, callback);
	ZEPHIR_CPY_WRT(&flt, filters);
	ZEPHIR_CPY_WRT(&loc, default_location);
	
            php_sdl_dialog_context *ctx = php_sdl_dialog_context_alloc(&cb, &flt);
            SDL_Window *win = (window != 0) ? (SDL_Window *)(uintptr_t) window : NULL;
            const char *location = (Z_TYPE_P(&loc) == IS_NULL) ? NULL : Z_STRVAL_P(&loc);

            SDL_ShowSaveFileDialog(
                php_sdl_dialog_file_callback_bridge,
                ctx,
                win,
                ctx->filters,
                ctx->nfilters,
                location
            );
        
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Sdl3_SDL_Dialog_SDLDialog, SDLShowOpenFolderDialog)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool allow_many;
	zend_long window;
	zval *callback, callback_sub, *window_param = NULL, *default_location = NULL, default_location_sub, *allow_many_param = NULL, __$null, cb, loc;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&default_location_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&cb);
	ZVAL_UNDEF(&loc);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_ZVAL(callback)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(window)
		Z_PARAM_ZVAL_OR_NULL(default_location)
		Z_PARAM_BOOL(allow_many)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 3, &callback, &window_param, &default_location, &allow_many_param);
	if (!window_param) {
		window = 0;
	} else {
		}
	if (!default_location) {
		default_location = &default_location_sub;
		default_location = &__$null;
	}
	if (!allow_many_param) {
		allow_many = 0;
	} else {
		}
	ZEPHIR_CPY_WRT(&cb, callback);
	ZEPHIR_CPY_WRT(&loc, default_location);
	
            php_sdl_dialog_context *ctx = php_sdl_dialog_context_alloc(&cb, NULL);
            SDL_Window *win = (window != 0) ? (SDL_Window *)(uintptr_t) window : NULL;
            const char *location = (Z_TYPE_P(&loc) == IS_NULL) ? NULL : Z_STRVAL_P(&loc);

            SDL_ShowOpenFolderDialog(
                php_sdl_dialog_file_callback_bridge,
                ctx,
                win,
                location,
                allow_many
            );
        
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Sdl3_SDL_Dialog_SDLDialog, SDLShowFileDialogWithProperties)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *type_param = NULL, *callback, callback_sub, *props_param = NULL, cb;
	zend_long type, props;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&cb);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(type)
		Z_PARAM_ZVAL(callback)
		Z_PARAM_LONG(props)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &type_param, &callback, &props_param);
	ZEPHIR_CPY_WRT(&cb, callback);
	
            php_sdl_dialog_context *ctx = php_sdl_dialog_context_alloc(&cb, NULL);

            SDL_ShowFileDialogWithProperties(
                (SDL_FileDialogType) type,
                php_sdl_dialog_file_callback_bridge,
                ctx,
                (SDL_PropertiesID) props
            );
        
	ZEPHIR_MM_RESTORE();
}

