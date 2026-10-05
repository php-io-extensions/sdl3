PHP_ARG_ENABLE([sdl3],
  [whether to enable sdl3 support],
  [AS_HELP_STRING([--enable-sdl3], [Enable the SDL 3 bindings])],
  [no])

if test "$PHP_SDL3" != "no"; then
  PKG_CHECK_MODULES([SDL3], [sdl3 >= 3.2.0])
  PHP_EVAL_INCLINE([$SDL3_CFLAGS])
  PHP_EVAL_LIBLINE([$SDL3_LIBS], [SDL3_SHARED_LIBADD])
  PHP_SUBST([SDL3_SHARED_LIBADD])

  PHP_NEW_EXTENSION([sdl3],
    [src/sdl3.c src/runtime.c src/SDL_init.c src/SDL_video.c src/SDL_surface.c src/SDL_hooks.c src/SDL_gpu_types.c src/SDL_gpu.c src/SDL_gpu_pass.c],
    [$ext_shared],, [-DZEND_ENABLE_STATIC_TSRMLS_CACHE=1])
  PHP_ADD_BUILD_DIR([$ext_builddir/src])
fi
