---
type: Convention
title: Sibling patterns
description: Shared php-io-extensions packaging style (not dependencies)
tags: [sdl3, convention, packaging]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: composer
    resource: /composer.json
    title: composer.json
  - id: config
    resource: /config.json
    title: config.json
  - id: readme
    resource: /README.md
    title: README.md
---

# Borrowed patterns (style only)

| Pattern | How sdl3 uses it |
|---------|------------------|
| Thin Zephir static classes | `Sdl3\SDL\…::*` wraps `SDL_*` |
| Opaque int handles | SDL pointers as PHP `int` |
| PIE `type: php-ext`, `build-path: ext` | Same layout in `composer.json`[^composer] |
| Platform installers | `install-macos*.sh`, debian, jetpack |
| Version `0.7.0`, PHP ≥ 8.2 | Aligned with sibling extensions |
| Windows excluded | `os-families-exclude: ["windows"]` |
| IDE stubs path | `ide/0.7.0/Sdl3/SDL/` |
| No FFI | Native extension only |

# Distinct from siblings

- **No** separate `src/*-api.c` thin ABI (unlike vulkan/metal) — inline C in `.zep`.
- **Includes** windowing itself (unlike vulkan, which peers with glfw).
- **Not** Darwin-only (unlike metal).
- Downstream ergonomics live in **microscrap/sdl3** / **sdl3-gfx**, not here.[^readme]

[^composer]: composer.json
[^config]: config.json
[^readme]: README.md
