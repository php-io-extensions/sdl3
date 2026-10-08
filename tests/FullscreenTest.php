<?php

declare(strict_types=1);

it('holds borderless and exclusive fullscreen modes on a hidden window', function (): void {
    $window = hiddenWindow();
    $display = SDL_GetDisplayForWindow($window);
    $mode = SDL_GetFullscreenDisplayModes($display)[0];

    expect(SDL_SetWindowFullscreenMode($window, null))->toBeTrue()
        ->and(SDL_GetWindowFullscreenMode($window))->toBeNull()
        ->and(SDL_SetWindowFullscreenMode($window, $mode))->toBeTrue(SDL_GetError());

    $held = SDL_GetWindowFullscreenMode($window);
    expect($held)->toBeInstanceOf(SDL_DisplayMode::class)
        ->and([$held->w, $held->h, $held->refresh_rate])->toBe([$mode->w, $mode->h, $mode->refresh_rate]);

    $bogus = new SDL_DisplayMode();
    $bogus->displayID = $display;
    $bogus->w = 7;
    $bogus->h = 3;
    expect(SDL_SetWindowFullscreenMode($window, $bogus))->toBeFalse()
        ->and(SDL_SetWindowFullscreenMode($window, null))->toBeTrue();

    SDL_DestroyWindow($window);
});

it('enters and leaves borderless fullscreen desktop on a shown window', function (): void {
    $window = hiddenWindow(SDL_WINDOW_RESIZABLE);
    SDL_ShowWindow($window);
    SDL_SyncWindow($window);
    pumpEvents();

    // The transition is animated (a Space of its own on the Mac by default); wait on its events.
    expect(SDL_SetWindowFullscreenMode($window, null))->toBeTrue()
        ->and(SDL_SetWindowFullscreen($window, true))->toBeTrue()
        ->and(SDL_SyncWindow($window))->toBeBool()
        ->and(pumpEvents(fn (SDL_Event $e): bool => $e->type === SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 5.0))->toContain(SDL_EVENT_WINDOW_ENTER_FULLSCREEN)
        ->and(SDL_GetWindowFlags($window) & SDL_WINDOW_FULLSCREEN)->toBe(SDL_WINDOW_FULLSCREEN)
        ->and(SDL_SetWindowFullscreen($window, false))->toBeTrue()
        ->and(SDL_SyncWindow($window))->toBeBool()
        ->and(pumpEvents(fn (SDL_Event $e): bool => $e->type === SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 5.0))->toContain(SDL_EVENT_WINDOW_LEAVE_FULLSCREEN)
        ->and(SDL_GetWindowFlags($window) & SDL_WINDOW_FULLSCREEN)->toBe(0);

    SDL_DestroyWindow($window);
});

it('switches the display mode for exclusive fullscreen and reports it as a display event', function (): void {
    if (driver() === 'wayland') {
        $this->markTestSkipped('Wayland emulates exclusive modes by scaling; the next test covers it');
    }

    $window = hiddenWindow();
    $display = SDL_GetDisplayForWindow($window);
    $desktop = SDL_GetDesktopDisplayMode($display);
    $other = null;
    foreach (SDL_GetFullscreenDisplayModes($display) as $mode) {
        if ($mode->w !== $desktop->w || $mode->h !== $desktop->h) {
            $other = $mode;
            break;
        }
    }
    expect($other)->not->toBeNull('the display offers only its desktop size');

    SDL_ShowWindow($window);
    SDL_SyncWindow($window);
    pumpEvents();
    $displayEvent = null;
    $catch = function (SDL_Event $e) use (&$displayEvent, $display): bool {
        if ($e->type === SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED && $e->display->displayID === $display) {
            $displayEvent = [$e->display->type, $e->display->displayID];
        }

        return $displayEvent !== null;
    };

    expect(SDL_SetWindowFullscreenMode($window, $other))->toBeTrue(SDL_GetError())
        ->and(SDL_SetWindowFullscreen($window, true))->toBeTrue()
        ->and(SDL_SyncWindow($window))->toBeBool();
    pumpEvents($catch, 5.0);
    $current = SDL_GetCurrentDisplayMode($display);

    expect($displayEvent)->toBe([SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, $display])
        ->and([$current->w, $current->h])->toBe([$other->w, $other->h]);

    expect(SDL_SetWindowFullscreen($window, false))->toBeTrue()
        ->and(SDL_SyncWindow($window))->toBeBool();
    pumpEvents(fn (SDL_Event $e): bool => SDL_GetCurrentDisplayMode($display)->w === $desktop->w
        && (SDL_GetWindowFlags($window) & SDL_WINDOW_FULLSCREEN) === 0, 5.0);
    $back = SDL_GetCurrentDisplayMode($display);

    expect([$back->w, $back->h])->toBe([$desktop->w, $desktop->h]);

    SDL_DestroyWindow($window);
});

it('emulates an exclusive mode on Wayland by sizing the window to it, leaving the display alone', function (): void {
    $window = hiddenWindow();
    $display = SDL_GetDisplayForWindow($window);
    $desktop = SDL_GetDesktopDisplayMode($display);
    $other = null;
    foreach (SDL_GetFullscreenDisplayModes($display) as $mode) {
        if ($mode->w !== $desktop->w || $mode->h !== $desktop->h) {
            $other = $mode;
            break;
        }
    }
    SDL_ShowWindow($window);
    SDL_SyncWindow($window);
    pumpEvents();

    expect(SDL_SetWindowFullscreenMode($window, $other))->toBeTrue(SDL_GetError())
        ->and(SDL_SetWindowFullscreen($window, true))->toBeTrue()
        ->and(SDL_SyncWindow($window))->toBeBool()
        ->and(pumpEvents(fn (SDL_Event $e): bool => $e->type === SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 5.0))->toContain(SDL_EVENT_WINDOW_ENTER_FULLSCREEN)
        ->and(SDL_GetWindowSizeInPixels($window, $pw, $ph))->toBeTrue()
        ->and([$pw, $ph])->toBe([$other->w, $other->h])
        ->and([SDL_GetCurrentDisplayMode($display)->w, SDL_GetCurrentDisplayMode($display)->h])->toBe([$desktop->w, $desktop->h]);

    SDL_SetWindowFullscreen($window, false);
    pumpEvents(fn (SDL_Event $e): bool => $e->type === SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 5.0);
    SDL_DestroyWindow($window);
})->skip(fn (): bool => driver() !== 'wayland', 'only Wayland emulates exclusive modes');
