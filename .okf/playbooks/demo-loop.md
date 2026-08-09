---
type: Playbook
title: Minimal demo loop
description: examples/proof_of_work.php — headless surface + software renderer
resource: /examples/proof_of_work.php
tags: [sdl3, playbook, demo]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: demo
    resource: /examples/proof_of_work.php
    title: proof_of_work.php
  - id: readme
    resource: /README.md
    title: Package README
---

# Goal

Prove the extension loads and can run the headless surface + software-renderer pipeline **without** a display server.[^demo][^readme]

# Prerequisites

- Built/installed `sdl3.so`
- libSDL3 ≥ 3.4.0 discoverable at runtime

# Canonical demo

```bash
php -d extension=ext/modules/sdl3.so examples/proof_of_work.php
# or, if globally installed:
php examples/proof_of_work.php
```

Expected summary line:

```text
All checks passed — sdl3 extension is working correctly.
```

# What it exercises

1. Extension loaded
2. `SDL::SDLGetVersion` / `SDLGetPlatform`
3. Surface create/mutate + software renderer clear/present path

# Related proofs

| Script | Focus |
|--------|--------|
| `proof_surface.php` | Surface round-trip |
| `proof_render.php` | Renderer |
| `proof_video.php` | Window (needs display) |
| `proof_audio.php` / `proof_gpu.php` / input / dialog / properties | Subsystem smoke |

# Acceptance criteria

- Headless run exits successfully on Linux or macOS CI/dev machines without a GUI.
- No invented APIs; uses `Sdl3\SDL\{SDL,SDLError,Surface\SDLSurface,Render\SDLRender}` only.

[^demo]: proof_of_work.php
[^readme]: Package README
