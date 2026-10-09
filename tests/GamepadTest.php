<?php

declare(strict_types=1);

/** A virtual device on SDL's joystick subsystem, which this file starts once and never quits: the id, detached after the test. */
function virtualDevice(int $type, int $axes, int $buttons, int $hats, string $name): int
{
    static $up = false;
    if (! $up) {
        SDL_InitSubSystem(SDL_INIT_GAMEPAD) || throw new RuntimeException('SDL_InitSubSystem: '.SDL_GetError());
        $up = true;
    }
    $desc = new SDL_VirtualJoystickDesc();
    $desc->type = $type;
    $desc->naxes = $axes;
    $desc->nbuttons = $buttons;
    $desc->nhats = $hats;
    $desc->name = $name;
    $id = SDL_AttachVirtualJoystick($desc);
    $id > 0 || throw new RuntimeException('SDL_AttachVirtualJoystick: '.SDL_GetError());
    $GLOBALS['sdl3_virtual_devices'][] = $id;

    return $id;
}

afterEach(function (): void {
    foreach ($GLOBALS['sdl3_virtual_devices'] ?? [] as $id) {
        SDL_DetachVirtualJoystick($id);
    }
    $GLOBALS['sdl3_virtual_devices'] = [];
});

it('lists a virtual gamepad and reads its buttons and axes after an update', function (): void {
    $id = virtualDevice(SDL_JOYSTICK_TYPE_GAMEPAD, 6, 15, 0, 'php pad');
    $pad = SDL_OpenGamepad($id);
    $stick = SDL_OpenJoystick($id);

    SDL_SetJoystickVirtualButton($stick, SDL_GAMEPAD_BUTTON_EAST, true);
    SDL_SetJoystickVirtualAxis($stick, SDL_GAMEPAD_AXIS_LEFTX, SDL_JOYSTICK_AXIS_MAX);
    // A trigger's raw range (−32768 resting … 32767) maps onto 0 … 32767: raw 0 is half pulled.
    SDL_SetJoystickVirtualAxis($stick, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER, 0);
    $before = SDL_GetGamepadButton($pad, SDL_GAMEPAD_BUTTON_EAST);
    SDL_UpdateGamepads();

    expect(SDL_GetGamepads())->toContain($id)
        ->and(SDL_IsGamepad($id))->toBeTrue()
        ->and(SDL_GetGamepadName($pad))->toBe('php pad')
        ->and(SDL_GetGamepadID($pad))->toBe($id)
        ->and($before)->toBeFalse()
        ->and(SDL_GetGamepadButton($pad, SDL_GAMEPAD_BUTTON_EAST))->toBeTrue()
        ->and(SDL_GetGamepadButton($pad, SDL_GAMEPAD_BUTTON_SOUTH))->toBeFalse()
        ->and(SDL_GetGamepadAxis($pad, SDL_GAMEPAD_AXIS_LEFTX))->toBe(32767)
        ->and(SDL_GetGamepadAxis($pad, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER))->toBe(16383)
        ->and(SDL_GetGamepadAxis($pad, SDL_GAMEPAD_AXIS_LEFT_TRIGGER))->toBe(0);

    SDL_CloseJoystick($stick);
    SDL_CloseGamepad($pad);
});

it('reads a plain joystick through the joystick API', function (): void {
    $id = virtualDevice(SDL_JOYSTICK_TYPE_UNKNOWN, 3, 9, 1, 'php stick');
    $stick = SDL_OpenJoystick($id);

    SDL_SetJoystickVirtualHat($stick, 0, SDL_HAT_UP | SDL_HAT_LEFT);
    SDL_SetJoystickVirtualButton($stick, 2, true);
    SDL_SetJoystickVirtualAxis($stick, 1, SDL_JOYSTICK_AXIS_MIN);
    SDL_UpdateJoysticks();

    expect(SDL_GetJoysticks())->toContain($id)
        ->and(SDL_GetGamepads())->not->toContain($id)
        ->and(SDL_IsGamepad($id))->toBeFalse()
        ->and(SDL_GetJoystickName($stick))->toBe('php stick')
        ->and([SDL_GetNumJoystickAxes($stick), SDL_GetNumJoystickButtons($stick), SDL_GetNumJoystickHats($stick)])->toBe([3, 9, 1])
        ->and(SDL_GetJoystickHat($stick, 0))->toBe(SDL_HAT_UP | SDL_HAT_LEFT)
        ->and(SDL_GetJoystickButton($stick, 2))->toBeTrue()
        ->and(SDL_GetJoystickAxis($stick, 1))->toBe(-32768);

    SDL_CloseJoystick($stick);
});

it('counts opens: the handle stays live until every open is closed', function (): void {
    $id = virtualDevice(SDL_JOYSTICK_TYPE_GAMEPAD, 6, 15, 0, 'twice');
    $first = SDL_OpenGamepad($id);
    $second = SDL_OpenGamepad($id);

    expect($second)->toBe($first);

    SDL_CloseGamepad($second);

    expect(SDL_GetGamepadName($first))->toBe('twice');

    SDL_CloseGamepad($first);

    expect(fn () => SDL_GetGamepadName($first))->toThrow(ValueError::class, 'SDL_Gamepad has been destroyed');
});

