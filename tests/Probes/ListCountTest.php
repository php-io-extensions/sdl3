<?php

declare(strict_types=1);

// Site sdl3-list-count (outcome 1): a list and its C count are separate parameters. SDL reads count
// elements from the native array built from the list, so a count past the list reads past that array.
// The child runs under libgmalloc, so the over-read faults at the guard page.

beforeEach(fn () => requireProbeBuild());

it('refuses a count past the list, which SDL reads past (SIGSEGV) without the refusal', function (): void {
    $code = <<<'PHP'
        $window = SDL_CreateWindow('probe', 64, 64, SDL_WINDOW_HIDDEN);
        SDL_GetWindowSurface($window);
        SDL_UpdateWindowSurfaceRects($window, [new SDL_Rect(0, 0, 8, 8)], 1 << 20);
    PHP;

    $kept = sdl3Probe($code, null, gmalloc: true);
    $off = sdl3Probe($code, 'sdl3-list-count', gmalloc: true);

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError: SDL_UpdateWindowSurfaceRects(): Argument #3 ($numrects) must be between 0 and the length of argument #2 ($rects)')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});

it('refuses a vertex count past the list of SDL_RenderGeometry, which SDL reads past (SIGSEGV) without the refusal', function (): void {
    $code = <<<'PHP'
        $surface = SDL_CreateSurface(8, 8, SDL_PIXELFORMAT_RGBA32);
        $renderer = SDL_CreateSoftwareRenderer($surface);
        $vertex = new SDL_Vertex(new SDL_FPoint(1.0, 1.0), new SDL_FColor(), new SDL_FPoint());
        SDL_RenderGeometry($renderer, null, [$vertex], (1 << 20) - 1, null, 0);
    PHP;

    $kept = sdl3Probe($code, null, gmalloc: true);
    $off = sdl3Probe($code, 'sdl3-list-count', gmalloc: true);

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError: SDL_RenderGeometry(): Argument #4 ($num_vertices) must be between 0 and the length of argument #3 ($vertices)')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});
