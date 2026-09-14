---
type: CoreType
title: Events/*
description: Event queue, keyboard, mouse, display, clipboard, drop, watch, quit, window
resource: /sdl3/sdl/events/sdlevents.zep
tags: [sdl3, api, events]
status: draft
generated: { by: claude-opus-5/claude-code, at: 2026-09-14T00:00:00Z }
sources:
  - id: events-zep
    resource: /sdl3/sdl/events/sdlevents.zep
    title: sdlevents.zep
  - id: window-zep
    resource: /sdl3/sdl/events/sdlwindowevents.zep
    title: sdlwindowevents.zep
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
| `SDLWindowEvents` | `SDLReadWindowEvent` (0.8.0) | 1 |

# Reserved empty event classes

`SDLKeymap`, `SDLScancodeTables` ship as empty class shells — see [Reserved & empty scaffolds](/api/reserved-and-scaffolds.md).

# Reading events

`SDLPollEvent()` / `SDLWaitEvent()` → `['ptr' => int, 'event_type' => int]` or `null`; `ptr` = emalloc'd `SDL_Event`.

`SDLReadEvent($ptr, $key)` decodes by key: `key`, `text`, `edit`, `edit_candidates`, `kdevice`, `display`, `quit`, `drop`, `mdevice`, `motion`, `button`, `wheel`, `window`. Unknown key → frees, throws `RuntimeException`.[^events-zep]

**Rule:** every `SDLReadEvent` reader frees the event — never `SDLFreeEvent` after it. Unread events → `SDLFreeEvent`.

`window` → `SDLWindowEvents::SDLReadWindowEvent`: `['type', 'timestamp', 'window_id', 'data1', 'data2']` for any `SDL_EVENT_WINDOW_*`.[^window-zep]

```php
use Sdl3\SDL\Events\SDLEvents;

while (! is_null($ev = SDLEvents::SDLPollEvent())) {
    if ($ev['event_type'] === 514) {                    // SDL_EVENT_WINDOW_SHOWN
        $window = SDLEvents::SDLReadEvent($ev['ptr'], 'window');   // freed
        continue;
    }
    SDLEvents::SDLFreeEvent($ev['ptr']);
}
```

Define `SDL_EVENT_*` in app code or microscrap — not as extension class constants.[^readme]

[^events-zep]: sdlevents.zep
[^window-zep]: sdlwindowevents.zep
[^readme]: Package README
