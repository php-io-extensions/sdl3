<?php

declare(strict_types=1);

it('creates a hidden window and reads it back', function (): void {
    $window = hiddenWindow();

    expect(SDL_GetWindowTitle($window))->toBe('ext-sdl3 test')
        ->and(SDL_GetWindowFlags($window) & SDL_WINDOW_HIDDEN)->toBe(SDL_WINDOW_HIDDEN)
        ->and(SDL_GetWindowFromID(SDL_GetWindowID($window)))->toBe($window)
        ->and(SDL_SetWindowTitle($window, 'renamed'))->toBeTrue()
        ->and(SDL_GetWindowTitle($window))->toBe('renamed');

    SDL_DestroyWindow($window);
});

it('reports its size in points and in pixels through out-parameters', function (): void {
    $window = hiddenWindow(SDL_WINDOW_HIGH_PIXEL_DENSITY);

    expect(SDL_GetWindowSize($window, $w, $h))->toBeTrue()
        ->and([$w, $h])->toBe([160, 120])
        ->and(SDL_GetWindowSizeInPixels($window, $pw, $ph))->toBeTrue()
        ->and($pw)->toBe((int) round($w * SDL_GetWindowPixelDensity($window)))
        ->and(SDL_GetWindowDisplayScale($window))->toBeGreaterThan(0.0);

    SDL_DestroyWindow($window);
});

it('creates a window from properties', function (): void {
    video();
    $props = SDL_CreateProperties();
    SDL_SetStringProperty($props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, 'from properties');
    SDL_SetNumberProperty($props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 200);
    SDL_SetNumberProperty($props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 100);
    SDL_SetBooleanProperty($props, SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN, true);
    SDL_SetPointerProperty($props, 'ext-sdl3.test.pointer', 0x1000);

    $window = SDL_CreateWindowWithProperties($props);

    expect(SDL_GetWindowTitle($window))->toBe('from properties')
        ->and(SDL_GetNumberProperty($props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 0))->toBe(200)
        ->and(SDL_GetPointerProperty($props, 'ext-sdl3.test.pointer', null))->toBe(0x1000)
        ->and(SDL_GetPointerProperty($props, 'missing', null))->toBeNull()
        ->and(SDL_GetWindowProperties($window))->toBeGreaterThan(0);

    SDL_DestroyWindow($window);
    SDL_DestroyProperties($props);
});

it('refuses a destroyed window, and hands a new one at a reused address a fresh object', function (): void {
    $window = hiddenWindow();
    $address = $window->pointer();
    SDL_DestroyWindow($window);

    expect(fn () => SDL_GetWindowTitle($window))->toThrow(ValueError::class, 'SDL_Window has been destroyed')
        ->and(fn () => SDL_DestroyWindow($window))->toThrow(ValueError::class)
        ->and(fn () => $window->pointer())->toThrow(ValueError::class);

    $next = hiddenWindow();
    expect($next)->not->toBe($window);
    SDL_DestroyWindow($next);
});

it('shows, raises and hides', function (): void {
    $window = hiddenWindow();

    expect(SDL_ShowWindow($window))->toBeTrue()
        ->and(SDL_RaiseWindow($window))->toBeBool()
        ->and(SDL_HideWindow($window))->toBeTrue();

    SDL_DestroyWindow($window);
});
