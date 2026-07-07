
extern zend_class_entry *sdl3_sdl_events_sdlkeyboard_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Events_SDLKeyboard);

PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLHasKeyboard);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyboards);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyboardNameForID);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyboardFocus);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyboardState);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetModState);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLSetModState);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyFromScancode);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetScancodeFromKey);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLSetScancodeName);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetScancodeName);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetScancodeFromName);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyName);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyFromName);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLStartTextInput);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLStartTextInputWithProperties);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLTextInputActive);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLStopTextInput);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLClearComposition);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLSetTextInputArea);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLGetTextInputArea);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLHasScreenKeyboardSupport);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLScreenKeyboardShown);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLReadKeyboardEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLReadTextInputEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLReadTextEditingEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLReadTextEditingCandidatesEvent);
PHP_METHOD(Sdl3_SDL_Events_SDLKeyboard, SDLReadKeyboardDeviceEvent);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlhaskeyboard, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyboards, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyboardnameforid, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyboardfocus, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyboardstate, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetmodstate, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlsetmodstate, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, modstate, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyfromscancode, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scancode, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, modstate, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, key_event, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetscancodefromkey, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlsetscancodename, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, scancode, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetscancodename, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, scancode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetscancodefromname, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyname, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyfromname, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlstarttextinput, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlstarttextinputwithproperties, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdltextinputactive, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlstoptextinput, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlclearcomposition, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlsettextinputarea, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, rect)
	ZEND_ARG_TYPE_INFO(0, cursor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlgettextinputarea, 0, 1, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlhasscreenkeyboardsupport, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlscreenkeyboardshown, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlreadkeyboardevent, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlreadtextinputevent, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlreadtexteditingevent, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlreadtexteditingcandidatesevent, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_events_sdlkeyboard_sdlreadkeyboarddeviceevent, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_events_sdlkeyboard_method_entry) {
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLHasKeyboard, arginfo_sdl3_sdl_events_sdlkeyboard_sdlhaskeyboard, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyboards, arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyboards, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyboardNameForID, arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyboardnameforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyboardFocus, arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyboardfocus, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyboardState, arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyboardstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLGetModState, arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetmodstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLSetModState, arginfo_sdl3_sdl_events_sdlkeyboard_sdlsetmodstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyFromScancode, arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyfromscancode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLGetScancodeFromKey, arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetscancodefromkey, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLSetScancodeName, arginfo_sdl3_sdl_events_sdlkeyboard_sdlsetscancodename, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLGetScancodeName, arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetscancodename, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLGetScancodeFromName, arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetscancodefromname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyName, arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLGetKeyFromName, arginfo_sdl3_sdl_events_sdlkeyboard_sdlgetkeyfromname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLStartTextInput, arginfo_sdl3_sdl_events_sdlkeyboard_sdlstarttextinput, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLStartTextInputWithProperties, arginfo_sdl3_sdl_events_sdlkeyboard_sdlstarttextinputwithproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLTextInputActive, arginfo_sdl3_sdl_events_sdlkeyboard_sdltextinputactive, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLStopTextInput, arginfo_sdl3_sdl_events_sdlkeyboard_sdlstoptextinput, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLClearComposition, arginfo_sdl3_sdl_events_sdlkeyboard_sdlclearcomposition, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLSetTextInputArea, arginfo_sdl3_sdl_events_sdlkeyboard_sdlsettextinputarea, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLGetTextInputArea, arginfo_sdl3_sdl_events_sdlkeyboard_sdlgettextinputarea, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLHasScreenKeyboardSupport, arginfo_sdl3_sdl_events_sdlkeyboard_sdlhasscreenkeyboardsupport, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLScreenKeyboardShown, arginfo_sdl3_sdl_events_sdlkeyboard_sdlscreenkeyboardshown, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLReadKeyboardEvent, arginfo_sdl3_sdl_events_sdlkeyboard_sdlreadkeyboardevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLReadTextInputEvent, arginfo_sdl3_sdl_events_sdlkeyboard_sdlreadtextinputevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLReadTextEditingEvent, arginfo_sdl3_sdl_events_sdlkeyboard_sdlreadtexteditingevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLReadTextEditingCandidatesEvent, arginfo_sdl3_sdl_events_sdlkeyboard_sdlreadtexteditingcandidatesevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Events_SDLKeyboard, SDLReadKeyboardDeviceEvent, arginfo_sdl3_sdl_events_sdlkeyboard_sdlreadkeyboarddeviceevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
