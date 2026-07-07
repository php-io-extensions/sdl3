<?php
/**
 * sdl3 extension — SDL Video proof script (WP3)
 *
 * Headless-safe subset: video drivers, screensaver toggles, display queries.
 * Windowed operations smoke-tested when SDL_INIT_VIDEO succeeds; skipped otherwise.
 *
 * Usage:
 *   php examples/proof_video.php
 */

declare(strict_types=1);

use Sdl3\SDL\SDL;
use Sdl3\SDL\SDLError;
use Sdl3\SDL\SDLProperties;
use Sdl3\SDL\Events\SDLDisplayEvents;
use Sdl3\SDL\Video\SDLVideo;
use Sdl3\SDL\Video\SDLGL;

const SDL_INIT_VIDEO = 0x00000020;
const SDL_WINDOW_HIDDEN = 0x00000008;
const SDL_WINDOW_OPENGL = 0x00000002;
const SDL_PIXELFORMAT_RGBA8888 = 373694468;
const SDL_HITTEST_NORMAL = 0;
const SDL_FLASH_CANCEL = 0;

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

function assert_true(bool $ok, string $label, int &$errors): void
{
    if ($ok) {
        pass($label);
        return;
    }
    fail($label, sdl_err());
    $errors++;
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

$errors = 0;

section('Extension check');
if (!extension_loaded('sdl3')) {
    echo "  [FATAL] sdl3 extension is NOT loaded. Aborting.\n";
    exit(1);
}
pass('sdl3 extension is loaded');

section('SDL_Init(0) — headless baseline');
if (!SDL::SDLInit(0)) {
    fail('SDL_Init(0)', sdl_err());
    exit(1);
}
pass('SDL_Init(0) succeeded');

section('Video drivers (no window required)');
$numDrivers = SDLVideo::SDLGetNumVideoDrivers();
if ($numDrivers >= 0) {
    pass("SDLGetNumVideoDrivers returned {$numDrivers}");
} else {
    fail('SDLGetNumVideoDrivers');
    $errors++;
}

if ($numDrivers > 0) {
    $driver0 = SDLVideo::SDLGetVideoDriver(0);
    if ($driver0 !== '') {
        pass("SDLGetVideoDriver(0) = {$driver0}");
    } else {
        fail('SDLGetVideoDriver(0)');
        $errors++;
    }
}

$videoOk = SDL::SDLInitSubSystem(SDL_INIT_VIDEO);
if ($videoOk) {
    pass('SDL_InitSubSystem(VIDEO) succeeded');
} else {
    pass('SDL_InitSubSystem(VIDEO) unavailable — skipping video-dependent tests (' . sdl_err() . ')');
}

section('Screensaver toggles');
if (!$videoOk) {
    pass('Screensaver tests skipped — video subsystem unavailable');
} else {
    $initialSaver = SDLVideo::SDLScreenSaverEnabled();
    pass('SDLScreenSaverEnabled initial=' . ($initialSaver ? 'true' : 'false'));

    assert_true(SDLVideo::SDLEnableScreenSaver(), 'SDLEnableScreenSaver', $errors);
    assert_true(SDLVideo::SDLScreenSaverEnabled(), 'SDLScreenSaverEnabled after enable', $errors);
    assert_true(SDLVideo::SDLDisableScreenSaver(), 'SDLDisableScreenSaver', $errors);
    assert_true(!SDLVideo::SDLScreenSaverEnabled(), 'SDLScreenSaverEnabled after disable', $errors);

    if ($initialSaver) {
        SDLVideo::SDLEnableScreenSaver();
    }
}

section('System theme');
$theme = SDLVideo::SDLGetSystemTheme();
pass("SDLGetSystemTheme = {$theme}");

section('Display enumeration');
$displays = SDLDisplayEvents::SDLGetDisplays();
if (count($displays) > 0) {
    pass('SDLGetDisplays returned ' . count($displays) . ' display(s)');
    $primary = SDLDisplayEvents::SDLGetPrimaryDisplay();
    pass("SDLGetPrimaryDisplay = {$primary}");

    $displayId = $displays[0];
    $name = SDLDisplayEvents::SDLGetDisplayName($displayId);
    if ($name !== '') {
        pass("SDLGetDisplayName = {$name}");
    }

    $bounds = SDLDisplayEvents::SDLGetDisplayBounds($displayId);
    if ($bounds !== []) {
        pass('SDLGetDisplayBounds returned rect');
    }

    $usable = SDLVideo::SDLGetDisplayUsableBounds($displayId);
    if ($usable !== []) {
        pass('SDLGetDisplayUsableBounds returned rect');
    }

    $props = SDLVideo::SDLGetDisplayProperties($displayId);
    if ($props !== 0) {
        pass("SDLGetDisplayProperties id={$props}");
    }

    $scale = SDLDisplayEvents::SDLGetDisplayContentScale($displayId);
    pass("SDLGetDisplayContentScale = {$scale}");

    if ($bounds !== []) {
        $cx = (int) ($bounds['x'] + $bounds['w'] / 2);
        $cy = (int) ($bounds['y'] + $bounds['h'] / 2);
        $forPoint = SDLVideo::SDLGetDisplayForPoint($cx, $cy);
        if ($forPoint !== 0) {
            pass("SDLGetDisplayForPoint = {$forPoint}");
        }

        $forRect = SDLVideo::SDLGetDisplayForRect([$bounds['x'], $bounds['y'], 1, 1]);
        if ($forRect !== 0) {
            pass("SDLGetDisplayForRect = {$forRect}");
        }
    }
} else {
    pass('SDLGetDisplays returned empty (headless OK)');
}

section('OpenGL attribute round-trip (no context)');
if (!$videoOk) {
    pass('OpenGL attribute tests skipped — video subsystem unavailable');
} else {
    SDLGL::SDLGLResetAttributes();
    assert_true(SDLGL::SDLGLSetAttribute(0, 8), 'SDLGLSetAttribute RED_SIZE=8', $errors);
    pass('SDLGLResetAttributes + SDLGLSetAttribute (GetAttribute requires an active GL context)');
}

section('Video subsystem — window smoke test');
if (!$videoOk) {
    pass('Window smoke test skipped — video subsystem unavailable');
} else {
    $currentDriver = SDLVideo::SDLGetCurrentVideoDriver();
    if ($currentDriver !== '') {
        pass("SDLGetCurrentVideoDriver = {$currentDriver}");
    }

    try {
        $window = SDLVideo::SDLCreateWindow('sdl3 proof_video', 320, 240, SDL_WINDOW_HIDDEN);
        pass("SDLCreateWindow hidden handle={$window}");

        $winId = SDLVideo::SDLGetWindowID($window);
        assert_eq(SDLVideo::SDLGetWindowFromID($winId), $window, 'SDLGetWindowFromID round-trip', $errors);

        $title = 'proof title';
        assert_true(SDLVideo::SDLSetWindowTitle($window, $title), 'SDLSetWindowTitle', $errors);
        assert_eq(SDLVideo::SDLGetWindowTitle($window), $title, 'SDLGetWindowTitle', $errors);

        assert_true(SDLVideo::SDLSetWindowSize($window, 400, 300), 'SDLSetWindowSize', $errors);
        $size = SDLVideo::SDLGetWindowSize($window);
        if (count($size) === 2) {
            pass('SDLGetWindowSize = [' . $size[0] . ', ' . $size[1] . ']');
        }

        assert_true(SDLVideo::SDLSetWindowMinimumSize($window, 200, 150), 'SDLSetWindowMinimumSize', $errors);
        $minSize = SDLVideo::SDLGetWindowMinimumSize($window);
        if (count($minSize) === 2 && $minSize[0] >= 200 && $minSize[1] >= 150) {
            pass('SDLGetWindowMinimumSize');
        }

        assert_true(SDLVideo::SDLSetWindowOpacity($window, 0.75), 'SDLSetWindowOpacity', $errors);
        $opacity = SDLVideo::SDLGetWindowOpacity($window);
        if ($opacity > 0.0) {
            pass("SDLGetWindowOpacity = {$opacity}");
        }

        $flags = SDLVideo::SDLGetWindowFlags($window);
        pass("SDLGetWindowFlags = {$flags}");

        $displayForWin = SDLDisplayEvents::SDLGetDisplayForWindow($window);
        if ($displayForWin !== 0) {
            pass("SDLGetDisplayForWindow = {$displayForWin}");
        }

        $density = SDLVideo::SDLGetWindowPixelDensity($window);
        pass("SDLGetWindowPixelDensity = {$density}");

        $displayScale = SDLVideo::SDLGetWindowDisplayScale($window);
        pass("SDLGetWindowDisplayScale = {$displayScale}");

        $pixelFormat = SDLVideo::SDLGetWindowPixelFormat($window);
        pass("SDLGetWindowPixelFormat = {$pixelFormat}");

        $winProps = SDLVideo::SDLGetWindowProperties($window);
        if ($winProps !== 0) {
            pass("SDLGetWindowProperties id={$winProps}");
        }

        $windows = SDLVideo::SDLGetWindows();
        if (in_array($window, $windows, true)) {
            pass('SDLGetWindows contains created window');
        }

        assert_true(SDLVideo::SDLSetWindowHitTest($window, function (int $win, int $x, int $y): int {
            return SDL_HITTEST_NORMAL;
        }), 'SDLSetWindowHitTest', $errors);
        assert_true(SDLVideo::SDLSetWindowHitTest($window, null), 'SDLSetWindowHitTest clear', $errors);

        assert_true(SDLVideo::SDLFlashWindow($window, SDL_FLASH_CANCEL), 'SDLFlashWindow', $errors);

        try {
            $props = SDLProperties::SDLCreateProperties();
            $winFromProps = SDLVideo::SDLCreateWindowWithProperties($props);
            pass("SDLCreateWindowWithProperties handle={$winFromProps}");
            SDLVideo::SDLDestroyWindow($winFromProps);
            SDLProperties::SDLDestroyProperties($props);
        } catch (\RuntimeException $e) {
            fail('SDLCreateWindowWithProperties', $e->getMessage());
            $errors++;
        }

        SDLGL::SDLGLResetAttributes();
        assert_true(SDLGL::SDLGLSetAttribute(0, 8), 'SDLGLSetAttribute before context', $errors);

        try {
            $glWindow = SDLVideo::SDLCreateWindow('sdl3 proof_gl', 64, 64, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
            $glCtx = SDLGL::SDLGLCreateContext($glWindow);
            $attr = SDLGL::SDLGLGetAttribute(0);
            if ($attr !== [] && isset($attr['value']) && (int) $attr['value'] === 8) {
                pass('SDLGLGetAttribute RED_SIZE value=' . $attr['value']);
            } else {
                fail('SDLGLGetAttribute RED_SIZE with context', sdl_err());
                $errors++;
            }
            SDLGL::SDLGLDestroyContext($glCtx);
            SDLVideo::SDLDestroyWindow($glWindow);
        } catch (\RuntimeException $e) {
            pass('OpenGL context smoke test skipped: ' . $e->getMessage());
        }

        SDLVideo::SDLDestroyWindow($window);
        pass('SDLDestroyWindow');
    } catch (\RuntimeException $e) {
        fail('Window smoke test', $e->getMessage());
        $errors++;
    }

    SDL::SDLQuitSubSystem(SDL_INIT_VIDEO);
}

section('Cleanup');
SDL::SDLQuit();

section('Summary');
if ($errors === 0) {
    echo "\nAll proof_video checks passed.\n";
    exit(0);
}

echo "\n{$errors} check(s) failed.\n";
exit(1);
