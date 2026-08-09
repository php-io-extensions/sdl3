---
type: Trap
title: IDE stub path lag
description: Prefer ide/0.7.0 stubs; README may still cite older ide/ trees
resource: /ide/0.7.0
tags: [sdl3, trap, ide, stubs]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: config
    resource: /config.json
    title: config.json stubs path
  - id: readme
    resource: /README.md
    title: README.md
---

# Trap

`config.json` generates stubs under `ide/%version%/%namespace%/`. For **0.7.0**, use `ide/0.7.0/Sdl3/SDL/`.[^config]

Older trees (`ide/0.2.0`, `ide/0.5.0`) may remain in the repo. README prose can lag and mention `ide/0.2.0/` — treat **0.7.0** as the current stub root for this release line.[^readme]

When regenerating after API changes, refresh `ide/0.7.0/` and avoid editing stale stub trees as if they were source of truth.

[^config]: config.json stubs path
[^readme]: README.md
