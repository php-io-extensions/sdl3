<?php
/**
 * sdl3 extension — SDL Render proof script (WP2)
 *
 * Headless software-renderer set/get symmetry checks on render state,
 * textures, render targets, and draw helpers. No display server required.
 *
 * Usage:
 *   php examples/proof_render.php
 */

declare(strict_types=1);

use Sdl3\SDL\SDL;
use Sdl3\SDL\SDLError;
use Sdl3\SDL\SDLProperties;
use Sdl3\SDL\Surface\SDLSurface;
use Sdl3\SDL\Render\SDLRender;

const SDL_PIXELFORMAT_RGBA8888 = 373694468;
const SDL_TEXTUREACCESS_STREAMING = 1;
const SDL_TEXTUREACCESS_TARGET = 2;
const SDL_BLENDMODE_BLEND = 0x00000001;
const SDL_BLENDMODE_ADD = 0x00000002;
const SDL_SCALEMODE_NEAREST = 0;
const SDL_SCALEMODE_LINEAR = 1;
const SDL_RENDERER_VSYNC_DISABLED = 0;

function pass(string $label): void
{
    echo "  [PASS] {$label}\n";
}

function fail(string $label, string $detail = ''): void
{
    $msg = "  [FAIL] {$label}";
    if ($detail !== '') {
        $msg .= ": {$detail}";
    }
    echo $msg . "\n";
}

function section(string $title): void
{
    echo "\n── {$title} ──\n";
}

function sdl_err(): string
{
    return SDLError::SDLGetError();
}

function assert_eq(mixed $got, mixed $expected, string $label, int &$errors): void
{
    if ($got === $expected) {
        pass($label);
        return;
    }
    fail($label, 'expected ' . var_export($expected, true) . ', got ' . var_export($got, true));
    $errors++;
}

function assert_true(bool $ok, string $label, int &$errors): void
{
    if ($ok) {
        pass($label);
        return;
    }
    fail($label, sdl_err());
    $errors++;
}

$errors = 0;

section('Extension check');
if (!extension_loaded('sdl3')) {
    echo "  [FATAL] sdl3 extension is NOT loaded. Aborting.\n";
    exit(1);
}
pass('sdl3 extension is loaded');

section('SDL_Init(0)');
if (!SDL::SDLInit(0)) {
    fail('SDL_Init', sdl_err());
    exit(1);
}
pass('SDL_Init succeeded');

section('Render drivers');
$driverCount = SDLRender::SDLGetNumRenderDrivers();
if ($driverCount >= 0) {
    pass("SDLGetNumRenderDrivers returned {$driverCount}");
    if ($driverCount > 0) {
        $driverName = SDLRender::SDLGetRenderDriver(0);
        if ($driverName !== '') {
            pass("SDLGetRenderDriver(0) = {$driverName}");
        } else {
            fail('SDLGetRenderDriver(0)', 'empty name');
            $errors++;
        }
    }
} else {
    fail('SDLGetNumRenderDrivers', 'negative count');
    $errors++;
}

section('Software renderer setup');
$W = 32;
$H = 32;
$surf = SDLSurface::SDLCreateSurface($W, $H, SDL_PIXELFORMAT_RGBA8888);
if (empty($surf) || $surf['ptr'] === 0) {
    fail('SDLCreateSurface', sdl_err());
    SDL::SDLQuit();
    exit(1);
}
$surfPtr = $surf['ptr'];

try {
    $renderer = SDLRender::SDLCreateSoftwareRenderer($surfPtr);
    pass('SDLCreateSoftwareRenderer');
} catch (\RuntimeException $e) {
    fail('SDLCreateSoftwareRenderer', $e->getMessage());
    SDLSurface::SDLDestroySurface($surfPtr);
    SDL::SDLQuit();
    exit(1);
}

$rendererName = SDLRender::SDLGetRendererName($renderer);
if ($rendererName !== '') {
    pass("SDLGetRendererName = {$rendererName}");
} else {
    fail('SDLGetRendererName', 'empty');
    $errors++;
}

$rendererProps = SDLRender::SDLGetRendererProperties($renderer);
if ($rendererProps !== 0) {
    pass("SDLGetRendererProperties id={$rendererProps}");
} else {
    fail('SDLGetRendererProperties', sdl_err());
    $errors++;
}

