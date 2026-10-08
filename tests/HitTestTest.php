<?php

declare(strict_types=1);

it('sets, replaces and clears a hit test', function (): void {
    $window = hiddenWindow();

    expect(SDL_SetWindowHitTest($window, fn (): int => SDL_HITTEST_NORMAL))->toBeTrue()
        ->and(SDL_SetWindowHitTest($window, fn (): int => SDL_HITTEST_DRAGGABLE, ['data']))->toBeTrue()
        ->and(SDL_SetWindowHitTest($window, null))->toBeTrue()
        ->and(fn () => SDL_SetWindowHitTest($window, 'no_such_function'))->toThrow(TypeError::class);

    SDL_DestroyWindow($window);
});

it('drops a hit test with its window', function (): void {
    $window = hiddenWindow();
    $held = new stdClass();
    $ref = WeakReference::create($held);
    SDL_SetWindowHitTest($window, fn (): int => SDL_HITTEST_NORMAL, $held);
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
    SDL_SetWindowHitTest($window, function (SDL_Window $win, SDL_Point $area, mixed $data) use (&$calls, &$armed): int {
        if (! $armed) {
            return SDL_HITTEST_NORMAL;
        }
        $calls[] = [$win, $area->x, $area->y, $data];

        return SDL_HITTEST_DRAGGABLE;
    }, 'title bar');
    try {
        $nswindow = nsWindowOf($window);
        $number = objcMsg('long objc_msgSend(id, SEL)')->objc_msgSend($nswindow, sel('windowNumber'));
        $mouse = objcMsg('id objc_msgSend(id, SEL, unsigned long, NSPoint, unsigned long, double, long, id, long, long, float)');
        $event = function (int $type) use ($mouse, $number): FFI\CData {
            $point = $mouse->new('NSPoint');
            $point->x = 80.0;
            $point->y = 100.0;

            return $mouse->objc_msgSend(objc()->objc_getClass('NSEvent'), sel('mouseEventWithType:location:modifierFlags:timestamp:windowNumber:context:eventNumber:clickCount:pressure:'),
                $type, $point, 0, 0.0, $number, null, 0, 1, 1.0);
        };
        // The mouse-up waits in the queue so a drag NSWindow starts on the mouse-down ends at once.
        objcMsg('void objc_msgSend(id, SEL, id, signed char)')->objc_msgSend(nsApp(), sel('postEvent:atStart:'), $event(2), 0);
        $armed = true;
        objcMsg('void objc_msgSend(id, SEL, id)')->objc_msgSend($nswindow, sel('sendEvent:'), $event(1));
        $armed = false;

        expect($calls)->not->toBeEmpty()
            ->and($calls[0][0])->toBe($window)
            ->and($calls[0][1])->toBe(80)
            ->and($calls[0][3])->toBe('title bar')
            ->and(pumpEvents(fn (SDL_Event $e): bool => $e->type === SDL_EVENT_WINDOW_HIT_TEST))->toContain(SDL_EVENT_WINDOW_HIT_TEST);
    } finally {
        SDL_DestroyWindow($window);
    }
})->skip(PHP_OS_FAMILY !== 'Darwin', 'the click is synthesized through AppKit');

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
        $nswindow = nsWindowOf($window);
        $number = objcMsg('long objc_msgSend(id, SEL)')->objc_msgSend($nswindow, sel('windowNumber'));
        $mouse = objcMsg('id objc_msgSend(id, SEL, unsigned long, NSPoint, unsigned long, double, long, id, long, long, float)');
        $point = $mouse->new('NSPoint');
        $point->x = 10.0;
        $point->y = 10.0;
        $down = $mouse->objc_msgSend(objc()->objc_getClass('NSEvent'), sel('mouseEventWithType:location:modifierFlags:timestamp:windowNumber:context:eventNumber:clickCount:pressure:'),
            1, $point, 0, 0.0, $number, null, 0, 1, 1.0);

        $send = function () use ($nswindow, $down, &$armed): void {
            $armed = true;
            try {
                objcMsg('void objc_msgSend(id, SEL, id)')->objc_msgSend($nswindow, sel('sendEvent:'), $down);
            } finally {
                $armed = false;
            }
        };
        expect($send)->toThrow(TypeError::class, 'must return int, string returned');
        pumpEvents();
    } finally {
        SDL_DestroyWindow($window);
    }
})->skip(PHP_OS_FAMILY !== 'Darwin', 'the click is synthesized through AppKit');
