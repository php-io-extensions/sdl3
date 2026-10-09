#include "runtime.h"
#include "../stubs/SDL_input_arginfo.h"

zend_class_entry *sdl3_ce_SDL_Gamepad;
zend_class_entry *sdl3_ce_SDL_Joystick;
zend_class_entry *sdl3_ce_SDL_VirtualJoystickDesc;

SDL3_POINTER_METHODS(SDL_Gamepad)
SDL3_POINTER_METHODS(SDL_Joystick)

/* The live pointer of handle argument 1, or the function throws. */
#define SDL3_ARG_HANDLE(var, type, zv, ce) \
	type *var = sdl3_handle_ptr((zv), (ce), 1); \
	if (var == NULL) { RETURN_THROWS(); }

/* One more open of the handle in return_value: SDL counts opens of a device and returns the same pointer. */
static void sdl3_opened(zval *return_value)
{
	if (Z_TYPE_P(return_value) == IS_OBJECT) {
		sdl3_handle_from(Z_OBJ_P(return_value))->opens++;
	}
}

/* One open fewer: the handle is released with the last close. */
static void sdl3_closed(zval *handle)
{
	sdl3_handle *intern = sdl3_handle_from(Z_OBJ_P(handle));

	if (intern->opens > 0) {
		intern->opens--;
	}
	if (intern->opens == 0) {
		sdl3_release(Z_OBJ_P(handle));
	}
}

static void sdl3_id_list(zval *return_value, SDL_JoystickID *ids, int count)
{
	array_init_size(return_value, count > 0 ? (uint32_t) count : 0);
	for (int i = 0; ids != NULL && i < count; i++) {
		add_next_index_long(return_value, (zend_long) ids[i]);
	}
	SDL_free(ids);
}

void sdl3_input_subsystems_gone(void)
{
	/* SDL frees every open gamepad when the gamepad subsystem goes down, joysticks or not. */
	if ((SDL_WasInit(SDL_INIT_GAMEPAD) & SDL_INIT_GAMEPAD) == 0) {
		sdl3_release_all(sdl3_ce_SDL_Gamepad);
	}
	if ((SDL_WasInit(SDL_INIT_JOYSTICK) & SDL_INIT_JOYSTICK) == 0) {
		sdl3_release_all(sdl3_ce_SDL_Joystick);
	}
}

ZEND_FUNCTION(SDL_GetKeyboardFocus)
{
	ZEND_PARSE_PARAMETERS_NONE();
	sdl3_box(return_value, SDL_GetKeyboardFocus(), sdl3_ce_SDL_Window);
}

ZEND_FUNCTION(SDL_StartTextInput)
{
	zval *zv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Window)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(window, SDL_Window, zv, sdl3_ce_SDL_Window);
	RETURN_BOOL(SDL_StartTextInput(window));
}

ZEND_FUNCTION(SDL_StopTextInput)
{
	zval *zv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Window)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(window, SDL_Window, zv, sdl3_ce_SDL_Window);
	RETURN_BOOL(SDL_StopTextInput(window));
}

ZEND_FUNCTION(SDL_TextInputActive)
{
	zval *zv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Window)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(window, SDL_Window, zv, sdl3_ce_SDL_Window);
	RETURN_BOOL(SDL_TextInputActive(window));
}

ZEND_FUNCTION(SDL_GetGamepads)
{
	int count = 0;
	SDL_JoystickID *ids;

	ZEND_PARSE_PARAMETERS_NONE();
	ids = SDL_GetGamepads(&count);
	sdl3_id_list(return_value, ids, count);
}

ZEND_FUNCTION(SDL_IsGamepad)
{
	zend_long id;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(id)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_IsGamepad((SDL_JoystickID) id));
}

ZEND_FUNCTION(SDL_OpenGamepad)
{
	zend_long id;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(id)
	ZEND_PARSE_PARAMETERS_END();

	sdl3_box(return_value, SDL_OpenGamepad((SDL_JoystickID) id), sdl3_ce_SDL_Gamepad);
	sdl3_opened(return_value);
}

ZEND_FUNCTION(SDL_CloseGamepad)
{
	zval *zv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Gamepad)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(gamepad, SDL_Gamepad, zv, sdl3_ce_SDL_Gamepad);
	SDL_CloseGamepad(gamepad);
	sdl3_closed(zv);
}

ZEND_FUNCTION(SDL_GetGamepadName)
{
	zval *zv;
	const char *name;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Gamepad)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(gamepad, SDL_Gamepad, zv, sdl3_ce_SDL_Gamepad);
	name = SDL_GetGamepadName(gamepad);
	if (name == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(name);
}

ZEND_FUNCTION(SDL_GetGamepadID)
{
	zval *zv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Gamepad)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(gamepad, SDL_Gamepad, zv, sdl3_ce_SDL_Gamepad);
	RETURN_LONG((zend_long) SDL_GetGamepadID(gamepad));
}

