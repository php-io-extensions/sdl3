
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
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/operators.h"

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



ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLEventWatch)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Events, SDLEventWatch, sdl3, sdl_events_sdleventwatch, sdl3_sdl_events_sdleventwatch_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Events_SDLEventWatch, SDLSetEventFilter)
{
	zval *callback = NULL, callback_sub, __$null;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(0, 1, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	
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
        
}

PHP_METHOD(Sdl3_SDL_Events_SDLEventWatch, SDLGetEventFilter)
{
	zend_bool result = 0;
	
            SDL_EventFilter filter = NULL;
            void *userdata = NULL;
            result = SDL_GetEventFilter(&filter, &userdata);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Events_SDLEventWatch, SDLAddEventWatch)
{
	zend_long watch_id = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *callback, callback_sub, cb;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&cb);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(callback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &callback);
	ZEPHIR_CPY_WRT(&cb, callback);
	
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
        
	RETURN_MM_LONG(watch_id);
}

PHP_METHOD(Sdl3_SDL_Events_SDLEventWatch, SDLRemoveEventWatch)
{
	zend_bool removed = 0;
	zval *watch_id_param = NULL;
	zend_long watch_id;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(watch_id)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &watch_id_param);
	
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
        
	RETURN_BOOL(removed);
}

PHP_METHOD(Sdl3_SDL_Events_SDLEventWatch, SDLFilterEvents)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *callback, callback_sub, cb;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&cb);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(callback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &callback);
	ZEPHIR_CPY_WRT(&cb, callback);
	
            php_sdl_event_filter_context *ctx = php_sdl_event_filter_context_alloc(&cb, 0);
            SDL_FilterEvents(php_sdl_event_filter_bridge, ctx);
            php_sdl_event_filter_context_free(ctx);
        
	ZEPHIR_MM_RESTORE();
}

