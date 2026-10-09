#include "runtime.h"
#include "../stubs/SDL_init_arginfo.h"

zend_class_entry *sdl3_ce_SDL_Event;
zend_class_entry *sdl3_ce_SDL_WindowEvent;
zend_class_entry *sdl3_ce_SDL_DisplayEvent;
zend_class_entry *sdl3_ce_SDL_KeyboardEvent;
zend_class_entry *sdl3_ce_SDL_TextInputEvent;
zend_class_entry *sdl3_ce_SDL_MouseMotionEvent;
zend_class_entry *sdl3_ce_SDL_MouseButtonEvent;
zend_class_entry *sdl3_ce_SDL_MouseWheelEvent;

#define SDL3_SET_LONG(obj, field, value) \
	zend_update_property_long((obj)->ce, (obj), #field, sizeof(#field) - 1, (zend_long) (value))
#define SDL3_SET_DOUBLE(obj, field, value) \
	zend_update_property_double((obj)->ce, (obj), #field, sizeof(#field) - 1, (double) (value))
#define SDL3_SET_BOOL(obj, field, value) \
	zend_update_property_bool((obj)->ce, (obj), #field, sizeof(#field) - 1, (value) ? 1 : 0)

/* Readers for SDL_PushEvent: a false read returns false from the caller, the exception already set. */
#define SDL3_GET_LONG(obj, field, dest) \
	do { zend_long v_; if (!sdl3_prop_long((obj), #field, &v_)) return false; (dest) = v_; } while (0)
#define SDL3_GET_DOUBLE(obj, field, dest) \
	do { double v_; if (!sdl3_prop_double((obj), #field, &v_)) return false; (dest) = (float) v_; } while (0)
#define SDL3_GET_BOOL(obj, field, dest) \
	do { bool v_; if (!sdl3_prop_bool((obj), #field, &v_)) return false; (dest) = v_; } while (0)

/* The part an SDL_Event holds under $name. False: unset or replaced by PHP code, an exception is already set. */
static bool sdl3_event_part(zend_object *event_obj, const char *name, zend_class_entry *ce, zend_object **part)
{
	return sdl3_prop_object(event_obj, name, ce, part);
}

/* False: a part was unset or replaced, an exception is already set. */
static bool sdl3_event_write(zend_object *event_obj, const SDL_Event *event)
{
	zend_object *part;

	SDL3_SET_LONG(event_obj, type, event->type);

	switch (event->type) {
	case SDL_EVENT_KEY_DOWN:
	case SDL_EVENT_KEY_UP:
		if (!sdl3_event_part(event_obj, "key", sdl3_ce_SDL_KeyboardEvent, &part)) {
			return false;
		}
		SDL3_SET_LONG(part, type, event->key.type);
		SDL3_SET_LONG(part, timestamp, event->key.timestamp);
		SDL3_SET_LONG(part, windowID, event->key.windowID);
		SDL3_SET_LONG(part, which, event->key.which);
		SDL3_SET_LONG(part, scancode, event->key.scancode);
		SDL3_SET_LONG(part, key, event->key.key);
		SDL3_SET_LONG(part, mod, event->key.mod);
		SDL3_SET_LONG(part, raw, event->key.raw);
		SDL3_SET_BOOL(part, down, event->key.down);
		SDL3_SET_BOOL(part, repeat, event->key.repeat);
		return true;
	case SDL_EVENT_TEXT_INPUT:
		if (!sdl3_event_part(event_obj, "text", sdl3_ce_SDL_TextInputEvent, &part)) {
			return false;
		}
		SDL3_SET_LONG(part, type, event->text.type);
		SDL3_SET_LONG(part, timestamp, event->text.timestamp);
		SDL3_SET_LONG(part, windowID, event->text.windowID);
		zend_update_property_string(part->ce, part, "text", sizeof("text") - 1, event->text.text != NULL ? event->text.text : "");
		return true;
	case SDL_EVENT_MOUSE_MOTION:
		if (!sdl3_event_part(event_obj, "motion", sdl3_ce_SDL_MouseMotionEvent, &part)) {
			return false;
		}
		SDL3_SET_LONG(part, type, event->motion.type);
		SDL3_SET_LONG(part, timestamp, event->motion.timestamp);
		SDL3_SET_LONG(part, windowID, event->motion.windowID);
		SDL3_SET_LONG(part, which, event->motion.which);
		SDL3_SET_LONG(part, state, event->motion.state);
		SDL3_SET_DOUBLE(part, x, event->motion.x);
		SDL3_SET_DOUBLE(part, y, event->motion.y);
		SDL3_SET_DOUBLE(part, xrel, event->motion.xrel);
		SDL3_SET_DOUBLE(part, yrel, event->motion.yrel);
		return true;
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	case SDL_EVENT_MOUSE_BUTTON_UP:
		if (!sdl3_event_part(event_obj, "button", sdl3_ce_SDL_MouseButtonEvent, &part)) {
			return false;
		}
		SDL3_SET_LONG(part, type, event->button.type);
		SDL3_SET_LONG(part, timestamp, event->button.timestamp);
		SDL3_SET_LONG(part, windowID, event->button.windowID);
		SDL3_SET_LONG(part, which, event->button.which);
		SDL3_SET_LONG(part, button, event->button.button);
		SDL3_SET_BOOL(part, down, event->button.down);
		SDL3_SET_LONG(part, clicks, event->button.clicks);
		SDL3_SET_DOUBLE(part, x, event->button.x);
		SDL3_SET_DOUBLE(part, y, event->button.y);
		return true;
	case SDL_EVENT_MOUSE_WHEEL:
		if (!sdl3_event_part(event_obj, "wheel", sdl3_ce_SDL_MouseWheelEvent, &part)) {
			return false;
		}
		SDL3_SET_LONG(part, type, event->wheel.type);
		SDL3_SET_LONG(part, timestamp, event->wheel.timestamp);
		SDL3_SET_LONG(part, windowID, event->wheel.windowID);
		SDL3_SET_LONG(part, which, event->wheel.which);
		SDL3_SET_DOUBLE(part, x, event->wheel.x);
		SDL3_SET_DOUBLE(part, y, event->wheel.y);
		SDL3_SET_LONG(part, direction, event->wheel.direction);
		SDL3_SET_DOUBLE(part, mouse_x, event->wheel.mouse_x);
		SDL3_SET_DOUBLE(part, mouse_y, event->wheel.mouse_y);
		return true;
	default:
		break;
	}

	if (event->type >= SDL_EVENT_DISPLAY_FIRST && event->type <= SDL_EVENT_DISPLAY_LAST) {
		if (!sdl3_event_part(event_obj, "display", sdl3_ce_SDL_DisplayEvent, &part)) {
			return false;
		}
		SDL3_SET_LONG(part, type, event->display.type);
		SDL3_SET_LONG(part, timestamp, event->display.timestamp);
		SDL3_SET_LONG(part, displayID, event->display.displayID);
		SDL3_SET_LONG(part, data1, event->display.data1);
		SDL3_SET_LONG(part, data2, event->display.data2);
		return true;
	}

	if (event->type >= SDL_EVENT_WINDOW_FIRST && event->type <= SDL_EVENT_WINDOW_LAST) {
		if (!sdl3_event_part(event_obj, "window", sdl3_ce_SDL_WindowEvent, &part)) {
			return false;
		}
		SDL3_SET_LONG(part, type, event->window.type);
		SDL3_SET_LONG(part, timestamp, event->window.timestamp);
		SDL3_SET_LONG(part, windowID, event->window.windowID);
		SDL3_SET_LONG(part, data1, event->window.data1);
		SDL3_SET_LONG(part, data2, event->window.data2);
	}
	return true;
}

/* The C event an SDL_Event describes, for SDL_PushEvent. False: an exception is already set. */
static bool sdl3_event_read(zend_object *event_obj, SDL_Event *out)
{
	zend_long type;
	zend_object *part;

	SDL_zerop(out);
	if (!sdl3_prop_long(event_obj, "type", &type)) {
		return false;
	}

	switch ((Uint32) type) {
	case SDL_EVENT_KEY_DOWN:
	case SDL_EVENT_KEY_UP:
		if (!sdl3_prop_object(event_obj, "key", sdl3_ce_SDL_KeyboardEvent, &part)) return false;
		SDL3_GET_LONG(part, timestamp, out->key.timestamp);
		SDL3_GET_LONG(part, windowID, out->key.windowID);
		SDL3_GET_LONG(part, which, out->key.which);
		SDL3_GET_LONG(part, scancode, out->key.scancode);
		SDL3_GET_LONG(part, key, out->key.key);
		SDL3_GET_LONG(part, mod, out->key.mod);
		SDL3_GET_LONG(part, raw, out->key.raw);
		SDL3_GET_BOOL(part, down, out->key.down);
		SDL3_GET_BOOL(part, repeat, out->key.repeat);
		break;
	case SDL_EVENT_TEXT_INPUT: {
		zend_string *text;
		char *copy;

		if (!sdl3_prop_object(event_obj, "text", sdl3_ce_SDL_TextInputEvent, &part)) return false;
		SDL3_GET_LONG(part, timestamp, out->text.timestamp);
		SDL3_GET_LONG(part, windowID, out->text.windowID);
		if (!sdl3_prop_string(part, "text", &text)) return false;
		copy = SDL_strdup(ZSTR_VAL(text));
		if (copy != NULL) {
			zend_hash_next_index_insert_ptr(&SDL3_G(pushed_texts), copy);
		}
		out->text.text = copy;
		break;
	}
	case SDL_EVENT_MOUSE_MOTION:
		if (!sdl3_prop_object(event_obj, "motion", sdl3_ce_SDL_MouseMotionEvent, &part)) return false;
		SDL3_GET_LONG(part, timestamp, out->motion.timestamp);
		SDL3_GET_LONG(part, windowID, out->motion.windowID);
		SDL3_GET_LONG(part, which, out->motion.which);
		SDL3_GET_LONG(part, state, out->motion.state);
		SDL3_GET_DOUBLE(part, x, out->motion.x);
		SDL3_GET_DOUBLE(part, y, out->motion.y);
		SDL3_GET_DOUBLE(part, xrel, out->motion.xrel);
		SDL3_GET_DOUBLE(part, yrel, out->motion.yrel);
		break;
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	case SDL_EVENT_MOUSE_BUTTON_UP:
		if (!sdl3_prop_object(event_obj, "button", sdl3_ce_SDL_MouseButtonEvent, &part)) return false;
		SDL3_GET_LONG(part, timestamp, out->button.timestamp);
		SDL3_GET_LONG(part, windowID, out->button.windowID);
		SDL3_GET_LONG(part, which, out->button.which);
		SDL3_GET_LONG(part, button, out->button.button);
		SDL3_GET_BOOL(part, down, out->button.down);
		SDL3_GET_LONG(part, clicks, out->button.clicks);
		SDL3_GET_DOUBLE(part, x, out->button.x);
		SDL3_GET_DOUBLE(part, y, out->button.y);
		break;
	case SDL_EVENT_MOUSE_WHEEL:
		if (!sdl3_prop_object(event_obj, "wheel", sdl3_ce_SDL_MouseWheelEvent, &part)) return false;
		SDL3_GET_LONG(part, timestamp, out->wheel.timestamp);
		SDL3_GET_LONG(part, windowID, out->wheel.windowID);
		SDL3_GET_LONG(part, which, out->wheel.which);
		SDL3_GET_DOUBLE(part, x, out->wheel.x);
		SDL3_GET_DOUBLE(part, y, out->wheel.y);
		SDL3_GET_LONG(part, direction, out->wheel.direction);
		SDL3_GET_DOUBLE(part, mouse_x, out->wheel.mouse_x);
		SDL3_GET_DOUBLE(part, mouse_y, out->wheel.mouse_y);
		break;
	default:
		if (type >= SDL_EVENT_DISPLAY_FIRST && type <= SDL_EVENT_DISPLAY_LAST) {
			if (!sdl3_prop_object(event_obj, "display", sdl3_ce_SDL_DisplayEvent, &part)) return false;
			SDL3_GET_LONG(part, timestamp, out->display.timestamp);
			SDL3_GET_LONG(part, displayID, out->display.displayID);
			SDL3_GET_LONG(part, data1, out->display.data1);
			SDL3_GET_LONG(part, data2, out->display.data2);
		} else if (type >= SDL_EVENT_WINDOW_FIRST && type <= SDL_EVENT_WINDOW_LAST) {
			if (!sdl3_prop_object(event_obj, "window", sdl3_ce_SDL_WindowEvent, &part)) return false;
			SDL3_GET_LONG(part, timestamp, out->window.timestamp);
			SDL3_GET_LONG(part, windowID, out->window.windowID);
			SDL3_GET_LONG(part, data1, out->window.data1);
			SDL3_GET_LONG(part, data2, out->window.data2);
		}
		break;
	}

	/* Last: every part's type field is this same word of the union. */
	out->type = (Uint32) type;
	return true;
}

void sdl3_pushed_texts_clear(void)
{
	void *text;

	ZEND_HASH_FOREACH_PTR(&SDL3_G(pushed_texts), text) {
		SDL_free(text);
	} ZEND_HASH_FOREACH_END();
	zend_hash_clean(&SDL3_G(pushed_texts));
}

ZEND_METHOD(SDL_Event, __construct)
{
	zend_object *self = Z_OBJ_P(ZEND_THIS);

	ZEND_PARSE_PARAMETERS_NONE();

	sdl3_init_nested(self, "window", sdl3_ce_SDL_WindowEvent);
	sdl3_init_nested(self, "display", sdl3_ce_SDL_DisplayEvent);
	sdl3_init_nested(self, "key", sdl3_ce_SDL_KeyboardEvent);
	sdl3_init_nested(self, "text", sdl3_ce_SDL_TextInputEvent);
	sdl3_init_nested(self, "motion", sdl3_ce_SDL_MouseMotionEvent);
	sdl3_init_nested(self, "button", sdl3_ce_SDL_MouseButtonEvent);
	sdl3_init_nested(self, "wheel", sdl3_ce_SDL_MouseWheelEvent);
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

ZEND_FUNCTION(SDL_QuitSubSystem)
{
	zend_long flags;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();

	SDL_QuitSubSystem((SDL_InitFlags) flags);
	sdl3_input_subsystems_gone();
	if ((SDL_WasInit(SDL_INIT_EVENTS) & SDL_INIT_EVENTS) == 0) {
		sdl3_pushed_texts_clear();
	}
}

ZEND_FUNCTION(SDL_Quit)
{
	ZEND_PARSE_PARAMETERS_NONE();
	sdl3_hit_tests_clear();
	SDL_Quit();
	sdl3_input_subsystems_gone();
	sdl3_pushed_texts_clear();
}

ZEND_FUNCTION(SDL_GetError)
{
	const char *error;

	ZEND_PARSE_PARAMETERS_NONE();

	error = SDL_GetError();
	RETURN_STRING(error != NULL ? error : "");
}

ZEND_FUNCTION(SDL_ClearError)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_BOOL(SDL_ClearError());
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

	if (got && event != NULL && !sdl3_event_write(event, &native)) {
		RETURN_THROWS();
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
	if (got && event != NULL && !sdl3_event_write(event, &native)) {
		RETURN_THROWS();
	}

	RETURN_BOOL(got);
}

ZEND_FUNCTION(SDL_PushEvent)
{
	zend_object *event;
	SDL_Event native;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(event, sdl3_ce_SDL_Event)
	ZEND_PARSE_PARAMETERS_END();

	if (!sdl3_event_read(event, &native)) {
		RETURN_THROWS();
	}

	RETURN_BOOL(SDL_PushEvent(&native));
}

ZEND_FUNCTION(SDL_SetEventEnabled)
{
	zend_long type;
	bool enabled;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(type)
		Z_PARAM_BOOL(enabled)
	ZEND_PARSE_PARAMETERS_END();

	SDL_SetEventEnabled((Uint32) type, enabled);
}

ZEND_FUNCTION(SDL_EventEnabled)
{
	zend_long type;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(type)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_EventEnabled((Uint32) type));
}

void sdl3_register_SDL_init(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	register_SDL_init_symbols(module_number);

	sdl3_ce_SDL_WindowEvent = register_class_SDL_WindowEvent();
	sdl3_struct_setup(sdl3_ce_SDL_WindowEvent);
	sdl3_ce_SDL_DisplayEvent = register_class_SDL_DisplayEvent();
	sdl3_struct_setup(sdl3_ce_SDL_DisplayEvent);
	sdl3_ce_SDL_KeyboardEvent = register_class_SDL_KeyboardEvent();
	sdl3_struct_setup(sdl3_ce_SDL_KeyboardEvent);
	sdl3_ce_SDL_TextInputEvent = register_class_SDL_TextInputEvent();
	sdl3_struct_setup(sdl3_ce_SDL_TextInputEvent);
	sdl3_ce_SDL_MouseMotionEvent = register_class_SDL_MouseMotionEvent();
	sdl3_struct_setup(sdl3_ce_SDL_MouseMotionEvent);
	sdl3_ce_SDL_MouseButtonEvent = register_class_SDL_MouseButtonEvent();
	sdl3_struct_setup(sdl3_ce_SDL_MouseButtonEvent);
	sdl3_ce_SDL_MouseWheelEvent = register_class_SDL_MouseWheelEvent();
	sdl3_struct_setup(sdl3_ce_SDL_MouseWheelEvent);
	sdl3_ce_SDL_Event = register_class_SDL_Event();
	sdl3_struct_setup(sdl3_ce_SDL_Event);
}
