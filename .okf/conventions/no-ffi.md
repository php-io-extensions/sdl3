---
type: Convention
title: No FFI
description: Extension-only binding; no PHP FFI fallback
tags: [sdl3, convention, ffi]
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

# Rule

This package is a compiled PHP extension (`type: php-ext`). There is **no** PHP FFI code path, no pure-PHP polyfill, and no optional FFI mode.[^composer][^readme]

Consumers must install `sdl3.so` (PIE or installers) and load `extension=sdl3`.

Downstream PHP packages (microscrap/sdl3) may wrap this extension’s classes — they still require the native extension.

[^composer]: composer.json
[^readme]: README.md
