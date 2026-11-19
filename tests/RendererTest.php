<?php

declare(strict_types=1);

/*
 * The software renderer and the surface calls it rests on: SDL_CreateSurface, SDL_ConvertSurface,
 * the alpha and colour mods, SDL_CreateSoftwareRenderer, textures and their lifetime. None of it
 * needs SDL_Init(): a software renderer draws into a surface with no video up.
 */

/** The bytes of a surface's pixels, rows packed (a surface from SDL_CreateSurface may pad its pitch). */
function rendererBytes(SDL_Surface $surface): string
{
    $row = $surface->w() * match ($surface->format()) {
        SDL_PIXELFORMAT_RGB24, SDL_PIXELFORMAT_BGR24 => 3,
        SDL_PIXELFORMAT_RGB565, SDL_PIXELFORMAT_BGR565 => 2,
        default => 4,
    };
    $io = SDL_IOFromConstMem($surface->pixels(), $surface->pitch() * $surface->h());
    $all = readIO($io, $surface->pitch() * $surface->h());
    SDL_CloseIO($io);
    $rows = [];
    for ($y = 0; $y < $surface->h(); $y++) {
        $rows[] = substr($all, $y * $surface->pitch(), $row);
    }

    return implode('', $rows);
}

it('creates a zeroed surface of SDL\'s own memory', function (): void {
    $surface = SDL_CreateSurface(5, 3, SDL_PIXELFORMAT_RGBA32);

    expect($surface)->toBeInstanceOf(SDL_Surface::class)
        ->and([$surface->w(), $surface->h(), $surface->format()])->toBe([5, 3, SDL_PIXELFORMAT_RGBA32])
        ->and($surface->pixels())->not->toBe(0)
        ->and(rendererBytes($surface))->toBe(str_repeat("\0", 5 * 3 * 4))
        ->and(SDL_CreateSurface(-1, 3, SDL_PIXELFORMAT_RGBA32))->toBeNull()
        ->and(SDL_GetError())->not->toBe('');

    SDL_DestroySurface($surface);
});

it('converts a surface into another format and leaves the first as it was', function (): void {
    $source = SDL_CreateSurfaceFrom(2, 1, SDL_PIXELFORMAT_RGBA32, "\x11\x22\x33\x44\x55\x66\x77\x88", 8);
    $bgra = SDL_ConvertSurface($source, SDL_PIXELFORMAT_BGRA32);
    $rgb = SDL_ConvertSurface($source, SDL_PIXELFORMAT_RGB24);

    expect($bgra->format())->toBe(SDL_PIXELFORMAT_BGRA32)
        ->and(rendererBytes($bgra))->toBe("\x33\x22\x11\x44\x77\x66\x55\x88")
        ->and(rendererBytes($rgb))->toBe("\x11\x22\x33\x55\x66\x77")
        ->and(rendererBytes($source))->toBe("\x11\x22\x33\x44\x55\x66\x77\x88")
        ->and(SDL_ConvertSurface($source, 0))->toBeNull();

    foreach ([$source, $bgra, $rgb] as $surface) {
        SDL_DestroySurface($surface);
    }
});

it('holds a surface\'s alpha and colour mods, and a blit uses them', function (): void {
    $source = SDL_CreateSurfaceFrom(1, 1, SDL_PIXELFORMAT_RGBA32, "\xff\xff\xff\xff", 4);
    $target = SDL_CreateSurfaceFrom(1, 1, SDL_PIXELFORMAT_RGBA32, "\x00\x00\x00\xff", 4);

    expect(SDL_GetSurfaceAlphaMod($source, $alpha))->toBeTrue()
        ->and($alpha)->toBe(255)
        ->and(SDL_GetSurfaceColorMod($source, $r, $g, $b))->toBeTrue()
        ->and([$r, $g, $b])->toBe([255, 255, 255])
        ->and(SDL_SetSurfaceAlphaMod($source, 128))->toBeTrue()
        ->and(SDL_SetSurfaceColorMod($source, 255, 0, 64))->toBeTrue()
        ->and(SDL_GetSurfaceAlphaMod($source, $alpha))->toBeTrue()
        ->and($alpha)->toBe(128)
        ->and(SDL_GetSurfaceColorMod($source, $r, $g, $b))->toBeTrue()
        ->and([$r, $g, $b])->toBe([255, 0, 64]);

    SDL_BlitSurface($source, null, $target, null);
    // White at alpha 128 tinted (255, 0, 64) over opaque black, as SDL lands it: red 128, green none, blue 32, alpha kept.
    expect(bin2hex(rendererBytes($target)))->toBe('800020ff');

    SDL_DestroySurface($source);
    SDL_DestroySurface($target);
});

