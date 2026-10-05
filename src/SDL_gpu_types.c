#include "SDL_gpu_types.h"
#include "../stubs/SDL_gpu_types_arginfo.h"

zend_class_entry *sdl3_ce_SDL_GPUShader;
zend_class_entry *sdl3_ce_SDL_GPUTexture;
zend_class_entry *sdl3_ce_SDL_GPUBuffer;
zend_class_entry *sdl3_ce_SDL_GPUTransferBuffer;
zend_class_entry *sdl3_ce_SDL_GPUSampler;
zend_class_entry *sdl3_ce_SDL_FColor;
zend_class_entry *sdl3_ce_SDL_GPUViewport;
zend_class_entry *sdl3_ce_SDL_GPUShaderCreateInfo;
zend_class_entry *sdl3_ce_SDL_GPUVertexBufferDescription;
zend_class_entry *sdl3_ce_SDL_GPUVertexAttribute;
zend_class_entry *sdl3_ce_SDL_GPUVertexInputState;
zend_class_entry *sdl3_ce_SDL_GPUStencilOpState;
zend_class_entry *sdl3_ce_SDL_GPURasterizerState;
zend_class_entry *sdl3_ce_SDL_GPUMultisampleState;
zend_class_entry *sdl3_ce_SDL_GPUDepthStencilState;
zend_class_entry *sdl3_ce_SDL_GPUColorTargetBlendState;
zend_class_entry *sdl3_ce_SDL_GPUColorTargetDescription;
zend_class_entry *sdl3_ce_SDL_GPUGraphicsPipelineTargetInfo;
zend_class_entry *sdl3_ce_SDL_GPUGraphicsPipelineCreateInfo;
zend_class_entry *sdl3_ce_SDL_GPUTextureCreateInfo;
zend_class_entry *sdl3_ce_SDL_GPUSamplerCreateInfo;
zend_class_entry *sdl3_ce_SDL_GPUBufferCreateInfo;
zend_class_entry *sdl3_ce_SDL_GPUTransferBufferCreateInfo;
zend_class_entry *sdl3_ce_SDL_GPUTextureTransferInfo;
zend_class_entry *sdl3_ce_SDL_GPUTransferBufferLocation;
zend_class_entry *sdl3_ce_SDL_GPUTextureRegion;
zend_class_entry *sdl3_ce_SDL_GPUBufferRegion;
zend_class_entry *sdl3_ce_SDL_GPUBlitRegion;
zend_class_entry *sdl3_ce_SDL_GPUColorTargetInfo;
zend_class_entry *sdl3_ce_SDL_GPUDepthStencilTargetInfo;
zend_class_entry *sdl3_ce_SDL_GPUBufferBinding;
zend_class_entry *sdl3_ce_SDL_GPUTextureSamplerBinding;
zend_class_entry *sdl3_ce_SDL_GPUBlitInfo;

SDL3_POINTER_METHODS(SDL_GPUShader)
SDL3_POINTER_METHODS(SDL_GPUTexture)
SDL3_POINTER_METHODS(SDL_GPUBuffer)
SDL3_POINTER_METHODS(SDL_GPUTransferBuffer)
SDL3_POINTER_METHODS(SDL_GPUSampler)

bool sdl3_SDL_FColor_from(zend_object *obj, SDL_FColor *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		double value;
		if (!sdl3_prop_double(obj, "r", &value)) {
			return false;
		}
		out->r = (float) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "g", &value)) {
			return false;
		}
		out->g = (float) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "b", &value)) {
			return false;
		}
		out->b = (float) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "a", &value)) {
			return false;
		}
		out->a = (float) value;
	}
	return true;
}

bool sdl3_SDL_GPUViewport_from(zend_object *obj, SDL_GPUViewport *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		double value;
		if (!sdl3_prop_double(obj, "x", &value)) {
			return false;
		}
		out->x = (float) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "y", &value)) {
			return false;
		}
		out->y = (float) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "w", &value)) {
			return false;
		}
		out->w = (float) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "h", &value)) {
			return false;
		}
		out->h = (float) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "min_depth", &value)) {
			return false;
		}
		out->min_depth = (float) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "max_depth", &value)) {
			return false;
		}
		out->max_depth = (float) value;
	}
	return true;
}

bool sdl3_SDL_GPUShaderCreateInfo_from(zend_object *obj, SDL_GPUShaderCreateInfo *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		zend_string *value;
		if (!sdl3_prop_string(obj, "code", &value)) {
			return false;
		}
		out->code = (const Uint8 *) ZSTR_VAL(value);
		out->code_size = ZSTR_LEN(value);
	}
	{
		zend_string *value;
		if (!sdl3_prop_string(obj, "entrypoint", &value)) {
			return false;
		}
		out->entrypoint = ZSTR_VAL(value);
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "format", &value)) {
			return false;
		}
		out->format = (SDL_GPUShaderFormat) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "stage", &value)) {
			return false;
		}
		out->stage = (SDL_GPUShaderStage) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "num_samplers", &value)) {
			return false;
		}
		out->num_samplers = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "num_storage_textures", &value)) {
			return false;
		}
		out->num_storage_textures = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "num_storage_buffers", &value)) {
			return false;
		}
		out->num_storage_buffers = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "num_uniform_buffers", &value)) {
			return false;
		}
		out->num_uniform_buffers = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "props", &value)) {
			return false;
		}
		out->props = (SDL_PropertiesID) value;
	}
	return true;
}

