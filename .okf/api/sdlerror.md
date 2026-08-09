---
type: CoreType
title: Sdl3\\SDL\\SDLError
description: Error get/set/clear
resource: /sdl3/sdl/sdlerror.zep
tags: [sdl3, api, error]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: err-zep
    resource: /sdl3/sdl/sdlerror.zep
    title: sdlerror.zep
  - id: readme
    resource: /README.md
    title: Package README
---

# Role

Thin wrap of SDL’s thread-local error string API.[^err-zep]

| Method | Returns |
|--------|---------|
| `SDLGetError()` | `string` |
| `SDLSetError(string $message)` | `bool` |
| `SDLOutOfMemory()` | `bool` |
| `SDLClearError()` | `bool` |

After a failing call that returns `false` / `0` / `null`, read `SDLGetError()` for the SDL message.[^readme]

[^err-zep]: sdlerror.zep
[^readme]: Package README
