<?php
/**
 * sdl3 extension — SDL Surface proof script (WP4)
 *
 * Headless round-trip: create, mutate, save to temp file, reload, compare pixels.
 *
 * Usage:
 *   php examples/proof_surface.php
 */

declare(strict_types=1);

use Sdl3\SDL\SDL;
use Sdl3\SDL\SDLError;
use Sdl3\SDL\Surface\SDLSurface;

const SDL_PIXELFORMAT_RGBA8888 = 373694468;
const SDL_PIXELFORMAT_ARGB8888 = 377888772;
const SDL_PIXELFORMAT_INDEX8   = 318769153;
const SDL_BLENDMODE_BLEND      = 1;
const SDL_FLIP_HORIZONTAL      = 1;
const SDL_SCALEMODE_NEAREST    = 0;

const PIXEL_RED   = 0xFF0000FF;
const PIXEL_GREEN = 0x00FF00FF;
const PIXEL_BLUE  = 0x0000FFFF;

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

$tmpBmp = sys_get_temp_dir() . '/sdl3_proof_surface_' . getmypid() . '.bmp';
$tmpPng = sys_get_temp_dir() . '/sdl3_proof_surface_' . getmypid() . '.png';

section('Create / properties / palette');
$surf = SDLSurface::SDLCreateSurface(8, 8, SDL_PIXELFORMAT_RGBA8888);
$ptr  = $surf['ptr'];
if ($ptr === 0) {
    fail('SDLCreateSurface', sdl_err());
    exit(1);
}
pass("Created 8x8 surface ptr={$ptr}");

$props = SDLSurface::SDLGetSurfaceProperties($ptr);
if ($props !== 0) {
    pass("SDLGetSurfaceProperties id={$props}");
} else {
    fail('SDLGetSurfaceProperties', sdl_err());
    $errors++;
}

if (SDLSurface::SDLSetSurfaceColorspace($ptr, 0)) {
    pass('SDLSetSurfaceColorspace');
} else {
    fail('SDLSetSurfaceColorspace', sdl_err());
    $errors++;
}

$cs = SDLSurface::SDLGetSurfaceColorspace($ptr);
pass("SDLGetSurfaceColorspace = {$cs}");

$fmtName = SDLSurface::SDLGetPixelFormatName(SDL_PIXELFORMAT_RGBA8888);
if ($fmtName !== '') {
    pass("SDLGetPixelFormatName = {$fmtName}");
} else {
    fail('SDLGetPixelFormatName');
    $errors++;
}

$masks = SDLSurface::SDLGetMasksForPixelFormat(SDL_PIXELFORMAT_RGBA8888);
if ($masks['result'] && $masks['bpp'] === 32) {
    pass('SDLGetMasksForPixelFormat bpp=32');
} else {
    fail('SDLGetMasksForPixelFormat', json_encode($masks));
    $errors++;
}

$fromMasks = SDLSurface::SDLGetPixelFormatForMasks(
    $masks['bpp'],
    $masks['rmask'],
    $masks['gmask'],
    $masks['bmask'],
    $masks['amask']
);
if ($fromMasks === SDL_PIXELFORMAT_RGBA8888) {
    pass('SDLGetPixelFormatForMasks round-trip');
} else {
    fail('SDLGetPixelFormatForMasks', "got {$fromMasks}");
    $errors++;
}

section('Per-pixel read/write and map');

if (SDLSurface::SDLWriteSurfacePixel($ptr, 0, 0, 255, 0, 0, 255)) {
    pass('SDLWriteSurfacePixel red at (0,0)');
} else {
    fail('SDLWriteSurfacePixel', sdl_err());
    $errors++;
}

$px = SDLSurface::SDLReadSurfacePixel($ptr, 0, 0);
if ($px['result'] && $px['r'] === 255 && $px['g'] === 0 && $px['b'] === 0 && $px['a'] === 255) {
    pass('SDLReadSurfacePixel matches write');
} else {
    fail('SDLReadSurfacePixel', json_encode($px));
    $errors++;
}