bool sdl3_SDL_GPUVertexBufferDescription_from(zend_object *obj, SDL_GPUVertexBufferDescription *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "slot", &value)) {
			return false;
		}
		out->slot = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "pitch", &value)) {
			return false;
		}
		out->pitch = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "input_rate", &value)) {
			return false;
		}
		out->input_rate = (SDL_GPUVertexInputRate) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "instance_step_rate", &value)) {
			return false;
		}
		out->instance_step_rate = (Uint32) value;
	}
	return true;
}

bool sdl3_SDL_GPUVertexAttribute_from(zend_object *obj, SDL_GPUVertexAttribute *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "location", &value)) {
			return false;
		}
		out->location = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "buffer_slot", &value)) {
			return false;
		}
		out->buffer_slot = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "format", &value)) {
			return false;
		}
		out->format = (SDL_GPUVertexElementFormat) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "offset", &value)) {
			return false;
		}
		out->offset = (Uint32) value;
	}
	return true;
}

bool sdl3_SDL_GPUVertexInputState_from(zend_object *obj, SDL_GPUVertexInputState *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	{
		zend_object **items = NULL;
		uint32_t count = 0;
		if (!sdl3_prop_list(obj, "vertex_buffer_descriptions", sdl3_ce_SDL_GPUVertexBufferDescription, &items, &count, scratch)) {
			return false;
		}
		if (count == 0) {
			out->vertex_buffer_descriptions = NULL;
			out->num_vertex_buffers = 0;
		} else {
			SDL_GPUVertexBufferDescription *native = sdl3_scratch_alloc(scratch, sizeof(SDL_GPUVertexBufferDescription) * count);
			uint32_t i;
			for (i = 0; i < count; i++) {
				if (!sdl3_SDL_GPUVertexBufferDescription_from(items[i], &native[i], scratch)) {
					return false;
				}
			}
			out->vertex_buffer_descriptions = native;
			out->num_vertex_buffers = count;
		}
	}
	{
		zend_object **items = NULL;
		uint32_t count = 0;
		if (!sdl3_prop_list(obj, "vertex_attributes", sdl3_ce_SDL_GPUVertexAttribute, &items, &count, scratch)) {
			return false;
		}
		if (count == 0) {
			out->vertex_attributes = NULL;
			out->num_vertex_attributes = 0;
		} else {
			SDL_GPUVertexAttribute *native = sdl3_scratch_alloc(scratch, sizeof(SDL_GPUVertexAttribute) * count);
			uint32_t i;
			for (i = 0; i < count; i++) {
				if (!sdl3_SDL_GPUVertexAttribute_from(items[i], &native[i], scratch)) {
					return false;
				}
			}
			out->vertex_attributes = native;
			out->num_vertex_attributes = count;
		}
	}
	return true;
}

bool sdl3_SDL_GPUStencilOpState_from(zend_object *obj, SDL_GPUStencilOpState *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "fail_op", &value)) {
			return false;
		}
		out->fail_op = (SDL_GPUStencilOp) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "pass_op", &value)) {
			return false;
		}
		out->pass_op = (SDL_GPUStencilOp) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "depth_fail_op", &value)) {
			return false;
		}
		out->depth_fail_op = (SDL_GPUStencilOp) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "compare_op", &value)) {
			return false;
		}
		out->compare_op = (SDL_GPUCompareOp) value;
	}
	return true;
}

bool sdl3_SDL_GPURasterizerState_from(zend_object *obj, SDL_GPURasterizerState *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "fill_mode", &value)) {
			return false;
		}
		out->fill_mode = (SDL_GPUFillMode) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "cull_mode", &value)) {
			return false;
		}
		out->cull_mode = (SDL_GPUCullMode) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "front_face", &value)) {
			return false;
		}
		out->front_face = (SDL_GPUFrontFace) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "depth_bias_constant_factor", &value)) {
			return false;
		}
		out->depth_bias_constant_factor = (float) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "depth_bias_clamp", &value)) {
			return false;
		}
		out->depth_bias_clamp = (float) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "depth_bias_slope_factor", &value)) {
			return false;
		}
		out->depth_bias_slope_factor = (float) value;
	}
	if (!sdl3_prop_bool(obj, "enable_depth_bias", &out->enable_depth_bias)) {
		return false;
	}
	if (!sdl3_prop_bool(obj, "enable_depth_clip", &out->enable_depth_clip)) {
		return false;
	}
	return true;
}

