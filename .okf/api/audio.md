---
type: CoreType
title: Sdl3\\SDL\\Audio\\SDLAudio
description: Devices, streams, binary I/O
resource: /sdl3/sdl/audio/sdlaudio.zep
tags: [sdl3, api, audio]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: audio-zep
    resource: /sdl3/sdl/audio/sdlaudio.zep
    title: sdlaudio.zep
  - id: readme
    resource: /README.md
    title: Package README
  - id: demo
    resource: /examples/proof_audio.php
    title: proof_audio.php
---

# Role

Audio devices and streams (~57 methods). Device/stream handles are opaque `int`.[^audio-zep]

# Patterns

| Concept | PHP shape |
|---------|-----------|
| `SDL_AudioSpec` | `["format" => int, "channels" => int, "freq" => int]` |
| Push/pull | PHP binary `string` |
| WAV load | `SDLLoadWAV(string $path)` → array (path-based; not IO) |
| Callbacks | bridge pattern for stream get/put and postmix (advanced) |

`SDL_LoadWAV_IO` is **not** bound — see [IOStream unbound](/traps/iostream-unbound.md).[^readme]

# Proof

`examples/proof_audio.php`.[^demo]

[^audio-zep]: sdlaudio.zep
[^readme]: Package README
[^demo]: proof_audio.php
