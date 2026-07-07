<?php
/**
 * sdl3 extension — SDL Gamepad proof script (WP6)
 *
 * Headless coverage via a virtual joystick + custom gamepad mapping: attach,
 * map, open as gamepad, inject axis/button/touchpad/sensor state through the
 * underlying joystick, read it back through gamepad APIs.
 *
 * Usage:
 *   php examples/proof_gamepad.php
 */

declare(strict_types=1);

use Sdl3\SDL\SDL;
use Sdl3\SDL\SDLError;
use Sdl3\SDL\Input\SDLGamepad;
use Sdl3\SDL\Input\SDLJoystick;

const SDL_INIT_JOYSTICK = 0x00000200;
const SDL_INIT_GAMEPAD = 0x00002000;
const SDL_JOYSTICK_TYPE_GAMEPAD = 1;
const SDL_JOYSTICK_AXIS_MAX = 32767;
const SDL_GAMEPAD_BUTTON_SOUTH = 0;
const SDL_GAMEPAD_BUTTON_EAST = 1;
const SDL_GAMEPAD_AXIS_LEFTX = 0;
const SDL_GAMEPAD_AXIS_LEFTY = 1;
const SDL_GAMEPAD_AXIS_LEFT_TRIGGER = 4;
const SDL_GAMEPAD_TYPE_STANDARD = 1;
const SDL_SENSOR_ACCEL = 1;

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

section('SDL_Init + subsystems');
if (!SDL::SDLInit(0)) {
    fail('SDL_Init(0)', sdl_err());
    exit(1);
}
pass('SDL_Init(0) succeeded');

if (!SDL::SDLInitSubSystem(SDL_INIT_GAMEPAD)) {
    fail('SDL_InitSubSystem(GAMEPAD)', sdl_err());
    SDL::SDLQuit();
    exit(1);
}
pass('SDL_InitSubSystem(GAMEPAD) succeeded (implies JOYSTICK)');

section('Mapping database helpers');
$reloadOk = SDLGamepad::SDLReloadGamepadMappings();
pass('SDLReloadGamepadMappings → ' . ($reloadOk ? 'true' : 'false'));

$mappings = SDLGamepad::SDLGetGamepadMappings();
if (is_array($mappings)) {
    pass('SDLGetGamepadMappings returned ' . count($mappings) . ' built-in mapping(s)');
} else {
    fail('SDLGetGamepadMappings', 'expected array');
    $errors++;
}

$typeFromStr = SDLGamepad::SDLGetGamepadTypeFromString('xbox360');
if ($typeFromStr !== 0) {
    pass("SDLGetGamepadTypeFromString('xbox360') → {$typeFromStr}");
} else {
    fail('SDLGetGamepadTypeFromString', sdl_err());
    $errors++;
}

$typeStr = SDLGamepad::SDLGetGamepadStringForType(SDL_GAMEPAD_TYPE_STANDARD);
if ($typeStr !== '') {
    pass("SDLGetGamepadStringForType(STANDARD) → {$typeStr}");
} else {
    fail('SDLGetGamepadStringForType', 'empty string');
    $errors++;
}

$axisFromStr = SDLGamepad::SDLGetGamepadAxisFromString('leftx');
if ($axisFromStr === SDL_GAMEPAD_AXIS_LEFTX) {
    pass('SDLGetGamepadAxisFromString(leftx) → LEFTX');
} else {
    fail('SDLGetGamepadAxisFromString', "expected " . SDL_GAMEPAD_AXIS_LEFTX . ", got {$axisFromStr}");
    $errors++;
}

$axisStr = SDLGamepad::SDLGetGamepadStringForAxis(SDL_GAMEPAD_AXIS_LEFTY);
if ($axisStr === 'lefty') {
    pass("SDLGetGamepadStringForAxis(LEFTY) → {$axisStr}");
} else {
    fail('SDLGetGamepadStringForAxis', $axisStr);
    $errors++;
}

$btnFromStr = SDLGamepad::SDLGetGamepadButtonFromString('a');
if ($btnFromStr === SDL_GAMEPAD_BUTTON_SOUTH) {
    pass('SDLGetGamepadButtonFromString(a) → SOUTH');
} else {
    fail('SDLGetGamepadButtonFromString', "expected " . SDL_GAMEPAD_BUTTON_SOUTH . ", got {$btnFromStr}");
    $errors++;
}

