namespace Sdl3\SDL\Gpu;

%{
#include <SDL3/SDL.h>
#include <string.h>

/* --- assoc-array field readers ------------------------------------------ */

static zval *php_sdl_gpu_field(zval *arr, const char *key)
{
    if (arr == NULL || Z_TYPE_P(arr) != IS_ARRAY) {
        return NULL;
    }
    return zend_hash_str_find(Z_ARRVAL_P(arr), key, strlen(key));
}

static zend_long php_sdl_gpu_long(zval *arr, const char *key, zend_long defval)
{
    zval *v = php_sdl_gpu_field(arr, key);
    return v ? zval_get_long(v) : defval;
}

static double php_sdl_gpu_double(zval *arr, const char *key, double defval)
{
    zval *v = php_sdl_gpu_field(arr, key);
    return v ? zval_get_double(v) : defval;
}

static bool php_sdl_gpu_bool(zval *arr, const char *key, bool defval)
{
    zval *v = php_sdl_gpu_field(arr, key);
    return v ? (zend_is_true(v) ? true : false) : defval;
}

static void *php_sdl_gpu_handle(zval *arr, const char *key)
{
    return (void *)(uintptr_t) php_sdl_gpu_long(arr, key, 0);
}

static Uint32 php_sdl_gpu_count(zval *arr)
{
    if (arr == NULL || Z_TYPE_P(arr) != IS_ARRAY) {
        return 0;
    }
    return (Uint32) zend_hash_num_elements(Z_ARRVAL_P(arr));
}

/* --- struct builders (assoc arrays mirror the C field names) ------------- */

static void php_sdl_gpu_fcolor(zval *arr, SDL_FColor *out)
{
    out->r = (float) php_sdl_gpu_double(arr, "r", 0.0);
    out->g = (float) php_sdl_gpu_double(arr, "g", 0.0);
    out->b = (float) php_sdl_gpu_double(arr, "b", 0.0);
    out->a = (float) php_sdl_gpu_double(arr, "a", 0.0);
}

static void php_sdl_gpu_viewport(zval *arr, SDL_GPUViewport *out)
{
    SDL_zerop(out);
    out->x = (float) php_sdl_gpu_double(arr, "x", 0.0);
    out->y = (float) php_sdl_gpu_double(arr, "y", 0.0);
    out->w = (float) php_sdl_gpu_double(arr, "w", 0.0);
    out->h = (float) php_sdl_gpu_double(arr, "h", 0.0);
    out->min_depth = (float) php_sdl_gpu_double(arr, "min_depth", 0.0);
    out->max_depth = (float) php_sdl_gpu_double(arr, "max_depth", 1.0);
}

static void php_sdl_gpu_color_target_info(zval *arr, SDL_GPUColorTargetInfo *out)
{
    zval *cc;

    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->mip_level = (Uint32) php_sdl_gpu_long(arr, "mip_level", 0);
    out->layer_or_depth_plane = (Uint32) php_sdl_gpu_long(arr, "layer_or_depth_plane", 0);
    cc = php_sdl_gpu_field(arr, "clear_color");
    if (cc != NULL) {
        php_sdl_gpu_fcolor(cc, &out->clear_color);
    }
    out->load_op = (SDL_GPULoadOp) php_sdl_gpu_long(arr, "load_op", 0);
    out->store_op = (SDL_GPUStoreOp) php_sdl_gpu_long(arr, "store_op", 0);
    out->resolve_texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "resolve_texture");
    out->resolve_mip_level = (Uint32) php_sdl_gpu_long(arr, "resolve_mip_level", 0);
    out->resolve_layer = (Uint32) php_sdl_gpu_long(arr, "resolve_layer", 0);
    out->cycle = php_sdl_gpu_bool(arr, "cycle", false);
    out->cycle_resolve_texture = php_sdl_gpu_bool(arr, "cycle_resolve_texture", false);
}

static void php_sdl_gpu_depth_stencil_target_info(zval *arr, SDL_GPUDepthStencilTargetInfo *out)
{
    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->clear_depth = (float) php_sdl_gpu_double(arr, "clear_depth", 0.0);
    out->load_op = (SDL_GPULoadOp) php_sdl_gpu_long(arr, "load_op", 0);
    out->store_op = (SDL_GPUStoreOp) php_sdl_gpu_long(arr, "store_op", 0);
    out->stencil_load_op = (SDL_GPULoadOp) php_sdl_gpu_long(arr, "stencil_load_op", 0);
    out->stencil_store_op = (SDL_GPUStoreOp) php_sdl_gpu_long(arr, "stencil_store_op", 0);
    out->cycle = php_sdl_gpu_bool(arr, "cycle", false);
    out->clear_stencil = (Uint8) php_sdl_gpu_long(arr, "clear_stencil", 0);
    out->mip_level = (Uint8) php_sdl_gpu_long(arr, "mip_level", 0);
    out->layer = (Uint8) php_sdl_gpu_long(arr, "layer", 0);
}

static void php_sdl_gpu_buffer_binding(zval *arr, SDL_GPUBufferBinding *out)
{
    SDL_zerop(out);
    out->buffer = (SDL_GPUBuffer *) php_sdl_gpu_handle(arr, "buffer");
    out->offset = (Uint32) php_sdl_gpu_long(arr, "offset", 0);
}

static void php_sdl_gpu_texture_sampler_binding(zval *arr, SDL_GPUTextureSamplerBinding *out)
{
    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->sampler = (SDL_GPUSampler *) php_sdl_gpu_handle(arr, "sampler");
}

static void php_sdl_gpu_storage_texture_rw_binding(zval *arr, SDL_GPUStorageTextureReadWriteBinding *out)
{
    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->mip_level = (Uint32) php_sdl_gpu_long(arr, "mip_level", 0);
    out->layer = (Uint32) php_sdl_gpu_long(arr, "layer", 0);
    out->cycle = php_sdl_gpu_bool(arr, "cycle", false);
}

static void php_sdl_gpu_storage_buffer_rw_binding(zval *arr, SDL_GPUStorageBufferReadWriteBinding *out)
{
    SDL_zerop(out);
    out->buffer = (SDL_GPUBuffer *) php_sdl_gpu_handle(arr, "buffer");
    out->cycle = php_sdl_gpu_bool(arr, "cycle", false);
}

static void php_sdl_gpu_texture_transfer_info(zval *arr, SDL_GPUTextureTransferInfo *out)
{
    SDL_zerop(out);
    out->transfer_buffer = (SDL_GPUTransferBuffer *) php_sdl_gpu_handle(arr, "transfer_buffer");
    out->offset = (Uint32) php_sdl_gpu_long(arr, "offset", 0);
    out->pixels_per_row = (Uint32) php_sdl_gpu_long(arr, "pixels_per_row", 0);
    out->rows_per_layer = (Uint32) php_sdl_gpu_long(arr, "rows_per_layer", 0);
}

static void php_sdl_gpu_texture_region(zval *arr, SDL_GPUTextureRegion *out)
{
    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->mip_level = (Uint32) php_sdl_gpu_long(arr, "mip_level", 0);
    out->layer = (Uint32) php_sdl_gpu_long(arr, "layer", 0);
    out->x = (Uint32) php_sdl_gpu_long(arr, "x", 0);
    out->y = (Uint32) php_sdl_gpu_long(arr, "y", 0);
    out->z = (Uint32) php_sdl_gpu_long(arr, "z", 0);
    out->w = (Uint32) php_sdl_gpu_long(arr, "w", 0);
    out->h = (Uint32) php_sdl_gpu_long(arr, "h", 0);
    out->d = (Uint32) php_sdl_gpu_long(arr, "d", 0);
}

static void php_sdl_gpu_texture_location(zval *arr, SDL_GPUTextureLocation *out)
{
    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->mip_level = (Uint32) php_sdl_gpu_long(arr, "mip_level", 0);
    out->layer = (Uint32) php_sdl_gpu_long(arr, "layer", 0);
    out->x = (Uint32) php_sdl_gpu_long(arr, "x", 0);
    out->y = (Uint32) php_sdl_gpu_long(arr, "y", 0);
    out->z = (Uint32) php_sdl_gpu_long(arr, "z", 0);
}

static void php_sdl_gpu_transfer_buffer_location(zval *arr, SDL_GPUTransferBufferLocation *out)
{
    SDL_zerop(out);
    out->transfer_buffer = (SDL_GPUTransferBuffer *) php_sdl_gpu_handle(arr, "transfer_buffer");
    out->offset = (Uint32) php_sdl_gpu_long(arr, "offset", 0);
}

static void php_sdl_gpu_buffer_location(zval *arr, SDL_GPUBufferLocation *out)
{
    SDL_zerop(out);
    out->buffer = (SDL_GPUBuffer *) php_sdl_gpu_handle(arr, "buffer");
    out->offset = (Uint32) php_sdl_gpu_long(arr, "offset", 0);
}

static void php_sdl_gpu_buffer_region(zval *arr, SDL_GPUBufferRegion *out)
{
    SDL_zerop(out);
    out->buffer = (SDL_GPUBuffer *) php_sdl_gpu_handle(arr, "buffer");
    out->offset = (Uint32) php_sdl_gpu_long(arr, "offset", 0);
    out->size = (Uint32) php_sdl_gpu_long(arr, "size", 0);
}

