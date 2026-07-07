namespace Sdl3\SDL\Audio;

%{
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
}%

/**
 * SDL audio subsystem — devices, streams, push/pull binary I/O, and optional callbacks.
 */
class SDLAudio
{
    public static function SDLGetNumAudioDrivers() -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetNumAudioDrivers();
        }%

        return result;
    }

    public static function SDLGetAudioDriver(int index) -> string
    {
        string result = "";

        %{
            const char *name = SDL_GetAudioDriver((int) index);
            if (name) {
                ZVAL_STRING(&result, name);
            }
        }%

        return result;
    }

    public static function SDLGetCurrentAudioDriver() -> string
    {
        string result = "";

        %{
            const char *name = SDL_GetCurrentAudioDriver();
            if (name) {
                ZVAL_STRING(&result, name);
            }
        }%

        return result;
    }

    public static function SDLGetAudioPlaybackDevices() -> array
    {
        array result;

        %{
            int count = 0;
            SDL_AudioDeviceID *ids = SDL_GetAudioPlaybackDevices(&count);

            array_init(&result);
            if (ids != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) ids[i]);
                }
                SDL_free(ids);
            }
        }%

        return result;
    }

    public static function SDLGetAudioRecordingDevices() -> array
    {
        array result;

        %{
            int count = 0;
            SDL_AudioDeviceID *ids = SDL_GetAudioRecordingDevices(&count);

            array_init(&result);
            if (ids != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) ids[i]);
                }
                SDL_free(ids);
            }
        }%

        return result;
    }

    public static function SDLGetAudioDeviceName(int devid) -> string
    {
        string result = "";

        %{
            const char *name = SDL_GetAudioDeviceName((SDL_AudioDeviceID) devid);
            if (name) {
                ZVAL_STRING(&result, name);
            }
        }%

        return result;
    }

    public static function SDLGetAudioDeviceFormat(int devid) -> array
    {
        array result = [];

        %{
            SDL_AudioSpec spec;
            int sample_frames = 0;

            if (SDL_GetAudioDeviceFormat((SDL_AudioDeviceID) devid, &spec, &sample_frames)) {
                php_sdl_audio_spec_to_array(&spec, &result);
                add_assoc_long(&result, "sample_frames", (zend_long) sample_frames);
            }
        }%

        return result;
    }

    public static function SDLGetAudioDeviceChannelMap(int devid) -> array
    {
        array result;

        %{
            int count = 0;
            int *map = SDL_GetAudioDeviceChannelMap((SDL_AudioDeviceID) devid, &count);

            array_init(&result);
            if (map != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) map[i]);
                }
                SDL_free(map);
            }
        }%

        return result;
    }

    public static function SDLOpenAudioDevice(int devid, var spec = null) -> int
    {
        int device;

        %{
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
        }%

        if device == 0 {
            throw new \RuntimeException("SDL_OpenAudioDevice failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return device;
    }

    public static function SDLIsAudioDevicePhysical(int devid) -> bool
    {
        bool result;

        %{
            result = SDL_IsAudioDevicePhysical((SDL_AudioDeviceID) devid);
        }%

        return result;
    }

    public static function SDLIsAudioDevicePlayback(int devid) -> bool
    {
        bool result;

        %{
            result = SDL_IsAudioDevicePlayback((SDL_AudioDeviceID) devid);
        }%

        return result;
    }

    public static function SDLPauseAudioDevice(int devid) -> bool
    {
        bool result;

        %{
            result = SDL_PauseAudioDevice((SDL_AudioDeviceID) devid);
        }%

        return result;
    }

    public static function SDLResumeAudioDevice(int devid) -> bool
    {
        bool result;

        %{
            result = SDL_ResumeAudioDevice((SDL_AudioDeviceID) devid);
        }%

        return result;
    }

    public static function SDLAudioDevicePaused(int devid) -> bool
    {
        bool result;

        %{
            result = SDL_AudioDevicePaused((SDL_AudioDeviceID) devid);
        }%

        return result;
    }

    public static function SDLGetAudioDeviceGain(int devid) -> double
    {
        double result;

        %{
            result = (double) SDL_GetAudioDeviceGain((SDL_AudioDeviceID) devid);
        }%

        return result;
    }

    public static function SDLSetAudioDeviceGain(int devid, double gain) -> bool
    {
        bool result;

        %{
            result = SDL_SetAudioDeviceGain((SDL_AudioDeviceID) devid, (float) gain);
        }%

        return result;
    }

    public static function SDLCloseAudioDevice(int devid) -> void
    {
        %{
            php_sdl_audio_callback_maps_ensure();
            zval *zv = zend_hash_index_find(&php_sdl_audio_postmix_callback_map, (zend_ulong) devid);
            if (zv != NULL) {
                php_sdl_audio_callback_context_free((php_sdl_audio_callback_context *) Z_PTR_P(zv));
                zend_hash_index_del(&php_sdl_audio_postmix_callback_map, (zend_ulong) devid);
            }
            SDL_CloseAudioDevice((SDL_AudioDeviceID) devid);
        }%
    }

    public static function SDLBindAudioStreams(int devid, array streams) -> bool
    {
        bool result;
        var s;

        let s = streams;

        %{
            int count = 0;
            SDL_AudioStream **stream_ptrs = php_sdl_audio_streams_from_array(&s, &count);

            result = SDL_BindAudioStreams((SDL_AudioDeviceID) devid, stream_ptrs, count);
            if (stream_ptrs) {
                efree(stream_ptrs);
            }
        }%

        return result;
    }

    public static function SDLBindAudioStream(int devid, int stream) -> bool
    {
        bool result;

        %{
            SDL_AudioStream *s = php_sdl_audio_stream_from_handle(stream);
            result = SDL_BindAudioStream((SDL_AudioDeviceID) devid, s);
        }%

        return result;
    }

    public static function SDLUnbindAudioStreams(array streams) -> void
    {
        var s;

        let s = streams;

        %{
            int count = 0;
            SDL_AudioStream **stream_ptrs = php_sdl_audio_streams_from_array(&s, &count);

            if (stream_ptrs) {
                SDL_UnbindAudioStreams(stream_ptrs, count);
                efree(stream_ptrs);
            }
        }%
    }

    public static function SDLUnbindAudioStream(int stream) -> void
    {
        %{
            SDL_UnbindAudioStream(php_sdl_audio_stream_from_handle(stream));
        }%
    }

    public static function SDLGetAudioStreamDevice(int stream) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetAudioStreamDevice(php_sdl_audio_stream_from_handle(stream));
        }%

        return result;
    }

    public static function SDLCreateAudioStream(var src_spec, var dst_spec) -> int
    {
        int stream_ptr;
        var src;
        var dst;

        let src = src_spec;
        let dst = dst_spec;

        %{
            SDL_AudioSpec src_audio;
            SDL_AudioSpec dst_audio;

            if (!php_sdl_audio_spec_from_array(&src, &src_audio) || !php_sdl_audio_spec_from_array(&dst, &dst_audio)) {
                zend_throw_exception(zend_ce_exception, "Invalid audio spec array", 0);
                RETURN_MM();
            }

            SDL_AudioStream *stream = SDL_CreateAudioStream(&src_audio, &dst_audio);
            stream_ptr = (zend_long)(uintptr_t) stream;
        }%

        if stream_ptr == 0 {
            throw new \RuntimeException("SDL_CreateAudioStream failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return stream_ptr;
    }

    public static function SDLGetAudioStreamProperties(int stream) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetAudioStreamProperties(php_sdl_audio_stream_from_handle(stream));
        }%

        return result;
    }

    public static function SDLGetAudioStreamFormat(int stream) -> array
    {
        array result = [];

        %{
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
        }%

        return result;
    }

    public static function SDLSetAudioStreamFormat(int stream, var src_spec, var dst_spec) -> bool
    {
        bool result;
        var src;
        var dst;

        let src = src_spec;
        let dst = dst_spec;

        %{
            SDL_AudioSpec src_audio;
            SDL_AudioSpec dst_audio;

            if (!php_sdl_audio_spec_from_array(&src, &src_audio) || !php_sdl_audio_spec_from_array(&dst, &dst_audio)) {
                zend_throw_exception(zend_ce_exception, "Invalid audio spec array", 0);
                RETURN_MM();
            }

            result = SDL_SetAudioStreamFormat(php_sdl_audio_stream_from_handle(stream), &src_audio, &dst_audio);
        }%

        return result;
    }

    public static function SDLGetAudioStreamFrequencyRatio(int stream) -> double
    {
        double result;

        %{
            result = (double) SDL_GetAudioStreamFrequencyRatio(php_sdl_audio_stream_from_handle(stream));
        }%

        return result;
    }

    public static function SDLSetAudioStreamFrequencyRatio(int stream, double ratio) -> bool
    {
        bool result;

        %{
            result = SDL_SetAudioStreamFrequencyRatio(php_sdl_audio_stream_from_handle(stream), (float) ratio);
        }%

        return result;
    }

    public static function SDLGetAudioStreamGain(int stream) -> double
    {
        double result;

        %{
            result = (double) SDL_GetAudioStreamGain(php_sdl_audio_stream_from_handle(stream));
        }%

        return result;
    }

    public static function SDLSetAudioStreamGain(int stream, double gain) -> bool
    {
        bool result;

        %{
            result = SDL_SetAudioStreamGain(php_sdl_audio_stream_from_handle(stream), (float) gain);
        }%

        return result;
    }

    public static function SDLGetAudioStreamInputChannelMap(int stream) -> array
    {
        array result;

        %{
            int count = 0;
            int *map = SDL_GetAudioStreamInputChannelMap(php_sdl_audio_stream_from_handle(stream), &count);

            array_init(&result);
            if (map != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) map[i]);
                }
                SDL_free(map);
            }
        }%

        return result;
    }

    public static function SDLGetAudioStreamOutputChannelMap(int stream) -> array
    {
        array result;

        %{
            int count = 0;
            int *map = SDL_GetAudioStreamOutputChannelMap(php_sdl_audio_stream_from_handle(stream), &count);

            array_init(&result);
            if (map != NULL) {
                for (int i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) map[i]);
                }
                SDL_free(map);
            }
        }%

        return result;
    }

    public static function SDLSetAudioStreamInputChannelMap(int stream, array chmap) -> bool
    {
        bool result;
        var map;

        let map = chmap;

        %{
            int count = 0;
            int *values = php_sdl_audio_int_array_from_php(&map, &count);

            result = SDL_SetAudioStreamInputChannelMap(php_sdl_audio_stream_from_handle(stream), values, count);
            if (values) {
                efree(values);
            }
        }%

        return result;
    }

    public static function SDLSetAudioStreamOutputChannelMap(int stream, array chmap) -> bool
    {
        bool result;
        var map;

        let map = chmap;

        %{
            int count = 0;
            int *values = php_sdl_audio_int_array_from_php(&map, &count);

            result = SDL_SetAudioStreamOutputChannelMap(php_sdl_audio_stream_from_handle(stream), values, count);
            if (values) {
                efree(values);
            }
        }%

        return result;
    }

    public static function SDLPutAudioStreamData(int stream, string data) -> bool
    {
        bool result;

        %{
            result = SDL_PutAudioStreamData(
                php_sdl_audio_stream_from_handle(stream),
                (const void *) Z_STRVAL(data),
                (int) Z_STRLEN(data)
            );
        }%

        return result;
    }

    public static function SDLPutAudioStreamDataNoCopy(int stream, string data, var callback = null) -> bool
    {
        bool result;
        var cb;

        let cb = callback;

        %{
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
        }%

        return result;
    }

    public static function SDLPutAudioStreamPlanarData(int stream, array channel_buffers, int num_channels, int num_samples) -> bool
    {
        bool result;
        var buffers;

        let buffers = channel_buffers;

        %{
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
        }%

        return result;
    }

    public static function SDLGetAudioStreamData(int stream, int len) -> string
    {
        string result = "";

        %{
            void *buf = emalloc((size_t) len);
            int got = SDL_GetAudioStreamData(php_sdl_audio_stream_from_handle(stream), buf, (int) len);

            if (got > 0) {
                ZVAL_STRINGL(&result, (char *) buf, (size_t) got);
            }
            efree(buf);
        }%

        return result;
    }

    public static function SDLGetAudioStreamAvailable(int stream) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetAudioStreamAvailable(php_sdl_audio_stream_from_handle(stream));
        }%

        return result;
    }

    public static function SDLGetAudioStreamQueued(int stream) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetAudioStreamQueued(php_sdl_audio_stream_from_handle(stream));
        }%

        return result;
    }

    public static function SDLFlushAudioStream(int stream) -> bool
    {
        bool result;

        %{
            result = SDL_FlushAudioStream(php_sdl_audio_stream_from_handle(stream));
        }%

        return result;
    }

    public static function SDLClearAudioStream(int stream) -> bool
    {
        bool result;

        %{
            result = SDL_ClearAudioStream(php_sdl_audio_stream_from_handle(stream));
        }%

        return result;
    }

    public static function SDLPauseAudioStreamDevice(int stream) -> bool
    {
        bool result;

        %{
            result = SDL_PauseAudioStreamDevice(php_sdl_audio_stream_from_handle(stream));
        }%

        return result;
    }

    public static function SDLResumeAudioStreamDevice(int stream) -> bool
    {
        bool result;

        %{
            result = SDL_ResumeAudioStreamDevice(php_sdl_audio_stream_from_handle(stream));
        }%

        return result;
    }

    public static function SDLAudioStreamDevicePaused(int stream) -> bool
    {
        bool result;

        %{
            result = SDL_AudioStreamDevicePaused(php_sdl_audio_stream_from_handle(stream));
        }%

        return result;
    }

    public static function SDLLockAudioStream(int stream) -> bool
    {
        bool result;

        %{
            result = SDL_LockAudioStream(php_sdl_audio_stream_from_handle(stream));
        }%

        return result;
    }

    public static function SDLUnlockAudioStream(int stream) -> bool
    {
        bool result;

        %{
            result = SDL_UnlockAudioStream(php_sdl_audio_stream_from_handle(stream));
        }%

        return result;
    }

    public static function SDLSetAudioStreamGetCallback(int stream, var callback = null) -> bool
    {
        bool result;
        var cb;

        let cb = callback;

        %{
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
        }%

        return result;
    }

    public static function SDLSetAudioStreamPutCallback(int stream, var callback = null) -> bool
    {
        bool result;
        var cb;

        let cb = callback;

        %{
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
        }%

        return result;
    }

    public static function SDLDestroyAudioStream(int stream) -> void
    {
        %{
            zend_long stream_ptr = (zend_long) stream;
            php_sdl_audio_clear_stream_callback(stream_ptr);
            SDL_DestroyAudioStream(php_sdl_audio_stream_from_handle(stream_ptr));
        }%
    }

    public static function SDLOpenAudioDeviceStream(int devid, var spec = null, var callback = null) -> int
    {
        int stream_ptr;
        var sp;
        var cb;

        let sp = spec;
        let cb = callback;

        %{
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
        }%

        if stream_ptr == 0 {
            throw new \RuntimeException("SDL_OpenAudioDeviceStream failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return stream_ptr;
    }

    public static function SDLSetAudioPostmixCallback(int devid, var callback = null) -> bool
    {
        bool result;
        var cb;

        let cb = callback;

        %{
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
        }%

        return result;
    }

    public static function SDLLoadWAV(string path) -> array
    {
        array result = [];

        %{
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
        }%

        if empty(result) {
            throw new \RuntimeException("SDL_LoadWAV failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return result;
    }

    public static function SDLMixAudio(string dst, string src, int format, int len, double volume) -> string
    {
        string result = "";

        %{
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
        }%

        return result;
    }

    public static function SDLConvertAudioSamples(var src_spec, string src_data, int src_len, var dst_spec) -> array
    {
        array result = [];
        var src;
        var dst;

        let src = src_spec;
        let dst = dst_spec;

        %{
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
        }%

        return result;
    }

    public static function SDLGetAudioFormatName(int format) -> string
    {
        string result = "";

        %{
            const char *name = SDL_GetAudioFormatName((SDL_AudioFormat) format);
            if (name) {
                ZVAL_STRING(&result, name);
            }
        }%

        return result;
    }

    public static function SDLGetSilenceValueForFormat(int format) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetSilenceValueForFormat((SDL_AudioFormat) format);
        }%

        return result;
    }
}
