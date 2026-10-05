#ifndef PHP_SDL3_H
#define PHP_SDL3_H

extern zend_module_entry sdl3_module_entry;
#define phpext_sdl3_ptr &sdl3_module_entry

#define PHP_SDL3_VERSION "0.10.0"

#if defined(ZTS) && defined(COMPILE_DL_SDL3)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif
