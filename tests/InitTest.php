<?php

declare(strict_types=1);

it('starts video and reports a 3.2-or-newer SDL', function (): void {
    video();
    $version = SDL_GetVersion();

    expect(intdiv($version, 1000000))->toBe(3)
        ->and(intdiv($version, 1000) % 1000)->toBeGreaterThanOrEqual(2);
});

it('sets a hint and reads errors as strings', function (): void {
    expect(SDL_SetHint(SDL_HINT_VIDEO_DRIVER, 'nonexistent-driver-for-this-test'))->toBeTrue()
        ->and(SDL_SetHint(SDL_HINT_VIDEO_DRIVER, ''))->toBeTrue()
        ->and(SDL_GetError())->toBeString();
});

it('pumps and polls events into an SDL_Event', function (): void {
    video();
    $event = new SDL_Event();
    SDL_PumpEvents();

    while (SDL_PollEvent($event)) {
        expect($event->type)->toBeInt();
    }

    expect(SDL_PollEvent(null))->toBeFalse()
        ->and(SDL_WaitEventTimeout($event, 0))->toBeBool()
        ->and($event->window)->toBeInstanceOf(SDL_WindowEvent::class);
});

it('starts structs at zero with their nested structs made', function (): void {
    $event = new SDL_Event();

    expect([$event->type, $event->window->windowID, $event->window->data1])->toBe([0, 0, 0]);
});