bool sdl3_SDL_GPUMultisampleState_from(zend_object *obj, SDL_GPUMultisampleState *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "sample_count", &value)) {
			return false;
		}
		out->sample_count = (SDL_GPUSampleCount) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "sample_mask", &value)) {
			return false;
		}
		out->sample_mask = (Uint32) value;
	}
	if (!sdl3_prop_bool(obj, "enable_mask", &out->enable_mask)) {
		return false;
	}
	return true;
}

bool sdl3_SDL_GPUDepthStencilState_from(zend_object *obj, SDL_GPUDepthStencilState *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "compare_op", &value)) {
			return false;
		}
		out->compare_op = (SDL_GPUCompareOp) value;
	}
	{
		zend_object *child;
		if (!sdl3_prop_object(obj, "back_stencil_state", sdl3_ce_SDL_GPUStencilOpState, &child)) {
			return false;
		}
		if (!sdl3_SDL_GPUStencilOpState_from(child, &out->back_stencil_state, scratch)) {
			return false;
		}
	}
	{
		zend_object *child;
		if (!sdl3_prop_object(obj, "front_stencil_state", sdl3_ce_SDL_GPUStencilOpState, &child)) {
			return false;
		}
		if (!sdl3_SDL_GPUStencilOpState_from(child, &out->front_stencil_state, scratch)) {
			return false;
		}
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "compare_mask", &value)) {
			return false;
		}
		out->compare_mask = (Uint8) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "write_mask", &value)) {
			return false;
		}
		out->write_mask = (Uint8) value;
	}
	if (!sdl3_prop_bool(obj, "enable_depth_test", &out->enable_depth_test)) {
		return false;
	}
	if (!sdl3_prop_bool(obj, "enable_depth_write", &out->enable_depth_write)) {
		return false;
	}
	if (!sdl3_prop_bool(obj, "enable_stencil_test", &out->enable_stencil_test)) {
		return false;
	}
	return true;
}

bool sdl3_SDL_GPUColorTargetBlendState_from(zend_object *obj, SDL_GPUColorTargetBlendState *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "src_color_blendfactor", &value)) {
			return false;
		}
		out->src_color_blendfactor = (SDL_GPUBlendFactor) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "dst_color_blendfactor", &value)) {
			return false;
		}
		out->dst_color_blendfactor = (SDL_GPUBlendFactor) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "color_blend_op", &value)) {
			return false;
		}
		out->color_blend_op = (SDL_GPUBlendOp) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "src_alpha_blendfactor", &value)) {
			return false;
		}
		out->src_alpha_blendfactor = (SDL_GPUBlendFactor) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "dst_alpha_blendfactor", &value)) {
			return false;
		}
		out->dst_alpha_blendfactor = (SDL_GPUBlendFactor) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "alpha_blend_op", &value)) {
			return false;
		}
		out->alpha_blend_op = (SDL_GPUBlendOp) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "color_write_mask", &value)) {
			return false;
		}
		out->color_write_mask = (SDL_GPUColorComponentFlags) value;
	}
	if (!sdl3_prop_bool(obj, "enable_blend", &out->enable_blend)) {
		return false;
	}
	if (!sdl3_prop_bool(obj, "enable_color_write_mask", &out->enable_color_write_mask)) {
		return false;
	}
	return true;
}

bool sdl3_SDL_GPUColorTargetDescription_from(zend_object *obj, SDL_GPUColorTargetDescription *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "format", &value)) {
			return false;
		}
		out->format = (SDL_GPUTextureFormat) value;
	}
	{
		zend_object *child;
		if (!sdl3_prop_object(obj, "blend_state", sdl3_ce_SDL_GPUColorTargetBlendState, &child)) {
			return false;
		}
		if (!sdl3_SDL_GPUColorTargetBlendState_from(child, &out->blend_state, scratch)) {
			return false;
		}
	}
	return true;
}

bool sdl3_SDL_GPUGraphicsPipelineTargetInfo_from(zend_object *obj, SDL_GPUGraphicsPipelineTargetInfo *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	{
		zend_object **items = NULL;
		uint32_t count = 0;
		if (!sdl3_prop_list(obj, "color_target_descriptions", sdl3_ce_SDL_GPUColorTargetDescription, &items, &count, scratch)) {
			return false;
		}
		if (count == 0) {
			out->color_target_descriptions = NULL;
			out->num_color_targets = 0;
		} else {
			SDL_GPUColorTargetDescription *native = sdl3_scratch_alloc(scratch, sizeof(SDL_GPUColorTargetDescription) * count);
			uint32_t i;
			for (i = 0; i < count; i++) {
				if (!sdl3_SDL_GPUColorTargetDescription_from(items[i], &native[i], scratch)) {
					return false;
				}
			}
			out->color_target_descriptions = native;
			out->num_color_targets = count;
		}
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "depth_stencil_format", &value)) {
			return false;
		}
		out->depth_stencil_format = (SDL_GPUTextureFormat) value;
	}
	if (!sdl3_prop_bool(obj, "has_depth_stencil_target", &out->has_depth_stencil_target)) {
		return false;
	}
	return true;
}

