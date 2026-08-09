---
type: Trap
title: Herd extension_dir is not the Zend API path
description: "Herd overrides ini_get('extension_dir') to …/config/php/NN/extensions — do not parse that basename for ZEND_MODULE_API_NO."
tags: [trap, herd, macos, install, abi]
status: draft
generated: { by: cursor-agent/grok-4.5, at: "2026-08-09T19:25:00Z" }
sources:
  - id: herd-installer
    resource: /install-macos-herd.sh
    title: install-macos-herd.sh
---

# Trap

Laravel Herd sets `extension_dir` via drop-in ini to a flat folder:

`~/Library/Application Support/Herd/config/php/84/extensions`

`basename(...)` → `extensions`. That is **not** the Zend module API suffix.

Homebrew `php-config --extension-dir` still looks like `…/pecl/20240924`.

# Do

- ABI-check with compile-time `PHP_EXTENSION_DIR` (`…/no-debug-non-zts-20240924`) or `php -i` → `PHP API`.
- Install the `.so` into Herd’s config dir (and point `30-sdl3.ini` at the absolute path) — that is separate from the ABI check.
- Prefer matching Homebrew `php` / `phpize` major.minor to Herd (8.4 ↔ 8.4).
- After `cp`, **ad-hoc codesign** the `.so` (`codesign --force --sign -`) — otherwise dyld kills PHP with `Code Signature Invalid` (exit 137).

# Related

- [Zephir + PIE install](../build/zephir-and-pie.md)