ZEND_FUNCTION(SDL_GetGamepadSerial)
{
	zval *zv;
	const char *serial;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Gamepad)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(gamepad, SDL_Gamepad, zv, sdl3_ce_SDL_Gamepad);
	serial = SDL_GetGamepadSerial(gamepad);
	if (serial == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(serial);
}

ZEND_FUNCTION(SDL_GetGamepadPath)
{
	zval *zv;
	const char *path;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Gamepad)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(gamepad, SDL_Gamepad, zv, sdl3_ce_SDL_Gamepad);
	path = SDL_GetGamepadPath(gamepad);
	if (path == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(path);
}

ZEND_FUNCTION(SDL_GetGamepadPlayerIndex)
{
	zval *zv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Gamepad)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(gamepad, SDL_Gamepad, zv, sdl3_ce_SDL_Gamepad);
	RETURN_LONG((zend_long) SDL_GetGamepadPlayerIndex(gamepad));
}

ZEND_FUNCTION(SDL_SetGamepadPlayerIndex)
{
	zval *zv;
	zend_long player_index;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Gamepad)
		Z_PARAM_LONG(player_index)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(gamepad, SDL_Gamepad, zv, sdl3_ce_SDL_Gamepad);
	RETURN_BOOL(SDL_SetGamepadPlayerIndex(gamepad, (int) player_index));
}

ZEND_FUNCTION(SDL_GetGamepadButton)
{
	zval *zv;
	zend_long button;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Gamepad)
		Z_PARAM_LONG(button)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(gamepad, SDL_Gamepad, zv, sdl3_ce_SDL_Gamepad);
	RETURN_BOOL(SDL_GetGamepadButton(gamepad, (SDL_GamepadButton) button));
}

ZEND_FUNCTION(SDL_GetGamepadAxis)
{
	zval *zv;
	zend_long axis;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Gamepad)
		Z_PARAM_LONG(axis)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(gamepad, SDL_Gamepad, zv, sdl3_ce_SDL_Gamepad);
	RETURN_LONG((zend_long) SDL_GetGamepadAxis(gamepad, (SDL_GamepadAxis) axis));
}

ZEND_FUNCTION(SDL_UpdateGamepads)
{
	ZEND_PARSE_PARAMETERS_NONE();
	SDL_UpdateGamepads();
}

ZEND_FUNCTION(SDL_GetJoysticks)
{
	int count = 0;
	SDL_JoystickID *ids;

	ZEND_PARSE_PARAMETERS_NONE();
	ids = SDL_GetJoysticks(&count);
	sdl3_id_list(return_value, ids, count);
}

ZEND_FUNCTION(SDL_OpenJoystick)
{
	zend_long id;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(id)
	ZEND_PARSE_PARAMETERS_END();

	sdl3_box(return_value, SDL_OpenJoystick((SDL_JoystickID) id), sdl3_ce_SDL_Joystick);
	sdl3_opened(return_value);
}

ZEND_FUNCTION(SDL_CloseJoystick)
{
	zval *zv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	SDL_CloseJoystick(joystick);
	sdl3_closed(zv);
}

