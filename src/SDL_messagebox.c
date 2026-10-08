#include "runtime.h"
#include "../stubs/SDL_messagebox_arginfo.h"

ZEND_FUNCTION(SDL_ShowSimpleMessageBox)
{
	zend_long flags;
	zend_string *title, *message;
	zval *window_zv = NULL;
	SDL_Window *window = NULL;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(flags)
		Z_PARAM_STR(title)
		Z_PARAM_STR(message)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(window_zv, sdl3_ce_SDL_Window)
	ZEND_PARSE_PARAMETERS_END();

	if (window_zv != NULL) {
		window = sdl3_handle_ptr(window_zv, sdl3_ce_SDL_Window, 4);
		if (window == NULL) {
			RETURN_THROWS();
		}
	}

	RETURN_BOOL(SDL_ShowSimpleMessageBox((SDL_MessageBoxFlags) flags, ZSTR_VAL(title), ZSTR_VAL(message), window));
}

void sdl3_register_SDL_messagebox(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	register_SDL_messagebox_symbols(module_number);
}
