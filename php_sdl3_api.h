/*
 * The object model another extension builds on: include this, add
 * -I$(php-config --include-dir)/ext/sdl3, declare ZEND_MOD_REQUIRED("sdl3"),
 * and load after sdl3. Its handle classes are boxed in sdl3's registry
 * (sdl3_box, sdl3_release), take sdl3's handles (sdl3_handle_ptr) and call
 * sdl3's helpers; the symbols resolve against the loaded sdl3.so.
 */

#ifndef PHP_SDL3_API_H
#define PHP_SDL3_API_H

#include "src/runtime.h"

#endif
