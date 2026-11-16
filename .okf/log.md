# Log

## 2026-11-15

* **`SDL_BeginGPUComputePass`, `SDL_PushGPUComputeUniformData`** bound 1:1 (SDL_gpu.h, in 3.2), after `typemap` entries for the two binding lists and the `sdl3-compute-uniform-length` site. `GpuComputeTest` dispatches two MSL kernels: one writes a storage buffer from a pushed uniform, one writes a storage texture; both read back exact. The probe for the new site passes on a probe build (SIGSEGV under libgmalloc without the refusal). 255 / 1233. Measured: SDL's Metal backend numbers a compute kernel's `[[buffer]]` slots uniform buffers first, then read-write storage buffers.

* **SDL_GPU compute, storage binds and GPU-to-GPU copies** bound 1:1 (SDL_gpu.h, in 3.2): handles `SDL_GPUComputePipeline`, `SDL_GPUComputePass`; structs `SDL_GPUComputePipelineCreateInfo`, `SDL_GPUStorageBufferReadWriteBinding`, `SDL_GPUStorageTextureReadWriteBinding`, `SDL_GPUTextureLocation`, `SDL_GPUBufferLocation`; 16 functions, listed in [bindings](api/bindings.md). `GpuComputeTest` covers them. 253 / 1233. Suite 112 passed, 8 skipped on Homebrew PHP 8.4 NTS and ZTS. Two wait on `bindings.json`: `SDL_BeginGPUComputePass` on `typemap` entries for `SDL_GPUStorageTextureReadWriteBinding*` and `SDL_GPUStorageBufferReadWriteBinding*`, and `SDL_PushGPUComputeUniformData` on a `sites` entry of its own for its length check (one id marks one site).
* **Measured**: `SDL_GPUSupportsShaderFormats` answers false for every format until video is initialised. With video up it is true for MSL and METALLIB on `metal`, SPIR-V on `vulkan`, and any of them with no name. `SDL_CreateGPUComputePipeline` with a bad kernel or a missing entry point returns NULL and logs the Metal compiler's message; `SDL_GetError()` stays empty.

## 2026-11-14

* **Software renderer and surface mods** bound 1:1 (SDL_surface.h and SDL_render.h, in 3.2): `SDL_CreateSurface`, `SDL_ConvertSurface`, `SDL_Set/GetSurfaceAlphaMod`, `SDL_Set/GetSurfaceColorMod`; handles `SDL_Renderer`, `SDL_Texture`; structs `SDL_FPoint`, `SDL_Vertex`; `SDL_CreateSoftwareRenderer`, `SDL_DestroyRenderer`, `SDL_CreateTextureFromSurface`, `SDL_DestroyTexture`, `SDL_SetTextureBlendMode`, `SDL_SetTextureScaleMode`, `SDL_SetTextureAlphaMod`, `SDL_SetTextureColorMod`, `SDL_SetRenderClipRect`, `SDL_RenderGeometry`, `SDL_FlushRenderer`. `RendererTest` covers them. 237 / 1233. Suite 107 passed, 8 skipped on Homebrew PHP 8.4 NTS and ZTS; the probe for `SDL_RenderGeometry`'s vertex count passes on a probe build (SIGSEGV under libgmalloc without the refusal).
* **Measured**: a software renderer needs no `SDL_Init()`. Drawn into a surface it rasterises a rotated textured quad with no video up. Over a transparent surface `SDL_BLENDMODE_BLEND` leaves the colour scaled by alpha (a quad at alpha 0.5 reads `80000080` for red), as the blend sums `src * a + dst * (1 - a)` without dividing by the result alpha. The software renderer takes colour and alpha from the vertices: a texture's own `SDL_SetTextureAlphaMod` and `SDL_SetTextureColorMod` succeed and change nothing in `SDL_RenderGeometry`. With no indices, `SDL_RenderGeometry` refuses a vertex count that is not a multiple of 3 ("Parameter 'num_vertices' is invalid").
* **Lifetime**: `SDL_DestroyRenderer` destroys the renderer's textures, so the renderer's handle keeps its textures and releases them with it; `SDL_DestroyTexture` drops its texture from that list. A surface a software renderer draws into must outlive the renderer. [handles](architecture/handles.md)

