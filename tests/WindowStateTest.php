<?php

declare(strict_types=1);

it('moves, sizes and bounds a window', function (): void {
    // X11 applies a size to a mapped window only, so it is shown first.
    $window = hiddenWindow(SDL_WINDOW_RESIZABLE);
    SDL_ShowWindow($window);
    SDL_SyncWindow($window);

    // Constraints first: on X11 each constraint call re-applies the size the window last committed.
    expect(SDL_SetWindowMinimumSize($window, 100, 80))->toBeTrue()
        ->and(SDL_SetWindowMaximumSize($window, 800, 600))->toBeTrue()
        ->and(SDL_SetWindowAspectRatio($window, 1.0, 2.0))->toBeTrue()
        ->and(SDL_SetWindowSize($window, 320, 200))->toBeTrue()
        ->and(SDL_SyncWindow($window))->toBeBool()
        ->and(SDL_GetWindowSize($window, $w, $h))->toBeTrue()
        ->and([$w, $h])->toBe([320, 200])
        ->and(SDL_GetWindowMinimumSize($window, $minW, $minH))->toBeTrue()
        ->and([$minW, $minH])->toBe([100, 80])
        ->and(SDL_GetWindowMaximumSize($window, $maxW, $maxH))->toBeTrue()
        ->and([$maxW, $maxH])->toBe([800, 600])
        ->and(SDL_GetWindowAspectRatio($window, $minA, $maxA))->toBeTrue()
        ->and([$minA, $maxA])->toBe([1.0, 2.0]);

    SDL_DestroyWindow($window);
});

it('places a window where the compositor allows it', function (): void {
    $window = hiddenWindow();

    if (driver() === 'wayland') {
        // xdg-shell toplevels have no global position.
        expect(SDL_SetWindowPosition($window, 40, 60))->toBeFalse()
            ->and(SDL_GetError())->toBe('wayland cannot position non-popup windows');
    } else {
        expect(SDL_SetWindowPosition($window, 40, 60))->toBeTrue()
            ->and(SDL_SyncWindow($window))->toBeBool()
            ->and(SDL_GetWindowPosition($window, $x, $y))->toBeTrue()
            ->and([$x, $y])->toBe([40, 60]);
    }

    SDL_DestroyWindow($window);
});

it('toggles a window\'s border, resizing, stacking and focus flags', function (): void {
    $window = hiddenWindow();

    expect(SDL_SetWindowBordered($window, false))->toBeTrue()
        ->and(SDL_GetWindowFlags($window) & SDL_WINDOW_BORDERLESS)->toBe(SDL_WINDOW_BORDERLESS)
        ->and(SDL_SetWindowBordered($window, true))->toBeTrue()
        ->and(SDL_GetWindowFlags($window) & SDL_WINDOW_BORDERLESS)->toBe(0)
        ->and(SDL_SetWindowResizable($window, true))->toBeTrue()
        ->and(SDL_GetWindowFlags($window) & SDL_WINDOW_RESIZABLE)->toBe(SDL_WINDOW_RESIZABLE)
        ->and(SDL_SetWindowAlwaysOnTop($window, true))->toBeTrue()
        ->and(SDL_SetWindowFocusable($window, false))->toBeTrue();

    // xdg-shell has no stacking or focus refusal after creation: SDL accepts both calls and leaves the flags clear.
    $stacked = driver() === 'wayland' ? 0 : SDL_WINDOW_ALWAYS_ON_TOP;
    $unfocusable = driver() === 'wayland' ? 0 : SDL_WINDOW_NOT_FOCUSABLE;
    expect(SDL_GetWindowFlags($window) & SDL_WINDOW_ALWAYS_ON_TOP)->toBe($stacked)
        ->and(SDL_GetWindowFlags($window) & SDL_WINDOW_NOT_FOCUSABLE)->toBe($unfocusable)
        ->and(SDL_SetWindowFocusable($window, true))->toBeTrue()
        ->and(SDL_GetWindowFlags($window) & SDL_WINDOW_NOT_FOCUSABLE)->toBe(0);

    SDL_DestroyWindow($window);
});

