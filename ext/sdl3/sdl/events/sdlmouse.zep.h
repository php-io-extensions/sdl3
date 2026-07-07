
extern zend_class_entry *sdl3_sdl_events_sdlmouse_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLMouse);

PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLHasMouse);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetMice);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetMouseNameForID);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetMouseFocus);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetMouseState);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetGlobalMouseState);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetRelativeMouseState);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLWarpMouseInWindow);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLWarpMouseGlobal);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLSetWindowRelativeMouseMode);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetWindowRelativeMouseMode);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLCaptureMouse);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLCreateCursor);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLCreateColorCursor);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLCreateAnimatedCursor);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLCreateSystemCursor);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLSetCursor);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetCursor);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLGetDefaultCursor);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLDestroyCursor);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLShowCursor);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLHideCursor);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLCursorVisible);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLReadMouseDeviceEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLReadMouseMotionEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLReadMouseButtonEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLMouse, SDLReadMouseWheelEvent);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlhasmouse, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlgetmice, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlgetmousenameforid, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlgetmousefocus, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlgetmousestate, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlgetglobalmousestate, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlgetrelativemousestate, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlwarpmouseinwindow, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlwarpmouseglobal, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlsetwindowrelativemousemode, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, enabled, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlgetwindowrelativemousemode, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlcapturemouse, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, enabled, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlcreatecursor, 0, 6, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, mask, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, hot_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, hot_y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlcreatecolorcursor, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, hot_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, hot_y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlcreateanimatedcursor, 0, 3, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, frames, 0)
	ZEND_ARG_TYPE_INFO(0, hot_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, hot_y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlcreatesystemcursor, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlsetcursor, 0, 0, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, cursor)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlgetcursor, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlgetdefaultcursor, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdldestroycursor, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, cursor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlshowcursor, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlhidecursor, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlcursorvisible, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlreadmousedeviceevent, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlreadmousemotionevent, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlreadmousebuttonevent, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlmouse_sdlreadmousewheelevent, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_events_sdlmouse_method_entry) {
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLHasMouse, arginfo_sdl3_sdl_events_sdlmouse_sdlhasmouse, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLGetMice, arginfo_sdl3_sdl_events_sdlmouse_sdlgetmice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLGetMouseNameForID, arginfo_sdl3_sdl_events_sdlmouse_sdlgetmousenameforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLGetMouseFocus, arginfo_sdl3_sdl_events_sdlmouse_sdlgetmousefocus, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLGetMouseState, arginfo_sdl3_sdl_events_sdlmouse_sdlgetmousestate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLGetGlobalMouseState, arginfo_sdl3_sdl_events_sdlmouse_sdlgetglobalmousestate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLGetRelativeMouseState, arginfo_sdl3_sdl_events_sdlmouse_sdlgetrelativemousestate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLWarpMouseInWindow, arginfo_sdl3_sdl_events_sdlmouse_sdlwarpmouseinwindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLWarpMouseGlobal, arginfo_sdl3_sdl_events_sdlmouse_sdlwarpmouseglobal, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLSetWindowRelativeMouseMode, arginfo_sdl3_sdl_events_sdlmouse_sdlsetwindowrelativemousemode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLGetWindowRelativeMouseMode, arginfo_sdl3_sdl_events_sdlmouse_sdlgetwindowrelativemousemode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLCaptureMouse, arginfo_sdl3_sdl_events_sdlmouse_sdlcapturemouse, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLCreateCursor, arginfo_sdl3_sdl_events_sdlmouse_sdlcreatecursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLCreateColorCursor, arginfo_sdl3_sdl_events_sdlmouse_sdlcreatecolorcursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLCreateAnimatedCursor, arginfo_sdl3_sdl_events_sdlmouse_sdlcreateanimatedcursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLCreateSystemCursor, arginfo_sdl3_sdl_events_sdlmouse_sdlcreatesystemcursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLSetCursor, arginfo_sdl3_sdl_events_sdlmouse_sdlsetcursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLGetCursor, arginfo_sdl3_sdl_events_sdlmouse_sdlgetcursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLGetDefaultCursor, arginfo_sdl3_sdl_events_sdlmouse_sdlgetdefaultcursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLDestroyCursor, arginfo_sdl3_sdl_events_sdlmouse_sdldestroycursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLShowCursor, arginfo_sdl3_sdl_events_sdlmouse_sdlshowcursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLHideCursor, arginfo_sdl3_sdl_events_sdlmouse_sdlhidecursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLCursorVisible, arginfo_sdl3_sdl_events_sdlmouse_sdlcursorvisible, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLReadMouseDeviceEvent, arginfo_sdl3_sdl_events_sdlmouse_sdlreadmousedeviceevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLReadMouseMotionEvent, arginfo_sdl3_sdl_events_sdlmouse_sdlreadmousemotionevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLReadMouseButtonEvent, arginfo_sdl3_sdl_events_sdlmouse_sdlreadmousebuttonevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLMouse, SDLReadMouseWheelEvent, arginfo_sdl3_sdl_events_sdlmouse_sdlreadmousewheelevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
