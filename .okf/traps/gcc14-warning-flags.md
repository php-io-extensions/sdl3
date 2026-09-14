---
type: Trap
title: GCC 14 warning-as-error
description: config.m4 demotes Zephir-hostile -Werror conversions on modern GCC
resource: /ext/config.m4
tags: [sdl3, trap, gcc, build]
status: draft
generated: { by: claude-opus-5/claude-code, at: 2026-09-14T00:00:00Z }
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

# Regen clobbers hand-kept fixes

`zephir build` (Zephir 0.19) rewrites these committed files; restore after every regen:

- `ext/config.m4` — the GCC 14 `-Wno-error=…` block is dropped.
- `ext/kernel/file.c`, `ext/kernel/require.c` — Zephir emits `zval_ptr_dtor(<zend_string*>)`; committed tree keeps `zend_string_release`.
- `ext/kernel/main.c` — Zephir emits `zend_hash_str_exists(…) != NULL` (bool vs pointer); committed tree keeps the bare test.

`git checkout HEAD -- ext/kernel/{file,main,require}.c`, then re-insert the `config.m4` block. `install-macos-herd.sh` always regenerates, so it installs the clobbered kernel — rebuild from the restored `ext/` with `phpize` before trusting a Mac `.so`.

[^config-m4]: config.m4
[^install]: install-macos.sh
