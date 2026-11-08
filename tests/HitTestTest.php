<?php

declare(strict_types=1);

it('sets, replaces and clears a hit test', function (): void {
    $window = hiddenWindow();

    expect(SDL_SetWindowHitTest($window, fn (): int => SDL_HITTEST_NORMAL))->toBeTrue()
        ->and(SDL_SetWindowHitTest($window, fn (): int => SDL_HITTEST_DRAGGABLE))->toBeTrue()
        ->and(SDL_SetWindowHitTest($window, null))->toBeTrue()
        ->and(fn () => SDL_SetWindowHitTest($window, 'no_such_function'))->toThrow(TypeError::class);

    SDL_DestroyWindow($window);
});

it('drops a hit test with its window', function (): void {
    $window = hiddenWindow();
    $held = new stdClass();
    $ref = WeakReference::create($held);
    // The closure's capture is the data it carries.
    SDL_SetWindowHitTest($window, function () use ($held): int {
        return SDL_HITTEST_NORMAL;
    });
    unset($held);

    // Booleans only: an expectation holding the object would keep it alive.
    $heldBefore = $ref->get() !== null;
    SDL_DestroyWindow($window);

    expect($heldBefore)->toBeTrue()->and($ref->get() === null)->toBeTrue();
});

it('calls the PHP hit test on a click and uses what it returns', function (): void {
    // An inactive window spends the first click on activation unless click-through is on.
    SDL_SetHint('SDL_MOUSE_FOCUS_CLICKTHROUGH', '1');
    $window = hiddenWindow();
    SDL_ShowWindow($window);
    SDL_SyncWindow($window);
    pumpEvents();
    $calls = [];
    $armed = false;
    // Only the synthesized click counts: the real cursor passing over the window calls the hit test too.
    $data = 'title bar';
    SDL_SetWindowHitTest($window, function (SDL_Window $win, SDL_Point $area) use (&$calls, &$armed, $data): int {
        if (! $armed) {
            return SDL_HITTEST_NORMAL;
        }
        $calls[] = [$win, $area->x, $area->y, $data];

        return SDL_HITTEST_DRAGGABLE;
    });
    try {
        $nswindow = nsWindowOf($window);
        $number = $nswindow->windowNumber();
        $event = fn (NSEventType $type): NSEvent => NSEvent::mouseEventWithTypeLocationModifierFlagsTimestampWindowNumberContextEventNumberClickCountPressure(
            $type, new NSPoint(80.0, 100.0), 0, 0.0, $number, null, 0, 1, 1.0);
        // The mouse-up waits in the queue so a drag NSWindow starts on the mouse-down ends at once.
        NSApplication::sharedApplication()->postEventAtStart($event(NSEventType::LEFT_MOUSE_UP), false);
        $armed = true;
        // (the application hands a mouse event to the window its number names, as the window's own sendEvent: would take it)
        NSApplication::sharedApplication()->sendEvent($event(NSEventType::LEFT_MOUSE_DOWN));
        $armed = false;

        expect($calls)->not->toBeEmpty()
            ->and($calls[0][0])->toBe($window)
            ->and($calls[0][1])->toBe(80)
            ->and($calls[0][3])->toBe('title bar')
            ->and(pumpEvents(fn (SDL_Event $e): bool => $e->type === SDL_EVENT_WINDOW_HIT_TEST))->toContain(SDL_EVENT_WINDOW_HIT_TEST);
    } finally {
        SDL_DestroyWindow($window);
    }
})->skip(PHP_OS_FAMILY !== 'Darwin' || ! extension_loaded('appkit'), 'the click is synthesized through ext-appkit');

it('treats a throwing or non-int hit test as SDL_HITTEST_NORMAL and surfaces the error', function (): void {
    // An inactive window spends the first click on activation unless click-through is on.
    SDL_SetHint('SDL_MOUSE_FOCUS_CLICKTHROUGH', '1');
    $window = hiddenWindow();
    SDL_ShowWindow($window);
    SDL_SyncWindow($window);
    $armed = false;
    // Wrong only for the synthesized click: the real cursor passing over the window calls the hit test too.
    SDL_SetWindowHitTest($window, function () use (&$armed): int|string {
        return $armed ? 'not an int' : SDL_HITTEST_NORMAL;
    });
    try {
        $number = nsWindowOf($window)->windowNumber();
        $down = NSEvent::mouseEventWithTypeLocationModifierFlagsTimestampWindowNumberContextEventNumberClickCountPressure(
            NSEventType::LEFT_MOUSE_DOWN, new NSPoint(10.0, 10.0), 0, 0.0, $number, null, 0, 1, 1.0);

        $send = function () use ($down, &$armed): void {
            $armed = true;
            try {
                NSApplication::sharedApplication()->sendEvent($down);
            } finally {
                $armed = false;
            }
        };
        expect($send)->toThrow(TypeError::class, 'must return int, string returned');
        pumpEvents();
    } finally {
        SDL_DestroyWindow($window);
    }
})->skip(PHP_OS_FAMILY !== 'Darwin' || ! extension_loaded('appkit'), 'the click is synthesized through ext-appkit');
