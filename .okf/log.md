# Log

## 2026-10-04

Created the bundle for 0.10.0. The extension binds SDL 3.2: core and events, windows and properties, surfaces and memory streams, the GL, Metal and Vulkan hooks, and SDL_GPU through blit. The suite is 28 passed, 1 skipped, 622 assertions on Homebrew PHP 8.4 NTS and ZTS, and 28 passed, 1 skipped, 618 assertions on the Pi (distro SDL 3.2.10, Vulkan). The skipped test is Vulkan instance extensions on the Mac and the Metal view on the Pi. The gate's stencil-then-cover triangle, resolved from 4 samples and blitted, reads back the same on Metal and on V3DV, with the hypotenuse neither solid red nor solid clear.
