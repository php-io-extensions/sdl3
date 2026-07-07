namespace Sdl3\SDL\Dialog;

%{
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
}%

/**
 * SDL file dialog subsystem — async native dialogs with PHP callback bridge.
 *
 * Callbacks fire during event pumping; callers must run an event loop
 * (e.g. SDL_PollEvent / SDL_PumpEvents) for results to arrive.
 */
class SDLDialog
{
    public static function SDLShowOpenFileDialog(var callback, int window = 0, var filters = null, var default_location = null, bool allow_many = false) -> void
    {
        var cb;
        var flt;
        var loc;

        let cb = callback;
        let flt = filters;
        let loc = default_location;

        %{
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
        }%
    }

    public static function SDLShowSaveFileDialog(var callback, int window = 0, var filters = null, var default_location = null) -> void
    {
        var cb;
        var flt;
        var loc;

        let cb = callback;
        let flt = filters;
        let loc = default_location;

        %{
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
        }%
    }

    public static function SDLShowOpenFolderDialog(var callback, int window = 0, var default_location = null, bool allow_many = false) -> void
    {
        var cb;
        var loc;

        let cb = callback;
        let loc = default_location;

        %{
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
        }%
    }

    public static function SDLShowFileDialogWithProperties(int type, var callback, int props) -> void
    {
        var cb;

        let cb = callback;

        %{
            php_sdl_dialog_context *ctx = php_sdl_dialog_context_alloc(&cb, NULL);

            SDL_ShowFileDialogWithProperties(
                (SDL_FileDialogType) type,
                php_sdl_dialog_file_callback_bridge,
                ctx,
                (SDL_PropertiesID) props
            );
        }%
    }
}
