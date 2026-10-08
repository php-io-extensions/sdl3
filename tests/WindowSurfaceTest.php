<?php

declare(strict_types=1);

it('presents only the rects it is given', function (): void {
    $window = hiddenWindow();
    SDL_ShowWindow($window);
    $surface = SDL_GetWindowSurface($window);
    SDL_FillSurfaceRect($surface, new SDL_Rect(0, 0, 40, 40), 0xffff0000);

    expect(SDL_UpdateWindowSurfaceRects($window, [new SDL_Rect(0, 0, 40, 40), new SDL_Rect(80, 60, 10, 10)]))->toBeTrue(SDL_GetError())
        ->and(fn () => SDL_UpdateWindowSurfaceRects($window, [new SDL_Rect(), 'not a rect']))
            ->toThrow(TypeError::class, 'must be a list of SDL_Rect, string found');

    SDL_DestroyWindow($window);
});

it('creates, reports and destroys the window surface, letting go of the boxed one', function (): void {
    $window = hiddenWindow();

    expect(SDL_WindowHasSurface($window))->toBeFalse();
    $surface = SDL_GetWindowSurface($window);
    expect(SDL_WindowHasSurface($window))->toBeTrue()
        ->and(SDL_DestroyWindowSurface($window))->toBeTrue()
        ->and(SDL_WindowHasSurface($window))->toBeFalse()
        ->and(fn () => $surface->w())->toThrow(ValueError::class, 'SDL_Surface has been destroyed');

    SDL_DestroyWindow($window);
});

it('toggles window surface vsync', function (): void {
    $window = hiddenWindow();
    SDL_GetWindowSurface($window);

    expect(SDL_SetWindowSurfaceVSync($window, 1))->toBeTrue(SDL_GetError())
        ->and(SDL_GetWindowSurfaceVSync($window, $vsync))->toBeTrue()
        ->and($vsync)->toBe(1)
        ->and(SDL_SetWindowSurfaceVSync($window, SDL_WINDOW_SURFACE_VSYNC_DISABLED))->toBeTrue()
        ->and(SDL_GetWindowSurfaceVSync($window, $vsync))->toBeTrue()
        ->and($vsync)->toBe(SDL_WINDOW_SURFACE_VSYNC_DISABLED);

    SDL_DestroyWindow($window);
});

it('toggles the GL swap interval and reads it back', function (): void {
    video();
    $mac = PHP_OS_FAMILY === 'Darwin';
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, $mac ? SDL_GL_CONTEXT_PROFILE_CORE : SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, $mac ? 4 : 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    $window = hiddenWindow(SDL_WINDOW_OPENGL);
    $context = SDL_GL_CreateContext($window);
    SDL_GL_MakeCurrent($window, $context);

    expect(SDL_GL_SetSwapInterval(1))->toBeTrue()
        ->and(SDL_GL_GetSwapInterval($interval))->toBeTrue()
        ->and($interval)->toBe(1)
        ->and(SDL_GL_SetSwapInterval(0))->toBeTrue()
        ->and(SDL_GL_GetSwapInterval($interval))->toBeTrue()
        ->and($interval)->toBe(0);

    SDL_GL_MakeCurrent($window, null);
    SDL_GL_DestroyContext($context);
    SDL_DestroyWindow($window);
});

it('asks whether a claimed window supports each GPU present mode', function (): void {
    $window = hiddenWindow();
    SDL_ShowWindow($window);
    SDL_ClaimWindowForGPUDevice(gpu(), $window);

    expect(SDL_WindowSupportsGPUPresentMode(gpu(), $window, SDL_GPU_PRESENTMODE_VSYNC))->toBeTrue()
        ->and(SDL_WindowSupportsGPUPresentMode(gpu(), $window, SDL_GPU_PRESENTMODE_IMMEDIATE))->toBeBool()
        ->and(SDL_WindowSupportsGPUPresentMode(gpu(), $window, SDL_GPU_PRESENTMODE_MAILBOX))->toBeBool();

    SDL_ReleaseWindowFromGPUDevice(gpu(), $window);
    SDL_DestroyWindow($window);
});
