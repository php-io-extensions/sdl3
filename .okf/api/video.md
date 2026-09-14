---
type: CoreType
title: Video (SDLVideo, SDLGL, SDLMetal, SDLVulkan)
description: Windows, OpenGL/EGL context helpers, Metal views, Vulkan loader + surfaces
resource: /sdl3/sdl/video/sdlvideo.zep
tags: [sdl3, api, video, opengl, metal, vulkan]
status: draft
generated: { by: claude-opus-5/claude-code, at: 2026-09-14T00:00:00Z }
sources:
  - id: video-zep
    resource: /sdl3/sdl/video/sdlvideo.zep
    title: sdlvideo.zep
  - id: gl-zep
    resource: /sdl3/sdl/video/sdlgl.zep
    title: sdlgl.zep
  - id: metal-zep
    resource: /sdl3/sdl/video/sdlmetal.zep
    title: sdlmetal.zep
  - id: vulkan-zep
    resource: /sdl3/sdl/video/sdlvulkan.zep
    title: sdlvulkan.zep
  - id: stage-proof
    resource: /examples/proof_stage_hosts.php
    title: proof_stage_hosts.php
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

## `Sdl3\SDL\Video\SDLMetal` (0.8.0)

`SDL_metal.h`. Layer crosses as raw pointer bits.[^metal-zep]

| Method | Returns | Notes |
|--------|---------|--------|
| `SDLMetalCreateView(int $window)` | `int` | Throws `RuntimeException` on NULL (always off Apple) |
| `SDLMetalDestroyView(int $view)` | `void` | |
| `SDLMetalGetLayer(int $view)` | `int` | `CAMetalLayer` bits; borrowed — valid until `SDLMetalDestroyView`, never release |

Compiles everywhere; only callable on macOS.

## `Sdl3\SDL\Video\SDLVulkan` (0.8.0)

`SDL_vulkan.h`. Every Vulkan handle = raw pointer bits in `int`, `0` = `VK_NULL_HANDLE` (ext-vulkan currency).[^vulkan-zep]

| Method | Returns | Notes |
|--------|---------|--------|
| `SDLVulkanLoadLibrary(?string $path = null)` | `bool` | `null` = SDL default loader |
| `SDLVulkanUnloadLibrary()` | `void` | |
| `SDLVulkanGetVkGetInstanceProcAddr()` | `int` | Fn pointer bits |
| `SDLVulkanGetInstanceExtensions()` | `array` | `list<string>`; SDL-owned names copied; `[]` = failure → `SDLError::SDLGetError()` |
| `SDLVulkanCreateSurface(int $window, int $instance, int $allocator)` | `int` | `VkSurfaceKHR` bits, `0` on failure → `SDLError::SDLGetError()` |
| `SDLVulkanDestroySurface(int $instance, int $surface, int $allocator)` | `void` | |
| `SDLVulkanGetPresentationSupport(int $instance, int $physical_device, int $queue_family_index)` | `bool` | |

Param names fold-match C prototypes (`physicalDevice`, `queueFamilyIndex`).

Instance extensions follow the live video driver: `VK_KHR_surface` + cocoa → `VK_EXT_metal_surface`, x11 → `VK_KHR_xlib_surface`, wayland → `VK_KHR_wayland_surface`.[^stage-proof]

32-bit builds: `VkSurfaceKHR` (uint64) truncates into `zend_long` — Vulkan surface calls unsupported on 32-bit.

`?string` params: `SDLVulkanLoadLibrary`, `SDLGLLoadLibrary`, `SDLRender::SDLCreateRenderer` `$name`. Zephir signature stays `var x = null` (reflects untyped); any non-null non-string throws `TypeError` (`<fn>() expects ?string …`) before C.

# Proof

`examples/proof_video.php`.[^demo] Metal/Vulkan/window events: `examples/proof_stage_hosts.php` (surface creation proven downstream, where an instance exists).[^stage-proof]

[^video-zep]: sdlvideo.zep
[^gl-zep]: sdlgl.zep
[^readme]: Package README
[^demo]: proof_video.php
[^metal-zep]: sdlmetal.zep
[^vulkan-zep]: sdlvulkan.zep
[^stage-proof]: proof_stage_hosts.php
