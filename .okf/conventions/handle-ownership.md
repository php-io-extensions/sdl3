---
type: Convention
title: Handle ownership
description: Create/destroy opaque SDL ints; PHP GC does not free natives
tags: [sdl3, convention, memory, handles]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: readme
    resource: /README.md
    title: Package README
  - id: video-zep
    resource: /sdl3/sdl/video/sdlvideo.zep
    title: sdlvideo.zep
  - id: render-zep
    resource: /sdl3/sdl/render/sdlrender.zep
    title: sdlrender.zep
  - id: surface-zep
    resource: /sdl3/sdl/surface/sdlsurface.zep
    title: sdlsurface.zep
  - id: config
    resource: /config.json
    title: Zephir config destructor
---

# Rules (representative)

| Object | Create | Destroy |
|--------|--------|---------|
| Window | `SDLVideo::SDLCreateWindow` / `…AndRenderer` | `SDLVideo::SDLDestroyWindow` |
| Renderer | `SDLRender::SDLCreateRenderer` / `SDLCreateSoftwareRenderer` | `SDLRender::SDLDestroyRenderer` |
| Texture | `SDLCreateTexture*` | `SDLDestroyTexture` |
| Surface | `SDLCreateSurface*` / loaders | `SDLDestroySurface` |
| GL context | `SDLGL::SDLGLCreateContext` | `SDLGLDestroyContext` |
| Joystick / gamepad | `SDLOpen*` | `SDLClose*` |
| Audio device / stream | `SDLOpen*` / `SDLCreateAudioStream` | `SDLCloseAudioDevice` / `SDLDestroyAudioStream` |
| GPU objects | `SDLCreateGPU*` | matching `SDLRelease*` / `SDLDestroyGPUDevice` |
| Properties | `SDLCreateProperties` | `SDLDestroyProperties` |

# Semantics

- `0` means null/failure; do not destroy `0`.
- Dropping a PHP int without calling destroy **leaks** until process exit (or module unload’s `SDL_Quit()`).[^config]
- Typical teardown order for a windowed app: textures → renderer → window → `SDLQuit`.
- Software path: destroy renderer before surface if the renderer owns drawing to that surface.

# Checklist

1. Pair every create/open with destroy/close/release.
2. After failure returns, check `SDLError::SDLGetError()`.
3. Do not share opaque handles across process forks.

[^readme]: Package README
[^video-zep]: sdlvideo.zep
[^render-zep]: sdlrender.zep
[^surface-zep]: sdlsurface.zep
[^config]: Zephir config destructor
