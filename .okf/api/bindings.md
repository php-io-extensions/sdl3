---
type: API
title: Bindings
description: SDL 3.2 functions, handles, structs and constants bound by this extension, grouped as the slice plan's tasks.
resource: stubs/
tags: [sdl3, api]
status: draft
generated: { by: grok/4.7, at: 2026-10-04T23:50:00-04:00 }
sources:
  - id: stubs
    resource: stubs/
    title: gen_stub declarations
---

# Overview

Every name below is the C name. Constants are `@cvalue` from the SDL headers.[^stubs]

# Core and events

`SDL_Init`, `SDL_InitSubSystem`, `SDL_Quit`, `SDL_GetError`, `SDL_GetVersion`, `SDL_SetHint`, `SDL_PumpEvents`, `SDL_PollEvent`, `SDL_WaitEventTimeout`. Structs `SDL_Event`, `SDL_WindowEvent`. Constants `SDL_INIT_VIDEO`, `SDL_EVENT_QUIT`, the `SDL_EVENT_WINDOW_*` set the plan names, `SDL_HINT_VIDEO_DRIVER`.

# Windows and properties

Handle `SDL_Window`. `SDL_CreateWindow`, `SDL_CreateWindowWithProperties`, `SDL_DestroyWindow`, id lookup, title, size in points and in pixels, pixel density, display scale, show, hide, raise, flags, window properties. `SDL_CreateProperties`, `SDL_DestroyProperties`, and the set/get calls for pointer, number, string, and boolean. Window flags `SDL_WINDOW_{HIDDEN, RESIZABLE, HIGH_PIXEL_DENSITY, OPENGL, VULKAN, METAL}` and the `SDL_PROP_WINDOW_CREATE_*` strings, including the Cocoa view, Wayland surface, and X11 window properties.

# Surfaces and streams

Handles `SDL_IOStream`, `SDL_Surface`. Struct `SDL_Rect`. `SDL_IOFromMem`, `SDL_IOFromConstMem`, `SDL_ReadIO`, `SDL_WriteIO`, `SDL_CloseIO`. `SDL_GetWindowSurface`, `SDL_UpdateWindowSurface`, `SDL_CreateSurfaceFrom`, `SDL_DestroySurface`, `SDL_BlitSurface`, `SDL_BlitSurfaceScaled`, `SDL_FillSurfaceRect`. `SDL_PIXELFORMAT_RGBA32`, `SDL_PIXELFORMAT_BGRA32`, `SDL_SCALEMODE_NEAREST`, `SDL_SCALEMODE_LINEAR`.

`SDL_MapGPUTransferBuffer` returns the address. These stream calls are how bytes move.

# GL, Metal, Vulkan

Handles `SDL_GLContext`, `SDL_MetalView`. Attribute, context, swap, and destroy for GL. `SDL_Metal_CreateView`, `SDL_Metal_GetLayer` (the `CAMetalLayer` address), `SDL_Metal_DestroyView`. `SDL_Vulkan_GetInstanceExtensions`, `SDL_Vulkan_CreateSurface`, `SDL_Vulkan_DestroySurface`. The `SDL_GL_*` attribute and profile constants.

# SDL_GPU types

Handles named by the structs: `SDL_GPUShader`, `SDL_GPUTexture`, `SDL_GPUBuffer`, `SDL_GPUTransferBuffer`, `SDL_GPUSampler`. Every struct in the slice plan's task 5 table, fields as SDL 3.2 names them. The `SDL_GPU_*` constants those calls and structs take, including every texture format in the 3.2 header, plus `SDL_FLIP_NONE`.

# SDL_GPU device and passes

Handles `SDL_GPUDevice`, `SDL_GPUCommandBuffer`, `SDL_GPUCopyPass`, `SDL_GPUFence`, `SDL_GPUGraphicsPipeline`, `SDL_GPURenderPass`. Device, texture, sampler, buffer, transfer buffer, shader, and pipeline create/release. Map and unmap. Command buffers, fences, idle. Copy, render, and blit. Swapchain claim, parameters, format, and acquire.

[^stubs]: `stubs/*.stub.php`
