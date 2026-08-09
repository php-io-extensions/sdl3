---
type: Architecture
title: Layered stack
description: Zephir → inline C → libSDL3
resource: /config.json
tags: [sdl3, architecture, zephir]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: config
    resource: /config.json
    title: Zephir config
  - id: sdl-zep
    resource: /sdl3/sdl/sdl.zep
    title: sdl.zep
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: config-m4
    resource: /ext/config.m4
    title: Portable ext/config.m4
---

# Layers

```text
PHP (Sdl3\SDL\{SDL,SDLError,…,Video,Surface,Render,Events,Input,Audio,Dialog,Gpu})
        │  Zephir public static methods
        ▼
Inline C in .zep (`%{ #include <SDL3/SDL.h> … %}`)
        │  cast opaque pointers ↔ zend_long; pack/unpack assoc arrays
        ▼
libSDL3 (≥ 3.4.0)
   macOS: Homebrew /usr/local or /opt/homebrew
   Linux: pkg-config sdl3 / distro or from-source (JetPack installer)
```

Unlike [metal](../../metal/) and [vulkan](../../vulkan/), this package has **no** separate `src/*-api.c` thin ABI — Zephir talks to SDL3 headers directly.[^sdl-zep][^config]

# Source map

| Layer | Path | Role |
|-------|------|------|
| Zephir | `sdl3/sdl/**/*.zep` | Public PHP API |
| Generated C | `ext/sdl3/…` + Zephir kernel | Committed build tree for PIE/`phpize` |
| Zephir config | `config.json` | `extra-libs: -lSDL3`, Homebrew include hints, module destructor `SDL_Quit()` |
| Packaging | `ext/config.m4` | `--enable-sdl3`, pkg-config, GCC 14 warning demotion |
| PIE | `composer.json` | `build-path: ext`, Linux+macOS |
| Stubs | `ide/0.7.0/Sdl3/SDL/` | IDE autocomplete |

# Design intent

- Keep method names close to SDL3 C (`SDLCreateWindow`, …) for 1:1 mapping.
- Opaque objects and structs use the [handle and struct model](/architecture/handle-and-struct-model.md).
- Module destructor calls `SDL_Quit()` on unload (config.json).[^config]
- Constants stay out of the extension — see [Constants outside the extension](/conventions/constants-outside-ext.md).

[^config]: Zephir config
[^sdl-zep]: sdl.zep
[^composer]: PIE package manifest
[^config-m4]: Portable ext/config.m4