$btnStr = SDLGamepad::SDLGetGamepadStringForButton(SDL_GAMEPAD_BUTTON_EAST);
if ($btnStr === 'b') {
    pass("SDLGetGamepadStringForButton(EAST) → {$btnStr}");
} else {
    fail('SDLGetGamepadStringForButton', $btnStr);
    $errors++;
}

section('Attach virtual joystick and register gamepad mapping');
$instanceId = SDLJoystick::SDLAttachVirtualJoystick([
    'type' => SDL_JOYSTICK_TYPE_GAMEPAD,
    'naxes' => 6,
    'nbuttons' => 12,
    'ntouchpads' => 1,
    'nsensors' => 1,
    'touchpads' => [['nfingers' => 2]],
    'sensors' => [['type' => SDL_SENSOR_ACCEL, 'rate' => 100.0]],
    'name' => 'PHP Virtual Gamepad',
]);
pass("SDLAttachVirtualJoystick instance_id={$instanceId}");

$guid = SDLJoystick::SDLGetJoystickGUIDForID($instanceId);
if ($guid === '') {
    fail('SDLGetJoystickGUIDForID', 'empty GUID');
    SDLJoystick::SDLDetachVirtualJoystick($instanceId);
    SDL::SDLQuit();
    exit(1);
}
pass("GUID for virtual device → {$guid}");

$mappingLine = sprintf(
    '%s,PHP Virtual Gamepad,a:b0,b:b1,x:b2,y:b3,back:b4,start:b5,'
    . 'leftshoulder:b6,rightshoulder:b7,leftx:a0,lefty:a1,rightx:a2,righty:a3,'
    . 'lefttrigger:a4,righttrigger:a5,dpup:b8,dpdown:b9,dpleft:b10,dpright:b11',
    $guid
);

$addResult = SDLGamepad::SDLAddGamepadMapping($mappingLine);
if ($addResult >= 0) {
    pass("SDLAddGamepadMapping → {$addResult}");
} else {
    fail('SDLAddGamepadMapping', sdl_err());
    $errors++;
}

if (!SDLGamepad::SDLIsGamepad($instanceId)) {
    fail('SDLIsGamepad', 'expected true after mapping');
    $errors++;
} else {
    pass('SDLIsGamepad confirmed mapped device');
}

if (!SDLGamepad::SDLHasGamepad()) {
    fail('SDLHasGamepad', 'expected true');
    $errors++;
} else {
    pass('SDLHasGamepad true');
}

$gamepads = SDLGamepad::SDLGetGamepads();
if (in_array($instanceId, $gamepads, true)) {
    pass('SDLGetGamepads contains virtual instance id');
} else {
    fail('SDLGetGamepads', 'virtual instance id missing');
    $errors++;
}

$nameForId = SDLGamepad::SDLGetGamepadNameForID($instanceId);
pass("SDLGetGamepadNameForID → {$nameForId}");

$guidForId = SDLGamepad::SDLGetGamepadGUIDForID($instanceId);
if ($guidForId === $guid) {
    pass('SDLGetGamepadGUIDForID matches joystick GUID');
} else {
    fail('SDLGetGamepadGUIDForID', $guidForId);
    $errors++;
}

$mappingForId = SDLGamepad::SDLGetGamepadMappingForID($instanceId);
if ($mappingForId !== '') {
    pass('SDLGetGamepadMappingForID returned mapping string');
} else {
    fail('SDLGetGamepadMappingForID', sdl_err());
    $errors++;
}

$mappingForGuid = SDLGamepad::SDLGetGamepadMappingForGUID($guid);
if ($mappingForGuid !== '') {
    pass('SDLGetGamepadMappingForGUID returned mapping string');
} else {
    fail('SDLGetGamepadMappingForGUID', sdl_err());
    $errors++;
}

$typeForId = SDLGamepad::SDLGetGamepadTypeForID($instanceId);
pass("SDLGetGamepadTypeForID → {$typeForId}");
$realTypeForId = SDLGamepad::SDLGetRealGamepadTypeForID($instanceId);
pass("SDLGetRealGamepadTypeForID → {$realTypeForId}");

section('Open gamepad and query metadata');
$pad = SDLGamepad::SDLOpenGamepad($instanceId);
pass('SDLOpenGamepad ptr=0x' . dechex($pad));

if (SDLGamepad::SDLGetGamepadFromID($instanceId) !== $pad) {
    fail('SDLGetGamepadFromID', 'handle mismatch');
    $errors++;
} else {
    pass('SDLGetGamepadFromID returns same handle');
}

