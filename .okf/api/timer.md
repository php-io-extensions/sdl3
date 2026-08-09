---
type: CoreType
title: Sdl3\\SDL\\Timer\\SDLTimer
description: Delay and ticks
resource: /sdl3/sdl/timer/sdltimer.zep
tags: [sdl3, api, timer]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: timer-zep
    resource: /sdl3/sdl/timer/sdltimer.zep
    title: sdltimer.zep
  - id: readme
    resource: /README.md
    title: Package README
---

# Role

Minimal timer helpers present on disk:[^timer-zep][^readme]

| Method | Returns |
|--------|---------|
| `SDLDelay(int $ms)` | `void` |
| `SDLGetTicks()` | `int` |

Do not invent additional timer APIs (callbacks, high-res timers) unless new `.zep` methods land.

[^timer-zep]: sdltimer.zep
[^readme]: Package README
