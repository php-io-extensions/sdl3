<?php

/** @generate-class-entries */

/**
 * An address other than null is trusted: the binding does not check that it points at a live object.
 *
 * @not-serializable
 */
final class SDL_Window
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): static {}
}

/**
 * A copy of the native SDL_DisplayMode. SDL's private driver data is not carried; SDL matches a
 * mode passed back in against its own list by its public fields.
 *
 * @not-serializable
 */
final class SDL_DisplayMode
{
    public int $displayID = 0;

    public int $format = 0;

    public int $w = 0;

    public int $h = 0;

    public float $pixel_density = 0.0;

    public float $refresh_rate = 0.0;

    public int $refresh_rate_numerator = 0;

    public int $refresh_rate_denominator = 0;
}

/**
 * @var int
 * @cvalue SDL_WINDOW_HIDDEN
 */
const SDL_WINDOW_HIDDEN = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_RESIZABLE
 */
const SDL_WINDOW_RESIZABLE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_HIGH_PIXEL_DENSITY
 */
const SDL_WINDOW_HIGH_PIXEL_DENSITY = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_OPENGL
 */
const SDL_WINDOW_OPENGL = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_VULKAN
 */
const SDL_WINDOW_VULKAN = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_METAL
 */
const SDL_WINDOW_METAL = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_FULLSCREEN
 */
const SDL_WINDOW_FULLSCREEN = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_OCCLUDED
 */
const SDL_WINDOW_OCCLUDED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_BORDERLESS
 */
const SDL_WINDOW_BORDERLESS = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_MINIMIZED
 */
const SDL_WINDOW_MINIMIZED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_MAXIMIZED
 */
const SDL_WINDOW_MAXIMIZED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_INPUT_FOCUS
 */
const SDL_WINDOW_INPUT_FOCUS = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_EXTERNAL
 */
const SDL_WINDOW_EXTERNAL = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_MODAL
 */
const SDL_WINDOW_MODAL = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_ALWAYS_ON_TOP
 */
const SDL_WINDOW_ALWAYS_ON_TOP = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_UTILITY
 */
const SDL_WINDOW_UTILITY = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_TRANSPARENT
 */
const SDL_WINDOW_TRANSPARENT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_NOT_FOCUSABLE
 */
const SDL_WINDOW_NOT_FOCUSABLE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOWPOS_UNDEFINED_MASK
 */
const SDL_WINDOWPOS_UNDEFINED_MASK = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOWPOS_UNDEFINED
 */
const SDL_WINDOWPOS_UNDEFINED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOWPOS_CENTERED_MASK
 */
const SDL_WINDOWPOS_CENTERED_MASK = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOWPOS_CENTERED
 */
const SDL_WINDOWPOS_CENTERED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_SURFACE_VSYNC_DISABLED
 */
const SDL_WINDOW_SURFACE_VSYNC_DISABLED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_WINDOW_SURFACE_VSYNC_ADAPTIVE
 */
const SDL_WINDOW_SURFACE_VSYNC_ADAPTIVE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_FLASH_CANCEL
 */
const SDL_FLASH_CANCEL = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_FLASH_BRIEFLY
 */
const SDL_FLASH_BRIEFLY = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_FLASH_UNTIL_FOCUSED
 */
const SDL_FLASH_UNTIL_FOCUSED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_HITTEST_NORMAL
 */
const SDL_HITTEST_NORMAL = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_HITTEST_DRAGGABLE
 */
const SDL_HITTEST_DRAGGABLE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_HITTEST_RESIZE_TOPLEFT
 */
const SDL_HITTEST_RESIZE_TOPLEFT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_HITTEST_RESIZE_TOP
 */
const SDL_HITTEST_RESIZE_TOP = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_HITTEST_RESIZE_TOPRIGHT
 */
const SDL_HITTEST_RESIZE_TOPRIGHT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_HITTEST_RESIZE_RIGHT
 */
const SDL_HITTEST_RESIZE_RIGHT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_HITTEST_RESIZE_BOTTOMRIGHT
 */
const SDL_HITTEST_RESIZE_BOTTOMRIGHT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_HITTEST_RESIZE_BOTTOM
 */
const SDL_HITTEST_RESIZE_BOTTOM = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_HITTEST_RESIZE_BOTTOMLEFT
 */
const SDL_HITTEST_RESIZE_BOTTOMLEFT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_HITTEST_RESIZE_LEFT
 */
const SDL_HITTEST_RESIZE_LEFT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_ORIENTATION_UNKNOWN
 */
const SDL_ORIENTATION_UNKNOWN = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_ORIENTATION_LANDSCAPE
 */
const SDL_ORIENTATION_LANDSCAPE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_ORIENTATION_LANDSCAPE_FLIPPED
 */
const SDL_ORIENTATION_LANDSCAPE_FLIPPED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_ORIENTATION_PORTRAIT
 */
