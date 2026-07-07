<?php

namespace Sdl3\SDL\Audio;

/**
 * SDL audio subsystem — devices, streams, push/pull binary I/O, and optional callbacks.
 */
class SDLAudio
{


    /**
     * @return int
     */
    public static function SDLGetNumAudioDrivers(): int
    {
    }

    /**
     * @param int $index
     * @return string
     */
    public static function SDLGetAudioDriver(int $index): string
    {
    }

    /**
     * @return string
     */
    public static function SDLGetCurrentAudioDriver(): string
    {
    }

    /**
     * @return array
     */
    public static function SDLGetAudioPlaybackDevices(): array
    {
    }

    /**
     * @return array
     */
    public static function SDLGetAudioRecordingDevices(): array
    {
    }

    /**
     * @param int $devid
     * @return string
     */
    public static function SDLGetAudioDeviceName(int $devid): string
    {
    }

    /**
     * @param int $devid
     * @return array
     */
    public static function SDLGetAudioDeviceFormat(int $devid): array
    {
    }

    /**
     * @param int $devid
     * @return array
     */
    public static function SDLGetAudioDeviceChannelMap(int $devid): array
    {
    }

    /**
     * @param int $devid
     * @param mixed $spec
     * @return int
     */
    public static function SDLOpenAudioDevice(int $devid, $spec = null): int
    {
    }

    /**
     * @param int $devid
     * @return bool
     */
    public static function SDLIsAudioDevicePhysical(int $devid): bool
    {
    }

    /**
     * @param int $devid
     * @return bool
     */
    public static function SDLIsAudioDevicePlayback(int $devid): bool
    {
    }

    /**
     * @param int $devid
     * @return bool
     */
    public static function SDLPauseAudioDevice(int $devid): bool
    {
    }

    /**
     * @param int $devid
     * @return bool
     */
    public static function SDLResumeAudioDevice(int $devid): bool
    {
    }

    /**
     * @param int $devid
     * @return bool
     */
    public static function SDLAudioDevicePaused(int $devid): bool
    {
    }

    /**
     * @param int $devid
     * @return float
     */
    public static function SDLGetAudioDeviceGain(int $devid): float
    {
    }

    /**
     * @param int $devid
     * @param double $gain
     * @return bool
     */
    public static function SDLSetAudioDeviceGain(int $devid, float $gain): bool
    {
    }

    /**
     * @param int $devid
     * @return void
     */
    public static function SDLCloseAudioDevice(int $devid): void
    {
    }

    /**
     * @param int $devid
     * @param array $streams
     * @return bool
     */
    public static function SDLBindAudioStreams(int $devid, array $streams): bool
    {
    }

    /**
     * @param int $devid
     * @param int $stream
     * @return bool
     */
    public static function SDLBindAudioStream(int $devid, int $stream): bool
    {
    }

    /**
     * @param array $streams
     * @return void
     */
    public static function SDLUnbindAudioStreams(array $streams): void
    {
    }

    /**
     * @param int $stream
     * @return void
     */
    public static function SDLUnbindAudioStream(int $stream): void
    {
    }

    /**
     * @param int $stream
     * @return int
     */
    public static function SDLGetAudioStreamDevice(int $stream): int
    {
    }

    /**
     * @param mixed $src_spec
     * @param mixed $dst_spec
     * @return int
     */
    public static function SDLCreateAudioStream($src_spec, $dst_spec): int
    {
    }

    /**
     * @param int $stream
     * @return int
     */
    public static function SDLGetAudioStreamProperties(int $stream): int
    {
    }

    /**
     * @param int $stream
     * @return array
     */
    public static function SDLGetAudioStreamFormat(int $stream): array
    {
    }

    /**
     * @param int $stream
     * @param mixed $src_spec
     * @param mixed $dst_spec
     * @return bool
     */
    public static function SDLSetAudioStreamFormat(int $stream, $src_spec, $dst_spec): bool
    {
    }

    /**
     * @param int $stream
     * @return float
     */
    public static function SDLGetAudioStreamFrequencyRatio(int $stream): float
    {
    }

    /**
     * @param int $stream
     * @param double $ratio
     * @return bool
     */
    public static function SDLSetAudioStreamFrequencyRatio(int $stream, float $ratio): bool
    {
    }

    /**
     * @param int $stream
     * @return float
     */
    public static function SDLGetAudioStreamGain(int $stream): float
    {
    }

    /**
     * @param int $stream
     * @param double $gain
     * @return bool
     */
    public static function SDLSetAudioStreamGain(int $stream, float $gain): bool
    {
    }