it('drops a detached device from the lists', function (): void {
    $id = virtualDevice(SDL_JOYSTICK_TYPE_GAMEPAD, 6, 15, 0, 'leaving');
    SDL_DetachVirtualJoystick($id);
    SDL_UpdateGamepads();

    expect(SDL_GetGamepads())->not->toContain($id)
        ->and(SDL_GetJoysticks())->not->toContain($id)
        ->and(SDL_OpenGamepad($id))->toBeNull();
});

it('releases its pad and stick handles when SDL takes the joystick subsystem down', function (string $quit): void {
    $script = tempnam(sys_get_temp_dir(), 'sdl3').'.php';
    file_put_contents($script, '<?php
        SDL_InitSubSystem(SDL_INIT_GAMEPAD) || exit("init: ".SDL_GetError());
        $desc = new SDL_VirtualJoystickDesc();
        $desc->type = SDL_JOYSTICK_TYPE_GAMEPAD;
        $desc->naxes = 6;
        $desc->nbuttons = 15;
        $desc->name = "gone";
        $id = SDL_AttachVirtualJoystick($desc);
        $pad = SDL_OpenGamepad($id);
        $stick = SDL_OpenJoystick($id);
        '.$quit.';
        $out = [];
        foreach ([fn () => SDL_GetGamepadName($pad), fn () => SDL_GetJoystickName($stick)] as $read) {
            try {
                $read();
                $out[] = "live";
            } catch (ValueError $e) {
                $out[] = str_contains($e->getMessage(), "has been destroyed") ? "released" : $e->getMessage();
            }
        }
        echo json_encode($out);');

    $out = shell_exec(escapeshellarg(PHP_BINARY).' -d memory_limit=128M '.escapeshellarg($script).' 2>&1');
    unlink($script);

    expect(json_decode((string) $out, true))->toBe(['released', 'released']);
})->with(['SDL_QuitSubSystem(SDL_INIT_GAMEPAD)', 'SDL_Quit()']);

it('lays gamepad buttons and axes out as SDL numbers them', function (): void {
    expect([SDL_GAMEPAD_BUTTON_SOUTH, SDL_GAMEPAD_BUTTON_DPAD_RIGHT, SDL_GAMEPAD_AXIS_LEFTX, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER])->toBe([0, 14, 0, 5])
        ->and([SDL_HAT_CENTERED, SDL_HAT_UP, SDL_HAT_RIGHT, SDL_HAT_DOWN, SDL_HAT_LEFT])->toBe([0, 1, 2, 4, 8])
        ->and([SDL_JOYSTICK_AXIS_MIN, SDL_JOYSTICK_AXIS_MAX])->toBe([-32768, 32767]);
});

it('releases its pad handles when the gamepad subsystem goes down while joysticks stay up', function (): void {
    $script = tempnam(sys_get_temp_dir(), 'sdl3').'.php';
    file_put_contents($script, '<?php
        SDL_InitSubSystem(SDL_INIT_JOYSTICK) || exit("init: ".SDL_GetError());
        SDL_InitSubSystem(SDL_INIT_GAMEPAD) || exit("init: ".SDL_GetError());
        $desc = new SDL_VirtualJoystickDesc();
        $desc->type = SDL_JOYSTICK_TYPE_GAMEPAD;
        $desc->naxes = 6;
        $desc->nbuttons = 15;
        $desc->name = "half";
        $id = SDL_AttachVirtualJoystick($desc);
        $pad = SDL_OpenGamepad($id);
        $stick = SDL_OpenJoystick($id);
        SDL_QuitSubSystem(SDL_INIT_GAMEPAD);
        $out = [];
        try {
            SDL_GetGamepadName($pad);
            $out[] = "live";
        } catch (ValueError $e) {
            $out[] = str_contains($e->getMessage(), "has been destroyed") ? "released" : $e->getMessage();
        }
        $out[] = SDL_GetJoystickName($stick);
        echo json_encode($out);');

    $out = shell_exec(escapeshellarg(PHP_BINARY).' -d memory_limit=128M '.escapeshellarg($script).' 2>&1');
    unlink($script);

    expect(json_decode((string) $out, true))->toBe(['released', 'half']);
});

it('sets and reads player indexes, and has no serial or path for a virtual device', function (): void {
    $pad_id = virtualDevice(SDL_JOYSTICK_TYPE_GAMEPAD, 6, 15, 0, 'php pad');
    $stick_id = virtualDevice(SDL_JOYSTICK_TYPE_UNKNOWN, 2, 4, 0, 'php stick');
    $pad = SDL_OpenGamepad($pad_id);
    $stick = SDL_OpenJoystick($stick_id);

    $set = [SDL_SetGamepadPlayerIndex($pad, 2), SDL_SetJoystickPlayerIndex($stick, 3)];
    $read = [SDL_GetGamepadPlayerIndex($pad), SDL_GetJoystickPlayerIndex($stick)];
    SDL_SetGamepadPlayerIndex($pad, -1);

    expect($set)->toBe([true, true])
        ->and($read)->toBe([2, 3])
        ->and(SDL_GetGamepadPlayerIndex($pad))->toBe(-1)
        ->and(SDL_GetGamepadSerial($pad))->toBeNull()
        ->and(SDL_GetJoystickSerial($stick))->toBeNull()
        ->and(SDL_GetGamepadPath($pad))->toBeNull()
        ->and(SDL_GetJoystickPath($stick))->toBeNull();

    SDL_CloseJoystick($stick);
    SDL_CloseGamepad($pad);
});
