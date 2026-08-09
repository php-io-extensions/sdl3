---
type: Convention
title: Constants outside the extension
description: No PHP class constants; SDL flags live in app or microscrap enums
tags: [sdl3, convention, constants, enums]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: readme
    resource: /README.md
    title: README.md
  - id: demo
    resource: /examples/proof_of_work.php
    title: proof_of_work.php
  - id: sdl-zep
    resource: /sdl3/sdl/sdl.zep
    title: sdl.zep
---

# Rule

Zephir classes under `Sdl3\SDL\` expose **methods**, not PHP class constants for `SDL_*` flags/enums.[^sdl-zep]

Examples and apps define locals (as in README quick start / `proof_of_work.php`) or consume **microscrap** backed enums.[^readme][^demo]

```php
const SDL_INIT_VIDEO = 0x20;
const SDL_EVENT_QUIT = 0x100;
const SDL_PIXELFORMAT_RGBA8888 = 373694468;
```

Prefer int-/string-backed PHP Enums (FULLY UPPERCASE cases) in application or microscrap layers — not new class constants inside this extension.

[^readme]: README.md
[^demo]: proof_of_work.php
[^sdl-zep]: sdl.zep