if (SDLSurface::SDLWriteSurfacePixelFloat($ptr, 1, 0, 0.0, 1.0, 0.0, 1.0)) {
    pass('SDLWriteSurfacePixelFloat green at (1,0)');
} else {
    fail('SDLWriteSurfacePixelFloat', sdl_err());
    $errors++;
}

$pfx = SDLSurface::SDLReadSurfacePixelFloat($ptr, 1, 0);
if ($pfx['result'] && abs($pfx['g'] - 1.0) < 0.01) {
    pass('SDLReadSurfacePixelFloat matches write');
} else {
    fail('SDLReadSurfacePixelFloat', json_encode($pfx));
    $errors++;
}

$mapped = SDLSurface::SDLMapSurfaceRGBA($ptr, 0, 0, 255, 255);
$rgb    = SDLSurface::SDLGetRGB($mapped, SDL::SDLGetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888)['ptr']);
if ($rgb['b'] === 255) {
    pass('SDLMapSurfaceRGBA + SDLGetRGB');
} else {
    fail('SDLMapSurfaceRGBA/SDLGetRGB', json_encode($rgb));
    $errors++;
}

section('Color mod, blend, clip, RLE, colorkey');

SDLSurface::SDLSetSurfaceColorMod($ptr, 200, 200, 200);
$cm = SDLSurface::SDLGetSurfaceColorMod($ptr);
if ($cm['result'] && $cm['r'] === 200) {
    pass('SDLSetSurfaceColorMod / SDLGetSurfaceColorMod');
} else {
    fail('ColorMod get/set', json_encode($cm));
    $errors++;
}

SDLSurface::SDLSetSurfaceAlphaMod($ptr, 128);
$am = SDLSurface::SDLGetSurfaceAlphaMod($ptr);
if ($am['result'] && $am['alpha'] === 128) {
    pass('SDLSetSurfaceAlphaMod / SDLGetSurfaceAlphaMod');
} else {
    fail('AlphaMod get/set', json_encode($am));
    $errors++;
}

SDLSurface::SDLSetSurfaceBlendMode($ptr, SDL_BLENDMODE_BLEND);
$bm = SDLSurface::SDLGetSurfaceBlendMode($ptr);
if ($bm['result'] && $bm['blend_mode'] === SDL_BLENDMODE_BLEND) {
    pass('SDLSetSurfaceBlendMode / SDLGetSurfaceBlendMode');
} else {
    fail('BlendMode get/set', json_encode($bm));
    $errors++;
}

SDLSurface::SDLSetSurfaceClipRect($ptr, [2, 2, 4, 4]);
$clip = SDLSurface::SDLGetSurfaceClipRect($ptr);
if ($clip['result'] && $clip['x'] === 2 && $clip['w'] === 4) {
    pass('SDLSetSurfaceClipRect / SDLGetSurfaceClipRect');
} else {
    fail('ClipRect get/set', json_encode($clip));
    $errors++;
}
SDLSurface::SDLSetSurfaceClipRect($ptr, null);

SDLSurface::SDLSetSurfaceRLE($ptr, true);
if (SDLSurface::SDLSurfaceHasRLE($ptr)) {
    pass('SDLSetSurfaceRLE / SDLSurfaceHasRLE');
} else {
    fail('RLE');
    $errors++;
}
SDLSurface::SDLSetSurfaceRLE($ptr, false);

$keyPx = SDLSurface::SDLMapSurfaceRGB($ptr, 255, 0, 255);
SDLSurface::SDLSetSurfaceColorKey($ptr, true, $keyPx);
if (SDLSurface::SDLSurfaceHasColorKey($ptr)) {
    $ck = SDLSurface::SDLGetSurfaceColorKey($ptr);
    if ($ck['result'] && $ck['key'] === $keyPx) {
        pass('SDLSetSurfaceColorKey / SDLGetSurfaceColorKey');
    } else {
        fail('GetSurfaceColorKey', json_encode($ck));
        $errors++;
    }
} else {
    fail('SurfaceHasColorKey');
    $errors++;
}

section('Fill, clear, blits, transforms');

