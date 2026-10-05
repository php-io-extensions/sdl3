<?php

declare(strict_types=1);

it('creates a GL context on a GL window, the core profile on the Mac and GLES on Linux', function (): void {
    video();
    $mac = PHP_OS_FAMILY === 'Darwin';
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, $mac ? SDL_GL_CONTEXT_PROFILE_CORE : SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, $mac ? 4 : 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, $mac ? 1 : 1);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    $window = hiddenWindow(SDL_WINDOW_OPENGL);

    $context = SDL_GL_CreateContext($window);

    expect($context)->toBeInstanceOf(SDL_GLContext::class, SDL_GetError())
        ->and(SDL_GL_MakeCurrent($window, $context))->toBeTrue()
        ->and(SDL_GL_SetSwapInterval(0))->toBeTrue()
        ->and(SDL_GL_SwapWindow($window))->toBeBool()
        ->and(SDL_GL_MakeCurrent($window, null))->toBeTrue()
        ->and(SDL_GL_DestroyContext($context))->toBeTrue()
        ->and(fn () => SDL_GL_MakeCurrent($window, $context))->toThrow(ValueError::class, 'SDL_GLContext has been destroyed');

    SDL_DestroyWindow($window);
});

it('makes a Metal view whose layer ext-metal can take', function (): void {
    $window = hiddenWindow(SDL_WINDOW_METAL);
    $view = SDL_Metal_CreateView($window);
    $layer = SDL_Metal_GetLayer($view);

    expect($layer)->toBeGreaterThan(0);
    if (class_exists(CAMetalLayer::class)) {
        expect(CAMetalLayer::fromPointer($layer))->toBeInstanceOf(CAMetalLayer::class);
    }

    SDL_Metal_DestroyView($view);
    SDL_DestroyWindow($window);
})->skip(PHP_OS_FAMILY !== 'Darwin', 'Metal is macOS only');

it('lists the Vulkan instance extensions a window surface needs', function (): void {
    video();
    $extensions = SDL_Vulkan_GetInstanceExtensions();

    expect($extensions)->toBeArray()->toContain('VK_KHR_surface');
})->skip(PHP_OS_FAMILY === 'Darwin', 'the Mac has no Vulkan loader on its default path until slice 5');
