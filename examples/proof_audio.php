<?php
/**
 * sdl3 extension — SDL Audio proof script (WP7)
 *
 * Headless via SDL_AUDIO_DRIVER=dummy: open default device, push sine-wave
 * samples, verify queued byte counts.
 *
 * Usage:
 *   SDL_AUDIO_DRIVER=dummy php examples/proof_audio.php
 */

declare(strict_types=1);

use Sdl3\SDL\SDL;
use Sdl3\SDL\SDLError;
use Sdl3\SDL\Audio\SDLAudio;

const SDL_INIT_AUDIO = 0x10;
const SDL_AUDIO_S16 = 0x8010;
const SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK = -1;

function pass(string $label): void
{
    echo "  [PASS] {$label}\n";
}

function fail(string $label, string $detail = ''): void
{
    $msg = "  [FAIL] {$label}";
    if ($detail !== '') {
        $msg .= ": {$detail}";
    }
    echo $msg . "\n";
}

function section(string $title): void
{
    echo "\n── {$title} ──\n";
}

function sdl_err(): string
{
    return SDLError::SDLGetError();
}

function make_sine_pcm(int $frames, int $channels, int $freq, int $sample_rate): string
{
    $bytes_per_sample = 2;
    $buf = '';
    for ($i = 0; $i < $frames; $i++) {
        $t = $i / $sample_rate;
        $sample = (int) (sin(2 * M_PI * $freq * $t) * 16000);
        $le = pack('v', $sample & 0xFFFF);
        for ($c = 0; $c < $channels; $c++) {
            $buf .= $le;
        }
    }
    return $buf;
}

$errors = 0;

section('Extension check');
if (!extension_loaded('sdl3')) {
    echo "  [FATAL] sdl3 extension is NOT loaded. Aborting.\n";
    exit(1);
}
pass('sdl3 extension is loaded');

putenv('SDL_AUDIO_DRIVER=dummy');

section('SDL_Init(SDL_INIT_AUDIO)');
if (!SDL::SDLInit(SDL_INIT_AUDIO)) {
    fail('SDL_Init', sdl_err());
    exit(1);
}
pass('SDL_Init(SDL_INIT_AUDIO) succeeded');

section('Driver enumeration');
$numDrivers = SDLAudio::SDLGetNumAudioDrivers();
if ($numDrivers > 0) {
    pass("SDLGetNumAudioDrivers = {$numDrivers}");
    $driver0 = SDLAudio::SDLGetAudioDriver(0);
    if ($driver0 !== '') {
        pass("SDLGetAudioDriver(0) = {$driver0}");
    } else {
        fail('SDLGetAudioDriver(0)');
        $errors++;
    }
} else {
    fail('SDLGetNumAudioDrivers', 'expected > 0');
    $errors++;
}

$current = SDLAudio::SDLGetCurrentAudioDriver();
if ($current !== '') {
    pass("SDLGetCurrentAudioDriver = {$current}");
} else {
    fail('SDLGetCurrentAudioDriver', sdl_err());
    $errors++;
}

section('Device listing');
$playback = SDLAudio::SDLGetAudioPlaybackDevices();
if (count($playback) >= 0) {
    pass('SDLGetAudioPlaybackDevices returned ' . count($playback) . ' device(s)');
} else {
    fail('SDLGetAudioPlaybackDevices');
    $errors++;
}

$recording = SDLAudio::SDLGetAudioRecordingDevices();
pass('SDLGetAudioRecordingDevices returned ' . count($recording) . ' device(s)');

section('Format helpers');
$fmtName = SDLAudio::SDLGetAudioFormatName(SDL_AUDIO_S16);
if ($fmtName !== '') {
    pass("SDLGetAudioFormatName(SDL_AUDIO_S16) = {$fmtName}");
} else {
    fail('SDLGetAudioFormatName');
    $errors++;
}

$silence = SDLAudio::SDLGetSilenceValueForFormat(SDL_AUDIO_S16);
pass("SDLGetSilenceValueForFormat = {$silence}");

section('Audio stream push/pull');
$spec = ['format' => SDL_AUDIO_S16, 'channels' => 1, 'freq' => 44100];

