
extern zend_class_entry *sdl3_sdl_input_sdljoystick_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Input_SDLJoystick);

PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLLockJoysticks);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLUnlockJoysticks);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLHasJoystick);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoysticks);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickNameForID);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPathForID);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPlayerIndexForID);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickGUIDForID);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickVendorForID);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProductForID);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProductVersionForID);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickTypeForID);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLOpenJoystick);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickFromID);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickFromPlayerIndex);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLAttachVirtualJoystick);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLDetachVirtualJoystick);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLIsJoystickVirtual);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualAxis);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualBall);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualButton);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualHat);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualTouchpad);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSendJoystickVirtualSensorData);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProperties);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickName);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPath);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPlayerIndex);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickPlayerIndex);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickGUID);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickVendor);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProduct);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProductVersion);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickFirmwareVersion);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickSerial);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickType);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickGUIDInfo);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLJoystickConnected);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickID);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetNumJoystickAxes);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetNumJoystickBalls);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetNumJoystickHats);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetNumJoystickButtons);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickEventsEnabled);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLJoystickEventsEnabled);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLUpdateJoysticks);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickAxis);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickAxisInitialState);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickBall);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickHat);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickButton);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLRumbleJoystick);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLRumbleJoystickTriggers);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickLED);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLSendJoystickEffect);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLCloseJoystick);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickConnectionState);
PHP_METHOD(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPowerInfo);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdllockjoysticks, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlunlockjoysticks, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlhasjoystick, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoysticks, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoysticknameforid, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickpathforid, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickplayerindexforid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickguidforid, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickvendorforid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickproductforid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickproductversionforid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoysticktypeforid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlopenjoystick, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickfromid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickfromplayerindex, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, player_index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlattachvirtualjoystick, 0, 1, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, desc, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdldetachvirtualjoystick, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlisjoystickvirtual, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickvirtualaxis, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, axis, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickvirtualball, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ball, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, xrel, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, yrel, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickvirtualbutton, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, button, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, down, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickvirtualhat, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, hat, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickvirtualtouchpad, 0, 7, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, touchpad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, finger, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, down, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, pressure, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlsendjoystickvirtualsensordata, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sensor_timestamp, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, data, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickproperties, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickname, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickpath, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickplayerindex, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickplayerindex, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, player_index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickguid, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickvendor, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickproduct, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickproductversion, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickfirmwareversion, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickserial, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoysticktype, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickguidinfo, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, guid, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdljoystickconnected, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetnumjoystickaxes, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetnumjoystickballs, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetnumjoystickhats, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetnumjoystickbuttons, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickeventsenabled, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, enabled, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdljoystickeventsenabled, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlupdatejoysticks, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickaxis, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, axis, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickaxisinitialstate, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, axis, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickball, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ball, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickhat, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, hat, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickbutton, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, button, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlrumblejoystick, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, low_frequency_rumble, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, high_frequency_rumble, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, duration_ms, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlrumblejoysticktriggers, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, left_rumble, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, right_rumble, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, duration_ms, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickled, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, red, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, green, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, blue, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlsendjoystickeffect, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlclosejoystick, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickconnectionstate, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickpowerinfo, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_input_sdljoystick_method_entry) {
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLLockJoysticks, arginfo_sdl3_sdl_input_sdljoystick_sdllockjoysticks, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLUnlockJoysticks, arginfo_sdl3_sdl_input_sdljoystick_sdlunlockjoysticks, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLHasJoystick, arginfo_sdl3_sdl_input_sdljoystick_sdlhasjoystick, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoysticks, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoysticks, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickNameForID, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoysticknameforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPathForID, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickpathforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPlayerIndexForID, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickplayerindexforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickGUIDForID, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickguidforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickVendorForID, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickvendorforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProductForID, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickproductforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProductVersionForID, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickproductversionforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickTypeForID, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoysticktypeforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLOpenJoystick, arginfo_sdl3_sdl_input_sdljoystick_sdlopenjoystick, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickFromID, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickfromid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickFromPlayerIndex, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickfromplayerindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLAttachVirtualJoystick, arginfo_sdl3_sdl_input_sdljoystick_sdlattachvirtualjoystick, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLDetachVirtualJoystick, arginfo_sdl3_sdl_input_sdljoystick_sdldetachvirtualjoystick, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLIsJoystickVirtual, arginfo_sdl3_sdl_input_sdljoystick_sdlisjoystickvirtual, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualAxis, arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickvirtualaxis, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualBall, arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickvirtualball, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualButton, arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickvirtualbutton, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualHat, arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickvirtualhat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickVirtualTouchpad, arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickvirtualtouchpad, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLSendJoystickVirtualSensorData, arginfo_sdl3_sdl_input_sdljoystick_sdlsendjoystickvirtualsensordata, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProperties, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickName, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPath, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickpath, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPlayerIndex, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickplayerindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickPlayerIndex, arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickplayerindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickGUID, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickguid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickVendor, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickvendor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProduct, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickproduct, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickProductVersion, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickproductversion, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickFirmwareVersion, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickfirmwareversion, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickSerial, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickserial, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickType, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoysticktype, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickGUIDInfo, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickguidinfo, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLJoystickConnected, arginfo_sdl3_sdl_input_sdljoystick_sdljoystickconnected, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickID, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetNumJoystickAxes, arginfo_sdl3_sdl_input_sdljoystick_sdlgetnumjoystickaxes, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetNumJoystickBalls, arginfo_sdl3_sdl_input_sdljoystick_sdlgetnumjoystickballs, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetNumJoystickHats, arginfo_sdl3_sdl_input_sdljoystick_sdlgetnumjoystickhats, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetNumJoystickButtons, arginfo_sdl3_sdl_input_sdljoystick_sdlgetnumjoystickbuttons, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickEventsEnabled, arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickeventsenabled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLJoystickEventsEnabled, arginfo_sdl3_sdl_input_sdljoystick_sdljoystickeventsenabled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLUpdateJoysticks, arginfo_sdl3_sdl_input_sdljoystick_sdlupdatejoysticks, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickAxis, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickaxis, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickAxisInitialState, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickaxisinitialstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickBall, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickball, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickHat, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickhat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickButton, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickbutton, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLRumbleJoystick, arginfo_sdl3_sdl_input_sdljoystick_sdlrumblejoystick, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLRumbleJoystickTriggers, arginfo_sdl3_sdl_input_sdljoystick_sdlrumblejoysticktriggers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLSetJoystickLED, arginfo_sdl3_sdl_input_sdljoystick_sdlsetjoystickled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLSendJoystickEffect, arginfo_sdl3_sdl_input_sdljoystick_sdlsendjoystickeffect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLCloseJoystick, arginfo_sdl3_sdl_input_sdljoystick_sdlclosejoystick, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickConnectionState, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickconnectionstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLJoystick, SDLGetJoystickPowerInfo, arginfo_sdl3_sdl_input_sdljoystick_sdlgetjoystickpowerinfo, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
