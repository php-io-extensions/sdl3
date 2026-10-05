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