if (!SDLGamepad::SDLGamepadConnected($pad)) {
    fail('SDLGamepadConnected', 'expected true');
    $errors++;
} else {
    pass('SDLGamepadConnected true');
}

if (SDLGamepad::SDLGetGamepadID($pad) !== $instanceId) {
    fail('SDLGetGamepadID', 'instance id mismatch');
    $errors++;
} else {
    pass('SDLGetGamepadID matches instance id');
}

$joy = SDLGamepad::SDLGetGamepadJoystick($pad);
if ($joy !== 0) {
    pass('SDLGetGamepadJoystick returned underlying joystick handle');
} else {
    fail('SDLGetGamepadJoystick', sdl_err());
    $errors++;
}

$padName = SDLGamepad::SDLGetGamepadName($pad);
pass("SDLGetGamepadName → {$padName}");

$props = SDLGamepad::SDLGetGamepadProperties($pad);
if ($props !== 0) {
    pass("SDLGetGamepadProperties id={$props}");
} else {
    fail('SDLGetGamepadProperties', sdl_err());
    $errors++;
}

$padType = SDLGamepad::SDLGetGamepadType($pad);
pass("SDLGetGamepadType → {$padType}");
$realType = SDLGamepad::SDLGetRealGamepadType($pad);
pass("SDLGetRealGamepadType → {$realType}");

$padMapping = SDLGamepad::SDLGetGamepadMapping($pad);
if ($padMapping !== '') {
    pass('SDLGetGamepadMapping returned non-empty string');
} else {
    fail('SDLGetGamepadMapping', sdl_err());
    $errors++;
}

$bindings = SDLGamepad::SDLGetGamepadBindings($pad);
if (is_array($bindings) && count($bindings) > 0) {
    $first = $bindings[0];
    if (is_array($first) && array_key_exists('input_type', $first) && array_key_exists('output_type', $first)) {
        pass('SDLGetGamepadBindings returned ' . count($bindings) . ' binding(s) with expected shape');
    } else {
        fail('SDLGetGamepadBindings', 'unexpected binding shape');
        $errors++;
    }
} else {
    fail('SDLGetGamepadBindings', 'expected non-empty array');
    $errors++;
}

$connState = SDLGamepad::SDLGetGamepadConnectionState($pad);
pass("SDLGetGamepadConnectionState → {$connState}");

$power = SDLGamepad::SDLGetGamepadPowerInfo($pad);
if (is_array($power) && array_key_exists('state', $power) && array_key_exists('percent', $power)) {
    pass("SDLGetGamepadPowerInfo state={$power['state']} percent={$power['percent']}");
} else {
    fail('SDLGetGamepadPowerInfo', 'unexpected shape');
    $errors++;
}

$eventsEnabled = SDLGamepad::SDLGamepadEventsEnabled();
pass('SDLGamepadEventsEnabled → ' . ($eventsEnabled ? 'true' : 'false'));
SDLGamepad::SDLSetGamepadEventsEnabled(true);
pass('SDLSetGamepadEventsEnabled(true)');

$labelForType = SDLGamepad::SDLGetGamepadButtonLabelForType(SDL_GAMEPAD_TYPE_STANDARD, SDL_GAMEPAD_BUTTON_SOUTH);
pass("SDLGetGamepadButtonLabelForType(SOUTH) → {$labelForType}");
$label = SDLGamepad::SDLGetGamepadButtonLabel($pad, SDL_GAMEPAD_BUTTON_SOUTH);
pass("SDLGetGamepadButtonLabel(SOUTH) → {$label}");

$sfBtn = SDLGamepad::SDLGetGamepadAppleSFSymbolsNameForButton($pad, SDL_GAMEPAD_BUTTON_SOUTH);
pass('SDLGetGamepadAppleSFSymbolsNameForButton invoked (may be empty off Apple UI)');
$sfAxis = SDLGamepad::SDLGetGamepadAppleSFSymbolsNameForAxis($pad, SDL_GAMEPAD_AXIS_LEFTX);
pass('SDLGetGamepadAppleSFSymbolsNameForAxis invoked (may be empty off Apple UI)');

section('Inject virtual state via joystick, read via gamepad');
if (!SDLJoystick::SDLSetJoystickVirtualAxis($joy, 0, SDL_JOYSTICK_AXIS_MAX)) {
    fail('SDLSetJoystickVirtualAxis', sdl_err());
    $errors++;
} else {
    pass('Injected left stick X at max via virtual axis 0');
}