static void php_sdl_gpu_blit_region(zval *arr, SDL_GPUBlitRegion *out)
{
    SDL_zerop(out);
    out->texture = (SDL_GPUTexture *) php_sdl_gpu_handle(arr, "texture");
    out->mip_level = (Uint32) php_sdl_gpu_long(arr, "mip_level", 0);
    out->layer_or_depth_plane = (Uint32) php_sdl_gpu_long(arr, "layer_or_depth_plane", 0);
    out->x = (Uint32) php_sdl_gpu_long(arr, "x", 0);
    out->y = (Uint32) php_sdl_gpu_long(arr, "y", 0);
    out->w = (Uint32) php_sdl_gpu_long(arr, "w", 0);
    out->h = (Uint32) php_sdl_gpu_long(arr, "h", 0);
}

static void php_sdl_gpu_stencil_op_state(zval *arr, SDL_GPUStencilOpState *out)
{
    SDL_zerop(out);
    out->fail_op = (SDL_GPUStencilOp) php_sdl_gpu_long(arr, "fail_op", 0);
    out->pass_op = (SDL_GPUStencilOp) php_sdl_gpu_long(arr, "pass_op", 0);
    out->depth_fail_op = (SDL_GPUStencilOp) php_sdl_gpu_long(arr, "depth_fail_op", 0);
    out->compare_op = (SDL_GPUCompareOp) php_sdl_gpu_long(arr, "compare_op", 0);
}

static void php_sdl_gpu_color_target_blend_state(zval *arr, SDL_GPUColorTargetBlendState *out)
{
    SDL_zerop(out);
    out->src_color_blendfactor = (SDL_GPUBlendFactor) php_sdl_gpu_long(arr, "src_color_blendfactor", 0);
    out->dst_color_blendfactor = (SDL_GPUBlendFactor) php_sdl_gpu_long(arr, "dst_color_blendfactor", 0);
    out->color_blend_op = (SDL_GPUBlendOp) php_sdl_gpu_long(arr, "color_blend_op", 0);
    out->src_alpha_blendfactor = (SDL_GPUBlendFactor) php_sdl_gpu_long(arr, "src_alpha_blendfactor", 0);
    out->dst_alpha_blendfactor = (SDL_GPUBlendFactor) php_sdl_gpu_long(arr, "dst_alpha_blendfactor", 0);
    out->alpha_blend_op = (SDL_GPUBlendOp) php_sdl_gpu_long(arr, "alpha_blend_op", 0);
    out->color_write_mask = (SDL_GPUColorComponentFlags) php_sdl_gpu_long(arr, "color_write_mask", 0);
    out->enable_blend = php_sdl_gpu_bool(arr, "enable_blend", false);
    out->enable_color_write_mask = php_sdl_gpu_bool(arr, "enable_color_write_mask", false);
}

/* Build an emalloc'd array of opaque handles from a PHP list of ints. */
static void **php_sdl_gpu_handle_list(zval *arr, Uint32 *out_count)
{
    Uint32 n = php_sdl_gpu_count(arr);
    void **items;
    Uint32 i = 0;
    zval *el;

    *out_count = n;
    if (n == 0) {
        return NULL;
    }

    items = (void **) emalloc(sizeof(void *) * n);
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(arr), el) {
        items[i] = (void *)(uintptr_t) zval_get_long(el);
        i++;
    } ZEND_HASH_FOREACH_END();

    return items;
}
}%

/**
 * Bindings for the SDL3 GPU API (SDL_gpu.h) plus the GPU render-state
 * functions from SDL_render.h.
 *
 * All opaque SDL_GPU* objects (device, buffers, textures, samplers, shaders,
 * pipelines, command buffers, passes, fences, render states) travel across
 * the PHP boundary as opaque int handles. Creation-info structs are assoc
 * arrays that mirror the C struct field names exactly; nested struct lists
 * are arrays of assoc arrays. Shader bytecode and uniform data are binary
 * PHP strings.
 */
class SDLGPU
{
    // --- Device -----------------------------------------------------------

    public static function SDLGPUSupportsShaderFormats(int format_flags, var name = null) -> bool
    {
        bool result;

        %{
            const char *drv = (Z_TYPE_P(name) == IS_STRING) ? Z_STRVAL_P(name) : NULL;
            result = SDL_GPUSupportsShaderFormats((SDL_GPUShaderFormat) format_flags, drv);
        }%

        return result;
    }

    public static function SDLGPUSupportsProperties(int props) -> bool
    {
        bool result;

        %{
            result = SDL_GPUSupportsProperties((SDL_PropertiesID) props);
        }%

        return result;
    }

    public static function SDLCreateGPUDevice(int format_flags, bool debug_mode, var name = null) -> int
    {
        int ptr;

        %{
            const char *drv = (Z_TYPE_P(name) == IS_STRING) ? Z_STRVAL_P(name) : NULL;
            SDL_GPUDevice *device = SDL_CreateGPUDevice((SDL_GPUShaderFormat) format_flags, debug_mode ? true : false, drv);
            ptr = (zend_long)(uintptr_t) device;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateGPUDevice failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLCreateGPUDeviceWithProperties(int props) -> int
    {
        int ptr;

        %{
            SDL_GPUDevice *device = SDL_CreateGPUDeviceWithProperties((SDL_PropertiesID) props);
            ptr = (zend_long)(uintptr_t) device;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateGPUDeviceWithProperties failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLDestroyGPUDevice(int device) -> void
    {
        %{
            SDL_DestroyGPUDevice((SDL_GPUDevice *)(uintptr_t) device);
        }%
    }

    public static function SDLGetNumGPUDrivers() -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetNumGPUDrivers();
        }%

        return result;
    }

    public static function SDLGetGPUDriver(int index) -> string
    {
        string result = "";

        %{
            const char *drv = SDL_GetGPUDriver((int) index);
            if (drv != NULL) {
                ZVAL_STRING(&result, drv);
            }
        }%

        return result;
    }

    public static function SDLGetGPUDeviceDriver(int device) -> string
    {
        string result = "";

        %{
            const char *drv = SDL_GetGPUDeviceDriver((SDL_GPUDevice *)(uintptr_t) device);
            if (drv != NULL) {
                ZVAL_STRING(&result, drv);
            }
        }%

        return result;
    }

    public static function SDLGetGPUShaderFormats(int device) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetGPUShaderFormats((SDL_GPUDevice *)(uintptr_t) device);
        }%

        return result;
    }

