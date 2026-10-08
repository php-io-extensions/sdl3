<?php

/** @generate-class-entries */

/**
 * @var int
 * @cvalue SDL_INIT_VIDEO
 */
const SDL_INIT_VIDEO = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_QUIT
 */
const SDL_EVENT_QUIT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_CLOSE_REQUESTED
 */
const SDL_EVENT_WINDOW_CLOSE_REQUESTED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_RESIZED
 */
const SDL_EVENT_WINDOW_RESIZED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED
 */
const SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_FOCUS_GAINED
 */
const SDL_EVENT_WINDOW_FOCUS_GAINED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_FOCUS_LOST
 */
const SDL_EVENT_WINDOW_FOCUS_LOST = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_SHOWN
 */
const SDL_EVENT_WINDOW_SHOWN = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_HIDDEN
 */
const SDL_EVENT_WINDOW_HIDDEN = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_EXPOSED
 */
const SDL_EVENT_WINDOW_EXPOSED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_MOVED
 */
const SDL_EVENT_WINDOW_MOVED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_METAL_VIEW_RESIZED
 */
const SDL_EVENT_WINDOW_METAL_VIEW_RESIZED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_MINIMIZED
 */
const SDL_EVENT_WINDOW_MINIMIZED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_MAXIMIZED
 */
const SDL_EVENT_WINDOW_MAXIMIZED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_RESTORED
 */
const SDL_EVENT_WINDOW_RESTORED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_HIT_TEST
 */
const SDL_EVENT_WINDOW_HIT_TEST = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_ICCPROF_CHANGED
 */
const SDL_EVENT_WINDOW_ICCPROF_CHANGED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_DISPLAY_CHANGED
 */
const SDL_EVENT_WINDOW_DISPLAY_CHANGED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED
 */
const SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_SAFE_AREA_CHANGED
 */
const SDL_EVENT_WINDOW_SAFE_AREA_CHANGED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_OCCLUDED
 */
const SDL_EVENT_WINDOW_OCCLUDED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_ENTER_FULLSCREEN
 */
const SDL_EVENT_WINDOW_ENTER_FULLSCREEN = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_LEAVE_FULLSCREEN
 */
const SDL_EVENT_WINDOW_LEAVE_FULLSCREEN = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_DESTROYED
 */
const SDL_EVENT_WINDOW_DESTROYED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_HDR_STATE_CHANGED
 */
const SDL_EVENT_WINDOW_HDR_STATE_CHANGED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_FIRST
 */
const SDL_EVENT_WINDOW_FIRST = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_WINDOW_LAST
 */
const SDL_EVENT_WINDOW_LAST = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_DISPLAY_ORIENTATION
 */
const SDL_EVENT_DISPLAY_ORIENTATION = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_DISPLAY_ADDED
 */
const SDL_EVENT_DISPLAY_ADDED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_DISPLAY_REMOVED
 */
const SDL_EVENT_DISPLAY_REMOVED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_DISPLAY_MOVED
 */
const SDL_EVENT_DISPLAY_MOVED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED
 */
const SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED
 */
const SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED
 */
const SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_DISPLAY_FIRST
 */
const SDL_EVENT_DISPLAY_FIRST = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_EVENT_DISPLAY_LAST
 */
const SDL_EVENT_DISPLAY_LAST = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_HINT_VIDEO_DRIVER
 */
const SDL_HINT_VIDEO_DRIVER = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES
 */
const SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS
 */
const SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS = UNKNOWN;

/**
 * @var string
 * @cvalue SDL_HINT_VIDEO_FORCE_EGL
 */
const SDL_HINT_VIDEO_FORCE_EGL = UNKNOWN;

/**
 * @not-serializable
 */
final class SDL_WindowEvent
{
    public int $type = 0;

    public int $timestamp = 0;

    public int $windowID = 0;

    public int $data1 = 0;

    public int $data2 = 0;
}

/**
 * @not-serializable
 */
final class SDL_DisplayEvent
{
    public int $type = 0;

    public int $timestamp = 0;

    public int $displayID = 0;

    public int $data1 = 0;

    public int $data2 = 0;
}

/**
 * @not-serializable
 */
final class SDL_Event
{
    public int $type = 0;

    public SDL_WindowEvent $window;

    public SDL_DisplayEvent $display;

    public function __construct() {}
}

function SDL_Init(int $flags): bool {}

function SDL_InitSubSystem(int $flags): bool {}

function SDL_Quit(): void {}

function SDL_GetError(): string {}

function SDL_ClearError(): bool {}

function SDL_GetVersion(): int {}

function SDL_SetHint(string $name, string $value): bool {}

function SDL_PumpEvents(): void {}

/** A null $event passes NULL through to SDL and discards the event. */
function SDL_PollEvent(?SDL_Event $event): bool {}

/** A null $event passes NULL through to SDL and discards the event. */
function SDL_WaitEventTimeout(?SDL_Event $event, int $timeoutMS): bool {}
