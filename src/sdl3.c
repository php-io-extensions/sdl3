/*
 * sdl3: 1:1 bindings of SDL 3 at the 3.2 API. Handles, structs and constants
 * keep their C names. Dropping the last PHP reference does not destroy the
 * native object.
 */

#include "runtime.h"
#include "SDL_gpu_types.h"
#include "ext/standard/info.h"

ZEND_DECLARE_MODULE_GLOBALS(sdl3)

static PHP_GINIT_FUNCTION(sdl3)
{
#if defined(COMPILE_DL_SDL3) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	zend_hash_init(&sdl3_globals->boxes, 64, NULL, NULL, 1);
	sdl3_hit_tests_init(&sdl3_globals->hit_tests);
	zend_hash_init(&sdl3_globals->pushed_texts, 8, NULL, NULL, 1);
}

static PHP_GSHUTDOWN_FUNCTION(sdl3)
{
	void *text;

	ZEND_HASH_FOREACH_PTR(&sdl3_globals->pushed_texts, text) {
		SDL_free(text);
	} ZEND_HASH_FOREACH_END();
	zend_hash_destroy(&sdl3_globals->pushed_texts);
	zend_hash_destroy(&sdl3_globals->boxes);
	zend_hash_destroy(&sdl3_globals->hit_tests);
}

PHP_MINIT_FUNCTION(sdl3)
{
	sdl3_register_SDL_init(module_number);
	sdl3_register_SDL_video(module_number);
	sdl3_register_SDL_surface(module_number);
	sdl3_register_SDL_hooks(module_number);
	sdl3_register_SDL_messagebox(module_number);
	sdl3_register_SDL_input(module_number);
	sdl3_register_SDL_gpu_types(module_number);
	sdl3_register_SDL_gpu(module_number);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(sdl3)
{
#if defined(COMPILE_DL_SDL3) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(sdl3)
{
	/* The callbacks are request memory; SDL must not reach them after the request. */
	sdl3_hit_tests_clear();
	/* A text event still queued would point at freed bytes in the next request. */
	if (SDL_WasInit(SDL_INIT_EVENTS) & SDL_INIT_EVENTS) {
		SDL_FlushEvent(SDL_EVENT_TEXT_INPUT);
	}
	sdl3_pushed_texts_clear();
	return SUCCESS;
}

PHP_MINFO_FUNCTION(sdl3)
{
	int version = SDL_GetVersion();
	char decoded[32];

	snprintf(decoded, sizeof(decoded), "%d.%d.%d",
		version / 1000000, (version / 1000) % 1000, version % 1000);

	php_info_print_table_start();
	php_info_print_table_row(2, "sdl3 support", "enabled");
	php_info_print_table_row(2, "Version", PHP_SDL3_VERSION);
	php_info_print_table_row(2, "SDL version", decoded);
	php_info_print_table_end();
}

zend_module_entry sdl3_module_entry = {
	STANDARD_MODULE_HEADER,
	"sdl3",
	NULL,
	PHP_MINIT(sdl3),
	NULL,
	PHP_RINIT(sdl3),
	PHP_RSHUTDOWN(sdl3),
	PHP_MINFO(sdl3),
	PHP_SDL3_VERSION,
	PHP_MODULE_GLOBALS(sdl3),
	PHP_GINIT(sdl3),
	PHP_GSHUTDOWN(sdl3),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_SDL3
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(sdl3)
#endif
