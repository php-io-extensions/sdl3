<?php

namespace Sdl3\SDL\Dialog;

/**
 * SDL file dialog subsystem — async native dialogs with PHP callback bridge.
 *
 * Callbacks fire during event pumping; callers must run an event loop
 * (e.g. SDL_PollEvent / SDL_PumpEvents) for results to arrive.
 */
class SDLDialog
{


    /**
     * @param mixed $callback
     * @param int $window
     * @param mixed $filters
     * @param mixed $default_location
     * @param bool $allow_many
     * @return void
     */
    public static function SDLShowOpenFileDialog($callback, int $window = 0, $filters = null, $default_location = null, bool $allow_many = false): void
    {
    }

    /**
     * @param mixed $callback
     * @param int $window
     * @param mixed $filters
     * @param mixed $default_location
     * @return void
     */
    public static function SDLShowSaveFileDialog($callback, int $window = 0, $filters = null, $default_location = null): void
    {
    }

    /**
     * @param mixed $callback
     * @param int $window
     * @param mixed $default_location
     * @param bool $allow_many
     * @return void
     */
    public static function SDLShowOpenFolderDialog($callback, int $window = 0, $default_location = null, bool $allow_many = false): void
    {
    }

    /**
     * @param int $type
     * @param mixed $callback
     * @param int $props
     * @return void
     */
    public static function SDLShowFileDialogWithProperties(int $type, $callback, int $props): void
    {
    }
}
