---
type: Playbook
title: Regenerate committed ext/
description: Maintainer Zephir build steps before tagging
resource: /install-macos.sh
tags: [sdl3, playbook, packaging, zephir]
status: draft
generated: { by: claude-opus-5/claude-code, at: 2026-09-14T00:00:00Z }
sources:
  - id: install
    resource: /install-macos.sh
    title: install-macos.sh
  - id: config
    resource: /config.json
    title: config.json
  - id: php-h
    resource: /ext/php_sdl3.h
    title: php_sdl3.h
  - id: demo
    resource: /examples/proof_of_work.php
    title: proof_of_work.php
---

# When

Before tagging a Packagist/PIE release, or after changing `.zep` / `config.json` / link flags.

# Steps

1. On Linux or macOS with Zephir + matching PHP + libSDL3:

```bash
# Prefer installer path (fullclean + build + install), or:
zephir fullclean
zephir build
```

Set `ZEPHIR_BIN` if `zephir` is not on `PATH`.[^install]

2. Restore hand-kept files (`config.m4` GCC 14 block, `kernel/{file,main,require}.c`) — see [GCC 14 trap](/traps/gcc14-warning-flags.md).

3. Confirm version strings match **0.8.0** in `composer.json`, `config.json`, and `PHP_SDL3_VERSION` in `ext/php_sdl3.h`.[^config][^php-h]

4. Smoke:

```bash
php -n -d extension=./ext/modules/sdl3.so --ri sdl3
php -d extension=./ext/modules/sdl3.so examples/proof_of_work.php
```

5. Refresh IDE stubs under `ide/0.7.0/` when the public surface changes.

6. Commit regenerable `ext/` sources + stubs that belong in git — not phpize junk (`Makefile`, `modules/*.so`, …).

7. Update `.okf` + `log.md` if the public surface or packaging changed.

# Notes

- There is currently **no** `scripts/prepare-ext.sh` (unlike vulkan/metal). Installers are the canonical regenerate path.
- Preserve `ext/config.m4` GCC 14 demotion flags across regenerations — see [GCC 14 trap](/traps/gcc14-warning-flags.md).

[^install]: install-macos.sh
[^config]: config.json
[^php-h]: php_sdl3.h
[^demo]: proof_of_work.php
