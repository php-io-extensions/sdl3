namespace Sdl3\SDL\Events;

%{
#include <SDL3/SDL.h>
#include <stdio.h>

typedef struct _php_sdl_event_filter_context {
    zval callback;
    zend_long id;
} php_sdl_event_filter_context;

static php_sdl_event_filter_context *php_sdl_global_event_filter = NULL;
static HashTable php_sdl_event_watch_map;
static bool php_sdl_event_watch_map_initialized = false;
static zend_long php_sdl_next_event_watch_id = 1;

static void php_sdl_event_watch_ensure_map(void)
{
    if (!php_sdl_event_watch_map_initialized) {
        zend_hash_init(&php_sdl_event_watch_map, 8, NULL, ZVAL_PTR_DTOR, 0);
        php_sdl_event_watch_map_initialized = true;
    }
}

static php_sdl_event_filter_context *php_sdl_event_filter_context_alloc(zval *callback, zend_long id)
{
    php_sdl_event_filter_context *ctx = emalloc(sizeof(php_sdl_event_filter_context));
    ZVAL_UNDEF(&ctx->callback);
    ZVAL_COPY(&ctx->callback, callback);
    ctx->id = id;
    return ctx;
}

static void php_sdl_event_filter_context_free(php_sdl_event_filter_context *ctx)
{
    if (!ctx) {
        return;
    }

    zval_ptr_dtor(&ctx->callback);
    efree(ctx);
}

static bool SDLCALL php_sdl_event_filter_bridge(void *userdata, SDL_Event *event)
{
    php_sdl_event_filter_context *ctx = (php_sdl_event_filter_context *) userdata;
    zval retval;
    zval params[2];
    bool accepted = true;

    if (ctx == NULL || event == NULL) {
        return true;
    }

    ZVAL_LONG(&params[0], (zend_long) (uintptr_t) event);
    ZVAL_LONG(&params[1], (zend_long) event->type);
    ZVAL_UNDEF(&retval);

    if (call_user_function(EG(function_table), NULL, &ctx->callback, &retval, 2, params) == SUCCESS) {
        accepted = zend_is_true(&retval);
    }

    if (!Z_ISUNDEF(retval)) {
        zval_ptr_dtor(&retval);
    }

    return accepted;
}
}%

class SDLEventWatch
{
    public static function SDLSetEventFilter(var callback = null) -> void
    {
        %{
            if (php_sdl_global_event_filter != NULL) {
                php_sdl_event_filter_context_free(php_sdl_global_event_filter);
                php_sdl_global_event_filter = NULL;
            }

            if (Z_TYPE_P(&callback) == IS_NULL) {
                SDL_SetEventFilter(NULL, NULL);
            } else {
                php_sdl_global_event_filter = php_sdl_event_filter_context_alloc(&callback, 0);
                SDL_SetEventFilter(php_sdl_event_filter_bridge, php_sdl_global_event_filter);
            }
        }%
    }

    public static function SDLGetEventFilter() -> bool
    {
        bool result;

        %{
            SDL_EventFilter filter = NULL;
            void *userdata = NULL;
            result = SDL_GetEventFilter(&filter, &userdata);
        }%

        return result;
    }

    public static function SDLAddEventWatch(var callback) -> int
    {
        int watch_id;
        var cb;

        let cb = callback;

        %{
            php_sdl_event_filter_context *ctx = php_sdl_event_filter_context_alloc(&cb, php_sdl_next_event_watch_id++);
            bool added = SDL_AddEventWatch(php_sdl_event_filter_bridge, ctx);

            if (!added) {
                php_sdl_event_filter_context_free(ctx);
                watch_id = 0;
            } else {
                zval zv;

                php_sdl_event_watch_ensure_map();
                ZVAL_PTR(&zv, ctx);
                zend_hash_index_update(&php_sdl_event_watch_map, (zend_ulong) ctx->id, &zv);
                watch_id = (zend_long) ctx->id;
            }
        }%

        return watch_id;
    }

    public static function SDLRemoveEventWatch(int watch_id) -> bool
    {
        bool removed;

        %{
            zval *zv = NULL;

            removed = false;
            if (php_sdl_event_watch_map_initialized) {
                zv = zend_hash_index_find(&php_sdl_event_watch_map, (zend_ulong) watch_id);
                if (zv != NULL) {
                    php_sdl_event_filter_context *ctx = (php_sdl_event_filter_context *) Z_PTR_P(zv);
                    SDL_RemoveEventWatch(php_sdl_event_filter_bridge, ctx);
                    php_sdl_event_filter_context_free(ctx);
                    zend_hash_index_del(&php_sdl_event_watch_map, (zend_ulong) watch_id);
                    removed = true;
                }
            }
        }%

        return removed;
    }

    public static function SDLFilterEvents(var callback) -> void
    {
        var cb;

        let cb = callback;

        %{
            php_sdl_event_filter_context *ctx = php_sdl_event_filter_context_alloc(&cb, 0);
            SDL_FilterEvents(php_sdl_event_filter_bridge, ctx);
            php_sdl_event_filter_context_free(ctx);
        }%
    }
}
