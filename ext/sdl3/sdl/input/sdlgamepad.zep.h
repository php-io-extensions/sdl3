
extern zend_class_entry *sdl3_sdl_input_sdlgamepad_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Input_SDLGamepad);

PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLAddGamepadMapping);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLAddGamepadMappingsFromFile);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLReloadGamepadMappings);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadMappings);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadMappingForGUID);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadMapping);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadMapping);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLHasGamepad);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepads);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLIsGamepad);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadNameForID);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPathForID);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPlayerIndexForID);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadGUIDForID);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadVendorForID);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProductForID);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProductVersionForID);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadTypeForID);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetRealGamepadTypeForID);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadMappingForID);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLOpenGamepad);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadFromID);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadFromPlayerIndex);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProperties);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadID);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadName);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPath);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadType);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetRealGamepadType);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPlayerIndex);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadPlayerIndex);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadVendor);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProduct);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProductVersion);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadFirmwareVersion);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadSerial);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadSteamHandle);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadConnectionState);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPowerInfo);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGamepadConnected);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadJoystick);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadEventsEnabled);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGamepadEventsEnabled);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadBindings);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLUpdateGamepads);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadTypeFromString);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadStringForType);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadAxisFromString);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadStringForAxis);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGamepadHasAxis);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadAxis);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadButtonFromString);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadStringForButton);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGamepadHasButton);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadButton);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadButtonLabelForType);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadButtonLabel);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetNumGamepadTouchpads);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetNumGamepadTouchpadFingers);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadTouchpadFinger);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGamepadHasSensor);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadSensorEnabled);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGamepadSensorEnabled);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadSensorDataRate);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadSensorData);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLRumbleGamepad);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLRumbleGamepadTriggers);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadLED);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLSendGamepadEffect);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLCloseGamepad);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadAppleSFSymbolsNameForButton);
PHP_METHOD(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadAppleSFSymbolsNameForAxis);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdladdgamepadmapping, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mapping, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdladdgamepadmappingsfromfile, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, file, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlreloadgamepadmappings, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadmappings, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadmappingforguid, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, guid, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadmapping, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlsetgamepadmapping, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
	ZEND_ARG_INFO(0, mapping)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlhasgamepad, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepads, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlisgamepad, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadnameforid, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadpathforid, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadplayerindexforid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadguidforid, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadvendorforid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadproductforid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadproductversionforid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadtypeforid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetrealgamepadtypeforid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadmappingforid, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlopengamepad, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadfromid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance_id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadfromplayerindex, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, player_index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadproperties, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadid, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadname, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadpath, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadtype, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetrealgamepadtype, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadplayerindex, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlsetgamepadplayerindex, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, player_index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadvendor, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadproduct, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadproductversion, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadfirmwareversion, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadserial, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadsteamhandle, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadconnectionstate, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadpowerinfo, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgamepadconnected, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadjoystick, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlsetgamepadeventsenabled, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, enabled, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgamepadeventsenabled, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadbindings, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlupdategamepads, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadtypefromstring, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadstringfortype, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadaxisfromstring, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadstringforaxis, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, axis, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgamepadhasaxis, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, axis, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadaxis, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, axis, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadbuttonfromstring, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadstringforbutton, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, button, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgamepadhasbutton, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, button, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadbutton, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, button, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadbuttonlabelfortype, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, button, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadbuttonlabel, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, button, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetnumgamepadtouchpads, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetnumgamepadtouchpadfingers, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, touchpad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadtouchpadfinger, 0, 3, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, touchpad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, finger, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgamepadhassensor, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlsetgamepadsensorenabled, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, enabled, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgamepadsensorenabled, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadsensordatarate, 0, 2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadsensordata, 0, 3, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, num_values, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlrumblegamepad, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, low_frequency_rumble, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, high_frequency_rumble, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, duration_ms, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlrumblegamepadtriggers, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, left_rumble, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, right_rumble, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, duration_ms, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlsetgamepadled, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, red, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, green, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, blue, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlsendgamepadeffect, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlclosegamepad, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadapplesfsymbolsnameforbutton, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, button, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadapplesfsymbolsnameforaxis, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, gamepad, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, axis, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_input_sdlgamepad_method_entry) {
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLAddGamepadMapping, arginfo_sdl3_sdl_input_sdlgamepad_sdladdgamepadmapping, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLAddGamepadMappingsFromFile, arginfo_sdl3_sdl_input_sdlgamepad_sdladdgamepadmappingsfromfile, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLReloadGamepadMappings, arginfo_sdl3_sdl_input_sdlgamepad_sdlreloadgamepadmappings, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadMappings, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadmappings, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadMappingForGUID, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadmappingforguid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadMapping, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadmapping, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadMapping, arginfo_sdl3_sdl_input_sdlgamepad_sdlsetgamepadmapping, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLHasGamepad, arginfo_sdl3_sdl_input_sdlgamepad_sdlhasgamepad, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepads, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepads, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLIsGamepad, arginfo_sdl3_sdl_input_sdlgamepad_sdlisgamepad, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadNameForID, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadnameforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPathForID, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadpathforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPlayerIndexForID, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadplayerindexforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadGUIDForID, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadguidforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadVendorForID, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadvendorforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProductForID, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadproductforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProductVersionForID, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadproductversionforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadTypeForID, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadtypeforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetRealGamepadTypeForID, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetrealgamepadtypeforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadMappingForID, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadmappingforid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLOpenGamepad, arginfo_sdl3_sdl_input_sdlgamepad_sdlopengamepad, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadFromID, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadfromid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadFromPlayerIndex, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadfromplayerindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProperties, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadID, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadName, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPath, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadpath, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadType, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadtype, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetRealGamepadType, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetrealgamepadtype, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPlayerIndex, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadplayerindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadPlayerIndex, arginfo_sdl3_sdl_input_sdlgamepad_sdlsetgamepadplayerindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadVendor, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadvendor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProduct, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadproduct, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadProductVersion, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadproductversion, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadFirmwareVersion, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadfirmwareversion, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadSerial, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadserial, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadSteamHandle, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadsteamhandle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadConnectionState, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadconnectionstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadPowerInfo, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadpowerinfo, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGamepadConnected, arginfo_sdl3_sdl_input_sdlgamepad_sdlgamepadconnected, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadJoystick, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadjoystick, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadEventsEnabled, arginfo_sdl3_sdl_input_sdlgamepad_sdlsetgamepadeventsenabled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGamepadEventsEnabled, arginfo_sdl3_sdl_input_sdlgamepad_sdlgamepadeventsenabled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadBindings, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadbindings, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLUpdateGamepads, arginfo_sdl3_sdl_input_sdlgamepad_sdlupdategamepads, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadTypeFromString, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadtypefromstring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadStringForType, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadstringfortype, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadAxisFromString, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadaxisfromstring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadStringForAxis, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadstringforaxis, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGamepadHasAxis, arginfo_sdl3_sdl_input_sdlgamepad_sdlgamepadhasaxis, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadAxis, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadaxis, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadButtonFromString, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadbuttonfromstring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadStringForButton, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadstringforbutton, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGamepadHasButton, arginfo_sdl3_sdl_input_sdlgamepad_sdlgamepadhasbutton, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadButton, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadbutton, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadButtonLabelForType, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadbuttonlabelfortype, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadButtonLabel, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadbuttonlabel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetNumGamepadTouchpads, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetnumgamepadtouchpads, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetNumGamepadTouchpadFingers, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetnumgamepadtouchpadfingers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadTouchpadFinger, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadtouchpadfinger, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGamepadHasSensor, arginfo_sdl3_sdl_input_sdlgamepad_sdlgamepadhassensor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadSensorEnabled, arginfo_sdl3_sdl_input_sdlgamepad_sdlsetgamepadsensorenabled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGamepadSensorEnabled, arginfo_sdl3_sdl_input_sdlgamepad_sdlgamepadsensorenabled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadSensorDataRate, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadsensordatarate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadSensorData, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadsensordata, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLRumbleGamepad, arginfo_sdl3_sdl_input_sdlgamepad_sdlrumblegamepad, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLRumbleGamepadTriggers, arginfo_sdl3_sdl_input_sdlgamepad_sdlrumblegamepadtriggers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLSetGamepadLED, arginfo_sdl3_sdl_input_sdlgamepad_sdlsetgamepadled, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLSendGamepadEffect, arginfo_sdl3_sdl_input_sdlgamepad_sdlsendgamepadeffect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLCloseGamepad, arginfo_sdl3_sdl_input_sdlgamepad_sdlclosegamepad, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadAppleSFSymbolsNameForButton, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadapplesfsymbolsnameforbutton, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Input_SDLGamepad, SDLGetGamepadAppleSFSymbolsNameForAxis, arginfo_sdl3_sdl_input_sdlgamepad_sdlgetgamepadapplesfsymbolsnameforaxis, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
