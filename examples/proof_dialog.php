<?php
/**
 * sdl3 extension — SDL Dialog proof script (WP8)
 *
 * Smoke test: verifies dialog bindings are present. When stdin is a TTY and a
 * display is available, launches one open-file dialog and pumps events until
 * the async callback fires (cancel the dialog to complete).
 *
 * Usage:
 *   php examples/proof_dialog.php
 */

declare(strict_types=1);

use Sdl3\SDL\SDL;
use Sdl3\SDL\SDLError;
use Sdl3\SDL\Dialog\SDLDialog;
use Sdl3\SDL\Events\SDLEvents;

const SDL_INIT_VIDEO = 0x00000020;

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

function pump_until(int $timeout_ms, callable $done): bool
{
    $start = (int) (microtime(true) * 1000);
    while (((int) (microtime(true) * 1000) - $start) < $timeout_ms) {
        if ($done()) {
            return true;
        }
        SDLEvents::SDLPumpEvents();
        usleep(10000);
    }
    return $done();
}

$errors = 0;
$interactive = function_exists('posix_isatty') && posix_isatty(STDIN);

section('Extension check');
if (!extension_loaded('sdl3')) {
    echo "  [FATAL] sdl3 extension is NOT loaded. Aborting.\n";
    exit(1);
}
pass('sdl3 extension is loaded');

section('Binding surface');
$methods = [
    'SDLShowOpenFileDialog',
    'SDLShowSaveFileDialog',
    'SDLShowOpenFolderDialog',
    'SDLShowFileDialogWithProperties',
];
foreach ($methods as $method) {
    if (method_exists(SDLDialog::class, $method)) {
        pass("SDLDialog::{$method} exists");
    } else {
        fail("SDLDialog::{$method} missing");
        $errors++;
    }
}

if ($errors > 0) {
    section('Summary');
    echo "  {$errors} check(s) FAILED.\n\n";
    exit(1);
}

section('SDL_Init(SDL_INIT_VIDEO)');
if (!SDL::SDLInit(SDL_INIT_VIDEO)) {
    echo "  [SKIP] SDL_Init(SDL_INIT_VIDEO) failed (headless?): " . sdl_err() . "\n";
    echo "  Dialog bindings present; visual callback test requires a display server.\n\n";
    exit(0);
}
pass('SDL_Init(SDL_INIT_VIDEO) succeeded');

if ($interactive) {
    section('SDL_ShowOpenFileDialog interactive smoke');
    $openCalled = false;
    SDLDialog::SDLShowOpenFileDialog(
        static function (?array $files, int $filter) use (&$openCalled): void {
            $openCalled = true;
        },
        0,
        [
            ['name' => 'Text files', 'pattern' => 'txt;md'],
            ['name' => 'All files', 'pattern' => '*'],
        ]
    );
    pass('SDLShowOpenFileDialog invoked without error');
    echo "  (cancel the open-file dialog to continue)\n";
    if (pump_until(60000, static fn (): bool => $openCalled)) {
        pass('Open-file callback fired');
    } else {
        fail('Open-file callback', 'timed out — cancel the dialog to complete the test');
        $errors++;
    }
} else {
    section('Non-interactive smoke');
    pass('Skipped GUI dialog launch (no TTY); binding surface verified above');
}

section('Cleanup');
SDL::SDLQuit();
pass('SDL_Quit');

section('Summary');
if ($errors === 0) {
    echo "  All dialog smoke checks passed.\n\n";
    exit(0);
}

echo "  {$errors} check(s) FAILED.\n\n";
exit(1);