    public static function SDLGetGPUDeviceProperties(int device) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetGPUDeviceProperties((SDL_GPUDevice *)(uintptr_t) device);
        }%

        return result;
    }

    // --- Resource creation --------------------------------------------------

    /**
     * createinfo: ["code": string (bytecode), "entrypoint": string, "format": int,
     *  "num_samplers": int, "num_readonly_storage_textures": int,
     *  "num_readonly_storage_buffers": int, "num_readwrite_storage_textures": int,
     *  "num_readwrite_storage_buffers": int, "num_uniform_buffers": int,
     *  "threadcount_x": int, "threadcount_y": int, "threadcount_z": int, "props": int]
     */
    public static function SDLCreateGPUComputePipeline(int device, var createinfo) -> int
    {
        int ptr;

        %{
            SDL_GPUComputePipelineCreateInfo ci;
            zval *code = php_sdl_gpu_field(createinfo, "code");
            zval *entry = php_sdl_gpu_field(createinfo, "entrypoint");

            SDL_zero(ci);
            if (code != NULL && Z_TYPE_P(code) == IS_STRING) {
                ci.code = (const Uint8 *) Z_STRVAL_P(code);
                ci.code_size = (size_t) Z_STRLEN_P(code);
            }
            ci.entrypoint = (entry != NULL && Z_TYPE_P(entry) == IS_STRING) ? Z_STRVAL_P(entry) : "main";
            ci.format = (SDL_GPUShaderFormat) php_sdl_gpu_long(createinfo, "format", 0);
            ci.num_samplers = (Uint32) php_sdl_gpu_long(createinfo, "num_samplers", 0);
            ci.num_readonly_storage_textures = (Uint32) php_sdl_gpu_long(createinfo, "num_readonly_storage_textures", 0);
            ci.num_readonly_storage_buffers = (Uint32) php_sdl_gpu_long(createinfo, "num_readonly_storage_buffers", 0);
            ci.num_readwrite_storage_textures = (Uint32) php_sdl_gpu_long(createinfo, "num_readwrite_storage_textures", 0);
            ci.num_readwrite_storage_buffers = (Uint32) php_sdl_gpu_long(createinfo, "num_readwrite_storage_buffers", 0);
            ci.num_uniform_buffers = (Uint32) php_sdl_gpu_long(createinfo, "num_uniform_buffers", 0);
            ci.threadcount_x = (Uint32) php_sdl_gpu_long(createinfo, "threadcount_x", 0);
            ci.threadcount_y = (Uint32) php_sdl_gpu_long(createinfo, "threadcount_y", 0);
            ci.threadcount_z = (Uint32) php_sdl_gpu_long(createinfo, "threadcount_z", 0);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            SDL_GPUComputePipeline *pipeline = SDL_CreateGPUComputePipeline((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) pipeline;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateGPUComputePipeline failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    /**
     * createinfo: ["vertex_shader": int, "fragment_shader": int,
     *  "vertex_input_state": ["vertex_buffer_descriptions": array, "vertex_attributes": array],
     *  "primitive_type": int, "rasterizer_state": array, "multisample_state": array,
     *  "depth_stencil_state": array,
     *  "target_info": ["color_target_descriptions": array, "depth_stencil_format": int,
     *                  "has_depth_stencil_target": bool],
     *  "props": int]
     */
    public static function SDLCreateGPUGraphicsPipeline(int device, var createinfo) -> int
    {
        int ptr;

        %{
            SDL_GPUGraphicsPipelineCreateInfo ci;
            SDL_GPUVertexBufferDescription *vbds = NULL;
            SDL_GPUVertexAttribute *vats = NULL;
            SDL_GPUColorTargetDescription *ctds = NULL;
            zval *vis, *rs, *ms, *dss, *ti, *el;
            Uint32 i;

            SDL_zero(ci);
            ci.vertex_shader = (SDL_GPUShader *) php_sdl_gpu_handle(createinfo, "vertex_shader");
            ci.fragment_shader = (SDL_GPUShader *) php_sdl_gpu_handle(createinfo, "fragment_shader");
            ci.primitive_type = (SDL_GPUPrimitiveType) php_sdl_gpu_long(createinfo, "primitive_type", 0);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            vis = php_sdl_gpu_field(createinfo, "vertex_input_state");
            if (vis != NULL && Z_TYPE_P(vis) == IS_ARRAY) {
                zval *vbd_arr = php_sdl_gpu_field(vis, "vertex_buffer_descriptions");
                zval *vat_arr = php_sdl_gpu_field(vis, "vertex_attributes");
                Uint32 nvb = php_sdl_gpu_count(vbd_arr);
                Uint32 nva = php_sdl_gpu_count(vat_arr);

                if (nvb > 0) {
                    vbds = (SDL_GPUVertexBufferDescription *) emalloc(sizeof(*vbds) * nvb);
                    i = 0;
                    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(vbd_arr), el) {
                        SDL_zerop(&vbds[i]);
                        vbds[i].slot = (Uint32) php_sdl_gpu_long(el, "slot", 0);
                        vbds[i].pitch = (Uint32) php_sdl_gpu_long(el, "pitch", 0);
                        vbds[i].input_rate = (SDL_GPUVertexInputRate) php_sdl_gpu_long(el, "input_rate", 0);
                        vbds[i].instance_step_rate = (Uint32) php_sdl_gpu_long(el, "instance_step_rate", 0);
                        i++;
                    } ZEND_HASH_FOREACH_END();
                }
                if (nva > 0) {
                    vats = (SDL_GPUVertexAttribute *) emalloc(sizeof(*vats) * nva);
                    i = 0;
                    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(vat_arr), el) {
                        SDL_zerop(&vats[i]);
                        vats[i].location = (Uint32) php_sdl_gpu_long(el, "location", 0);
                        vats[i].buffer_slot = (Uint32) php_sdl_gpu_long(el, "buffer_slot", 0);
                        vats[i].format = (SDL_GPUVertexElementFormat) php_sdl_gpu_long(el, "format", 0);
                        vats[i].offset = (Uint32) php_sdl_gpu_long(el, "offset", 0);
                        i++;
                    } ZEND_HASH_FOREACH_END();
                }

                ci.vertex_input_state.vertex_buffer_descriptions = vbds;
                ci.vertex_input_state.num_vertex_buffers = nvb;
                ci.vertex_input_state.vertex_attributes = vats;
                ci.vertex_input_state.num_vertex_attributes = nva;
            }

            rs = php_sdl_gpu_field(createinfo, "rasterizer_state");
            if (rs != NULL && Z_TYPE_P(rs) == IS_ARRAY) {
                ci.rasterizer_state.fill_mode = (SDL_GPUFillMode) php_sdl_gpu_long(rs, "fill_mode", 0);
                ci.rasterizer_state.cull_mode = (SDL_GPUCullMode) php_sdl_gpu_long(rs, "cull_mode", 0);
                ci.rasterizer_state.front_face = (SDL_GPUFrontFace) php_sdl_gpu_long(rs, "front_face", 0);
                ci.rasterizer_state.depth_bias_constant_factor = (float) php_sdl_gpu_double(rs, "depth_bias_constant_factor", 0.0);
                ci.rasterizer_state.depth_bias_clamp = (float) php_sdl_gpu_double(rs, "depth_bias_clamp", 0.0);
                ci.rasterizer_state.depth_bias_slope_factor = (float) php_sdl_gpu_double(rs, "depth_bias_slope_factor", 0.0);
                ci.rasterizer_state.enable_depth_bias = php_sdl_gpu_bool(rs, "enable_depth_bias", false);
                ci.rasterizer_state.enable_depth_clip = php_sdl_gpu_bool(rs, "enable_depth_clip", false);
            }

            ms = php_sdl_gpu_field(createinfo, "multisample_state");
            if (ms != NULL && Z_TYPE_P(ms) == IS_ARRAY) {
                ci.multisample_state.sample_count = (SDL_GPUSampleCount) php_sdl_gpu_long(ms, "sample_count", 0);
                ci.multisample_state.sample_mask = (Uint32) php_sdl_gpu_long(ms, "sample_mask", 0);
                ci.multisample_state.enable_mask = php_sdl_gpu_bool(ms, "enable_mask", false);
                ci.multisample_state.enable_alpha_to_coverage = php_sdl_gpu_bool(ms, "enable_alpha_to_coverage", false);
            }

            dss = php_sdl_gpu_field(createinfo, "depth_stencil_state");
            if (dss != NULL && Z_TYPE_P(dss) == IS_ARRAY) {
                zval *back = php_sdl_gpu_field(dss, "back_stencil_state");
                zval *front = php_sdl_gpu_field(dss, "front_stencil_state");

                ci.depth_stencil_state.compare_op = (SDL_GPUCompareOp) php_sdl_gpu_long(dss, "compare_op", 0);
                if (back != NULL) {
                    php_sdl_gpu_stencil_op_state(back, &ci.depth_stencil_state.back_stencil_state);
                }
                if (front != NULL) {
                    php_sdl_gpu_stencil_op_state(front, &ci.depth_stencil_state.front_stencil_state);
                }
                ci.depth_stencil_state.compare_mask = (Uint8) php_sdl_gpu_long(dss, "compare_mask", 0);
                ci.depth_stencil_state.write_mask = (Uint8) php_sdl_gpu_long(dss, "write_mask", 0);
                ci.depth_stencil_state.enable_depth_test = php_sdl_gpu_bool(dss, "enable_depth_test", false);
                ci.depth_stencil_state.enable_depth_write = php_sdl_gpu_bool(dss, "enable_depth_write", false);
                ci.depth_stencil_state.enable_stencil_test = php_sdl_gpu_bool(dss, "enable_stencil_test", false);
            }

            ti = php_sdl_gpu_field(createinfo, "target_info");
            if (ti != NULL && Z_TYPE_P(ti) == IS_ARRAY) {
                zval *ctd_arr = php_sdl_gpu_field(ti, "color_target_descriptions");
                Uint32 nct = php_sdl_gpu_count(ctd_arr);

                if (nct > 0) {
                    ctds = (SDL_GPUColorTargetDescription *) emalloc(sizeof(*ctds) * nct);
                    i = 0;
                    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(ctd_arr), el) {
                        zval *bs = php_sdl_gpu_field(el, "blend_state");
                        SDL_zerop(&ctds[i]);
                        ctds[i].format = (SDL_GPUTextureFormat) php_sdl_gpu_long(el, "format", 0);
                        if (bs != NULL) {
                            php_sdl_gpu_color_target_blend_state(bs, &ctds[i].blend_state);
                        }
                        i++;
                    } ZEND_HASH_FOREACH_END();
                }

                ci.target_info.color_target_descriptions = ctds;
                ci.target_info.num_color_targets = nct;
                ci.target_info.depth_stencil_format = (SDL_GPUTextureFormat) php_sdl_gpu_long(ti, "depth_stencil_format", 0);
                ci.target_info.has_depth_stencil_target = php_sdl_gpu_bool(ti, "has_depth_stencil_target", false);
            }

            SDL_GPUGraphicsPipeline *pipeline = SDL_CreateGPUGraphicsPipeline((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) pipeline;

            if (vbds != NULL) { efree(vbds); }
            if (vats != NULL) { efree(vats); }
            if (ctds != NULL) { efree(ctds); }
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateGPUGraphicsPipeline failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    /**
     * createinfo: ["min_filter": int, "mag_filter": int, "mipmap_mode": int,
     *  "address_mode_u": int, "address_mode_v": int, "address_mode_w": int,
     *  "mip_lod_bias": float, "max_anisotropy": float, "compare_op": int,
     *  "min_lod": float, "max_lod": float, "enable_anisotropy": bool,
     *  "enable_compare": bool, "props": int]
     */
    public static function SDLCreateGPUSampler(int device, var createinfo) -> int
    {
        int ptr;

        %{
            SDL_GPUSamplerCreateInfo ci;

            SDL_zero(ci);
            ci.min_filter = (SDL_GPUFilter) php_sdl_gpu_long(createinfo, "min_filter", 0);
            ci.mag_filter = (SDL_GPUFilter) php_sdl_gpu_long(createinfo, "mag_filter", 0);
            ci.mipmap_mode = (SDL_GPUSamplerMipmapMode) php_sdl_gpu_long(createinfo, "mipmap_mode", 0);
            ci.address_mode_u = (SDL_GPUSamplerAddressMode) php_sdl_gpu_long(createinfo, "address_mode_u", 0);
            ci.address_mode_v = (SDL_GPUSamplerAddressMode) php_sdl_gpu_long(createinfo, "address_mode_v", 0);
            ci.address_mode_w = (SDL_GPUSamplerAddressMode) php_sdl_gpu_long(createinfo, "address_mode_w", 0);
            ci.mip_lod_bias = (float) php_sdl_gpu_double(createinfo, "mip_lod_bias", 0.0);
            ci.max_anisotropy = (float) php_sdl_gpu_double(createinfo, "max_anisotropy", 0.0);
            ci.compare_op = (SDL_GPUCompareOp) php_sdl_gpu_long(createinfo, "compare_op", 0);
            ci.min_lod = (float) php_sdl_gpu_double(createinfo, "min_lod", 0.0);
            ci.max_lod = (float) php_sdl_gpu_double(createinfo, "max_lod", 0.0);
            ci.enable_anisotropy = php_sdl_gpu_bool(createinfo, "enable_anisotropy", false);
            ci.enable_compare = php_sdl_gpu_bool(createinfo, "enable_compare", false);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            SDL_GPUSampler *sampler = SDL_CreateGPUSampler((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) sampler;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateGPUSampler failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    /**
     * createinfo: ["code": string (bytecode), "entrypoint": string, "format": int,
     *  "stage": int, "num_samplers": int, "num_storage_textures": int,
     *  "num_storage_buffers": int, "num_uniform_buffers": int, "props": int]
     */
    public static function SDLCreateGPUShader(int device, var createinfo) -> int
    {
        int ptr;

        %{
            SDL_GPUShaderCreateInfo ci;
            zval *code = php_sdl_gpu_field(createinfo, "code");
            zval *entry = php_sdl_gpu_field(createinfo, "entrypoint");

            SDL_zero(ci);
            if (code != NULL && Z_TYPE_P(code) == IS_STRING) {
                ci.code = (const Uint8 *) Z_STRVAL_P(code);
                ci.code_size = (size_t) Z_STRLEN_P(code);
            }
            ci.entrypoint = (entry != NULL && Z_TYPE_P(entry) == IS_STRING) ? Z_STRVAL_P(entry) : "main";
            ci.format = (SDL_GPUShaderFormat) php_sdl_gpu_long(createinfo, "format", 0);
            ci.stage = (SDL_GPUShaderStage) php_sdl_gpu_long(createinfo, "stage", 0);
            ci.num_samplers = (Uint32) php_sdl_gpu_long(createinfo, "num_samplers", 0);
            ci.num_storage_textures = (Uint32) php_sdl_gpu_long(createinfo, "num_storage_textures", 0);
            ci.num_storage_buffers = (Uint32) php_sdl_gpu_long(createinfo, "num_storage_buffers", 0);
            ci.num_uniform_buffers = (Uint32) php_sdl_gpu_long(createinfo, "num_uniform_buffers", 0);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            SDL_GPUShader *shader = SDL_CreateGPUShader((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) shader;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateGPUShader failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    /**
     * createinfo: ["type": int, "format": int, "usage": int, "width": int,
     *  "height": int, "layer_count_or_depth": int, "num_levels": int,
     *  "sample_count": int, "props": int]
     */
    public static function SDLCreateGPUTexture(int device, var createinfo) -> int
    {
        int ptr;

        %{
            SDL_GPUTextureCreateInfo ci;

            SDL_zero(ci);
            ci.type = (SDL_GPUTextureType) php_sdl_gpu_long(createinfo, "type", 0);
            ci.format = (SDL_GPUTextureFormat) php_sdl_gpu_long(createinfo, "format", 0);
            ci.usage = (SDL_GPUTextureUsageFlags) php_sdl_gpu_long(createinfo, "usage", 0);
            ci.width = (Uint32) php_sdl_gpu_long(createinfo, "width", 0);
            ci.height = (Uint32) php_sdl_gpu_long(createinfo, "height", 0);
            ci.layer_count_or_depth = (Uint32) php_sdl_gpu_long(createinfo, "layer_count_or_depth", 1);
            ci.num_levels = (Uint32) php_sdl_gpu_long(createinfo, "num_levels", 1);
            ci.sample_count = (SDL_GPUSampleCount) php_sdl_gpu_long(createinfo, "sample_count", 0);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            SDL_GPUTexture *texture = SDL_CreateGPUTexture((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) texture;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateGPUTexture failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    /**
     * createinfo: ["usage": int, "size": int, "props": int]
     */
    public static function SDLCreateGPUBuffer(int device, var createinfo) -> int
    {
        int ptr;

        %{
            SDL_GPUBufferCreateInfo ci;

            SDL_zero(ci);
            ci.usage = (SDL_GPUBufferUsageFlags) php_sdl_gpu_long(createinfo, "usage", 0);
            ci.size = (Uint32) php_sdl_gpu_long(createinfo, "size", 0);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            SDL_GPUBuffer *buf = SDL_CreateGPUBuffer((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) buf;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateGPUBuffer failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    /**
     * createinfo: ["usage": int, "size": int, "props": int]
     */
    public static function SDLCreateGPUTransferBuffer(int device, var createinfo) -> int
    {
        int ptr;

        %{
            SDL_GPUTransferBufferCreateInfo ci;

            SDL_zero(ci);
            ci.usage = (SDL_GPUTransferBufferUsage) php_sdl_gpu_long(createinfo, "usage", 0);
            ci.size = (Uint32) php_sdl_gpu_long(createinfo, "size", 0);
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            SDL_GPUTransferBuffer *buf = SDL_CreateGPUTransferBuffer((SDL_GPUDevice *)(uintptr_t) device, &ci);
            ptr = (zend_long)(uintptr_t) buf;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateGPUTransferBuffer failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    // --- Debug naming -------------------------------------------------------

    public static function SDLSetGPUBufferName(int device, int buffer, string text) -> void
    {
        %{
            SDL_SetGPUBufferName((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUBuffer *)(uintptr_t) buffer, Z_STRVAL(text));
        }%
    }

    public static function SDLSetGPUTextureName(int device, int texture, string text) -> void
    {
        %{
            SDL_SetGPUTextureName((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUTexture *)(uintptr_t) texture, Z_STRVAL(text));
        }%
    }

    public static function SDLInsertGPUDebugLabel(int command_buffer, string text) -> void
    {
        %{
            SDL_InsertGPUDebugLabel((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer, Z_STRVAL(text));
        }%
    }

    public static function SDLPushGPUDebugGroup(int command_buffer, string name) -> void
    {
        %{
            SDL_PushGPUDebugGroup((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer, Z_STRVAL(name));
        }%
    }

    public static function SDLPopGPUDebugGroup(int command_buffer) -> void
    {
        %{
            SDL_PopGPUDebugGroup((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer);
        }%
    }

    // --- Resource release -----------------------------------------------------

    public static function SDLReleaseGPUTexture(int device, int texture) -> void
    {
        %{
            SDL_ReleaseGPUTexture((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUTexture *)(uintptr_t) texture);
        }%
    }

    public static function SDLReleaseGPUSampler(int device, int sampler) -> void
    {
        %{
            SDL_ReleaseGPUSampler((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUSampler *)(uintptr_t) sampler);
        }%
    }

    public static function SDLReleaseGPUBuffer(int device, int buffer) -> void
    {
        %{
            SDL_ReleaseGPUBuffer((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUBuffer *)(uintptr_t) buffer);
        }%
    }

    public static function SDLReleaseGPUTransferBuffer(int device, int transfer_buffer) -> void
    {
        %{
            SDL_ReleaseGPUTransferBuffer((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer);
        }%
    }

    public static function SDLReleaseGPUComputePipeline(int device, int compute_pipeline) -> void
    {
        %{
            SDL_ReleaseGPUComputePipeline((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUComputePipeline *)(uintptr_t) compute_pipeline);
        }%
    }

    public static function SDLReleaseGPUShader(int device, int shader) -> void
    {
        %{
            SDL_ReleaseGPUShader((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUShader *)(uintptr_t) shader);
        }%
    }

    public static function SDLReleaseGPUGraphicsPipeline(int device, int graphics_pipeline) -> void
    {
        %{
            SDL_ReleaseGPUGraphicsPipeline((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUGraphicsPipeline *)(uintptr_t) graphics_pipeline);
        }%
    }

    // --- Command buffers & uniform data ----------------------------------------

    public static function SDLAcquireGPUCommandBuffer(int device) -> int
    {
        int ptr;

        %{
            SDL_GPUCommandBuffer *cb = SDL_AcquireGPUCommandBuffer((SDL_GPUDevice *)(uintptr_t) device);
            ptr = (zend_long)(uintptr_t) cb;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_AcquireGPUCommandBuffer failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLPushGPUVertexUniformData(int command_buffer, int slot_index, string data) -> void
    {
        %{
            SDL_PushGPUVertexUniformData(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                (Uint32) slot_index,
                (const void *) Z_STRVAL(data),
                (Uint32) Z_STRLEN(data)
            );
        }%
    }

    public static function SDLPushGPUFragmentUniformData(int command_buffer, int slot_index, string data) -> void
    {
        %{
            SDL_PushGPUFragmentUniformData(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                (Uint32) slot_index,
                (const void *) Z_STRVAL(data),
                (Uint32) Z_STRLEN(data)
            );
        }%
    }

    public static function SDLPushGPUComputeUniformData(int command_buffer, int slot_index, string data) -> void
    {
        %{
            SDL_PushGPUComputeUniformData(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                (Uint32) slot_index,
                (const void *) Z_STRVAL(data),
                (Uint32) Z_STRLEN(data)
            );
        }%
    }

    // --- Render passes ---------------------------------------------------------

    /**
     * color_target_infos: array of ["texture": int, "mip_level": int,
     *  "layer_or_depth_plane": int, "clear_color": ["r","g","b","a"],
     *  "load_op": int, "store_op": int, "resolve_texture": int,
     *  "resolve_mip_level": int, "resolve_layer": int, "cycle": bool,
     *  "cycle_resolve_texture": bool]
     * depth_stencil_target_info: assoc array or null.
     */
    public static function SDLBeginGPURenderPass(int command_buffer, var color_target_infos, var depth_stencil_target_info = null) -> int
    {
        int ptr;

        %{
            SDL_GPUColorTargetInfo *targets = NULL;
            SDL_GPUDepthStencilTargetInfo ds;
            SDL_GPUDepthStencilTargetInfo *dsp = NULL;
            Uint32 num_targets = php_sdl_gpu_count(color_target_infos);
            zval *el;
            Uint32 i = 0;

            if (num_targets > 0) {
                targets = (SDL_GPUColorTargetInfo *) emalloc(sizeof(*targets) * num_targets);
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(color_target_infos), el) {
                    php_sdl_gpu_color_target_info(el, &targets[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }

            if (Z_TYPE_P(depth_stencil_target_info) == IS_ARRAY) {
                php_sdl_gpu_depth_stencil_target_info(depth_stencil_target_info, &ds);
                dsp = &ds;
            }

            SDL_GPURenderPass *pass = SDL_BeginGPURenderPass(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                targets, num_targets, dsp
            );
            ptr = (zend_long)(uintptr_t) pass;

            if (targets != NULL) { efree(targets); }
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_BeginGPURenderPass failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLBindGPUGraphicsPipeline(int render_pass, int graphics_pipeline) -> void
    {
        %{
            SDL_BindGPUGraphicsPipeline((SDL_GPURenderPass *)(uintptr_t) render_pass, (SDL_GPUGraphicsPipeline *)(uintptr_t) graphics_pipeline);
        }%
    }

    /**
     * viewport: ["x", "y", "w", "h", "min_depth", "max_depth"]
     */
    public static function SDLSetGPUViewport(int render_pass, var viewport) -> void
    {
        %{
            SDL_GPUViewport vp;
            php_sdl_gpu_viewport(viewport, &vp);
            SDL_SetGPUViewport((SDL_GPURenderPass *)(uintptr_t) render_pass, &vp);
        }%
    }

    /**
     * scissor: ["x": int, "y": int, "w": int, "h": int]
     */
    public static function SDLSetGPUScissor(int render_pass, var scissor) -> void
    {
        %{
            SDL_Rect rect;
            rect.x = (int) php_sdl_gpu_long(scissor, "x", 0);
            rect.y = (int) php_sdl_gpu_long(scissor, "y", 0);
            rect.w = (int) php_sdl_gpu_long(scissor, "w", 0);
            rect.h = (int) php_sdl_gpu_long(scissor, "h", 0);
            SDL_SetGPUScissor((SDL_GPURenderPass *)(uintptr_t) render_pass, &rect);
        }%
    }

    /**
     * blend_constants: ["r", "g", "b", "a"] floats
     */
    public static function SDLSetGPUBlendConstants(int render_pass, var blend_constants) -> void
    {
        %{
            SDL_FColor color;
            php_sdl_gpu_fcolor(blend_constants, &color);
            SDL_SetGPUBlendConstants((SDL_GPURenderPass *)(uintptr_t) render_pass, color);
        }%
    }

    public static function SDLSetGPUStencilReference(int render_pass, int reference) -> void
    {
        %{
            SDL_SetGPUStencilReference((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint8) reference);
        }%
    }

    /**
     * bindings: array of ["buffer": int, "offset": int]
     */
    public static function SDLBindGPUVertexBuffers(int render_pass, int first_slot, var bindings) -> void
    {
        %{
            SDL_GPUBufferBinding *items = NULL;
            Uint32 n = php_sdl_gpu_count(bindings);
            Uint32 i = 0;
            zval *el;

            if (n > 0) {
                items = (SDL_GPUBufferBinding *) emalloc(sizeof(*items) * n);
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(bindings), el) {
                    php_sdl_gpu_buffer_binding(el, &items[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }

            SDL_BindGPUVertexBuffers((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, items, n);

            if (items != NULL) { efree(items); }
        }%
    }

    /**
     * binding: ["buffer": int, "offset": int]
     */
    public static function SDLBindGPUIndexBuffer(int render_pass, var binding, int index_element_size) -> void
    {
        %{
            SDL_GPUBufferBinding item;
            php_sdl_gpu_buffer_binding(binding, &item);
            SDL_BindGPUIndexBuffer((SDL_GPURenderPass *)(uintptr_t) render_pass, &item, (SDL_GPUIndexElementSize) index_element_size);
        }%
    }

    /**
     * bindings: array of ["texture": int, "sampler": int]
     */
    public static function SDLBindGPUVertexSamplers(int render_pass, int first_slot, var bindings) -> void
    {
        %{
            SDL_GPUTextureSamplerBinding *items = NULL;
            Uint32 n = php_sdl_gpu_count(bindings);
            Uint32 i = 0;
            zval *el;

            if (n > 0) {
                items = (SDL_GPUTextureSamplerBinding *) emalloc(sizeof(*items) * n);
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(bindings), el) {
                    php_sdl_gpu_texture_sampler_binding(el, &items[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }

            SDL_BindGPUVertexSamplers((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, items, n);

            if (items != NULL) { efree(items); }
        }%
    }

    /**
     * storage_textures: array of int texture handles
     */
    public static function SDLBindGPUVertexStorageTextures(int render_pass, int first_slot, var storage_textures) -> void
    {
        %{
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(storage_textures, &n);

            SDL_BindGPUVertexStorageTextures((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, (SDL_GPUTexture *const *) items, n);

            if (items != NULL) { efree(items); }
        }%
    }

    /**
     * storage_buffers: array of int buffer handles
     */
    public static function SDLBindGPUVertexStorageBuffers(int render_pass, int first_slot, var storage_buffers) -> void
    {
        %{
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(storage_buffers, &n);

            SDL_BindGPUVertexStorageBuffers((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, (SDL_GPUBuffer *const *) items, n);

            if (items != NULL) { efree(items); }
        }%
    }

    /**
     * bindings: array of ["texture": int, "sampler": int]
     */
    public static function SDLBindGPUFragmentSamplers(int render_pass, int first_slot, var bindings) -> void
    {
        %{
            SDL_GPUTextureSamplerBinding *items = NULL;
            Uint32 n = php_sdl_gpu_count(bindings);
            Uint32 i = 0;
            zval *el;

            if (n > 0) {
                items = (SDL_GPUTextureSamplerBinding *) emalloc(sizeof(*items) * n);
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(bindings), el) {
                    php_sdl_gpu_texture_sampler_binding(el, &items[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }

            SDL_BindGPUFragmentSamplers((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, items, n);

            if (items != NULL) { efree(items); }
        }%
    }

    /**
     * storage_textures: array of int texture handles
     */
    public static function SDLBindGPUFragmentStorageTextures(int render_pass, int first_slot, var storage_textures) -> void
    {
        %{
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(storage_textures, &n);

            SDL_BindGPUFragmentStorageTextures((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, (SDL_GPUTexture *const *) items, n);

            if (items != NULL) { efree(items); }
        }%
    }

    /**
     * storage_buffers: array of int buffer handles
     */
    public static function SDLBindGPUFragmentStorageBuffers(int render_pass, int first_slot, var storage_buffers) -> void
    {
        %{
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(storage_buffers, &n);

            SDL_BindGPUFragmentStorageBuffers((SDL_GPURenderPass *)(uintptr_t) render_pass, (Uint32) first_slot, (SDL_GPUBuffer *const *) items, n);

            if (items != NULL) { efree(items); }
        }%
    }

    public static function SDLDrawGPUIndexedPrimitives(int render_pass, int num_indices, int num_instances, int first_index, int vertex_offset, int first_instance) -> void
    {
        %{
            SDL_DrawGPUIndexedPrimitives(
                (SDL_GPURenderPass *)(uintptr_t) render_pass,
                (Uint32) num_indices, (Uint32) num_instances,
                (Uint32) first_index, (Sint32) vertex_offset, (Uint32) first_instance
            );
        }%
    }

    public static function SDLDrawGPUPrimitives(int render_pass, int num_vertices, int num_instances, int first_vertex, int first_instance) -> void
    {
        %{
            SDL_DrawGPUPrimitives(
                (SDL_GPURenderPass *)(uintptr_t) render_pass,
                (Uint32) num_vertices, (Uint32) num_instances,
                (Uint32) first_vertex, (Uint32) first_instance
            );
        }%
    }

    public static function SDLDrawGPUPrimitivesIndirect(int render_pass, int buffer, int offset, int draw_count) -> void
    {
        %{
            SDL_DrawGPUPrimitivesIndirect(
                (SDL_GPURenderPass *)(uintptr_t) render_pass,
                (SDL_GPUBuffer *)(uintptr_t) buffer,
                (Uint32) offset, (Uint32) draw_count
            );
        }%
    }

    public static function SDLDrawGPUIndexedPrimitivesIndirect(int render_pass, int buffer, int offset, int draw_count) -> void
    {
        %{
            SDL_DrawGPUIndexedPrimitivesIndirect(
                (SDL_GPURenderPass *)(uintptr_t) render_pass,
                (SDL_GPUBuffer *)(uintptr_t) buffer,
                (Uint32) offset, (Uint32) draw_count
            );
        }%
    }

    public static function SDLEndGPURenderPass(int render_pass) -> void
    {
        %{
            SDL_EndGPURenderPass((SDL_GPURenderPass *)(uintptr_t) render_pass);
        }%
    }

    // --- Compute passes ----------------------------------------------------------

    /**
     * storage_texture_bindings: array of ["texture": int, "mip_level": int, "layer": int, "cycle": bool]
     * storage_buffer_bindings: array of ["buffer": int, "cycle": bool]
     */
    public static function SDLBeginGPUComputePass(int command_buffer, var storage_texture_bindings = null, var storage_buffer_bindings = null) -> int
    {
        int ptr;

        %{
            SDL_GPUStorageTextureReadWriteBinding *tex_items = NULL;
            SDL_GPUStorageBufferReadWriteBinding *buf_items = NULL;
            Uint32 num_tex = php_sdl_gpu_count(storage_texture_bindings);
            Uint32 num_buf = php_sdl_gpu_count(storage_buffer_bindings);
            Uint32 i;
            zval *el;

            if (num_tex > 0) {
                tex_items = (SDL_GPUStorageTextureReadWriteBinding *) emalloc(sizeof(*tex_items) * num_tex);
                i = 0;
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(storage_texture_bindings), el) {
                    php_sdl_gpu_storage_texture_rw_binding(el, &tex_items[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }
            if (num_buf > 0) {
                buf_items = (SDL_GPUStorageBufferReadWriteBinding *) emalloc(sizeof(*buf_items) * num_buf);
                i = 0;
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(storage_buffer_bindings), el) {
                    php_sdl_gpu_storage_buffer_rw_binding(el, &buf_items[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }

            SDL_GPUComputePass *pass = SDL_BeginGPUComputePass(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                tex_items, num_tex, buf_items, num_buf
            );
            ptr = (zend_long)(uintptr_t) pass;

            if (tex_items != NULL) { efree(tex_items); }
            if (buf_items != NULL) { efree(buf_items); }
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_BeginGPUComputePass failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLBindGPUComputePipeline(int compute_pass, int compute_pipeline) -> void
    {
        %{
            SDL_BindGPUComputePipeline((SDL_GPUComputePass *)(uintptr_t) compute_pass, (SDL_GPUComputePipeline *)(uintptr_t) compute_pipeline);
        }%
    }

    /**
     * bindings: array of ["texture": int, "sampler": int]
     */
    public static function SDLBindGPUComputeSamplers(int compute_pass, int first_slot, var bindings) -> void
    {
        %{
            SDL_GPUTextureSamplerBinding *items = NULL;
            Uint32 n = php_sdl_gpu_count(bindings);
            Uint32 i = 0;
            zval *el;

            if (n > 0) {
                items = (SDL_GPUTextureSamplerBinding *) emalloc(sizeof(*items) * n);
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(bindings), el) {
                    php_sdl_gpu_texture_sampler_binding(el, &items[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }

            SDL_BindGPUComputeSamplers((SDL_GPUComputePass *)(uintptr_t) compute_pass, (Uint32) first_slot, items, n);

            if (items != NULL) { efree(items); }
        }%
    }

    /**
     * storage_textures: array of int texture handles
     */
    public static function SDLBindGPUComputeStorageTextures(int compute_pass, int first_slot, var storage_textures) -> void
    {
        %{
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(storage_textures, &n);

            SDL_BindGPUComputeStorageTextures((SDL_GPUComputePass *)(uintptr_t) compute_pass, (Uint32) first_slot, (SDL_GPUTexture *const *) items, n);

            if (items != NULL) { efree(items); }
        }%
    }

    /**
     * storage_buffers: array of int buffer handles
     */
    public static function SDLBindGPUComputeStorageBuffers(int compute_pass, int first_slot, var storage_buffers) -> void
    {
        %{
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(storage_buffers, &n);

            SDL_BindGPUComputeStorageBuffers((SDL_GPUComputePass *)(uintptr_t) compute_pass, (Uint32) first_slot, (SDL_GPUBuffer *const *) items, n);

            if (items != NULL) { efree(items); }
        }%
    }

    public static function SDLDispatchGPUCompute(int compute_pass, int groupcount_x, int groupcount_y, int groupcount_z) -> void
    {
        %{
            SDL_DispatchGPUCompute(
                (SDL_GPUComputePass *)(uintptr_t) compute_pass,
                (Uint32) groupcount_x, (Uint32) groupcount_y, (Uint32) groupcount_z
            );
        }%
    }

    public static function SDLDispatchGPUComputeIndirect(int compute_pass, int buffer, int offset) -> void
    {
        %{
            SDL_DispatchGPUComputeIndirect(
                (SDL_GPUComputePass *)(uintptr_t) compute_pass,
                (SDL_GPUBuffer *)(uintptr_t) buffer,
                (Uint32) offset
            );
        }%
    }

    public static function SDLEndGPUComputePass(int compute_pass) -> void
    {
        %{
            SDL_EndGPUComputePass((SDL_GPUComputePass *)(uintptr_t) compute_pass);
        }%
    }

    // --- Transfer buffers ----------------------------------------------------------

    /**
     * Returns the mapped memory address as an opaque int. Prefer the
     * writeToGPUTransferBuffer / readFromGPUTransferBuffer helpers, which
     * handle the map/copy/unmap cycle with PHP binary strings.
     */
    public static function SDLMapGPUTransferBuffer(int device, int transfer_buffer, bool cycle = false) -> int
    {
        int ptr;

        %{
            void *mapped = SDL_MapGPUTransferBuffer(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer,
                cycle ? true : false
            );
            ptr = (zend_long)(uintptr_t) mapped;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_MapGPUTransferBuffer failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLUnmapGPUTransferBuffer(int device, int transfer_buffer) -> void
    {
        %{
            SDL_UnmapGPUTransferBuffer(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer
            );
        }%
    }

    /**
     * Helper: maps the transfer buffer, copies the binary string into it at
     * the given byte offset, and unmaps it.
     */
    public static function writeToGPUTransferBuffer(int device, int transfer_buffer, string data, bool cycle = false, int offset = 0) -> bool
    {
        bool result = false;

        if offset < 0 {
            throw new \InvalidArgumentException("offset must be >= 0");
        }

        %{
            void *mapped = SDL_MapGPUTransferBuffer(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer,
                cycle ? true : false
            );

            if (mapped != NULL) {
                memcpy((Uint8 *) mapped + (size_t) offset, Z_STRVAL(data), Z_STRLEN(data));
                SDL_UnmapGPUTransferBuffer(
                    (SDL_GPUDevice *)(uintptr_t) device,
                    (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer
                );
                result = true;
            }
        }%

        return result;
    }

    /**
     * Helper: maps the transfer buffer, copies `length` bytes out from the
     * given byte offset as a binary string, and unmaps it.
     */
    public static function readFromGPUTransferBuffer(int device, int transfer_buffer, int length, int offset = 0) -> string
    {
        string result = "";

        if length < 0 || offset < 0 {
            throw new \InvalidArgumentException("length and offset must be >= 0");
        }

        %{
            void *mapped = SDL_MapGPUTransferBuffer(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer,
                false
            );

            if (mapped != NULL && length > 0) {
                ZVAL_STRINGL(&result, (char *)((Uint8 *) mapped + (size_t) offset), (size_t) length);
            }
            if (mapped != NULL) {
                SDL_UnmapGPUTransferBuffer(
                    (SDL_GPUDevice *)(uintptr_t) device,
                    (SDL_GPUTransferBuffer *)(uintptr_t) transfer_buffer
                );
            }
        }%

        return result;
    }

    // --- Copy passes ----------------------------------------------------------

    public static function SDLBeginGPUCopyPass(int command_buffer) -> int
    {
        int ptr;

        %{
            SDL_GPUCopyPass *pass = SDL_BeginGPUCopyPass((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer);
            ptr = (zend_long)(uintptr_t) pass;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_BeginGPUCopyPass failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    /**
     * source: ["transfer_buffer": int, "offset": int, "pixels_per_row": int, "rows_per_layer": int]
     * destination: ["texture": int, "mip_level": int, "layer": int, "x", "y", "z", "w", "h", "d"]
     */
    public static function SDLUploadToGPUTexture(int copy_pass, var source, var destination, bool cycle = false) -> void
    {
        %{
            SDL_GPUTextureTransferInfo src;
            SDL_GPUTextureRegion dst;

            php_sdl_gpu_texture_transfer_info(source, &src);
            php_sdl_gpu_texture_region(destination, &dst);

            SDL_UploadToGPUTexture((SDL_GPUCopyPass *)(uintptr_t) copy_pass, &src, &dst, cycle ? true : false);
        }%
    }

    /**
     * source: ["transfer_buffer": int, "offset": int]
     * destination: ["buffer": int, "offset": int, "size": int]
     */
    public static function SDLUploadToGPUBuffer(int copy_pass, var source, var destination, bool cycle = false) -> void
    {
        %{
            SDL_GPUTransferBufferLocation src;
            SDL_GPUBufferRegion dst;

            php_sdl_gpu_transfer_buffer_location(source, &src);
            php_sdl_gpu_buffer_region(destination, &dst);

            SDL_UploadToGPUBuffer((SDL_GPUCopyPass *)(uintptr_t) copy_pass, &src, &dst, cycle ? true : false);
        }%
    }

    /**
     * source/destination: ["texture": int, "mip_level": int, "layer": int, "x", "y", "z"]
     */
    public static function SDLCopyGPUTextureToTexture(int copy_pass, var source, var destination, int w, int h, int d, bool cycle = false) -> void
    {
        %{
            SDL_GPUTextureLocation src;
            SDL_GPUTextureLocation dst;

            php_sdl_gpu_texture_location(source, &src);
            php_sdl_gpu_texture_location(destination, &dst);

            SDL_CopyGPUTextureToTexture(
                (SDL_GPUCopyPass *)(uintptr_t) copy_pass,
                &src, &dst,
                (Uint32) w, (Uint32) h, (Uint32) d,
                cycle ? true : false
            );
        }%
    }

    /**
     * source/destination: ["buffer": int, "offset": int]
     */
    public static function SDLCopyGPUBufferToBuffer(int copy_pass, var source, var destination, int size, bool cycle = false) -> void
    {
        %{
            SDL_GPUBufferLocation src;
            SDL_GPUBufferLocation dst;

            php_sdl_gpu_buffer_location(source, &src);
            php_sdl_gpu_buffer_location(destination, &dst);

            SDL_CopyGPUBufferToBuffer(
                (SDL_GPUCopyPass *)(uintptr_t) copy_pass,
                &src, &dst,
                (Uint32) size,
                cycle ? true : false
            );
        }%
    }

    /**
     * source: texture region, destination: texture transfer info.
     */
    public static function SDLDownloadFromGPUTexture(int copy_pass, var source, var destination) -> void
    {
        %{
            SDL_GPUTextureRegion src;
            SDL_GPUTextureTransferInfo dst;

            php_sdl_gpu_texture_region(source, &src);
            php_sdl_gpu_texture_transfer_info(destination, &dst);

            SDL_DownloadFromGPUTexture((SDL_GPUCopyPass *)(uintptr_t) copy_pass, &src, &dst);
        }%
    }

    /**
     * source: buffer region, destination: transfer buffer location.
     */
    public static function SDLDownloadFromGPUBuffer(int copy_pass, var source, var destination) -> void
    {
        %{
            SDL_GPUBufferRegion src;
            SDL_GPUTransferBufferLocation dst;

            php_sdl_gpu_buffer_region(source, &src);
            php_sdl_gpu_transfer_buffer_location(destination, &dst);

            SDL_DownloadFromGPUBuffer((SDL_GPUCopyPass *)(uintptr_t) copy_pass, &src, &dst);
        }%
    }

    public static function SDLEndGPUCopyPass(int copy_pass) -> void
    {
        %{
            SDL_EndGPUCopyPass((SDL_GPUCopyPass *)(uintptr_t) copy_pass);
        }%
    }

    public static function SDLGenerateMipmapsForGPUTexture(int command_buffer, int texture) -> void
    {
        %{
            SDL_GenerateMipmapsForGPUTexture((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer, (SDL_GPUTexture *)(uintptr_t) texture);
        }%
    }

    /**
     * info: ["source": blit region, "destination": blit region, "load_op": int,
     *  "clear_color": ["r","g","b","a"], "flip_mode": int, "filter": int, "cycle": bool]
     */
    public static function SDLBlitGPUTexture(int command_buffer, var info) -> void
    {
        %{
            SDL_GPUBlitInfo bi;
            zval *src = php_sdl_gpu_field(info, "source");
            zval *dst = php_sdl_gpu_field(info, "destination");
            zval *cc = php_sdl_gpu_field(info, "clear_color");

            SDL_zero(bi);
            if (src != NULL) {
                php_sdl_gpu_blit_region(src, &bi.source);
            }
            if (dst != NULL) {
                php_sdl_gpu_blit_region(dst, &bi.destination);
            }
            bi.load_op = (SDL_GPULoadOp) php_sdl_gpu_long(info, "load_op", 0);
            if (cc != NULL) {
                php_sdl_gpu_fcolor(cc, &bi.clear_color);
            }
            bi.flip_mode = (SDL_FlipMode) php_sdl_gpu_long(info, "flip_mode", 0);
            bi.filter = (SDL_GPUFilter) php_sdl_gpu_long(info, "filter", 0);
            bi.cycle = php_sdl_gpu_bool(info, "cycle", false);

            SDL_BlitGPUTexture((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer, &bi);
        }%
    }

    // --- Swapchain & window ----------------------------------------------------------

    public static function SDLWindowSupportsGPUSwapchainComposition(int device, int window, int swapchain_composition) -> bool
    {
        bool result;

        %{
            result = SDL_WindowSupportsGPUSwapchainComposition(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_Window *)(uintptr_t) window,
                (SDL_GPUSwapchainComposition) swapchain_composition
            );
        }%

        return result;
    }

    public static function SDLWindowSupportsGPUPresentMode(int device, int window, int present_mode) -> bool
    {
        bool result;

        %{
            result = SDL_WindowSupportsGPUPresentMode(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_Window *)(uintptr_t) window,
                (SDL_GPUPresentMode) present_mode
            );
        }%

        return result;
    }

    public static function SDLClaimWindowForGPUDevice(int device, int window) -> bool
    {
        bool result;

        %{
            result = SDL_ClaimWindowForGPUDevice((SDL_GPUDevice *)(uintptr_t) device, (SDL_Window *)(uintptr_t) window);
        }%

        return result;
    }

    public static function SDLReleaseWindowFromGPUDevice(int device, int window) -> void
    {
        %{
            SDL_ReleaseWindowFromGPUDevice((SDL_GPUDevice *)(uintptr_t) device, (SDL_Window *)(uintptr_t) window);
        }%
    }

    public static function SDLSetGPUSwapchainParameters(int device, int window, int swapchain_composition, int present_mode) -> bool
    {
        bool result;

        %{
            result = SDL_SetGPUSwapchainParameters(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_Window *)(uintptr_t) window,
                (SDL_GPUSwapchainComposition) swapchain_composition,
                (SDL_GPUPresentMode) present_mode
            );
        }%

        return result;
    }

    public static function SDLSetGPUAllowedFramesInFlight(int device, int allowed_frames_in_flight) -> bool
    {
        bool result;

        %{
            result = SDL_SetGPUAllowedFramesInFlight((SDL_GPUDevice *)(uintptr_t) device, (Uint32) allowed_frames_in_flight);
        }%

        return result;
    }

    public static function SDLGetGPUSwapchainTextureFormat(int device, int window) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetGPUSwapchainTextureFormat((SDL_GPUDevice *)(uintptr_t) device, (SDL_Window *)(uintptr_t) window);
        }%

        return result;
    }

    /**
     * Returns ["texture": int, "width": int, "height": int]; "texture" is 0
     * when the swapchain is not ready (too many frames in flight).
     */
    public static function SDLAcquireGPUSwapchainTexture(int command_buffer, int window) -> array
    {
        int tex_ptr = 0;
        int tex_w = 0;
        int tex_h = 0;
        bool ok;

        %{
            SDL_GPUTexture *texture = NULL;
            Uint32 w = 0, h = 0;

            ok = SDL_AcquireGPUSwapchainTexture(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                (SDL_Window *)(uintptr_t) window,
                &texture, &w, &h
            );
            tex_ptr = (zend_long)(uintptr_t) texture;
            tex_w = (zend_long) w;
            tex_h = (zend_long) h;
        }%

        if !ok {
            throw new \RuntimeException("SDL_AcquireGPUSwapchainTexture failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ["texture": tex_ptr, "width": tex_w, "height": tex_h];
    }

    public static function SDLWaitForGPUSwapchain(int device, int window) -> bool
    {
        bool result;

        %{
            result = SDL_WaitForGPUSwapchain((SDL_GPUDevice *)(uintptr_t) device, (SDL_Window *)(uintptr_t) window);
        }%

        return result;
    }

    /**
     * Returns ["texture": int, "width": int, "height": int].
     */
    public static function SDLWaitAndAcquireGPUSwapchainTexture(int command_buffer, int window) -> array
    {
        int tex_ptr = 0;
        int tex_w = 0;
        int tex_h = 0;
        bool ok;

        %{
            SDL_GPUTexture *texture = NULL;
            Uint32 w = 0, h = 0;

            ok = SDL_WaitAndAcquireGPUSwapchainTexture(
                (SDL_GPUCommandBuffer *)(uintptr_t) command_buffer,
                (SDL_Window *)(uintptr_t) window,
                &texture, &w, &h
            );
            tex_ptr = (zend_long)(uintptr_t) texture;
            tex_w = (zend_long) w;
            tex_h = (zend_long) h;
        }%

        if !ok {
            throw new \RuntimeException("SDL_WaitAndAcquireGPUSwapchainTexture failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ["texture": tex_ptr, "width": tex_w, "height": tex_h];
    }

    // --- Submission & fences ----------------------------------------------------------

    public static function SDLSubmitGPUCommandBuffer(int command_buffer) -> bool
    {
        bool result;

        %{
            result = SDL_SubmitGPUCommandBuffer((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer);
        }%

        return result;
    }

    public static function SDLSubmitGPUCommandBufferAndAcquireFence(int command_buffer) -> int
    {
        int ptr;

        %{
            SDL_GPUFence *fence = SDL_SubmitGPUCommandBufferAndAcquireFence((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer);
            ptr = (zend_long)(uintptr_t) fence;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_SubmitGPUCommandBufferAndAcquireFence failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLCancelGPUCommandBuffer(int command_buffer) -> bool
    {
        bool result;

        %{
            result = SDL_CancelGPUCommandBuffer((SDL_GPUCommandBuffer *)(uintptr_t) command_buffer);
        }%

        return result;
    }

    public static function SDLWaitForGPUIdle(int device) -> bool
    {
        bool result;

        %{
            result = SDL_WaitForGPUIdle((SDL_GPUDevice *)(uintptr_t) device);
        }%

        return result;
    }

    /**
     * fences: array of int fence handles
     */
    public static function SDLWaitForGPUFences(int device, bool wait_all, var fences) -> bool
    {
        bool result;

        %{
            Uint32 n = 0;
            void **items = php_sdl_gpu_handle_list(fences, &n);

            result = SDL_WaitForGPUFences(
                (SDL_GPUDevice *)(uintptr_t) device,
                wait_all ? true : false,
                (SDL_GPUFence *const *) items,
                n
            );

            if (items != NULL) { efree(items); }
        }%

        return result;
    }

    public static function SDLQueryGPUFence(int device, int fence) -> bool
    {
        bool result;

        %{
            result = SDL_QueryGPUFence((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUFence *)(uintptr_t) fence);
        }%

        return result;
    }

    public static function SDLReleaseGPUFence(int device, int fence) -> void
    {
        %{
            SDL_ReleaseGPUFence((SDL_GPUDevice *)(uintptr_t) device, (SDL_GPUFence *)(uintptr_t) fence);
        }%
    }

    // --- Format queries ----------------------------------------------------------

    public static function SDLGPUTextureFormatTexelBlockSize(int format) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GPUTextureFormatTexelBlockSize((SDL_GPUTextureFormat) format);
        }%

        return result;
    }

    public static function SDLGPUTextureSupportsFormat(int device, int format, int type, int usage) -> bool
    {
        bool result;

        %{
            result = SDL_GPUTextureSupportsFormat(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_GPUTextureFormat) format,
                (SDL_GPUTextureType) type,
                (SDL_GPUTextureUsageFlags) usage
            );
        }%

        return result;
    }

    public static function SDLGPUTextureSupportsSampleCount(int device, int format, int sample_count) -> bool
    {
        bool result;

        %{
            result = SDL_GPUTextureSupportsSampleCount(
                (SDL_GPUDevice *)(uintptr_t) device,
                (SDL_GPUTextureFormat) format,
                (SDL_GPUSampleCount) sample_count
            );
        }%

        return result;
    }

    public static function SDLCalculateGPUTextureFormatSize(int format, int width, int height, int depth_or_layer_count) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_CalculateGPUTextureFormatSize(
                (SDL_GPUTextureFormat) format,
                (Uint32) width, (Uint32) height, (Uint32) depth_or_layer_count
            );
        }%

        return result;
    }

    public static function SDLGetPixelFormatFromGPUTextureFormat(int format) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetPixelFormatFromGPUTextureFormat((SDL_GPUTextureFormat) format);
        }%

        return result;
    }

    public static function SDLGetGPUTextureFormatFromPixelFormat(int format) -> int
    {
        int result;

        %{
            result = (zend_long) SDL_GetGPUTextureFormatFromPixelFormat((SDL_PixelFormat) format);
        }%

        return result;
    }

    // --- GDK (Xbox) ----------------------------------------------------------

    /**
     * Only functional on GDK (Xbox) builds; throws elsewhere.
     */
    public static function SDLGDKSuspendGPU(int device) -> void
    {
        bool supported = false;

        %{
#ifdef SDL_PLATFORM_GDK
            SDL_GDKSuspendGPU((SDL_GPUDevice *)(uintptr_t) device);
            supported = true;
#else
            (void) device;
#endif
        }%

        if !supported {
            throw new \RuntimeException("SDL_GDKSuspendGPU is only available on the GDK (Xbox) platform");
        }
    }

    /**
     * Only functional on GDK (Xbox) builds; throws elsewhere.
     */
    public static function SDLGDKResumeGPU(int device) -> void
    {
        bool supported = false;

        %{
#ifdef SDL_PLATFORM_GDK
            SDL_GDKResumeGPU((SDL_GPUDevice *)(uintptr_t) device);
            supported = true;
#else
            (void) device;
#endif
        }%

        if !supported {
            throw new \RuntimeException("SDL_GDKResumeGPU is only available on the GDK (Xbox) platform");
        }
    }

    // --- GPU render state (SDL_render.h; closes the WP2 deferrals) -------------

    public static function SDLCreateGPURenderer(int device, int window) -> int
    {
        int ptr;

        %{
            SDL_Renderer *renderer = SDL_CreateGPURenderer((SDL_GPUDevice *)(uintptr_t) device, (SDL_Window *)(uintptr_t) window);
            ptr = (zend_long)(uintptr_t) renderer;
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateGPURenderer failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLGetGPURendererDevice(int renderer) -> int
    {
        int ptr;

        %{
            SDL_GPUDevice *device = SDL_GetGPURendererDevice((SDL_Renderer *)(uintptr_t) renderer);
            ptr = (zend_long)(uintptr_t) device;
        }%

        return ptr;
    }

    /**
     * createinfo: ["fragment_shader": int,
     *  "sampler_bindings": array of ["texture": int, "sampler": int],
     *  "storage_textures": array of int, "storage_buffers": array of int,
     *  "props": int]
     */
    public static function SDLCreateGPURenderState(int renderer, var createinfo) -> int
    {
        int ptr;

        %{
            SDL_GPURenderStateCreateInfo ci;
            SDL_GPUTextureSamplerBinding *samplers = NULL;
            void **stex = NULL;
            void **sbuf = NULL;
            zval *sb_arr = php_sdl_gpu_field(createinfo, "sampler_bindings");
            Uint32 nsb = php_sdl_gpu_count(sb_arr);
            Uint32 ntex = 0;
            Uint32 nbuf = 0;
            Uint32 i = 0;
            zval *el;

            SDL_zero(ci);
            ci.fragment_shader = (SDL_GPUShader *) php_sdl_gpu_handle(createinfo, "fragment_shader");
            ci.props = (SDL_PropertiesID) php_sdl_gpu_long(createinfo, "props", 0);

            if (nsb > 0) {
                samplers = (SDL_GPUTextureSamplerBinding *) emalloc(sizeof(*samplers) * nsb);
                ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(sb_arr), el) {
                    php_sdl_gpu_texture_sampler_binding(el, &samplers[i]);
                    i++;
                } ZEND_HASH_FOREACH_END();
            }
            ci.num_sampler_bindings = (Sint32) nsb;
            ci.sampler_bindings = samplers;

            stex = php_sdl_gpu_handle_list(php_sdl_gpu_field(createinfo, "storage_textures"), &ntex);
            ci.num_storage_textures = (Sint32) ntex;
            ci.storage_textures = (SDL_GPUTexture *const *) stex;

            sbuf = php_sdl_gpu_handle_list(php_sdl_gpu_field(createinfo, "storage_buffers"), &nbuf);
            ci.num_storage_buffers = (Sint32) nbuf;
            ci.storage_buffers = (SDL_GPUBuffer *const *) sbuf;

            SDL_GPURenderState *state = SDL_CreateGPURenderState((SDL_Renderer *)(uintptr_t) renderer, &ci);
            ptr = (zend_long)(uintptr_t) state;

            if (samplers != NULL) { efree(samplers); }
            if (stex != NULL) { efree(stex); }
            if (sbuf != NULL) { efree(sbuf); }
        }%

        if ptr == 0 {
            throw new \RuntimeException("SDL_CreateGPURenderState failed: " . \Sdl3\SDL\SDLError::SDLGetError());
        }

        return ptr;
    }

    public static function SDLSetGPURenderStateFragmentUniforms(int state, int slot_index, string data) -> bool
    {
        bool result;

        %{
            result = SDL_SetGPURenderStateFragmentUniforms(
                (SDL_GPURenderState *)(uintptr_t) state,
                (Uint32) slot_index,
                (const void *) Z_STRVAL(data),
                (Uint32) Z_STRLEN(data)
            );
        }%

        return result;
    }

    /**
     * Pass state = 0 to clear the current render state.
     */
    public static function SDLSetGPURenderState(int renderer, int state = 0) -> bool
    {
        bool result;

        %{
            result = SDL_SetGPURenderState((SDL_Renderer *)(uintptr_t) renderer, (SDL_GPURenderState *)(uintptr_t) state);
        }%

        return result;
    }

    public static function SDLDestroyGPURenderState(int state) -> void
    {
        %{
            SDL_DestroyGPURenderState((SDL_GPURenderState *)(uintptr_t) state);
        }%
    }
}