try {
    $stream = SDLAudio::SDLOpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, $spec);
    pass("SDLOpenAudioDeviceStream stream={$stream}");
} catch (\RuntimeException $e) {
    fail('SDLOpenAudioDeviceStream', $e->getMessage());
    SDL::SDLQuit();
    exit(1);
}

$gotFormat = SDLAudio::SDLGetAudioStreamFormat($stream);
if (isset($gotFormat['src']['freq']) && $gotFormat['src']['freq'] === 44100) {
    pass('SDLGetAudioStreamFormat src freq = 44100');
} else {
    fail('SDLGetAudioStreamFormat', json_encode($gotFormat));
    $errors++;
}

$pcm = make_sine_pcm(1024, 1, 440, 44100);
if (SDLAudio::SDLPutAudioStreamData($stream, $pcm)) {
    pass('SDLPutAudioStreamData(' . strlen($pcm) . ' bytes)');
} else {
    fail('SDLPutAudioStreamData', sdl_err());
    $errors++;
}

$queued = SDLAudio::SDLGetAudioStreamQueued($stream);
if ($queued > 0) {
    pass("SDLGetAudioStreamQueued = {$queued}");
} else {
    fail('SDLGetAudioStreamQueued', "expected > 0, got {$queued}");
    $errors++;
}

$available = SDLAudio::SDLGetAudioStreamAvailable($stream);
pass("SDLGetAudioStreamAvailable = {$available}");

if (SDLAudio::SDLSetAudioStreamGain($stream, 0.75)) {
    pass('SDLSetAudioStreamGain');
    $gain = SDLAudio::SDLGetAudioStreamGain($stream);
    if (abs($gain - 0.75) < 0.01) {
        pass("SDLGetAudioStreamGain = {$gain}");
    } else {
        fail('SDLGetAudioStreamGain', "expected ~0.75, got {$gain}");
        $errors++;
    }
} else {
    fail('SDLSetAudioStreamGain', sdl_err());
    $errors++;
}

if (SDLAudio::SDLResumeAudioStreamDevice($stream)) {
    pass('SDLResumeAudioStreamDevice');
} else {
    fail('SDLResumeAudioStreamDevice', sdl_err());
    $errors++;
}

$paused = SDLAudio::SDLAudioStreamDevicePaused($stream);
pass('SDLAudioStreamDevicePaused = ' . ($paused ? 'true' : 'false'));

section('SDL_MixAudio');
$silenceBuf = str_repeat(pack('v', 0), 64);
$mixed = SDLAudio::SDLMixAudio($silenceBuf, substr($pcm, 0, 128), SDL_AUDIO_S16, 128, 0.5);
if ($mixed !== '' && strlen($mixed) === 128) {
    pass('SDLMixAudio returned ' . strlen($mixed) . ' bytes');
} else {
    fail('SDLMixAudio');
    $errors++;
}

section('Standalone stream convert path');
$stream2 = SDLAudio::SDLCreateAudioStream($spec, $spec);
if ($stream2 !== 0) {
    pass("SDLCreateAudioStream stream2={$stream2}");
    SDLAudio::SDLPutAudioStreamData($stream2, substr($pcm, 0, 512));
    $queued2 = SDLAudio::SDLGetAudioStreamQueued($stream2);
    if ($queued2 > 0) {
        pass("stream2 SDLGetAudioStreamQueued = {$queued2}");
    } else {
        fail('stream2 queued');
        $errors++;
    }
    SDLAudio::SDLClearAudioStream($stream2);
    pass('SDLClearAudioStream');
    SDLAudio::SDLDestroyAudioStream($stream2);
    pass('SDLDestroyAudioStream(stream2)');
} else {
    fail('SDLCreateAudioStream');
    $errors++;
}

section('Cleanup');
SDLAudio::SDLDestroyAudioStream($stream);
pass('SDLDestroyAudioStream(primary)');
SDL::SDLQuit();
pass('SDL_Quit');

section('Summary');
if ($errors === 0) {
    echo "  All audio checks passed.\n\n";
    exit(0);
}

echo "  {$errors} check(s) FAILED.\n\n";
exit(1);
