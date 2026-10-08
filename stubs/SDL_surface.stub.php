<?php

/** @generate-class-entries */

/**
 * An address other than 0 is trusted.
 *
 * @not-serializable
 */
final class SDL_IOStream
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): static {}
}

/**
 * An address other than 0 is trusted. A string passed to SDL_CreateSurfaceFrom()
 * is kept alive until SDL_DestroySurface().
 *
 * @not-serializable
 */
final class SDL_Surface
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): static {}

    public function flags(): int {}

    public function format(): int {}

    public function w(): int {}

    public function h(): int {}

    public function pitch(): int {}

    public function pixels(): int {}
}

/**
 * @not-serializable
 */
final class SDL_Rect
{
    public int $x = 0;

    public int $y = 0;

    public int $w = 0;

    public int $h = 0;

    public function __construct(int $x = 0, int $y = 0, int $w = 0, int $h = 0) {}
}

/**
 * @not-serializable
 */
final class SDL_Point
{
    public int $x = 0;

    public int $y = 0;

    public function __construct(int $x = 0, int $y = 0) {}
}

/**
 * @var int
 * @cvalue SDL_PIXELFORMAT_RGBA32
 */
const SDL_PIXELFORMAT_RGBA32 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_PIXELFORMAT_BGRA32
 */
const SDL_PIXELFORMAT_BGRA32 = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_SCALEMODE_NEAREST
 */
const SDL_SCALEMODE_NEAREST = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_SCALEMODE_LINEAR
 */
const SDL_SCALEMODE_LINEAR = UNKNOWN;

/** $mem other than 0 is trusted. */
function SDL_IOFromMem(int $mem, int $size): ?SDL_IOStream {}

/** $mem other than 0 is trusted. */
function SDL_IOFromConstMem(int $mem, int $size): ?SDL_IOStream {}

function SDL_ReadIO(SDL_IOStream $context, int $size): string {}

function SDL_WriteIO(SDL_IOStream $context, string $ptr, int $size): int {}

function SDL_CloseIO(SDL_IOStream $context): bool {}

function SDL_GetWindowSurface(SDL_Window $window): ?SDL_Surface {}

function SDL_UpdateWindowSurface(SDL_Window $window): bool {}

/** $rects is a list of SDL_Rect; numrects is its length. */
function SDL_UpdateWindowSurfaceRects(SDL_Window $window, array $rects): bool {}

function SDL_WindowHasSurface(SDL_Window $window): bool {}

function SDL_DestroyWindowSurface(SDL_Window $window): bool {}

function SDL_SetWindowSurfaceVSync(SDL_Window $window, int $vsync): bool {}

function SDL_GetWindowSurfaceVSync(SDL_Window $window, ?int &$vsync): bool {}

/**
 * $pixels as a string must hold $pitch × $height bytes and is kept until SDL_DestroySurface().
 * $pixels as an address: 0 is refused, any other address is trusted.
 */
function SDL_CreateSurfaceFrom(int $width, int $height, int $format, string|int $pixels, int $pitch): ?SDL_Surface {}

function SDL_DestroySurface(SDL_Surface $surface): void {}

function SDL_BlitSurface(SDL_Surface $src, ?SDL_Rect $srcrect, SDL_Surface $dst, ?SDL_Rect $dstrect): bool {}

function SDL_BlitSurfaceScaled(SDL_Surface $src, ?SDL_Rect $srcrect, SDL_Surface $dst, ?SDL_Rect $dstrect, int $scaleMode): bool {}

function SDL_FillSurfaceRect(SDL_Surface $dst, ?SDL_Rect $rect, int $color): bool {}