it('creates a software renderer over a surface with no video up', function (): void {
    $target = SDL_CreateSurface(8, 8, SDL_PIXELFORMAT_RGBA32);
    $renderer = SDL_CreateSoftwareRenderer($target);

    expect($renderer)->toBeInstanceOf(SDL_Renderer::class)
        ->and($renderer->pointer())->not->toBe(0)
        ->and(SDL_SetRenderClipRect($renderer, new SDL_Rect(1, 1, 4, 4)))->toBeTrue()
        ->and(SDL_SetRenderClipRect($renderer, null))->toBeTrue()
        ->and(SDL_FlushRenderer($renderer))->toBeTrue();

    SDL_DestroyRenderer($renderer);
    expect($renderer->pointer())->toBe(0);
    SDL_DestroySurface($target);
});

it('releases a texture with SDL_DestroyTexture and every texture with its renderer', function (): void {
    $target = SDL_CreateSurface(8, 8, SDL_PIXELFORMAT_RGBA32);
    $source = SDL_CreateSurface(4, 4, SDL_PIXELFORMAT_RGBA32);
    $renderer = SDL_CreateSoftwareRenderer($target);
    $one = SDL_CreateTextureFromSurface($renderer, $source);
    $two = SDL_CreateTextureFromSurface($renderer, $source);

    expect($one)->toBeInstanceOf(SDL_Texture::class)
        ->and($one->pointer())->not->toBe($two->pointer())
        ->and(SDL_SetTextureBlendMode($one, SDL_BLENDMODE_BLEND))->toBeTrue()
        ->and(SDL_SetTextureScaleMode($one, SDL_SCALEMODE_LINEAR))->toBeTrue()
        ->and(SDL_SetTextureAlphaMod($one, 200))->toBeTrue()
        ->and(SDL_SetTextureColorMod($one, 255, 128, 0))->toBeTrue();

    SDL_DestroyTexture($one);
    expect($one->pointer())->toBe(0)
        ->and($two->pointer())->not->toBe(0)
        ->and($renderer->pointer())->not->toBe(0);

    // The renderer's textures go with it, and so do their PHP handles.
    SDL_DestroyRenderer($renderer);
    expect($two->pointer())->toBe(0)
        ->and($renderer->pointer())->toBe(0);

    SDL_DestroySurface($source);
    SDL_DestroySurface($target);
});

/** A vertex at ($x, $y) with a texture coordinate and a colour (white unless given as [r, g, b, a]). */
function rendererVertex(float $x, float $y, float $u, float $v, array $rgba = [1.0, 1.0, 1.0, 1.0]): SDL_Vertex
{
    $color = new SDL_FColor();
    [$color->r, $color->g, $color->b, $color->a] = $rgba;

    return new SDL_Vertex(new SDL_FPoint($x, $y), $color, new SDL_FPoint($u, $v));
}

/**
 * A rotated quad over a 32x32 surface, textured with a solid red 8x8 surface: $mod is applied to the
 * texture first, $rgba is every vertex's colour.
 */
