<?php

declare(strict_types=1);

it('claims a window, sets its swapchain and acquires a texture or none, without waiting', function (): void {
    $window = hiddenWindow();
    SDL_ShowWindow($window);

    expect(SDL_ClaimWindowForGPUDevice(gpu(), $window))->toBeTrue(SDL_GetError())
        ->and(SDL_SetGPUSwapchainParameters(gpu(), $window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC))->toBeTrue()
        ->and(SDL_GetGPUSwapchainTextureFormat(gpu(), $window))->not->toBe(SDL_GPU_TEXTUREFORMAT_INVALID);

    $commands = SDL_AcquireGPUCommandBuffer(gpu());
    expect(SDL_AcquireGPUSwapchainTexture($commands, $window, $texture, $w, $h))->toBeTrue();
    if ($texture !== null) {
        expect($texture)->toBeInstanceOf(SDL_GPUTexture::class)->and($w)->toBeGreaterThan(0);
    }
    SDL_SubmitGPUCommandBuffer($commands);
    if ($texture !== null) {
        expect(fn () => $texture->pointer())->toThrow(ValueError::class);
    }

    SDL_WaitForGPUIdle(gpu());
    SDL_ReleaseWindowFromGPUDevice(gpu(), $window);
    SDL_DestroyWindow($window);
});

it('waits for a swapchain texture, acquires one waiting, bounds frames in flight, and asks about compositions', function (): void {
    $window = hiddenWindow();
    SDL_ShowWindow($window);
    SDL_ClaimWindowForGPUDevice(gpu(), $window) || throw new RuntimeException(SDL_GetError());

    expect(SDL_SetGPUAllowedFramesInFlight(gpu(), 1))->toBeTrue(SDL_GetError())
        ->and(SDL_WindowSupportsGPUSwapchainComposition(gpu(), $window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR))->toBeTrue()
        ->and(SDL_WindowSupportsGPUSwapchainComposition(gpu(), $window, SDL_GPU_SWAPCHAINCOMPOSITION_HDR10_ST2084))->toBeBool()
        ->and(SDL_WaitForGPUSwapchain(gpu(), $window))->toBeTrue(SDL_GetError());

    $commands = SDL_AcquireGPUCommandBuffer(gpu());
    expect(SDL_WaitAndAcquireGPUSwapchainTexture($commands, $window, $texture, $w, $h))->toBeTrue(SDL_GetError())
        ->and($texture)->toBeInstanceOf(SDL_GPUTexture::class)
        ->and($w)->toBeGreaterThan(0);
    SDL_SubmitGPUCommandBuffer($commands);
    expect(fn () => $texture->pointer())->toThrow(ValueError::class);

    SDL_SetGPUAllowedFramesInFlight(gpu(), 2);
    SDL_WaitForGPUIdle(gpu());
    SDL_ReleaseWindowFromGPUDevice(gpu(), $window);
    SDL_DestroyWindow($window);
});
