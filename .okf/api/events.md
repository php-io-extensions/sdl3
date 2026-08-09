---
type: CoreType
title: Events/*
description: Event queue, keyboard, mouse, display, clipboard, drop, watch, quit
resource: /sdl3/sdl/events/sdlevents.zep
tags: [sdl3, api, events]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: events-zep
    resource: /sdl3/sdl/events/sdlevents.zep
    title: sdlevents.zep
  - id: readme
    resource: /README.md
    title: Package README
---

# Role

Event subsystem split across classes under `Sdl3\SDL\Events\`. Polled events are assoc arrays with a numeric `type` key (`SDL_EVENT_*`).[^events-zep][^readme]

# Implemented classes

| Class | Focus | ~methods |
|-------|-------|----------|
| `SDLEvents` | Poll/wait/peep/flush/push/pump; keyboard state snapshot | 13 |
| `SDLCategories` | Enable/register events; window-from-event; description | 5 |
| `SDLKeyboard` | Devices, mods, scancodes, text input, read helpers | 28 |
| `SDLMouse` | Devices, warp/relative, cursors, read helpers | 27 |
| `SDLDisplayEvents` | Displays, modes, orientations, read display event | 13 |
| `SDLClipboardEvents` | Clipboard + primary selection | 10 |
| `SDLDropEvents` | `SDLReadDropEvent` | 1 |
| `SDLEventWatch` | Filters/watches (PHP callbacks) | 5 |
| `SDLQuit` | `SDLReadQuitEvent` | 1 |

# Reserved empty event classes

`SDLKeymap`, `SDLScancodeTables`, `SDLWindowEvents` ship as empty class shells — see [Reserved & empty scaffolds](/api/reserved-and-scaffolds.md).

# Loop sketch

```php
use Sdl3\SDL\Events\SDLEvents;

while (($ev = SDLEvents::SDLPollEvent()) !== null) {
    if (($ev['type'] ?? 0) === $SDL_EVENT_QUIT) {
        break;
    }
}
```

Define `SDL_EVENT_*` in app code or microscrap — not as extension class constants.[^readme]

[^events-zep]: sdlevents.zep
[^readme]: Package README
