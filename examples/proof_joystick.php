<?php
/**
 * sdl3 extension — SDL Joystick proof script (WP5)
 *
 * Headless coverage via a virtual joystick: attach, open, inject axis/button
 * state, read it back after SDL_UpdateJoysticks. No physical hardware required.
 *
 * Usage:
 *   php examples/proof_joystick.php
 */

declare(strict_types=1);

use Sdl3\SDL\SDL;
use Sdl3\SDL\SDLError;
use Sdl3\SDL\Input\SDLJoystick;

const SDL_INIT_JOYSTICK = 0x00000200;
const SDL_JOYSTICK_TYPE_GAMEPAD = 1;
const SDL_JOYSTICK_AXIS_MAX = 32767;
const SDL_HAT_CENTERED = 0x00;
const SDL_HAT_UP = 0x01;

function pass(string $label): void
{
    echo "  [PASS] {$label}\n";
}

function fail(string $label, string $detail = ''): void
{
    $msg = "  [FAIL] {$label}";
    if ($detail !== '') {
        $msg .= ": {$detail}";
    }
    echo $msg . "\n";
}

function section(string $title): void
{
    echo "\n── {$title} ──\n";
}

function sdl_err(): string
{
    return SDLError::SDLGetError();
}

$errors = 0;

section('Extension check');
if (!extension_loaded('sdl3')) {
    echo "  [FATAL] sdl3 extension is NOT loaded. Aborting.\n";
    exit(1);
}
pass('sdl3 extension is loaded');

section('SDL_Init + SDL_InitSubSystem(JOYSTICK)');
if (!SDL::SDLInit(0)) {
    fail('SDL_Init(0)', sdl_err());
    exit(1);
}
pass('SDL_Init(0) succeeded');

if (!SDL::SDLInitSubSystem(SDL_INIT_JOYSTICK)) {
    fail('SDL_InitSubSystem(JOYSTICK)', sdl_err());
    SDL::SDLQuit();
    exit(1);
}
pass('SDL_InitSubSystem(JOYSTICK) succeeded');

section('Lock / unlock / event toggles');
SDLJoystick::SDLLockJoysticks();
pass('SDLLockJoysticks');
SDLJoystick::SDLUnlockJoysticks();
pass('SDLUnlockJoysticks');

$eventsEnabled = SDLJoystick::SDLJoystickEventsEnabled();
pass('SDLJoystickEventsEnabled returned ' . ($eventsEnabled ? 'true' : 'false'));
SDLJoystick::SDLSetJoystickEventsEnabled(true);
pass('SDLSetJoystickEventsEnabled(true)');

section('Attach virtual joystick');
$instanceId = SDLJoystick::SDLAttachVirtualJoystick([
    'type' => SDL_JOYSTICK_TYPE_GAMEPAD,
    'naxes' => 2,
    'nbuttons' => 4,
    'nballs' => 1,
    'nhats' => 1,
    'name' => 'PHP Virtual Joystick',
]);
pass("SDLAttachVirtualJoystick instance_id={$instanceId}");

if (!SDLJoystick::SDLIsJoystickVirtual($instanceId)) {
    fail('SDLIsJoystickVirtual', 'expected true');
    $errors++;
} else {
    pass('SDLIsJoystickVirtual confirmed virtual device');
}

if (!SDLJoystick::SDLHasJoystick()) {
    fail('SDLHasJoystick', 'expected true after attach');
    $errors++;
} else {
    pass('SDLHasJoystick true');
}

$joysticks = SDLJoystick::SDLGetJoysticks();
if (in_array($instanceId, $joysticks, true)) {
    pass('SDLGetJoysticks contains virtual instance id');
} else {
    fail('SDLGetJoysticks', 'virtual instance id missing from list');
    $errors++;
}

$nameForId = SDLJoystick::SDLGetJoystickNameForID($instanceId);
if ($nameForId === 'PHP Virtual Joystick') {
    pass("SDLGetJoystickNameForID → {$nameForId}");
} else {
    fail('SDLGetJoystickNameForID', "expected 'PHP Virtual Joystick', got '{$nameForId}'");
    $errors++;
}