$fromTexRenderer = SDLRender::SDLGetRendererFromTexture(0);
// No texture yet; just ensure call is safe with zero texture skipped below.

section('Draw color set/get');
assert_true(SDLRender::SDLSetRenderDrawColor($renderer, 10, 20, 30, 40), 'SDLSetRenderDrawColor', $errors);
$color = SDLRender::SDLGetRenderDrawColor($renderer);
assert_eq($color['r'] ?? null, 10, 'GetRenderDrawColor r', $errors);
assert_eq($color['g'] ?? null, 20, 'GetRenderDrawColor g', $errors);
assert_eq($color['b'] ?? null, 30, 'GetRenderDrawColor b', $errors);
assert_eq($color['a'] ?? null, 40, 'GetRenderDrawColor a', $errors);

assert_true(
    SDLRender::SDLSetRenderDrawColorFloat($renderer, 0.5, 0.25, 0.75, 1.0),
    'SDLSetRenderDrawColorFloat',
    $errors
);
$colorF = SDLRender::SDLGetRenderDrawColorFloat($renderer);
if (!empty($colorF)) {
    pass('SDLGetRenderDrawColorFloat returned values');
} else {
    fail('SDLGetRenderDrawColorFloat', sdl_err());
    $errors++;
}

section('Blend mode, color scale, scale, vsync');
assert_true(SDLRender::SDLSetRenderDrawBlendMode($renderer, SDL_BLENDMODE_ADD), 'SDLSetRenderDrawBlendMode', $errors);
$blend = SDLRender::SDLGetRenderDrawBlendMode($renderer);
assert_eq($blend['blend_mode'] ?? null, SDL_BLENDMODE_ADD, 'GetRenderDrawBlendMode', $errors);

assert_true(SDLRender::SDLSetRenderColorScale($renderer, 1.25), 'SDLSetRenderColorScale', $errors);
$colorScale = SDLRender::SDLGetRenderColorScale($renderer);
if (abs(($colorScale['scale'] ?? 0) - 1.25) < 0.01) {
    pass('SDLGetRenderColorScale ≈ 1.25');
} else {
    fail('SDLGetRenderColorScale', var_export($colorScale, true));
    $errors++;
}

assert_true(SDLRender::SDLSetRenderScale($renderer, 2.0, 2.0), 'SDLSetRenderScale', $errors);
$scale = SDLRender::SDLGetRenderScale($renderer);
assert_eq($scale['scale_x'] ?? null, 2.0, 'GetRenderScale scale_x', $errors);
assert_eq($scale['scale_y'] ?? null, 2.0, 'GetRenderScale scale_y', $errors);

assert_true(SDLRender::SDLSetRenderVSync($renderer, SDL_RENDERER_VSYNC_DISABLED), 'SDLSetRenderVSync', $errors);
$vsync = SDLRender::SDLGetRenderVSync($renderer);
assert_eq($vsync['vsync'] ?? null, SDL_RENDERER_VSYNC_DISABLED, 'GetRenderVSync', $errors);

section('Viewport and clip rect set/get');
$viewport = [0, 0, 16, 16];
assert_true(SDLRender::SDLSetRenderViewport($renderer, $viewport), 'SDLSetRenderViewport', $errors);
$gotViewport = SDLRender::SDLGetRenderViewport($renderer);
assert_eq($gotViewport[0] ?? null, 0, 'GetRenderViewport x', $errors);
assert_eq($gotViewport[2] ?? null, 16, 'GetRenderViewport w', $errors);
assert_true(SDLRender::SDLRenderViewportSet($renderer), 'SDLRenderViewportSet', $errors);

$clip = [2, 2, 8, 8];
assert_true(SDLRender::SDLSetRenderClipRect($renderer, $clip), 'SDLSetRenderClipRect', $errors);
$gotClip = SDLRender::SDLGetRenderClipRect($renderer);
assert_eq($gotClip[0] ?? null, 2, 'GetRenderClipRect x', $errors);
assert_true(SDLRender::SDLRenderClipEnabled($renderer), 'SDLRenderClipEnabled', $errors);

section('Output size and logical presentation');
$outSize = SDLRender::SDLGetRenderOutputSize($renderer);
if (!empty($outSize)) {
    pass('SDLGetRenderOutputSize w=' . ($outSize['w'] ?? '?') . ' h=' . ($outSize['h'] ?? '?'));
} else {
    fail('SDLGetRenderOutputSize', sdl_err());
    $errors++;
}