bool sdl3_SDL_GPUGraphicsPipelineCreateInfo_from(zend_object *obj, SDL_GPUGraphicsPipelineCreateInfo *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	{
		void *ptr;
		if (!sdl3_prop_handle(obj, "vertex_shader", sdl3_ce_SDL_GPUShader, &ptr)) {
			return false;
		}
		out->vertex_shader = (SDL_GPUShader *) ptr;
	}
	{
		void *ptr;
		if (!sdl3_prop_handle(obj, "fragment_shader", sdl3_ce_SDL_GPUShader, &ptr)) {
			return false;
		}
		out->fragment_shader = (SDL_GPUShader *) ptr;
	}
	{
		zend_object *child;
		if (!sdl3_prop_object(obj, "vertex_input_state", sdl3_ce_SDL_GPUVertexInputState, &child)) {
			return false;
		}
		if (!sdl3_SDL_GPUVertexInputState_from(child, &out->vertex_input_state, scratch)) {
			return false;
		}
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "primitive_type", &value)) {
			return false;
		}
		out->primitive_type = (SDL_GPUPrimitiveType) value;
	}
	{
		zend_object *child;
		if (!sdl3_prop_object(obj, "rasterizer_state", sdl3_ce_SDL_GPURasterizerState, &child)) {
			return false;
		}
		if (!sdl3_SDL_GPURasterizerState_from(child, &out->rasterizer_state, scratch)) {
			return false;
		}
	}
	{
		zend_object *child;
		if (!sdl3_prop_object(obj, "multisample_state", sdl3_ce_SDL_GPUMultisampleState, &child)) {
			return false;
		}
		if (!sdl3_SDL_GPUMultisampleState_from(child, &out->multisample_state, scratch)) {
			return false;
		}
	}
	{
		zend_object *child;
		if (!sdl3_prop_object(obj, "depth_stencil_state", sdl3_ce_SDL_GPUDepthStencilState, &child)) {
			return false;
		}
		if (!sdl3_SDL_GPUDepthStencilState_from(child, &out->depth_stencil_state, scratch)) {
			return false;
		}
	}
	{
		zend_object *child;
		if (!sdl3_prop_object(obj, "target_info", sdl3_ce_SDL_GPUGraphicsPipelineTargetInfo, &child)) {
			return false;
		}
		if (!sdl3_SDL_GPUGraphicsPipelineTargetInfo_from(child, &out->target_info, scratch)) {
			return false;
		}
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "props", &value)) {
			return false;
		}
		out->props = (SDL_PropertiesID) value;
	}
	return true;
}

bool sdl3_SDL_GPUTextureCreateInfo_from(zend_object *obj, SDL_GPUTextureCreateInfo *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "type", &value)) {
			return false;
		}
		out->type = (SDL_GPUTextureType) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "format", &value)) {
			return false;
		}
		out->format = (SDL_GPUTextureFormat) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "usage", &value)) {
			return false;
		}
		out->usage = (SDL_GPUTextureUsageFlags) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "width", &value)) {
			return false;
		}
		out->width = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "height", &value)) {
			return false;
		}
		out->height = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "layer_count_or_depth", &value)) {
			return false;
		}
		out->layer_count_or_depth = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "num_levels", &value)) {
			return false;
		}
		out->num_levels = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "sample_count", &value)) {
			return false;
		}
		out->sample_count = (SDL_GPUSampleCount) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "props", &value)) {
			return false;
		}
		out->props = (SDL_PropertiesID) value;
	}
	return true;
}

bool sdl3_SDL_GPUSamplerCreateInfo_from(zend_object *obj, SDL_GPUSamplerCreateInfo *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "min_filter", &value)) {
			return false;
		}
		out->min_filter = (SDL_GPUFilter) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "mag_filter", &value)) {
			return false;
		}
		out->mag_filter = (SDL_GPUFilter) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "mipmap_mode", &value)) {
			return false;
		}
		out->mipmap_mode = (SDL_GPUSamplerMipmapMode) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "address_mode_u", &value)) {
			return false;
		}
		out->address_mode_u = (SDL_GPUSamplerAddressMode) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "address_mode_v", &value)) {
			return false;
		}
		out->address_mode_v = (SDL_GPUSamplerAddressMode) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "address_mode_w", &value)) {
			return false;
		}
		out->address_mode_w = (SDL_GPUSamplerAddressMode) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "mip_lod_bias", &value)) {
			return false;
		}
		out->mip_lod_bias = (float) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "max_anisotropy", &value)) {
			return false;
		}
		out->max_anisotropy = (float) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "compare_op", &value)) {
			return false;
		}
		out->compare_op = (SDL_GPUCompareOp) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "min_lod", &value)) {
			return false;
		}
		out->min_lod = (float) value;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "max_lod", &value)) {
			return false;
		}
		out->max_lod = (float) value;
	}
	if (!sdl3_prop_bool(obj, "enable_anisotropy", &out->enable_anisotropy)) {
		return false;
	}
	if (!sdl3_prop_bool(obj, "enable_compare", &out->enable_compare)) {
		return false;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "props", &value)) {
			return false;
		}
		out->props = (SDL_PropertiesID) value;
	}
	return true;
}

