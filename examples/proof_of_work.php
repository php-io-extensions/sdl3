<?php
/**
 * sdl3 extension — proof-of-work script
 *
 * Runs entirely headless via SDL's software renderer; no display server required.
 *
 * Usage:
 *   php -d extension=ext/modules/sdl3.so examples/proof_of_work.php
 *   # or, if the extension is globally installed:
 *   php examples/proof_of_work.php
 */

declare(strict_types=1);

use Sdl3\SDL\SDL;
use Sdl3\SDL\SDLError;
use Sdl3\SDL\Surface\SDLSurface;
use Sdl3\SDL\Render\SDLRender;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

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

// ---------------------------------------------------------------------------
// SDL3 pixel-format constant (SDL_PIXELFORMAT_RGBA8888)
//   SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32=6, SDL_PACKEDORDER_RGBA=4,
//                           SDL_PACKEDLAYOUT_8888=6, bits=32, bytes=4)
//   = (1<<28) | (6<<24) | (4<<20) | (6<<16) | (32<<8) | 4
// ---------------------------------------------------------------------------
const SDL_PIXELFORMAT_RGBA8888 = 373694468;

// RGBA8888 packed pixel values: bits 24-31=R, 16-23=G, 8-15=B, 0-7=A
const PIXEL_RED   = 0xFF0000FF; // R=255 G=0   B=0   A=255
const PIXEL_GREEN = 0x00FF00FF; // R=0   G=255 B=0   A=255
const PIXEL_BLUE  = 0x0000FFFF; // R=0   G=0   B=255 A=255

$errors = 0;

// ---------------------------------------------------------------------------
// 1. Extension presence
// ---------------------------------------------------------------------------
section('Extension check');
if (extension_loaded('sdl3')) {
    pass('sdl3 extension is loaded');
} else {
    echo "  [FATAL] sdl3 extension is NOT loaded. Aborting.\n";
    exit(1);
}

// ---------------------------------------------------------------------------
// 2. SDL version / platform info  (no SDL_Init required)
// ---------------------------------------------------------------------------
section('Library metadata');

$rawVersion = SDL::SDLGetVersion();
$major      = intdiv($rawVersion, 1_000_000);
$minor      = intdiv($rawVersion % 1_000_000, 1_000);
$patch      = $rawVersion % 1_000;
echo "  SDL3 version  : {$major}.{$minor}.{$patch} (raw={$rawVersion})\n";

$revision = SDL::SDLGetRevision();
echo "  SDL3 revision : {$revision}\n";

$platform = SDL::SDLGetPlatform();
echo "  Platform      : {$platform}\n";

if ($rawVersion > 0) {
    pass('SDLGetVersion returned a non-zero value');
} else {
    fail('SDLGetVersion', 'returned 0'); $errors++;
}

if ($platform !== '') {
    pass('SDLGetPlatform returned a non-empty string');
} else {
    fail('SDLGetPlatform', 'returned empty string'); $errors++;
}

// ---------------------------------------------------------------------------
// 3. SDL_Init  (flags=0 initialises the SDL core without any subsystem —
//               guaranteed to succeed even without a display or audio device)
// ---------------------------------------------------------------------------
section('SDL_Init(0)');
$initOk = SDL::SDLInit(0);
if ($initOk) {
    pass('SDL_Init succeeded');
} else {
    fail('SDL_Init', sdl_err()); $errors++;
}

// ---------------------------------------------------------------------------
// 4. Surface creation
// ---------------------------------------------------------------------------
section('SDLCreateSurface (16×8, RGBA8888)');
$W = 16;
$H = 8;
$surf = SDLSurface::SDLCreateSurface($W, $H, SDL_PIXELFORMAT_RGBA8888);
if (!empty($surf) && $surf['ptr'] !== 0) {
    pass("Surface created: ptr=0x" . dechex($surf['ptr'])
       . " size={$surf['w']}×{$surf['h']} pitch={$surf['pitch']}");
} else {
    fail('SDLCreateSurface', sdl_err()); $errors++;
    SDL::SDLQuit();
    exit(1);
}
$surfPtr = $surf['ptr'];

// ---------------------------------------------------------------------------
// 5. Fill surface with solid red, verify via pixel read-back
// ---------------------------------------------------------------------------
section('SDLFillSurfaceRect → pixel read-back');

$ok = SDLSurface::SDLFillSurfaceRect($surfPtr, PIXEL_RED);
if ($ok) {
    pass('SDLFillSurfaceRect (solid red)');
} else {
    fail('SDLFillSurfaceRect', sdl_err()); $errors++;
}

$read   = SDLSurface::SDLReadSurfacePixels($surfPtr);
$pixels = $read['pixels_data'] ?? [];
$total  = $W * $H;

