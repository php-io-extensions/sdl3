/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 7481b26acbdedea2fd4487a2d2943d1d447f61af */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_Init, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_InitSubSystem arginfo_SDL_Init

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_QuitSubSystem, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_Quit, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetError, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_ClearError, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetVersion, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetHint, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_PumpEvents arginfo_SDL_Quit

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_PollEvent, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, event, SDL_Event, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_WaitEventTimeout, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, event, SDL_Event, 1)
	ZEND_ARG_TYPE_INFO(0, timeoutMS, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_PushEvent, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, event, SDL_Event, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetEventEnabled, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, enabled, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_EventEnabled, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_Event___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(SDL_Init);
ZEND_FUNCTION(SDL_InitSubSystem);
ZEND_FUNCTION(SDL_QuitSubSystem);
ZEND_FUNCTION(SDL_Quit);
ZEND_FUNCTION(SDL_GetError);
ZEND_FUNCTION(SDL_ClearError);
ZEND_FUNCTION(SDL_GetVersion);
ZEND_FUNCTION(SDL_SetHint);
ZEND_FUNCTION(SDL_PumpEvents);
ZEND_FUNCTION(SDL_PollEvent);
ZEND_FUNCTION(SDL_WaitEventTimeout);
ZEND_FUNCTION(SDL_PushEvent);
ZEND_FUNCTION(SDL_SetEventEnabled);
ZEND_FUNCTION(SDL_EventEnabled);
ZEND_METHOD(SDL_Event, __construct);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(SDL_Init, arginfo_SDL_Init)
	ZEND_FE(SDL_InitSubSystem, arginfo_SDL_InitSubSystem)
	ZEND_FE(SDL_QuitSubSystem, arginfo_SDL_QuitSubSystem)
	ZEND_FE(SDL_Quit, arginfo_SDL_Quit)
	ZEND_FE(SDL_GetError, arginfo_SDL_GetError)
	ZEND_FE(SDL_ClearError, arginfo_SDL_ClearError)
	ZEND_FE(SDL_GetVersion, arginfo_SDL_GetVersion)
	ZEND_FE(SDL_SetHint, arginfo_SDL_SetHint)
	ZEND_FE(SDL_PumpEvents, arginfo_SDL_PumpEvents)
	ZEND_FE(SDL_PollEvent, arginfo_SDL_PollEvent)
	ZEND_FE(SDL_WaitEventTimeout, arginfo_SDL_WaitEventTimeout)
	ZEND_FE(SDL_PushEvent, arginfo_SDL_PushEvent)
	ZEND_FE(SDL_SetEventEnabled, arginfo_SDL_SetEventEnabled)
	ZEND_FE(SDL_EventEnabled, arginfo_SDL_EventEnabled)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_Event_methods[] = {
	ZEND_ME(SDL_Event, __construct, arginfo_class_SDL_Event___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static void register_SDL_init_symbols(int module_number)
{
	REGISTER_LONG_CONSTANT("SDL_INIT_VIDEO", SDL_INIT_VIDEO, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_QUIT", SDL_EVENT_QUIT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_CLOSE_REQUESTED", SDL_EVENT_WINDOW_CLOSE_REQUESTED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_RESIZED", SDL_EVENT_WINDOW_RESIZED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED", SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_FOCUS_GAINED", SDL_EVENT_WINDOW_FOCUS_GAINED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_FOCUS_LOST", SDL_EVENT_WINDOW_FOCUS_LOST, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_SHOWN", SDL_EVENT_WINDOW_SHOWN, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_HIDDEN", SDL_EVENT_WINDOW_HIDDEN, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_EXPOSED", SDL_EVENT_WINDOW_EXPOSED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_MOVED", SDL_EVENT_WINDOW_MOVED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_METAL_VIEW_RESIZED", SDL_EVENT_WINDOW_METAL_VIEW_RESIZED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_MINIMIZED", SDL_EVENT_WINDOW_MINIMIZED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_MAXIMIZED", SDL_EVENT_WINDOW_MAXIMIZED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_RESTORED", SDL_EVENT_WINDOW_RESTORED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_HIT_TEST", SDL_EVENT_WINDOW_HIT_TEST, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_ICCPROF_CHANGED", SDL_EVENT_WINDOW_ICCPROF_CHANGED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_DISPLAY_CHANGED", SDL_EVENT_WINDOW_DISPLAY_CHANGED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED", SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_SAFE_AREA_CHANGED", SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_OCCLUDED", SDL_EVENT_WINDOW_OCCLUDED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_ENTER_FULLSCREEN", SDL_EVENT_WINDOW_ENTER_FULLSCREEN, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_LEAVE_FULLSCREEN", SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_DESTROYED", SDL_EVENT_WINDOW_DESTROYED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_HDR_STATE_CHANGED", SDL_EVENT_WINDOW_HDR_STATE_CHANGED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_FIRST", SDL_EVENT_WINDOW_FIRST, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_LAST", SDL_EVENT_WINDOW_LAST, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_DISPLAY_ORIENTATION", SDL_EVENT_DISPLAY_ORIENTATION, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_DISPLAY_ADDED", SDL_EVENT_DISPLAY_ADDED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_DISPLAY_REMOVED", SDL_EVENT_DISPLAY_REMOVED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_DISPLAY_MOVED", SDL_EVENT_DISPLAY_MOVED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED", SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED", SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED", SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_DISPLAY_FIRST", SDL_EVENT_DISPLAY_FIRST, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_DISPLAY_LAST", SDL_EVENT_DISPLAY_LAST, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_KEY_DOWN", SDL_EVENT_KEY_DOWN, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_KEY_UP", SDL_EVENT_KEY_UP, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_TEXT_INPUT", SDL_EVENT_TEXT_INPUT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_MOUSE_MOTION", SDL_EVENT_MOUSE_MOTION, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_MOUSE_BUTTON_DOWN", SDL_EVENT_MOUSE_BUTTON_DOWN, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_MOUSE_BUTTON_UP", SDL_EVENT_MOUSE_BUTTON_UP, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_MOUSE_WHEEL", SDL_EVENT_MOUSE_WHEEL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_MOUSE_ENTER", SDL_EVENT_WINDOW_MOUSE_ENTER, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_MOUSE_LEAVE", SDL_EVENT_WINDOW_MOUSE_LEAVE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_JOYSTICK_AXIS_MOTION", SDL_EVENT_JOYSTICK_AXIS_MOTION, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_JOYSTICK_UPDATE_COMPLETE", SDL_EVENT_JOYSTICK_UPDATE_COMPLETE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_GAMEPAD_ADDED", SDL_EVENT_GAMEPAD_ADDED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_GAMEPAD_AXIS_MOTION", SDL_EVENT_GAMEPAD_AXIS_MOTION, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_FINGER_DOWN", SDL_EVENT_FINGER_DOWN, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_LEFT", SDL_BUTTON_LEFT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_MIDDLE", SDL_BUTTON_MIDDLE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_RIGHT", SDL_BUTTON_RIGHT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_X1", SDL_BUTTON_X1, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_X2", SDL_BUTTON_X2, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MOUSEWHEEL_NORMAL", SDL_MOUSEWHEEL_NORMAL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MOUSEWHEEL_FLIPPED", SDL_MOUSEWHEEL_FLIPPED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KMOD_NONE", SDL_KMOD_NONE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KMOD_LSHIFT", SDL_KMOD_LSHIFT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KMOD_RSHIFT", SDL_KMOD_RSHIFT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KMOD_SHIFT", SDL_KMOD_SHIFT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KMOD_LCTRL", SDL_KMOD_LCTRL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KMOD_RCTRL", SDL_KMOD_RCTRL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KMOD_CTRL", SDL_KMOD_CTRL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KMOD_LALT", SDL_KMOD_LALT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KMOD_RALT", SDL_KMOD_RALT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KMOD_ALT", SDL_KMOD_ALT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KMOD_LGUI", SDL_KMOD_LGUI, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KMOD_RGUI", SDL_KMOD_RGUI, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KMOD_GUI", SDL_KMOD_GUI, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_HINT_VIDEO_DRIVER", SDL_HINT_VIDEO_DRIVER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES", SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS", SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_HINT_VIDEO_FORCE_EGL", SDL_HINT_VIDEO_FORCE_EGL, CONST_PERSISTENT);
}

static zend_class_entry *register_class_SDL_WindowEvent(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_WindowEvent", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_type_default_value;
	ZVAL_LONG(&property_type_default_value, 0);
	zend_string *property_type_name = zend_string_init("type", sizeof("type") - 1, 1);
	zend_declare_typed_property(class_entry, property_type_name, &property_type_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_type_name);

	zval property_timestamp_default_value;
	ZVAL_LONG(&property_timestamp_default_value, 0);
	zend_string *property_timestamp_name = zend_string_init("timestamp", sizeof("timestamp") - 1, 1);
	zend_declare_typed_property(class_entry, property_timestamp_name, &property_timestamp_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_timestamp_name);

	zval property_windowID_default_value;
	ZVAL_LONG(&property_windowID_default_value, 0);
	zend_string *property_windowID_name = zend_string_init("windowID", sizeof("windowID") - 1, 1);
	zend_declare_typed_property(class_entry, property_windowID_name, &property_windowID_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_windowID_name);

	zval property_data1_default_value;
	ZVAL_LONG(&property_data1_default_value, 0);
	zend_string *property_data1_name = zend_string_init("data1", sizeof("data1") - 1, 1);
	zend_declare_typed_property(class_entry, property_data1_name, &property_data1_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_data1_name);

	zval property_data2_default_value;
	ZVAL_LONG(&property_data2_default_value, 0);
	zend_string *property_data2_name = zend_string_init("data2", sizeof("data2") - 1, 1);
	zend_declare_typed_property(class_entry, property_data2_name, &property_data2_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_data2_name);

	return class_entry;
}

static zend_class_entry *register_class_SDL_DisplayEvent(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_DisplayEvent", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_type_default_value;
	ZVAL_LONG(&property_type_default_value, 0);
	zend_string *property_type_name = zend_string_init("type", sizeof("type") - 1, 1);
	zend_declare_typed_property(class_entry, property_type_name, &property_type_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_type_name);

	zval property_timestamp_default_value;
	ZVAL_LONG(&property_timestamp_default_value, 0);
	zend_string *property_timestamp_name = zend_string_init("timestamp", sizeof("timestamp") - 1, 1);
	zend_declare_typed_property(class_entry, property_timestamp_name, &property_timestamp_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_timestamp_name);

	zval property_displayID_default_value;
	ZVAL_LONG(&property_displayID_default_value, 0);
	zend_string *property_displayID_name = zend_string_init("displayID", sizeof("displayID") - 1, 1);
	zend_declare_typed_property(class_entry, property_displayID_name, &property_displayID_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_displayID_name);

	zval property_data1_default_value;
	ZVAL_LONG(&property_data1_default_value, 0);
	zend_string *property_data1_name = zend_string_init("data1", sizeof("data1") - 1, 1);
	zend_declare_typed_property(class_entry, property_data1_name, &property_data1_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_data1_name);

	zval property_data2_default_value;
	ZVAL_LONG(&property_data2_default_value, 0);
	zend_string *property_data2_name = zend_string_init("data2", sizeof("data2") - 1, 1);
	zend_declare_typed_property(class_entry, property_data2_name, &property_data2_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_data2_name);

	return class_entry;
}

static zend_class_entry *register_class_SDL_KeyboardEvent(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_KeyboardEvent", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_type_default_value;
	ZVAL_LONG(&property_type_default_value, 0);
	zend_string *property_type_name = zend_string_init("type", sizeof("type") - 1, 1);
	zend_declare_typed_property(class_entry, property_type_name, &property_type_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_type_name);

	zval property_timestamp_default_value;
	ZVAL_LONG(&property_timestamp_default_value, 0);
	zend_string *property_timestamp_name = zend_string_init("timestamp", sizeof("timestamp") - 1, 1);
	zend_declare_typed_property(class_entry, property_timestamp_name, &property_timestamp_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_timestamp_name);

	zval property_windowID_default_value;
	ZVAL_LONG(&property_windowID_default_value, 0);
	zend_string *property_windowID_name = zend_string_init("windowID", sizeof("windowID") - 1, 1);
	zend_declare_typed_property(class_entry, property_windowID_name, &property_windowID_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_windowID_name);

	zval property_which_default_value;
	ZVAL_LONG(&property_which_default_value, 0);
	zend_string *property_which_name = zend_string_init("which", sizeof("which") - 1, 1);
	zend_declare_typed_property(class_entry, property_which_name, &property_which_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_which_name);

	zval property_scancode_default_value;
	ZVAL_LONG(&property_scancode_default_value, 0);
	zend_string *property_scancode_name = zend_string_init("scancode", sizeof("scancode") - 1, 1);
	zend_declare_typed_property(class_entry, property_scancode_name, &property_scancode_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_scancode_name);

	zval property_key_default_value;
	ZVAL_LONG(&property_key_default_value, 0);
	zend_string *property_key_name = zend_string_init("key", sizeof("key") - 1, 1);
	zend_declare_typed_property(class_entry, property_key_name, &property_key_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_key_name);

	zval property_mod_default_value;
	ZVAL_LONG(&property_mod_default_value, 0);
	zend_string *property_mod_name = zend_string_init("mod", sizeof("mod") - 1, 1);
	zend_declare_typed_property(class_entry, property_mod_name, &property_mod_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_mod_name);

	zval property_raw_default_value;
	ZVAL_LONG(&property_raw_default_value, 0);
	zend_string *property_raw_name = zend_string_init("raw", sizeof("raw") - 1, 1);
	zend_declare_typed_property(class_entry, property_raw_name, &property_raw_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_raw_name);

	zval property_down_default_value;
	ZVAL_FALSE(&property_down_default_value);
	zend_string *property_down_name = zend_string_init("down", sizeof("down") - 1, 1);
	zend_declare_typed_property(class_entry, property_down_name, &property_down_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_BOOL));
	zend_string_release(property_down_name);

	zval property_repeat_default_value;
	ZVAL_FALSE(&property_repeat_default_value);
	zend_string *property_repeat_name = zend_string_init("repeat", sizeof("repeat") - 1, 1);
	zend_declare_typed_property(class_entry, property_repeat_name, &property_repeat_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_BOOL));
	zend_string_release(property_repeat_name);

	return class_entry;
}

static zend_class_entry *register_class_SDL_TextInputEvent(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_TextInputEvent", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_type_default_value;
	ZVAL_LONG(&property_type_default_value, 0);
	zend_string *property_type_name = zend_string_init("type", sizeof("type") - 1, 1);
	zend_declare_typed_property(class_entry, property_type_name, &property_type_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_type_name);

	zval property_timestamp_default_value;
	ZVAL_LONG(&property_timestamp_default_value, 0);
	zend_string *property_timestamp_name = zend_string_init("timestamp", sizeof("timestamp") - 1, 1);
	zend_declare_typed_property(class_entry, property_timestamp_name, &property_timestamp_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_timestamp_name);

	zval property_windowID_default_value;
	ZVAL_LONG(&property_windowID_default_value, 0);
	zend_string *property_windowID_name = zend_string_init("windowID", sizeof("windowID") - 1, 1);
	zend_declare_typed_property(class_entry, property_windowID_name, &property_windowID_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_windowID_name);

	zval property_text_default_value;
	ZVAL_EMPTY_STRING(&property_text_default_value);
	zend_string *property_text_name = zend_string_init("text", sizeof("text") - 1, 1);
	zend_declare_typed_property(class_entry, property_text_name, &property_text_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
	zend_string_release(property_text_name);

	return class_entry;
}

static zend_class_entry *register_class_SDL_MouseMotionEvent(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_MouseMotionEvent", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_type_default_value;
	ZVAL_LONG(&property_type_default_value, 0);
	zend_string *property_type_name = zend_string_init("type", sizeof("type") - 1, 1);
	zend_declare_typed_property(class_entry, property_type_name, &property_type_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_type_name);

	zval property_timestamp_default_value;
	ZVAL_LONG(&property_timestamp_default_value, 0);
	zend_string *property_timestamp_name = zend_string_init("timestamp", sizeof("timestamp") - 1, 1);
	zend_declare_typed_property(class_entry, property_timestamp_name, &property_timestamp_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_timestamp_name);

	zval property_windowID_default_value;
	ZVAL_LONG(&property_windowID_default_value, 0);
	zend_string *property_windowID_name = zend_string_init("windowID", sizeof("windowID") - 1, 1);
	zend_declare_typed_property(class_entry, property_windowID_name, &property_windowID_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_windowID_name);

	zval property_which_default_value;
	ZVAL_LONG(&property_which_default_value, 0);
	zend_string *property_which_name = zend_string_init("which", sizeof("which") - 1, 1);
	zend_declare_typed_property(class_entry, property_which_name, &property_which_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_which_name);

	zval property_state_default_value;
	ZVAL_LONG(&property_state_default_value, 0);
	zend_string *property_state_name = zend_string_init("state", sizeof("state") - 1, 1);
	zend_declare_typed_property(class_entry, property_state_name, &property_state_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_state_name);

	zval property_x_default_value;
	ZVAL_DOUBLE(&property_x_default_value, 0.0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_DOUBLE(&property_y_default_value, 0.0);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_y_name);

	zval property_xrel_default_value;
	ZVAL_DOUBLE(&property_xrel_default_value, 0.0);
	zend_string *property_xrel_name = zend_string_init("xrel", sizeof("xrel") - 1, 1);
	zend_declare_typed_property(class_entry, property_xrel_name, &property_xrel_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_xrel_name);

	zval property_yrel_default_value;
	ZVAL_DOUBLE(&property_yrel_default_value, 0.0);
	zend_string *property_yrel_name = zend_string_init("yrel", sizeof("yrel") - 1, 1);
	zend_declare_typed_property(class_entry, property_yrel_name, &property_yrel_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_yrel_name);

	return class_entry;
}

static zend_class_entry *register_class_SDL_MouseButtonEvent(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_MouseButtonEvent", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_type_default_value;
	ZVAL_LONG(&property_type_default_value, 0);
	zend_string *property_type_name = zend_string_init("type", sizeof("type") - 1, 1);
	zend_declare_typed_property(class_entry, property_type_name, &property_type_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_type_name);

	zval property_timestamp_default_value;
	ZVAL_LONG(&property_timestamp_default_value, 0);
	zend_string *property_timestamp_name = zend_string_init("timestamp", sizeof("timestamp") - 1, 1);
	zend_declare_typed_property(class_entry, property_timestamp_name, &property_timestamp_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_timestamp_name);

	zval property_windowID_default_value;
	ZVAL_LONG(&property_windowID_default_value, 0);
	zend_string *property_windowID_name = zend_string_init("windowID", sizeof("windowID") - 1, 1);
	zend_declare_typed_property(class_entry, property_windowID_name, &property_windowID_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_windowID_name);

	zval property_which_default_value;
	ZVAL_LONG(&property_which_default_value, 0);
	zend_string *property_which_name = zend_string_init("which", sizeof("which") - 1, 1);
	zend_declare_typed_property(class_entry, property_which_name, &property_which_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_which_name);

	zval property_button_default_value;
	ZVAL_LONG(&property_button_default_value, 0);
	zend_string *property_button_name = zend_string_init("button", sizeof("button") - 1, 1);
	zend_declare_typed_property(class_entry, property_button_name, &property_button_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_button_name);

	zval property_down_default_value;
	ZVAL_FALSE(&property_down_default_value);
	zend_string *property_down_name = zend_string_init("down", sizeof("down") - 1, 1);
	zend_declare_typed_property(class_entry, property_down_name, &property_down_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_BOOL));
	zend_string_release(property_down_name);

	zval property_clicks_default_value;
	ZVAL_LONG(&property_clicks_default_value, 0);
	zend_string *property_clicks_name = zend_string_init("clicks", sizeof("clicks") - 1, 1);
	zend_declare_typed_property(class_entry, property_clicks_name, &property_clicks_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_clicks_name);

	zval property_x_default_value;
	ZVAL_DOUBLE(&property_x_default_value, 0.0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_DOUBLE(&property_y_default_value, 0.0);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_y_name);

	return class_entry;
}

static zend_class_entry *register_class_SDL_MouseWheelEvent(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_MouseWheelEvent", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_type_default_value;
	ZVAL_LONG(&property_type_default_value, 0);
	zend_string *property_type_name = zend_string_init("type", sizeof("type") - 1, 1);
	zend_declare_typed_property(class_entry, property_type_name, &property_type_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_type_name);

	zval property_timestamp_default_value;
	ZVAL_LONG(&property_timestamp_default_value, 0);
	zend_string *property_timestamp_name = zend_string_init("timestamp", sizeof("timestamp") - 1, 1);
	zend_declare_typed_property(class_entry, property_timestamp_name, &property_timestamp_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_timestamp_name);

	zval property_windowID_default_value;
	ZVAL_LONG(&property_windowID_default_value, 0);
	zend_string *property_windowID_name = zend_string_init("windowID", sizeof("windowID") - 1, 1);
	zend_declare_typed_property(class_entry, property_windowID_name, &property_windowID_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_windowID_name);

	zval property_which_default_value;
	ZVAL_LONG(&property_which_default_value, 0);
	zend_string *property_which_name = zend_string_init("which", sizeof("which") - 1, 1);
	zend_declare_typed_property(class_entry, property_which_name, &property_which_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_which_name);

	zval property_x_default_value;
	ZVAL_DOUBLE(&property_x_default_value, 0.0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_DOUBLE(&property_y_default_value, 0.0);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_y_name);

	zval property_direction_default_value;
	ZVAL_LONG(&property_direction_default_value, 0);
	zend_string *property_direction_name = zend_string_init("direction", sizeof("direction") - 1, 1);
	zend_declare_typed_property(class_entry, property_direction_name, &property_direction_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_direction_name);

	zval property_mouse_x_default_value;
	ZVAL_DOUBLE(&property_mouse_x_default_value, 0.0);
	zend_string *property_mouse_x_name = zend_string_init("mouse_x", sizeof("mouse_x") - 1, 1);
	zend_declare_typed_property(class_entry, property_mouse_x_name, &property_mouse_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_mouse_x_name);

	zval property_mouse_y_default_value;
	ZVAL_DOUBLE(&property_mouse_y_default_value, 0.0);
	zend_string *property_mouse_y_name = zend_string_init("mouse_y", sizeof("mouse_y") - 1, 1);
	zend_declare_typed_property(class_entry, property_mouse_y_name, &property_mouse_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_mouse_y_name);

	return class_entry;
}

static zend_class_entry *register_class_SDL_Event(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_Event", class_SDL_Event_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_type_default_value;
	ZVAL_LONG(&property_type_default_value, 0);
	zend_string *property_type_name = zend_string_init("type", sizeof("type") - 1, 1);
	zend_declare_typed_property(class_entry, property_type_name, &property_type_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_type_name);

	zval property_window_default_value;
	ZVAL_UNDEF(&property_window_default_value);
	zend_string *property_window_name = zend_string_init("window", sizeof("window") - 1, 1);
	zend_string *property_window_class_SDL_WindowEvent = zend_string_init("SDL_WindowEvent", sizeof("SDL_WindowEvent")-1, 1);
	zend_declare_typed_property(class_entry, property_window_name, &property_window_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_window_class_SDL_WindowEvent, 0, 0));
	zend_string_release(property_window_name);

	zval property_display_default_value;
	ZVAL_UNDEF(&property_display_default_value);
	zend_string *property_display_name = zend_string_init("display", sizeof("display") - 1, 1);
	zend_string *property_display_class_SDL_DisplayEvent = zend_string_init("SDL_DisplayEvent", sizeof("SDL_DisplayEvent")-1, 1);
	zend_declare_typed_property(class_entry, property_display_name, &property_display_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_display_class_SDL_DisplayEvent, 0, 0));
	zend_string_release(property_display_name);

	zval property_key_default_value;
	ZVAL_UNDEF(&property_key_default_value);
	zend_string *property_key_name = zend_string_init("key", sizeof("key") - 1, 1);
	zend_string *property_key_class_SDL_KeyboardEvent = zend_string_init("SDL_KeyboardEvent", sizeof("SDL_KeyboardEvent")-1, 1);
	zend_declare_typed_property(class_entry, property_key_name, &property_key_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_key_class_SDL_KeyboardEvent, 0, 0));
	zend_string_release(property_key_name);

	zval property_text_default_value;
	ZVAL_UNDEF(&property_text_default_value);
	zend_string *property_text_name = zend_string_init("text", sizeof("text") - 1, 1);
	zend_string *property_text_class_SDL_TextInputEvent = zend_string_init("SDL_TextInputEvent", sizeof("SDL_TextInputEvent")-1, 1);
	zend_declare_typed_property(class_entry, property_text_name, &property_text_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_text_class_SDL_TextInputEvent, 0, 0));
	zend_string_release(property_text_name);

	zval property_motion_default_value;
	ZVAL_UNDEF(&property_motion_default_value);
	zend_string *property_motion_name = zend_string_init("motion", sizeof("motion") - 1, 1);
	zend_string *property_motion_class_SDL_MouseMotionEvent = zend_string_init("SDL_MouseMotionEvent", sizeof("SDL_MouseMotionEvent")-1, 1);
	zend_declare_typed_property(class_entry, property_motion_name, &property_motion_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_motion_class_SDL_MouseMotionEvent, 0, 0));
	zend_string_release(property_motion_name);

	zval property_button_default_value;
	ZVAL_UNDEF(&property_button_default_value);
	zend_string *property_button_name = zend_string_init("button", sizeof("button") - 1, 1);
	zend_string *property_button_class_SDL_MouseButtonEvent = zend_string_init("SDL_MouseButtonEvent", sizeof("SDL_MouseButtonEvent")-1, 1);
	zend_declare_typed_property(class_entry, property_button_name, &property_button_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_button_class_SDL_MouseButtonEvent, 0, 0));
	zend_string_release(property_button_name);

	zval property_wheel_default_value;
	ZVAL_UNDEF(&property_wheel_default_value);
	zend_string *property_wheel_name = zend_string_init("wheel", sizeof("wheel") - 1, 1);
	zend_string *property_wheel_class_SDL_MouseWheelEvent = zend_string_init("SDL_MouseWheelEvent", sizeof("SDL_MouseWheelEvent")-1, 1);
	zend_declare_typed_property(class_entry, property_wheel_name, &property_wheel_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_wheel_class_SDL_MouseWheelEvent, 0, 0));
	zend_string_release(property_wheel_name);

	return class_entry;
}
