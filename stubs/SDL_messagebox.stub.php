<?php

/** @generate-class-entries */

/**
 * @var int
 * @cvalue SDL_MESSAGEBOX_ERROR
 */
const SDL_MESSAGEBOX_ERROR = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_MESSAGEBOX_WARNING
 */
const SDL_MESSAGEBOX_WARNING = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_MESSAGEBOX_INFORMATION
 */
const SDL_MESSAGEBOX_INFORMATION = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT
 */
const SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT
 */
const SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT = UNKNOWN;

/** Blocks until the dialog is dismissed. */
function SDL_ShowSimpleMessageBox(int $flags, string $title, string $message, ?SDL_Window $window): bool {}
