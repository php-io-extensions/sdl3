
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"

#include <SDL3/SDL.h>
#include <stdio.h>

typedef struct _php_sdl_audio_callback_context {
    zval callback;
    zend_long key;
} php_sdl_audio_callback_context;

static HashTable php_sdl_audio_stream_callback_map;
static HashTable php_sdl_audio_postmix_callback_map;
static HashTable php_sdl_audio_nocopy_callback_map;
static bool php_sdl_audio_callback_maps_initialized = false;

static void php_sdl_audio_callback_maps_ensure(void)
{
    if (!php_sdl_audio_callback_maps_initialized) {
        zend_hash_init(&php_sdl_audio_stream_callback_map, 8, NULL, ZVAL_PTR_DTOR, 0);
        zend_hash_init(&php_sdl_audio_postmix_callback_map, 8, NULL, ZVAL_PTR_DTOR, 0);
        zend_hash_init(&php_sdl_audio_nocopy_callback_map, 8, NULL, ZVAL_PTR_DTOR, 0);
        php_sdl_audio_callback_maps_initialized = true;
    }
}

static php_sdl_audio_callback_context *php_sdl_audio_callback_context_alloc(zval *callback, zend_long key)
{
    php_sdl_audio_callback_context *ctx = emalloc(sizeof(php_sdl_audio_callback_context));
    ZVAL_UNDEF(&ctx->callback);
    ZVAL_COPY(&ctx->callback, callback);
    ctx->key = key;
    return ctx;
}

static void php_sdl_audio_callback_context_free(php_sdl_audio_callback_context *ctx)
{
    if (!ctx) {
        return;
    }
    zval_ptr_dtor(&ctx->callback);
    efree(ctx);
}

static SDL_AudioStream *php_sdl_audio_stream_from_handle(zend_long handle)
{
    return (SDL_AudioStream *)(uintptr_t) handle;
}

static zval *php_sdl_audio_assoc_zval(zval *arr, const char *key, size_t key_len)
{
    if (Z_TYPE_P(arr) != IS_ARRAY) {
        return NULL;
    }
    return zend_hash_str_find(Z_ARRVAL_P(arr), key, key_len);
}

static bool php_sdl_audio_spec_from_array(zval *arr, SDL_AudioSpec *spec)
{
    zval *entry;

    if (Z_TYPE_P(arr) != IS_ARRAY) {
        return false;
    }

    entry = php_sdl_audio_assoc_zval(arr, "format", sizeof("format") - 1);
    spec->format = entry ? (SDL_AudioFormat) zval_get_long(entry) : SDL_AUDIO_UNKNOWN;
    entry = php_sdl_audio_assoc_zval(arr, "channels", sizeof("channels") - 1);
    spec->channels = entry ? (int) zval_get_long(entry) : 0;
    entry = php_sdl_audio_assoc_zval(arr, "freq", sizeof("freq") - 1);
    spec->freq = entry ? (int) zval_get_long(entry) : 0;

    return true;
}

static void php_sdl_audio_spec_to_array(const SDL_AudioSpec *spec, zval *out)
{
    array_init(out);
    add_assoc_long(out, "format", (zend_long) spec->format);
    add_assoc_long(out, "channels", (zend_long) spec->channels);
    add_assoc_long(out, "freq", (zend_long) spec->freq);
}

static int *php_sdl_audio_int_array_from_php(zval *arr, int *count_out)
{
    int count;
    int *values;
    int i = 0;
    zval *item;

    *count_out = 0;
    if (Z_TYPE_P(arr) != IS_ARRAY) {
        return NULL;
    }

    count = (int) zend_hash_num_elements(Z_ARRVAL_P(arr));
    if (count <= 0) {
        return NULL;
    }

    values = ecalloc((size_t) count, sizeof(int));
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(arr), item) {
        if (i < count) {
            values[i++] = (int) zval_get_long(item);
        }
    } ZEND_HASH_FOREACH_END();

    *count_out = count;
    return values;
}

static SDL_AudioStream **php_sdl_audio_streams_from_array(zval *arr, int *count_out)
{
    int count;
    SDL_AudioStream **streams;
    int i = 0;
    zval *item;

    *count_out = 0;
    if (Z_TYPE_P(arr) != IS_ARRAY) {
        return NULL;
    }

    count = (int) zend_hash_num_elements(Z_ARRVAL_P(arr));
    if (count <= 0) {
        return NULL;
    }

    streams = ecalloc((size_t) count, sizeof(SDL_AudioStream *));
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(arr), item) {
        if (i < count) {
            streams[i++] = php_sdl_audio_stream_from_handle(zval_get_long(item));
        }
    } ZEND_HASH_FOREACH_END();

    *count_out = count;
    return streams;
}

static void SDLCALL php_sdl_audio_stream_callback_bridge(void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount)
{
    php_sdl_audio_callback_context *ctx = (php_sdl_audio_callback_context *) userdata;
    zval retval;
    zval params[3];

    if (ctx == NULL) {
        return;
    }

    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) stream);
    ZVAL_LONG(&params[1], (zend_long) additional_amount);
    ZVAL_LONG(&params[2], (zend_long) total_amount);
    ZVAL_UNDEF(&retval);

    call_user_function(EG(function_table), NULL, &ctx->callback, &retval, 3, params);

    if (!Z_ISUNDEF(retval)) {
        zval_ptr_dtor(&retval);
    }
}