bool sdl3_SDL_GPUBufferCreateInfo_from(zend_object *obj, SDL_GPUBufferCreateInfo *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "usage", &value)) {
			return false;
		}
		out->usage = (SDL_GPUBufferUsageFlags) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "size", &value)) {
			return false;
		}
		out->size = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "props", &value)) {
			return false;
		}
		out->props = (SDL_PropertiesID) value;
	}
	return true;
}

bool sdl3_SDL_GPUTransferBufferCreateInfo_from(zend_object *obj, SDL_GPUTransferBufferCreateInfo *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "usage", &value)) {
			return false;
		}
		out->usage = (SDL_GPUTransferBufferUsage) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "size", &value)) {
			return false;
		}
		out->size = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "props", &value)) {
			return false;
		}
		out->props = (SDL_PropertiesID) value;
	}
	return true;
}

bool sdl3_SDL_GPUTextureTransferInfo_from(zend_object *obj, SDL_GPUTextureTransferInfo *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		void *ptr;
		if (!sdl3_prop_handle(obj, "transfer_buffer", sdl3_ce_SDL_GPUTransferBuffer, &ptr)) {
			return false;
		}
		out->transfer_buffer = (SDL_GPUTransferBuffer *) ptr;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "offset", &value)) {
			return false;
		}
		out->offset = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "pixels_per_row", &value)) {
			return false;
		}
		out->pixels_per_row = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "rows_per_layer", &value)) {
			return false;
		}
		out->rows_per_layer = (Uint32) value;
	}
	return true;
}

bool sdl3_SDL_GPUTransferBufferLocation_from(zend_object *obj, SDL_GPUTransferBufferLocation *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		void *ptr;
		if (!sdl3_prop_handle(obj, "transfer_buffer", sdl3_ce_SDL_GPUTransferBuffer, &ptr)) {
			return false;
		}
		out->transfer_buffer = (SDL_GPUTransferBuffer *) ptr;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "offset", &value)) {
			return false;
		}
		out->offset = (Uint32) value;
	}
	return true;
}

bool sdl3_SDL_GPUTextureRegion_from(zend_object *obj, SDL_GPUTextureRegion *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		void *ptr;
		if (!sdl3_prop_handle(obj, "texture", sdl3_ce_SDL_GPUTexture, &ptr)) {
			return false;
		}
		out->texture = (SDL_GPUTexture *) ptr;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "mip_level", &value)) {
			return false;
		}
		out->mip_level = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "layer", &value)) {
			return false;
		}
		out->layer = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "x", &value)) {
			return false;
		}
		out->x = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "y", &value)) {
			return false;
		}
		out->y = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "z", &value)) {
			return false;
		}
		out->z = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "w", &value)) {
			return false;
		}
		out->w = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "h", &value)) {
			return false;
		}
		out->h = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "d", &value)) {
			return false;
		}
		out->d = (Uint32) value;
	}
	return true;
}

bool sdl3_SDL_GPUBufferRegion_from(zend_object *obj, SDL_GPUBufferRegion *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		void *ptr;
		if (!sdl3_prop_handle(obj, "buffer", sdl3_ce_SDL_GPUBuffer, &ptr)) {
			return false;
		}
		out->buffer = (SDL_GPUBuffer *) ptr;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "offset", &value)) {
			return false;
		}
		out->offset = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "size", &value)) {
			return false;
		}
		out->size = (Uint32) value;
	}
	return true;
}

bool sdl3_SDL_GPUBlitRegion_from(zend_object *obj, SDL_GPUBlitRegion *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		void *ptr;
		if (!sdl3_prop_handle(obj, "texture", sdl3_ce_SDL_GPUTexture, &ptr)) {
			return false;
		}
		out->texture = (SDL_GPUTexture *) ptr;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "mip_level", &value)) {
			return false;
		}
		out->mip_level = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "layer_or_depth_plane", &value)) {
			return false;
		}
		out->layer_or_depth_plane = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "x", &value)) {
			return false;
		}
		out->x = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "y", &value)) {
			return false;
		}
		out->y = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "w", &value)) {
			return false;
		}
		out->w = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "h", &value)) {
			return false;
		}
		out->h = (Uint32) value;
	}
	return true;
}

