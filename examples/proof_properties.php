<?php
/**
 * sdl3 extension — SDL Properties proof script (WP1)
 *
 * Headless round-trip of every bindable property type: create, set, get,
 * enumerate, copy, lock, clear, destroy. No display server required.
 *
 * Usage:
 *   php examples/proof_properties.php
 */

declare(strict_types=1);

use Sdl3\SDL\SDL;
use Sdl3\SDL\SDLError;
use Sdl3\SDL\SDLProperties;
use Sdl3\SDL\Surface\SDLSurface;

const SDL_PROPERTY_TYPE_INVALID = 0;
const SDL_PROPERTY_TYPE_POINTER = 1;
const SDL_PROPERTY_TYPE_STRING = 2;
const SDL_PROPERTY_TYPE_NUMBER = 3;
const SDL_PROPERTY_TYPE_FLOAT = 4;
const SDL_PROPERTY_TYPE_BOOLEAN = 5;

const SDL_PIXELFORMAT_RGBA8888 = 373694468;

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

section('SDL_Init(0)');
if (!SDL::SDLInit(0)) {
    fail('SDL_Init', sdl_err());
    exit(1);
}
pass('SDL_Init succeeded');

section('SDL_GetGlobalProperties');
$globalProps = SDLProperties::SDLGetGlobalProperties();
if ($globalProps !== 0) {
    pass("Global properties id={$globalProps}");
} else {
    fail('SDLGetGlobalProperties', sdl_err());
    $errors++;
}

section('SDL_CreateProperties');
try {
    $props = SDLProperties::SDLCreateProperties();
    pass("Created properties id={$props}");
} catch (\RuntimeException $e) {
    fail('SDLCreateProperties', $e->getMessage());
    SDL::SDLQuit();
    exit(1);
}

section('Set / get every property type');

$surf = SDLSurface::SDLCreateSurface(4, 4, SDL_PIXELFORMAT_RGBA8888);
$surfPtr = $surf['ptr'];
if ($surfPtr === 0) {
    fail('SDLCreateSurface (fixture)', sdl_err());
    $errors++;
} else {
    pass('Surface fixture for pointer property');
}

$setOk = SDLProperties::SDLSetStringProperty($props, 'test.string', 'hello');
$setOk = $setOk && SDLProperties::SDLSetNumberProperty($props, 'test.number', 42);
$setOk = $setOk && SDLProperties::SDLSetFloatProperty($props, 'test.float', 3.14);
$setOk = $setOk && SDLProperties::SDLSetBooleanProperty($props, 'test.boolean', true);
$setOk = $setOk && SDLProperties::SDLSetPointerProperty($props, 'test.pointer', $surfPtr);

if ($setOk) {
    pass('All property setters succeeded');
} else {
    fail('Property setters', sdl_err());
    $errors++;
}

if (SDLProperties::SDLGetStringProperty($props, 'test.string', '') === 'hello') {
    pass('SDLGetStringProperty');
} else {
    fail('SDLGetStringProperty', 'expected "hello"');
    $errors++;
}

if (SDLProperties::SDLGetNumberProperty($props, 'test.number', 0) === 42) {
    pass('SDLGetNumberProperty');
} else {
    fail('SDLGetNumberProperty', 'expected 42');
    $errors++;
}

$gotFloat = SDLProperties::SDLGetFloatProperty($props, 'test.float', 0.0);
if (abs($gotFloat - 3.14) < 0.001) {
    pass('SDLGetFloatProperty');
} else {
    fail('SDLGetFloatProperty', "expected ~3.14, got {$gotFloat}");
    $errors++;
}

if (SDLProperties::SDLGetBooleanProperty($props, 'test.boolean', false) === true) {
    pass('SDLGetBooleanProperty');
} else {
    fail('SDLGetBooleanProperty', 'expected true');
    $errors++;
}

if (SDLProperties::SDLGetPointerProperty($props, 'test.pointer', 0) === $surfPtr) {
    pass('SDLGetPointerProperty');
} else {
    fail('SDLGetPointerProperty', "expected ptr {$surfPtr}");
    $errors++;
}

