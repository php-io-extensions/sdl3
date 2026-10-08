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

`SDL_Init`, `SDL_InitSubSystem`, `SDL_Quit`, `SDL_GetError`, `SDL_ClearError`, `SDL_GetVersion`, `SDL_SetHint`, `SDL_PumpEvents`, `SDL_PollEvent`, `SDL_WaitEventTimeout`. Structs `SDL_Event`, `SDL_WindowEvent`, `SDL_DisplayEvent` (`SDL_Event::$display`, written for `SDL_EVENT_DISPLAY_FIRST`..`LAST`). Constants `SDL_INIT_VIDEO`, `SDL_EVENT_QUIT`, every `SDL_EVENT_WINDOW_*` except mouse enter/leave, every `SDL_EVENT_DISPLAY_*`, the first/last bounds of both ranges, `SDL_HINT_VIDEO_DRIVER`, `SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES`, `SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS`, `SDL_HINT_VIDEO_FORCE_EGL`.

# Windows and properties

Handle `SDL_Window`. `SDL_CreateWindow`, `SDL_CreateWindowWithProperties`, `SDL_DestroyWindow`, id lookup, title, size in points and in pixels, pixel density, display scale, show, hide, raise, flags, window properties. `SDL_CreateProperties`, `SDL_DestroyProperties`, and the set/get calls for pointer, number, string, and boolean. `SDL_GetStringProperty`, `SDL_GetFloatProperty`, `SDL_SetFloatProperty`, `SDL_GetBooleanProperty`. Window flags `SDL_WINDOW_*` except the mouse/keyboard grab, mouse focus/capture, tooltip and popup-menu flags. The `SDL_PROP_WINDOW_CREATE_*` strings: title, position, size, the graphics API booleans, hidden, resizable, borderless, always-on-top, focusable, maximized, minimized, fullscreen, transparent, utility, external graphics context, the Cocoa window and view, the Wayland surface, the X11 window. The window's own properties: HDR enabled, SDR white level, HDR headroom, the Cocoa window and Metal view tag, the X11 display, screen and window, the Wayland display and surface. `SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN`.

# Window state

`SDL_SetWindowSize`, `SDL_SetWindowPosition`, `SDL_GetWindowPosition`, minimum and maximum size set/get, aspect ratio set/get, `SDL_GetWindowBordersSize`, `SDL_GetWindowSafeArea`. `SDL_MaximizeWindow`, `SDL_MinimizeWindow`, `SDL_RestoreWindow`, `SDL_SyncWindow`. `SDL_SetWindowResizable`, `SDL_SetWindowBordered`, `SDL_SetWindowAlwaysOnTop`, `SDL_SetWindowFocusable`, opacity set/get, `SDL_SetWindowIcon`, `SDL_FlashWindow` with `SDL_FLASH_*`. `SDL_SetWindowHitTest` with `SDL_HITTEST_*`. `SDL_ScreenSaverEnabled`, `SDL_EnableScreenSaver`, `SDL_DisableScreenSaver`. `SDL_WINDOWPOS_UNDEFINED`, `SDL_WINDOWPOS_CENTERED` and their masks. `SDL_ShowSimpleMessageBox` with the `SDL_MESSAGEBOX_*` dialog and button-order flags.

Measured driver behaviour: Wayland refuses `SDL_SetWindowPosition` ("wayland cannot position non-popup windows"), accepts always-on-top and not-focusable after creation without setting their flags, and emulates an exclusive mode by sizing the window to it while the display mode stays put. Cocoa and Wayland answer "That operation is not supported" for `SDL_GetWindowBordersSize`. X11 applies a resize to a mapped window, and each min/max/aspect call re-applies the size the window last committed.

# Displays and fullscreen

