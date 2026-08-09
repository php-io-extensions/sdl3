---
type: CoreType
title: Sdl3\\SDL\\Render\\SDLRender
description: Renderer, textures, draw primitives
resource: /sdl3/sdl/render/sdlrender.zep
tags: [sdl3, api, render]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: render-zep
    resource: /sdl3/sdl/render/sdlrender.zep
    title: sdlrender.zep
  - id: readme
    resource: /README.md
    title: Package README
  - id: demo
    resource: /examples/proof_render.php
    title: proof_render.php
  - id: pow
    resource: /examples/proof_of_work.php
    title: proof_of_work.php
---

# Role

2D renderer API: create hardware or software renderer, textures, clear/present, geometry, debug text (~94 methods).[^render-zep]

# Patterns

| Concept | PHP shape |
|---------|-----------|
| Renderer | opaque `int` (`SDLCreateRenderer`, `SDLCreateSoftwareRenderer`) |
| Texture create | often `array` with handle + metadata |
| Draw color | int RGBA 0..255 or float variants |
| Present | `SDLRenderPresent(int $renderer): bool` |
| Destroy | `SDLDestroyRenderer` / `SDLDestroyTexture` |

Headless path: create surface → `SDLCreateSoftwareRenderer` → draw → present/read — used by `proof_of_work.php`.[^pow][^readme]

# Proof

`examples/proof_render.php`, `examples/proof_of_work.php`.[^demo][^pow]

[^render-zep]: sdlrender.zep
[^readme]: Package README
[^demo]: proof_render.php
[^pow]: proof_of_work.php
