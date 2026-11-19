<?php

declare(strict_types=1);

/** The 4 bytes of the RGBA32 pixel at (x, y), as hex. */
function clipPixel(SDL_Surface $surface, int $x, int $y): string
{
    $io = SDL_IOFromConstMem($surface->pixels() + $y * $surface->pitch() + $x * 4, 4);
    $bytes = readIO($io, 4);
    SDL_CloseIO($io);

    return bin2hex($bytes);
}

it('clips a null-rect fill to the clip rect', function (): void {
    $surface = SDL_CreateSurface(4, 4, SDL_PIXELFORMAT_RGBA32);
    expect(SDL_SetSurfaceClipRect($surface, new SDL_Rect(1, 1, 2, 2)))->toBeTrue()
        ->and(SDL_FillSurfaceRect($surface, null, 0xFF0000FF))->toBeTrue();

    expect(clipPixel($surface, 0, 0))->toBe('00000000')
        ->and(clipPixel($surface, 3, 3))->toBe('00000000')
        ->and(clipPixel($surface, 1, 1))->not->toBe('00000000')
        ->and(clipPixel($surface, 2, 2))->not->toBe('00000000');

    SDL_DestroySurface($surface);
});

it('restores full-surface fills when the clip rect is null', function (): void {
    $surface = SDL_CreateSurface(4, 4, SDL_PIXELFORMAT_RGBA32);
    SDL_SetSurfaceClipRect($surface, new SDL_Rect(1, 1, 2, 2));
    expect(SDL_SetSurfaceClipRect($surface, null))->toBeTrue()
        ->and(SDL_FillSurfaceRect($surface, null, 0xFF0000FF))->toBeTrue();

    expect(clipPixel($surface, 0, 0))->not->toBe('00000000')
        ->and(clipPixel($surface, 3, 3))->not->toBe('00000000');

    SDL_DestroySurface($surface);
});

it('reports the stored clip rect, and the whole surface after null', function (): void {
    $surface = SDL_CreateSurface(4, 3, SDL_PIXELFORMAT_RGBA32);
    $rect = new SDL_Rect();
    SDL_SetSurfaceClipRect($surface, new SDL_Rect(1, 1, 2, 1));
    expect(SDL_GetSurfaceClipRect($surface, $rect))->toBeTrue()
        ->and([$rect->x, $rect->y, $rect->w, $rect->h])->toBe([1, 1, 2, 1]);

    SDL_SetSurfaceClipRect($surface, null);
    expect(SDL_GetSurfaceClipRect($surface, $rect))->toBeTrue()
        ->and([$rect->x, $rect->y, $rect->w, $rect->h])->toBe([0, 0, 4, 3]);

    SDL_DestroySurface($surface);
});
