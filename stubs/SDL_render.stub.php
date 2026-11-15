<?php

/** @generate-class-entries */

/**
 * An address other than 0 is trusted. SDL_DestroyRenderer() destroys the textures the renderer
 * made, and releases their PHP handles with it.
 *
 * @not-serializable
 */
final class SDL_Renderer
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/**
 * An address other than 0 is trusted.
 *
 * @not-serializable
 */
final class SDL_Texture
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/**
 * @not-serializable
 */
final class SDL_FPoint
{
    public float $x = 0.0;

    public float $y = 0.0;

    public function __construct(float $x = 0.0, float $y = 0.0) {}
}

/**
 * @not-serializable
 */
final class SDL_Vertex
{
    public SDL_FPoint $position;

    public SDL_FColor $color;

    public SDL_FPoint $tex_coord;

    public function __construct(SDL_FPoint $position, SDL_FColor $color, SDL_FPoint $tex_coord) {}
}

/**
 * Draws into $surface's pixels. The surface must outlive the renderer: destroy the renderer first.
 * No SDL_Init() is needed.
 */
function SDL_CreateSoftwareRenderer(SDL_Surface $surface): ?SDL_Renderer {}

/** Destroys the renderer and the textures it made. */
function SDL_DestroyRenderer(SDL_Renderer $renderer): void {}

function SDL_CreateTextureFromSurface(SDL_Renderer $renderer, SDL_Surface $surface): ?SDL_Texture {}

function SDL_DestroyTexture(SDL_Texture $texture): void {}

function SDL_SetTextureBlendMode(SDL_Texture $texture, int $blendMode): bool {}

function SDL_SetTextureScaleMode(SDL_Texture $texture, int $scaleMode): bool {}

/** $alpha is an Uint8: its low 8 bits are used. */
function SDL_SetTextureAlphaMod(SDL_Texture $texture, int $alpha): bool {}

/** $r, $g and $b are Uint8s: their low 8 bits are used. */
function SDL_SetTextureColorMod(SDL_Texture $texture, int $r, int $g, int $b): bool {}

/** Null takes the whole target. */
function SDL_SetRenderClipRect(SDL_Renderer $renderer, ?SDL_Rect $rect): bool {}

/**
 * $vertices is a list of SDL_Vertex and $num_vertices its count. $indices is a list of ints and
 * $num_indices its count; null $indices draws the vertices in order and ignores $num_indices.
 * A null $texture draws the vertex colours. A count past its list is refused.
 */
function SDL_RenderGeometry(SDL_Renderer $renderer, ?SDL_Texture $texture, array $vertices, int $num_vertices, ?array $indices, int $num_indices): bool {}

/** The software renderer batches: flush before reading the target surface's pixels. */
function SDL_FlushRenderer(SDL_Renderer $renderer): bool {}