$curOut = SDLRender::SDLGetCurrentRenderOutputSize($renderer);
if (!empty($curOut)) {
    pass('SDLGetCurrentRenderOutputSize');
} else {
    fail('SDLGetCurrentRenderOutputSize', sdl_err());
    $errors++;
}

assert_true(SDLRender::SDLSetRenderLogicalPresentation($renderer, $W, $H, 1), 'SDLSetRenderLogicalPresentation', $errors);
$logical = SDLRender::SDLGetRenderLogicalPresentation($renderer);
assert_eq($logical['w'] ?? null, $W, 'GetRenderLogicalPresentation w', $errors);
$logicalRect = SDLRender::SDLGetRenderLogicalPresentationRect($renderer);
if (!empty($logicalRect)) {
    pass('SDLGetRenderLogicalPresentationRect');
} else {
    fail('SDLGetRenderLogicalPresentationRect', sdl_err());
    $errors++;
}

section('Default texture scale mode');
assert_true(SDLRender::SDLSetDefaultTextureScaleMode($renderer, SDL_SCALEMODE_LINEAR), 'SDLSetDefaultTextureScaleMode', $errors);
$defaultScale = SDLRender::SDLGetDefaultTextureScaleMode($renderer);
assert_eq($defaultScale['scale_mode'] ?? null, SDL_SCALEMODE_LINEAR, 'GetDefaultTextureScaleMode', $errors);

section('Texture create, mods, lock, update');
$texInfo = SDLRender::SDLCreateTexture($renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 8, 8);
if (empty($texInfo) || ($texInfo['ptr'] ?? 0) === 0) {
    fail('SDLCreateTexture', sdl_err());
    $errors++;
    $texPtr = 0;
} else {
    $texPtr = $texInfo['ptr'];
    pass('SDLCreateTexture streaming 8×8');

    assert_true(SDLRender::SDLSetTextureColorMod($texPtr, 128, 64, 32), 'SDLSetTextureColorMod', $errors);
    $texColor = SDLRender::SDLGetTextureColorMod($texPtr);
    assert_eq($texColor['r'] ?? null, 128, 'GetTextureColorMod r', $errors);

    assert_true(SDLRender::SDLSetTextureAlphaMod($texPtr, 200), 'SDLSetTextureAlphaMod', $errors);
    $texAlpha = SDLRender::SDLGetTextureAlphaMod($texPtr);
    assert_eq($texAlpha['alpha'] ?? null, 200, 'GetTextureAlphaMod', $errors);

    assert_true(SDLRender::SDLSetTextureBlendMode($texPtr, SDL_BLENDMODE_BLEND), 'SDLSetTextureBlendMode', $errors);
    $texBlend = SDLRender::SDLGetTextureBlendMode($texPtr);
    assert_eq($texBlend['blend_mode'] ?? null, SDL_BLENDMODE_BLEND, 'GetTextureBlendMode', $errors);

    assert_true(SDLRender::SDLSetTextureScaleMode($texPtr, SDL_SCALEMODE_NEAREST), 'SDLSetTextureScaleMode', $errors);
    $texScale = SDLRender::SDLGetTextureScaleMode($texPtr);
    assert_eq($texScale['scale_mode'] ?? null, SDL_SCALEMODE_NEAREST, 'GetTextureScaleMode', $errors);

    $lock = SDLRender::SDLLockTexture($texPtr);
    if (!empty($lock) && ($lock['pitch'] ?? 0) > 0) {
        pass('SDLLockTexture pitch=' . $lock['pitch']);
        SDLRender::SDLUnlockTexture($texPtr);
        pass('SDLUnlockTexture after lock');
    } else {
        fail('SDLLockTexture', sdl_err());
        $errors++;
    }

    $pixelBytes = str_repeat("\xFF\x00\x00\xFF", 8 * 8);
    assert_true(SDLRender::SDLUpdateTexture($texPtr, $pixelBytes, 8 * 4), 'SDLUpdateTexture', $errors);

    $renFromTex = SDLRender::SDLGetRendererFromTexture($texPtr);
    assert_eq($renFromTex, $renderer, 'SDLGetRendererFromTexture', $errors);
}

