---
type: Trap
title: Destroy opaque handles
description: PHP GC does not free SDL objects behind int handles
tags: [sdl3, trap, memory]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: ownership
    resource: /conventions/handle-ownership.md
    title: Handle ownership
  - id: config
    resource: /config.json
    title: Module destructor SDL_Quit
---

# Trap

Opaque handles are ordinary PHP integers. Unsetting a variable does **not** call `SDL_DestroyWindow` / `SDL_DestroyRenderer` / etc.

Always call the matching destroy/close/release API. Relying solely on module unload (`SDL_Quit()` in config destructor) is a last-resort process teardown, not a substitute for correct pairing — see [Handle ownership](/conventions/handle-ownership.md).[^ownership][^config]

[^ownership]: Handle ownership
[^config]: Module destructor SDL_Quit
