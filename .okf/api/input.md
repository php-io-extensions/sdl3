---
type: CoreType
title: Input (Joystick, Gamepad)
description: Joystick and gamepad APIs
resource: /sdl3/sdl/input/sdljoystick.zep
tags: [sdl3, api, input, joystick, gamepad]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T16:47:00Z }
sources:
  - id: joy-zep
    resource: /sdl3/sdl/input/sdljoystick.zep
    title: sdljoystick.zep
  - id: pad-zep
    resource: /sdl3/sdl/input/sdlgamepad.zep
    title: sdlgamepad.zep
  - id: readme
    resource: /README.md
    title: Package README
  - id: joy-demo
    resource: /examples/proof_joystick.php
    title: proof_joystick.php
  - id: pad-demo
    resource: /examples/proof_gamepad.php
    title: proof_gamepad.php
---

# Role

Raw joystick and higher-level gamepad bindings. Handles are opaque `int`; instance IDs are plain `int`. GUIDs are ASCII strings via `SDL_GUIDToString`.[^joy-zep][^pad-zep][^readme]

## `Sdl3\SDL\Input\SDLJoystick` (~58)

Enumerate/open/close joysticks; axes/balls/hats/buttons; rumble/LED; virtual joystick attach (`SDLAttachVirtualJoystick(array $desc)` matching `SDL_VirtualJoystickDesc` field names).[^readme]

## `Sdl3\SDL\Input\SDLGamepad` (~72)

Mappings, open/close, standard axes/buttons, touchpads, sensors, rumble/LED. `SDL_AddGamepadMappingsFromIO` is **not** bound (needs `SDL_IOStream`).[^readme]

Bindings query returns arrays of assoc arrays (`input_type`, `output_type`, …).[^readme]

# Proofs

- `examples/proof_joystick.php`[^joy-demo]
- `examples/proof_gamepad.php`[^pad-demo]

[^joy-zep]: sdljoystick.zep
[^pad-zep]: sdlgamepad.zep
[^readme]: Package README
[^joy-demo]: proof_joystick.php
[^pad-demo]: proof_gamepad.php