it('creates a window from the full set of creation properties', function (): void {
    video();
    $props = SDL_CreateProperties();
    SDL_SetStringProperty($props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, 'props');
    SDL_SetNumberProperty($props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_CENTERED);
    SDL_SetNumberProperty($props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_CENTERED);
    SDL_SetNumberProperty($props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 200);
    SDL_SetNumberProperty($props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 120);
    SDL_SetBooleanProperty($props, SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN, true);
    SDL_SetBooleanProperty($props, SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN, true);
    SDL_SetBooleanProperty($props, SDL_PROP_WINDOW_CREATE_ALWAYS_ON_TOP_BOOLEAN, true);
    SDL_SetBooleanProperty($props, SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN, false);
    SDL_SetBooleanProperty($props, SDL_PROP_WINDOW_CREATE_TRANSPARENT_BOOLEAN, true);

    $window = SDL_CreateWindowWithProperties($props);
    $flags = SDL_GetWindowFlags($window);
    $want = SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_TRANSPARENT;

    expect($flags & $want)->toBe($want)
        ->and(SDL_WINDOWPOS_CENTERED & SDL_WINDOWPOS_CENTERED_MASK)->toBe(SDL_WINDOWPOS_CENTERED_MASK)
        ->and(SDL_WINDOWPOS_UNDEFINED & SDL_WINDOWPOS_UNDEFINED_MASK)->toBe(SDL_WINDOWPOS_UNDEFINED_MASK);

    SDL_DestroyWindow($window);
    SDL_DestroyProperties($props);
});

it('reads the safe area and border sizes of a shown window', function (): void {
    $window = hiddenWindow();
    SDL_ShowWindow($window);
    SDL_SyncWindow($window);
    $area = new SDL_Rect();

    expect(SDL_GetWindowSafeArea($window, $area))->toBeTrue()
        ->and([$area->w, $area->h])->toBe([160, 120]);

    SDL_ClearError();
    $borders = SDL_GetWindowBordersSize($window, $top, $left, $bottom, $right);
    if (driver() === 'x11') {
        expect($borders)->toBeTrue()->and($top)->toBeGreaterThanOrEqual(0);
    } else {
        // SDL's Cocoa and Wayland drivers have no borders query.
        expect($borders)->toBeFalse()->and(SDL_GetError())->toBe('That operation is not supported');
    }

    SDL_DestroyWindow($window);
});

it('maximizes, minimizes and restores a shown window, with the matching events', function (): void {
    $window = hiddenWindow(SDL_WINDOW_RESIZABLE);
    SDL_ShowWindow($window);
    SDL_SyncWindow($window);
    pumpEvents();

    expect(SDL_MaximizeWindow($window))->toBeTrue()
        ->and(SDL_SyncWindow($window))->toBeBool()
        ->and(pumpEvents(fn (SDL_Event $e): bool => $e->type === SDL_EVENT_WINDOW_MAXIMIZED, 3.0))->toContain(SDL_EVENT_WINDOW_MAXIMIZED)
        ->and(SDL_GetWindowFlags($window) & SDL_WINDOW_MAXIMIZED)->toBe(SDL_WINDOW_MAXIMIZED)
        ->and(SDL_RestoreWindow($window))->toBeTrue()
        ->and(SDL_SyncWindow($window))->toBeBool()
        ->and(pumpEvents(fn (SDL_Event $e): bool => $e->type === SDL_EVENT_WINDOW_RESTORED, 3.0))->toContain(SDL_EVENT_WINDOW_RESTORED)
        ->and(SDL_GetWindowFlags($window) & SDL_WINDOW_MAXIMIZED)->toBe(0);

    expect(SDL_MinimizeWindow($window))->toBeTrue()
        ->and(SDL_SyncWindow($window))->toBeBool();
    if (driver() !== 'wayland') {
        // xdg-shell has no minimized state to report back, so only X11 and Cocoa confirm it.
        expect(pumpEvents(fn (SDL_Event $e): bool => $e->type === SDL_EVENT_WINDOW_MINIMIZED, 3.0))->toContain(SDL_EVENT_WINDOW_MINIMIZED)
            ->and(SDL_GetWindowFlags($window) & SDL_WINDOW_MINIMIZED)->toBe(SDL_WINDOW_MINIMIZED);
    }
    expect(SDL_RestoreWindow($window))->toBeTrue();

    SDL_DestroyWindow($window);
});