function rotatedQuad(?Closure $mod = null, array $rgba = [1.0, 1.0, 1.0, 1.0]): string
{
    $target = SDL_CreateSurface(32, 32, SDL_PIXELFORMAT_RGBA32);
    $source = SDL_CreateSurface(8, 8, SDL_PIXELFORMAT_RGBA32);
    SDL_FillSurfaceRect($source, null, 0xFF0000FF);
    $renderer = SDL_CreateSoftwareRenderer($target);
    $texture = SDL_CreateTextureFromSurface($renderer, $source);
    SDL_SetTextureBlendMode($texture, SDL_BLENDMODE_BLEND);
    if ($mod !== null) {
        $mod($texture);
    }
    $quad = [rendererVertex(4, 4, 0, 0, $rgba), rendererVertex(28, 8, 1, 0, $rgba), rendererVertex(24, 28, 1, 1, $rgba), rendererVertex(2, 22, 0, 1, $rgba)];

    expect(SDL_RenderGeometry($renderer, $texture, $quad, 4, [0, 1, 2, 0, 2, 3], 6))->toBeTrue()
        ->and(SDL_FlushRenderer($renderer))->toBeTrue();
    $bytes = rendererBytes($target);
    SDL_DestroyRenderer($renderer);
    SDL_DestroySurface($source);
    SDL_DestroySurface($target);

    return $bytes;
}

it('draws a textured, rotated quad into a software renderer\'s surface', function (): void {
    $bytes = rotatedQuad();
    $at = fn (int $x, int $y): string => bin2hex(substr($bytes, ($y * 32 + $x) * 4, 4));

    // Inside the quad the texture's red, opaque; outside it the surface is untouched.
    expect($at(16, 16))->toBe('ff0000ff')
        ->and($at(12, 14))->toBe('ff0000ff')
        ->and($at(0, 0))->toBe('00000000')
        ->and($at(31, 31))->toBe('00000000')
        ->and($at(30, 4))->toBe('00000000');
});

it('modulates a quad by its vertex colours, which is how the software renderer takes a tint and an opacity', function (): void {
    $centre = (16 * 32 + 16) * 4;
    $at = fn (string $bytes): string => bin2hex(substr($bytes, $centre, 4));

    expect($at(rotatedQuad()))->toBe('ff0000ff')
        // Vertex colour (0.5, 1, 1, 1): the red channel halves, alpha stays.
        ->and($at(rotatedQuad(null, [0.5, 1.0, 1.0, 1.0])))->toBe('800000ff')
        // Vertex alpha 0.5 over a transparent surface: SDL's blend leaves red scaled by the alpha, as it blends (premultiplied), alpha 128.
        ->and($at(rotatedQuad(null, [1.0, 1.0, 1.0, 0.5])))->toBe('80000080')
        ->and($at(rotatedQuad(null, [1.0, 1.0, 1.0, 200 / 255])))->toBe('c80000c8');
});

it('does not apply a texture\'s own alpha and colour mod to the software renderer\'s geometry', function (): void {
    $centre = (16 * 32 + 16) * 4;
    $at = fn (string $bytes): string => bin2hex(substr($bytes, $centre, 4));

    // The mods are set (the calls succeed) but SDL's software renderer takes colour and alpha from the vertices only.
    expect($at(rotatedQuad(fn (SDL_Texture $t) => SDL_SetTextureAlphaMod($t, 128))))->toBe('ff0000ff')
        ->and($at(rotatedQuad(fn (SDL_Texture $t) => SDL_SetTextureColorMod($t, 128, 255, 255))))->toBe('ff0000ff');
});

it('refuses a count past its list instead of reading past it', function (): void {
    $target = SDL_CreateSurface(8, 8, SDL_PIXELFORMAT_RGBA32);
    $renderer = SDL_CreateSoftwareRenderer($target);
    $triangle = [rendererVertex(0, 0, 0, 0), rendererVertex(7, 0, 1, 0), rendererVertex(0, 7, 0, 1)];

    expect(fn () => SDL_RenderGeometry($renderer, null, $triangle, 4, null, 0))->toThrow(ValueError::class, 'must be between 0 and the length of argument #3 ($vertices)')
        ->and(fn () => SDL_RenderGeometry($renderer, null, $triangle, 3, [0, 1, 2], 7))->toThrow(ValueError::class, 'must be between 0 and the length of argument #5 ($indices)')
        ->and(fn () => SDL_RenderGeometry($renderer, null, [new stdClass()], 1, null, 0))->toThrow(TypeError::class)
        ->and(SDL_RenderGeometry($renderer, null, $triangle, 3, null, 0))->toBeTrue();

    SDL_DestroyRenderer($renderer);
    SDL_DestroySurface($target);
});