ZEND_FUNCTION(SDL_GetJoystickName)
{
	zval *zv;
	const char *name;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	name = SDL_GetJoystickName(joystick);
	if (name == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(name);
}

ZEND_FUNCTION(SDL_GetJoystickSerial)
{
	zval *zv;
	const char *serial;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	serial = SDL_GetJoystickSerial(joystick);
	if (serial == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(serial);
}

ZEND_FUNCTION(SDL_GetJoystickPath)
{
	zval *zv;
	const char *path;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	path = SDL_GetJoystickPath(joystick);
	if (path == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(path);
}

ZEND_FUNCTION(SDL_GetJoystickPlayerIndex)
{
	zval *zv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	RETURN_LONG((zend_long) SDL_GetJoystickPlayerIndex(joystick));
}

ZEND_FUNCTION(SDL_SetJoystickPlayerIndex)
{
	zval *zv;
	zend_long player_index;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
		Z_PARAM_LONG(player_index)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	RETURN_BOOL(SDL_SetJoystickPlayerIndex(joystick, (int) player_index));
}

ZEND_FUNCTION(SDL_GetNumJoystickAxes)
{
	zval *zv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	RETURN_LONG(SDL_GetNumJoystickAxes(joystick));
}

ZEND_FUNCTION(SDL_GetNumJoystickButtons)
{
	zval *zv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	RETURN_LONG(SDL_GetNumJoystickButtons(joystick));
}

ZEND_FUNCTION(SDL_GetNumJoystickHats)
{
	zval *zv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	RETURN_LONG(SDL_GetNumJoystickHats(joystick));
}

ZEND_FUNCTION(SDL_GetJoystickAxis)
{
	zval *zv;
	zend_long axis;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
		Z_PARAM_LONG(axis)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	RETURN_LONG((zend_long) SDL_GetJoystickAxis(joystick, (int) axis));
}

ZEND_FUNCTION(SDL_GetJoystickButton)
{
	zval *zv;
	zend_long button;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
		Z_PARAM_LONG(button)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	RETURN_BOOL(SDL_GetJoystickButton(joystick, (int) button));
}

ZEND_FUNCTION(SDL_GetJoystickHat)
{
	zval *zv;
	zend_long hat;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
		Z_PARAM_LONG(hat)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	RETURN_LONG((zend_long) SDL_GetJoystickHat(joystick, (int) hat));
}

ZEND_FUNCTION(SDL_UpdateJoysticks)
{
	ZEND_PARSE_PARAMETERS_NONE();
	SDL_UpdateJoysticks();
}

ZEND_FUNCTION(SDL_AttachVirtualJoystick)
{
	zend_object *desc_obj;
	SDL_VirtualJoystickDesc desc;
	zend_long type, vendor, product, naxes, nbuttons, nhats, button_mask, axis_mask;
	zend_string *name;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(desc_obj, sdl3_ce_SDL_VirtualJoystickDesc)
	ZEND_PARSE_PARAMETERS_END();

	if (!sdl3_prop_long(desc_obj, "type", &type)
		|| !sdl3_prop_long(desc_obj, "vendor_id", &vendor)
		|| !sdl3_prop_long(desc_obj, "product_id", &product)
		|| !sdl3_prop_long(desc_obj, "naxes", &naxes)
		|| !sdl3_prop_long(desc_obj, "nbuttons", &nbuttons)
		|| !sdl3_prop_long(desc_obj, "nhats", &nhats)
		|| !sdl3_prop_long(desc_obj, "button_mask", &button_mask)
		|| !sdl3_prop_long(desc_obj, "axis_mask", &axis_mask)
		|| !sdl3_prop_string(desc_obj, "name", &name)) {
		RETURN_THROWS();
	}

	SDL_INIT_INTERFACE(&desc);
	desc.type = (Uint16) type;
	desc.vendor_id = (Uint16) vendor;
	desc.product_id = (Uint16) product;
	desc.naxes = (Uint16) naxes;
	desc.nbuttons = (Uint16) nbuttons;
	desc.nhats = (Uint16) nhats;
	desc.button_mask = (Uint32) button_mask;
	desc.axis_mask = (Uint32) axis_mask;
	/* SDL copies the name (measured on 3.2.10 and 3.4.4). */
	desc.name = ZSTR_LEN(name) > 0 ? ZSTR_VAL(name) : NULL;

	RETURN_LONG((zend_long) SDL_AttachVirtualJoystick(&desc));
}

ZEND_FUNCTION(SDL_DetachVirtualJoystick)
{
	zend_long id;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(id)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SDL_DetachVirtualJoystick((SDL_JoystickID) id));
}

ZEND_FUNCTION(SDL_SetJoystickVirtualAxis)
{
	zval *zv;
	zend_long axis, value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
		Z_PARAM_LONG(axis)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	RETURN_BOOL(SDL_SetJoystickVirtualAxis(joystick, (int) axis, (Sint16) value));
}

ZEND_FUNCTION(SDL_SetJoystickVirtualButton)
{
	zval *zv;
	zend_long button;
	bool down;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
		Z_PARAM_LONG(button)
		Z_PARAM_BOOL(down)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	RETURN_BOOL(SDL_SetJoystickVirtualButton(joystick, (int) button, down));
}

ZEND_FUNCTION(SDL_SetJoystickVirtualHat)
{
	zval *zv;
	zend_long hat, value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zv, sdl3_ce_SDL_Joystick)
		Z_PARAM_LONG(hat)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();

	SDL3_ARG_HANDLE(joystick, SDL_Joystick, zv, sdl3_ce_SDL_Joystick);
	RETURN_BOOL(SDL_SetJoystickVirtualHat(joystick, (int) hat, (Uint8) value));
}

void sdl3_register_SDL_input(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	register_SDL_input_symbols(module_number);

	sdl3_ce_SDL_Gamepad = register_class_SDL_Gamepad();
	sdl3_handle_setup(sdl3_ce_SDL_Gamepad);
	sdl3_ce_SDL_Joystick = register_class_SDL_Joystick();
	sdl3_handle_setup(sdl3_ce_SDL_Joystick);
	sdl3_ce_SDL_VirtualJoystickDesc = register_class_SDL_VirtualJoystickDesc();
	sdl3_struct_setup(sdl3_ce_SDL_VirtualJoystickDesc);
}