it('sets opacity, flashes and takes an icon', function (): void {
    $window = hiddenWindow();
    $icon = SDL_CreateSurfaceFrom(16, 16, SDL_PIXELFORMAT_RGBA32, str_repeat("\xff\x80\x00\xff", 256), 64);

    expect(SDL_SetWindowIcon($window, $icon))->toBeTrue(SDL_GetError())
        ->and(SDL_FlashWindow($window, SDL_FLASH_BRIEFLY))->toBeTrue(SDL_GetError())
        ->and(SDL_FlashWindow($window, SDL_FLASH_CANCEL))->toBeTrue();

    expect(SDL_SetWindowOpacity($window, 0.5))->toBeTrue()
        ->and(SDL_GetWindowOpacity($window))->toBe(0.5);

    SDL_DestroySurface($icon);
    SDL_DestroyWindow($window);
});

it('hands out the native handles other extensions take', function (): void {
    $window = hiddenWindow();
    $props = SDL_GetWindowProperties($window);

    match (driver()) {
        'cocoa' => expect(SDL_GetPointerProperty($props, SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, null))->toBeInt()->toBeGreaterThan(0),
        'wayland' => expect(SDL_GetPointerProperty($props, SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, null))->toBeInt()
            ->and(SDL_GetPointerProperty($props, SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, null))->toBeInt(),
        'x11' => expect(SDL_GetPointerProperty($props, SDL_PROP_WINDOW_X11_DISPLAY_POINTER, null))->toBeInt()
            ->and(SDL_GetNumberProperty($props, SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0))->toBeGreaterThan(0),
    };

    expect(SDL_GetBooleanProperty($props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, false))->toBeBool()
        ->and(SDL_GetFloatProperty($props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, 1.0))->toBeGreaterThan(0.0)
        ->and(SDL_GetFloatProperty($props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, 1.0))->toBeGreaterThan(0.0);

    SDL_DestroyWindow($window);
});

it('stores and reads float, string and boolean properties', function (): void {
    $props = SDL_CreateProperties();

    expect(SDL_SetFloatProperty($props, 'f', 0.25))->toBeTrue()
        ->and(SDL_GetFloatProperty($props, 'f', 0.0))->toBe(0.25)
        ->and(SDL_GetFloatProperty($props, 'missing', 2.5))->toBe(2.5)
        ->and(SDL_SetStringProperty($props, 's', 'value'))->toBeTrue()
        ->and(SDL_GetStringProperty($props, 's', null))->toBe('value')
        ->and(SDL_GetStringProperty($props, 'missing', null))->toBeNull()
        ->and(SDL_GetStringProperty($props, 'missing', 'fallback'))->toBe('fallback')
        ->and(SDL_SetBooleanProperty($props, 'b', true))->toBeTrue()
        ->and(SDL_GetBooleanProperty($props, 'b', false))->toBeTrue()
        ->and(SDL_GetBooleanProperty($props, 'missing', true))->toBeTrue();

    SDL_DestroyProperties($props);
});

it('turns the screen saver off and back on', function (): void {
    video();
    $was = SDL_ScreenSaverEnabled();

    expect(SDL_DisableScreenSaver())->toBeTrue()
        ->and(SDL_ScreenSaverEnabled())->toBeFalse()
        ->and(SDL_EnableScreenSaver())->toBeTrue()
        ->and(SDL_ScreenSaverEnabled())->toBeTrue();

    $was ? SDL_EnableScreenSaver() : SDL_DisableScreenSaver();
});

it('refuses a destroyed window in the new window calls', function (): void {
    $window = hiddenWindow();
    SDL_DestroyWindow($window);

    expect(fn () => SDL_MaximizeWindow($window))->toThrow(ValueError::class, 'SDL_Window has been destroyed')
        ->and(fn () => SDL_SetWindowBordered($window, true))->toThrow(ValueError::class)
        ->and(fn () => SDL_SetWindowPosition($window, 0, 0))->toThrow(ValueError::class)
        ->and(fn () => SDL_GetWindowMinimumSize($window, $w, $h))->toThrow(ValueError::class)
        ->and(fn () => SDL_GetWindowSafeArea($window, new SDL_Rect()))->toThrow(ValueError::class)
        ->and(fn () => SDL_SetWindowHitTest($window, fn () => SDL_HITTEST_NORMAL))->toThrow(ValueError::class);
});
