---
type: Orientation
title: Package overview
description: What sdl3 is, version targets, and what it deliberately is not
resource: /composer.json
tags: [sdl3, orientation, php-ext]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: config
    resource: /config.json
    title: Zephir config
  - id: readme
    resource: /README.md
    title: Package README
  - id: php-h
    resource: /ext/php_sdl3.h
    title: PHP_SDL3_VERSION
  - id: demo
    resource: /examples/proof_of_work.php
    title: proof_of_work.php
---

# Summary

`php-io-extensions/sdl3` is a **Linux + macOS** PHP extension (`type: php-ext`) that exposes SDL3 to PHP 8.2+ via Zephir static classes under `Sdl3\SDL\…`. It links the system **libSDL3** (≥ 3.4.0) and supports both hardware-accelerated windows and the headless software renderer.[^composer][^readme]

| Fact | Value |
|------|--------|
| Package | `php-io-extensions/sdl3` |
| Extension name | `sdl3` |
| Version | `0.7.0` |
| PHP | `>= 8.2` (ZTS + NTS) |
| OS | Linux + macOS; Windows excluded |
| Namespace | `Sdl3\SDL\*` |
| Author | Project Saturn Studios, LLC |
| License | MIT |
| Binding | Zephir + inline C → `SDL_*` — **no FFI** |
| Link | `-lSDL3` (pkg-config / Homebrew paths) |
| SDL3 | ≥ 3.4.0 |

Version is aligned across `composer.json`, `config.json`, and `PHP_SDL3_VERSION` in `ext/php_sdl3.h`.[^composer][^config][^php-h]

# End capability (v0.7)

Documented public surface on disk includes:

1. Lifecycle / platform / pixel helpers (`SDL`, `SDLError`, `SDLProperties`)
2. Video windows + OpenGL/EGL helpers (`Video\SDLVideo`, `Video\SDLGL`)
3. Surfaces, software/hardware renderers, textures, draw primitives
4. Event queue + keyboard/mouse/display/clipboard/drop/watch helpers
5. Joystick + gamepad input; audio devices/streams; async file dialogs
6. Full SDL GPU binding (`Gpu\SDLGPU`) plus GPU render-state helpers

Canonical headless demo: `examples/proof_of_work.php`.[^demo]

# What it is not

- Not a high-level PHP framework wrapper — that is **microscrap/sdl3** (bindings/enums layer).
- Not a tubes framebuffer/gfx companion — that is **microscrap/sdl3-gfx**.
- Not Apple AppKit/Metal — that is `php-io-extensions/metal` (separate product).
- Not GLFW windowing — that is `php-io-extensions/glfw`.
- Not OpenGL draw API bindings — that is `php-io-extensions/open-gl` (SDLGL only loads/contexts via SDL).
- Not available on Windows.
- Not an FFI wrapper and not a home for PHP class constants (`SDL_*` flags live in app code or microscrap enums).

# Public namespace

Zephir classes live under `Sdl3\SDL\` (`sdl3/sdl/**/*.zep`). IDE stubs: `ide/0.7.0/Sdl3/SDL/`.

See [Stack segmentation](/orientation/stack-segmentation.md) and [Layered stack](/architecture/stack.md).

[^composer]: PIE package manifest
[^config]: Zephir config
[^readme]: Package README
[^php-h]: PHP_SDL3_VERSION
[^demo]: proof_of_work.php