## 2026-11-13

* **`SDL_SetSurfaceBlendMode`, `SDL_GetSurfaceBlendMode`** bound 1:1 (SDL_surface.h, in 3.2), with the `SDL_BLENDMODE_*` constants and six more pixel formats: `ARGB32`, `ABGR32`, `RGB24`, `BGR24`, `RGB565`, `BGR565`. With `SDL_BLENDMODE_NONE` on the source, `SDL_BlitSurface` copies translucent pixels unchanged. `SurfaceBytesTest` checks NONE against BLEND, and fills and copies in the 24- and 16-bit formats. 220 / 1233.

## 2026-11-11

* **Public API, 0.11.2**: `php_sdl3_api.h` (includes `src/runtime.h`) is installed with `php_sdl3.h` into `$(php-config --include-dir)/ext/sdl3/` by both installers and by `PHP_INSTALL_HEADERS`. An extension that requires sdl3 compiles against it and boxes its handles in sdl3's registry. `sdl3_add_audio_quit_hooks(before, after)`: `SDL_QuitSubSystem` and `SDL_Quit` run the before hooks while audio is up and the after hooks once audio is down, since SDL destroys every audio stream then. `ApiHeaderTest`; suite 90 passed, 7 skipped on Homebrew PHP 8.4 NTS and ZTS. [handles](architecture/handles.md)
* **`SDL_INIT_AUDIO`, `SDL_WasInit`** bound 1:1 (SDL_init.h, in 3.2). `InitTest` brings audio up and down on the dummy output. 217 / 1233. Suite 91 passed, 7 skipped on NTS and ZTS.
* **`SDL_IOFromFile`** bound 1:1 (SDL_iostream.h, in 3.2): a path and an fopen mode; `null` and `SDL_GetError()` when SDL cannot open it. `SurfaceBytesTest` reads a file back through it. 218 / 1233. Suite 92 passed, 7 skipped on NTS and ZTS.
* **Debian installer**: `-isystem /usr/include`, not `-I`. GCC drops `-I` for a system directory, so a `/usr/local` SDL build (3.4.9 on the Pi) shadowed the distro 3.2.10 headers the library came from.

## 2026-11-06

* **`SDL_GetModState`** bound 1:1 (SDL_keyboard.h:186, in 3.2): returns the `SDL_Keymod` bits held now as an int, the `SDL_KMOD_*` constants name them. `KeyboardTest` has a behaviour test; NTS and ZTS built and installed. 216 / 1233.

* **1:1 under ext-guard** (audit 0). A build with every check off showed which calls crash. Kept, each behind `SDL3_PROBE_OFF` with a `tests/Probes` test: surface pixels shorter than pitch × height, uniform data past its string, `SDL_WriteIO` size past its string, a list's count past the list, a released `SDL_Surface`'s field getters. Dropped: "has been destroyed" for SDL calls (a released handle is NULL; SDL answers "Invalid window", "Invalid GPU device" and the like), null-address and negative-size checks, `fromPointer(0)` (null). API: the five list functions take their C count; `SDL_ReadIO(ctx, ptr, size): int`; `SDL_Vulkan_GetInstanceExtensions(?int &$count)`; `SDL_SetWindowHitTest(window, callback)`. `--enable-sdl3-probes` builds the switch. Mac, SDL 3.4.4: probe build 5 probes pass; release NTS and ZTS 49 passed, 6 skipped across the files that open no visible window. Window tests and the Pi not run yet.

## 2026-10-28

