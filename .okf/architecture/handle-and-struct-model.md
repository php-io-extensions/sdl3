---
type: Architecture
title: Handle and struct model
description: Opaque SDL pointers as PHP int; C structs as assoc arrays
resource: /README.md
tags: [sdl3, architecture, handles, structs]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: readme
    resource: /README.md
    title: Package README
  - id: surface-zep
    resource: /sdl3/sdl/surface/sdlsurface.zep
    title: sdlsurface.zep
  - id: gpu-zep
    resource: /sdl3/sdl/gpu/sdlgpu.zep
    title: sdlgpu.zep
  - id: props-zep
    resource: /sdl3/sdl/sdlproperties.zep
    title: sdlproperties.zep
---

# Opaque objects → PHP `int`

SDL pointers (`SDL_Window *`, `SDL_Renderer *`, `SDL_Surface *`, GPU objects, joysticks, audio streams, …) are cast to `zend_long` and exposed as PHP `int`.[^readme]

| Convention | Meaning |
|------------|---------|
| Non-zero `int` | Live opaque handle |
| `0` | Null / failure (check `SDLError::SDLGetError()` when expected) |
| Ownership | Caller must call the matching `SDLDestroy*` / `SDLClose*` / `SDLRelease*` |

There is **no** Zephir DTO class wrapping handles (contrast vulkan’s `fd` objects). Handles are bare ints passed between static methods.

# Structs → assoc arrays

C structs become PHP arrays whose keys match SDL field names:

| Example | Shape |
|---------|--------|
| Surface create result | `['ptr' => int, 'w' => int, 'h' => int, 'pitch' => int, …]`[^surface-zep][^readme] |
| `SDL_AudioSpec` | `["format" => int, "channels" => int, "freq" => int]`[^readme] |
| GPU create infos | keys mirror `SDL_GPUBufferCreateInfo`, etc.; nested lists are arrays of assoc arrays[^gpu-zep][^readme] |
| Virtual joystick desc | assoc array matching `SDL_VirtualJoystickDesc`[^readme] |
| Events from poll | always include numeric `type` (`SDL_EVENT_*`)[^readme] |

Out-param style getters often return `['result' => bool, …]`.[^readme]

# Binary buffers → PHP `string`

Pixel/audio/shader bytes use PHP binary strings (`SDLConvertPixels`, `SDLPutAudioStreamData`, GPU shader code, …).[^readme]

# Properties

`SDL_PropertiesID` values are plain `int` handles via `SDLProperties`. Pointer properties store opaque handles the same way as renderers/surfaces. `SDL_SetPointerPropertyWithCleanup` is intentionally unbound.[^props-zep][^readme]

# Rects

Many APIs accept `mixed $rect = null`. Implementations commonly accept a numeric-indexed array `[x, y, w, h]` (see surface helpers) or null for “full target”.[^surface-zep]

[^readme]: Package README
[^surface-zep]: sdlsurface.zep
[^gpu-zep]: sdlgpu.zep
[^props-zep]: sdlproperties.zep
