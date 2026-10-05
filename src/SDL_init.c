#include "runtime.h"
#include "../stubs/SDL_init_arginfo.h"

zend_class_entry *sdl3_ce_SDL_Event;
zend_class_entry *sdl3_ce_SDL_WindowEvent;

static void sdl3_event_write(zend_object *event_obj, const SDL_Event *event)
{
	zend_update_property_long(sdl3_ce_SDL_Event, event_obj, "type", sizeof("type") - 1, (zend_long) event->type);

	if (event->type < SDL_EVENT_WINDOW_FIRST || event->type > SDL_EVENT_WINDOW_LAST) {
		return;
	}

	zval *window = zend_read_property(sdl3_ce_SDL_Event, event_obj, "window", sizeof("window") - 1, 0, NULL);
	zend_object *window_obj = Z_OBJ_P(window);
	const SDL_WindowEvent *win = &event->window;

	zend_update_property_long(sdl3_ce_SDL_WindowEvent, window_obj, "type", sizeof("type") - 1, (zend_long) win->type);
	zend_update_property_long(sdl3_ce_SDL_WindowEvent, window_obj, "timestamp", sizeof("timestamp") - 1, (zend_long) win->timestamp);
	zend_update_property_long(sdl3_ce_SDL_WindowEvent, window_obj, "windowID", sizeof("windowID") - 1, (zend_long) win->windowID);
	zend_update_property_long(sdl3_ce_SDL_WindowEvent, window_obj, "data1", sizeof("data1") - 1, (zend_long) win->data1);
	zend_update_property_long(sdl3_ce_SDL_WindowEvent, window_obj, "data2", sizeof("data2") - 1, (zend_long) win->data2);
}


ZEND_METHOD(SDL_Event, __construct)
{
	zval window;

	ZEND_PARSE_PARAMETERS_NONE();

	object_init_ex(&window, sdl3_ce_SDL_WindowEvent);
	zend_update_property(sdl3_ce_SDL_Event, Z_OBJ_P(ZEND_THIS), "window", sizeof("window") - 1, &window);
	zval_ptr_dtor(&window);
}

ZEND_FUNCTION(SDL_Init)
{
	zend_long flags;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_Init((SDL_InitFlags) flags));
}

ZEND_FUNCTION(SDL_InitSubSystem)
{
	zend_long flags;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_InitSubSystem((SDL_InitFlags) flags));
}

ZEND_FUNCTION(SDL_Quit)
{
	ZEND_PARSE_PARAMETERS_NONE();
	SDL_Quit();
}

ZEND_FUNCTION(SDL_GetError)
{
	const char *error;

	ZEND_PARSE_PARAMETERS_NONE();

	error = SDL_GetError();
	RETURN_STRING(error != NULL ? error : "");
}

ZEND_FUNCTION(SDL_GetVersion)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG(SDL_GetVersion());
}

ZEND_FUNCTION(SDL_SetHint)
{
	zend_string *name, *value;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(name)
		Z_PARAM_STR(value)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_SetHint(ZSTR_VAL(name), ZSTR_VAL(value)));
}

ZEND_FUNCTION(SDL_PumpEvents)
{
	ZEND_PARSE_PARAMETERS_NONE();
	SDL_PumpEvents();
}

ZEND_FUNCTION(SDL_PollEvent)
{
	zend_object *event = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(event, sdl3_ce_SDL_Event)
	ZEND_PARSE_PARAMETERS_END();

	SDL_Event native;
	bool got = SDL_PollEvent(event == NULL ? NULL : &native);

	if (got && event != NULL) {
		sdl3_event_write(event, &native);
	}

	RETURN_BOOL(got);
}

ZEND_FUNCTION(SDL_WaitEventTimeout)
{
	zend_object *event = NULL;
	zend_long timeout;
	SDL_Event native;
	bool got;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(event, sdl3_ce_SDL_Event)
		Z_PARAM_LONG(timeout)
	ZEND_PARSE_PARAMETERS_END();

	got = SDL_WaitEventTimeout(event == NULL ? NULL : &native, (int32_t) timeout);
	if (got && event != NULL) {
		sdl3_event_write(event, &native);
	}

	RETURN_BOOL(got);
}

void sdl3_register_SDL_init(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	register_SDL_init_symbols(module_number);

	sdl3_ce_SDL_WindowEvent = register_class_SDL_WindowEvent();
	sdl3_struct_setup(sdl3_ce_SDL_WindowEvent);
	sdl3_ce_SDL_Event = register_class_SDL_Event();
	sdl3_struct_setup(sdl3_ce_SDL_Event);
}
