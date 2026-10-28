<?php

declare(strict_types=1);

require_once __DIR__ . '/../scripts/support.php';

it('counts the SDL_DECLSPEC functions of each header, across lines, sorted, once each', function (): void {
    $video = "extern SDL_DECLSPEC int SDLCALL SDL_GetNumVideoDrivers(void);\n"
        . "extern SDL_DECLSPEC const char * SDLCALL SDL_GetVideoDriver(int index);\n"
        . "extern SDL_DECLSPEC SDL_Window * SDLCALL\nSDL_CreateWindow(const char *title, int w, int h, SDL_WindowFlags flags);\n"
        . "typedef void (SDLCALL *SDL_HintCallback)(void *userdata);\n";

    expect(support_counted(['SDL_video.h' => $video, 'SDL_begin_code.h' => "#define SDLCALL\n"]))
        ->toBe(['SDL_video.h' => ['SDL_CreateWindow', 'SDL_GetNumVideoDrivers', 'SDL_GetVideoDriver']]);
});

it('measures SDL headers only: not the test library or the old names', function (): void {
    expect(support_measured('SDL_video.h'))->toBeTrue()
        ->and(support_measured('SDL_test_assert.h'))->toBeFalse()
        ->and(support_measured('SDL_oldnames.h'))->toBeFalse()
        ->and(support_measured('LICENSE.txt'))->toBeFalse();
});

it('reads the top-level functions of a stub, not class methods', function (): void {
    $stub = "<?php\nfunction SDL_Init(int \$flags): bool {}\nfinal class SDL_Window { public function pointer(): int {} }\nfunction SDL_Quit(): void {}\n";

    expect(support_functions($stub))->toBe(['SDL_Init', 'SDL_Quit']);
});

it('renders one line per function and lists the bindings that match none', function (): void {
    $md = support_render(['SDL_init.h' => ['SDL_Init', 'SDL_Quit']], ['SDL_Init' => true, 'sdl_helper' => true], 'SDL 3.2.0', '2026-10-28');

    expect($md)->toContain('- [x] `SDL_Init`')
        ->toContain('- [ ] `SDL_Quit`')
        ->toContain('## SDL_init.h (1 / 2)')
        ->toContain('SDL 3.2.0 — 1 / 2 members bound (50.0%) — 2026-10-28')
        ->toContain('- `sdl_helper`');
});

it('computes the badge from the counts', function (): void {
    expect(support_badge('SDL API', 215, 1233))
        ->toBe('[![SDL API](https://img.shields.io/badge/SDL_API-17.4%25_%28215%2F1233%29-blue?style=flat-square)](SUPPORT.md)');
});

it('compares a support list without its date', function (): void {
    expect(support_same("SDL 3.2.0 — 2 / 4 members bound (50.0%) — 2026-10-28\n", "SDL 3.2.0 — 2 / 4 members bound (50.0%) — 2026-11-01\n"))->toBeTrue()
        ->and(support_same("SDL 3.2.0 — 2 / 4 members bound (50.0%) — 2026-10-28\n", "SDL 3.2.0 — 3 / 4 members bound (75.0%) — 2026-10-28\n"))->toBeFalse();
});