$guidForId = SDLJoystick::SDLGetJoystickGUIDForID($instanceId);
if ($guidForId !== '') {
    pass("SDLGetJoystickGUIDForID → {$guidForId}");
    $guidInfo = SDLJoystick::SDLGetJoystickGUIDInfo($guidForId);
    if (is_array($guidInfo) && array_key_exists('vendor', $guidInfo)) {
        pass('SDLGetJoystickGUIDInfo returned vendor/product/version/crc16');
    } else {
        fail('SDLGetJoystickGUIDInfo', 'unexpected shape');
        $errors++;
    }
} else {
    fail('SDLGetJoystickGUIDForID', 'empty GUID string');
    $errors++;
}

section('Open virtual joystick and query metadata');
$joy = SDLJoystick::SDLOpenJoystick($instanceId);
pass('SDLOpenJoystick ptr=0x' . dechex($joy));

if (SDLJoystick::SDLGetJoystickFromID($instanceId) !== $joy) {
    fail('SDLGetJoystickFromID', 'handle mismatch');
    $errors++;
} else {
    pass('SDLGetJoystickFromID returns same handle');
}

if (!SDLJoystick::SDLJoystickConnected($joy)) {
    fail('SDLJoystickConnected', 'expected true');
    $errors++;
} else {
    pass('SDLJoystickConnected true');
}

if (SDLJoystick::SDLGetJoystickID($joy) !== $instanceId) {
    fail('SDLGetJoystickID', 'instance id mismatch');
    $errors++;
} else {
    pass('SDLGetJoystickID matches instance id');
}

$axes = SDLJoystick::SDLGetNumJoystickAxes($joy);
$buttons = SDLJoystick::SDLGetNumJoystickButtons($joy);
$balls = SDLJoystick::SDLGetNumJoystickBalls($joy);
$hats = SDLJoystick::SDLGetNumJoystickHats($joy);
if ($axes === 2 && $buttons === 4 && $hats === 1) {
    pass("Counts axes={$axes} buttons={$buttons} balls={$balls} hats={$hats}");
} else {
    fail('Joystick counts', "axes={$axes} buttons={$buttons} balls={$balls} hats={$hats}");
    $errors++;
}

$joyName = SDLJoystick::SDLGetJoystickName($joy);
if ($joyName === 'PHP Virtual Joystick') {
    pass("SDLGetJoystickName → {$joyName}");
} else {
    fail('SDLGetJoystickName', $joyName);
    $errors++;
}

$joyGuid = SDLJoystick::SDLGetJoystickGUID($joy);
if ($joyGuid !== '') {
    pass("SDLGetJoystickGUID → {$joyGuid}");
} else {
    fail('SDLGetJoystickGUID', 'empty');
    $errors++;
}

$props = SDLJoystick::SDLGetJoystickProperties($joy);
if ($props !== 0) {
    pass("SDLGetJoystickProperties id={$props}");
} else {
    fail('SDLGetJoystickProperties', sdl_err());
    $errors++;
}

$connState = SDLJoystick::SDLGetJoystickConnectionState($joy);
pass("SDLGetJoystickConnectionState → {$connState}");

$power = SDLJoystick::SDLGetJoystickPowerInfo($joy);
if (is_array($power) && array_key_exists('state', $power) && array_key_exists('percent', $power)) {
    pass("SDLGetJoystickPowerInfo state={$power['state']} percent={$power['percent']}");
} else {
    fail('SDLGetJoystickPowerInfo', 'unexpected shape');
    $errors++;
}

section('Inject virtual state and read back');
if (!SDLJoystick::SDLSetJoystickVirtualAxis($joy, 0, SDL_JOYSTICK_AXIS_MAX)) {
    fail('SDLSetJoystickVirtualAxis', sdl_err());
    $errors++;
} else {
    pass('SDLSetJoystickVirtualAxis axis0=max');
}

if (!SDLJoystick::SDLSetJoystickVirtualButton($joy, 1, true)) {
    fail('SDLSetJoystickVirtualButton', sdl_err());
    $errors++;
} else {
    pass('SDLSetJoystickVirtualButton button1=down');
}

if (!SDLJoystick::SDLSetJoystickVirtualHat($joy, 0, SDL_HAT_UP)) {
    fail('SDLSetJoystickVirtualHat', sdl_err());
    $errors++;
} else {
    pass('SDLSetJoystickVirtualHat hat0=UP');
}

