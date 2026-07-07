PHP_ARG_ENABLE(sdl3, whether to enable sdl3, [ --enable-sdl3   Enable Sdl3])

if test "$PHP_SDL3" = "yes"; then

	dnl GCC 14 promoted several long-standing warnings to hard errors by default
	dnl (-Wincompatible-pointer-types, -Wint-conversion, -Wimplicit-function-declaration,
	dnl -Wimplicit-int). Zephir-generated C code (both kernel/ and .zep.c files) trips
	dnl these in spots that are dead-code or type-punned but runtime-safe, and has
	dnl built cleanly on gcc <= 13 and clang for years. Demote them back to warnings
	dnl so newer distros (Debian Trixie, Ubuntu 24.10+, Fedora 40+) can build the
	dnl extension. Each flag is silently ignored by compilers that don't know it.
	CFLAGS="$CFLAGS -Wno-error=incompatible-pointer-types -Wno-error=int-conversion -Wno-error=implicit-function-declaration -Wno-error=implicit-int"

	AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
	if test "x$PKG_CONFIG" = "xno"; then
		AC_MSG_RESULT([pkg-config not found])
		AC_MSG_ERROR([Please reinstall the pkg-config distribution])
	fi


	AC_MSG_CHECKING([for sdl3])
	if $PKG_CONFIG --exists sdl3; then
		PHP_SDL3_VERSION=`$PKG_CONFIG sdl3 --modversion`
		PHP_SDL3_PREFIX=`$PKG_CONFIG sdl3 --variable=prefix`

		if $PKG_CONFIG --atleast-version=0.0.0 sdl3; then
			AC_MSG_RESULT([found version $PHP_SDL3_VERSION, under $PHP_SDL3_PREFIX])
			PHP_SDL3_LIBS=`$PKG_CONFIG sdl3 --libs`
			PHP_SDL3_INCS=`$PKG_CONFIG sdl3 --cflags`

			PHP_EVAL_LIBLINE($PHP_SDL3_LIBS, SDL3_SHARED_LIBADD)
			PHP_EVAL_INCLINE($PHP_SDL3_INCS)
		else
			AC_MSG_ERROR(Requested 'sdl3 >= 0.0.0' but version of sdl3 is $PHP_SDL3_VERSION)
		fi
	else
		AC_MSG_ERROR(Unable to find sdl3 installation)
	fi



	if ! test "x-L/opt/homebrew/lib -L/usr/local/lib -lSDL3" = "x"; then
		PHP_EVAL_LIBLINE(-L/opt/homebrew/lib -L/usr/local/lib -lSDL3, SDL3_SHARED_LIBADD)
	fi

	AC_DEFINE(HAVE_SDL3, 1, [Whether you have Sdl3])
	sdl3_sources="sdl3.c kernel/main.c kernel/memory.c kernel/exception.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c sdl3/sdl/audio/sdlaudio.zep.c
	sdl3/sdl/dialog/sdldialog.zep.c
	sdl3/sdl/events/sdlcategories.zep.c
	sdl3/sdl/events/sdlclipboardevents.zep.c
	sdl3/sdl/events/sdldisplayevents.zep.c
	sdl3/sdl/events/sdldropevents.zep.c
	sdl3/sdl/events/sdlevents.zep.c
	sdl3/sdl/events/sdleventwatch.zep.c
	sdl3/sdl/events/sdlkeyboard.zep.c
	sdl3/sdl/events/sdlkeymap.zep.c
	sdl3/sdl/events/sdlmouse.zep.c
	sdl3/sdl/events/sdlquit.zep.c
	sdl3/sdl/events/sdlscancodetables.zep.c
	sdl3/sdl/events/sdlwindowevents.zep.c
	sdl3/sdl/gpu/sdlgpu.zep.c
	sdl3/sdl/input/sdlgamepad.zep.c
	sdl3/sdl/input/sdljoystick.zep.c
	sdl3/sdl/render/sdlrender.zep.c
	sdl3/sdl/sdl.zep.c
	sdl3/sdl/sdlassert.zep.c
	sdl3/sdl/sdlerror.zep.c
	sdl3/sdl/sdllist.zep.c
	sdl3/sdl/sdllog.zep.c
	sdl3/sdl/sdlproperties.zep.c
	sdl3/sdl/sdlutils.zep.c
	sdl3/sdl/surface/sdlsurface.zep.c
	sdl3/sdl/timer/sdltimer.zep.c
	sdl3/sdl/video/sdlgl.zep.c
	sdl3/sdl/video/sdlvideo.zep.c "
	PHP_NEW_EXTENSION(sdl3, $sdl3_sources, $ext_shared,, -I/opt/homebrew/include/SDL3 -I/usr/local/include/SDL3 $PHP_SDL3_INCS )
	PHP_ADD_BUILD_DIR([$ext_builddir/kernel/])
	for dir in "sdl3/sdl sdl3/sdl/audio sdl3/sdl/dialog sdl3/sdl/events sdl3/sdl/gpu sdl3/sdl/input sdl3/sdl/render sdl3/sdl/surface sdl3/sdl/timer sdl3/sdl/video"; do
		PHP_ADD_BUILD_DIR([$ext_builddir/$dir])
	done
	PHP_SUBST(SDL3_SHARED_LIBADD)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([sdl3], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([sdl3], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS

	PHP_INSTALL_HEADERS([ext/sdl3], [php_SDL3.h])

fi