* **Version**: 0.11.0 in `PHP_SDL3_VERSION` (`php_sdl3.h`), `AGENTS.md`, README and the index; `branch-alias` `dev-main` is `0.11.x-dev`. Promoted with the Venusian 0.11 ecosystem. No API or behaviour change. Built and loaded on Homebrew PHP 8.4 NTS and ZTS (81 passed, 2 skipped each), the Pi on 8.4 ZTS (78 passed, 5 skipped) and an x86_64 8.4 NTS box (77 passed, 5 skipped; `HooksTest`'s GL context fails where that box's X session has no GL).
* **Coverage**: `scripts/support.php` writes `SUPPORT.md` and the README's API badge: every `extern SDL_DECLSPEC … SDLCALL` function of the public headers at the release-3.2.0 tag (the floor), all of SDL, bound when a stub declares the function of the same name; `SDL_test*.h` and `SDL_oldnames.h` are not read. Headers download once into `scripts/.support-cache/` (gitignored); `--check` exits 1 when the list or badge is stale. 215 / 1233 (17.4%).

## 2026-10-09


## 2026-10-08

Bound pad identity and player lights for HumanInput slice 18b: `SDL_GetGamepadSerial`, `SDL_GetJoystickSerial`, `SDL_GetGamepadPath`, `SDL_GetJoystickPath`, `SDL_Get/SetGamepadPlayerIndex`, `SDL_Get/SetJoystickPlayerIndex`. A virtual device has neither serial nor path. Measured: on the Pi without /dev/hidraw access SDL reads a DualSense through evdev with no serial; its path is the /dev/input/event node. Suite: Mac NTS and ZTS 81 passed, 2 skipped; Pi 78 passed, 5 skipped (after the path bindings too).

Bound input for HumanInput's sdl3 engine: keyboard, text and mouse events both ways with `SDL_PushEvent`, event switches, `SDL_QuitSubSystem`, keyboard focus and text input, scancodes, gamepads, joysticks and virtual joysticks with counted opens. Measured: SDL keeps a pushed text event's pointer, so the binding keeps the bytes; every `SDL_UpdateGamepads()` queues a `JOYSTICK_UPDATE_COMPLETE` even with gamepad and joystick events off, and only `SDL_SetEventEnabled` over 0x600–0x6FF stops them. Suite: Mac NTS and ZTS 78 passed, 2 skipped; Pi 75 passed, 5 skipped. Review fixes: a gamepad-only quit releases `SDL_Gamepad` handles, and a poll into an unset part throws instead of crashing (80 passed on the Mac).

GPU swapchain pacing: wait for a swapchain, wait-and-acquire, frames in flight, composition support. Suite: Homebrew PHP 8.4 NTS and ZTS 60 passed, 2 skipped; Pi 57 passed, 5 skipped under Wayland and X11.

Bound what a staged window needs from SDL 3.2, input excluded: window position, size limits, aspect ratio, safe area, border sizes, maximize/minimize/restore/sync, border/resize/stacking/focus toggles, opacity, icon, flash, PHP hit tests, screen saver, the simple message box; displays, display modes, orientation, content scale, display lookup, borderless and exclusive fullscreen; HDR and native-handle properties with string/float/boolean property access; window surface rects, surface lifetime and surface vsync; the GL swap interval getter and the GPU present-mode query; `SDL_DisplayEvent` and the remaining window and display event types; `SDL_ClearError`, `SDL_EGL_GetCurrentDisplay`. Every new symbol is in the distro SDL 3.2.10 headers. The suite is 59 passed, 2 skipped, 1097 assertions on Homebrew PHP 8.4 NTS and ZTS, and 56 passed, 5 skipped on the Pi under both Wayland and X11 (runtime SDL 3.2.10). Hit-test clicks and dialog dismissal are driven through AppKit on the Mac only.

## 2026-10-04

Created the bundle for 0.10.0. The extension binds SDL 3.2: core and events, windows and properties, surfaces and memory streams, the GL, Metal and Vulkan hooks, and SDL_GPU through blit. The suite is 28 passed, 1 skipped, 622 assertions on Homebrew PHP 8.4 NTS and ZTS, and 28 passed, 1 skipped, 618 assertions on the Pi (distro SDL 3.2.10, Vulkan). The skipped test is Vulkan instance extensions on the Mac and the Metal view on the Pi. The gate's stencil-then-cover triangle, resolved from 4 samples and blitted, reads back the same on Metal and on V3DV, with the hypotenuse neither solid red nor solid clear.
