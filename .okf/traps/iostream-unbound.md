---
type: Trap
title: IOStream APIs unbound
description: SDL_IOStream-based loaders/savers are intentionally missing
resource: /README.md
tags: [sdl3, trap, iostream]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: readme
    resource: /README.md
    title: README.md
---

# Trap

Several SDL3 APIs that require `SDL_IOStream` are **not** bound, including (documented in README):[^readme]

- Surface `*_IO` loaders/savers
- `SDL_LoadWAV_IO`
- `SDL_AddGamepadMappingsFromIO`

Use path-based alternatives (`SDLLoadPNG`, `SDLLoadWAV`, `SDLAddGamepadMappingsFromFile`, …) or wait for an `io` subsystem binding (`sdl3/sdl/io/` is currently an empty scaffold).

Do not invent IOStream wrappers in docs or call sites.

[^readme]: README.md