static void SDLCALL php_sdl_audio_postmix_callback_bridge(void *userdata, const SDL_AudioSpec *spec, float *buffer, int buflen)
{
    php_sdl_audio_callback_context *ctx = (php_sdl_audio_callback_context *) userdata;
    zval retval;
    zval params[2];
    zval spec_arr;

    if (ctx == NULL || spec == NULL || buffer == NULL || buflen <= 0) {
        return;
    }

    php_sdl_audio_spec_to_array(spec, &spec_arr);
    ZVAL_COPY(&params[0], &spec_arr);
    ZVAL_STRINGL(&params[1], (char *) buffer, (size_t) buflen);
    ZVAL_UNDEF(&retval);

    if (call_user_function(EG(function_table), NULL, &ctx->callback, &retval, 2, params) == SUCCESS) {
        if (Z_TYPE(retval) == IS_STRING && (int) Z_STRLEN(retval) == buflen) {
            memcpy(buffer, Z_STRVAL(retval), (size_t) buflen);
        }
    }

    if (!Z_ISUNDEF(retval)) {
        zval_ptr_dtor(&retval);
    }
    zval_ptr_dtor(&params[0]);
    zval_ptr_dtor(&params[1]);
    zval_ptr_dtor(&spec_arr);
}

static void SDLCALL php_sdl_audio_nocopy_complete_bridge(void *userdata, const void *buf, int buflen)
{
    php_sdl_audio_callback_context *ctx = (php_sdl_audio_callback_context *) userdata;
    zval retval;
    zval params[2];

    if (ctx == NULL) {
        return;
    }

    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) buf);
    ZVAL_LONG(&params[1], (zend_long) buflen);
    ZVAL_UNDEF(&retval);

    call_user_function(EG(function_table), NULL, &ctx->callback, &retval, 2, params);

    if (!Z_ISUNDEF(retval)) {
        zval_ptr_dtor(&retval);
    }
}

static void php_sdl_audio_store_stream_callback(zend_long stream_ptr, php_sdl_audio_callback_context *ctx)
{
    zval zv;
    zval *old;

    php_sdl_audio_callback_maps_ensure();
    old = zend_hash_index_find(&php_sdl_audio_stream_callback_map, (zend_ulong) stream_ptr);
    if (old != NULL) {
        php_sdl_audio_callback_context_free((php_sdl_audio_callback_context *) Z_PTR_P(old));
        zend_hash_index_del(&php_sdl_audio_stream_callback_map, (zend_ulong) stream_ptr);
    }
    ZVAL_PTR(&zv, ctx);
    zend_hash_index_update(&php_sdl_audio_stream_callback_map, (zend_ulong) stream_ptr, &zv);
}

static void php_sdl_audio_clear_stream_callback(zend_long stream_ptr)
{
    zval *zv;

    if (!php_sdl_audio_callback_maps_initialized) {
        return;
    }
    zv = zend_hash_index_find(&php_sdl_audio_stream_callback_map, (zend_ulong) stream_ptr);
    if (zv != NULL) {
        php_sdl_audio_callback_context_free((php_sdl_audio_callback_context *) Z_PTR_P(zv));
        zend_hash_index_del(&php_sdl_audio_stream_callback_map, (zend_ulong) stream_ptr);
    }
}



/**
 * SDL audio subsystem — devices, streams, push/pull binary I/O, and optional callbacks.
 */
