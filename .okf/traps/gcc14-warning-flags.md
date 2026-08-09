---
type: Trap
title: GCC 14 warning-as-error
description: config.m4 demotes Zephir-hostile -Werror conversions on modern GCC
resource: /ext/config.m4
tags: [sdl3, trap, gcc, build]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: config-m4
    resource: /ext/config.m4
    title: config.m4
  - id: install
    resource: /install-macos.sh
    title: install-macos.sh
---

# Trap

Zephir-generated C trips GCC 14+ hard errors (`-Wincompatible-pointer-types`, `-Wint-conversion`, …). `ext/config.m4` demotes those back to warnings so Debian Trixie / newer distros can build.[^config-m4]

macOS installers also export conservative `-Wno-error…` CFLAGS during Zephir builds.[^install]

If a clean rebuild fails with pointer-type errors after regenerating `ext/`, verify `config.m4` still carries the demotion flags before “fixing” generated kernel code by hand.

[^config-m4]: config.m4
[^install]: install-macos.sh
