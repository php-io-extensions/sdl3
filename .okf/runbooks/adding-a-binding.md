---
type: Runbook
title: Adding a binding
description: Declare it in the stub for its SDL header, regenerate arginfo, implement it beside that group, and let the surface test see it.
resource: stubs/
tags: [sdl3, contributing]
status: draft
generated: { by: grok/4.7, at: 2026-10-04T23:50:00-04:00 }
sources:
  - id: build
    resource: runbooks/build.md
    title: Build runbook
---

# Overview

1. Add the function, class, or `@cvalue` constant to the stub for its header: `stubs/SDL_init.stub.php`, `SDL_video.stub.php`, `SDL_surface.stub.php`, `SDL_hooks.stub.php`, `SDL_gpu_types.stub.php`, or `SDL_gpu.stub.php`. Each file starts with `@generate-class-entries`. A handle is `final`, `@not-serializable`, private `__construct`, `pointer()`, `fromPointer()`. A struct property uses the C field name. An address parameter says, in the docblock, that any address other than 0 is trusted.
2. `php84 /opt/homebrew/opt/php@8.4/lib/php/build/gen_stub.php stubs` rewrites `stubs/*_arginfo.h`. Commit the stub and the header. Do not edit the header by hand.
3. Implement the function in the C file that already includes that arginfo (`src/SDL_init.c`, `SDL_video.c`, `SDL_surface.c`, `SDL_hooks.c`, `SDL_gpu.c`) or, for render-pass calls, in `src/SDL_gpu_pass.c` with the body only. `SDL_gpu.c` includes `SDL_gpu_arginfo.h` and registers the whole table. A new `.c` file is added to `PHP_NEW_EXTENSION` in `config.m4` and its `sdl3_register_*` is called from `PHP_MINIT_FUNCTION` in `src/sdl3.c`.
4. A new handle class gets `sdl3_ce_<Class>`, `sdl3_handle_setup`, and `SDL3_POINTER_METHODS`. A new struct gets `sdl3_struct_setup`, a constructor when it nests another struct, and `sdl3_<Struct>_from`.
5. `tests/SurfaceTest.php` fails if a stub declaration is missing from the loaded extension. Add a behaviour test. Build and run per [build](/runbooks/build.md).

[^build]: Build runbook