SDLSurface::SDLFillSurfaceRect($ptr, PIXEL_BLUE);
SDLSurface::SDLFillSurfaceRects($ptr, [[0, 0, 2, 2], [2, 2, 2, 2]], PIXEL_RED);

$dst = SDLSurface::SDLCreateSurface(8, 8, SDL_PIXELFORMAT_RGBA8888);
$dstPtr = $dst['ptr'];
SDLSurface::SDLBlitSurface($ptr, $dstPtr, [0, 0, 8, 8], [0, 0, 8, 8]);
SDLSurface::SDLBlitSurfaceScaled($ptr, $dstPtr, [0, 0, 8, 8], [0, 0, 4, 4], SDL_SCALEMODE_NEAREST);
SDLSurface::SDLBlitSurfaceTiled($ptr, $dstPtr, [0, 0, 2, 2], [0, 0, 8, 8]);
SDLSurface::SDLBlitSurfaceTiledWithScale($ptr, $dstPtr, 2.0, SDL_SCALEMODE_NEAREST, [0, 0, 2, 2], [0, 0, 8, 8]);
SDLSurface::SDLBlitSurface9Grid($ptr, $dstPtr, 1, 1, 1, 1, 1.0, SDL_SCALEMODE_NEAREST);
SDLSurface::SDLBlitSurfaceUnchecked($ptr, [0, 0, 4, 4], $dstPtr, [4, 4, 4, 4]);
SDLSurface::SDLBlitSurfaceUncheckedScaled($ptr, [0, 0, 4, 4], $dstPtr, [0, 0, 4, 4], SDL_SCALEMODE_NEAREST);
SDLSurface::SDLStretchSurface($ptr, $dstPtr, [0, 0, 4, 4], [0, 0, 8, 8], SDL_SCALEMODE_NEAREST);
pass('Blit variants exercised');

SDLSurface::SDLClearSurface($ptr, 0.0, 0.0, 0.0, 1.0);
pass('SDLClearSurface');

SDLSurface::SDLFlipSurface($ptr, SDL_FLIP_HORIZONTAL);
pass('SDLFlipSurface');

$scaled = SDLSurface::SDLScaleSurface($ptr, 16, 16, SDL_SCALEMODE_NEAREST);
if ($scaled['ptr'] !== 0 && $scaled['w'] === 16) {
    pass('SDLScaleSurface 16x16');
    SDLSurface::SDLDestroySurface($scaled['ptr']);
} else {
    fail('SDLScaleSurface');
    $errors++;
}

$rotated = SDLSurface::SDLRotateSurface($ptr, 90.0);
if ($rotated['ptr'] !== 0) {
    pass('SDLRotateSurface 90°');
    SDLSurface::SDLDestroySurface($rotated['ptr']);
} else {
    fail('SDLRotateSurface', sdl_err());
    $errors++;
}

$dup = SDLSurface::SDLDuplicateSurface($ptr);
if ($dup['ptr'] !== 0) {
    pass('SDLDuplicateSurface');
    SDLSurface::SDLDestroySurface($dup['ptr']);
} else {
    fail('SDLDuplicateSurface');
    $errors++;
}

$converted = SDLSurface::SDLConvertSurface($ptr, SDL_PIXELFORMAT_ARGB8888);
if ($converted['ptr'] !== 0) {
    pass('SDLConvertSurface');
    SDLSurface::SDLDestroySurface($converted['ptr']);
} else {
    fail('SDLConvertSurface', sdl_err());
    $errors++;
}

$convCs = SDLSurface::SDLConvertSurfaceAndColorspace($ptr, SDL_PIXELFORMAT_RGBA8888);
if ($convCs['ptr'] !== 0) {
    pass('SDLConvertSurfaceAndColorspace');
    SDLSurface::SDLDestroySurface($convCs['ptr']);
} else {
    fail('SDLConvertSurfaceAndColorspace', sdl_err());
    $errors++;
}

section('CreateSurfaceFrom / ConvertPixels / Premultiply');

