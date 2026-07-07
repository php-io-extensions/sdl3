# php-sdl3

[![PHP](https://img.shields.io/badge/php-%E2%89%A5%208.2-777bb4?logo=php&logoColor=white)](https://www.php.net)
[![SDL3](https://img.shields.io/badge/SDL3-%E2%89%A5%203.4.0-1d4ed8)](https://www.libsdl.org/)
[![Built with Zephir](https://img.shields.io/badge/built%20with-Zephir-ff6a00)](https://zephir-lang.com/)
[![Platform](https://img.shields.io/badge/platform-linux%20%7C%20macOS-lightgrey)](#requirements)
[![License: MIT](https://img.shields.io/badge/license-MIT-green)](#license)

> PHP extension for SDL3 — built with [Zephir](https://zephir-lang.com/), installable via [PHP PIE](https://github.com/php/pie).

`sdl3` exposes SDL3's core, video, render, surface, timer, and event APIs to
PHP 8.2+ as a set of namespaced classes under `Sdl3\SDL\…`. The extension links
against the system `libSDL3`, so it is as fast as a native SDL3 program and
supports both hardware-accelerated windows and the headless software renderer.

---

## Table of contents

- [Requirements](#requirements)
- [Installation](#installation)
  - [Via PHP PIE (recommended)](#via-php-pie-recommended)
  - [Platform installers](#platform-installers)
  - [Manual build with `phpize`](#manual-build-with-phpize)
- [Verifying the install](#verifying-the-install)
- [Quick start](#quick-start)
- [API reference](#api-reference)
- [License](#license)

---

## Requirements

| Component            | Minimum version | Notes                                                                 |
| -------------------- | --------------- | --------------------------------------------------------------------- |
| PHP                  | 8.2             | ZTS and NTS builds both supported.                                    |
| SDL3                 | 3.4.0           | Must be discoverable via `pkg-config sdl3` or the usual search paths. |
| OS                   | Linux / macOS   | Windows is not currently supported.                                   |
| Compiler             | C11 toolchain   | `gcc`, `clang`, or Apple Clang.                                       |
| `php-dev` / `phpize` | matches PHP     | Required for any build path that is not PIE.                          |

Tested on macOS (Apple Silicon + Intel), Debian Trixie, Raspberry Pi OS
(arm64 / armhf), and NVIDIA JetPack 6 (Jetson Orin).

---

## Installation

### Via PHP PIE (recommended)

PIE reads the `php-ext` block from `composer.json` and runs the full build
pipeline (phpize → configure → make → install) on your behalf:

```bash
pie install php-io-extensions/sdl3
```

PIE will invoke the `--enable-sdl3` configure option automatically. Make sure
SDL3 ≥ 3.4.0 is already installed on the system (see the platform installers
below if it is not).

### Platform installers

Three installer scripts live at the repository root. They install SDL3 if it
is missing, then build and enable the extension for every available PHP SAPI.

**macOS** (Homebrew):

```bash
bash install-macos.sh
```

**Debian Trixie / Raspberry Pi OS** (amd64, arm64, armhf):

```bash
bash install-debian-trixie.sh
```

**JetPack 6 / Ubuntu 22.04** (builds SDL3 from source, since apt ships no
compatible version):

```bash
bash install-jetpack6.sh
```

Each script writes a full build log to `./build.log` and prints concise
failure diagnostics if anything goes wrong.

### Manual build with `phpize`

For full control, build from the pre-generated C source in `ext/`:

```bash
cd ext
phpize
./configure --enable-sdl3
make -j"$(nproc 2>/dev/null || sysctl -n hw.logicalcpu)"
sudo make install
```

Then enable it for the CLI (and any other SAPI you use) by adding
`extension=sdl3.so` to the appropriate `php.ini` file, or drop a file into
your distribution's conf.d directory:

```ini
; /etc/php/8.3/cli/conf.d/20-sdl3.ini
extension=sdl3.so
```

If SDL3 is installed in a non-standard prefix, export
`PKG_CONFIG_PATH=/usr/local/lib/pkgconfig` (or the equivalent) before running
`./configure`.

---

## Verifying the install

Run the bundled proof-of-work script — it exercises the full surface and
software-renderer pipeline headlessly, so it works without a display server:

```bash
php examples/proof_of_work.php
```

Expected tail of the output:

```
── Summary ──
  All checks passed — sdl3 extension is working correctly.
```

A one-liner sanity check:

```bash
php -r 'echo Sdl3\SDL\SDL::SDLGetPlatform(), PHP_EOL;'
```

---

## Quick start

```php
<?php
use Sdl3\SDL\SDL;
use Sdl3\SDL\Video\SDLVideo;
use Sdl3\SDL\Render\SDLRender;
use Sdl3\SDL\Events\SDLEvents;

const SDL_INIT_VIDEO = 0x20;
const SDL_EVENT_QUIT = 0x100;

SDL::SDLInit(SDL_INIT_VIDEO);

[$window, $renderer] = array_values(
    SDLVideo::SDLCreateWindowAndRenderer('Hello SDL3', 640, 480, 0)
);

$running = true;
while ($running) {
    while (($ev = SDLEvents::SDLPollEvent()) !== null) {
        if (($ev['type'] ?? 0) === SDL_EVENT_QUIT) {
            $running = false;
        }
    }

    SDLRender::SDLSetRenderDrawColor($renderer, 30, 30, 60, 255);
    SDLRender::SDLRenderClear($renderer);
    SDLRender::SDLSetRenderDrawColor($renderer, 255, 200, 0, 255);
    SDLRender::SDLRenderDebugText($renderer, 20.0, 20.0, 'Hello from PHP + SDL3!');
    SDLRender::SDLRenderPresent($renderer);
}

SDLRender::SDLDestroyRenderer($renderer);
SDLVideo::SDLDestroyWindow($window);
SDL::SDLQuit();
```

See `examples/proof_of_work.php` for a headless surface/renderer example.

---

## API reference

All classes live under the `Sdl3\SDL` namespace. The PHP stubs that drive your
IDE's autocomplete are published under `ide/0.2.0/` — this reference mirrors
them exactly.

### `Sdl3\SDL\SDL` — lifecycle, version, platform

| Method                                                                                      | Returns   |
| -------------------------------------------------------------------------------------------- | --------- |
| `SDLInit(int $flags)`                                                                        | `bool`    |
| `SDLInitSubSystem(int $flags)`                                                               | `bool`    |
| `SDLWasInit(int $flags)`                                                                     | `int`     |
| `SDLQuit()`                                                                                  | `void`    |
| `SDLQuitSubSystem(int $flags)`                                                               | `void`    |
| `SDLExitProcess(int $exitcode)`                                                              | `void`    |
| `SDLGetPixelFormatDetails(int $format)`                                                      | `array`   |
| `SDLGetRGBA(int $pixel, int $format_ptr, mixed $palette_ptr = null)`                         | `array`   |
| `SDLMapRGBA(int $format_ptr, mixed $palette_ptr, int $r, int $g, int $b, int $a)`            | `int`     |
| `SDLGetSandbox()`                                                                            | `int`     |
| `SDLGetVersion()`                                                                            | `int`     |
| `SDLGetRevision()`                                                                           | `string`  |
| `SDLGetPlatform()`                                                                           | `string`  |
| `SDLIsTablet()`                                                                              | `bool`    |
| `SDLIsTV()`                                                                                  | `bool`    |
| `SDLSetAppMetadata(string $appname, string $appversion, string $appidentifier)`              | `bool`    |
| `SDLSetAppMetadataProperty(string $name, string $value)`                                     | `bool`    |
| `SDLGetAppMetadataProperty(string $name)`                                                    | `string`  |
| `SDLSetMainReady()`                                                                          | `void`    |
| `SDLIsMainThread()`                                                                          | `bool`    |
| `SDLRand(int $n)`                                                                            | `int`     |
| `SDLRandf()`                                                                                 | `float`   |

`SDLGetVersion()` returns SDL's packed integer: `major = v / 1_000_000`,
`minor = (v / 1_000) % 1_000`, `patch = v % 1_000`.

### `Sdl3\SDL\SDLError` — error handling

| Method                          | Returns  |
| ------------------------------- | -------- |
| `SDLGetError()`                 | `string` |
| `SDLSetError(string $message)`  | `bool`   |
| `SDLOutOfMemory()`              | `bool`   |
| `SDLClearError()`               | `bool`   |

### `Sdl3\SDL\Surface\SDLSurface` — surfaces & pixel operations

| Method                                                                                       | Returns |
| -------------------------------------------------------------------------------------------- | ------- |
| `SDLCreateSurface(int $width, int $height, int $format)`                                     | `array` |
| `SDLCreateSurfaceFrom(int $width, int $height, int $format, string $pixels, int $pitch)`     | `array` |
| `SDLDuplicateSurface(int $surface)`                                                          | `array` |
| `SDLConvertSurface(int $surface, int $format)`                                               | `array` |
| `SDLConvertSurfaceAndColorspace(int $surface, int $format, mixed $palette = null, int $colorspace = 0, int $props = 0)` | `array` |
| `SDLScaleSurface(int $surface, int $width, int $height, int $scaleMode)`                     | `array` |
| `SDLRotateSurface(int $surface, float $angle)`                                               | `array` |
| `SDLLoadSurface(string $file)`                                                               | `array` |
| `SDLLoadPNG(string $file)` / `SDLLoadBMP(string $file)`                                      | `array` |
| `SDLSavePNG(int $surface, string $file)` / `SDLSaveBMP(int $surface, string $file)`          | `bool`  |
| `SDLGetSurfaceProperties(int $surface)`                                                        | `int`   |
| `SDLGetSurfaceColorspace(int $surface)` / `SDLSetSurfaceColorspace(int $surface, int $cs)`   | `int` / `bool` |
| `SDLGetSurfacePalette(int $surface)` / `SDLCreateSurfacePalette(int $surface)`               | `array` |
| `SDLSetSurfacePalette(int $surface, int $palette)`                                           | `bool`  |
| `SDLCreatePalette(int $ncolors)` / `SDLDestroyPalette(int $palette)`                         | `array` / `void` |
| `SDLSetPaletteColors(int $palette, array $colors, int $first, int $count)`                    | `bool`  |
| `SDLGetPixelFormatName(int $format)`                                                         | `string` |
| `SDLGetMasksForPixelFormat(int $format)` / `SDLGetPixelFormatForMasks(...)`                    | `array` / `int` |
| `SDLGetRGB(int $pixel, int $format, mixed $palette = null)`                                  | `array` |
| `SDLMapRGB(int $format, int $palette, int $r, int $g, int $b)`                              | `int`   |
| `SDLMapSurfaceRGB(int $surface, int $r, int $g, int $b)` / `SDLMapSurfaceRGBA(...)`          | `int`   |
| `SDLBlitSurface(int $src, int $dst, mixed $srcrect = null, mixed $dstrect = null)`           | `bool`  |
| `SDLBlitSurfaceScaled(...)` / `SDLBlitSurfaceTiled(...)` / `SDLBlitSurface9Grid(...)`          | `bool`  |
| `SDLBlitSurfaceUnchecked(...)` / `SDLStretchSurface(...)`                                    | `bool`  |
| `SDLFillSurfaceRect(int $surface, int $color, mixed $rect = null)`                            | `bool`  |
| `SDLFillSurfaceRects(int $surface, array $rects, int $color)`                                | `bool`  |
| `SDLClearSurface(int $surface, float $r, float $g, float $b, float $a)`                      | `bool`  |
| `SDLSetSurfaceRLE(...)` / `SDLSetSurfaceColorKey(...)` / `SDLSetSurfaceColorMod(...)`         | `bool`  |
| `SDLSetSurfaceAlphaMod(...)` / `SDLSetSurfaceBlendMode(...)` / `SDLSetSurfaceClipRect(...)`  | `bool`  |
| `SDLGetSurface*Mod/BlendMode/ClipRect/ColorKey(...)`                                         | `array` |
| `SDLSurfaceHasRLE(...)` / `SDLSurfaceHasColorKey(...)` / `SDLSurfaceHasAlternateImages(...)` | `bool`  |
| `SDLAddSurfaceAlternateImage(...)` / `SDLGetSurfaceImages(...)` / `SDLRemoveSurfaceAlternateImages(...)` | `bool`/`array`/`void` |
| `SDLFlipSurface(int $surface, int $flip)`                                                    | `bool`  |
| `SDLConvertPixels(...)` / `SDLConvertPixelsAndColorspace(...)`                               | `string` |
| `SDLPremultiplyAlpha(...)` / `SDLPremultiplySurfaceAlpha(...)`                              | `string`/`bool` |
| `SDLReadSurfacePixel(...)` / `SDLWriteSurfacePixel(...)` (+ float variants)                  | `array`/`bool` |
| `SDLLockSurface(int $surface)` / `SDLUnlockSurface(int $surface)`                            | `bool`/`void` |
| `SDLDestroySurface(int $surface)`                                                            | `void`  |
| `SDLSurfaceToBlackAndWhite(int $surface)`                                                    | `void`  |
| `SDLWriteSurfacePixelAt(int $surface, int $x, int $y, int $pixel)` *(legacy helper)*         | `bool`  |
| `SDLWriteSurfacePixels(int $surface, array $data)` / `SDLReadSurfacePixels(int $surface)`   | `bool`/`array` |

`SDLCreateSurface` returns `['ptr' => int, 'w' => int, 'h' => int, 'pitch' => int, …]`.
Getters with out-params return `['result' => bool, …]`. Binary pixel buffers use PHP
`string` (`SDLConvertPixels`, `SDLCreateSurfaceFrom`). `*_IO` loaders/savers are excluded
(no `SDL_IOStream` binding yet).

Proof: `php examples/proof_surface.php` (headless create/mutate/save/reload round-trip).

### `Sdl3\SDL\Render\SDLRender` — renderer & drawing primitives

| Method                                                                                                       | Returns |
| ------------------------------------------------------------------------------------------------------------ | ------- |
| `SDLCreateRenderer(int $window, mixed $name = null)`                                                         | `int`   |
| `SDLCreateSoftwareRenderer(int $surface)`                                                                    | `int`   |
| `SDLRenderClear(int $renderer)`                                                                              | `void`  |
| `SDLRenderPresent(int $renderer)`                                                                            | `bool`  |
| `SDLRenderTexture(int $renderer, int $texture, mixed $srcrect = null, mixed $dstrect = null)`               | `bool`  |
| `SDLRenderTextureRotated(int $renderer, int $texture, float $angle, int $flip, …)`                           | `bool`  |
| `SDLRenderTextureAffine(int $renderer, int $texture, mixed $origin, mixed $right, mixed $down, …)`           | `bool`  |
| `SDLSetRenderDrawColor(int $renderer, int $r, int $g, int $b, int $a)`                                       | `bool`  |
| `SDLSetRenderDrawColorFloat(int $renderer, float $r, float $g, float $b, float $a)`                          | `bool`  |
| `SDLCreateTexture(int $renderer, int $format, int $access, int $w, int $h)`                                  | `array` |
| `SDLCreateTextureFromSurface(int $renderer, int $surface)`                                                   | `array` |
| `SDLLockTextureToSurface(int $texture, mixed $rect = null)`                                                  | `array` |
| `SDLUnlockTexture(int $texture)`                                                                             | `void`  |
| `SDLSetTextureColorModFloat(int $texture, float $r, float $g, float $b)`                                    | `bool`  |
| `SDLSetTextureScaleMode(int $texture, int $scaleMode)`                                                       | `bool`  |
| `SDLGetTextureSize(int $texture)`                                                                            | `array` |
| `SDLSetRenderLogicalPresentation(int $renderer, int $w, int $h, int $mode)`                                  | `bool`  |
| `SDLDestroyRenderer(int $renderer)`                                                                          | `void`  |
| `SDLDestroyTexture(int $texture)`                                                                            | `void`  |
| `SDLRenderFillRect(int $renderer, mixed $rect = null)`                                                       | `bool`  |
| `SDLRenderFillRects(int $renderer, array $rects, int $count)`                                                | `bool`  |
| `SDLRenderRect(int $renderer, mixed $rect = null)`                                                           | `bool`  |
| `SDLRenderRects(int $renderer, array $rects, int $count)`                                                    | `bool`  |
| `SDLRenderLine(int $renderer, float $x1, float $y1, float $x2, float $y2)`                                   | `bool`  |
| `SDLRenderLines(int $renderer, array $points, int $count)`                                                   | `bool`  |
| `SDLRenderPoints(int $renderer, array $points, int $count)`                                                  | `bool`  |
| `SDLRenderGeometry(int $renderer, int $texture, array $vertices, int $num_vertices, int $num_indices, …)`    | `bool`  |
| `SDLRenderReadPixels(int $renderer, mixed $rect = null)`                                                     | `array` |
| `SDLUpdateTextureFromSurface(int $texture, int $surface)`                                                    | `bool`  |
| `SDLRenderDebugText(int $renderer, float $x, float $y, string $str)`                                         | `bool`  |
| `SDLSetRenderScale(int $renderer, float $scaleX, float $scaleY)`                                             | `bool`  |
| `SDLSetRenderViewport(int $renderer, mixed $rect = null)`                                                    | `bool`  |
| `SDLSetRenderClipRect(int $renderer, mixed $rect = null)`                                                    | `bool`  |

### `Sdl3\SDL\Video\SDLVideo` — window management

| Method                                                                               | Returns |
| ------------------------------------------------------------------------------------ | ------- |
| `SDLCreateWindow(string $title, int $width, int $height, int $flags)`                | `int`   |
| `SDLCreateWindowAndRenderer(string $title, int $w, int $h, int $flags)`              | `array` |
| `SDLGetWindowSize(int $window)`                                                      | `array` |
| `SDLGetWindowPosition(int $window)`                                                  | `array` |
| `SDLGetWindowSizeInPixels(int $window)`                                              | `array` |
| `SDLGetWindowMinimumSize(int $window)`                                               | `array` |
| `SDLGetWindowMaximumSize(int $window)`                                               | `array` |
| `SDLGetWindowAspectRatio(int $window)`                                               | `array` |
| `SDLSetWindowIcon(int $window, int $surface)`                                        | `bool`  |
| `SDLDestroyWindow(int $window)`                                                      | `void`  |

`SDLCreateWindowAndRenderer` returns `['window' => int, 'renderer' => int, …]`.

### `Sdl3\SDL\Timer\SDLTimer` — timing utilities

| Method                | Returns |
| --------------------- | ------- |
| `SDLDelay(int $ms)`   | `void`  |
| `SDLGetTicks()`       | `int`   |

### `Sdl3\SDL\Events\SDLEvents` — event queue

| Method                                                                                | Returns        |
| ------------------------------------------------------------------------------------- | -------------- |
| `SDLPollEvent()`                                                                      | `array\|null`  |
| `SDLWaitEvent()`                                                                      | `array\|null`  |
| `SDLWaitEventTimeout(int $timeout_ms)`                                                | `int`          |
| `SDLReadEvent(int $ptr, string $key)`                                                 | `array`        |
| `SDLPeepEvents(int $action, int $min_type, int $max_type, int $numevents = 1)`        | `array`        |
| `SDLHasEvent(int $type)`                                                              | `bool`         |
| `SDLHasEvents(int $min_type, int $max_type)`                                          | `bool`         |
| `SDLFlushEvent(int $type)`                                                            | `void`         |
| `SDLFlushEvents(int $min_type, int $max_type)`                                        | `void`         |
| `SDLPushEvent(int $event_ptr)`                                                        | `bool`         |
| `SDLFreeEvent(int $ptr)`                                                              | `void`         |
| `SDLPumpEvents()`                                                                     | `void`         |
| `SDLGetKeyboardState()`                                                               | `array`        |

Each event array always carries a numeric `type` key matching the
`SDL_EVENT_*` enum.

### `Sdl3\SDL\Events\SDLCategories` — event filtering & metadata

| Method                                                       | Returns  |
| ------------------------------------------------------------ | -------- |
| `SDLSetEventEnabled(int $type, bool $enabled)`               | `void`   |
| `SDLEventEnabled(int $type)`                                 | `bool`   |
| `SDLRegisterEvents(int $numevents)`                          | `int`    |
| `SDLGetWindowFromEvent(int $event_ptr)`                      | `int`    |
| `SDLGetEventDescription(int $event_ptr, int $buflen = 256)`  | `string` |

### `Sdl3\SDL\Events\SDLKeyboard` — keyboard input & text entry

| Method                                                                        | Returns       |
| ----------------------------------------------------------------------------- | ------------- |
| `SDLHasKeyboard()`                                                            | `bool`        |
| `SDLGetKeyboards()`                                                           | `array`       |
| `SDLGetKeyboardNameForID(int $instance_id)`                                   | `string`      |
| `SDLGetKeyboardFocus()`                                                       | `int`         |
| `SDLGetKeyboardState()`                                                       | `array`       |
| `SDLGetModState()`                                                            | `int`         |
| `SDLSetModState(int $modstate)`                                               | `void`        |
| `SDLGetKeyFromScancode(int $scancode, int $modstate = 0, bool $key_event = true)` | `int`     |
| `SDLGetScancodeFromKey(int $key)`                                             | `array`       |
| `SDLSetScancodeName(int $scancode, string $name)`                             | `bool`        |
| `SDLGetScancodeName(int $scancode)`                                           | `string`      |
| `SDLGetScancodeFromName(string $name)`                                        | `int`         |
| `SDLGetKeyName(int $key)`                                                     | `string`      |
| `SDLGetKeyFromName(string $name)`                                             | `int`         |
| `SDLStartTextInput(int $window)`                                              | `bool`        |
| `SDLStartTextInputWithProperties(int $window, int $props)`                    | `bool`        |
| `SDLTextInputActive(int $window)`                                             | `bool`        |
| `SDLStopTextInput(int $window)`                                               | `bool`        |
| `SDLClearComposition(int $window)`                                            | `bool`        |
| `SDLSetTextInputArea(int $window, mixed $rect = null, int $cursor = 0)`       | `bool`        |
| `SDLGetTextInputArea(int $window)`                                            | `array\|null` |
| `SDLHasScreenKeyboardSupport()`                                               | `bool`        |
| `SDLScreenKeyboardShown(int $window)`                                         | `bool`        |
| `SDLReadKeyboardEvent(int $ptr)`                                              | `array`       |
| `SDLReadTextInputEvent(int $ptr)`                                             | `array`       |
| `SDLReadTextEditingEvent(int $ptr)`                                           | `array`       |
| `SDLReadTextEditingCandidatesEvent(int $ptr)`                                 | `array`       |
| `SDLReadKeyboardDeviceEvent(int $ptr)`                                        | `array`       |

### `Sdl3\SDL\Events\SDLMouse` — mouse devices, cursors, event arms

| Method                                                                               | Returns |
| ------------------------------------------------------------------------------------ | ------- |
| `SDLHasMouse()`                                                                      | `bool`  |
| `SDLGetMice()`                                                                       | `array` |
| `SDLGetMouseNameForID(int $instance_id)`                                             | `string`|
| `SDLGetMouseFocus()`                                                                 | `int`   |
| `SDLGetMouseState()`                                                                 | `array` |
| `SDLGetGlobalMouseState()`                                                           | `array` |
| `SDLGetRelativeMouseState()`                                                         | `array` |
| `SDLWarpMouseInWindow(int $window, float $x, float $y)`                              | `void`  |
| `SDLWarpMouseGlobal(float $x, float $y)`                                             | `bool`  |
| `SDLSetWindowRelativeMouseMode(int $window, bool $enabled)`                          | `bool`  |
| `SDLGetWindowRelativeMouseMode(int $window)`                                         | `bool`  |
| `SDLCaptureMouse(bool $enabled)`                                                     | `bool`  |
| `SDLCreateCursor(string $data, string $mask, int $w, int $h, int $hot_x, int $hot_y)`| `int`   |
| `SDLCreateColorCursor(int $surface, int $hot_x, int $hot_y)`                         | `int`   |
| `SDLCreateAnimatedCursor(array $frames, int $hot_x, int $hot_y)`                     | `int`   |
| `SDLCreateSystemCursor(int $id)`                                                     | `int`   |
| `SDLSetCursor(mixed $cursor = null)`                                                 | `bool`  |
| `SDLGetCursor()`                                                                     | `int`   |
| `SDLGetDefaultCursor()`                                                              | `int`   |
| `SDLDestroyCursor(int $cursor)`                                                      | `void`  |
| `SDLShowCursor()`                                                                    | `bool`  |
| `SDLHideCursor()`                                                                    | `bool`  |
| `SDLCursorVisible()`                                                                 | `bool`  |
| `SDLReadMouseDeviceEvent(int $ptr)`                                                  | `array` |
| `SDLReadMouseMotionEvent(int $ptr)`                                                  | `array` |
| `SDLReadMouseButtonEvent(int $ptr)`                                                  | `array` |
| `SDLReadMouseWheelEvent(int $ptr)`                                                   | `array` |

### `Sdl3\SDL\Events\SDLDisplayEvents` — displays & display modes

| Method                                                                                                           | Returns |
| ---------------------------------------------------------------------------------------------------------------- | ------- |
| `SDLReadDisplayEvent(int $ptr)`                                                                                  | `array` |
| `SDLGetDisplays()`                                                                                               | `array` |
| `SDLGetPrimaryDisplay()`                                                                                         | `int`   |
| `SDLGetDisplayName(int $display_id)`                                                                             | `string`|
| `SDLGetDisplayBounds(int $display_id)`                                                                           | `array` |
| `SDLGetDisplayForWindow(int $window)`                                                                            | `int`   |
| `SDLGetNaturalDisplayOrientation(int $display_id)`                                                               | `int`   |
| `SDLGetCurrentDisplayOrientation(int $display_id)`                                                               | `int`   |
| `SDLGetDisplayContentScale(int $display_id)`                                                                     | `float` |
| `SDLGetFullscreenDisplayModes(int $display_id)`                                                                  | `array` |
| `SDLGetDesktopDisplayMode(int $display_id)`                                                                      | `array` |
| `SDLGetCurrentDisplayMode(int $display_id)`                                                                      | `array` |
| `SDLGetClosestFullscreenDisplayMode(int $display_id, int $w, int $h, float $refresh_rate = 0.0, bool $include_high_density_modes = false)` | `array` |

### `Sdl3\SDL\Events\SDLClipboardEvents` — clipboard & primary selection

| Method                                       | Returns  |
| -------------------------------------------- | -------- |
| `SDLReadClipboardEvent(int $ptr)`            | `array`  |
| `SDLSetClipboardText(string $text)`          | `bool`   |
| `SDLGetClipboardText()`                      | `string` |
| `SDLHasClipboardText()`                      | `bool`   |
| `SDLSetPrimarySelectionText(string $text)`   | `bool`   |
| `SDLGetPrimarySelectionText()`               | `string` |
| `SDLHasPrimarySelectionText()`               | `bool`   |
| `SDLGetClipboardMimeTypes()`                 | `array`  |
| `SDLHasClipboardData(string $mime_type)`     | `bool`   |
| `SDLClearClipboardData()`                    | `void`   |

### `Sdl3\SDL\Events\SDLDropEvents` — drag-and-drop payloads

| Method                        | Returns |
| ----------------------------- | ------- |
| `SDLReadDropEvent(int $ptr)`  | `array` |

### `Sdl3\SDL\Events\SDLEventWatch` — filters & watchers

| Method                                            | Returns |
| ------------------------------------------------- | ------- |
| `SDLSetEventFilter(mixed $callback = null)`       | `void`  |
| `SDLGetEventFilter()`                             | `bool`  |
| `SDLAddEventWatch(mixed $callback)`               | `int`   |
| `SDLRemoveEventWatch(int $watch_id)`              | `bool`  |
| `SDLFilterEvents(mixed $callback)`                | `void`  |

### `Sdl3\SDL\Events\SDLQuit` — quit event payload

| Method                         | Returns |
| ------------------------------ | ------- |
| `SDLReadQuitEvent(int $ptr)`   | `array` |

### `Sdl3\SDL\SDLProperties` — property bags

`SDL_PropertiesID` values are plain `int` handles. Pointer properties store
opaque handles the same way as renderers and surfaces. `SDL_SetPointerPropertyWithCleanup`
is intentionally unbound (cleanup callbacks on arbitrary pointers are unsafe from PHP).

| Method | Returns |
| ------ | ------- |
| `SDLGetGlobalProperties()` | `int` |
| `SDLCreateProperties()` | `int` |
| `SDLCopyProperties(int $src, int $dst)` | `bool` |
| `SDLLockProperties(int $props)` | `bool` |
| `SDLUnlockProperties(int $props)` | `void` |
| `SDLSetPointerProperty(int $props, string $name, mixed $value = null)` | `bool` |
| `SDLSetStringProperty(int $props, string $name, mixed $value = null)` | `bool` |
| `SDLSetNumberProperty(int $props, string $name, int $value)` | `bool` |
| `SDLSetFloatProperty(int $props, string $name, float $value)` | `bool` |
| `SDLSetBooleanProperty(int $props, string $name, bool $value)` | `bool` |
| `SDLHasProperty(int $props, string $name)` | `bool` |
| `SDLGetPropertyType(int $props, string $name)` | `int` |
| `SDLGetPointerProperty(int $props, string $name, mixed $defaultValue = null)` | `int` |
| `SDLGetStringProperty(int $props, string $name, mixed $defaultValue = null)` | `string` |
| `SDLGetNumberProperty(int $props, string $name, int $defaultValue)` | `int` |
| `SDLGetFloatProperty(int $props, string $name, float $defaultValue)` | `float` |
| `SDLGetBooleanProperty(int $props, string $name, bool $defaultValue)` | `bool` |
| `SDLClearProperty(int $props, string $name)` | `bool` |
| `SDLEnumerateProperties(int $props, mixed $callback)` | `bool` |
| `SDLDestroyProperties(int $props)` | `void` |

### `Sdl3\SDL\Input\SDLJoystick` — joysticks & virtual devices

Joystick handles are opaque `int` pointers; instance IDs are plain `int` values.
GUIDs are exposed as ASCII strings via `SDL_GUIDToString`. Virtual joystick
descriptions are assoc arrays matching `SDL_VirtualJoystickDesc` field names.

| Method | Returns |
| ------ | ------- |
| `SDLLockJoysticks()` | `void` |
| `SDLUnlockJoysticks()` | `void` |
| `SDLHasJoystick()` | `bool` |
| `SDLGetJoysticks()` | `array` |
| `SDLGetJoystickNameForID(int $instance_id)` | `string` |
| `SDLGetJoystickPathForID(int $instance_id)` | `string` |
| `SDLGetJoystickPlayerIndexForID(int $instance_id)` | `int` |
| `SDLGetJoystickGUIDForID(int $instance_id)` | `string` |
| `SDLGetJoystickVendorForID(int $instance_id)` | `int` |
| `SDLGetJoystickProductForID(int $instance_id)` | `int` |
| `SDLGetJoystickProductVersionForID(int $instance_id)` | `int` |
| `SDLGetJoystickTypeForID(int $instance_id)` | `int` |
| `SDLOpenJoystick(int $instance_id)` | `int` |
| `SDLGetJoystickFromID(int $instance_id)` | `int` |
| `SDLGetJoystickFromPlayerIndex(int $player_index)` | `int` |
| `SDLAttachVirtualJoystick(array $desc)` | `int` |
| `SDLDetachVirtualJoystick(int $instance_id)` | `bool` |
| `SDLIsJoystickVirtual(int $instance_id)` | `bool` |
| `SDLSetJoystickVirtualAxis(int $joystick, int $axis, int $value)` | `bool` |
| `SDLSetJoystickVirtualBall(int $joystick, int $ball, int $xrel, int $yrel)` | `bool` |
| `SDLSetJoystickVirtualButton(int $joystick, int $button, bool $down)` | `bool` |
| `SDLSetJoystickVirtualHat(int $joystick, int $hat, int $value)` | `bool` |
| `SDLSetJoystickVirtualTouchpad(int $joystick, int $touchpad, int $finger, bool $down, float $x, float $y, float $pressure)` | `bool` |
| `SDLSendJoystickVirtualSensorData(int $joystick, int $type, int $sensor_timestamp, array $data)` | `bool` |
| `SDLGetJoystickProperties(int $joystick)` | `int` |
| `SDLGetJoystickName(int $joystick)` | `string` |
| `SDLGetJoystickPath(int $joystick)` | `string` |
| `SDLGetJoystickPlayerIndex(int $joystick)` | `int` |
| `SDLSetJoystickPlayerIndex(int $joystick, int $player_index)` | `bool` |
| `SDLGetJoystickGUID(int $joystick)` | `string` |
| `SDLGetJoystickVendor(int $joystick)` | `int` |
| `SDLGetJoystickProduct(int $joystick)` | `int` |
| `SDLGetJoystickProductVersion(int $joystick)` | `int` |
| `SDLGetJoystickFirmwareVersion(int $joystick)` | `int` |
| `SDLGetJoystickSerial(int $joystick)` | `string` |
| `SDLGetJoystickType(int $joystick)` | `int` |
| `SDLGetJoystickGUIDInfo(string $guid)` | `array` |
| `SDLJoystickConnected(int $joystick)` | `bool` |
| `SDLGetJoystickID(int $joystick)` | `int` |
| `SDLGetNumJoystickAxes(int $joystick)` | `int` |
| `SDLGetNumJoystickBalls(int $joystick)` | `int` |
| `SDLGetNumJoystickHats(int $joystick)` | `int` |
| `SDLGetNumJoystickButtons(int $joystick)` | `int` |
| `SDLSetJoystickEventsEnabled(bool $enabled)` | `void` |
| `SDLJoystickEventsEnabled()` | `bool` |
| `SDLUpdateJoysticks()` | `void` |
| `SDLGetJoystickAxis(int $joystick, int $axis)` | `int` |
| `SDLGetJoystickAxisInitialState(int $joystick, int $axis)` | `array` |
| `SDLGetJoystickBall(int $joystick, int $ball)` | `array` |
| `SDLGetJoystickHat(int $joystick, int $hat)` | `int` |
| `SDLGetJoystickButton(int $joystick, int $button)` | `bool` |
| `SDLRumbleJoystick(int $joystick, int $low_frequency_rumble, int $high_frequency_rumble, int $duration_ms)` | `bool` |
| `SDLRumbleJoystickTriggers(int $joystick, int $left_rumble, int $right_rumble, int $duration_ms)` | `bool` |
| `SDLSetJoystickLED(int $joystick, int $red, int $green, int $blue)` | `bool` |
| `SDLSendJoystickEffect(int $joystick, string $data)` | `bool` |
| `SDLCloseJoystick(int $joystick)` | `void` |
| `SDLGetJoystickConnectionState(int $joystick)` | `int` |
| `SDLGetJoystickPowerInfo(int $joystick)` | `array` |

### `Sdl3\SDL\Input\SDLGamepad` — gamepad mappings & standard controls

Gamepad handles are opaque `int` pointers; instance IDs are plain `int` values.
`SDL_GetGamepadBindings` returns an array of assoc arrays with `input_type`,
`output_type`, and type-specific fields (`input_button`, `input_axis`, etc.).
`SDL_GetGamepadTouchpadFinger` and `SDL_GetGamepadSensorData` return assoc
arrays. `SDL_AddGamepadMappingsFromIO` is not bound (requires `SDL_IOStream`).

| Method | Returns |
|--------|---------|
| `SDLAddGamepadMapping(string $mapping)` | `int` |
| `SDLAddGamepadMappingsFromFile(string $file)` | `int` |
| `SDLReloadGamepadMappings()` | `bool` |
| `SDLGetGamepadMappings()` | `array` |
| `SDLGetGamepadMappingForGUID(string $guid)` | `string` |
| `SDLGetGamepadMapping(int $gamepad)` | `string` |
| `SDLSetGamepadMapping(int $instance_id, mixed $mapping = null)` | `bool` |
| `SDLHasGamepad()` | `bool` |
| `SDLGetGamepads()` | `array` |
| `SDLIsGamepad(int $instance_id)` | `bool` |
| `SDLGetGamepadNameForID(int $instance_id)` | `string` |
| `SDLGetGamepadPathForID(int $instance_id)` | `string` |
| `SDLGetGamepadPlayerIndexForID(int $instance_id)` | `int` |
| `SDLGetGamepadGUIDForID(int $instance_id)` | `string` |
| `SDLGetGamepadVendorForID(int $instance_id)` | `int` |
| `SDLGetGamepadProductForID(int $instance_id)` | `int` |
| `SDLGetGamepadProductVersionForID(int $instance_id)` | `int` |
| `SDLGetGamepadTypeForID(int $instance_id)` | `int` |
| `SDLGetRealGamepadTypeForID(int $instance_id)` | `int` |
| `SDLGetGamepadMappingForID(int $instance_id)` | `string` |
| `SDLOpenGamepad(int $instance_id)` | `int` |
| `SDLGetGamepadFromID(int $instance_id)` | `int` |
| `SDLGetGamepadFromPlayerIndex(int $player_index)` | `int` |
| `SDLGetGamepadProperties(int $gamepad)` | `int` |
| `SDLGetGamepadID(int $gamepad)` | `int` |
| `SDLGetGamepadName(int $gamepad)` | `string` |
| `SDLGetGamepadPath(int $gamepad)` | `string` |
| `SDLGetGamepadType(int $gamepad)` | `int` |
| `SDLGetRealGamepadType(int $gamepad)` | `int` |
| `SDLGetGamepadPlayerIndex(int $gamepad)` | `int` |
| `SDLSetGamepadPlayerIndex(int $gamepad, int $player_index)` | `bool` |
| `SDLGetGamepadVendor(int $gamepad)` | `int` |
| `SDLGetGamepadProduct(int $gamepad)` | `int` |
| `SDLGetGamepadProductVersion(int $gamepad)` | `int` |
| `SDLGetGamepadFirmwareVersion(int $gamepad)` | `int` |
| `SDLGetGamepadSerial(int $gamepad)` | `string` |
| `SDLGetGamepadSteamHandle(int $gamepad)` | `int` |
| `SDLGetGamepadConnectionState(int $gamepad)` | `int` |
| `SDLGetGamepadPowerInfo(int $gamepad)` | `array` |
| `SDLGamepadConnected(int $gamepad)` | `bool` |
| `SDLGetGamepadJoystick(int $gamepad)` | `int` |
| `SDLSetGamepadEventsEnabled(bool $enabled)` | `void` |
| `SDLGamepadEventsEnabled()` | `bool` |
| `SDLGetGamepadBindings(int $gamepad)` | `array` |
| `SDLUpdateGamepads()` | `void` |
| `SDLGetGamepadTypeFromString(string $str)` | `int` |
| `SDLGetGamepadStringForType(int $type)` | `string` |
| `SDLGetGamepadAxisFromString(string $str)` | `int` |
| `SDLGetGamepadStringForAxis(int $axis)` | `string` |
| `SDLGamepadHasAxis(int $gamepad, int $axis)` | `bool` |
| `SDLGetGamepadAxis(int $gamepad, int $axis)` | `int` |
| `SDLGetGamepadButtonFromString(string $str)` | `int` |
| `SDLGetGamepadStringForButton(int $button)` | `string` |
| `SDLGamepadHasButton(int $gamepad, int $button)` | `bool` |
| `SDLGetGamepadButton(int $gamepad, int $button)` | `bool` |
| `SDLGetGamepadButtonLabelForType(int $type, int $button)` | `int` |
| `SDLGetGamepadButtonLabel(int $gamepad, int $button)` | `int` |
| `SDLGetNumGamepadTouchpads(int $gamepad)` | `int` |
| `SDLGetNumGamepadTouchpadFingers(int $gamepad, int $touchpad)` | `int` |
| `SDLGetGamepadTouchpadFinger(int $gamepad, int $touchpad, int $finger)` | `array` |
| `SDLGamepadHasSensor(int $gamepad, int $type)` | `bool` |
| `SDLSetGamepadSensorEnabled(int $gamepad, int $type, bool $enabled)` | `bool` |
| `SDLGamepadSensorEnabled(int $gamepad, int $type)` | `bool` |
| `SDLGetGamepadSensorDataRate(int $gamepad, int $type)` | `float` |
| `SDLGetGamepadSensorData(int $gamepad, int $type, int $num_values)` | `array` |
| `SDLRumbleGamepad(int $gamepad, int $low_frequency_rumble, int $high_frequency_rumble, int $duration_ms)` | `bool` |
| `SDLRumbleGamepadTriggers(int $gamepad, int $left_rumble, int $right_rumble, int $duration_ms)` | `bool` |
| `SDLSetGamepadLED(int $gamepad, int $red, int $green, int $blue)` | `bool` |
| `SDLSendGamepadEffect(int $gamepad, string $data)` | `bool` |
| `SDLCloseGamepad(int $gamepad)` | `void` |
| `SDLGetGamepadAppleSFSymbolsNameForButton(int $gamepad, int $button)` | `string` |
| `SDLGetGamepadAppleSFSymbolsNameForAxis(int $gamepad, int $axis)` | `string` |

### `Sdl3\SDL\Audio\SDLAudio` — devices, streams & binary I/O

Audio device and stream handles are opaque `int` pointers. `SDL_AudioSpec` is
an assoc array `["format" => int, "channels" => int, "freq" => int]`.
Push/pull I/O uses PHP binary strings. `SDL_LoadWAV_IO` is not bound (requires
`SDL_IOStream`). Stream/device callbacks use the bridge pattern (advanced).

| Method | Returns |
| ------ | ------- |
| `SDLGetNumAudioDrivers()` | `int` |
| `SDLGetAudioDriver(int $index)` | `string` |
| `SDLGetCurrentAudioDriver()` | `string` |
| `SDLGetAudioPlaybackDevices()` | `array` |
| `SDLGetAudioRecordingDevices()` | `array` |
| `SDLGetAudioDeviceName(int $devid)` | `string` |
| `SDLGetAudioDeviceFormat(int $devid)` | `array` |
| `SDLGetAudioDeviceChannelMap(int $devid)` | `array` |
| `SDLOpenAudioDevice(int $devid, mixed $spec = null)` | `int` |
| `SDLIsAudioDevicePhysical(int $devid)` | `bool` |
| `SDLIsAudioDevicePlayback(int $devid)` | `bool` |
| `SDLPauseAudioDevice(int $devid)` | `bool` |
| `SDLResumeAudioDevice(int $devid)` | `bool` |
| `SDLAudioDevicePaused(int $devid)` | `bool` |
| `SDLGetAudioDeviceGain(int $devid)` | `float` |
| `SDLSetAudioDeviceGain(int $devid, float $gain)` | `bool` |
| `SDLCloseAudioDevice(int $devid)` | `void` |
| `SDLBindAudioStreams(int $devid, array $streams)` | `bool` |
| `SDLBindAudioStream(int $devid, int $stream)` | `bool` |
| `SDLUnbindAudioStreams(array $streams)` | `void` |
| `SDLUnbindAudioStream(int $stream)` | `void` |
| `SDLGetAudioStreamDevice(int $stream)` | `int` |
| `SDLCreateAudioStream(mixed $src_spec, mixed $dst_spec)` | `int` |
| `SDLGetAudioStreamProperties(int $stream)` | `int` |
| `SDLGetAudioStreamFormat(int $stream)` | `array` |
| `SDLSetAudioStreamFormat(int $stream, mixed $src_spec, mixed $dst_spec)` | `bool` |
| `SDLGetAudioStreamFrequencyRatio(int $stream)` | `float` |
| `SDLSetAudioStreamFrequencyRatio(int $stream, float $ratio)` | `bool` |
| `SDLGetAudioStreamGain(int $stream)` | `float` |
| `SDLSetAudioStreamGain(int $stream, float $gain)` | `bool` |
| `SDLGetAudioStreamInputChannelMap(int $stream)` | `array` |
| `SDLGetAudioStreamOutputChannelMap(int $stream)` | `array` |
| `SDLSetAudioStreamInputChannelMap(int $stream, array $chmap)` | `bool` |
| `SDLSetAudioStreamOutputChannelMap(int $stream, array $chmap)` | `bool` |
| `SDLPutAudioStreamData(int $stream, string $data)` | `bool` |
| `SDLPutAudioStreamDataNoCopy(int $stream, string $data, mixed $callback = null)` | `bool` |
| `SDLPutAudioStreamPlanarData(int $stream, array $channel_buffers, int $num_channels, int $num_samples)` | `bool` |
| `SDLGetAudioStreamData(int $stream, int $len)` | `string` |
| `SDLGetAudioStreamAvailable(int $stream)` | `int` |
| `SDLGetAudioStreamQueued(int $stream)` | `int` |
| `SDLFlushAudioStream(int $stream)` | `bool` |
| `SDLClearAudioStream(int $stream)` | `bool` |
| `SDLPauseAudioStreamDevice(int $stream)` | `bool` |
| `SDLResumeAudioStreamDevice(int $stream)` | `bool` |
| `SDLAudioStreamDevicePaused(int $stream)` | `bool` |
| `SDLLockAudioStream(int $stream)` | `bool` |
| `SDLUnlockAudioStream(int $stream)` | `bool` |
| `SDLSetAudioStreamGetCallback(int $stream, mixed $callback = null)` | `bool` |
| `SDLSetAudioStreamPutCallback(int $stream, mixed $callback = null)` | `bool` |
| `SDLDestroyAudioStream(int $stream)` | `void` |
| `SDLOpenAudioDeviceStream(int $devid, mixed $spec = null, mixed $callback = null)` | `int` |
| `SDLSetAudioPostmixCallback(int $devid, mixed $callback = null)` | `bool` |
| `SDLLoadWAV(string $path)` | `array` |
| `SDLMixAudio(string $dst, string $src, int $format, int $len, float $volume)` | `string` |
| `SDLConvertAudioSamples(mixed $src_spec, string $src_data, int $src_len, mixed $dst_spec)` | `array` |
| `SDLGetAudioFormatName(int $format)` | `string` |
| `SDLGetSilenceValueForFormat(int $format)` | `int` |

### `Sdl3\SDL\Dialog\SDLDialog` — async native file dialogs

All four functions are asynchronous; callbacks fire during event pumping.
Filters are PHP arrays of `["name" => ..., "pattern" => ...]`. The PHP
callback receives `(?array $filelist, int $filter_index)` — `null` on error,
`[]` on cancel.

| Method | Returns |
| ------ | ------- |
| `SDLShowOpenFileDialog(mixed $callback, int $window = 0, mixed $filters = null, mixed $default_location = null, bool $allow_many = false)` | `void` |
| `SDLShowSaveFileDialog(mixed $callback, int $window = 0, mixed $filters = null, mixed $default_location = null)` | `void` |
| `SDLShowOpenFolderDialog(mixed $callback, int $window = 0, mixed $default_location = null, bool $allow_many = false)` | `void` |
| `SDLShowFileDialogWithProperties(int $type, mixed $callback, int $props)` | `void` |

### `Sdl3\SDL\Gpu\SDLGPU` — modern GPU API (render, compute, copy)

Complete binding of `SDL_gpu.h` plus the GPU render-state functions from
`SDL_render.h`. All opaque objects (device, buffers, textures, samplers,
shaders, pipelines, command buffers, passes, fences, render states) are
opaque `int` handles. Creation-info structs and pass descriptors are assoc
arrays whose keys mirror the C struct field names exactly (e.g.
`SDL_GPUBufferCreateInfo` → `["usage" => int, "size" => int, "props" => int]`);
nested struct lists (color targets, vertex attributes, bindings) are arrays
of assoc arrays. Shader bytecode/source and uniform data travel as PHP binary
strings. `SDLMapGPUTransferBuffer` returns the raw mapped address as an
opaque int; prefer the `writeToGPUTransferBuffer` / `readFromGPUTransferBuffer`
helpers, which handle the map → copy → unmap cycle with binary strings.
`SDL_GDKSuspendGPU` / `SDL_GDKResumeGPU` throw outside GDK (Xbox) builds.

| Method | Returns |
| ------ | ------- |
| `SDLGPUSupportsShaderFormats(int $format_flags, mixed $name = null)` | `bool` |
| `SDLGPUSupportsProperties(int $props)` | `bool` |
| `SDLCreateGPUDevice(int $format_flags, bool $debug_mode, mixed $name = null)` | `int` |
| `SDLCreateGPUDeviceWithProperties(int $props)` | `int` |
| `SDLDestroyGPUDevice(int $device)` | `void` |
| `SDLGetNumGPUDrivers()` | `int` |
| `SDLGetGPUDriver(int $index)` | `string` |
| `SDLGetGPUDeviceDriver(int $device)` | `string` |
| `SDLGetGPUShaderFormats(int $device)` | `int` |
| `SDLGetGPUDeviceProperties(int $device)` | `int` |
| `SDLCreateGPUComputePipeline(int $device, mixed $createinfo)` | `int` |
| `SDLCreateGPUGraphicsPipeline(int $device, mixed $createinfo)` | `int` |
| `SDLCreateGPUSampler(int $device, mixed $createinfo)` | `int` |
| `SDLCreateGPUShader(int $device, mixed $createinfo)` | `int` |
| `SDLCreateGPUTexture(int $device, mixed $createinfo)` | `int` |
| `SDLCreateGPUBuffer(int $device, mixed $createinfo)` | `int` |
| `SDLCreateGPUTransferBuffer(int $device, mixed $createinfo)` | `int` |
| `SDLSetGPUBufferName(int $device, int $buffer, string $text)` | `void` |
| `SDLSetGPUTextureName(int $device, int $texture, string $text)` | `void` |
| `SDLInsertGPUDebugLabel(int $command_buffer, string $text)` | `void` |
| `SDLPushGPUDebugGroup(int $command_buffer, string $name)` | `void` |
| `SDLPopGPUDebugGroup(int $command_buffer)` | `void` |
| `SDLReleaseGPUTexture(int $device, int $texture)` | `void` |
| `SDLReleaseGPUSampler(int $device, int $sampler)` | `void` |
| `SDLReleaseGPUBuffer(int $device, int $buffer)` | `void` |
| `SDLReleaseGPUTransferBuffer(int $device, int $transfer_buffer)` | `void` |
| `SDLReleaseGPUComputePipeline(int $device, int $compute_pipeline)` | `void` |
| `SDLReleaseGPUShader(int $device, int $shader)` | `void` |
| `SDLReleaseGPUGraphicsPipeline(int $device, int $graphics_pipeline)` | `void` |
| `SDLAcquireGPUCommandBuffer(int $device)` | `int` |
| `SDLPushGPUVertexUniformData(int $command_buffer, int $slot_index, string $data)` | `void` |
| `SDLPushGPUFragmentUniformData(int $command_buffer, int $slot_index, string $data)` | `void` |
| `SDLPushGPUComputeUniformData(int $command_buffer, int $slot_index, string $data)` | `void` |
| `SDLBeginGPURenderPass(int $command_buffer, mixed $color_target_infos, mixed $depth_stencil_target_info = null)` | `int` |
| `SDLBindGPUGraphicsPipeline(int $render_pass, int $graphics_pipeline)` | `void` |
| `SDLSetGPUViewport(int $render_pass, mixed $viewport)` | `void` |
| `SDLSetGPUScissor(int $render_pass, mixed $scissor)` | `void` |
| `SDLSetGPUBlendConstants(int $render_pass, mixed $blend_constants)` | `void` |
| `SDLSetGPUStencilReference(int $render_pass, int $reference)` | `void` |
| `SDLBindGPUVertexBuffers(int $render_pass, int $first_slot, mixed $bindings)` | `void` |
| `SDLBindGPUIndexBuffer(int $render_pass, mixed $binding, int $index_element_size)` | `void` |
| `SDLBindGPUVertexSamplers(int $render_pass, int $first_slot, mixed $bindings)` | `void` |
| `SDLBindGPUVertexStorageTextures(int $render_pass, int $first_slot, mixed $storage_textures)` | `void` |
| `SDLBindGPUVertexStorageBuffers(int $render_pass, int $first_slot, mixed $storage_buffers)` | `void` |
| `SDLBindGPUFragmentSamplers(int $render_pass, int $first_slot, mixed $bindings)` | `void` |
| `SDLBindGPUFragmentStorageTextures(int $render_pass, int $first_slot, mixed $storage_textures)` | `void` |
| `SDLBindGPUFragmentStorageBuffers(int $render_pass, int $first_slot, mixed $storage_buffers)` | `void` |
| `SDLDrawGPUIndexedPrimitives(int $render_pass, int $num_indices, int $num_instances, int $first_index, int $vertex_offset, int $first_instance)` | `void` |
| `SDLDrawGPUPrimitives(int $render_pass, int $num_vertices, int $num_instances, int $first_vertex, int $first_instance)` | `void` |
| `SDLDrawGPUPrimitivesIndirect(int $render_pass, int $buffer, int $offset, int $draw_count)` | `void` |
| `SDLDrawGPUIndexedPrimitivesIndirect(int $render_pass, int $buffer, int $offset, int $draw_count)` | `void` |
| `SDLEndGPURenderPass(int $render_pass)` | `void` |
| `SDLBeginGPUComputePass(int $command_buffer, mixed $storage_texture_bindings = null, mixed $storage_buffer_bindings = null)` | `int` |
| `SDLBindGPUComputePipeline(int $compute_pass, int $compute_pipeline)` | `void` |
| `SDLBindGPUComputeSamplers(int $compute_pass, int $first_slot, mixed $bindings)` | `void` |
| `SDLBindGPUComputeStorageTextures(int $compute_pass, int $first_slot, mixed $storage_textures)` | `void` |
| `SDLBindGPUComputeStorageBuffers(int $compute_pass, int $first_slot, mixed $storage_buffers)` | `void` |
| `SDLDispatchGPUCompute(int $compute_pass, int $groupcount_x, int $groupcount_y, int $groupcount_z)` | `void` |
| `SDLDispatchGPUComputeIndirect(int $compute_pass, int $buffer, int $offset)` | `void` |
| `SDLEndGPUComputePass(int $compute_pass)` | `void` |
| `SDLMapGPUTransferBuffer(int $device, int $transfer_buffer, bool $cycle = false)` | `int` |
| `SDLUnmapGPUTransferBuffer(int $device, int $transfer_buffer)` | `void` |
| `writeToGPUTransferBuffer(int $device, int $transfer_buffer, string $data, bool $cycle = false, int $offset = 0)` | `bool` |
| `readFromGPUTransferBuffer(int $device, int $transfer_buffer, int $length, int $offset = 0)` | `string` |
| `SDLBeginGPUCopyPass(int $command_buffer)` | `int` |
| `SDLUploadToGPUTexture(int $copy_pass, mixed $source, mixed $destination, bool $cycle = false)` | `void` |
| `SDLUploadToGPUBuffer(int $copy_pass, mixed $source, mixed $destination, bool $cycle = false)` | `void` |
| `SDLCopyGPUTextureToTexture(int $copy_pass, mixed $source, mixed $destination, int $w, int $h, int $d, bool $cycle = false)` | `void` |
| `SDLCopyGPUBufferToBuffer(int $copy_pass, mixed $source, mixed $destination, int $size, bool $cycle = false)` | `void` |
| `SDLDownloadFromGPUTexture(int $copy_pass, mixed $source, mixed $destination)` | `void` |
| `SDLDownloadFromGPUBuffer(int $copy_pass, mixed $source, mixed $destination)` | `void` |
| `SDLEndGPUCopyPass(int $copy_pass)` | `void` |
| `SDLGenerateMipmapsForGPUTexture(int $command_buffer, int $texture)` | `void` |
| `SDLBlitGPUTexture(int $command_buffer, mixed $info)` | `void` |
| `SDLWindowSupportsGPUSwapchainComposition(int $device, int $window, int $swapchain_composition)` | `bool` |
| `SDLWindowSupportsGPUPresentMode(int $device, int $window, int $present_mode)` | `bool` |
| `SDLClaimWindowForGPUDevice(int $device, int $window)` | `bool` |
| `SDLReleaseWindowFromGPUDevice(int $device, int $window)` | `void` |
| `SDLSetGPUSwapchainParameters(int $device, int $window, int $swapchain_composition, int $present_mode)` | `bool` |
| `SDLSetGPUAllowedFramesInFlight(int $device, int $allowed_frames_in_flight)` | `bool` |
| `SDLGetGPUSwapchainTextureFormat(int $device, int $window)` | `int` |
| `SDLAcquireGPUSwapchainTexture(int $command_buffer, int $window)` | `array` |
| `SDLWaitForGPUSwapchain(int $device, int $window)` | `bool` |
| `SDLWaitAndAcquireGPUSwapchainTexture(int $command_buffer, int $window)` | `array` |
| `SDLSubmitGPUCommandBuffer(int $command_buffer)` | `bool` |
| `SDLSubmitGPUCommandBufferAndAcquireFence(int $command_buffer)` | `int` |
| `SDLCancelGPUCommandBuffer(int $command_buffer)` | `bool` |
| `SDLWaitForGPUIdle(int $device)` | `bool` |
| `SDLWaitForGPUFences(int $device, bool $wait_all, mixed $fences)` | `bool` |
| `SDLQueryGPUFence(int $device, int $fence)` | `bool` |
| `SDLReleaseGPUFence(int $device, int $fence)` | `void` |
| `SDLGPUTextureFormatTexelBlockSize(int $format)` | `int` |
| `SDLGPUTextureSupportsFormat(int $device, int $format, int $type, int $usage)` | `bool` |
| `SDLGPUTextureSupportsSampleCount(int $device, int $format, int $sample_count)` | `bool` |
| `SDLCalculateGPUTextureFormatSize(int $format, int $width, int $height, int $depth_or_layer_count)` | `int` |
| `SDLGetPixelFormatFromGPUTextureFormat(int $format)` | `int` |
| `SDLGetGPUTextureFormatFromPixelFormat(int $format)` | `int` |
| `SDLGDKSuspendGPU(int $device)` | `void` |
| `SDLGDKResumeGPU(int $device)` | `void` |
| `SDLCreateGPURenderer(int $device, int $window)` | `int` |
| `SDLGetGPURendererDevice(int $renderer)` | `int` |
| `SDLCreateGPURenderState(int $renderer, mixed $createinfo)` | `int` |
| `SDLSetGPURenderStateFragmentUniforms(int $state, int $slot_index, string $data)` | `bool` |
| `SDLSetGPURenderState(int $renderer, int $state = 0)` | `bool` |
| `SDLDestroyGPURenderState(int $state)` | `void` |

### Supporting / reserved classes

These classes are part of the public surface but currently ship without
methods; they are reserved for upcoming SDL3 subsystem bindings:

- `Sdl3\SDL\SDLAssert`
- `Sdl3\SDL\SDLList`
- `Sdl3\SDL\SDLLog`
- `Sdl3\SDL\SDLUtils`
- `Sdl3\SDL\Events\SDLKeymap`
- `Sdl3\SDL\Events\SDLScancodeTables`
- `Sdl3\SDL\Events\SDLWindowEvents`

---

## License

MIT © Project Saturn Studios, LLC.