    /**
     * @param int $stream
     * @return array
     */
    public static function SDLGetAudioStreamInputChannelMap(int $stream): array
    {
    }

    /**
     * @param int $stream
     * @return array
     */
    public static function SDLGetAudioStreamOutputChannelMap(int $stream): array
    {
    }

    /**
     * @param int $stream
     * @param array $chmap
     * @return bool
     */
    public static function SDLSetAudioStreamInputChannelMap(int $stream, array $chmap): bool
    {
    }

    /**
     * @param int $stream
     * @param array $chmap
     * @return bool
     */
    public static function SDLSetAudioStreamOutputChannelMap(int $stream, array $chmap): bool
    {
    }

    /**
     * @param int $stream
     * @param string $data
     * @return bool
     */
    public static function SDLPutAudioStreamData(int $stream, string $data): bool
    {
    }

    /**
     * @param int $stream
     * @param string $data
     * @param mixed $callback
     * @return bool
     */
    public static function SDLPutAudioStreamDataNoCopy(int $stream, string $data, $callback = null): bool
    {
    }

    /**
     * @param int $stream
     * @param array $channel_buffers
     * @param int $num_channels
     * @param int $num_samples
     * @return bool
     */
    public static function SDLPutAudioStreamPlanarData(int $stream, array $channel_buffers, int $num_channels, int $num_samples): bool
    {
    }

    /**
     * @param int $stream
     * @param int $len
     * @return string
     */
    public static function SDLGetAudioStreamData(int $stream, int $len): string
    {
    }

    /**
     * @param int $stream
     * @return int
     */
    public static function SDLGetAudioStreamAvailable(int $stream): int
    {
    }

    /**
     * @param int $stream
     * @return int
     */
    public static function SDLGetAudioStreamQueued(int $stream): int
    {
    }

    /**
     * @param int $stream
     * @return bool
     */
    public static function SDLFlushAudioStream(int $stream): bool
    {
    }

    /**
     * @param int $stream
     * @return bool
     */
    public static function SDLClearAudioStream(int $stream): bool
    {
    }

    /**
     * @param int $stream
     * @return bool
     */
    public static function SDLPauseAudioStreamDevice(int $stream): bool
    {
    }

    /**
     * @param int $stream
     * @return bool
     */
    public static function SDLResumeAudioStreamDevice(int $stream): bool
    {
    }

    /**
     * @param int $stream
     * @return bool
     */
    public static function SDLAudioStreamDevicePaused(int $stream): bool
    {
    }

    /**
     * @param int $stream
     * @return bool
     */
    public static function SDLLockAudioStream(int $stream): bool
    {
    }

    /**
     * @param int $stream
     * @return bool
     */
    public static function SDLUnlockAudioStream(int $stream): bool
    {
    }

    /**
     * @param int $stream
     * @param mixed $callback
     * @return bool
     */
    public static function SDLSetAudioStreamGetCallback(int $stream, $callback = null): bool
    {
    }

    /**
     * @param int $stream
     * @param mixed $callback
     * @return bool
     */
    public static function SDLSetAudioStreamPutCallback(int $stream, $callback = null): bool
    {
    }

    /**
     * @param int $stream
     * @return void
     */
    public static function SDLDestroyAudioStream(int $stream): void
    {
    }

    /**
     * @param int $devid
     * @param mixed $spec
     * @param mixed $callback
     * @return int
     */
    public static function SDLOpenAudioDeviceStream(int $devid, $spec = null, $callback = null): int
    {
    }

    /**
     * @param int $devid
     * @param mixed $callback
     * @return bool
     */
    public static function SDLSetAudioPostmixCallback(int $devid, $callback = null): bool
    {
    }

    /**
     * @param string $path
     * @return array
     */
    public static function SDLLoadWAV(string $path): array
    {
    }

    /**
     * @param string $dst
     * @param string $src
     * @param int $format
     * @param int $len
     * @param double $volume
     * @return string
     */
    public static function SDLMixAudio(string $dst, string $src, int $format, int $len, float $volume): string
    {
    }

    /**
     * @param mixed $src_spec
     * @param string $src_data
     * @param int $src_len
     * @param mixed $dst_spec
     * @return array
     */
    public static function SDLConvertAudioSamples($src_spec, string $src_data, int $src_len, $dst_spec): array
    {
    }

    /**
     * @param int $format
     * @return string
     */
    public static function SDLGetAudioFormatName(int $format): string
    {
    }

    /**
     * @param int $format
     * @return int
     */
    public static function SDLGetSilenceValueForFormat(int $format): int
    {
    }
}
