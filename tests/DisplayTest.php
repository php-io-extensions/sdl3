<?php

declare(strict_types=1);

it('lists the displays with the primary among them', function (): void {
    video();
    $displays = SDL_GetDisplays();

    expect($displays)->toBeArray()->not->toBeEmpty()
        ->and($displays)->toContain(SDL_GetPrimaryDisplay())
        ->and(SDL_GetCurrentVideoDriver())->toBeIn(['cocoa', 'wayland', 'x11']);
});

it('describes a display: name, bounds, scale, orientation and properties', function (): void {
    video();
    $display = SDL_GetPrimaryDisplay();
    $bounds = new SDL_Rect();
    $usable = new SDL_Rect();
    $orientations = [SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_PORTRAIT_FLIPPED];

    expect(SDL_GetDisplayName($display))->toBeString()
        ->and(SDL_GetDisplayBounds($display, $bounds))->toBeTrue()
        ->and($bounds->w)->toBeGreaterThan(0)
        ->and(SDL_GetDisplayUsableBounds($display, $usable))->toBeTrue()
        ->and($usable->w)->toBeLessThanOrEqual($bounds->w)
        ->and($usable->h)->toBeLessThanOrEqual($bounds->h)
        ->and(SDL_GetDisplayContentScale($display))->toBeGreaterThan(0.0)
        ->and(SDL_GetNaturalDisplayOrientation($display))->toBeIn($orientations)
        ->and(SDL_GetCurrentDisplayOrientation($display))->toBeIn($orientations)
        ->and(SDL_GetDisplayProperties($display))->toBeGreaterThan(0)
        ->and(SDL_GetBooleanProperty(SDL_GetDisplayProperties($display), SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, false))->toBeBool()
        ->and(SDL_GetDisplayForPoint(new SDL_Point($bounds->x + intdiv($bounds->w, 2), $bounds->y + intdiv($bounds->h, 2))))->toBe($display)
        ->and(SDL_GetDisplayForRect(new SDL_Rect($bounds->x + 10, $bounds->y + 10, 20, 20)))->toBe($display);
});

it('copies display modes out as SDL_DisplayMode', function (): void {
    video();
    $display = SDL_GetPrimaryDisplay();
    $desktop = SDL_GetDesktopDisplayMode($display);
    $current = SDL_GetCurrentDisplayMode($display);
    $modes = SDL_GetFullscreenDisplayModes($display);

    expect($desktop)->toBeInstanceOf(SDL_DisplayMode::class)
        ->and($desktop->displayID)->toBe($display)
        ->and($desktop->w)->toBeGreaterThan(0)
        ->and($desktop->pixel_density)->toBeGreaterThan(0.0)
        ->and($desktop->format)->toBeGreaterThan(0)
        ->and($current)->toBeInstanceOf(SDL_DisplayMode::class)
        ->and($modes)->toBeArray()->not->toBeEmpty()
        ->and($modes)->each->toBeInstanceOf(SDL_DisplayMode::class);

    $closest = new SDL_DisplayMode();
    expect(SDL_GetClosestFullscreenDisplayMode($display, $modes[0]->w, $modes[0]->h, 0.0, true, $closest))->toBeTrue()
        ->and([$closest->w, $closest->h])->toBe([$modes[0]->w, $modes[0]->h])
        ->and($closest->displayID)->toBe($display);
});

it('answers null, false and 0 for a display that does not exist', function (): void {
    video();

    expect(SDL_GetDisplayName(0))->toBeNull()
        ->and(SDL_GetDesktopDisplayMode(0))->toBeNull()
        ->and(SDL_GetFullscreenDisplayModes(0))->toBeNull()
        ->and(SDL_GetDisplayBounds(0, new SDL_Rect()))->toBeFalse()
        ->and(SDL_GetClosestFullscreenDisplayMode(0, 640, 480, 0.0, false, new SDL_DisplayMode()))->toBeFalse()
        ->and(SDL_GetDisplayProperties(0))->toBe(0);
});

it('names the display a window is on', function (): void {
    $window = hiddenWindow();

    expect(SDL_GetDisplays())->toContain(SDL_GetDisplayForWindow($window));

    SDL_DestroyWindow($window);
});

it('starts SDL_Point and SDL_DisplayMode at zero and carries display events on SDL_Event', function (): void {
    $mode = new SDL_DisplayMode();
    $event = new SDL_Event();

    expect([(new SDL_Point())->x, (new SDL_Point(3, 4))->y])->toBe([0, 4])
        ->and([$mode->w, $mode->refresh_rate, $mode->refresh_rate_denominator])->toBe([0, 0.0, 0])
        ->and($event->display)->toBeInstanceOf(SDL_DisplayEvent::class)
        ->and($event->display->displayID)->toBe(0)
        ->and(SDL_EVENT_DISPLAY_FIRST)->toBeLessThanOrEqual(SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED)
        ->and(SDL_EVENT_DISPLAY_LAST)->toBeGreaterThanOrEqual(SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED);
});
