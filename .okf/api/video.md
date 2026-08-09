---
type: CoreType
title: Video (SDLVideo, SDLGL)
description: Windows + OpenGL/EGL context helpers
resource: /sdl3/sdl/video/sdlvideo.zep
tags: [sdl3, api, video, opengl]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: video-zep
    resource: /sdl3/sdl/video/sdlvideo.zep
    title: sdlvideo.zep
  - id: gl-zep
    resource: /sdl3/sdl/video/sdlgl.zep
    title: sdlgl.zep
  - id: readme
    resource: /README.md
    title: Package README
  - id: demo
    resource: /examples/proof_video.php
    title: proof_video.php
---

# Role

Window management and OpenGL/EGL context helpers. Window/renderer handles are opaque `int`s.[^video-zep][^gl-zep]

## `Sdl3\SDL\Video\SDLVideo`

Large surface (~83 static methods). README highlights include:

| Method | Returns | Notes |
|--------|---------|--------|
| `SDLCreateWindow(string, int, int, int)` | `int` | Window handle |
| `SDLCreateWindowAndRenderer(…)` | `array` | `['window' => int, 'renderer' => int, …]` |
| `SDLGetWindowSize` / `Position` / `SizeInPixels` / min/max/aspect | `array` | Out-param style |
| `SDLSetWindowIcon(int $window, int $surface)` | `bool` | |
| `SDLDestroyWindow(int $window)` | `void` | |

Additional methods in `.zep` cover displays, window flags, fullscreen, hit-test bridges, etc. — open `sdlvideo.zep` / `ide/0.7.0` rather than inventing from memory.[^video-zep][^readme]

## `Sdl3\SDL\Video\SDLGL`

OpenGL/EGL via SDL (~20 methods): load library, attributes, create/make-current/swap/destroy context, EGL proc/display helpers.[^gl-zep]

This is **not** the OpenGL draw API — use `php-io-extensions/open-gl` for `gl*` if needed.

# Proof

`examples/proof_video.php`.[^demo]

[^video-zep]: sdlvideo.zep
[^gl-zep]: sdlgl.zep
[^readme]: Package README
[^demo]: proof_video.php
