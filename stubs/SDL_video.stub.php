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
