<?php

declare(strict_types=1);

it('starts, reports and stops text input on a window', function (): void {
    $window = hiddenWindow();

    expect(SDL_StartTextInput($window))->toBeTrue()
        ->and(SDL_TextInputActive($window))->toBeTrue()
        ->and(SDL_StopTextInput($window))->toBeTrue()
        ->and(SDL_TextInputActive($window))->toBeFalse();

    SDL_DestroyWindow($window);
});

it('answers the window with keyboard focus as the handle it already gave out, or null', function (): void {
    $window = hiddenWindow();
    $focus = SDL_GetKeyboardFocus();

    expect(is_null($focus) || $focus instanceof SDL_Window)->toBeTrue()
        ->and($focus === $window)->toBeFalse();

    SDL_DestroyWindow($window);
});

it('numbers scancodes by USB HID position', function (): void {
    expect([SDL_SCANCODE_A, SDL_SCANCODE_Z, SDL_SCANCODE_1, SDL_SCANCODE_0, SDL_SCANCODE_RETURN, SDL_SCANCODE_F12])->toBe([4, 29, 30, 39, 40, 69])
        ->and([SDL_SCANCODE_KP_0, SDL_SCANCODE_APPLICATION, SDL_SCANCODE_KP_EQUALS, SDL_SCANCODE_CLEAR])->toBe([98, 101, 103, 156])
        ->and([SDL_SCANCODE_LCTRL, SDL_SCANCODE_RGUI])->toBe([224, 231]);
});