const SDL_ORIENTATION_PORTRAIT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_ORIENTATION_PORTRAIT_FLIPPED
 */
const SDL_ORIENTATION_PORTRAIT_FLIPPED = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_TITLE_STRING
 */
const SDL_PROP_WINDOW_CREATE_TITLE_STRING = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER
 */
const SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER
 */
const SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_VULKAN_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_VULKAN_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_METAL_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_METAL_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_COCOA_VIEW_POINTER
 */
const SDL_PROP_WINDOW_CREATE_COCOA_VIEW_POINTER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_WAYLAND_WL_SURFACE_POINTER
 */
const SDL_PROP_WINDOW_CREATE_WAYLAND_WL_SURFACE_POINTER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_X11_WINDOW_NUMBER
 */
const SDL_PROP_WINDOW_CREATE_X11_WINDOW_NUMBER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_ALWAYS_ON_TOP_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_ALWAYS_ON_TOP_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_MAXIMIZED_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_MAXIMIZED_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_MINIMIZED_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_MINIMIZED_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_TRANSPARENT_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_TRANSPARENT_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_UTILITY_BOOLEAN
 */
const SDL_PROP_WINDOW_CREATE_UTILITY_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_X_NUMBER
 */
const SDL_PROP_WINDOW_CREATE_X_NUMBER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_Y_NUMBER
 */
const SDL_PROP_WINDOW_CREATE_Y_NUMBER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_CREATE_COCOA_WINDOW_POINTER
 */
const SDL_PROP_WINDOW_CREATE_COCOA_WINDOW_POINTER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN
 */
const SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT
 */
const SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT
 */
const SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_COCOA_WINDOW_POINTER
 */
const SDL_PROP_WINDOW_COCOA_WINDOW_POINTER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_COCOA_METAL_VIEW_TAG_NUMBER
 */
const SDL_PROP_WINDOW_COCOA_METAL_VIEW_TAG_NUMBER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_X11_DISPLAY_POINTER
 */
const SDL_PROP_WINDOW_X11_DISPLAY_POINTER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_X11_SCREEN_NUMBER
 */
const SDL_PROP_WINDOW_X11_SCREEN_NUMBER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_X11_WINDOW_NUMBER
 */
const SDL_PROP_WINDOW_X11_WINDOW_NUMBER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER
 */
const SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER
 */
const SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN
 */
const SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN = UNKNOWN;

function SDL_CreateWindow(string $title, int $w, int $h, int $flags): ?SDL_Window {}

function SDL_CreateWindowWithProperties(int $props): ?SDL_Window {}

function SDL_DestroyWindow(SDL_Window $window): void {}

function SDL_GetWindowID(SDL_Window $window): int {}

function SDL_GetWindowFromID(int $id): ?SDL_Window {}

function SDL_SetWindowTitle(SDL_Window $window, string $title): bool {}

function SDL_GetWindowTitle(SDL_Window $window): string {}

function SDL_GetWindowSize(SDL_Window $window, ?int &$w, ?int &$h): bool {}

function SDL_GetWindowSizeInPixels(SDL_Window $window, ?int &$w, ?int &$h): bool {}

function SDL_GetWindowPixelDensity(SDL_Window $window): float {}

function SDL_GetWindowDisplayScale(SDL_Window $window): float {}

function SDL_ShowWindow(SDL_Window $window): bool {}

function SDL_HideWindow(SDL_Window $window): bool {}

function SDL_RaiseWindow(SDL_Window $window): bool {}

function SDL_GetWindowFlags(SDL_Window $window): int {}

function SDL_GetWindowProperties(SDL_Window $window): int {}

function SDL_CreateProperties(): int {}

function SDL_DestroyProperties(int $props): void {}

/** $value other than null is trusted. */
function SDL_SetPointerProperty(int $props, string $name, ?int $value): bool {}

function SDL_SetNumberProperty(int $props, string $name, int $value): bool {}

function SDL_SetStringProperty(int $props, string $name, ?string $value): bool {}

function SDL_SetBooleanProperty(int $props, string $name, bool $value): bool {}

/** The result and $default are addresses. Null is a null pointer; any other address is trusted. */
function SDL_GetPointerProperty(int $props, string $name, ?int $default): ?int {}

function SDL_GetNumberProperty(int $props, string $name, int $default): int {}

function SDL_SetFloatProperty(int $props, string $name, float $value): bool {}

/** Null $default is a null pointer; the result is null when SDL answers one. */
function SDL_GetStringProperty(int $props, string $name, ?string $default): ?string {}

function SDL_GetFloatProperty(int $props, string $name, float $default): float {}

function SDL_GetBooleanProperty(int $props, string $name, bool $default): bool {}

function SDL_GetCurrentVideoDriver(): ?string {}

/** The display IDs; null when SDL fails. */
function SDL_GetDisplays(): ?array {}

