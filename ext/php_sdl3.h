
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_SDL3_H
#define PHP_SDL3_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_SDL3_NAME        "sdl3"
#define PHP_SDL3_VERSION     "0.5.0"
#define PHP_SDL3_EXTNAME     "sdl3"
#define PHP_SDL3_AUTHOR      "Project Saturn Studios, LLC"
#define PHP_SDL3_ZEPVERSION  "0.19.0-$Id$"
#define PHP_SDL3_DESCRIPTION "PHP-Controllable SDL3 Rendering Extension"



ZEND_BEGIN_MODULE_GLOBALS(sdl3)

	int initialized;

	/** Function cache */
	HashTable *fcache;

	zephir_fcall_cache_entry *scache[ZEPHIR_MAX_CACHE_SLOTS];

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	
ZEND_END_MODULE_GLOBALS(sdl3)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(sdl3)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(sdl3, v)
#else
	#define ZEPHIR_GLOBAL(v) (sdl3_globals.v)
#endif

#ifdef ZTS
	ZEND_TSRMLS_CACHE_EXTERN()
	#define ZEPHIR_VGLOBAL ((zend_sdl3_globals *) (*((void ***) tsrm_get_ls_cache()))[TSRM_UNSHUFFLE_RSRC_ID(sdl3_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(sdl3_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def sdl3_globals
#define zend_zephir_globals_def zend_sdl3_globals

extern zend_module_entry sdl3_module_entry;
#define phpext_sdl3_ptr &sdl3_module_entry

#endif
