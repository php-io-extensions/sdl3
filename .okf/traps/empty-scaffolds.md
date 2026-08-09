---
type: Trap
title: Empty scaffolds
description: Subsystem directories exist but have no Zephir sources yet
resource: /sdl3/sdl/camera
tags: [sdl3, trap, scaffold]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: readme
    resource: /README.md
    title: README.md
  - id: reserved
    resource: /api/reserved-and-scaffolds.md
    title: Reserved & empty scaffolds
---

# Trap

Directories `camera`, `cpuinfo`, `filesystem`, `haptic`, and `io` under `sdl3/sdl/` are **empty** (no `.zep`). Reserved classes (`SDLAssert`, `SDLLog`, `SDLList`, `SDLUtils`, some Events helpers) are empty shells.[^readme]

Agents often assume folder presence ⇒ API. Treat them as placeholders only — see [Reserved & empty scaffolds](/api/reserved-and-scaffolds.md).

[^readme]: README.md
[^reserved]: Reserved & empty scaffolds
