---
type: Architecture
title: Zephir inline C
description: "%{ … %}" blocks calling SDL_* directly (no separate C ABI layer)
resource: /sdl3/sdl/sdl.zep
tags: [sdl3, architecture, zephir, c]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: sdl-zep
    resource: /sdl3/sdl/sdl.zep
    title: sdl.zep
  - id: surface-zep
    resource: /sdl3/sdl/surface/sdlsurface.zep
    title: sdlsurface.zep
  - id: video-zep
    resource: /sdl3/sdl/video/sdlvideo.zep
    title: sdlvideo.zep
  - id: config
    resource: /config.json
    title: Zephir config
---

# Pattern

Each module `.zep` typically:

1. Declares `namespace Sdl3\SDL\…`
2. Opens an inline C preamble with `#include <SDL3/SDL.h>` (and helpers)
3. Implements `public static function …` methods whose bodies mix Zephir locals with `%{ … %}` C snippets that call `SDL_*`[^sdl-zep]

Example shape (`SDL::SDLInit`):

```zephir
public static function SDLInit(int flags) -> bool
{
    bool result;
    %{
        result = SDL_Init((Uint32) flags);
    }%
    return result;
}
```

# Extra C in preambles

Heavier modules embed static C helpers inside the Zephir preamble:

- Rect/array packing (`sdl3_rect_from_zval`, surface field readers)[^surface-zep]
- Callback bridges (hit-test, event watch, dialog, audio stream callbacks)[^video-zep]

These helpers are **not** a published C ABI for other extensions; they exist only to support the PHP static methods.

# Build path

- Maintainer installers run `zephir fullclean` + `zephir build` (regenerates `ext/`).
- Consumers/`pie` build from the committed `ext/` tree via `phpize` + `--enable-sdl3` — they do not need Zephir.

`config.json` supplies Homebrew/local include and `-lSDL3` link hints for Zephir builds.[^config]

[^sdl-zep]: sdl.zep
[^surface-zep]: sdlsurface.zep
[^video-zep]: sdlvideo.zep
[^config]: Zephir config
