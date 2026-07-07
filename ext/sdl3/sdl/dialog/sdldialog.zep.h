
extern zend_class_entry *sdl3_sdl_dialog_sdldialog_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Dialog_SDLDialog);

PHP_METHOD(Sdl3_SDL_Dialog_SDLDialog, SDLShowOpenFileDialog);
PHP_METHOD(Sdl3_SDL_Dialog_SDLDialog, SDLShowSaveFileDialog);
PHP_METHOD(Sdl3_SDL_Dialog_SDLDialog, SDLShowOpenFolderDialog);
PHP_METHOD(Sdl3_SDL_Dialog_SDLDialog, SDLShowFileDialogWithProperties);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_dialog_sdldialog_sdlshowopenfiledialog, 0, 1, IS_VOID, 0)

	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, filters)
	ZEND_ARG_INFO(0, default_location)
	ZEND_ARG_TYPE_INFO(0, allow_many, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_dialog_sdldialog_sdlshowsavefiledialog, 0, 1, IS_VOID, 0)

	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, filters)
	ZEND_ARG_INFO(0, default_location)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_dialog_sdldialog_sdlshowopenfolderdialog, 0, 1, IS_VOID, 0)

	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, default_location)
	ZEND_ARG_TYPE_INFO(0, allow_many, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_dialog_sdldialog_sdlshowfiledialogwithproperties, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_dialog_sdldialog_method_entry) {
	PHP_ME(Sdl3_SDL_Dialog_SDLDialog, SDLShowOpenFileDialog, arginfo_sdl3_sdl_dialog_sdldialog_sdlshowopenfiledialog, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Dialog_SDLDialog, SDLShowSaveFileDialog, arginfo_sdl3_sdl_dialog_sdldialog_sdlshowsavefiledialog, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Dialog_SDLDialog, SDLShowOpenFolderDialog, arginfo_sdl3_sdl_dialog_sdldialog_sdlshowopenfolderdialog, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Dialog_SDLDialog, SDLShowFileDialogWithProperties, arginfo_sdl3_sdl_dialog_sdldialog_sdlshowfiledialogwithproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
