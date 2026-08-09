---
type: Convention
title: Committed ext/ notes
description: config.m4, GCC 14 flags, stubs, and what belongs in git
resource: /ext/config.m4
tags: [sdl3, build, packaging]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: config-m4
    resource: /ext/config.m4
    title: Portable ext/config.m4
  - id: php-h
    resource: /ext/php_sdl3.h
    title: php_sdl3.h
  - id: config
    resource: /config.json
    title: Zephir config
  - id: composer
    resource: /composer.json
    title: PIE package manifest
---

# What ships in `ext/`

PIE/`phpize` builds from the pre-generated C tree under `ext/` (`build-path: ext`).[^composer]

Notable pieces:

| Artifact | Role |
|----------|------|
| `ext/config.m4` | `--enable-sdl3`, pkg-config for SDL3, GCC 14 warning demotion |
| `ext/php_sdl3.h` | `PHP_SDL3_VERSION` (`0.7.0`) |
| `ext/sdl3/` + kernel | Zephir-generated sources |

# GCC 14

`config.m4` appends `-Wno-error=incompatible-pointer-types` (and related) so Zephir-generated C builds on newer distros without treating long-standing warnings as hard errors.[^config-m4] See [GCC 14 trap](/traps/gcc14-warning-flags.md).

# Stubs

`config.json` stubs path: `ide/%version%/%namespace%/`. Prefer `ide/0.7.0/Sdl3/SDL/` for 0.7.x — older `ide/0.2.0` / `ide/0.5.0` trees may coexist.[^config] See [IDE stub paths](/traps/ide-stub-paths.md).

# Do not commit phpize junk

After local `phpize`/`make`, avoid committing generated `Makefile`, `configure`, `autom4te.cache`, `modules/*.so`, etc. Keep the portable sources + `config.m4` that installers/PIE expect.

Unlike vulkan/metal, this package currently has **no** `scripts/prepare-ext.sh` — maintainers regenerate via `zephir fullclean` + `zephir build` (installers) or an equivalent Zephir generate workflow. See [Regenerate ext](/playbooks/regenerate-ext.md).

[^config-m4]: Portable ext/config.m4
[^php-h]: php_sdl3.h
[^config]: Zephir config
[^composer]: PIE package manifest
