<?php

declare(strict_types=1);

it('installs php_sdl3_api.h with the runtime it includes', function () {
    $dir = trim((string) shell_exec(escapeshellarg(dirname(PHP_BINARY).'/php-config').' --include-dir')).'/ext/sdl3';
    expect(file_exists("$dir/php_sdl3_api.h"))->toBeTrue()
        ->and(file_exists("$dir/src/runtime.h"))->toBeTrue()
        ->and(file_get_contents("$dir/src/runtime.h"))->toContain('sdl3_add_audio_quit_hooks');
});
