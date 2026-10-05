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
 * @var string
 * @cvalue SDL_HINT_VIDEO_DRIVER
 */
const SDL_HINT_VIDEO_DRIVER = UNKNOWN;

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
final class SDL_Event
{
    public int $type = 0;

    public SDL_WindowEvent $window;

    public function __construct() {}
}

function SDL_Init(int $flags): bool {}

function SDL_InitSubSystem(int $flags): bool {}

function SDL_Quit(): void {}

function SDL_GetError(): string {}

function SDL_GetVersion(): int {}

function SDL_SetHint(string $name, string $value): bool {}

function SDL_PumpEvents(): void {}

/** A null $event passes NULL through to SDL and discards the event. */
function SDL_PollEvent(?SDL_Event $event): bool {}

/** A null $event passes NULL through to SDL and discards the event. */
function SDL_WaitEventTimeout(?SDL_Event $event, int $timeoutMS): bool {}
