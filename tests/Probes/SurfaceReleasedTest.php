<?php

declare(strict_types=1);

// Site sdl3-surface-released (outcome 1): SDL_Surface's field getters read the struct themselves, not
// through an SDL call. A destroyed surface's pointer is NULL, which the getter would dereference.

beforeEach(fn () => requireProbeBuild());

it('refuses a field of a destroyed surface, which the getter reads through NULL (SIGSEGV) without the refusal', function (): void {
    $code = <<<'PHP'
        $surface = SDL_CreateSurfaceFrom(8, 8, 376840196, str_repeat("\0", 256), 32);
        SDL_DestroySurface($surface);
        $surface->w();
    PHP;

    $kept = sdl3Probe($code, null);
    $off = sdl3Probe($code, 'sdl3-surface-released');

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError: SDL_Surface has been destroyed')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});