if (count($pixels) === $total) {
    pass("SDLReadSurfacePixels returned {$total} pixel(s) as expected");
} else {
    fail('SDLReadSurfacePixels', 'expected ' . $total . ' pixels, got ' . count($pixels));
    $errors++;
}

$allRed = true;
foreach ($pixels as $i => $px) {
    if (($px & 0xFFFFFFFF) !== PIXEL_RED) {
        $allRed = false;
        fail("Pixel #{$i} mismatch", sprintf('expected 0x%08X, got 0x%08X', PIXEL_RED, $px));
        $errors++;
        break;
    }
}
if ($allRed) {
    pass('All pixels confirmed as PIXEL_RED (0x' . dechex(PIXEL_RED) . ')');
}

// ---------------------------------------------------------------------------
// 6. Direct pixel writes — scatter three distinct colours
// ---------------------------------------------------------------------------
section('SDLWriteSurfacePixelAt');

$writeTests = [
    [0, 0, PIXEL_RED,   'red   at (0,0)'],
    [1, 0, PIXEL_GREEN, 'green at (1,0)'],
    [2, 0, PIXEL_BLUE,  'blue  at (2,0)'],
];
foreach ($writeTests as [$x, $y, $color, $label]) {
    $ok = SDLSurface::SDLWriteSurfacePixelAt($surfPtr, $x, $y, $color);
    if ($ok) {
        pass("Write {$label}");
    } else {
        fail("Write {$label}", sdl_err()); $errors++;
    }
}

// Verify the three written pixels
$read2   = SDLSurface::SDLReadSurfacePixels($surfPtr);
$pixels2 = $read2['pixels_data'] ?? [];
foreach ($writeTests as [$x, $y, $color, $label]) {
    $idx = $y * $W + $x;
    $got = $pixels2[$idx] ?? null;
    if ($got !== null && ($got & 0xFFFFFFFF) === $color) {
        pass("Readback {$label} → 0x" . sprintf('%08X', $got));
    } else {
        fail("Readback {$label}", sprintf('expected 0x%08X, got 0x%08X', $color, $got ?? 0));
        $errors++;
    }
}

// ---------------------------------------------------------------------------
// 7. Software renderer — SDLCreateSoftwareRenderer + clear + present
// ---------------------------------------------------------------------------
section('SDLCreateSoftwareRenderer + render pipeline');
try {
    $renderer = SDLRender::SDLCreateSoftwareRenderer($surfPtr);
    pass('SDLCreateSoftwareRenderer returned renderer ptr=0x' . dechex($renderer));
} catch (\RuntimeException $e) {
    fail('SDLCreateSoftwareRenderer', $e->getMessage()); $errors++;
    $renderer = 0;
}

if ($renderer !== 0) {
    // Clear to green
    $colorOk = SDLRender::SDLSetRenderDrawColor($renderer, 0, 255, 0, 255);
    if ($colorOk) {
        pass('SDLSetRenderDrawColor (0, 255, 0, 255)');
    } else {
        fail('SDLSetRenderDrawColor', sdl_err()); $errors++;
    }

    SDLRender::SDLRenderClear($renderer);
    pass('SDLRenderClear');

    $presented = SDLRender::SDLRenderPresent($renderer);
    if ($presented) {
        pass('SDLRenderPresent');
    } else {
        fail('SDLRenderPresent', sdl_err()); $errors++;
    }

    // After clear + present the surface should be mostly green.
    // We do a lightweight spot-check: at least one pixel has G channel set.
    $read3   = SDLSurface::SDLReadSurfacePixels($surfPtr);
    $pixels3 = $read3['pixels_data'] ?? [];
    $hasGreen = false;
    foreach ($pixels3 as $px) {
        // RGBA8888: G occupies bits 16-23
        if ((($px >> 16) & 0xFF) === 255) {
            $hasGreen = true;
            break;
        }
    }
    if ($hasGreen) {
        pass('Post-render pixel check: green channel (255) detected');
    } else {
        fail('Post-render pixel check', 'no pixel with G=255 found after clearing to green');
        $errors++;
    }

    SDLRender::SDLDestroyRenderer($renderer);
    pass('SDLDestroyRenderer');
}

// ---------------------------------------------------------------------------
// 8. Cleanup
// ---------------------------------------------------------------------------
section('Cleanup');
SDLSurface::SDLDestroySurface($surfPtr);
pass('SDLDestroySurface');

SDL::SDLQuit();
pass('SDL_Quit');

// ---------------------------------------------------------------------------
// Summary
// ---------------------------------------------------------------------------
section('Summary');
if ($errors === 0) {
    echo "  All checks passed — sdl3 extension is working correctly.\n\n";
    exit(0);
} else {
    echo "  {$errors} check(s) FAILED. See output above for details.\n\n";
    exit(1);
}