ZEPHIR_INIT_CLASS(Sdl3_SDL_Audio_SDLAudio)
{
	ZEPHIR_REGISTER_CLASS(Sdl3\\SDL\\Audio, SDLAudio, sdl3, sdl_audio_sdlaudio, sdl3_sdl_audio_sdlaudio_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetNumAudioDrivers)
{
	zend_long result = 0;
	
            result = (zend_long) SDL_GetNumAudioDrivers();
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDriver)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *index_param = NULL;
	zend_long index;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &index_param);
	ZEPHIR_INIT_VAR(&result);
	
            const char *name = SDL_GetAudioDriver((int) index);
            if (name) {
                ZVAL_STRING(&result, name);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetCurrentAudioDriver)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&result);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&result);
	
            const char *name = SDL_GetCurrentAudioDriver();
            if (name) {
                ZVAL_STRING(&result, name);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioPlaybackDevices)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            int count = 0;
            SDL_AudioDeviceID *ids = SDL_GetAudioPlaybackDevices(&count);

            array_init(&result);
            if (ids != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) ids[i]);
                }
                SDL_free(ids);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioRecordingDevices)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            int count = 0;
            SDL_AudioDeviceID *ids = SDL_GetAudioRecordingDevices(&count);

            array_init(&result);
            if (ids != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) ids[i]);
                }
                SDL_free(ids);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDeviceName)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *devid_param = NULL;
	zend_long devid;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(devid)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &devid_param);
	ZEPHIR_INIT_VAR(&result);
	
            const char *name = SDL_GetAudioDeviceName((SDL_AudioDeviceID) devid);
            if (name) {
                ZVAL_STRING(&result, name);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDeviceFormat)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *devid_param = NULL;
	zend_long devid;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(devid)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &devid_param);
	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	
            SDL_AudioSpec spec;
            int sample_frames = 0;

            if (SDL_GetAudioDeviceFormat((SDL_AudioDeviceID) devid, &spec, &sample_frames)) {
                php_sdl_audio_spec_to_array(&spec, &result);
                add_assoc_long(&result, "sample_frames", (zend_long) sample_frames);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDeviceChannelMap)
{
	zval result;
	zval *devid_param = NULL;
	zend_long devid;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(devid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &devid_param);
	
            int count = 0;
            int *map = SDL_GetAudioDeviceChannelMap((SDL_AudioDeviceID) devid, &count);

            array_init(&result);
            if (map != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) map[i]);
                }
                SDL_free(map);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLOpenAudioDevice)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *devid_param = NULL, *spec = NULL, spec_sub, __$null, _0$$3, _1$$3, _2$$3;
	zend_long devid, ZEPHIR_LAST_CALL_STATUS, device = 0;

	ZVAL_UNDEF(&spec_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(devid)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(spec)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &devid_param, &spec);
	if (!spec) {
		spec = &spec_sub;
		spec = &__$null;
	}
	
            SDL_AudioSpec audio_spec;
            const SDL_AudioSpec *spec_ptr = NULL;

            if (Z_TYPE_P(&spec) != IS_NULL) {
                if (!php_sdl_audio_spec_from_array(&spec, &audio_spec)) {
                    zend_throw_exception(zend_ce_exception, "Invalid audio spec array", 0);
                    RETURN_MM();
                }
                spec_ptr = &audio_spec;
            }

            device = (zend_long) SDL_OpenAudioDevice((SDL_AudioDeviceID) devid, spec_ptr);
        
	if (device == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_OpenAudioDevice failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/audio/sdlaudio.zep", 397);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(device);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLIsAudioDevicePhysical)
{
	zend_bool result = 0;
	zval *devid_param = NULL;
	zend_long devid;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(devid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &devid_param);
	
            result = SDL_IsAudioDevicePhysical((SDL_AudioDeviceID) devid);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLIsAudioDevicePlayback)
{
	zend_bool result = 0;
	zval *devid_param = NULL;
	zend_long devid;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(devid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &devid_param);
	
            result = SDL_IsAudioDevicePlayback((SDL_AudioDeviceID) devid);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLPauseAudioDevice)
{
	zend_bool result = 0;
	zval *devid_param = NULL;
	zend_long devid;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(devid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &devid_param);
	
            result = SDL_PauseAudioDevice((SDL_AudioDeviceID) devid);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLResumeAudioDevice)
{
	zend_bool result = 0;
	zval *devid_param = NULL;
	zend_long devid;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(devid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &devid_param);
	
            result = SDL_ResumeAudioDevice((SDL_AudioDeviceID) devid);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLAudioDevicePaused)
{
	zend_bool result = 0;
	zval *devid_param = NULL;
	zend_long devid;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(devid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &devid_param);
	
            result = SDL_AudioDevicePaused((SDL_AudioDeviceID) devid);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioDeviceGain)
{
	double result = 0;
	zval *devid_param = NULL;
	zend_long devid;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(devid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &devid_param);
	
            result = (double) SDL_GetAudioDeviceGain((SDL_AudioDeviceID) devid);
        
	RETURN_DOUBLE(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioDeviceGain)
{
	zend_bool result = 0;
	double gain;
	zval *devid_param = NULL, *gain_param = NULL;
	zend_long devid;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(devid)
		Z_PARAM_ZVAL(gain)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &devid_param, &gain_param);
	gain = zephir_get_doubleval(gain_param);
	
            result = SDL_SetAudioDeviceGain((SDL_AudioDeviceID) devid, (float) gain);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLCloseAudioDevice)
{
	zval *devid_param = NULL;
	zend_long devid;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(devid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &devid_param);
	
            php_sdl_audio_callback_maps_ensure();
            zval *zv = zend_hash_index_find(&php_sdl_audio_postmix_callback_map, (zend_ulong) devid);
            if (zv != NULL) {
                php_sdl_audio_callback_context_free((php_sdl_audio_callback_context *) Z_PTR_P(zv));
                zend_hash_index_del(&php_sdl_audio_postmix_callback_map, (zend_ulong) devid);
            }
            SDL_CloseAudioDevice((SDL_AudioDeviceID) devid);
        
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLBindAudioStreams)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval streams;
	zval *devid_param = NULL, *streams_param = NULL, s;
	zend_long devid;

	ZVAL_UNDEF(&s);
	ZVAL_UNDEF(&streams);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(devid)
		Z_PARAM_ARRAY(streams)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &devid_param, &streams_param);
	zephir_get_arrval(&streams, streams_param);
	ZEPHIR_CPY_WRT(&s, &streams);
	
            int count = 0;
            SDL_AudioStream **stream_ptrs = php_sdl_audio_streams_from_array(&s, &count);

            result = SDL_BindAudioStreams((SDL_AudioDeviceID) devid, stream_ptrs, count);
            if (stream_ptrs) {
                efree(stream_ptrs);
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLBindAudioStream)
{
	zend_bool result = 0;
	zval *devid_param = NULL, *stream_param = NULL;
	zend_long devid, stream;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(devid)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &devid_param, &stream_param);
	
            SDL_AudioStream *s = php_sdl_audio_stream_from_handle(stream);
            result = SDL_BindAudioStream((SDL_AudioDeviceID) devid, s);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLUnbindAudioStreams)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *streams_param = NULL, s;
	zval streams;

	ZVAL_UNDEF(&streams);
	ZVAL_UNDEF(&s);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ARRAY(streams)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &streams_param);
	zephir_get_arrval(&streams, streams_param);
	ZEPHIR_CPY_WRT(&s, &streams);
	
            int count = 0;
            SDL_AudioStream **stream_ptrs = php_sdl_audio_streams_from_array(&s, &count);

            if (stream_ptrs) {
                SDL_UnbindAudioStreams(stream_ptrs, count);
                efree(stream_ptrs);
            }
        
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLUnbindAudioStream)
{
	zval *stream_param = NULL;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            SDL_UnbindAudioStream(php_sdl_audio_stream_from_handle(stream));
        
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamDevice)
{
	zval *stream_param = NULL;
	zend_long stream, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            result = (zend_long) SDL_GetAudioStreamDevice(php_sdl_audio_stream_from_handle(stream));
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLCreateAudioStream)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, stream_ptr = 0;
	zval *src_spec, src_spec_sub, *dst_spec, dst_spec_sub, src, dst, _0$$3, _1$$3, _2$$3;

	ZVAL_UNDEF(&src_spec_sub);
	ZVAL_UNDEF(&dst_spec_sub);
	ZVAL_UNDEF(&src);
	ZVAL_UNDEF(&dst);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(src_spec)
		Z_PARAM_ZVAL(dst_spec)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &src_spec, &dst_spec);
	ZEPHIR_CPY_WRT(&src, src_spec);
	ZEPHIR_CPY_WRT(&dst, dst_spec);
	
            SDL_AudioSpec src_audio;
            SDL_AudioSpec dst_audio;

            if (!php_sdl_audio_spec_from_array(&src, &src_audio) || !php_sdl_audio_spec_from_array(&dst, &dst_audio)) {
                zend_throw_exception(zend_ce_exception, "Invalid audio spec array", 0);
                RETURN_MM();
            }

            SDL_AudioStream *stream = SDL_CreateAudioStream(&src_audio, &dst_audio);
            stream_ptr = (zend_long)(uintptr_t) stream;
        
	if (stream_ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_CreateAudioStream failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/audio/sdlaudio.zep", 583);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(stream_ptr);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamProperties)
{
	zval *stream_param = NULL;
	zend_long stream, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            result = (zend_long) SDL_GetAudioStreamProperties(php_sdl_audio_stream_from_handle(stream));
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamFormat)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *stream_param = NULL;
	zend_long stream;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &stream_param);
	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	
            SDL_AudioSpec src_spec;
            SDL_AudioSpec dst_spec;
            zval src_arr;
            zval dst_arr;

            if (SDL_GetAudioStreamFormat(php_sdl_audio_stream_from_handle(stream), &src_spec, &dst_spec)) {
                php_sdl_audio_spec_to_array(&src_spec, &src_arr);
                php_sdl_audio_spec_to_array(&dst_spec, &dst_arr);
                array_init(&result);
                add_assoc_zval(&result, "src", &src_arr);
                add_assoc_zval(&result, "dst", &dst_arr);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamFormat)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *stream_param = NULL, *src_spec, src_spec_sub, *dst_spec, dst_spec_sub, src, dst;
	zend_long stream;

	ZVAL_UNDEF(&src_spec_sub);
	ZVAL_UNDEF(&dst_spec_sub);
	ZVAL_UNDEF(&src);
	ZVAL_UNDEF(&dst);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(stream)
		Z_PARAM_ZVAL(src_spec)
		Z_PARAM_ZVAL(dst_spec)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &stream_param, &src_spec, &dst_spec);
	ZEPHIR_CPY_WRT(&src, src_spec);
	ZEPHIR_CPY_WRT(&dst, dst_spec);
	
            SDL_AudioSpec src_audio;
            SDL_AudioSpec dst_audio;

            if (!php_sdl_audio_spec_from_array(&src, &src_audio) || !php_sdl_audio_spec_from_array(&dst, &dst_audio)) {
                zend_throw_exception(zend_ce_exception, "Invalid audio spec array", 0);
                RETURN_MM();
            }

            result = SDL_SetAudioStreamFormat(php_sdl_audio_stream_from_handle(stream), &src_audio, &dst_audio);
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamFrequencyRatio)
{
	double result = 0;
	zval *stream_param = NULL;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            result = (double) SDL_GetAudioStreamFrequencyRatio(php_sdl_audio_stream_from_handle(stream));
        
	RETURN_DOUBLE(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamFrequencyRatio)
{
	zend_bool result = 0;
	double ratio;
	zval *stream_param = NULL, *ratio_param = NULL;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(stream)
		Z_PARAM_ZVAL(ratio)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &stream_param, &ratio_param);
	ratio = zephir_get_doubleval(ratio_param);
	
            result = SDL_SetAudioStreamFrequencyRatio(php_sdl_audio_stream_from_handle(stream), (float) ratio);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamGain)
{
	double result = 0;
	zval *stream_param = NULL;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            result = (double) SDL_GetAudioStreamGain(php_sdl_audio_stream_from_handle(stream));
        
	RETURN_DOUBLE(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamGain)
{
	zend_bool result = 0;
	double gain;
	zval *stream_param = NULL, *gain_param = NULL;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(stream)
		Z_PARAM_ZVAL(gain)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &stream_param, &gain_param);
	gain = zephir_get_doubleval(gain_param);
	
            result = SDL_SetAudioStreamGain(php_sdl_audio_stream_from_handle(stream), (float) gain);
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamInputChannelMap)
{
	zval result;
	zval *stream_param = NULL;
	zend_long stream;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            int count = 0;
            int *map = SDL_GetAudioStreamInputChannelMap(php_sdl_audio_stream_from_handle(stream), &count);

            array_init(&result);
            if (map != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) map[i]);
                }
                SDL_free(map);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamOutputChannelMap)
{
	zval result;
	zval *stream_param = NULL;
	zend_long stream;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            int count = 0;
            int *map = SDL_GetAudioStreamOutputChannelMap(php_sdl_audio_stream_from_handle(stream), &count);

            array_init(&result);
            if (map != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) map[i]);
                }
                SDL_free(map);
            }
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamInputChannelMap)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval chmap;
	zval *stream_param = NULL, *chmap_param = NULL, map;
	zend_long stream;

	ZVAL_UNDEF(&map);
	ZVAL_UNDEF(&chmap);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(stream)
		Z_PARAM_ARRAY(chmap)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &stream_param, &chmap_param);
	zephir_get_arrval(&chmap, chmap_param);
	ZEPHIR_CPY_WRT(&map, &chmap);
	
            int count = 0;
            int *values = php_sdl_audio_int_array_from_php(&map, &count);

            result = SDL_SetAudioStreamInputChannelMap(php_sdl_audio_stream_from_handle(stream), values, count);
            if (values) {
                efree(values);
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamOutputChannelMap)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval chmap;
	zval *stream_param = NULL, *chmap_param = NULL, map;
	zend_long stream;

	ZVAL_UNDEF(&map);
	ZVAL_UNDEF(&chmap);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(stream)
		Z_PARAM_ARRAY(chmap)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &stream_param, &chmap_param);
	zephir_get_arrval(&chmap, chmap_param);
	ZEPHIR_CPY_WRT(&map, &chmap);
	
            int count = 0;
            int *values = php_sdl_audio_int_array_from_php(&map, &count);

            result = SDL_SetAudioStreamOutputChannelMap(php_sdl_audio_stream_from_handle(stream), values, count);
            if (values) {
                efree(values);
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLPutAudioStreamData)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval data;
	zval *stream_param = NULL, *data_param = NULL;
	zend_long stream;

	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(stream)
		Z_PARAM_STR(data)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &stream_param, &data_param);
	zephir_get_strval(&data, data_param);
	
            result = SDL_PutAudioStreamData(
                php_sdl_audio_stream_from_handle(stream),
                (const void *) Z_STRVAL(data),
                (int) Z_STRLEN(data)
            );
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLPutAudioStreamDataNoCopy)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval data;
	zval *stream_param = NULL, *data_param = NULL, *callback = NULL, callback_sub, __$null, cb;
	zend_long stream;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&cb);
	ZVAL_UNDEF(&data);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(stream)
		Z_PARAM_STR(data)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &stream_param, &data_param, &callback);
	zephir_get_strval(&data, data_param);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	ZEPHIR_CPY_WRT(&cb, callback);
	
            SDL_AudioStream *s = php_sdl_audio_stream_from_handle(stream);
            SDL_AudioStreamDataCompleteCallback complete_cb = NULL;
            php_sdl_audio_callback_context *ctx = NULL;

            if (Z_TYPE_P(&cb) != IS_NULL) {
                ctx = php_sdl_audio_callback_context_alloc(&cb, stream);
                complete_cb = php_sdl_audio_nocopy_complete_bridge;
            }

            result = SDL_PutAudioStreamDataNoCopy(
                s,
                (const void *) Z_STRVAL(data),
                (int) Z_STRLEN(data),
                complete_cb,
                ctx
            );

            if (!result && ctx != NULL) {
                php_sdl_audio_callback_context_free(ctx);
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLPutAudioStreamPlanarData)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval channel_buffers;
	zval *stream_param = NULL, *channel_buffers_param = NULL, *num_channels_param = NULL, *num_samples_param = NULL, buffers;
	zend_long stream, num_channels, num_samples;

	ZVAL_UNDEF(&buffers);
	ZVAL_UNDEF(&channel_buffers);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(stream)
		Z_PARAM_ARRAY(channel_buffers)
		Z_PARAM_LONG(num_channels)
		Z_PARAM_LONG(num_samples)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &stream_param, &channel_buffers_param, &num_channels_param, &num_samples_param);
	zephir_get_arrval(&channel_buffers, channel_buffers_param);
	ZEPHIR_CPY_WRT(&buffers, &channel_buffers);
	
            int count = 0;
            const void **bufs = NULL;
            zval *item;
            int i = 0;

            if (Z_TYPE_P(&buffers) == IS_ARRAY) {
                count = (int) zend_hash_num_elements(Z_ARRVAL_P(&buffers));
                if (count > 0) {
                    bufs = ecalloc((size_t) count, sizeof(const void *));
                    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&buffers), item) {
                        if (i < count) {
                            if (Z_TYPE_P(item) == IS_STRING) {
                                bufs[i++] = (const void *) Z_STRVAL_P(item);
                            } else {
                                bufs[i++] = NULL;
                            }
                        }
                    } ZEND_HASH_FOREACH_END();
                }
            }

            result = SDL_PutAudioStreamPlanarData(
                php_sdl_audio_stream_from_handle(stream),
                bufs,
                (int) num_channels,
                (int) num_samples
            );
            if (bufs) {
                efree(bufs);
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamData)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *stream_param = NULL, *len_param = NULL;
	zend_long stream, len;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(stream)
		Z_PARAM_LONG(len)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &stream_param, &len_param);
	ZEPHIR_INIT_VAR(&result);
	
            void *buf = emalloc((size_t) len);
            int got = SDL_GetAudioStreamData(php_sdl_audio_stream_from_handle(stream), buf, (int) len);

            if (got > 0) {
                ZVAL_STRINGL(&result, (char *) buf, (size_t) got);
            }
            efree(buf);
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamAvailable)
{
	zval *stream_param = NULL;
	zend_long stream, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            result = (zend_long) SDL_GetAudioStreamAvailable(php_sdl_audio_stream_from_handle(stream));
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioStreamQueued)
{
	zval *stream_param = NULL;
	zend_long stream, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            result = (zend_long) SDL_GetAudioStreamQueued(php_sdl_audio_stream_from_handle(stream));
        
	RETURN_LONG(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLFlushAudioStream)
{
	zend_bool result = 0;
	zval *stream_param = NULL;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            result = SDL_FlushAudioStream(php_sdl_audio_stream_from_handle(stream));
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLClearAudioStream)
{
	zend_bool result = 0;
	zval *stream_param = NULL;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            result = SDL_ClearAudioStream(php_sdl_audio_stream_from_handle(stream));
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLPauseAudioStreamDevice)
{
	zend_bool result = 0;
	zval *stream_param = NULL;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            result = SDL_PauseAudioStreamDevice(php_sdl_audio_stream_from_handle(stream));
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLResumeAudioStreamDevice)
{
	zend_bool result = 0;
	zval *stream_param = NULL;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            result = SDL_ResumeAudioStreamDevice(php_sdl_audio_stream_from_handle(stream));
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLAudioStreamDevicePaused)
{
	zend_bool result = 0;
	zval *stream_param = NULL;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            result = SDL_AudioStreamDevicePaused(php_sdl_audio_stream_from_handle(stream));
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLLockAudioStream)
{
	zend_bool result = 0;
	zval *stream_param = NULL;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            result = SDL_LockAudioStream(php_sdl_audio_stream_from_handle(stream));
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLUnlockAudioStream)
{
	zend_bool result = 0;
	zval *stream_param = NULL;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            result = SDL_UnlockAudioStream(php_sdl_audio_stream_from_handle(stream));
        
	RETURN_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamGetCallback)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *stream_param = NULL, *callback = NULL, callback_sub, __$null, cb;
	zend_long stream;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&cb);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(stream)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &stream_param, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	ZEPHIR_CPY_WRT(&cb, callback);
	
            zend_long stream_ptr = (zend_long) stream;
            SDL_AudioStream *s = php_sdl_audio_stream_from_handle(stream_ptr);
            SDL_AudioStreamCallback stream_cb = NULL;
            php_sdl_audio_callback_context *ctx = NULL;

            php_sdl_audio_clear_stream_callback(stream_ptr);

            if (Z_TYPE_P(&cb) != IS_NULL) {
                ctx = php_sdl_audio_callback_context_alloc(&cb, stream_ptr);
                stream_cb = php_sdl_audio_stream_callback_bridge;
            }

            result = SDL_SetAudioStreamGetCallback(s, stream_cb, ctx);

            if (result && ctx != NULL) {
                php_sdl_audio_store_stream_callback(stream_ptr, ctx);
            } else if (ctx != NULL) {
                php_sdl_audio_callback_context_free(ctx);
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioStreamPutCallback)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *stream_param = NULL, *callback = NULL, callback_sub, __$null, cb;
	zend_long stream;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&cb);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(stream)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &stream_param, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	ZEPHIR_CPY_WRT(&cb, callback);
	
            zend_long stream_ptr = (zend_long) stream;
            SDL_AudioStream *s = php_sdl_audio_stream_from_handle(stream_ptr);
            SDL_AudioStreamCallback stream_cb = NULL;
            php_sdl_audio_callback_context *ctx = NULL;

            php_sdl_audio_clear_stream_callback(stream_ptr);

            if (Z_TYPE_P(&cb) != IS_NULL) {
                ctx = php_sdl_audio_callback_context_alloc(&cb, stream_ptr);
                stream_cb = php_sdl_audio_stream_callback_bridge;
            }

            result = SDL_SetAudioStreamPutCallback(s, stream_cb, ctx);

            if (result && ctx != NULL) {
                php_sdl_audio_store_stream_callback(stream_ptr, ctx);
            } else if (ctx != NULL) {
                php_sdl_audio_callback_context_free(ctx);
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLDestroyAudioStream)
{
	zval *stream_param = NULL;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &stream_param);
	
            zend_long stream_ptr = (zend_long) stream;
            php_sdl_audio_clear_stream_callback(stream_ptr);
            SDL_DestroyAudioStream(php_sdl_audio_stream_from_handle(stream_ptr));
        
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLOpenAudioDeviceStream)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *devid_param = NULL, *spec = NULL, spec_sub, *callback = NULL, callback_sub, __$null, sp, cb, _0$$3, _1$$3, _2$$3;
	zend_long devid, ZEPHIR_LAST_CALL_STATUS, stream_ptr = 0;

	ZVAL_UNDEF(&spec_sub);
	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&sp);
	ZVAL_UNDEF(&cb);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_LONG(devid)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(spec)
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &devid_param, &spec, &callback);
	if (!spec) {
		spec = &spec_sub;
		spec = &__$null;
	}
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	ZEPHIR_CPY_WRT(&sp, spec);
	ZEPHIR_CPY_WRT(&cb, callback);
	
            SDL_AudioSpec audio_spec;
            const SDL_AudioSpec *spec_ptr = NULL;
            SDL_AudioStreamCallback stream_cb = NULL;
            php_sdl_audio_callback_context *ctx = NULL;

            if (Z_TYPE_P(&sp) != IS_NULL) {
                if (!php_sdl_audio_spec_from_array(&sp, &audio_spec)) {
                    zend_throw_exception(zend_ce_exception, "Invalid audio spec array", 0);
                    RETURN_MM();
                }
                spec_ptr = &audio_spec;
            }

            if (Z_TYPE_P(&cb) != IS_NULL) {
                ctx = php_sdl_audio_callback_context_alloc(&cb, 0);
                stream_cb = php_sdl_audio_stream_callback_bridge;
            }

            SDL_AudioStream *stream = SDL_OpenAudioDeviceStream(
                (SDL_AudioDeviceID) devid,
                spec_ptr,
                stream_cb,
                ctx
            );
            stream_ptr = (zend_long)(uintptr_t) stream;

            if (stream_ptr != 0 && ctx != NULL) {
                php_sdl_audio_store_stream_callback(stream_ptr, ctx);
            } else if (ctx != NULL) {
                php_sdl_audio_callback_context_free(ctx);
            }
        
	if (stream_ptr == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_OpenAudioDeviceStream failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/audio/sdlaudio.zep", 1094);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(stream_ptr);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLSetAudioPostmixCallback)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *devid_param = NULL, *callback = NULL, callback_sub, __$null, cb;
	zend_long devid;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&cb);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(devid)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &devid_param, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	ZEPHIR_CPY_WRT(&cb, callback);
	
            SDL_AudioPostmixCallback postmix_cb = NULL;
            php_sdl_audio_callback_context *ctx = NULL;
            zval *zv;

            php_sdl_audio_callback_maps_ensure();
            zv = zend_hash_index_find(&php_sdl_audio_postmix_callback_map, (zend_ulong) devid);
            if (zv != NULL) {
                php_sdl_audio_callback_context_free((php_sdl_audio_callback_context *) Z_PTR_P(zv));
                zend_hash_index_del(&php_sdl_audio_postmix_callback_map, (zend_ulong) devid);
            }

            if (Z_TYPE_P(&cb) != IS_NULL) {
                ctx = php_sdl_audio_callback_context_alloc(&cb, devid);
                postmix_cb = php_sdl_audio_postmix_callback_bridge;
            }

            result = SDL_SetAudioPostmixCallback((SDL_AudioDeviceID) devid, postmix_cb, ctx);

            if (result && ctx != NULL) {
                zval zstore;
                ZVAL_PTR(&zstore, ctx);
                zend_hash_index_update(&php_sdl_audio_postmix_callback_map, (zend_ulong) devid, &zstore);
            } else if (ctx != NULL) {
                php_sdl_audio_callback_context_free(ctx);
            }
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLLoadWAV)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *path_param = NULL, _0$$3, _1$$3, _2$$3;
	zval path;

	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &path_param);
	zephir_get_strval(&path, path_param);
	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	
            SDL_AudioSpec spec;
            Uint8 *audio_buf = NULL;
            Uint32 audio_len = 0;

            if (SDL_LoadWAV(Z_STRVAL(path), &spec, &audio_buf, &audio_len)) {
                zval spec_arr;
                php_sdl_audio_spec_to_array(&spec, &spec_arr);
                array_init(&result);
                add_assoc_zval(&result, "spec", &spec_arr);
                if (audio_buf != NULL && audio_len > 0) {
                    add_assoc_stringl(&result, "data", (char *) audio_buf, (size_t) audio_len);
                    SDL_free(audio_buf);
                } else {
                    add_assoc_string(&result, "data", "");
                }
                add_assoc_long(&result, "len", (zend_long) audio_len);
            }
        
	if (ZEPHIR_IS_EMPTY(&result)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, sdl3_sdl_sdlerror_ce, "sdlgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "SDL_LoadWAV failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "sdl3/sdl/audio/sdlaudio.zep", 1163);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLMixAudio)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	double volume;
	zend_long format, len;
	zval *dst_param = NULL, *src_param = NULL, *format_param = NULL, *len_param = NULL, *volume_param = NULL;
	zval dst, src, result;

	ZVAL_UNDEF(&dst);
	ZVAL_UNDEF(&src);
	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_STR(dst)
		Z_PARAM_STR(src)
		Z_PARAM_LONG(format)
		Z_PARAM_LONG(len)
		Z_PARAM_ZVAL(volume)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 5, 0, &dst_param, &src_param, &format_param, &len_param, &volume_param);
	zephir_get_strval(&dst, dst_param);
	zephir_get_strval(&src, src_param);
	volume = zephir_get_doubleval(volume_param);
	ZEPHIR_INIT_VAR(&result);
	
            size_t dst_len = Z_STRLEN(dst);
            size_t src_len = Z_STRLEN(src);
            size_t mix_len = (size_t) len;

            if (mix_len > dst_len) {
                mix_len = dst_len;
            }
            if (mix_len > src_len) {
                mix_len = src_len;
            }

            char *buf = emalloc(mix_len);
            memcpy(buf, Z_STRVAL(dst), mix_len);

            if (SDL_MixAudio(
                (Uint8 *) buf,
                (const Uint8 *) Z_STRVAL(src),
                (SDL_AudioFormat) format,
                (Uint32) mix_len,
                (float) volume
            )) {
                ZVAL_STRINGL(&result, buf, mix_len);
            }
            efree(buf);
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLConvertAudioSamples)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long src_len;
	zval src_data;
	zval *src_spec, src_spec_sub, *src_data_param = NULL, *src_len_param = NULL, *dst_spec, dst_spec_sub, src, dst;

	ZVAL_UNDEF(&src_spec_sub);
	ZVAL_UNDEF(&dst_spec_sub);
	ZVAL_UNDEF(&src);
	ZVAL_UNDEF(&dst);
	ZVAL_UNDEF(&src_data);
	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_ZVAL(src_spec)
		Z_PARAM_STR(src_data)
		Z_PARAM_LONG(src_len)
		Z_PARAM_ZVAL(dst_spec)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &src_spec, &src_data_param, &src_len_param, &dst_spec);
	zephir_get_strval(&src_data, src_data_param);
	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	ZEPHIR_CPY_WRT(&src, src_spec);
	ZEPHIR_CPY_WRT(&dst, dst_spec);
	
            SDL_AudioSpec src_audio;
            SDL_AudioSpec dst_audio;
            Uint8 *dst_data = NULL;
            int dst_len = 0;

            if (!php_sdl_audio_spec_from_array(&src, &src_audio) || !php_sdl_audio_spec_from_array(&dst, &dst_audio)) {
                zend_throw_exception(zend_ce_exception, "Invalid audio spec array", 0);
                RETURN_MM();
            }

            if (SDL_ConvertAudioSamples(
                &src_audio,
                (const Uint8 *) Z_STRVAL(src_data),
                (int) src_len,
                &dst_audio,
                &dst_data,
                &dst_len
            )) {
                zval dst_spec_arr;
                php_sdl_audio_spec_to_array(&dst_audio, &dst_spec_arr);
                array_init(&result);
                add_assoc_zval(&result, "spec", &dst_spec_arr);
                if (dst_data != NULL && dst_len > 0) {
                    add_assoc_stringl(&result, "data", (char *) dst_data, (size_t) dst_len);
                    SDL_free(dst_data);
                } else {
                    add_assoc_string(&result, "data", "");
                }
                add_assoc_long(&result, "len", (zend_long) dst_len);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetAudioFormatName)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *format_param = NULL;
	zend_long format;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &format_param);
	ZEPHIR_INIT_VAR(&result);
	
            const char *name = SDL_GetAudioFormatName((SDL_AudioFormat) format);
            if (name) {
                ZVAL_STRING(&result, name);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Sdl3_SDL_Audio_SDLAudio, SDLGetSilenceValueForFormat)
{
	zval *format_param = NULL;
	zend_long format, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &format_param);
	
            result = (zend_long) SDL_GetSilenceValueForFormat((SDL_AudioFormat) format);
        
	RETURN_LONG(result);
}