$rawPixels = str_repeat("\x00\x00\xFF\xFF", 4); // 2x2 blue RGBA8888
$from = SDLSurface::SDLCreateSurfaceFrom(2, 2, SDL_PIXELFORMAT_RGBA8888, $rawPixels, 8);
if ($from['ptr'] !== 0) {
    pass('SDLCreateSurfaceFrom 2x2');
    SDLSurface::SDLDestroySurface($from['ptr']);
} else {
    fail('SDLCreateSurfaceFrom', sdl_err());
    $errors++;
}

$srcPitch = 8 * 4;
$srcBuf   = str_repeat("\xFF\x00\x00\xFF", 8 * 8);
$dstBuf   = SDLSurface::SDLConvertPixels(8, 8, SDL_PIXELFORMAT_RGBA8888, $srcBuf, $srcPitch, SDL_PIXELFORMAT_ARGB8888, $srcPitch);
if (strlen($dstBuf) === 8 * 8 * 4) {
    pass('SDLConvertPixels');
} else {
    fail('SDLConvertPixels', 'unexpected dst length ' . strlen($dstBuf));
    $errors++;
}

$dstCs = SDLSurface::SDLConvertPixelsAndColorspace(
    8, 8,
    SDL_PIXELFORMAT_RGBA8888, 0, 0,
    $srcBuf, $srcPitch,
    SDL_PIXELFORMAT_RGBA8888, 0, 0,
    $srcPitch
);
if (strlen($dstCs) === 8 * 8 * 4) {
    pass('SDLConvertPixelsAndColorspace');
} else {
    fail('SDLConvertPixelsAndColorspace');
    $errors++;
}

$pma = SDLSurface::SDLPremultiplyAlpha(8, 8, SDL_PIXELFORMAT_RGBA8888, $srcBuf, $srcPitch, SDL_PIXELFORMAT_RGBA8888, $srcPitch, false);
if (strlen($pma) === 8 * 8 * 4) {
    pass('SDLPremultiplyAlpha');
} else {
    fail('SDLPremultiplyAlpha');
    $errors++;
}

if (SDLSurface::SDLPremultiplySurfaceAlpha($ptr, false)) {
    pass('SDLPremultiplySurfaceAlpha');
} else {
    fail('SDLPremultiplySurfaceAlpha', sdl_err());
    $errors++;
}

section('Palette ops');

$pal = SDLSurface::SDLCreatePalette(4);
$palPtr = $pal['ptr'];
if ($palPtr !== 0) {
    pass('SDLCreatePalette');
} else {
    fail('SDLCreatePalette');
    $errors++;
}

$colors = [
    ['r' => 255, 'g' => 0,   'b' => 0,   'a' => 255],
    ['r' => 0,   'g' => 255, 'b' => 0,   'a' => 255],
    ['r' => 0,   'g' => 0,   'b' => 255, 'a' => 255],
    ['r' => 255, 'g' => 255, 'b' => 255, 'a' => 255],
];
if (SDLSurface::SDLSetPaletteColors($palPtr, $colors, 0, 4)) {
    pass('SDLSetPaletteColors');
} else {
    fail('SDLSetPaletteColors', sdl_err());
    $errors++;
}

$indexed = SDLSurface::SDLCreateSurface(4, 4, SDL_PIXELFORMAT_INDEX8);
$indexedPtr = $indexed['ptr'];
if ($indexedPtr !== 0) {
    try {
        $surfPal = SDLSurface::SDLCreateSurfacePalette($indexedPtr);
        if ($surfPal['ptr'] !== 0) {
            pass('SDLCreateSurfacePalette');
        } else {
            fail('SDLCreateSurfacePalette');
            $errors++;
        }
    } catch (\RuntimeException $e) {
        fail('SDLCreateSurfacePalette', $e->getMessage());
        $errors++;
    }
} else {
    fail('Indexed surface fixture for palette');
    $errors++;
}

if (SDLSurface::SDLSetSurfacePalette($indexedPtr, $palPtr)) {
    $gotPal = SDLSurface::SDLGetSurfacePalette($indexedPtr);
    if ($gotPal['ptr'] === $palPtr) {
        pass('SDLSetSurfacePalette / SDLGetSurfacePalette');
    } else {
        fail('SDLGetSurfacePalette after set');
        $errors++;
    }
} else {
    fail('SDLSetSurfacePalette', sdl_err());
    $errors++;
}

