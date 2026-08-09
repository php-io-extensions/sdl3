---
type: CoreType
title: Sdl3\\SDL\\Surface\\SDLSurface
description: Surfaces, pixels, blit/fill
resource: /sdl3/sdl/surface/sdlsurface.zep
tags: [sdl3, api, surface]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: surface-zep
    resource: /sdl3/sdl/surface/sdlsurface.zep
    title: sdlsurface.zep
  - id: readme
    resource: /README.md
    title: Package README
  - id: demo
    resource: /examples/proof_surface.php
    title: proof_surface.php
---

# Role

SDL surface create/convert/blit/fill/lock plus palette and pixel helpers (~72 methods).[^surface-zep]

# Patterns

- `SDLCreateSurface` returns `['ptr' => int, 'w' => int, 'h' => int, 'pitch' => int, …]`.[^readme]
- Pass the surface handle as the `ptr` int to subsequent APIs.
- Binary pixel buffers use PHP `string` (`SDLConvertPixels`, `SDLCreateSurfaceFrom`).
- `*_IO` loaders/savers are excluded — no `SDL_IOStream` binding yet (see [IOStream unbound](/traps/iostream-unbound.md)).[^readme]
- Destroy with `SDLDestroySurface(int $surface)`.

# Proof

`examples/proof_surface.php` (headless create/mutate/save/reload).[^demo]

Full method table: README § Surface / `ide/0.7.0/Sdl3/SDL/Surface/SDLSurface.php`.

[^surface-zep]: sdlsurface.zep
[^readme]: Package README
[^demo]: proof_surface.php
