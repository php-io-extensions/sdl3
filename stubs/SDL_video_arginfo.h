/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 4f4d97d7eff6c2c9f951ce06d0cca88f459fd188 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_CreateWindow, 0, 4, SDL_Window, 1)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_CreateWindowWithProperties, 0, 1, SDL_Window, 1)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_DestroyWindow, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetWindowID, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_GetWindowFromID, 0, 1, SDL_Window, 1)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowTitle, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetWindowTitle, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetWindowSize, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(1, w, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, h, IS_LONG, 1)
ZEND_END_ARG_INFO()

#define arginfo_SDL_GetWindowSizeInPixels arginfo_SDL_GetWindowSize

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetWindowPixelDensity, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_GetWindowDisplayScale arginfo_SDL_GetWindowPixelDensity

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_ShowWindow, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_HideWindow arginfo_SDL_ShowWindow

#define arginfo_SDL_RaiseWindow arginfo_SDL_ShowWindow

#define arginfo_SDL_GetWindowFlags arginfo_SDL_GetWindowID

#define arginfo_SDL_GetWindowProperties arginfo_SDL_GetWindowID

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_CreateProperties, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_DestroyProperties, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetPointerProperty, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetNumberProperty, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetStringProperty, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetBooleanProperty, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetPointerProperty, 0, 3, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, default, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetNumberProperty, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, default, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetFloatProperty, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetStringProperty, 0, 3, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, default, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetFloatProperty, 0, 3, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, default, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetBooleanProperty, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, props, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, default, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetCurrentVideoDriver, 0, 0, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetDisplays, 0, 0, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

#define arginfo_SDL_GetPrimaryDisplay arginfo_SDL_CreateProperties

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetDisplayProperties, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, displayID, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetDisplayName, 0, 1, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, displayID, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetDisplayBounds, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, displayID, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_GetDisplayUsableBounds arginfo_SDL_GetDisplayBounds

#define arginfo_SDL_GetNaturalDisplayOrientation arginfo_SDL_GetDisplayProperties

