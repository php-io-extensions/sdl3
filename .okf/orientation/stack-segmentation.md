---
type: Orientation
title: Stack segmentation
description: Boundaries vs microscrap bindings, sdl3-gfx, metal, glfw, open-gl
tags: [sdl3, orientation, boundaries]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: readme
    resource: /README.md
    title: Package README
  - id: demo
    resource: /examples/proof_of_work.php
    title: proof_of_work.php
---

# Who owns what

| Concern | Package | Notes |
|---------|---------|--------|
| Native SDL3 C API in PHP | **`php-io-extensions/sdl3`** | This package — Zephir extension |
| Typed PHP bindings / enums / ergonomics | `microscrap/sdl3` | Downstream; not documented deeply here |
| Tubes framebuffer / gfx companion | `microscrap/sdl3-gfx` | Downstream tubes path; Framebuffers-first |
| Native macOS AppKit + Metal | `php-io-extensions/metal` | Separate Darwin product — **not** a dep |
| GLFW window / Vulkan surface peer | `php-io-extensions/glfw` | Peer for Vulkan demos; not required by sdl3 |
| OpenGL `gl*` draw API | `php-io-extensions/open-gl` | Separate; SDLGL here is context/loader only |
| Enum / flag values (`SDL_*`) | app locals or microscrap enums | Not compiled into this extension |

# Composition sketch

```text
PHP app / tubes
  ├─ microscrap/sdl3       → ergonomic wrappers + enums (optional)
  ├─ microscrap/sdl3-gfx   → tubes companion (optional)
  └─ php-io-extensions/sdl3 → native SDL3 (this package)
         └─ libSDL3 ≥ 3.4.0
```

Headless proof needs only this extension + libSDL3 (software renderer).[^demo]

# Hard rules

1. Do **not** document microscrap/sdl3 or sdl3-gfx APIs inside this OKF — only composition boundaries.
2. Do **not** add metal/glfw/open-gl as runtime Composer deps of this package.
3. Do **not** nest a second `.okf` under `sdl3/sdl/`.
4. Keep Windows out of PIE (`os-families-exclude: ["windows"]`).[^composer]
5. Empty subsystem folders (`camera`, `cpuinfo`, `filesystem`, `haptic`, `io`) are scaffolds — no public API until `.zep` files exist.

[^composer]: PIE package manifest
[^readme]: Package README
[^demo]: proof_of_work.php
