---
type: CoreType
title: Sdl3\\SDL\\Gpu\\SDLGPU
description: SDL GPU API plus GPU render-state helpers
resource: /sdl3/sdl/gpu/sdlgpu.zep
tags: [sdl3, api, gpu]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: gpu-zep
    resource: /sdl3/sdl/gpu/sdlgpu.zep
    title: sdlgpu.zep
  - id: readme
    resource: /README.md
    title: Package README
  - id: demo
    resource: /examples/proof_gpu.php
    title: proof_gpu.php
---

# Role

Complete binding of `SDL_gpu.h` plus GPU render-state functions from `SDL_render.h` (~105 methods).[^gpu-zep][^readme]

# Patterns

- Opaque objects (device, buffers, textures, samplers, shaders, pipelines, command buffers, passes, fences, render states) → PHP `int`.
- Create-info / pass descriptors → assoc arrays with **exact C field names**; nested lists are arrays of assoc arrays.
- Shader bytecode/source and uniforms → PHP binary `string`.
- Prefer `writeToGPUTransferBuffer` / `readFromGPUTransferBuffer` over raw `SDLMapGPUTransferBuffer` address ints.
- `SDLGDKSuspendGPU` / `SDLGDKResumeGPU` throw outside GDK (Xbox) builds.[^readme]

# Proof

`examples/proof_gpu.php`.[^demo]

Full method table: README § Gpu / `ide/0.7.0/Sdl3/SDL/Gpu/SDLGPU.php`.

[^gpu-zep]: sdlgpu.zep
[^readme]: Package README
[^demo]: proof_gpu.php
