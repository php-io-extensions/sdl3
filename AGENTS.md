# Agent guidance — php-io-extensions/sdl3

1. **Read [`.okf/index.md`](.okf/index.md) first** before changing architecture, API, or packaging.
2. Open only the concept files you need; prefer `status: stable` when present (most are currently `draft`).
3. This package is **Linux + macOS** SDL3 bindings — Windows excluded. Links **libSDL3 ≥ 3.4.0**. No FFI.
4. Public PHP API: static methods under `Sdl3\SDL\…` (SDL, SDLError, SDLProperties, Video, Surface, Render, Timer, Events/*, Input, Audio, Dialog, Gpu). Opaque SDL objects are PHP `int` handles; structs are assoc arrays with C field names.
5. Empty scaffolds (no `.zep` yet): `camera`, `cpuinfo`, `filesystem`, `haptic`, `io`. Reserved empty classes: `SDLAssert`, `SDLLog`, `SDLList`, `SDLUtils` (+ empty Events helpers). Do not invent APIs for them.
6. Build: Zephir sources in `sdl3/sdl/**/*.zep`; committed C under `ext/`. Installers: `install-macos.sh`, `install-macos-herd.sh`, `install-debian-trixie.sh`, `install-jetpack6.sh`. PIE: `pie install php-io-extensions/sdl3`.
7. Demo: `examples/proof_of_work.php` (headless software renderer). Additional proofs under `examples/proof_*.php`.
8. Downstream: `microscrap/sdl3` (PHP bindings/enums) and `microscrap/sdl3-gfx` (tubes companion) are **peers** — document composition only; do not nest their docs here.
9. When you learn a durable package fact, **update the matching `.okf` concept**, bump `generated.at`, and append `.okf/log.md`.
10. Do not invent APIs not present in `.zep` / `ext/` / README. Keep the OKF bundle at package root only — never nest `.okf` under `sdl3/sdl/`.