if (!SDLJoystick::SDLSetJoystickVirtualButton($joy, 0, true)) {
    fail('SDLSetJoystickVirtualButton', sdl_err());
    $errors++;
} else {
    pass('Injected south face button via virtual button 0');
}

if (!SDLJoystick::SDLSetJoystickVirtualTouchpad($joy, 0, 0, true, 0.25, 0.75, 0.5)) {
    fail('SDLSetJoystickVirtualTouchpad', sdl_err());
    $errors++;
} else {
    pass('Injected touchpad finger 0 down at (0.25, 0.75)');
}

if (!SDLJoystick::SDLSendJoystickVirtualSensorData($joy, SDL_SENSOR_ACCEL, 1000, [0.0, 9.8, 0.0])) {
    fail('SDLSendJoystickVirtualSensorData', sdl_err());
    $errors++;
} else {
    pass('Injected accelerometer sample via virtual sensor');
}

SDLJoystick::SDLUpdateJoysticks();
SDLGamepad::SDLUpdateGamepads();
pass('SDL_UpdateJoysticks + SDL_UpdateGamepads');

if (SDLGamepad::SDLGamepadHasAxis($pad, SDL_GAMEPAD_AXIS_LEFTX)) {
    pass('SDLGamepadHasAxis(LEFTX) true');
    $axisVal = SDLGamepad::SDLGetGamepadAxis($pad, SDL_GAMEPAD_AXIS_LEFTX);
    if ($axisVal === SDL_JOYSTICK_AXIS_MAX) {
        pass("SDLGetGamepadAxis(LEFTX)={$axisVal}");
    } else {
        fail('SDLGetGamepadAxis', "expected " . SDL_JOYSTICK_AXIS_MAX . ", got {$axisVal}");
        $errors++;
    }
} else {
    fail('SDLGamepadHasAxis', 'LEFTX not reported');
    $errors++;
}

if (SDLGamepad::SDLGamepadHasButton($pad, SDL_GAMEPAD_BUTTON_SOUTH)) {
    pass('SDLGamepadHasButton(SOUTH) true');
    if (SDLGamepad::SDLGetGamepadButton($pad, SDL_GAMEPAD_BUTTON_SOUTH)) {
        pass('SDLGetGamepadButton(SOUTH) pressed');
    } else {
        fail('SDLGetGamepadButton', 'expected south button down');
        $errors++;
    }
} else {
    fail('SDLGamepadHasButton', 'SOUTH not reported');
    $errors++;
}

$touchpads = SDLGamepad::SDLGetNumGamepadTouchpads($pad);
if ($touchpads >= 1) {
    pass("SDLGetNumGamepadTouchpads → {$touchpads}");
    $fingers = SDLGamepad::SDLGetNumGamepadTouchpadFingers($pad, 0);
    pass("SDLGetNumGamepadTouchpadFingers(touchpad0) → {$fingers}");
    $finger = SDLGamepad::SDLGetGamepadTouchpadFinger($pad, 0, 0);
    if (($finger['success'] ?? false) && ($finger['down'] ?? false)) {
        pass('SDLGetGamepadTouchpadFinger finger0 down with x/y/pressure');
    } else {
        fail('SDLGetGamepadTouchpadFinger', json_encode($finger));
        $errors++;
    }
} else {
    fail('SDLGetNumGamepadTouchpads', "expected >= 1, got {$touchpads}");
    $errors++;
}

if (SDLGamepad::SDLGamepadHasSensor($pad, SDL_SENSOR_ACCEL)) {
    pass('SDLGamepadHasSensor(ACCEL) true');
    if (SDLGamepad::SDLSetGamepadSensorEnabled($pad, SDL_SENSOR_ACCEL, true)) {
        pass('SDLSetGamepadSensorEnabled(ACCEL, true)');
    } else {
        fail('SDLSetGamepadSensorEnabled', sdl_err());
        $errors++;
    }
    $sensorEnabled = SDLGamepad::SDLGamepadSensorEnabled($pad, SDL_SENSOR_ACCEL);
    pass('SDLGamepadSensorEnabled → ' . ($sensorEnabled ? 'true' : 'false'));
    $rate = SDLGamepad::SDLGetGamepadSensorDataRate($pad, SDL_SENSOR_ACCEL);
    pass("SDLGetGamepadSensorDataRate → {$rate}");
    $sensorData = SDLGamepad::SDLGetGamepadSensorData($pad, SDL_SENSOR_ACCEL, 3);
    if (($sensorData['success'] ?? false) && is_array($sensorData['data'] ?? null) && count($sensorData['data']) === 3) {
        pass('SDLGetGamepadSensorData returned 3 float samples');
    } else {
        fail('SDLGetGamepadSensorData', json_encode($sensorData));
        $errors++;
    }
} else {
    fail('SDLGamepadHasSensor', 'ACCEL not reported on virtual gamepad');
    $errors++;
}