section('CreateTextureWithProperties');
$texProps = SDLProperties::SDLCreateProperties();
SDLProperties::SDLSetNumberProperty($texProps, 'SDL.texture.create.format', SDL_PIXELFORMAT_RGBA8888);
SDLProperties::SDLSetNumberProperty($texProps, 'SDL.texture.create.access', SDL_TEXTUREACCESS_STREAMING);
SDLProperties::SDLSetNumberProperty($texProps, 'SDL.texture.create.width', 4);
SDLProperties::SDLSetNumberProperty($texProps, 'SDL.texture.create.height', 4);
$texPropsInfo = SDLRender::SDLCreateTextureWithProperties($renderer, $texProps);
SDLProperties::SDLDestroyProperties($texProps);
if (!empty($texPropsInfo) && ($texPropsInfo['ptr'] ?? 0) !== 0) {
    pass('SDLCreateTextureWithProperties 4×4');
    SDLRender::SDLDestroyTexture($texPropsInfo['ptr']);
} else {
    fail('SDLCreateTextureWithProperties', sdl_err());
    $errors++;
}

section('CreateRendererWithProperties (software surface)');
$surf2 = SDLSurface::SDLCreateSurface(8, 8, SDL_PIXELFORMAT_RGBA8888);
$renProps = SDLProperties::SDLCreateProperties();
SDLProperties::SDLSetPointerProperty($renProps, 'SDL.renderer.create.surface', $surf2['ptr']);
try {
    $renderer2 = SDLRender::SDLCreateRendererWithProperties($renProps);
    pass('SDLCreateRendererWithProperties surface-backed');
    SDLRender::SDLDestroyRenderer($renderer2);
} catch (\RuntimeException $e) {
    fail('SDLCreateRendererWithProperties', $e->getMessage());
    $errors++;
}
SDLProperties::SDLDestroyProperties($renProps);
SDLSurface::SDLDestroySurface($surf2['ptr']);

section('Render target');
$targetInfo = SDLRender::SDLCreateTexture($renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 8, 8);
if (!empty($targetInfo) && ($targetInfo['ptr'] ?? 0) !== 0) {
    $targetPtr = $targetInfo['ptr'];
    assert_true(SDLRender::SDLSetRenderTarget($renderer, $targetPtr), 'SDLSetRenderTarget', $errors);
    assert_eq(SDLRender::SDLGetRenderTarget($renderer), $targetPtr, 'SDLGetRenderTarget', $errors);
    assert_true(SDLRender::SDLSetRenderTarget($renderer, null), 'SDLSetRenderTarget NULL', $errors);
    assert_eq(SDLRender::SDLGetRenderTarget($renderer), 0, 'SDLGetRenderTarget cleared', $errors);
    SDLRender::SDLDestroyTexture($targetPtr);
    pass('Render target round-trip');
} else {
    fail('SDLCreateTexture TARGET', sdl_err());
    $errors++;
}

section('Draw helpers');
assert_true(SDLRender::SDLRenderPoint($renderer, 1.0, 1.0), 'SDLRenderPoint', $errors);
if ($texPtr !== 0) {
    assert_true(
        SDLRender::SDLRenderTextureTiled($renderer, $texPtr, 1.0, null, [0.0, 0.0, 16.0, 16.0]),
        'SDLRenderTextureTiled',
        $errors
    );
    assert_true(
        SDLRender::SDLRenderTexture9Grid($renderer, $texPtr, 1.0, 1.0, 1.0, 1.0, 1.0, null, [0.0, 0.0, 16.0, 16.0]),
        'SDLRenderTexture9Grid',
        $errors
    );
    assert_true(
        SDLRender::SDLRenderTexture9GridTiled($renderer, $texPtr, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, null, [0.0, 0.0, 16.0, 16.0]),
        'SDLRenderTexture9GridTiled',
        $errors
    );
    SDLRender::SDLDestroyTexture($texPtr);
}

assert_true(SDLRender::SDLFlushRenderer($renderer), 'SDLFlushRenderer', $errors);

section('Cleanup');
SDLRender::SDLDestroyRenderer($renderer);
SDLSurface::SDLDestroySurface($surfPtr);
SDL::SDLQuit();
pass('Cleanup complete');

section('Summary');
if ($errors === 0) {
    echo "  All render checks passed.\n\n";
    exit(0);
}

echo "  {$errors} check(s) FAILED.\n\n";
exit(1);