Struct `SDL_DisplayMode` (a copy; SDL's driver data is not carried, and SDL matches a mode passed back in by its public fields). Struct `SDL_Point`. `SDL_GetCurrentVideoDriver`, `SDL_GetDisplays`, `SDL_GetPrimaryDisplay`, `SDL_GetDisplayProperties`, `SDL_GetDisplayName`, `SDL_GetDisplayBounds`, `SDL_GetDisplayUsableBounds`, natural and current orientation with `SDL_ORIENTATION_*`, `SDL_GetDisplayContentScale`, `SDL_GetFullscreenDisplayModes`, `SDL_GetClosestFullscreenDisplayMode`, desktop and current display mode, `SDL_GetDisplayForPoint`, `SDL_GetDisplayForRect`, `SDL_GetDisplayForWindow`. `SDL_SetWindowFullscreenMode` (null for borderless desktop, a mode for exclusive), `SDL_GetWindowFullscreenMode`, `SDL_SetWindowFullscreen`.

# Surfaces and streams

Handles `SDL_IOStream`, `SDL_Surface`. Struct `SDL_Rect`. `SDL_IOFromMem`, `SDL_IOFromConstMem`, `SDL_ReadIO`, `SDL_WriteIO`, `SDL_CloseIO`. `SDL_GetWindowSurface`, `SDL_UpdateWindowSurface`, `SDL_UpdateWindowSurfaceRects`, `SDL_WindowHasSurface`, `SDL_DestroyWindowSurface`, `SDL_SetWindowSurfaceVSync` and `SDL_GetWindowSurfaceVSync` with `SDL_WINDOW_SURFACE_VSYNC_DISABLED`/`ADAPTIVE`, `SDL_CreateSurfaceFrom`, `SDL_DestroySurface`, `SDL_BlitSurface`, `SDL_BlitSurfaceScaled`, `SDL_FillSurfaceRect`. `SDL_PIXELFORMAT_RGBA32`, `SDL_PIXELFORMAT_BGRA32`, `SDL_SCALEMODE_NEAREST`, `SDL_SCALEMODE_LINEAR`.

`SDL_MapGPUTransferBuffer` returns the address. These stream calls are how bytes move.

# GL, Metal, Vulkan

Handles `SDL_GLContext`, `SDL_MetalView`. Attribute, context, swap, swap interval set/get, and destroy for GL; `SDL_EGL_GetCurrentDisplay` (the EGLDisplay address, null off EGL). `SDL_Metal_CreateView`, `SDL_Metal_GetLayer` (the `CAMetalLayer` address), `SDL_Metal_DestroyView`. `SDL_Vulkan_GetInstanceExtensions`, `SDL_Vulkan_CreateSurface`, `SDL_Vulkan_DestroySurface`. The `SDL_GL_*` attribute and profile constants.

# SDL_GPU types

Handles named by the structs: `SDL_GPUShader`, `SDL_GPUTexture`, `SDL_GPUBuffer`, `SDL_GPUTransferBuffer`, `SDL_GPUSampler`. Every struct in the slice plan's task 5 table, fields as SDL 3.2 names them. The `SDL_GPU_*` constants those calls and structs take, including every texture format in the 3.2 header, plus `SDL_FLIP_NONE`.

# SDL_GPU device and passes

Handles `SDL_GPUDevice`, `SDL_GPUCommandBuffer`, `SDL_GPUCopyPass`, `SDL_GPUFence`, `SDL_GPUGraphicsPipeline`, `SDL_GPURenderPass`. Device, texture, sampler, buffer, transfer buffer, shader, and pipeline create/release. Map and unmap. Command buffers, fences, idle. Copy, render, and blit. Swapchain claim, `SDL_WindowSupportsGPUPresentMode`, `SDL_WindowSupportsGPUSwapchainComposition`, parameters, format, acquire and `SDL_WaitAndAcquireGPUSwapchainTexture`, `SDL_WaitForGPUSwapchain`, `SDL_SetGPUAllowedFramesInFlight` (range checked only in SDL's GPU debug mode, measured).

[^stubs]: `stubs/*.stub.php`
