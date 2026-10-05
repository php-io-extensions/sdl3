<?php

/** @generate-class-entries */

/**
 * An address other than 0 is trusted.
 *
 * @not-serializable
 */
final class SDL_GLContext
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): static {}
}

/**
 * An address other than 0 is trusted.
 *
 * @not-serializable
 */
final class SDL_MetalView
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): static {}
}

/**
 * @var int
 * @cvalue SDL_GL_RED_SIZE
 */
const SDL_GL_RED_SIZE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_GREEN_SIZE
 */
const SDL_GL_GREEN_SIZE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_BLUE_SIZE
 */
const SDL_GL_BLUE_SIZE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_ALPHA_SIZE
 */
const SDL_GL_ALPHA_SIZE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_DEPTH_SIZE
 */
const SDL_GL_DEPTH_SIZE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_STENCIL_SIZE
 */
const SDL_GL_STENCIL_SIZE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_DOUBLEBUFFER
 */
const SDL_GL_DOUBLEBUFFER = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_MULTISAMPLEBUFFERS
 */
const SDL_GL_MULTISAMPLEBUFFERS = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_MULTISAMPLESAMPLES
 */
const SDL_GL_MULTISAMPLESAMPLES = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_CONTEXT_MAJOR_VERSION
 */
const SDL_GL_CONTEXT_MAJOR_VERSION = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_CONTEXT_MINOR_VERSION
 */
const SDL_GL_CONTEXT_MINOR_VERSION = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_CONTEXT_PROFILE_MASK
 */
const SDL_GL_CONTEXT_PROFILE_MASK = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_CONTEXT_FLAGS
 */
const SDL_GL_CONTEXT_FLAGS = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_CONTEXT_PROFILE_CORE
 */
const SDL_GL_CONTEXT_PROFILE_CORE = UNKNOWN;

/**
 * @var int
 * @cvalue SDL_GL_CONTEXT_PROFILE_ES
 */
const SDL_GL_CONTEXT_PROFILE_ES = UNKNOWN;

function SDL_GL_SetAttribute(int $attr, int $value): bool {}

function SDL_GL_CreateContext(SDL_Window $window): ?SDL_GLContext {}

function SDL_GL_MakeCurrent(SDL_Window $window, ?SDL_GLContext $context): bool {}

function SDL_GL_SwapWindow(SDL_Window $window): bool {}

function SDL_GL_SetSwapInterval(int $interval): bool {}

function SDL_GL_DestroyContext(SDL_GLContext $context): bool {}

function SDL_Metal_CreateView(SDL_Window $window): ?SDL_MetalView {}

/** The CAMetalLayer address, for CAMetalLayer::fromPointer(). 0 is a null layer. */
function SDL_Metal_GetLayer(SDL_MetalView $view): int {}

function SDL_Metal_DestroyView(SDL_MetalView $view): void {}

/** Null when SDL has no extension list. */
function SDL_Vulkan_GetInstanceExtensions(): ?array {}

/**
 * $instance and $allocator are addresses. 0 and null are a null pointer; any other address is trusted.
 * $surface receives the VkSurfaceKHR as an int.
 */
function SDL_Vulkan_CreateSurface(SDL_Window $window, int $instance, ?int $allocator, ?int &$surface): bool {}

/** $instance, $surface and $allocator are addresses. 0 and null are a null pointer; any other address is trusted. */
function SDL_Vulkan_DestroySurface(int $instance, int $surface, ?int $allocator): void {}
