<?php

declare(strict_types=1);

/** Empties SDL's queue: a null SDL_PollEvent only peeks. */
function drainEvents(): void
{
    $sink = new SDL_Event();
    while (SDL_PollEvent($sink)) {
    }
}

/** Pushes $event, then polls until SDL hands back an event of its type: that copy. */
function roundTrip(SDL_Event $event): SDL_Event
{
    video();
    SDL_PumpEvents();
    drainEvents();

    expect(SDL_PushEvent($event))->toBeTrue();

    $back = new SDL_Event();
    while (SDL_PollEvent($back)) {
        if ($back->type === $event->type) {
            return $back;
        }
    }

    throw new RuntimeException("SDL handed back no event of type {$event->type}.");
}

it('carries a key event both ways', function (): void {
    $event = new SDL_Event();
    $event->type = SDL_EVENT_KEY_DOWN;
    $event->key->windowID = 7;
    $event->key->which = 3;
    $event->key->scancode = 26;
    $event->key->key = 119;
    $event->key->mod = SDL_KMOD_LSHIFT;
    $event->key->raw = 13;
    $event->key->down = true;
    $event->key->repeat = true;

    $back = roundTrip($event);

    expect([$back->key->type, $back->key->windowID, $back->key->which, $back->key->scancode, $back->key->key, $back->key->mod, $back->key->raw, $back->key->down, $back->key->repeat])
        ->toBe([SDL_EVENT_KEY_DOWN, 7, 3, 26, 119, SDL_KMOD_LSHIFT, 13, true, true])
        ->and($back->key->timestamp)->toBeGreaterThan(0);
});

it('keeps a pushed text event\'s bytes until it is polled', function (): void {
    $event = new SDL_Event();
    $event->type = SDL_EVENT_TEXT_INPUT;
    $event->text->windowID = 9;
    $event->text->text = 'héllo '.str_repeat('x', 64);
    video();
    SDL_PumpEvents();
    drainEvents();
    SDL_PushEvent($event);
    // The PHP string the binding read is gone; SDL holds the binding's copy.
    $event->text->text = 'clobbered';
    unset($event);
    gc_collect_cycles();

    $back = new SDL_Event();
    $text = null;
    while (SDL_PollEvent($back)) {
        if ($back->type === SDL_EVENT_TEXT_INPUT) {
            $text = [$back->text->windowID, $back->text->text];
        }
    }

    expect($text)->toBe([9, 'héllo '.str_repeat('x', 64)]);
});

it('carries mouse motion, buttons and the wheel both ways', function (): void {
    $motion = new SDL_Event();
    $motion->type = SDL_EVENT_MOUSE_MOTION;
    $motion->motion->windowID = 4;
    $motion->motion->which = 2;
    $motion->motion->state = 1;
    $motion->motion->x = 10.5;
    $motion->motion->y = 20.25;
    $motion->motion->xrel = -3.0;
    $motion->motion->yrel = 1.5;

    $button = new SDL_Event();
    $button->type = SDL_EVENT_MOUSE_BUTTON_UP;
    $button->button->windowID = 4;
    $button->button->button = SDL_BUTTON_X2;
    $button->button->down = false;
    $button->button->clicks = 2;
    $button->button->x = 1.0;
    $button->button->y = 2.0;

    $wheel = new SDL_Event();
    $wheel->type = SDL_EVENT_MOUSE_WHEEL;
    $wheel->wheel->windowID = 4;
    $wheel->wheel->x = 0.5;
    $wheel->wheel->y = -2.0;
    $wheel->wheel->direction = SDL_MOUSEWHEEL_FLIPPED;
    $wheel->wheel->mouse_x = 30.0;
    $wheel->wheel->mouse_y = 40.0;

    $m = roundTrip($motion)->motion;
    $b = roundTrip($button)->button;
    $w = roundTrip($wheel)->wheel;

    expect([$m->windowID, $m->which, $m->state, $m->x, $m->y, $m->xrel, $m->yrel])->toBe([4, 2, 1, 10.5, 20.25, -3.0, 1.5])
        ->and([$b->type, $b->button, $b->down, $b->clicks, $b->x, $b->y])->toBe([SDL_EVENT_MOUSE_BUTTON_UP, SDL_BUTTON_X2, false, 2, 1.0, 2.0])
        ->and([$w->x, $w->y, $w->direction, $w->mouse_x, $w->mouse_y])->toBe([0.5, -2.0, SDL_MOUSEWHEEL_FLIPPED, 30.0, 40.0]);
});

