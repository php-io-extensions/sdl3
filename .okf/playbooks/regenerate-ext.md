---
type: Playbook
title: Regenerate committed ext/
description: Maintainer Zephir build steps before tagging
resource: /install-macos.sh
tags: [sdl3, playbook, packaging, zephir]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
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

2. Confirm version strings match **0.7.0** in `composer.json`, `config.json`, and `PHP_SDL3_VERSION` in `ext/php_sdl3.h`.[^config][^php-h]

3. Smoke:

```bash
php -n -d extension=./ext/modules/sdl3.so --ri sdl3
php -d extension=./ext/modules/sdl3.so examples/proof_of_work.php
```

4. Refresh IDE stubs under `ide/0.7.0/` when the public surface changes.

5. Commit regenerable `ext/` sources + stubs that belong in git — not phpize junk (`Makefile`, `modules/*.so`, …).

6. Update `.okf` + `log.md` if the public surface or packaging changed.

# Notes

- There is currently **no** `scripts/prepare-ext.sh` (unlike vulkan/metal). Installers are the canonical regenerate path.
- Preserve `ext/config.m4` GCC 14 demotion flags across regenerations — see [GCC 14 trap](/traps/gcc14-warning-flags.md).

[^install]: install-macos.sh
[^config]: config.json
[^php-h]: php_sdl3.h
[^demo]: proof_of_work.php
