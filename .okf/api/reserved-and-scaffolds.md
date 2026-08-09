---
type: CoreType
title: Reserved & empty scaffolds
description: Empty classes and empty subsystem directories
resource: /sdl3/sdl/sdlassert.zep
tags: [sdl3, api, scaffold, reserved]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: assert
    resource: /sdl3/sdl/sdlassert.zep
    title: sdlassert.zep
  - id: log
    resource: /sdl3/sdl/sdllog.zep
    title: sdllog.zep
  - id: list
    resource: /sdl3/sdl/sdllist.zep
    title: sdllist.zep
  - id: utils
    resource: /sdl3/sdl/sdlutils.zep
    title: sdlutils.zep
  - id: readme
    resource: /README.md
    title: Package README
---

# Reserved empty classes

These ship in the public namespace but currently have **no methods**:[^readme]

| Class | Path |
|-------|------|
| `Sdl3\SDL\SDLAssert` | `sdl3/sdl/sdlassert.zep` |
| `Sdl3\SDL\SDLLog` | `sdl3/sdl/sdllog.zep` |
| `Sdl3\SDL\SDLList` | `sdl3/sdl/sdllist.zep` |
| `Sdl3\SDL\SDLUtils` | `sdl3/sdl/sdlutils.zep` |
| `Sdl3\SDL\Events\SDLKeymap` | `sdl3/sdl/events/sdlkeymap.zep` |
| `Sdl3\SDL\Events\SDLScancodeTables` | `sdl3/sdl/events/sdlscancodetables.zep` |
| `Sdl3\SDL\Events\SDLWindowEvents` | `sdl3/sdl/events/sdlwindowevents.zep` |

# Empty subsystem directories

Present on disk with **no `.zep` files**:

- `sdl3/sdl/camera/`
- `sdl3/sdl/cpuinfo/`
- `sdl3/sdl/filesystem/`
- `sdl3/sdl/haptic/`
- `sdl3/sdl/io/`

# Agent rule

Do **not** invent APIs for these scaffolds. Document only what exists; when filled, add methods to the matching `.zep`, regenerate `ext/` + `ide/0.7.0/`, and update this OKF.

[^assert]: sdlassert.zep
[^log]: sdllog.zep
[^list]: sdllist.zep
[^utils]: sdlutils.zep
[^readme]: Package README
