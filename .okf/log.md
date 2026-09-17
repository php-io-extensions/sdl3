# Directory Update Log

## 2026-09-14 (later)
* **Fix**: published version relabeled 0.7.1 → 0.8.0 (0.7.1 never published; wave lands as first 0.8.x release). `composer.json`, `config.json`, `ext/php_sdl3.h` `PHP_SDL3_VERSION`, and every doc reference to the 0.7.1 wave updated. True 0.7.0 history (`ide/0.7.0/` stub path) left alone.

## 2026-09-14
* **Fix (draft)**: [Video](api/video.md) — `?string` loader/name params (`SDLVulkanLoadLibrary`, `SDLGLLoadLibrary`, `SDLCreateRenderer`) throw `TypeError` on non-string (was `Z_STRVAL` on any zval → segfault); Metal layer borrowed; extensions `[]` = failure; driver → surface-extension rule; 32-bit surface caveat. Wave concepts' `generated.by` → `claude-opus-5/claude-code`.
* **Update (draft)**: 0.8.0 wave. [Video](api/video.md) + `SDLMetal` (view/layer) + `SDLVulkan` (loader, instance extensions, surface, presentation). [Events](api/events.md) + `window` reader, rule: every `SDLReadEvent` reader frees — no `SDLFreeEvent` after. `SDLWindowEvents` off [scaffolds](api/reserved-and-scaffolds.md). Proof `examples/proof_stage_hosts.php`.
* **Update (draft)**: [GCC 14 trap](traps/gcc14-warning-flags.md) + [regenerate playbook](playbooks/regenerate-ext.md) — Zephir regen clobbers `config.m4` block and `kernel/{file,main,require}.c` fixes; restore step added.
* **Update (draft)**: version `0.8.0` in overview, packaging, sibling patterns. `ide/0.7.0/` stubs not regenerated.

## 2026-08-09
* **Fix (draft)**: [Herd extension_dir](traps/herd-extension-dir.md) — `install-macos-herd.sh` failed ABI check on `ini_get('extension_dir')` basename `extensions` vs Homebrew `20240924`; now uses `PHP_EXTENSION_DIR` / PHP API. Post-install **ad-hoc codesign** required or dyld SIGKILLs PHP (`Code Signature Invalid`, exit 137). Verified Herd load → `sdl3` **0.7.0**.
* **Initialization**: Created OKF v0.2 knowledge bundle for `php-io-extensions/sdl3` at package root `.okf/`, grounded in `composer.json` / `config.json` / `ext/php_sdl3.h` (**0.7.0**), `sdl3/sdl/**/*.zep`, `ext/config.m4`, README, installers (`install-macos.sh`, `install-macos-herd.sh`, `install-debian-trixie.sh`, `install-jetpack6.sh`), and `examples/proof_of_work.php`.
* **Creation**: Orientation (overview, stack segmentation), architecture (stack, Zephir inline C, handle/struct model), API index + module concepts (SDL, error, properties, video, surface, render, timer, events, input, audio, dialog, GPU, reserved/scaffolds), build/packaging, conventions, traps, playbooks; package-root `AGENTS.md`; `.gitattributes` `export-ignore` for `.okf/` and `AGENTS.md`.
* **Note**: All concepts marked `status: draft` pending Angel human verification. API concepts summarize module scope and point at README/`ide/0.7.0` for full method tables — they do not invent APIs beyond `.zep` on disk. Empty dirs (`camera`, `cpuinfo`, `filesystem`, `haptic`, `io`) and empty reserved classes documented as scaffolds only. Downstream `microscrap/sdl3` and `microscrap/sdl3-gfx` mentioned only as composition boundaries.

## 2026-09-17
* **Update**: `SDLEvents::SDLWaitEventTimeout` returns `?array` (`ptr`, `event_type`) like `SDLWaitEvent`/`SDLPollEvent`; a caller can route what it woke on.
