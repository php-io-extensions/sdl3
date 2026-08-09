---
type: CoreType
title: Sdl3\\SDL\\Dialog\\SDLDialog
description: Async native file dialogs
resource: /sdl3/sdl/dialog/sdldialog.zep
tags: [sdl3, api, dialog]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: dialog-zep
    resource: /sdl3/sdl/dialog/sdldialog.zep
    title: sdldialog.zep
  - id: readme
    resource: /README.md
    title: Package README
  - id: demo
    resource: /examples/proof_dialog.php
    title: proof_dialog.php
---

# Role

Four asynchronous native dialog entry points. Callbacks fire during event pumping.[^dialog-zep][^readme]

| Method | Notes |
|--------|--------|
| `SDLShowOpenFileDialog` | filters, multi-select |
| `SDLShowSaveFileDialog` | |
| `SDLShowOpenFolderDialog` | |
| `SDLShowFileDialogWithProperties` | type + properties bag |

# Callback contract

- Filters: arrays of `["name" => …, "pattern" => …]`.
- PHP callback receives `(?array $filelist, int $filter_index)` — `null` on error, `[]` on cancel.[^readme]

# Proof

`examples/proof_dialog.php` (needs a display / windowing environment).[^demo]

[^dialog-zep]: sdldialog.zep
[^readme]: Package README
[^demo]: proof_dialog.php