section('Alternate images');

$alt = SDLSurface::SDLCreateSurface(4, 4, SDL_PIXELFORMAT_RGBA8888);
$altPtr = $alt['ptr'];
if (SDLSurface::SDLAddSurfaceAlternateImage($ptr, $altPtr)) {
    pass('SDLAddSurfaceAlternateImage');
} else {
    fail('SDLAddSurfaceAlternateImage', sdl_err());
    $errors++;
}

if (SDLSurface::SDLSurfaceHasAlternateImages($ptr)) {
    pass('SDLSurfaceHasAlternateImages');
} else {
    fail('SDLSurfaceHasAlternateImages');
    $errors++;
}

$imgs = SDLSurface::SDLGetSurfaceImages($ptr);
if ($imgs['count'] >= 1) {
    pass("SDLGetSurfaceImages count={$imgs['count']}");
} else {
    fail('SDLGetSurfaceImages');
    $errors++;
}

SDLSurface::SDLRemoveSurfaceAlternateImages($ptr);
if (!SDLSurface::SDLSurfaceHasAlternateImages($ptr)) {
    pass('SDLRemoveSurfaceAlternateImages');
} else {
    fail('SDLRemoveSurfaceAlternateImages');
    $errors++;
}

section('Save / load round-trip');

SDLSurface::SDLFillSurfaceRect($ptr, PIXEL_RED);
SDLSurface::SDLWriteSurfacePixel($ptr, 7, 7, 0, 255, 0, 255);

$before = SDLSurface::SDLReadSurfacePixel($ptr, 7, 7);

if (SDLSurface::SDLSaveBMP($ptr, $tmpBmp)) {
    pass("SDLSaveBMP → {$tmpBmp}");
} else {
    fail('SDLSaveBMP', sdl_err());
    $errors++;
}

if (SDLSurface::SDLSavePNG($ptr, $tmpPng)) {
    pass("SDLSavePNG → {$tmpPng}");
} else {
    fail('SDLSavePNG', sdl_err());
    $errors++;
}

$loadedBmp = SDLSurface::SDLLoadBMP($tmpBmp);
$loadedPng = SDLSurface::SDLLoadPNG($tmpPng);

if ($loadedBmp['ptr'] !== 0 && $loadedBmp['w'] === 8) {
    pass('SDLLoadBMP reload');
    $afterBmp = SDLSurface::SDLReadSurfacePixel($loadedBmp['ptr'], 7, 7);
    if ($afterBmp['result'] && $afterBmp['g'] === $before['g']) {
        pass('BMP pixel at (7,7) matches');
    } else {
        fail('BMP pixel compare', json_encode($afterBmp));
        $errors++;
    }
    SDLSurface::SDLDestroySurface($loadedBmp['ptr']);
} else {
    fail('SDLLoadBMP', sdl_err());
    $errors++;
}

if ($loadedPng['ptr'] !== 0 && $loadedPng['w'] === 8) {
    pass('SDLLoadPNG reload');
    SDLSurface::SDLDestroySurface($loadedPng['ptr']);
} else {
    fail('SDLLoadPNG', sdl_err());
    $errors++;
}

if (is_file($tmpBmp)) {
    unlink($tmpBmp);
}
if (is_file($tmpPng)) {
    unlink($tmpPng);
}

section('Cleanup');

SDLSurface::SDLDestroySurface($indexedPtr);
SDLSurface::SDLDestroySurface($dstPtr);
SDLSurface::SDLDestroySurface($altPtr);
SDLSurface::SDLDestroyPalette($palPtr);
SDLSurface::SDLDestroySurface($ptr);
pass('Destroyed surfaces and palette');
SDL::SDLQuit();
pass('SDL_Quit');

section('Summary');
if ($errors === 0) {
    echo "  All surface checks passed.\n\n";
    exit(0);
}

echo "  {$errors} check(s) FAILED.\n\n";
exit(1);
