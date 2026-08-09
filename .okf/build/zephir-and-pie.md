---
type: Playbook
title: Zephir + PIE install
description: Platform installers, PIE, and phpize builds on Linux and macOS
resource: /composer.json
tags: [sdl3, build, pie, zephir]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: install
    resource: /install-macos.sh
    title: install-macos.sh
  - id: herd
    resource: /install-macos-herd.sh
    title: install-macos-herd.sh
  - id: debian
    resource: /install-debian-trixie.sh
    title: install-debian-trixie.sh
  - id: jetpack
    resource: /install-jetpack6.sh
    title: install-jetpack6.sh
  - id: readme
    resource: /README.md
    title: Package README
  - id: config-m4
    resource: /ext/config.m4
    title: Portable ext/config.m4
---

# Requirements

| Component | Notes |
|-----------|--------|
| OS | Linux or macOS (Windows excluded) |
| PHP | ≥ 8.2 with matching `phpize` / headers |
| SDL3 | ≥ 3.4.0 via `pkg-config sdl3` |
| Zephir | Required by platform installers (`ZEPHIR_BIN` optional); not required for PIE/`phpize` from committed `ext/` |
| Compiler | C11 (`gcc`, `clang`, Apple Clang) |

Tested targets (README): macOS (Apple Silicon + Intel), Debian Trixie, Raspberry Pi OS, JetPack 6.[^readme]

# PIE (consumers)

```bash
pie install php-io-extensions/sdl3
```

Uses `type: php-ext`, `extension-name: sdl3`, `build-path: "ext"`, `--enable-sdl3`. Ensure libSDL3 is installed first.[^composer]

# Platform installers

```bash
bash install-macos.sh            # Homebrew SDL3 + zephir build
bash install-macos-herd.sh       # Laravel Herd PHP on macOS
bash install-debian-trixie.sh    # Debian Trixie / Raspberry Pi OS
bash install-jetpack6.sh         # JetPack 6 / Ubuntu 22.04 (builds SDL3 from source)
```

Installers write `./build.log` and enable the extension across detected SAPIs.[^install][^herd][^debian][^jetpack]

macOS installer also verifies OpenGL.framework (expected built into macOS) for SDL GL paths.[^install]

# Manual build from committed `ext/`

```bash
cd ext
phpize
./configure --enable-sdl3
make -j"$(nproc 2>/dev/null || sysctl -n hw.logicalcpu)"
sudo make install
```

Non-standard SDL3 prefix: export `PKG_CONFIG_PATH=…` before configure.[^readme]

# Verify

```bash
php -r 'echo Sdl3\SDL\SDL::SDLGetPlatform(), PHP_EOL;'
php examples/proof_of_work.php
```

[^composer]: PIE package manifest
[^install]: install-macos.sh
[^herd]: install-macos-herd.sh
[^debian]: install-debian-trixie.sh
[^jetpack]: install-jetpack6.sh
[^readme]: Package README
[^config-m4]: Portable ext/config.m4
