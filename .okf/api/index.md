# Public PHP API

All public classes live under `Sdl3\SDL` and expose **static** methods. Opaque SDL objects are PHP `int` handles. C structs are assoc arrays with SDL field names. Full method tables live in `README.md` and `ide/0.7.0/`; concepts below summarize module scope grounded in `.zep` on disk.

Method counts below are `public static function` entries in the named `.zep` files (approximate surface size, not a stability guarantee).

* [Sdl3\\SDL\\SDL](sdl.md) - Lifecycle, version, platform, pixel helpers (~22)
* [Sdl3\\SDL\\SDLError](sdlerror.md) - Error get/set/clear (~4)
* [Sdl3\\SDL\\SDLProperties](sdlproperties.md) - Property bags (~20)
* [Video (SDLVideo, SDLGL)](video.md) - Windows (~83) + GL/EGL (~20)
* [Surface\\SDLSurface](surface.md) - Surfaces & pixels (~72)
* [Render\\SDLRender](render.md) - Renderer & textures (~94)
* [Timer\\SDLTimer](timer.md) - Delay / ticks (~2)
* [Events/\*](events.md) - Queue + device event helpers
* [Input (Joystick, Gamepad)](input.md) - Joystick (~58) + Gamepad (~72)
* [Audio\\SDLAudio](audio.md) - Devices & streams (~57)
* [Dialog\\SDLDialog](dialog.md) - Async file dialogs (~4)
* [Gpu\\SDLGPU](gpu.md) - GPU API (~105)
* [Reserved & empty scaffolds](reserved-and-scaffolds.md) - Empty classes and empty dirs