bool sdl3_SDL_GPUColorTargetInfo_from(zend_object *obj, SDL_GPUColorTargetInfo *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	{
		void *ptr;
		if (!sdl3_prop_handle(obj, "texture", sdl3_ce_SDL_GPUTexture, &ptr)) {
			return false;
		}
		out->texture = (SDL_GPUTexture *) ptr;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "mip_level", &value)) {
			return false;
		}
		out->mip_level = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "layer_or_depth_plane", &value)) {
			return false;
		}
		out->layer_or_depth_plane = (Uint32) value;
	}
	{
		zend_object *child;
		if (!sdl3_prop_object(obj, "clear_color", sdl3_ce_SDL_FColor, &child)) {
			return false;
		}
		if (!sdl3_SDL_FColor_from(child, &out->clear_color, scratch)) {
			return false;
		}
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "load_op", &value)) {
			return false;
		}
		out->load_op = (SDL_GPULoadOp) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "store_op", &value)) {
			return false;
		}
		out->store_op = (SDL_GPUStoreOp) value;
	}
	{
		void *ptr;
		if (!sdl3_prop_handle(obj, "resolve_texture", sdl3_ce_SDL_GPUTexture, &ptr)) {
			return false;
		}
		out->resolve_texture = (SDL_GPUTexture *) ptr;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "resolve_mip_level", &value)) {
			return false;
		}
		out->resolve_mip_level = (Uint32) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "resolve_layer", &value)) {
			return false;
		}
		out->resolve_layer = (Uint32) value;
	}
	if (!sdl3_prop_bool(obj, "cycle", &out->cycle)) {
		return false;
	}
	if (!sdl3_prop_bool(obj, "cycle_resolve_texture", &out->cycle_resolve_texture)) {
		return false;
	}
	return true;
}

bool sdl3_SDL_GPUDepthStencilTargetInfo_from(zend_object *obj, SDL_GPUDepthStencilTargetInfo *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		void *ptr;
		if (!sdl3_prop_handle(obj, "texture", sdl3_ce_SDL_GPUTexture, &ptr)) {
			return false;
		}
		out->texture = (SDL_GPUTexture *) ptr;
	}
	{
		double value;
		if (!sdl3_prop_double(obj, "clear_depth", &value)) {
			return false;
		}
		out->clear_depth = (float) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "load_op", &value)) {
			return false;
		}
		out->load_op = (SDL_GPULoadOp) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "store_op", &value)) {
			return false;
		}
		out->store_op = (SDL_GPUStoreOp) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "stencil_load_op", &value)) {
			return false;
		}
		out->stencil_load_op = (SDL_GPULoadOp) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "stencil_store_op", &value)) {
			return false;
		}
		out->stencil_store_op = (SDL_GPUStoreOp) value;
	}
	if (!sdl3_prop_bool(obj, "cycle", &out->cycle)) {
		return false;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "clear_stencil", &value)) {
			return false;
		}
		out->clear_stencil = (Uint8) value;
	}
	return true;
}

bool sdl3_SDL_GPUBufferBinding_from(zend_object *obj, SDL_GPUBufferBinding *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		void *ptr;
		if (!sdl3_prop_handle(obj, "buffer", sdl3_ce_SDL_GPUBuffer, &ptr)) {
			return false;
		}
		out->buffer = (SDL_GPUBuffer *) ptr;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "offset", &value)) {
			return false;
		}
		out->offset = (Uint32) value;
	}
	return true;
}

bool sdl3_SDL_GPUTextureSamplerBinding_from(zend_object *obj, SDL_GPUTextureSamplerBinding *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	(void) scratch;
	{
		void *ptr;
		if (!sdl3_prop_handle(obj, "texture", sdl3_ce_SDL_GPUTexture, &ptr)) {
			return false;
		}
		out->texture = (SDL_GPUTexture *) ptr;
	}
	{
		void *ptr;
		if (!sdl3_prop_handle(obj, "sampler", sdl3_ce_SDL_GPUSampler, &ptr)) {
			return false;
		}
		out->sampler = (SDL_GPUSampler *) ptr;
	}
	return true;
}

bool sdl3_SDL_GPUBlitInfo_from(zend_object *obj, SDL_GPUBlitInfo *out, sdl3_scratch *scratch)
{
	memset(out, 0, sizeof(*out));
	{
		zend_object *child;
		if (!sdl3_prop_object(obj, "source", sdl3_ce_SDL_GPUBlitRegion, &child)) {
			return false;
		}
		if (!sdl3_SDL_GPUBlitRegion_from(child, &out->source, scratch)) {
			return false;
		}
	}
	{
		zend_object *child;
		if (!sdl3_prop_object(obj, "destination", sdl3_ce_SDL_GPUBlitRegion, &child)) {
			return false;
		}
		if (!sdl3_SDL_GPUBlitRegion_from(child, &out->destination, scratch)) {
			return false;
		}
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "load_op", &value)) {
			return false;
		}
		out->load_op = (SDL_GPULoadOp) value;
	}
	{
		zend_object *child;
		if (!sdl3_prop_object(obj, "clear_color", sdl3_ce_SDL_FColor, &child)) {
			return false;
		}
		if (!sdl3_SDL_FColor_from(child, &out->clear_color, scratch)) {
			return false;
		}
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "flip_mode", &value)) {
			return false;
		}
		out->flip_mode = (SDL_FlipMode) value;
	}
	{
		zend_long value;
		if (!sdl3_prop_long(obj, "filter", &value)) {
			return false;
		}
		out->filter = (SDL_GPUFilter) value;
	}
	if (!sdl3_prop_bool(obj, "cycle", &out->cycle)) {
		return false;
	}
	return true;
}