function SDL_GetPrimaryDisplay(): int {}

function SDL_GetDisplayProperties(int $displayID): int {}

function SDL_GetDisplayName(int $displayID): ?string {}

/** Fills $rect. */
function SDL_GetDisplayBounds(int $displayID, SDL_Rect $rect): bool {}

/** Fills $rect. */
function SDL_GetDisplayUsableBounds(int $displayID, SDL_Rect $rect): bool {}

function SDL_GetNaturalDisplayOrientation(int $displayID): int {}

function SDL_GetCurrentDisplayOrientation(int $displayID): int {}

function SDL_GetDisplayContentScale(int $displayID): float {}

/** A list of SDL_DisplayMode copies; null when SDL fails. */
function SDL_GetFullscreenDisplayModes(int $displayID): ?array {}

/** Fills $closest. */
function SDL_GetClosestFullscreenDisplayMode(int $displayID, int $w, int $h, float $refresh_rate, bool $include_high_density_modes, SDL_DisplayMode $closest): bool {}

function SDL_GetDesktopDisplayMode(int $displayID): ?SDL_DisplayMode {}

function SDL_GetCurrentDisplayMode(int $displayID): ?SDL_DisplayMode {}

function SDL_GetDisplayForPoint(SDL_Point $point): int {}

function SDL_GetDisplayForRect(SDL_Rect $rect): int {}

function SDL_GetDisplayForWindow(SDL_Window $window): int {}

/** Null $mode is borderless fullscreen desktop; a mode is exclusive fullscreen. */
function SDL_SetWindowFullscreenMode(SDL_Window $window, ?SDL_DisplayMode $mode): bool {}

/** Null is borderless fullscreen desktop. */
function SDL_GetWindowFullscreenMode(SDL_Window $window): ?SDL_DisplayMode {}

function SDL_SetWindowFullscreen(SDL_Window $window, bool $fullscreen): bool {}

function SDL_SetWindowIcon(SDL_Window $window, SDL_Surface $icon): bool {}

function SDL_SetWindowPosition(SDL_Window $window, int $x, int $y): bool {}

function SDL_GetWindowPosition(SDL_Window $window, ?int &$x, ?int &$y): bool {}

function SDL_SetWindowSize(SDL_Window $window, int $w, int $h): bool {}

/** Fills $rect. */
function SDL_GetWindowSafeArea(SDL_Window $window, SDL_Rect $rect): bool {}

function SDL_SetWindowAspectRatio(SDL_Window $window, float $min_aspect, float $max_aspect): bool {}

function SDL_GetWindowAspectRatio(SDL_Window $window, ?float &$min_aspect, ?float &$max_aspect): bool {}

function SDL_GetWindowBordersSize(SDL_Window $window, ?int &$top, ?int &$left, ?int &$bottom, ?int &$right): bool {}

function SDL_SetWindowMinimumSize(SDL_Window $window, int $min_w, int $min_h): bool {}

function SDL_GetWindowMinimumSize(SDL_Window $window, ?int &$w, ?int &$h): bool {}

function SDL_SetWindowMaximumSize(SDL_Window $window, int $max_w, int $max_h): bool {}

function SDL_GetWindowMaximumSize(SDL_Window $window, ?int &$w, ?int &$h): bool {}

function SDL_SetWindowBordered(SDL_Window $window, bool $bordered): bool {}

function SDL_SetWindowResizable(SDL_Window $window, bool $resizable): bool {}

function SDL_SetWindowAlwaysOnTop(SDL_Window $window, bool $on_top): bool {}

function SDL_MaximizeWindow(SDL_Window $window): bool {}

function SDL_MinimizeWindow(SDL_Window $window): bool {}

function SDL_RestoreWindow(SDL_Window $window): bool {}

function SDL_SyncWindow(SDL_Window $window): bool {}

function SDL_SetWindowOpacity(SDL_Window $window, float $opacity): bool {}

function SDL_GetWindowOpacity(SDL_Window $window): float {}

function SDL_SetWindowFocusable(SDL_Window $window, bool $focusable): bool {}

/**
 * SDL calls $callback(SDL_Window $win, SDL_Point $area, mixed $data): int on the thread pumping
 * events and uses the SDL_HITTEST_* it returns; SDL_HITTEST_NORMAL when it throws. Null $callback
 * removes it. The callback and $callback_data are held until replaced, SDL_DestroyWindow(),
 * SDL_Quit() or the end of the request.
 */
function SDL_SetWindowHitTest(SDL_Window $window, ?callable $callback, mixed $callback_data = null): bool {}

function SDL_FlashWindow(SDL_Window $window, int $operation): bool {}

function SDL_ScreenSaverEnabled(): bool {}

function SDL_EnableScreenSaver(): bool {}

function SDL_DisableScreenSaver(): bool {}