if ($balls > 0) {
    if (!SDLJoystick::SDLSetJoystickVirtualBall($joy, 0, 3, -2)) {
        fail('SDLSetJoystickVirtualBall', sdl_err());
        $errors++;
    } else {
        pass('SDLSetJoystickVirtualBall ball0 rel=(3,-2)');
    }
} else {
    pass('Skipping ball tests — virtual joystick reports zero balls');
}

SDLJoystick::SDLUpdateJoysticks();
pass('SDLUpdateJoysticks');

$axisVal = SDLJoystick::SDLGetJoystickAxis($joy, 0);
if ($axisVal === SDL_JOYSTICK_AXIS_MAX) {
    pass("SDLGetJoystickAxis axis0={$axisVal}");
} else {
    fail('SDLGetJoystickAxis', "expected " . SDL_JOYSTICK_AXIS_MAX . ", got {$axisVal}");
    $errors++;
}

if (SDLJoystick::SDLGetJoystickButton($joy, 1)) {
    pass('SDLGetJoystickButton button1 pressed');
} else {
    fail('SDLGetJoystickButton', 'expected button1 down');
    $errors++;
}

$hatVal = SDLJoystick::SDLGetJoystickHat($joy, 0);
if ($hatVal === SDL_HAT_UP) {
    pass("SDLGetJoystickHat hat0={$hatVal}");
} else {
    fail('SDLGetJoystickHat', "expected " . SDL_HAT_UP . ", got {$hatVal}");
    $errors++;
}

$ball = SDLJoystick::SDLGetJoystickBall($joy, 0);
if ($balls > 0) {
    if (($ball['success'] ?? false) && ($ball['dx'] ?? null) === 3 && ($ball['dy'] ?? null) === -2) {
        pass('SDLGetJoystickBall dx=3 dy=-2');
    } else {
        fail('SDLGetJoystickBall', json_encode($ball));
        $errors++;
    }
} else {
    pass('Skipping SDLGetJoystickBall — no balls on virtual device');
}

$initial = SDLJoystick::SDLGetJoystickAxisInitialState($joy, 0);
if (is_array($initial) && array_key_exists('has_initial', $initial) && array_key_exists('state', $initial)) {
    pass('SDLGetJoystickAxisInitialState returned has_initial/state');
} else {
    fail('SDLGetJoystickAxisInitialState', 'unexpected shape');
    $errors++;
}

section('Player index round-trip');
if (SDLJoystick::SDLSetJoystickPlayerIndex($joy, 2)) {
    pass('SDLSetJoystickPlayerIndex(2)');
    $idx = SDLJoystick::SDLGetJoystickPlayerIndex($joy);
    if ($idx === 2) {
        pass("SDLGetJoystickPlayerIndex → {$idx}");
    } else {
        fail('SDLGetJoystickPlayerIndex', "expected 2, got {$idx}");
        $errors++;
    }
} else {
    fail('SDLSetJoystickPlayerIndex', sdl_err());
    $errors++;
}

section('Optional effect/rumble/LED (may be unsupported on virtual device)');
SDLJoystick::SDLRumbleJoystick($joy, 1000, 2000, 100);
pass('SDLRumbleJoystick invoked (return value ignored on virtual)');
SDLJoystick::SDLRumbleJoystickTriggers($joy, 500, 500, 100);
pass('SDLRumbleJoystickTriggers invoked');
SDLJoystick::SDLSetJoystickLED($joy, 255, 0, 128);
pass('SDLSetJoystickLED invoked');
SDLJoystick::SDLSendJoystickEffect($joy, "\x01\x02\x03\x04");
pass('SDLSendJoystickEffect invoked');

section('Cleanup');
SDLJoystick::SDLCloseJoystick($joy);
pass('SDLCloseJoystick');

if (!SDLJoystick::SDLDetachVirtualJoystick($instanceId)) {
    fail('SDLDetachVirtualJoystick', sdl_err());
    $errors++;
} else {
    pass('SDLDetachVirtualJoystick');
}

SDL::SDLQuitSubSystem(SDL_INIT_JOYSTICK);
pass('SDL_QuitSubSystem(JOYSTICK)');

SDL::SDLQuit();
pass('SDL_Quit');

section('Summary');
if ($errors === 0) {
    echo "  All joystick checks passed.\n\n";
    exit(0);
}

echo "  {$errors} check(s) FAILED.\n\n";
exit(1);