ZEND_METHOD(SDL_GPUDepthStencilState, __construct)
{
	ZEND_PARSE_PARAMETERS_NONE();
	sdl3_init_nested(Z_OBJ_P(ZEND_THIS), "back_stencil_state", sdl3_ce_SDL_GPUStencilOpState);
	sdl3_init_nested(Z_OBJ_P(ZEND_THIS), "front_stencil_state", sdl3_ce_SDL_GPUStencilOpState);
}

ZEND_METHOD(SDL_GPUColorTargetDescription, __construct)
{
	ZEND_PARSE_PARAMETERS_NONE();
	sdl3_init_nested(Z_OBJ_P(ZEND_THIS), "blend_state", sdl3_ce_SDL_GPUColorTargetBlendState);
}

ZEND_METHOD(SDL_GPUGraphicsPipelineCreateInfo, __construct)
{
	ZEND_PARSE_PARAMETERS_NONE();
	sdl3_init_nested(Z_OBJ_P(ZEND_THIS), "vertex_input_state", sdl3_ce_SDL_GPUVertexInputState);
	sdl3_init_nested(Z_OBJ_P(ZEND_THIS), "rasterizer_state", sdl3_ce_SDL_GPURasterizerState);
	sdl3_init_nested(Z_OBJ_P(ZEND_THIS), "multisample_state", sdl3_ce_SDL_GPUMultisampleState);
	sdl3_init_nested(Z_OBJ_P(ZEND_THIS), "depth_stencil_state", sdl3_ce_SDL_GPUDepthStencilState);
	sdl3_init_nested(Z_OBJ_P(ZEND_THIS), "target_info", sdl3_ce_SDL_GPUGraphicsPipelineTargetInfo);
}

ZEND_METHOD(SDL_GPUColorTargetInfo, __construct)
{
	ZEND_PARSE_PARAMETERS_NONE();
	sdl3_init_nested(Z_OBJ_P(ZEND_THIS), "clear_color", sdl3_ce_SDL_FColor);
}

ZEND_METHOD(SDL_GPUBlitInfo, __construct)
{
	ZEND_PARSE_PARAMETERS_NONE();
	sdl3_init_nested(Z_OBJ_P(ZEND_THIS), "source", sdl3_ce_SDL_GPUBlitRegion);
	sdl3_init_nested(Z_OBJ_P(ZEND_THIS), "destination", sdl3_ce_SDL_GPUBlitRegion);
	sdl3_init_nested(Z_OBJ_P(ZEND_THIS), "clear_color", sdl3_ce_SDL_FColor);
}