section('Player index round-trip');
if (SDLGamepad::SDLSetGamepadPlayerIndex($pad, 1)) {
    pass('SDLSetGamepadPlayerIndex(1)');
    $idx = SDLGamepad::SDLGetGamepadPlayerIndex($pad);
    if ($idx === 1) {
        pass("SDLGetGamepadPlayerIndex → {$idx}");
    } else {
        fail('SDLGetGamepadPlayerIndex', "expected 1, got {$idx}");
        $errors++;
    }
    $padFromPlayer = SDLGamepad::SDLGetGamepadFromPlayerIndex(1);
    if ($padFromPlayer === $pad) {
        pass('SDLGetGamepadFromPlayerIndex(1) returns same handle');
    } else {
        fail('SDLGetGamepadFromPlayerIndex', 'handle mismatch');
        $errors++;
    }
} else {
    fail('SDLSetGamepadPlayerIndex', sdl_err());
    $errors++;
}

section('Optional effect/rumble/LED (may be unsupported on virtual device)');
SDLGamepad::SDLRumbleGamepad($pad, 1000, 2000, 100);
pass('SDLRumbleGamepad invoked');
SDLGamepad::SDLRumbleGamepadTriggers($pad, 500, 500, 100);
pass('SDLRumbleGamepadTriggers invoked');
SDLGamepad::SDLSetGamepadLED($pad, 0, 128, 255);
pass('SDLSetGamepadLED invoked');
SDLGamepad::SDLSendGamepadEffect($pad, "\x01\x02\x03\x04");
pass('SDLSendGamepadEffect invoked');

section('Per-ID metadata and SetGamepadMapping');
$vendorForId = SDLGamepad::SDLGetGamepadVendorForID($instanceId);
$productForId = SDLGamepad::SDLGetGamepadProductForID($instanceId);
$versionForId = SDLGamepad::SDLGetGamepadProductVersionForID($instanceId);
$playerForId = SDLGamepad::SDLGetGamepadPlayerIndexForID($instanceId);
$pathForId = SDLGamepad::SDLGetGamepadPathForID($instanceId);
pass("ForID metadata vendor={$vendorForId} product={$productForId} version={$versionForId} player={$playerForId} path='{$pathForId}'");

$vendor = SDLGamepad::SDLGetGamepadVendor($pad);
$product = SDLGamepad::SDLGetGamepadProduct($pad);
$version = SDLGamepad::SDLGetGamepadProductVersion($pad);
$firmware = SDLGamepad::SDLGetGamepadFirmwareVersion($pad);
$serial = SDLGamepad::SDLGetGamepadSerial($pad);
$steam = SDLGamepad::SDLGetGamepadSteamHandle($pad);
pass("Opened metadata vendor={$vendor} product={$product} version={$version} firmware={$firmware} serial='{$serial}' steam={$steam}");

if (SDLGamepad::SDLSetGamepadMapping($instanceId, $mappingLine)) {
    pass('SDLSetGamepadMapping round-trip with same mapping');
} else {
    fail('SDLSetGamepadMapping', sdl_err());
    $errors++;
}

section('Cleanup');
SDLGamepad::SDLCloseGamepad($pad);
pass('SDLCloseGamepad');

if (!SDLJoystick::SDLDetachVirtualJoystick($instanceId)) {
    fail('SDLDetachVirtualJoystick', sdl_err());
    $errors++;
} else {
    pass('SDLDetachVirtualJoystick');
}

SDL::SDLQuitSubSystem(SDL_INIT_GAMEPAD);
pass('SDL_QuitSubSystem(GAMEPAD)');

SDL::SDLQuit();
pass('SDL_Quit');

section('Summary');
if ($errors === 0) {
    echo "  All gamepad checks passed.\n\n";
    exit(0);
}

echo "  {$errors} check(s) FAILED.\n\n";
exit(1);
