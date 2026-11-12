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
    // Windows shown by earlier tests can still deliver compositor events; let them land first.
    pumpEvents();
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

it('brings the audio subsystem up and down', function (): void {
    $before = getenv('SDL_AUDIO_DRIVER');
    putenv('SDL_AUDIO_DRIVER=dummy');
    try {
        expect(SDL_INIT_AUDIO)->toBe(0x10)
            ->and(SDL_InitSubSystem(SDL_INIT_AUDIO))->toBeTrue()
            ->and(SDL_WasInit(SDL_INIT_AUDIO))->toBe(SDL_INIT_AUDIO);
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        expect(SDL_WasInit(SDL_INIT_AUDIO))->toBe(0);
    } finally {
        putenv($before === false ? 'SDL_AUDIO_DRIVER' : "SDL_AUDIO_DRIVER=$before");
    }
});
