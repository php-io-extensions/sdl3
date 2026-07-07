
extern zend_class_entry *sdl3_sdl_sdlproperties_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_SDLProperties);

PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetGlobalProperties);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLCreateProperties);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLCopyProperties);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLLockProperties);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLUnlockProperties);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLSetPointerProperty);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLSetStringProperty);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLSetNumberProperty);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLSetFloatProperty);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLSetBooleanProperty);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLHasProperty);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetPropertyType);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetPointerProperty);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetStringProperty);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetNumberProperty);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetFloatProperty);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLGetBooleanProperty);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLClearProperty);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLEnumerateProperties);
PHP_METHOD(Sdl3_SDL_SDLProperties, SDLDestroyProperties);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlgetglobalproperties, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlcreateproperties, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlcopyproperties, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdllockproperties, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlunlockproperties, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlsetpointerproperty, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlsetstringproperty, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlsetnumberproperty, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlsetfloatproperty, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlsetbooleanproperty, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlhasproperty, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlgetpropertytype, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlgetpointerproperty, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_INFO(0, defaultValue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlgetstringproperty, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_INFO(0, defaultValue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlgetnumberproperty, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, defaultValue, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlgetfloatproperty, 0, 3, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, defaultValue, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlgetbooleanproperty, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, defaultValue, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlclearproperty, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdlenumerateproperties, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_sdlproperties_sdldestroyproperties, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_sdlproperties_method_entry) {
	PHP_ME(Sdl3_SDL_SDLProperties, SDLGetGlobalProperties, arginfo_sdl3_sdl_sdlproperties_sdlgetglobalproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLCreateProperties, arginfo_sdl3_sdl_sdlproperties_sdlcreateproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLCopyProperties, arginfo_sdl3_sdl_sdlproperties_sdlcopyproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLLockProperties, arginfo_sdl3_sdl_sdlproperties_sdllockproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLUnlockProperties, arginfo_sdl3_sdl_sdlproperties_sdlunlockproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLSetPointerProperty, arginfo_sdl3_sdl_sdlproperties_sdlsetpointerproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLSetStringProperty, arginfo_sdl3_sdl_sdlproperties_sdlsetstringproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLSetNumberProperty, arginfo_sdl3_sdl_sdlproperties_sdlsetnumberproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLSetFloatProperty, arginfo_sdl3_sdl_sdlproperties_sdlsetfloatproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLSetBooleanProperty, arginfo_sdl3_sdl_sdlproperties_sdlsetbooleanproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLHasProperty, arginfo_sdl3_sdl_sdlproperties_sdlhasproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLGetPropertyType, arginfo_sdl3_sdl_sdlproperties_sdlgetpropertytype, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLGetPointerProperty, arginfo_sdl3_sdl_sdlproperties_sdlgetpointerproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLGetStringProperty, arginfo_sdl3_sdl_sdlproperties_sdlgetstringproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLGetNumberProperty, arginfo_sdl3_sdl_sdlproperties_sdlgetnumberproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLGetFloatProperty, arginfo_sdl3_sdl_sdlproperties_sdlgetfloatproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLGetBooleanProperty, arginfo_sdl3_sdl_sdlproperties_sdlgetbooleanproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLClearProperty, arginfo_sdl3_sdl_sdlproperties_sdlclearproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLEnumerateProperties, arginfo_sdl3_sdl_sdlproperties_sdlenumerateproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_SDLProperties, SDLDestroyProperties, arginfo_sdl3_sdl_sdlproperties_sdldestroyproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
