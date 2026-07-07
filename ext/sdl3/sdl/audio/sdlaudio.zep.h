
extern zend_class_entry *sdl3_sdl_audio_sdlaudio_ce;

ZEPHIR_INIT_CLASS(Sdl3_SDL_Audio_SDLAudio);

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetNumAudioDrivers);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDriver);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetCurrentAudioDriver);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioPlaybackDevices);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioRecordingDevices);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDeviceName);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDeviceFormat);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDeviceChannelMap);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLOpenAudioDevice);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLIsAudioDevicePhysical);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLIsAudioDevicePlayback);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLPauseAudioDevice);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLResumeAudioDevice);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLAudioDevicePaused);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDeviceGain);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioDeviceGain);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLCloseAudioDevice);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLBindAudioStreams);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLBindAudioStream);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLUnbindAudioStreams);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLUnbindAudioStream);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamDevice);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLCreateAudioStream);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamProperties);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamFormat);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamFormat);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamFrequencyRatio);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamFrequencyRatio);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamGain);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamGain);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamInputChannelMap);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamOutputChannelMap);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamInputChannelMap);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamOutputChannelMap);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLPutAudioStreamData);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLPutAudioStreamDataNoCopy);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLPutAudioStreamPlanarData);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamData);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamAvailable);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamQueued);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLFlushAudioStream);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLClearAudioStream);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLPauseAudioStreamDevice);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLResumeAudioStreamDevice);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLAudioStreamDevicePaused);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLLockAudioStream);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLUnlockAudioStream);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamGetCallback);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamPutCallback);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLDestroyAudioStream);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLOpenAudioDeviceStream);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioPostmixCallback);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLLoadWAV);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLMixAudio);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLConvertAudioSamples);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioFormatName);
PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetSilenceValueForFormat);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetnumaudiodrivers, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiodriver, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetcurrentaudiodriver, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudioplaybackdevices, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiorecordingdevices, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiodevicename, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiodeviceformat, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiodevicechannelmap, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlopenaudiodevice, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
	ZEND_ARG_INFO(0, spec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlisaudiodevicephysical, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlisaudiodeviceplayback, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlpauseaudiodevice, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlresumeaudiodevice, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlaudiodevicepaused, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiodevicegain, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiodevicegain, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gain, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlcloseaudiodevice, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlbindaudiostreams, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, streams, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlbindaudiostream, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlunbindaudiostreams, 0, 1, IS_VOID, 0)

	ZEND_ARG_ARRAY_INFO(0, streams, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlunbindaudiostream, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamdevice, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlcreateaudiostream, 0, 2, IS_LONG, 0)
	ZEND_ARG_INFO(0, src_spec)
	ZEND_ARG_INFO(0, dst_spec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamproperties, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamformat, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreamformat, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
	ZEND_ARG_INFO(0, src_spec)
	ZEND_ARG_INFO(0, dst_spec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamfrequencyratio, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreamfrequencyratio, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ratio, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamgain, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreamgain, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gain, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreaminputchannelmap, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamoutputchannelmap, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreaminputchannelmap, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, chmap, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreamoutputchannelmap, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, chmap, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlputaudiostreamdata, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlputaudiostreamdatanocopy, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlputaudiostreamplanardata, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, channel_buffers, 0)
	ZEND_ARG_TYPE_INFO(0, num_channels, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, num_samples, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamdata, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, len, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamavailable, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamqueued, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlflushaudiostream, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlclearaudiostream, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlpauseaudiostreamdevice, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlresumeaudiostreamdevice, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlaudiostreamdevicepaused, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdllockaudiostream, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlunlockaudiostream, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreamgetcallback, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreamputcallback, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdldestroyaudiostream, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlopenaudiodevicestream, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
	ZEND_ARG_INFO(0, spec)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiopostmixcallback, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, devid, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlloadwav, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlmixaudio, 0, 5, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, dst, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, len, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, volume, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlconvertaudiosamples, 0, 4, IS_ARRAY, 0)
	ZEND_ARG_INFO(0, src_spec)
	ZEND_ARG_TYPE_INFO(0, src_data, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, src_len, IS_LONG, 0)
	ZEND_ARG_INFO(0, dst_spec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudioformatname, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3_sdl_audio_sdlaudio_sdlgetsilencevalueforformat, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3_sdl_audio_sdlaudio_method_entry) {
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetNumAudioDrivers, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetnumaudiodrivers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDriver, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiodriver, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetCurrentAudioDriver, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetcurrentaudiodriver, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioPlaybackDevices, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudioplaybackdevices, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioRecordingDevices, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiorecordingdevices, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDeviceName, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiodevicename, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDeviceFormat, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiodeviceformat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDeviceChannelMap, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiodevicechannelmap, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLOpenAudioDevice, arginfo_sdl3_sdl_audio_sdlaudio_sdlopenaudiodevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLIsAudioDevicePhysical, arginfo_sdl3_sdl_audio_sdlaudio_sdlisaudiodevicephysical, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLIsAudioDevicePlayback, arginfo_sdl3_sdl_audio_sdlaudio_sdlisaudiodeviceplayback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLPauseAudioDevice, arginfo_sdl3_sdl_audio_sdlaudio_sdlpauseaudiodevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLResumeAudioDevice, arginfo_sdl3_sdl_audio_sdlaudio_sdlresumeaudiodevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLAudioDevicePaused, arginfo_sdl3_sdl_audio_sdlaudio_sdlaudiodevicepaused, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDeviceGain, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiodevicegain, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioDeviceGain, arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiodevicegain, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLCloseAudioDevice, arginfo_sdl3_sdl_audio_sdlaudio_sdlcloseaudiodevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLBindAudioStreams, arginfo_sdl3_sdl_audio_sdlaudio_sdlbindaudiostreams, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLBindAudioStream, arginfo_sdl3_sdl_audio_sdlaudio_sdlbindaudiostream, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLUnbindAudioStreams, arginfo_sdl3_sdl_audio_sdlaudio_sdlunbindaudiostreams, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLUnbindAudioStream, arginfo_sdl3_sdl_audio_sdlaudio_sdlunbindaudiostream, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamDevice, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamdevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLCreateAudioStream, arginfo_sdl3_sdl_audio_sdlaudio_sdlcreateaudiostream, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamProperties, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamproperties, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamFormat, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamformat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamFormat, arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreamformat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamFrequencyRatio, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamfrequencyratio, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamFrequencyRatio, arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreamfrequencyratio, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamGain, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamgain, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamGain, arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreamgain, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamInputChannelMap, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreaminputchannelmap, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamOutputChannelMap, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamoutputchannelmap, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamInputChannelMap, arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreaminputchannelmap, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamOutputChannelMap, arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreamoutputchannelmap, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLPutAudioStreamData, arginfo_sdl3_sdl_audio_sdlaudio_sdlputaudiostreamdata, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLPutAudioStreamDataNoCopy, arginfo_sdl3_sdl_audio_sdlaudio_sdlputaudiostreamdatanocopy, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLPutAudioStreamPlanarData, arginfo_sdl3_sdl_audio_sdlaudio_sdlputaudiostreamplanardata, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamData, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamdata, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamAvailable, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamavailable, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamQueued, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudiostreamqueued, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLFlushAudioStream, arginfo_sdl3_sdl_audio_sdlaudio_sdlflushaudiostream, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLClearAudioStream, arginfo_sdl3_sdl_audio_sdlaudio_sdlclearaudiostream, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLPauseAudioStreamDevice, arginfo_sdl3_sdl_audio_sdlaudio_sdlpauseaudiostreamdevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLResumeAudioStreamDevice, arginfo_sdl3_sdl_audio_sdlaudio_sdlresumeaudiostreamdevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLAudioStreamDevicePaused, arginfo_sdl3_sdl_audio_sdlaudio_sdlaudiostreamdevicepaused, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLLockAudioStream, arginfo_sdl3_sdl_audio_sdlaudio_sdllockaudiostream, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLUnlockAudioStream, arginfo_sdl3_sdl_audio_sdlaudio_sdlunlockaudiostream, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamGetCallback, arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreamgetcallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamPutCallback, arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiostreamputcallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLDestroyAudioStream, arginfo_sdl3_sdl_audio_sdlaudio_sdldestroyaudiostream, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLOpenAudioDeviceStream, arginfo_sdl3_sdl_audio_sdlaudio_sdlopenaudiodevicestream, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioPostmixCallback, arginfo_sdl3_sdl_audio_sdlaudio_sdlsetaudiopostmixcallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLLoadWAV, arginfo_sdl3_sdl_audio_sdlaudio_sdlloadwav, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLMixAudio, arginfo_sdl3_sdl_audio_sdlaudio_sdlmixaudio, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLConvertAudioSamples, arginfo_sdl3_sdl_audio_sdlaudio_sdlconvertaudiosamples, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioFormatName, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetaudioformatname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3_SDL_Audio_SDLAudio, SDLGetSilenceValueForFormat, arginfo_sdl3_sdl_audio_sdlaudio_sdlgetsilencevalueforformat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
