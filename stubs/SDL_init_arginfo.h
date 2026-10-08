/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 1aa271f38d73c1ebb49886cca2cc1fded7b36b2f */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_Init, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_InitSubSystem arginfo_SDL_Init

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

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_Event___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(SDL_Init);
ZEND_FUNCTION(SDL_InitSubSystem);
ZEND_FUNCTION(SDL_Quit);
ZEND_FUNCTION(SDL_GetError);
ZEND_FUNCTION(SDL_ClearError);
ZEND_FUNCTION(SDL_GetVersion);
ZEND_FUNCTION(SDL_SetHint);
ZEND_FUNCTION(SDL_PumpEvents);
ZEND_FUNCTION(SDL_PollEvent);
ZEND_FUNCTION(SDL_WaitEventTimeout);
ZEND_METHOD(SDL_Event, __construct);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(SDL_Init, arginfo_SDL_Init)
	ZEND_FE(SDL_InitSubSystem, arginfo_SDL_InitSubSystem)
	ZEND_FE(SDL_Quit, arginfo_SDL_Quit)
	ZEND_FE(SDL_GetError, arginfo_SDL_GetError)
	ZEND_FE(SDL_ClearError, arginfo_SDL_ClearError)
	ZEND_FE(SDL_GetVersion, arginfo_SDL_GetVersion)
	ZEND_FE(SDL_SetHint, arginfo_SDL_SetHint)
	ZEND_FE(SDL_PumpEvents, arginfo_SDL_PumpEvents)
	ZEND_FE(SDL_PollEvent, arginfo_SDL_PollEvent)
	ZEND_FE(SDL_WaitEventTimeout, arginfo_SDL_WaitEventTimeout)
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

	return class_entry;
}
