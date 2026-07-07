
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


ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLScancodeTables)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Events, SDLScancodeTables, sdl3, sdl_events_sdlscancodetables, NULL, 0);

	return SUCCESS;
}