#define arginfo_SDL_GetCurrentDisplayOrientation arginfo_SDL_GetDisplayProperties

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetDisplayContentScale, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, displayID, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetFullscreenDisplayModes, 0, 1, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(0, displayID, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetClosestFullscreenDisplayMode, 0, 6, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, displayID, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, refresh_rate, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, include_high_density_modes, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, closest, SDL_DisplayMode, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_GetDesktopDisplayMode, 0, 1, SDL_DisplayMode, 1)
	ZEND_ARG_TYPE_INFO(0, displayID, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_GetCurrentDisplayMode arginfo_SDL_GetDesktopDisplayMode

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetDisplayForPoint, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, point, SDL_Point, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetDisplayForRect, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_GetDisplayForWindow arginfo_SDL_GetWindowID

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowFullscreenMode, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_OBJ_INFO(0, mode, SDL_DisplayMode, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_GetWindowFullscreenMode, 0, 1, SDL_DisplayMode, 1)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowFullscreen, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, fullscreen, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowIcon, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_OBJ_INFO(0, icon, SDL_Surface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowPosition, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetWindowPosition, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(1, x, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, y, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowSize, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetWindowSafeArea, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowAspectRatio, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, min_aspect, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, max_aspect, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetWindowAspectRatio, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(1, min_aspect, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, max_aspect, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetWindowBordersSize, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(1, top, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, left, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, bottom, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, right, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowMinimumSize, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, min_w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, min_h, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_GetWindowMinimumSize arginfo_SDL_GetWindowSize

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowMaximumSize, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, max_w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, max_h, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_GetWindowMaximumSize arginfo_SDL_GetWindowSize

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowBordered, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, bordered, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowResizable, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, resizable, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowAlwaysOnTop, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, on_top, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_MaximizeWindow arginfo_SDL_ShowWindow

#define arginfo_SDL_MinimizeWindow arginfo_SDL_ShowWindow

#define arginfo_SDL_RestoreWindow arginfo_SDL_ShowWindow

#define arginfo_SDL_SyncWindow arginfo_SDL_ShowWindow

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowOpacity, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, opacity, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_GetWindowOpacity arginfo_SDL_GetWindowPixelDensity

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowFocusable, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, focusable, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_SetWindowHitTest, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, callback, IS_CALLABLE, 1)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, callback_data, IS_MIXED, 0, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_FlashWindow, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_TYPE_INFO(0, operation, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_ScreenSaverEnabled, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_EnableScreenSaver arginfo_SDL_ScreenSaverEnabled

#define arginfo_SDL_DisableScreenSaver arginfo_SDL_ScreenSaverEnabled

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_Window___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_SDL_Window_pointer arginfo_SDL_CreateProperties

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Window_fromPointer, 0, 1, IS_STATIC, 0)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(SDL_CreateWindow);
ZEND_FUNCTION(SDL_CreateWindowWithProperties);
ZEND_FUNCTION(SDL_DestroyWindow);
ZEND_FUNCTION(SDL_GetWindowID);
ZEND_FUNCTION(SDL_GetWindowFromID);
ZEND_FUNCTION(SDL_SetWindowTitle);
ZEND_FUNCTION(SDL_GetWindowTitle);
ZEND_FUNCTION(SDL_GetWindowSize);
ZEND_FUNCTION(SDL_GetWindowSizeInPixels);
ZEND_FUNCTION(SDL_GetWindowPixelDensity);
ZEND_FUNCTION(SDL_GetWindowDisplayScale);
ZEND_FUNCTION(SDL_ShowWindow);
ZEND_FUNCTION(SDL_HideWindow);
ZEND_FUNCTION(SDL_RaiseWindow);
ZEND_FUNCTION(SDL_GetWindowFlags);
ZEND_FUNCTION(SDL_GetWindowProperties);
ZEND_FUNCTION(SDL_CreateProperties);
ZEND_FUNCTION(SDL_DestroyProperties);
ZEND_FUNCTION(SDL_SetPointerProperty);
ZEND_FUNCTION(SDL_SetNumberProperty);
ZEND_FUNCTION(SDL_SetStringProperty);
ZEND_FUNCTION(SDL_SetBooleanProperty);
ZEND_FUNCTION(SDL_GetPointerProperty);
ZEND_FUNCTION(SDL_GetNumberProperty);
ZEND_FUNCTION(SDL_SetFloatProperty);
ZEND_FUNCTION(SDL_GetStringProperty);
ZEND_FUNCTION(SDL_GetFloatProperty);
ZEND_FUNCTION(SDL_GetBooleanProperty);
ZEND_FUNCTION(SDL_GetCurrentVideoDriver);
ZEND_FUNCTION(SDL_GetDisplays);
ZEND_FUNCTION(SDL_GetPrimaryDisplay);
ZEND_FUNCTION(SDL_GetDisplayProperties);
ZEND_FUNCTION(SDL_GetDisplayName);
ZEND_FUNCTION(SDL_GetDisplayBounds);
ZEND_FUNCTION(SDL_GetDisplayUsableBounds);
ZEND_FUNCTION(SDL_GetNaturalDisplayOrientation);
ZEND_FUNCTION(SDL_GetCurrentDisplayOrientation);
ZEND_FUNCTION(SDL_GetDisplayContentScale);
ZEND_FUNCTION(SDL_GetFullscreenDisplayModes);
ZEND_FUNCTION(SDL_GetClosestFullscreenDisplayMode);
ZEND_FUNCTION(SDL_GetDesktopDisplayMode);
ZEND_FUNCTION(SDL_GetCurrentDisplayMode);
ZEND_FUNCTION(SDL_GetDisplayForPoint);
ZEND_FUNCTION(SDL_GetDisplayForRect);
ZEND_FUNCTION(SDL_GetDisplayForWindow);
ZEND_FUNCTION(SDL_SetWindowFullscreenMode);
ZEND_FUNCTION(SDL_GetWindowFullscreenMode);
ZEND_FUNCTION(SDL_SetWindowFullscreen);
ZEND_FUNCTION(SDL_SetWindowIcon);
ZEND_FUNCTION(SDL_SetWindowPosition);
ZEND_FUNCTION(SDL_GetWindowPosition);
ZEND_FUNCTION(SDL_SetWindowSize);
ZEND_FUNCTION(SDL_GetWindowSafeArea);
ZEND_FUNCTION(SDL_SetWindowAspectRatio);
ZEND_FUNCTION(SDL_GetWindowAspectRatio);
ZEND_FUNCTION(SDL_GetWindowBordersSize);
ZEND_FUNCTION(SDL_SetWindowMinimumSize);
ZEND_FUNCTION(SDL_GetWindowMinimumSize);
ZEND_FUNCTION(SDL_SetWindowMaximumSize);
ZEND_FUNCTION(SDL_GetWindowMaximumSize);
ZEND_FUNCTION(SDL_SetWindowBordered);
ZEND_FUNCTION(SDL_SetWindowResizable);
ZEND_FUNCTION(SDL_SetWindowAlwaysOnTop);
ZEND_FUNCTION(SDL_MaximizeWindow);
ZEND_FUNCTION(SDL_MinimizeWindow);
ZEND_FUNCTION(SDL_RestoreWindow);
ZEND_FUNCTION(SDL_SyncWindow);
ZEND_FUNCTION(SDL_SetWindowOpacity);
ZEND_FUNCTION(SDL_GetWindowOpacity);
ZEND_FUNCTION(SDL_SetWindowFocusable);
ZEND_FUNCTION(SDL_SetWindowHitTest);
ZEND_FUNCTION(SDL_FlashWindow);
ZEND_FUNCTION(SDL_ScreenSaverEnabled);
ZEND_FUNCTION(SDL_EnableScreenSaver);
ZEND_FUNCTION(SDL_DisableScreenSaver);
ZEND_METHOD(SDL_Window, __construct);
ZEND_METHOD(SDL_Window, pointer);
ZEND_METHOD(SDL_Window, fromPointer);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(SDL_CreateWindow, arginfo_SDL_CreateWindow)
	ZEND_FE(SDL_CreateWindowWithProperties, arginfo_SDL_CreateWindowWithProperties)
	ZEND_FE(SDL_DestroyWindow, arginfo_SDL_DestroyWindow)
	ZEND_FE(SDL_GetWindowID, arginfo_SDL_GetWindowID)
	ZEND_FE(SDL_GetWindowFromID, arginfo_SDL_GetWindowFromID)
	ZEND_FE(SDL_SetWindowTitle, arginfo_SDL_SetWindowTitle)
	ZEND_FE(SDL_GetWindowTitle, arginfo_SDL_GetWindowTitle)
	ZEND_FE(SDL_GetWindowSize, arginfo_SDL_GetWindowSize)
	ZEND_FE(SDL_GetWindowSizeInPixels, arginfo_SDL_GetWindowSizeInPixels)
	ZEND_FE(SDL_GetWindowPixelDensity, arginfo_SDL_GetWindowPixelDensity)
	ZEND_FE(SDL_GetWindowDisplayScale, arginfo_SDL_GetWindowDisplayScale)
	ZEND_FE(SDL_ShowWindow, arginfo_SDL_ShowWindow)
	ZEND_FE(SDL_HideWindow, arginfo_SDL_HideWindow)
	ZEND_FE(SDL_RaiseWindow, arginfo_SDL_RaiseWindow)
	ZEND_FE(SDL_GetWindowFlags, arginfo_SDL_GetWindowFlags)
	ZEND_FE(SDL_GetWindowProperties, arginfo_SDL_GetWindowProperties)
	ZEND_FE(SDL_CreateProperties, arginfo_SDL_CreateProperties)
	ZEND_FE(SDL_DestroyProperties, arginfo_SDL_DestroyProperties)
	ZEND_FE(SDL_SetPointerProperty, arginfo_SDL_SetPointerProperty)
	ZEND_FE(SDL_SetNumberProperty, arginfo_SDL_SetNumberProperty)
	ZEND_FE(SDL_SetStringProperty, arginfo_SDL_SetStringProperty)
	ZEND_FE(SDL_SetBooleanProperty, arginfo_SDL_SetBooleanProperty)
	ZEND_FE(SDL_GetPointerProperty, arginfo_SDL_GetPointerProperty)
	ZEND_FE(SDL_GetNumberProperty, arginfo_SDL_GetNumberProperty)
	ZEND_FE(SDL_SetFloatProperty, arginfo_SDL_SetFloatProperty)
	ZEND_FE(SDL_GetStringProperty, arginfo_SDL_GetStringProperty)
	ZEND_FE(SDL_GetFloatProperty, arginfo_SDL_GetFloatProperty)
	ZEND_FE(SDL_GetBooleanProperty, arginfo_SDL_GetBooleanProperty)
	ZEND_FE(SDL_GetCurrentVideoDriver, arginfo_SDL_GetCurrentVideoDriver)
	ZEND_FE(SDL_GetDisplays, arginfo_SDL_GetDisplays)
	ZEND_FE(SDL_GetPrimaryDisplay, arginfo_SDL_GetPrimaryDisplay)
	ZEND_FE(SDL_GetDisplayProperties, arginfo_SDL_GetDisplayProperties)
	ZEND_FE(SDL_GetDisplayName, arginfo_SDL_GetDisplayName)
	ZEND_FE(SDL_GetDisplayBounds, arginfo_SDL_GetDisplayBounds)
	ZEND_FE(SDL_GetDisplayUsableBounds, arginfo_SDL_GetDisplayUsableBounds)
	ZEND_FE(SDL_GetNaturalDisplayOrientation, arginfo_SDL_GetNaturalDisplayOrientation)
	ZEND_FE(SDL_GetCurrentDisplayOrientation, arginfo_SDL_GetCurrentDisplayOrientation)
	ZEND_FE(SDL_GetDisplayContentScale, arginfo_SDL_GetDisplayContentScale)
	ZEND_FE(SDL_GetFullscreenDisplayModes, arginfo_SDL_GetFullscreenDisplayModes)
	ZEND_FE(SDL_GetClosestFullscreenDisplayMode, arginfo_SDL_GetClosestFullscreenDisplayMode)
	ZEND_FE(SDL_GetDesktopDisplayMode, arginfo_SDL_GetDesktopDisplayMode)
	ZEND_FE(SDL_GetCurrentDisplayMode, arginfo_SDL_GetCurrentDisplayMode)
	ZEND_FE(SDL_GetDisplayForPoint, arginfo_SDL_GetDisplayForPoint)
	ZEND_FE(SDL_GetDisplayForRect, arginfo_SDL_GetDisplayForRect)
	ZEND_FE(SDL_GetDisplayForWindow, arginfo_SDL_GetDisplayForWindow)
	ZEND_FE(SDL_SetWindowFullscreenMode, arginfo_SDL_SetWindowFullscreenMode)
	ZEND_FE(SDL_GetWindowFullscreenMode, arginfo_SDL_GetWindowFullscreenMode)
	ZEND_FE(SDL_SetWindowFullscreen, arginfo_SDL_SetWindowFullscreen)
	ZEND_FE(SDL_SetWindowIcon, arginfo_SDL_SetWindowIcon)
	ZEND_FE(SDL_SetWindowPosition, arginfo_SDL_SetWindowPosition)
	ZEND_FE(SDL_GetWindowPosition, arginfo_SDL_GetWindowPosition)
	ZEND_FE(SDL_SetWindowSize, arginfo_SDL_SetWindowSize)
	ZEND_FE(SDL_GetWindowSafeArea, arginfo_SDL_GetWindowSafeArea)
	ZEND_FE(SDL_SetWindowAspectRatio, arginfo_SDL_SetWindowAspectRatio)
	ZEND_FE(SDL_GetWindowAspectRatio, arginfo_SDL_GetWindowAspectRatio)
	ZEND_FE(SDL_GetWindowBordersSize, arginfo_SDL_GetWindowBordersSize)
	ZEND_FE(SDL_SetWindowMinimumSize, arginfo_SDL_SetWindowMinimumSize)
	ZEND_FE(SDL_GetWindowMinimumSize, arginfo_SDL_GetWindowMinimumSize)
	ZEND_FE(SDL_SetWindowMaximumSize, arginfo_SDL_SetWindowMaximumSize)
	ZEND_FE(SDL_GetWindowMaximumSize, arginfo_SDL_GetWindowMaximumSize)
	ZEND_FE(SDL_SetWindowBordered, arginfo_SDL_SetWindowBordered)
	ZEND_FE(SDL_SetWindowResizable, arginfo_SDL_SetWindowResizable)
	ZEND_FE(SDL_SetWindowAlwaysOnTop, arginfo_SDL_SetWindowAlwaysOnTop)
	ZEND_FE(SDL_MaximizeWindow, arginfo_SDL_MaximizeWindow)
	ZEND_FE(SDL_MinimizeWindow, arginfo_SDL_MinimizeWindow)
	ZEND_FE(SDL_RestoreWindow, arginfo_SDL_RestoreWindow)
	ZEND_FE(SDL_SyncWindow, arginfo_SDL_SyncWindow)
	ZEND_FE(SDL_SetWindowOpacity, arginfo_SDL_SetWindowOpacity)
	ZEND_FE(SDL_GetWindowOpacity, arginfo_SDL_GetWindowOpacity)
	ZEND_FE(SDL_SetWindowFocusable, arginfo_SDL_SetWindowFocusable)
	ZEND_FE(SDL_SetWindowHitTest, arginfo_SDL_SetWindowHitTest)
	ZEND_FE(SDL_FlashWindow, arginfo_SDL_FlashWindow)
	ZEND_FE(SDL_ScreenSaverEnabled, arginfo_SDL_ScreenSaverEnabled)
	ZEND_FE(SDL_EnableScreenSaver, arginfo_SDL_EnableScreenSaver)
	ZEND_FE(SDL_DisableScreenSaver, arginfo_SDL_DisableScreenSaver)
	ZEND_FE_END
};

static const zend_function_entry class_SDL_Window_methods[] = {
	ZEND_ME(SDL_Window, __construct, arginfo_class_SDL_Window___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SDL_Window, pointer, arginfo_class_SDL_Window_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_Window, fromPointer, arginfo_class_SDL_Window_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static void register_SDL_video_symbols(int module_number)
{
	REGISTER_LONG_CONSTANT("SDL_WINDOW_HIDDEN", SDL_WINDOW_HIDDEN, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_RESIZABLE", SDL_WINDOW_RESIZABLE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_HIGH_PIXEL_DENSITY", SDL_WINDOW_HIGH_PIXEL_DENSITY, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_OPENGL", SDL_WINDOW_OPENGL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_VULKAN", SDL_WINDOW_VULKAN, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_METAL", SDL_WINDOW_METAL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_FULLSCREEN", SDL_WINDOW_FULLSCREEN, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_OCCLUDED", SDL_WINDOW_OCCLUDED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_BORDERLESS", SDL_WINDOW_BORDERLESS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_MINIMIZED", SDL_WINDOW_MINIMIZED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_MAXIMIZED", SDL_WINDOW_MAXIMIZED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_INPUT_FOCUS", SDL_WINDOW_INPUT_FOCUS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_EXTERNAL", SDL_WINDOW_EXTERNAL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_MODAL", SDL_WINDOW_MODAL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_ALWAYS_ON_TOP", SDL_WINDOW_ALWAYS_ON_TOP, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_UTILITY", SDL_WINDOW_UTILITY, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_TRANSPARENT", SDL_WINDOW_TRANSPARENT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_NOT_FOCUSABLE", SDL_WINDOW_NOT_FOCUSABLE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOWPOS_UNDEFINED_MASK", SDL_WINDOWPOS_UNDEFINED_MASK, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOWPOS_UNDEFINED", SDL_WINDOWPOS_UNDEFINED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOWPOS_CENTERED_MASK", SDL_WINDOWPOS_CENTERED_MASK, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOWPOS_CENTERED", SDL_WINDOWPOS_CENTERED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_SURFACE_VSYNC_DISABLED", SDL_WINDOW_SURFACE_VSYNC_DISABLED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_SURFACE_VSYNC_ADAPTIVE", SDL_WINDOW_SURFACE_VSYNC_ADAPTIVE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_FLASH_CANCEL", SDL_FLASH_CANCEL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_FLASH_BRIEFLY", SDL_FLASH_BRIEFLY, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_FLASH_UNTIL_FOCUSED", SDL_FLASH_UNTIL_FOCUSED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HITTEST_NORMAL", SDL_HITTEST_NORMAL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HITTEST_DRAGGABLE", SDL_HITTEST_DRAGGABLE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HITTEST_RESIZE_TOPLEFT", SDL_HITTEST_RESIZE_TOPLEFT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HITTEST_RESIZE_TOP", SDL_HITTEST_RESIZE_TOP, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HITTEST_RESIZE_TOPRIGHT", SDL_HITTEST_RESIZE_TOPRIGHT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HITTEST_RESIZE_RIGHT", SDL_HITTEST_RESIZE_RIGHT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HITTEST_RESIZE_BOTTOMRIGHT", SDL_HITTEST_RESIZE_BOTTOMRIGHT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HITTEST_RESIZE_BOTTOM", SDL_HITTEST_RESIZE_BOTTOM, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HITTEST_RESIZE_BOTTOMLEFT", SDL_HITTEST_RESIZE_BOTTOMLEFT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HITTEST_RESIZE_LEFT", SDL_HITTEST_RESIZE_LEFT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_ORIENTATION_UNKNOWN", SDL_ORIENTATION_UNKNOWN, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_ORIENTATION_LANDSCAPE", SDL_ORIENTATION_LANDSCAPE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_ORIENTATION_LANDSCAPE_FLIPPED", SDL_ORIENTATION_LANDSCAPE_FLIPPED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_ORIENTATION_PORTRAIT", SDL_ORIENTATION_PORTRAIT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_ORIENTATION_PORTRAIT_FLIPPED", SDL_ORIENTATION_PORTRAIT_FLIPPED, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_TITLE_STRING", SDL_PROP_WINDOW_CREATE_TITLE_STRING, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER", SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER", SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN", SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN", SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN", SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_VULKAN_BOOLEAN", SDL_PROP_WINDOW_CREATE_VULKAN_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_METAL_BOOLEAN", SDL_PROP_WINDOW_CREATE_METAL_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN", SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_COCOA_VIEW_POINTER", SDL_PROP_WINDOW_CREATE_COCOA_VIEW_POINTER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_WAYLAND_WL_SURFACE_POINTER", SDL_PROP_WINDOW_CREATE_WAYLAND_WL_SURFACE_POINTER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_X11_WINDOW_NUMBER", SDL_PROP_WINDOW_CREATE_X11_WINDOW_NUMBER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_ALWAYS_ON_TOP_BOOLEAN", SDL_PROP_WINDOW_CREATE_ALWAYS_ON_TOP_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN", SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN", SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN", SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN", SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_MAXIMIZED_BOOLEAN", SDL_PROP_WINDOW_CREATE_MAXIMIZED_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_MINIMIZED_BOOLEAN", SDL_PROP_WINDOW_CREATE_MINIMIZED_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_TRANSPARENT_BOOLEAN", SDL_PROP_WINDOW_CREATE_TRANSPARENT_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_UTILITY_BOOLEAN", SDL_PROP_WINDOW_CREATE_UTILITY_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_X_NUMBER", SDL_PROP_WINDOW_CREATE_X_NUMBER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_Y_NUMBER", SDL_PROP_WINDOW_CREATE_Y_NUMBER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_CREATE_COCOA_WINDOW_POINTER", SDL_PROP_WINDOW_CREATE_COCOA_WINDOW_POINTER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN", SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT", SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT", SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_COCOA_WINDOW_POINTER", SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_COCOA_METAL_VIEW_TAG_NUMBER", SDL_PROP_WINDOW_COCOA_METAL_VIEW_TAG_NUMBER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_X11_DISPLAY_POINTER", SDL_PROP_WINDOW_X11_DISPLAY_POINTER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_X11_SCREEN_NUMBER", SDL_PROP_WINDOW_X11_SCREEN_NUMBER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_X11_WINDOW_NUMBER", SDL_PROP_WINDOW_X11_WINDOW_NUMBER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER", SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER", SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN", SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, CONST_PERSISTENT);
}

static zend_class_entry *register_class_SDL_Window(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_Window", class_SDL_Window_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_SDL_DisplayMode(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_DisplayMode", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_displayID_default_value;
	ZVAL_LONG(&property_displayID_default_value, 0);
	zend_string *property_displayID_name = zend_string_init("displayID", sizeof("displayID") - 1, 1);
	zend_declare_typed_property(class_entry, property_displayID_name, &property_displayID_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_displayID_name);

	zval property_format_default_value;
	ZVAL_LONG(&property_format_default_value, 0);
	zend_string *property_format_name = zend_string_init("format", sizeof("format") - 1, 1);
	zend_declare_typed_property(class_entry, property_format_name, &property_format_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_format_name);

	zval property_w_default_value;
	ZVAL_LONG(&property_w_default_value, 0);
	zend_string *property_w_name = zend_string_init("w", sizeof("w") - 1, 1);
	zend_declare_typed_property(class_entry, property_w_name, &property_w_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_w_name);

	zval property_h_default_value;
	ZVAL_LONG(&property_h_default_value, 0);
	zend_string *property_h_name = zend_string_init("h", sizeof("h") - 1, 1);
	zend_declare_typed_property(class_entry, property_h_name, &property_h_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_h_name);

	zval property_pixel_density_default_value;
	ZVAL_DOUBLE(&property_pixel_density_default_value, 0.0);
	zend_string *property_pixel_density_name = zend_string_init("pixel_density", sizeof("pixel_density") - 1, 1);
	zend_declare_typed_property(class_entry, property_pixel_density_name, &property_pixel_density_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_pixel_density_name);

	zval property_refresh_rate_default_value;
	ZVAL_DOUBLE(&property_refresh_rate_default_value, 0.0);
	zend_string *property_refresh_rate_name = zend_string_init("refresh_rate", sizeof("refresh_rate") - 1, 1);
	zend_declare_typed_property(class_entry, property_refresh_rate_name, &property_refresh_rate_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_refresh_rate_name);

	zval property_refresh_rate_numerator_default_value;
	ZVAL_LONG(&property_refresh_rate_numerator_default_value, 0);
	zend_string *property_refresh_rate_numerator_name = zend_string_init("refresh_rate_numerator", sizeof("refresh_rate_numerator") - 1, 1);
	zend_declare_typed_property(class_entry, property_refresh_rate_numerator_name, &property_refresh_rate_numerator_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_refresh_rate_numerator_name);

	zval property_refresh_rate_denominator_default_value;
	ZVAL_LONG(&property_refresh_rate_denominator_default_value, 0);
	zend_string *property_refresh_rate_denominator_name = zend_string_init("refresh_rate_denominator", sizeof("refresh_rate_denominator") - 1, 1);
	zend_declare_typed_property(class_entry, property_refresh_rate_denominator_name, &property_refresh_rate_denominator_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_refresh_rate_denominator_name);

	return class_entry;
}
