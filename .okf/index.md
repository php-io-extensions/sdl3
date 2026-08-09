---
okf_version: "0.2"
---

# php-io-extensions/sdl3

Cross-platform (Linux + macOS) PHP extension: Zephir static classes under `Sdl3\SDL\…` that call **libSDL3** (≥ 3.4.0) via inline C. Opaque SDL objects are PHP `int` handles; C structs travel as assoc arrays mirroring field names. Windows is excluded. Headless software-renderer proof: `examples/proof_of_work.php`.

**Prefer** concepts with `status: stable` when present; content is currently `draft` pending Angel’s human verification of the OKF docs (implementation facts are grounded in shipped Zephir/`ext/`/README).

# Orientation

* [Package overview](orientation/overview.md) - What sdl3 is, version targets, and what it deliberately is not
* [Stack segmentation](orientation/stack-segmentation.md) - Boundaries vs microscrap bindings, sdl3-gfx, metal, glfw, open-gl

# Architecture

* [Layered stack](architecture/stack.md) - Zephir → inline C → libSDL3
* [Zephir inline C](architecture/zephir-inline-c.md) - `%{ … %}` blocks calling `SDL_*` directly
* [Handle and struct model](architecture/handle-and-struct-model.md) - Opaque ints + assoc-array structs

# Public PHP API

* [Sdl3\\SDL\\SDL](api/sdl.md) - Init/quit, version, platform, pixel helpers
* [Sdl3\\SDL\\SDLError](api/sdlerror.md) - Error get/set/clear
* [Sdl3\\SDL\\SDLProperties](api/sdlproperties.md) - Property bags (`SDL_PropertiesID` as int)
* [Video (SDLVideo, SDLGL)](api/video.md) - Windows + OpenGL/EGL context helpers
* [Surface\\SDLSurface](api/surface.md) - Surfaces, pixels, blit/fill
* [Render\\SDLRender](api/render.md) - Renderer, textures, draw primitives
* [Timer\\SDLTimer](api/timer.md) - Delay and ticks
* [Events/\*](api/events.md) - Event queue, keyboard, mouse, display, clipboard, …
* [Input (Joystick, Gamepad)](api/input.md) - Joystick + gamepad APIs
* [Audio\\SDLAudio](api/audio.md) - Devices, streams, WAV/mix
* [Dialog\\SDLDialog](api/dialog.md) - Async native file dialogs
* [Gpu\\SDLGPU](api/gpu.md) - SDL GPU API + GPU render-state
* [Reserved & empty scaffolds](api/reserved-and-scaffolds.md) - Empty classes and empty subsystem dirs

# Build & packaging

* [Zephir + PIE install](build/zephir-and-pie.md) - installers, PIE, phpize from `ext/`
* [Committed ext/ notes](build/packaging-ext.md) - `config.m4`, GCC 14 flags, stubs

# Conventions

* [Sibling patterns](conventions/sibling-patterns.md) - Shared php-io-extensions packaging style
* [Handle ownership](conventions/handle-ownership.md) - Create/destroy opaque SDL ints
* [No FFI](conventions/no-ffi.md) - Extension-only binding
* [Constants outside the extension](conventions/constants-outside-ext.md) - No PHP class constants; app/microscrap enums

# Traps

* [Windows excluded](traps/windows-excluded.md) - PIE `os-families-exclude: windows`
* [IOStream APIs unbound](traps/iostream-unbound.md) - No `SDL_IOStream` yet
* [Empty scaffolds](traps/empty-scaffolds.md) - camera/cpuinfo/filesystem/haptic/io dirs empty
* [GCC 14 warning-as-error](traps/gcc14-warning-flags.md) - `config.m4` demotes Zephir-hostile errors
* [IDE stub path lag](traps/ide-stub-paths.md) - Prefer `ide/0.7.0/`; README may cite older
* [Destroy opaque handles](traps/destroy-opaque-handles.md) - PHP GC does not free SDL objects

# Playbooks

* [Minimal demo loop](playbooks/demo-loop.md) - `examples/proof_of_work.php` (headless)
* [Regenerate committed ext/](playbooks/regenerate-ext.md) - Maintainer Zephir build before tagging

# Indexes

* [Orientation](orientation/) — start here
* [Architecture](architecture/)
* [API](api/)
* [Build](build/)
* [Conventions](conventions/)
* [Traps](traps/)
* [Playbooks](playbooks/)
