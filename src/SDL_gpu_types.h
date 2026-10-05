#ifndef SDL3_GPU_TYPES_H
#define SDL3_GPU_TYPES_H

#include "runtime.h"

extern zend_class_entry *sdl3_ce_SDL_GPUShader;
extern zend_class_entry *sdl3_ce_SDL_GPUTexture;
extern zend_class_entry *sdl3_ce_SDL_GPUBuffer;
extern zend_class_entry *sdl3_ce_SDL_GPUTransferBuffer;
extern zend_class_entry *sdl3_ce_SDL_GPUSampler;
extern zend_class_entry *sdl3_ce_SDL_FColor;
extern zend_class_entry *sdl3_ce_SDL_GPUViewport;
extern zend_class_entry *sdl3_ce_SDL_GPUShaderCreateInfo;
extern zend_class_entry *sdl3_ce_SDL_GPUVertexBufferDescription;
extern zend_class_entry *sdl3_ce_SDL_GPUVertexAttribute;
extern zend_class_entry *sdl3_ce_SDL_GPUVertexInputState;
extern zend_class_entry *sdl3_ce_SDL_GPUStencilOpState;
extern zend_class_entry *sdl3_ce_SDL_GPURasterizerState;
extern zend_class_entry *sdl3_ce_SDL_GPUMultisampleState;
extern zend_class_entry *sdl3_ce_SDL_GPUDepthStencilState;
extern zend_class_entry *sdl3_ce_SDL_GPUColorTargetBlendState;
extern zend_class_entry *sdl3_ce_SDL_GPUColorTargetDescription;
extern zend_class_entry *sdl3_ce_SDL_GPUGraphicsPipelineTargetInfo;
extern zend_class_entry *sdl3_ce_SDL_GPUGraphicsPipelineCreateInfo;
extern zend_class_entry *sdl3_ce_SDL_GPUTextureCreateInfo;
extern zend_class_entry *sdl3_ce_SDL_GPUSamplerCreateInfo;
extern zend_class_entry *sdl3_ce_SDL_GPUBufferCreateInfo;
extern zend_class_entry *sdl3_ce_SDL_GPUTransferBufferCreateInfo;
extern zend_class_entry *sdl3_ce_SDL_GPUTextureTransferInfo;
extern zend_class_entry *sdl3_ce_SDL_GPUTransferBufferLocation;
extern zend_class_entry *sdl3_ce_SDL_GPUTextureRegion;
extern zend_class_entry *sdl3_ce_SDL_GPUBufferRegion;
extern zend_class_entry *sdl3_ce_SDL_GPUBlitRegion;
extern zend_class_entry *sdl3_ce_SDL_GPUColorTargetInfo;
extern zend_class_entry *sdl3_ce_SDL_GPUDepthStencilTargetInfo;
extern zend_class_entry *sdl3_ce_SDL_GPUBufferBinding;
extern zend_class_entry *sdl3_ce_SDL_GPUTextureSamplerBinding;
extern zend_class_entry *sdl3_ce_SDL_GPUBlitInfo;

bool sdl3_SDL_FColor_from(zend_object *obj, SDL_FColor *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUViewport_from(zend_object *obj, SDL_GPUViewport *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUShaderCreateInfo_from(zend_object *obj, SDL_GPUShaderCreateInfo *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUVertexBufferDescription_from(zend_object *obj, SDL_GPUVertexBufferDescription *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUVertexAttribute_from(zend_object *obj, SDL_GPUVertexAttribute *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUVertexInputState_from(zend_object *obj, SDL_GPUVertexInputState *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUStencilOpState_from(zend_object *obj, SDL_GPUStencilOpState *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPURasterizerState_from(zend_object *obj, SDL_GPURasterizerState *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUMultisampleState_from(zend_object *obj, SDL_GPUMultisampleState *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUDepthStencilState_from(zend_object *obj, SDL_GPUDepthStencilState *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUColorTargetBlendState_from(zend_object *obj, SDL_GPUColorTargetBlendState *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUColorTargetDescription_from(zend_object *obj, SDL_GPUColorTargetDescription *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUGraphicsPipelineTargetInfo_from(zend_object *obj, SDL_GPUGraphicsPipelineTargetInfo *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUGraphicsPipelineCreateInfo_from(zend_object *obj, SDL_GPUGraphicsPipelineCreateInfo *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUTextureCreateInfo_from(zend_object *obj, SDL_GPUTextureCreateInfo *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUSamplerCreateInfo_from(zend_object *obj, SDL_GPUSamplerCreateInfo *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUBufferCreateInfo_from(zend_object *obj, SDL_GPUBufferCreateInfo *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUTransferBufferCreateInfo_from(zend_object *obj, SDL_GPUTransferBufferCreateInfo *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUTextureTransferInfo_from(zend_object *obj, SDL_GPUTextureTransferInfo *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUTransferBufferLocation_from(zend_object *obj, SDL_GPUTransferBufferLocation *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUTextureRegion_from(zend_object *obj, SDL_GPUTextureRegion *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUBufferRegion_from(zend_object *obj, SDL_GPUBufferRegion *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUBlitRegion_from(zend_object *obj, SDL_GPUBlitRegion *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUColorTargetInfo_from(zend_object *obj, SDL_GPUColorTargetInfo *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUDepthStencilTargetInfo_from(zend_object *obj, SDL_GPUDepthStencilTargetInfo *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUBufferBinding_from(zend_object *obj, SDL_GPUBufferBinding *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUTextureSamplerBinding_from(zend_object *obj, SDL_GPUTextureSamplerBinding *out, sdl3_scratch *scratch);
bool sdl3_SDL_GPUBlitInfo_from(zend_object *obj, SDL_GPUBlitInfo *out, sdl3_scratch *scratch);

void sdl3_register_SDL_gpu_types(int module_number);

extern zend_class_entry *sdl3_ce_SDL_GPUDevice;
extern zend_class_entry *sdl3_ce_SDL_GPUCommandBuffer;
extern zend_class_entry *sdl3_ce_SDL_GPUCopyPass;
extern zend_class_entry *sdl3_ce_SDL_GPUFence;
extern zend_class_entry *sdl3_ce_SDL_GPUGraphicsPipeline;
extern zend_class_entry *sdl3_ce_SDL_GPURenderPass;

void sdl3_register_SDL_gpu(int module_number);

#endif
