---
type: CoreType
title: Sdl3\\SDL\\SDLProperties
description: Property bags (SDL_PropertiesID as int)
resource: /sdl3/sdl/sdlproperties.zep
tags: [sdl3, api, properties]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: props-zep
    resource: /sdl3/sdl/sdlproperties.zep
    title: sdlproperties.zep
  - id: readme
    resource: /README.md
    title: Package README
  - id: demo
    resource: /examples/proof_properties.php
    title: proof_properties.php
---

# Role

Bind SDL property bags. `SDL_PropertiesID` values are plain `int` handles.[^props-zep][^readme]

# Surface (groups)

| Group | Methods |
|-------|---------|
| Lifecycle | `SDLGetGlobalProperties`, `SDLCreateProperties`, `SDLCopyProperties`, `SDLDestroyProperties` |
| Locking | `SDLLockProperties`, `SDLUnlockProperties` |
| Setters | `SDLSetPointerProperty`, `SDLSetStringProperty`, `SDLSetNumberProperty`, `SDLSetFloatProperty`, `SDLSetBooleanProperty` |
| Getters | `SDLHasProperty`, `SDLGetPropertyType`, `SDLGetPointerProperty`, `SDLGetStringProperty`, `SDLGetNumberProperty`, `SDLGetFloatProperty`, `SDLGetBooleanProperty` |
| Misc | `SDLClearProperty`, `SDLEnumerateProperties` |

# Notes

- Pointer properties store opaque handles like renderers/surfaces.
- `SDL_SetPointerPropertyWithCleanup` is **intentionally unbound** (cleanup callbacks on arbitrary pointers are unsafe from PHP).[^readme]
- Proof: `examples/proof_properties.php`.[^demo]

[^props-zep]: sdlproperties.zep
[^readme]: Package README
[^demo]: proof_properties.php
