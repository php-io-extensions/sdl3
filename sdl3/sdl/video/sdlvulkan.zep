namespace Sdl3\SDL\Video;

%{
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
}%

/**
 * SDL_vulkan.h. Every Vulkan handle crosses as raw pointer bits in an int
 * (0 = VK_NULL_HANDLE), the ext-vulkan currency. CreateSurface collapses
 * SDL's bool + out-param into the surface bits, 0 on failure — read
 * SDLError::SDLGetError() for the reason.
 */
class SDLVulkan
{
    public static function SDLVulkanLoadLibrary(var path = null) -> bool
    {
        bool result;
        var p;

        if typeof path != "null" && typeof path != "string" {
            throw new \TypeError("SDLVulkanLoadLibrary() expects ?string $path, got " . gettype(path));
        }

        let p = path;

        %{
            const char *libpath = (Z_TYPE_P(&p) == IS_NULL) ? NULL : Z_STRVAL(p);
            result = SDL_Vulkan_LoadLibrary(libpath);
        }%

        return result;
    }

    public static function SDLVulkanUnloadLibrary() -> void
    {
        %{
            SDL_Vulkan_UnloadLibrary();
        }%
    }

    public static function SDLVulkanGetVkGetInstanceProcAddr() -> int
    {
        int ptr;

        %{
            SDL_FunctionPointer fn = SDL_Vulkan_GetVkGetInstanceProcAddr();
            ptr = (zend_long)(uintptr_t) fn;
        }%

        return ptr;
    }

    public static function SDLVulkanGetInstanceExtensions() -> array
    {
        array result;

        %{
            Uint32 count = 0;
            char const * const *names = SDL_Vulkan_GetInstanceExtensions(&count);

            array_init(&result);
            if (names != NULL) {
                for (Uint32 i = 0; i < count; i++) {
                    add_next_index_string(&result, names[i]);
                }
            }
        }%

        return result;
    }

    public static function SDLVulkanCreateSurface(int window, int instance, int allocator) -> int
    {
        int ptr;

        %{
            VkSurfaceKHR surface = 0;
            bool ok = SDL_Vulkan_CreateSurface(
                (SDL_Window *)(uintptr_t) window,
                (VkInstance)(uintptr_t) instance,
                (const struct VkAllocationCallbacks *)(uintptr_t) allocator,
                &surface
            );
            ptr = ok ? (zend_long)(uintptr_t) surface : 0;
        }%

        return ptr;
    }

    public static function SDLVulkanDestroySurface(int instance, int surface, int allocator) -> void
    {
        %{
            SDL_Vulkan_DestroySurface(
                (VkInstance)(uintptr_t) instance,
                (VkSurfaceKHR)(uintptr_t) surface,
                (const struct VkAllocationCallbacks *)(uintptr_t) allocator
            );
        }%
    }

    public static function SDLVulkanGetPresentationSupport(int instance, int physical_device, int queue_family_index) -> bool
    {
        bool result;

        %{
            result = SDL_Vulkan_GetPresentationSupport(
                (VkInstance)(uintptr_t) instance,
                (VkPhysicalDevice)(uintptr_t) physical_device,
                (Uint32) queue_family_index
            );
        }%

        return result;
    }
}