void sdl3_register_SDL_gpu_types(int module_number)
{
	register_SDL_gpu_types_symbols(module_number);

	sdl3_ce_SDL_GPUShader = register_class_SDL_GPUShader();
	sdl3_handle_setup(sdl3_ce_SDL_GPUShader);
	sdl3_ce_SDL_GPUTexture = register_class_SDL_GPUTexture();
	sdl3_handle_setup(sdl3_ce_SDL_GPUTexture);
	sdl3_ce_SDL_GPUBuffer = register_class_SDL_GPUBuffer();
	sdl3_handle_setup(sdl3_ce_SDL_GPUBuffer);
	sdl3_ce_SDL_GPUTransferBuffer = register_class_SDL_GPUTransferBuffer();
	sdl3_handle_setup(sdl3_ce_SDL_GPUTransferBuffer);
	sdl3_ce_SDL_GPUSampler = register_class_SDL_GPUSampler();
	sdl3_handle_setup(sdl3_ce_SDL_GPUSampler);
	sdl3_ce_SDL_FColor = register_class_SDL_FColor();
	sdl3_struct_setup(sdl3_ce_SDL_FColor);
	sdl3_ce_SDL_GPUViewport = register_class_SDL_GPUViewport();
	sdl3_struct_setup(sdl3_ce_SDL_GPUViewport);
	sdl3_ce_SDL_GPUShaderCreateInfo = register_class_SDL_GPUShaderCreateInfo();
	sdl3_struct_setup(sdl3_ce_SDL_GPUShaderCreateInfo);
	sdl3_ce_SDL_GPUVertexBufferDescription = register_class_SDL_GPUVertexBufferDescription();
	sdl3_struct_setup(sdl3_ce_SDL_GPUVertexBufferDescription);
	sdl3_ce_SDL_GPUVertexAttribute = register_class_SDL_GPUVertexAttribute();
	sdl3_struct_setup(sdl3_ce_SDL_GPUVertexAttribute);
	sdl3_ce_SDL_GPUVertexInputState = register_class_SDL_GPUVertexInputState();
	sdl3_struct_setup(sdl3_ce_SDL_GPUVertexInputState);
	sdl3_ce_SDL_GPUStencilOpState = register_class_SDL_GPUStencilOpState();
	sdl3_struct_setup(sdl3_ce_SDL_GPUStencilOpState);
	sdl3_ce_SDL_GPURasterizerState = register_class_SDL_GPURasterizerState();
	sdl3_struct_setup(sdl3_ce_SDL_GPURasterizerState);
	sdl3_ce_SDL_GPUMultisampleState = register_class_SDL_GPUMultisampleState();
	sdl3_struct_setup(sdl3_ce_SDL_GPUMultisampleState);
	sdl3_ce_SDL_GPUDepthStencilState = register_class_SDL_GPUDepthStencilState();
	sdl3_struct_setup(sdl3_ce_SDL_GPUDepthStencilState);
	sdl3_ce_SDL_GPUColorTargetBlendState = register_class_SDL_GPUColorTargetBlendState();
	sdl3_struct_setup(sdl3_ce_SDL_GPUColorTargetBlendState);
	sdl3_ce_SDL_GPUColorTargetDescription = register_class_SDL_GPUColorTargetDescription();
	sdl3_struct_setup(sdl3_ce_SDL_GPUColorTargetDescription);
	sdl3_ce_SDL_GPUGraphicsPipelineTargetInfo = register_class_SDL_GPUGraphicsPipelineTargetInfo();
	sdl3_struct_setup(sdl3_ce_SDL_GPUGraphicsPipelineTargetInfo);
	sdl3_ce_SDL_GPUGraphicsPipelineCreateInfo = register_class_SDL_GPUGraphicsPipelineCreateInfo();
	sdl3_struct_setup(sdl3_ce_SDL_GPUGraphicsPipelineCreateInfo);
	sdl3_ce_SDL_GPUTextureCreateInfo = register_class_SDL_GPUTextureCreateInfo();
	sdl3_struct_setup(sdl3_ce_SDL_GPUTextureCreateInfo);
	sdl3_ce_SDL_GPUSamplerCreateInfo = register_class_SDL_GPUSamplerCreateInfo();
	sdl3_struct_setup(sdl3_ce_SDL_GPUSamplerCreateInfo);
	sdl3_ce_SDL_GPUBufferCreateInfo = register_class_SDL_GPUBufferCreateInfo();
	sdl3_struct_setup(sdl3_ce_SDL_GPUBufferCreateInfo);
	sdl3_ce_SDL_GPUTransferBufferCreateInfo = register_class_SDL_GPUTransferBufferCreateInfo();
	sdl3_struct_setup(sdl3_ce_SDL_GPUTransferBufferCreateInfo);
	sdl3_ce_SDL_GPUTextureTransferInfo = register_class_SDL_GPUTextureTransferInfo();
	sdl3_struct_setup(sdl3_ce_SDL_GPUTextureTransferInfo);
	sdl3_ce_SDL_GPUTransferBufferLocation = register_class_SDL_GPUTransferBufferLocation();
	sdl3_struct_setup(sdl3_ce_SDL_GPUTransferBufferLocation);
	sdl3_ce_SDL_GPUTextureRegion = register_class_SDL_GPUTextureRegion();
	sdl3_struct_setup(sdl3_ce_SDL_GPUTextureRegion);
	sdl3_ce_SDL_GPUBufferRegion = register_class_SDL_GPUBufferRegion();
	sdl3_struct_setup(sdl3_ce_SDL_GPUBufferRegion);
	sdl3_ce_SDL_GPUBlitRegion = register_class_SDL_GPUBlitRegion();
	sdl3_struct_setup(sdl3_ce_SDL_GPUBlitRegion);
	sdl3_ce_SDL_GPUColorTargetInfo = register_class_SDL_GPUColorTargetInfo();
	sdl3_struct_setup(sdl3_ce_SDL_GPUColorTargetInfo);
	sdl3_ce_SDL_GPUDepthStencilTargetInfo = register_class_SDL_GPUDepthStencilTargetInfo();
	sdl3_struct_setup(sdl3_ce_SDL_GPUDepthStencilTargetInfo);
	sdl3_ce_SDL_GPUBufferBinding = register_class_SDL_GPUBufferBinding();
	sdl3_struct_setup(sdl3_ce_SDL_GPUBufferBinding);
	sdl3_ce_SDL_GPUTextureSamplerBinding = register_class_SDL_GPUTextureSamplerBinding();
	sdl3_struct_setup(sdl3_ce_SDL_GPUTextureSamplerBinding);
	sdl3_ce_SDL_GPUBlitInfo = register_class_SDL_GPUBlitInfo();
	sdl3_struct_setup(sdl3_ce_SDL_GPUBlitInfo);
}
