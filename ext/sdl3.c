
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "sdl3.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *sdl3_sdl_audio_sdlaudio_ce;
zend_class_entry *sdl3_sdl_dialog_sdldialog_ce;
zend_class_entry *sdl3_sdl_events_sdlcategories_ce;
zend_class_entry *sdl3_sdl_events_sdlclipboardevents_ce;
zend_class_entry *sdl3_sdl_events_sdldisplayevents_ce;
zend_class_entry *sdl3_sdl_events_sdldropevents_ce;
zend_class_entry *sdl3_sdl_events_sdlevents_ce;
zend_class_entry *sdl3_sdl_events_sdleventwatch_ce;
zend_class_entry *sdl3_sdl_events_sdlkeyboard_ce;
zend_class_entry *sdl3_sdl_events_sdlkeymap_ce;
zend_class_entry *sdl3_sdl_events_sdlmouse_ce;
zend_class_entry *sdl3_sdl_events_sdlquit_ce;
zend_class_entry *sdl3_sdl_events_sdlscancodetables_ce;
zend_class_entry *sdl3_sdl_events_sdlwindowevents_ce;
zend_class_entry *sdl3_sdl_gpu_sdlgpu_ce;
zend_class_entry *sdl3_sdl_input_sdlgamepad_ce;
zend_class_entry *sdl3_sdl_input_sdljoystick_ce;
zend_class_entry *sdl3_sdl_render_sdlrender_ce;
zend_class_entry *sdl3_sdl_sdl_ce;
zend_class_entry *sdl3_sdl_sdlassert_ce;
zend_class_entry *sdl3_sdl_sdlerror_ce;
zend_class_entry *sdl3_sdl_sdllist_ce;
zend_class_entry *sdl3_sdl_sdllog_ce;
zend_class_entry *sdl3_sdl_sdlproperties_ce;
zend_class_entry *sdl3_sdl_sdlutils_ce;
zend_class_entry *sdl3_sdl_surface_sdlsurface_ce;
zend_class_entry *sdl3_sdl_timer_sdltimer_ce;
zend_class_entry *sdl3_sdl_video_sdlgl_ce;
zend_class_entry *sdl3_sdl_video_sdlvideo_ce;

ZEND_DECLARE_MODULE_GLOBALS(sdl3)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(sdl3)
{
	REGISTER_INI_ENTRIES();
	zephir_module_init();
	ZEPHIR_INIT(Sdl3_SDL_Audio_SDLAudio);
	ZEPHIR_INIT(Sdl3_SDL_Dialog_SDLDialog);
	ZEPHIR_INIT(Sdl3_SDL_Events_SDLCategories);
	ZEPHIR_INIT(Sdl3_SDL_Events_SDLClipboardEvents);
	ZEPHIR_INIT(Sdl3_SDL_Events_SDLDisplayEvents);
	ZEPHIR_INIT(Sdl3_SDL_Events_SDLDropEvents);
	ZEPHIR_INIT(Sdl3_SDL_Events_SDLEventWatch);
	ZEPHIR_INIT(Sdl3_SDL_Events_SDLEvents);
	ZEPHIR_INIT(Sdl3_SDL_Events_SDLKeyboard);
	ZEPHIR_INIT(Sdl3_SDL_Events_SDLKeymap);
	ZEPHIR_INIT(Sdl3_SDL_Events_SDLMouse);
	ZEPHIR_INIT(Sdl3_SDL_Events_SDLQuit);
	ZEPHIR_INIT(Sdl3_SDL_Events_SDLScancodeTables);
	ZEPHIR_INIT(Sdl3_SDL_Events_SDLWindowEvents);
	ZEPHIR_INIT(Sdl3_SDL_Gpu_SDLGPU);
	ZEPHIR_INIT(Sdl3_SDL_Input_SDLGamepad);
	ZEPHIR_INIT(Sdl3_SDL_Input_SDLJoystick);
	ZEPHIR_INIT(Sdl3_SDL_Render_SDLRender);
	ZEPHIR_INIT(Sdl3_SDL_SDL);
	ZEPHIR_INIT(Sdl3_SDL_SDLAssert);
	ZEPHIR_INIT(Sdl3_SDL_SDLError);
	ZEPHIR_INIT(Sdl3_SDL_SDLList);
	ZEPHIR_INIT(Sdl3_SDL_SDLLog);
	ZEPHIR_INIT(Sdl3_SDL_SDLProperties);
	ZEPHIR_INIT(Sdl3_SDL_SDLUtils);
	ZEPHIR_INIT(Sdl3_SDL_Surface_SDLSurface);
	ZEPHIR_INIT(Sdl3_SDL_Timer_SDLTimer);
	ZEPHIR_INIT(Sdl3_SDL_Video_SDLGL);
	ZEPHIR_INIT(Sdl3_SDL_Video_SDLVideo);
	
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(sdl3)
{
	
	zephir_deinitialize_memory();
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_sdl3_globals *sdl3_globals)
{
	sdl3_globals->initialized = 0;

	/* Cache Enabled */
	sdl3_globals->cache_enabled = 1;

	/* Recursive Lock */
	sdl3_globals->recursive_lock = 0;

	/* Static cache */
	memset(sdl3_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);

	
	
}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_sdl3_globals *sdl3_globals)
{
	
}

static PHP_RINIT_FUNCTION(sdl3)
{
	zend_sdl3_globals *sdl3_globals_ptr;
	sdl3_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(sdl3_globals_ptr);
	zephir_initialize_memory(sdl3_globals_ptr);

	
	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(sdl3)
{
	
	zephir_deinitialize_memory();
	return SUCCESS;
}



static PHP_MINFO_FUNCTION(sdl3)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_SDL3_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_SDL3_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_SDL3_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_SDL3_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_SDL3_ZEPVERSION);
	php_info_print_table_end();
	
	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(sdl3)
{
#if defined(COMPILE_DL_SDL3) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	php_zephir_init_globals(sdl3_globals);
	php_zephir_init_module_globals(sdl3_globals);
}

static PHP_GSHUTDOWN_FUNCTION(sdl3)
{
	
}


zend_function_entry php_sdl3_functions[] = {
	ZEND_FE_END

};

static const zend_module_dep php_sdl3_deps[] = {
	
	ZEND_MOD_END
};

zend_module_entry sdl3_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	php_sdl3_deps,
	PHP_SDL3_EXTNAME,
	php_sdl3_functions,
	PHP_MINIT(sdl3),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(sdl3),
#else
	NULL,
#endif
	PHP_RINIT(sdl3),
	PHP_RSHUTDOWN(sdl3),
	PHP_MINFO(sdl3),
	PHP_SDL3_VERSION,
	ZEND_MODULE_GLOBALS(sdl3),
	PHP_GINIT(sdl3),
	PHP_GSHUTDOWN(sdl3),
#ifdef ZEPHIR_POST_REQUEST
	PHP_PRSHUTDOWN(sdl3),
#else
	NULL,
#endif
	STANDARD_MODULE_PROPERTIES_EX
};

/* implement standard "stub" routine to introduce ourselves to Zend */
#ifdef COMPILE_DL_SDL3
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(sdl3)
#endif