it('draws packed triangles with a colour at each corner through SDL_RenderGeometryRaw', function (): void {
    $target = SDL_CreateSurface(8, 8, SDL_PIXELFORMAT_RGBA32);
    $renderer = SDL_CreateSoftwareRenderer($target);
    // one triangle over the top-left half, (0,0) (8,0) (0,8), opaque red at every corner: xy two floats a vertex,
    // colour four (an SDL_FColor)
    $xy = pack('g*', 0.0, 0.0, 8.0, 0.0, 0.0, 8.0);
    $red = pack('g*', 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0);

    expect(SDL_RenderGeometryRaw($renderer, null, $xy, 8, $red, 16, null, 0, 3, null, 0, 0))->toBeTrue()
        ->and(SDL_FlushRenderer($renderer))->toBeTrue();
    $bytes = rendererBytes($target);
    $at = fn (int $x, int $y): string => bin2hex(substr($bytes, ($y * 8 + $x) * 4, 4));

    // (1,1) is inside; (6,6) is past the diagonal x + y = 8, so untouched
    expect($at(1, 1))->toBe('ff0000ff')
        ->and($at(6, 6))->toBe('00000000');

    // the same triangle by index on a fresh surface, with one colour read three times (a stride of 0), 16-bit indices
    SDL_DestroyRenderer($renderer);
    SDL_DestroySurface($target);
    $target = SDL_CreateSurface(8, 8, SDL_PIXELFORMAT_RGBA32);
    $renderer = SDL_CreateSoftwareRenderer($target);
    $green = pack('g*', 0.0, 1.0, 0.0, 1.0);
    expect(SDL_RenderGeometryRaw($renderer, null, $xy, 8, $green, 0, null, 0, 3, pack('v*', 0, 1, 2), 3, 2))->toBeTrue()
        ->and(SDL_FlushRenderer($renderer))->toBeTrue();
    $bytes = rendererBytes($target);
    $at = fn (int $x, int $y): string => bin2hex(substr($bytes, ($y * 8 + $x) * 4, 4));
    expect($at(1, 1))->toBe('00ff00ff')
        ->and($at(6, 6))->toBe('00000000');

    // a string shorter than its stride and count reach is refused: 3 vertices of xy need 2 * 8 + 8 = 24 bytes
    expect(fn () => SDL_RenderGeometryRaw($renderer, null, substr($xy, 0, 20), 8, $red, 16, null, 0, 3, null, 0, 0))
        ->toThrow(ValueError::class, 'Argument #3 ($xy) must hold 24 bytes, 20 given')
        ->and(fn () => SDL_RenderGeometryRaw($renderer, null, $xy, 8, $red, 16, null, 0, 3, pack('v*', 0, 1), 3, 2))
        ->toThrow(ValueError::class, 'Argument #10 ($indices) must hold 6 bytes, 4 given')
        ->and(fn () => SDL_RenderGeometryRaw($renderer, null, $xy, -8, $red, 16, null, 0, 3, null, 0, 0))
        ->toThrow(ValueError::class, 'Argument #3 ($xy) must hold the bytes its stride and count reach, with a stride of 0 or more: 24 given');

    SDL_DestroyRenderer($renderer);
    SDL_DestroySurface($target);
});

it('does not let textures made and destroyed every frame pile up in their renderer', function (): void {
    $target = SDL_CreateSurface(8, 8, SDL_PIXELFORMAT_RGBA32);
    $source = SDL_CreateSurface(64, 64, SDL_PIXELFORMAT_RGBA32);
    $renderer = SDL_CreateSoftwareRenderer($target);

    $before = memory_get_usage();
    for ($i = 0; $i < 5000; $i++) {
        SDL_DestroyTexture(SDL_CreateTextureFromSurface($renderer, $source));
    }
    gc_collect_cycles();

    expect(memory_get_usage() - $before)->toBeLessThan(256 * 1024);

    SDL_DestroyRenderer($renderer);
    SDL_DestroySurface($source);
    SDL_DestroySurface($target);
});
