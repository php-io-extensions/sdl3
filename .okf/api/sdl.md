---
type: CoreType
title: Sdl3\\SDL\\SDL
description: Init/quit, version, platform, pixel helpers
resource: /sdl3/sdl/sdl.zep
tags: [sdl3, api, lifecycle]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: sdl-zep
    resource: /sdl3/sdl/sdl.zep
    title: sdl.zep
  - id: readme
    resource: /README.md
    title: Package README
  - id: demo
    resource: /examples/proof_of_work.php
    title: proof_of_work.php
---

# Role

Static facade for SDL lifecycle and process/platform metadata. Call `SDLInit` / `SDLInitSubSystem` before most other APIs; `SDLQuit` on shutdown (module unload also runs `SDL_Quit()` via config destructor).[^sdl-zep][^readme]

# Surface (groups)

| Group | Methods (see README for signatures) |
|-------|-------------------------------------|
| Init | `SDLInit`, `SDLInitSubSystem`, `SDLWasInit`, `SDLQuit`, `SDLQuitSubSystem`, `SDLExitProcess` |
| Pixels | `SDLGetPixelFormatDetails`, `SDLGetRGBA`, `SDLMapRGBA` |
| Version / platform | `SDLGetVersion`, `SDLGetRevision`, `SDLGetPlatform`, `SDLGetSandbox`, `SDLIsTablet`, `SDLIsTV` |
| App metadata | `SDLSetAppMetadata`, `SDLSetAppMetadataProperty`, `SDLGetAppMetadataProperty` |
| Main thread | `SDLSetMainReady`, `SDLIsMainThread` |
| RNG | `SDLRand`, `SDLRandf` |

`SDLGetVersion()` returns SDL’s packed integer: `major = v / 1_000_000`, `minor = (v / 1_000) % 1_000`, `patch = v % 1_000`.[^readme]

# Examples

```php
use Sdl3\SDL\SDL;

SDL::SDLInit(0x20); // SDL_INIT_VIDEO — define flags in app/microscrap
echo SDL::SDLGetPlatform(), PHP_EOL;
SDL::SDLQuit();
```

Proof: `examples/proof_of_work.php` prints version/platform before surface work.[^demo]

[^sdl-zep]: sdl.zep
[^readme]: Package README
[^demo]: proof_of_work.php