it('writes only the part its event type names, so one event can be reused', function (): void {
    $event = new SDL_Event();
    $event->type = SDL_EVENT_KEY_DOWN;
    $event->key->scancode = 4;
    $back = roundTrip($event);

    $next = new SDL_Event();
    $next->type = SDL_EVENT_MOUSE_MOTION;
    $next->motion->x = 5.0;
    video();
    SDL_PumpEvents();
    drainEvents();
    SDL_PushEvent($next);
    while (SDL_PollEvent($back) && $back->type !== SDL_EVENT_MOUSE_MOTION) {
    }

    expect([$back->type, $back->motion->x, $back->key->scancode])->toBe([SDL_EVENT_MOUSE_MOTION, 5.0, 4]);
});

it('carries a window event and a type with no part', function (): void {
    $window = new SDL_Event();
    $window->type = SDL_EVENT_WINDOW_MOUSE_LEAVE;
    $window->window->windowID = 12;

    $quit = new SDL_Event();
    $quit->type = SDL_EVENT_QUIT;

    expect(roundTrip($window)->window->windowID)->toBe(12)
        ->and(roundTrip($quit)->type)->toBe(SDL_EVENT_QUIT);
});

it('switches event types off and on', function (): void {
    video();
    SDL_SetEventEnabled(SDL_EVENT_JOYSTICK_UPDATE_COMPLETE, false);

    expect(SDL_EventEnabled(SDL_EVENT_JOYSTICK_UPDATE_COMPLETE))->toBeFalse();

    SDL_SetEventEnabled(SDL_EVENT_JOYSTICK_UPDATE_COMPLETE, true);

    expect(SDL_EventEnabled(SDL_EVENT_JOYSTICK_UPDATE_COMPLETE))->toBeTrue();
});

it('names the mouse buttons, wheel directions and modifier masks as SDL does', function (): void {
    expect([SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT, SDL_BUTTON_X1, SDL_BUTTON_X2])->toBe([1, 2, 3, 4, 5])
        ->and([SDL_MOUSEWHEEL_NORMAL, SDL_MOUSEWHEEL_FLIPPED])->toBe([0, 1])
        ->and(SDL_KMOD_SHIFT)->toBe(SDL_KMOD_LSHIFT | SDL_KMOD_RSHIFT)
        ->and(SDL_KMOD_CTRL)->toBe(SDL_KMOD_LCTRL | SDL_KMOD_RCTRL)
        ->and(SDL_KMOD_ALT)->toBe(SDL_KMOD_LALT | SDL_KMOD_RALT)
        ->and(SDL_KMOD_GUI)->toBe(SDL_KMOD_LGUI | SDL_KMOD_RGUI)
        ->and(SDL_KMOD_NONE)->toBe(0)
        ->and(SDL_EVENT_FINGER_DOWN - SDL_EVENT_JOYSTICK_AXIS_MOTION)->toBe(0x100);
});

it('starts every new part at zero', function (): void {
    $event = new SDL_Event();

    expect([$event->key->scancode, $event->key->down, $event->text->text, $event->motion->x, $event->button->button, $event->wheel->direction])
        ->toBe([0, false, '', 0.0, 0, 0]);
});

it('throws instead of crashing when a part was unset before a poll writes it', function (): void {
    $script = tempnam(sys_get_temp_dir(), 'sdl3').'.php';
    file_put_contents($script, '<?php
        SDL_Init(SDL_INIT_VIDEO) || exit("init: ".SDL_GetError());
        $sink = new SDL_Event();
        while (SDL_PollEvent($sink)) {
        }
        $push = new SDL_Event();
        $push->type = SDL_EVENT_KEY_DOWN;
        $push->key->scancode = 4;
        SDL_PushEvent($push);
        $event = new SDL_Event();
        unset($event->key);
        try {
            while (SDL_PollEvent($event)) {
            }
            echo "no error";
        } catch (Error $e) {
            echo get_class($e);
        }');

    $out = shell_exec(escapeshellarg(PHP_BINARY).' -d memory_limit=128M '.escapeshellarg($script).' 2>&1');
    unlink($script);

    expect(trim((string) $out))->toBe('Error');
});
