<?php

declare(strict_types=1);

/** The bytes at a surface's pixels, read through an SDL_IOStream over them. */
function surfaceBytes(SDL_Surface $surface): string
{
    $io = SDL_IOFromConstMem($surface->pixels(), $surface->pitch() * $surface->h());
    $bytes = readIO($io, $surface->pitch() * $surface->h());
    SDL_CloseIO($io);

    return $bytes;
}

it('wraps a PHP string as a surface and keeps the string alive', function (): void {
    $surface = (function (): SDL_Surface {
        $pixels = str_repeat("\x11\x22\x33\x44", 8);

        return SDL_CreateSurfaceFrom(4, 2, SDL_PIXELFORMAT_RGBA32, $pixels, 16);
    })();
    gc_collect_cycles();

    expect([$surface->w(), $surface->h(), $surface->pitch(), $surface->format()])->toBe([4, 2, 16, SDL_PIXELFORMAT_RGBA32])
        ->and(surfaceBytes($surface))->toBe(str_repeat("\x11\x22\x33\x44", 8));

    SDL_DestroySurface($surface);
});

it('fills and blits, scaled, between surfaces', function (): void {
    $source = SDL_CreateSurfaceFrom(2, 1, SDL_PIXELFORMAT_RGBA32, "\xff\x00\x00\xff\x00\x00\xff\xff", 8);
    $target = SDL_CreateSurfaceFrom(4, 2, SDL_PIXELFORMAT_RGBA32, str_repeat("\0", 32), 16);

    expect(SDL_FillSurfaceRect($target, null, 0))->toBeTrue()
        ->and(SDL_BlitSurfaceScaled($source, null, $target, new SDL_Rect(0, 0, 4, 2), SDL_SCALEMODE_NEAREST))->toBeTrue()
        ->and(bin2hex(substr(surfaceBytes($target), 0, 4)))->toBe('ff0000ff')
        ->and(bin2hex(substr(surfaceBytes($target), 12, 4)))->toBe('0000ffff')
        ->and(SDL_BlitSurface($source, new SDL_Rect(1, 0, 1, 1), $target, new SDL_Rect(0, 1, 1, 1)))->toBeTrue()
        ->and(bin2hex(substr(surfaceBytes($target), 16, 4)))->toBe('0000ffff');

    SDL_DestroySurface($source);
    SDL_DestroySurface($target);
});

it('writes through a stream over memory', function (): void {
    $target = SDL_CreateSurfaceFrom(2, 1, SDL_PIXELFORMAT_RGBA32, str_repeat("\0", 8), 8);
    $io = SDL_IOFromMem($target->pixels(), 8);

    expect(SDL_WriteIO($io, "\x01\x02\x03\x04\x05\x06\x07\x08", 8))->toBe(8)
        ->and(SDL_CloseIO($io))->toBeTrue()
        ->and(surfaceBytes($target))->toBe("\x01\x02\x03\x04\x05\x06\x07\x08")
        ->and(fn () => SDL_WriteIO(SDL_IOFromMem($target->pixels(), 8), 'abc', 4))->toThrow(ValueError::class, 'must hold');

    SDL_DestroySurface($target);
});

it('takes pixels from an address', function (): void {
    $buffer = new FbBuffer(new FbFormat(FB_LAYOUT_RGBA8888, channelOrder: FB_CHANNELS_RGBA), 2, 2);
    $buffer->fill(0x10203040);
    $surface = SDL_CreateSurfaceFrom(2, 2, SDL_PIXELFORMAT_RGBA32, $buffer->pointer(), 8);

    expect(surfaceBytes($surface))->toBe($buffer->bytes());

    SDL_DestroySurface($surface);
})->skip(! class_exists(FbBuffer::class), 'needs ext-fb for a native address');

it('updates a window surface', function (): void {
    $window = hiddenWindow();
    $surface = SDL_GetWindowSurface($window);

    expect($surface)->toBeInstanceOf(SDL_Surface::class)
        ->and(SDL_FillSurfaceRect($surface, null, 0))->toBeTrue()
        ->and(SDL_UpdateWindowSurface($window))->toBeBool();

    SDL_DestroyWindow($window);
});

it('opens a file as a stream and reads it back', function (): void {
    $file = tempnam(sys_get_temp_dir(), 'sdl3-io');
    file_put_contents($file, 'abcdef');

    $io = SDL_IOFromFile($file, 'rb');
    $read = $io === null ? '' : readIO($io, 6);

    expect($io)->toBeInstanceOf(SDL_IOStream::class)
        ->and($read)->toBe('abcdef')
        ->and(SDL_CloseIO($io))->toBeTrue()
        ->and(SDL_IOFromFile($file.'.missing', 'rb'))->toBeNull()
        ->and(SDL_GetError())->not->toBe('');
    unlink($file);
});

it('copies a translucent pixel unchanged with SDL_BLENDMODE_NONE and blends it with SDL_BLENDMODE_BLEND', function (): void {
    $pixel = "\xff\x00\x00\x80";
    $source = SDL_CreateSurfaceFrom(1, 1, SDL_PIXELFORMAT_RGBA32, $pixel, 4);
    $target = SDL_CreateSurfaceFrom(1, 1, SDL_PIXELFORMAT_RGBA32, "\x00\x00\xff\xff", 4);

    expect(SDL_GetSurfaceBlendMode($source, $mode))->toBeTrue()
        ->and($mode)->toBe(SDL_BLENDMODE_BLEND);
    SDL_BlitSurface($source, null, $target, null);
    expect(surfaceBytes($target))->not->toBe($pixel);

    expect(SDL_SetSurfaceBlendMode($source, SDL_BLENDMODE_NONE))->toBeTrue()
        ->and(SDL_GetSurfaceBlendMode($source, $mode))->toBeTrue()
        ->and($mode)->toBe(SDL_BLENDMODE_NONE);
    SDL_BlitSurface($source, null, $target, null);
    expect(surfaceBytes($target))->toBe($pixel)
        ->and(SDL_SetSurfaceBlendMode($source, SDL_BLENDMODE_INVALID))->toBeFalse();

    SDL_DestroySurface($source);
    SDL_DestroySurface($target);
});

it('fills and copies the 24- and 16-bit formats byte for byte', function (int $format, int $bytes): void {
    $pitch = 3 * $bytes;
    $source = SDL_CreateSurfaceFrom(3, 1, $format, substr("\x11\x22\x33\x44\x55\x66\x77\x88\x99", 0, $pitch), $pitch);
    $target = SDL_CreateSurfaceFrom(3, 1, $format, str_repeat("\0", $pitch), $pitch);
    SDL_SetSurfaceBlendMode($source, SDL_BLENDMODE_NONE);

    SDL_FillSurfaceRect($target, new SDL_Rect(0, 0, 1, 1), unpack('V', str_pad(substr("\xaa\xbb\xcc", 0, $bytes), 4, "\0"))[1]);
    SDL_BlitSurface($source, new SDL_Rect(0, 0, 2, 1), $target, new SDL_Rect(1, 0, 2, 1));

    expect(surfaceBytes($target))->toBe(substr("\xaa\xbb\xcc", 0, $bytes).substr("\x11\x22\x33\x44\x55\x66", 0, 2 * $bytes));

    SDL_DestroySurface($source);
    SDL_DestroySurface($target);
})->with([
    'RGB24' => [SDL_PIXELFORMAT_RGB24, 3],
    'BGR24' => [SDL_PIXELFORMAT_BGR24, 3],
    'RGB565' => [SDL_PIXELFORMAT_RGB565, 2],
    'BGR565' => [SDL_PIXELFORMAT_BGR565, 2],
]);