$typeChecks = [
    'test.string'   => SDL_PROPERTY_TYPE_STRING,
    'test.number'   => SDL_PROPERTY_TYPE_NUMBER,
    'test.float'    => SDL_PROPERTY_TYPE_FLOAT,
    'test.boolean'  => SDL_PROPERTY_TYPE_BOOLEAN,
    'test.pointer'  => SDL_PROPERTY_TYPE_POINTER,
];

foreach ($typeChecks as $name => $expectedType) {
    if (!SDLProperties::SDLHasProperty($props, $name)) {
        fail("SDLHasProperty({$name})", 'property missing');
        $errors++;
        continue;
    }
    $type = SDLProperties::SDLGetPropertyType($props, $name);
    if ($type === $expectedType) {
        pass("SDLGetPropertyType({$name}) = {$type}");
    } else {
        fail("SDLGetPropertyType({$name})", "expected {$expectedType}, got {$type}");
        $errors++;
    }
}

section('SDL_EnumerateProperties');
$enumerated = [];
$enumOk = SDLProperties::SDLEnumerateProperties(
    $props,
    static function (int $enumProps, string $name) use ($props, &$enumerated): void {
        if ($enumProps !== $props) {
            throw new \RuntimeException("enumerate props id mismatch: {$enumProps}");
        }
        $enumerated[] = $name;
    }
);

if ($enumOk) {
    pass('SDLEnumerateProperties returned true');
} else {
    fail('SDLEnumerateProperties', sdl_err());
    $errors++;
}

$expectedNames = array_keys($typeChecks);
sort($expectedNames);
sort($enumerated);
if ($enumerated === $expectedNames) {
    pass('Enumeration listed all five properties');
} else {
    fail(
        'Enumeration contents',
        'expected [' . implode(', ', $expectedNames) . '], got [' . implode(', ', $enumerated) . ']'
    );
    $errors++;
}

section('SDL_CopyProperties');
try {
    $copyDst = SDLProperties::SDLCreateProperties();
} catch (\RuntimeException $e) {
    fail('SDLCreateProperties (copy dst)', $e->getMessage());
    $copyDst = 0;
    $errors++;
}

if ($copyDst !== 0 && SDLProperties::SDLCopyProperties($props, $copyDst)) {
    pass('SDLCopyProperties');
    if (SDLProperties::SDLGetStringProperty($copyDst, 'test.string', '') === 'hello') {
        pass('Copied string property readable from dst');
    } else {
        fail('Copy verification', 'string not copied');
        $errors++;
    }
} else {
    fail('SDLCopyProperties', sdl_err());
    $errors++;
}

section('SDL_LockProperties / SDL_UnlockProperties');
if (SDLProperties::SDLLockProperties($props)) {
    pass('SDLLockProperties');
    SDLProperties::SDLUnlockProperties($props);
    pass('SDLUnlockProperties');
} else {
    fail('SDLLockProperties', sdl_err());
    $errors++;
}

section('SDL_ClearProperty');
if (SDLProperties::SDLClearProperty($props, 'test.string')) {
    pass('SDLClearProperty');
} else {
    fail('SDLClearProperty', sdl_err());
    $errors++;
}

if (!SDLProperties::SDLHasProperty($props, 'test.string')) {
    pass('Cleared property no longer present');
} else {
    fail('Post-clear HasProperty', 'test.string still exists');
    $errors++;
}

if (SDLProperties::SDLGetStringProperty($props, 'test.string', 'fallback') === 'fallback') {
    pass('SDLGetStringProperty returns default after clear');
} else {
    fail('SDLGetStringProperty default after clear');
    $errors++;
}

section('Cleanup');
if ($surfPtr !== 0) {
    SDLSurface::SDLDestroySurface($surfPtr);
    pass('SDLDestroySurface (fixture)');
}
if ($copyDst !== 0) {
    SDLProperties::SDLDestroyProperties($copyDst);
    pass('SDLDestroyProperties (copy dst)');
}
SDLProperties::SDLDestroyProperties($props);
pass('SDLDestroyProperties (primary)');
SDL::SDLQuit();
pass('SDL_Quit');

section('Summary');
if ($errors === 0) {
    echo "  All property checks passed.\n\n";
    exit(0);
}

echo "  {$errors} check(s) FAILED.\n\n";
exit(1);
