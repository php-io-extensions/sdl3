<?php
/**
 * ext-sdl3 0.8.0 wave proof. A window's events name their window; a Metal
 * view vends a CAMetalLayer (macOS); the Vulkan loader loads and names the
 * instance extensions the window needs. Surface creation itself is proven
 * downstream (venusian-vulkan + venusian-sdl3), where an instance exists.
 * PHP_OS_FAMILY is the caller choosing, which is where it may live.
 */

declare(strict_types=1);

use Sdl3\SDL\Events\SDLEvents;
use Sdl3\SDL\Render\SDLRender;
use Sdl3\SDL\SDL;
use Sdl3\SDL\SDLError;
use Sdl3\SDL\Video\SDLGL;
use Sdl3\SDL\Video\SDLMetal;
use Sdl3\SDL\Video\SDLVideo;
use Sdl3\SDL\Video\SDLVulkan;

function fail(string $why): never
{
    fwrite(STDERR, 'PROOF_STAGE_HOSTS_FAIL: '.$why.' — SDL says: '.SDLError::SDLGetError()."\n");
    exit(1);
}

SDL::SDLInit(0x20) || fail('SDL_Init(VIDEO)');                          // SDL_INIT_VIDEO

// 1. Window events carry their window id.
$window = SDLVideo::SDLCreateWindow('stage-hosts', 160, 120, 0x08);     // SDL_WINDOW_HIDDEN
$id = SDLVideo::SDLGetWindowID($window);
SDLVideo::SDLShowWindow($window);
$seen = null;
$deadline = microtime(true) + 2.0;
while (is_null($seen) && microtime(true) < $deadline) {
    while (! is_null($event = SDLEvents::SDLPollEvent())) {
        if ($event['event_type'] === 514) {                                 // SDL_EVENT_WINDOW_SHOWN
            $seen = SDLEvents::SDLReadEvent($event['ptr'], 'window');       // frees the event
            continue;
        }
        SDLEvents::SDLFreeEvent($event['ptr']);
    }
    usleep(10000);
}
is_array($seen) || fail('no SDL_EVENT_WINDOW_SHOWN');
$seen['window_id'] === $id || fail("window_id {$seen['window_id']} is not {$id}");
array_keys($seen) === ['type', 'timestamp', 'window_id', 'data1', 'data2'] || fail('window event shape');
SDLVideo::SDLDestroyWindow($window);

// 2. Metal view → CAMetalLayer pointer bits (macOS only).
if (PHP_OS_FAMILY === 'Darwin') {
    $metal = SDLVideo::SDLCreateWindow('stage-hosts-metal', 160, 120, 0x08 | 0x20000000);  // HIDDEN | SDL_WINDOW_METAL
    $view = SDLMetal::SDLMetalCreateView($metal);
    $view > 0 || fail('SDL_Metal_CreateView');
    SDLMetal::SDLMetalGetLayer($view) > 0 || fail('SDL_Metal_GetLayer');
    SDLMetal::SDLMetalDestroyView($view);
    SDLVideo::SDLDestroyWindow($metal);
}

// 3. Vulkan: the loader loads and names the window's instance extensions.
SDLVulkan::SDLVulkanLoadLibrary() || fail('SDL_Vulkan_LoadLibrary');
SDLVulkan::SDLVulkanGetVkGetInstanceProcAddr() > 0 || fail('vkGetInstanceProcAddr');
$extensions = SDLVulkan::SDLVulkanGetInstanceExtensions();
in_array('VK_KHR_surface', $extensions, true) || fail('VK_KHR_surface missing from '.implode(',', $extensions));
echo 'vulkan instance extensions: '.implode(', ', $extensions)."\n";
SDLVulkan::SDLVulkanUnloadLibrary();

// 4. ?string params behind `var x = null`: anything else is a TypeError, never C.
$typed = [
    'SDLVulkanLoadLibrary' => fn () => SDLVulkan::SDLVulkanLoadLibrary(1),
    'SDLGLLoadLibrary' => fn () => SDLGL::SDLGLLoadLibrary(1),
    'SDLCreateRenderer' => fn () => SDLRender::SDLCreateRenderer(0, 1),
];
foreach ($typed as $name => $call) {
    try {
        $call();
        fail("{$name}(int) did not throw TypeError");
    } catch (TypeError $e) {
        str_contains($e->getMessage(), $name) && str_contains($e->getMessage(), 'expects ?string')
            || fail("{$name} TypeError message: {$e->getMessage()}");
    }
}

echo "PROOF_STAGE_HOSTS_OK\n";
