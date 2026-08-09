---
type: Trap
title: Windows excluded
description: PIE os-families-exclude windows — do not claim Windows support
resource: /composer.json
tags: [sdl3, trap, windows]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: composer
    resource: /composer.json
    title: composer.json
  - id: readme
    resource: /README.md
    title: README.md
---

# Trap

`composer.json` sets `"os-families-exclude": ["windows"]`. README states Windows is not currently supported.[^composer][^readme]

Do not document install paths, MSVC notes, or claim PIE installs on Windows until that exclusion is removed and verified.

User-facing OS copy: **Linux** and **macOS** (prefer “macOS” over Darwin in product text).

[^composer]: composer.json
[^readme]: README.md
