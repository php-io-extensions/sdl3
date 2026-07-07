<?php
/**
 * sdl3 extension — SDL GPU proof script (WP9)
 *
 * Metal smoke test: creates a GPU device, round-trips data through GPU
 * buffers via transfer buffers and copy passes, renders a red triangle to an
 * offscreen texture with runtime-compiled MSL shaders and reads the pixels
 * back, dispatches a compute kernel, blits, generates mipmaps, exercises the
 * fence and swapchain APIs, and drives the GPU render-state API from
 * SDL_render.h.
 *
 * Skips gracefully (exit 0) when no GPU driver is available.
 *
 * Usage:
 *   php examples/proof_gpu.php
 */

declare(strict_types=1);

use Sdl3\SDL\SDL;
use Sdl3\SDL\SDLError;
use Sdl3\SDL\Gpu\SDLGPU;
use Sdl3\SDL\Render\SDLRender;
use Sdl3\SDL\Video\SDLVideo;

const SDL_INIT_VIDEO = 0x00000020;
const SDL_WINDOW_HIDDEN = 0x00000008;

const SDL_GPU_SHADERFORMAT_MSL = 1 << 4;
const SDL_GPU_SHADERFORMAT_METALLIB = 1 << 5;

const SDL_GPU_BUFFERUSAGE_VERTEX = 1 << 0;
const SDL_GPU_BUFFERUSAGE_INDEX = 1 << 1;
const SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_WRITE = 1 << 5;

const SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD = 0;
const SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD = 1;

const SDL_GPU_TEXTURETYPE_2D = 0;
const SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM = 4;
const SDL_GPU_TEXTUREUSAGE_SAMPLER = 1 << 0;
const SDL_GPU_TEXTUREUSAGE_COLOR_TARGET = 1 << 1;
const SDL_GPU_SAMPLECOUNT_1 = 0;

const SDL_GPU_LOADOP_LOAD = 0;
const SDL_GPU_LOADOP_CLEAR = 1;
const SDL_GPU_STOREOP_STORE = 0;

const SDL_GPU_PRIMITIVETYPE_TRIANGLELIST = 0;
const SDL_GPU_SHADERSTAGE_VERTEX = 0;
const SDL_GPU_SHADERSTAGE_FRAGMENT = 1;

const SDL_GPU_FILTER_LINEAR = 1;

const SDL_GPU_PRESENTMODE_VSYNC = 0;
const SDL_GPU_SWAPCHAINCOMPOSITION_SDR = 0;

const SDL_PIXELFORMAT_ABGR8888 = 376840196;

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

function skip(string $label, string $detail = ''): void
{
    $msg = "  [SKIP] {$label}";
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

$errors = 0;

section('Extension check');
if (!extension_loaded('sdl3')) {
    echo "  [FATAL] sdl3 extension is NOT loaded. Aborting.\n";
    exit(1);
}
pass('sdl3 extension is loaded');

section('SDL_Init(SDL_INIT_VIDEO)');
if (!SDL::SDLInit(SDL_INIT_VIDEO)) {
    skip('SDL_Init failed (headless?)', sdl_err());
    exit(0);
}
pass('SDL_Init succeeded');

section('Format queries (no device needed)');
$blockSize = SDLGPU::SDLGPUTextureFormatTexelBlockSize(SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM);
if ($blockSize === 4) {
    pass("Texel block size of RGBA8 = {$blockSize}");
} else {
    fail('SDLGPUTextureFormatTexelBlockSize', "expected 4, got {$blockSize}");
    $errors++;
}

$size = SDLGPU::SDLCalculateGPUTextureFormatSize(SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM, 64, 64, 1);
if ($size === 64 * 64 * 4) {
    pass("Calculated 64x64 RGBA8 size = {$size}");
} else {
    fail('SDLCalculateGPUTextureFormatSize', "expected 16384, got {$size}");
    $errors++;
}

$pixelFormat = SDLGPU::SDLGetPixelFormatFromGPUTextureFormat(SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM);
$roundTrip = SDLGPU::SDLGetGPUTextureFormatFromPixelFormat($pixelFormat);
if ($roundTrip === SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM) {
    pass("Pixel format round trip RGBA8 -> {$pixelFormat} -> {$roundTrip}");
} else {
    fail('Pixel format round trip', "got {$roundTrip}");
    $errors++;
}

section('Driver enumeration');
$numDrivers = SDLGPU::SDLGetNumGPUDrivers();
pass("SDLGetNumGPUDrivers = {$numDrivers}");
for ($i = 0; $i < $numDrivers; $i++) {
    $name = SDLGPU::SDLGetGPUDriver($i);
    pass("  driver[{$i}] = {$name}");
}

$mslSupported = SDLGPU::SDLGPUSupportsShaderFormats(SDL_GPU_SHADERFORMAT_MSL, null);
pass('SDLGPUSupportsShaderFormats(MSL) = ' . ($mslSupported ? 'true' : 'false'));

section('Device creation');
try {
    $device = SDLGPU::SDLCreateGPUDevice(SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_METALLIB, true, null);
} catch (\RuntimeException $e) {
    skip('No GPU device available', $e->getMessage());
    SDL::SDLQuit();
    exit(0);
}
pass("Created GPU device handle={$device}");

$driver = SDLGPU::SDLGetGPUDeviceDriver($device);
pass("Device driver = {$driver}");

$formats = SDLGPU::SDLGetGPUShaderFormats($device);
pass("Device shader formats bitmask = {$formats}");

$deviceProps = SDLGPU::SDLGetGPUDeviceProperties($device);
if ($deviceProps !== 0) {
    pass("Device properties id = {$deviceProps}");
} else {
    fail('SDLGetGPUDeviceProperties', sdl_err());
    $errors++;
}

if (SDLGPU::SDLSetGPUAllowedFramesInFlight($device, 2)) {
    pass('SDLSetGPUAllowedFramesInFlight(2)');
} else {
    fail('SDLSetGPUAllowedFramesInFlight', sdl_err());
    $errors++;
}

section('Buffer round trip through copy passes');
$payload = '';
for ($i = 0; $i < 256; $i++) {
    $payload .= chr(($i * 3) & 0xFF);
}

$bufSrc = SDLGPU::SDLCreateGPUBuffer($device, ['usage' => SDL_GPU_BUFFERUSAGE_VERTEX, 'size' => 256]);
$bufDst = SDLGPU::SDLCreateGPUBuffer($device, ['usage' => SDL_GPU_BUFFERUSAGE_INDEX, 'size' => 256]);
SDLGPU::SDLSetGPUBufferName($device, $bufSrc, 'proof_src_buffer');
pass("Created GPU buffers src={$bufSrc} dst={$bufDst} (+name set)");

$tbUp = SDLGPU::SDLCreateGPUTransferBuffer($device, ['usage' => SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD, 'size' => 256]);
$tbDown = SDLGPU::SDLCreateGPUTransferBuffer($device, ['usage' => SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD, 'size' => 256]);
pass("Created transfer buffers up={$tbUp} down={$tbDown}");

$mapped = SDLGPU::SDLMapGPUTransferBuffer($device, $tbUp, false);
SDLGPU::SDLUnmapGPUTransferBuffer($device, $tbUp);
if ($mapped !== 0) {
    pass("Raw map/unmap returned mapped address {$mapped}");
} else {
    fail('SDLMapGPUTransferBuffer returned 0');
    $errors++;
}

if (SDLGPU::writeToGPUTransferBuffer($device, $tbUp, $payload, true)) {
    pass('writeToGPUTransferBuffer copied 256-byte payload');
} else {
    fail('writeToGPUTransferBuffer', sdl_err());
    $errors++;
}

$cb = SDLGPU::SDLAcquireGPUCommandBuffer($device);
SDLGPU::SDLPushGPUDebugGroup($cb, 'proof_copy_chain');
SDLGPU::SDLInsertGPUDebugLabel($cb, 'upload+copy+download');
$copyPass = SDLGPU::SDLBeginGPUCopyPass($cb);
SDLGPU::SDLUploadToGPUBuffer($copyPass, ['transfer_buffer' => $tbUp, 'offset' => 0], ['buffer' => $bufSrc, 'offset' => 0, 'size' => 256], false);
SDLGPU::SDLCopyGPUBufferToBuffer($copyPass, ['buffer' => $bufSrc, 'offset' => 0], ['buffer' => $bufDst, 'offset' => 0], 256, false);
SDLGPU::SDLDownloadFromGPUBuffer($copyPass, ['buffer' => $bufDst, 'offset' => 0, 'size' => 256], ['transfer_buffer' => $tbDown, 'offset' => 0]);
SDLGPU::SDLEndGPUCopyPass($copyPass);
SDLGPU::SDLPopGPUDebugGroup($cb);

$fence = SDLGPU::SDLSubmitGPUCommandBufferAndAcquireFence($cb);
pass("Submitted copy chain, fence handle={$fence}");

if (SDLGPU::SDLWaitForGPUFences($device, true, [$fence])) {
    pass('SDLWaitForGPUFences signaled');
} else {
    fail('SDLWaitForGPUFences', sdl_err());
    $errors++;
}
if (SDLGPU::SDLQueryGPUFence($device, $fence)) {
    pass('SDLQueryGPUFence reports signaled');
} else {
    fail('SDLQueryGPUFence expected true after wait');
    $errors++;
}
SDLGPU::SDLReleaseGPUFence($device, $fence);
pass('Fence released');

$readBack = SDLGPU::readFromGPUTransferBuffer($device, $tbDown, 256);
if ($readBack === $payload) {
    pass('Buffer round trip: 256 bytes match after upload -> copy -> download');
} else {
    fail('Buffer round trip mismatch', bin2hex(substr($readBack, 0, 16)) . '...');
    $errors++;
}

section('Command buffer cancel');
$cbCancel = SDLGPU::SDLAcquireGPUCommandBuffer($device);
if (SDLGPU::SDLCancelGPUCommandBuffer($cbCancel)) {
    pass('SDLCancelGPUCommandBuffer');
} else {
    fail('SDLCancelGPUCommandBuffer', sdl_err());
    $errors++;
}

section('Offscreen render: red triangle via MSL shaders');
$vsSource = <<<'MSL'
#include <metal_stdlib>
using namespace metal;
struct VSOutput { float4 position [[position]]; };
vertex VSOutput vs_main(uint vid [[vertex_id]])
{
    float2 pos[3] = { float2(-1.0, -1.0), float2(3.0, -1.0), float2(-1.0, 3.0) };
    VSOutput o;
    o.position = float4(pos[vid], 0.0, 1.0);
    return o;
}
MSL;

$fsSource = <<<'MSL'
#include <metal_stdlib>
using namespace metal;
fragment float4 fs_main(constant float4 &ucolor [[buffer(0)]])
{
    return ucolor;
}
MSL;

$renderTest = true;
try {
    $vs = SDLGPU::SDLCreateGPUShader($device, [
        'code' => $vsSource,
        'entrypoint' => 'vs_main',
        'format' => SDL_GPU_SHADERFORMAT_MSL,
        'stage' => SDL_GPU_SHADERSTAGE_VERTEX,
    ]);
    $fs = SDLGPU::SDLCreateGPUShader($device, [
        'code' => $fsSource,
        'entrypoint' => 'fs_main',
        'format' => SDL_GPU_SHADERFORMAT_MSL,
        'stage' => SDL_GPU_SHADERSTAGE_FRAGMENT,
        'num_uniform_buffers' => 1,
    ]);
    pass("Compiled MSL shaders vs={$vs} fs={$fs}");
} catch (\RuntimeException $e) {
    skip('Runtime MSL compilation unavailable', $e->getMessage());
    $renderTest = false;
}

if ($renderTest) {
    $supportsRGBA8Target = SDLGPU::SDLGPUTextureSupportsFormat(
        $device,
        SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
        SDL_GPU_TEXTURETYPE_2D,
        SDL_GPU_TEXTUREUSAGE_COLOR_TARGET | SDL_GPU_TEXTUREUSAGE_SAMPLER
    );
    if ($supportsRGBA8Target) {
        pass('RGBA8 supported as color target + sampler');
    } else {
        fail('SDLGPUTextureSupportsFormat RGBA8 color target');
        $errors++;
    }
    if (SDLGPU::SDLGPUTextureSupportsSampleCount($device, SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM, SDL_GPU_SAMPLECOUNT_1)) {
        pass('RGBA8 supports 1x sample count');
    } else {
        fail('SDLGPUTextureSupportsSampleCount');
        $errors++;
    }

    $target = SDLGPU::SDLCreateGPUTexture($device, [
        'type' => SDL_GPU_TEXTURETYPE_2D,
        'format' => SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
        'usage' => SDL_GPU_TEXTUREUSAGE_COLOR_TARGET | SDL_GPU_TEXTUREUSAGE_SAMPLER,
        'width' => 64,
        'height' => 64,
        'layer_count_or_depth' => 1,
        'num_levels' => 1,
    ]);
    SDLGPU::SDLSetGPUTextureName($device, $target, 'proof_render_target');
    pass("Created 64x64 render target texture={$target} (+name set)");

    $sampler = SDLGPU::SDLCreateGPUSampler($device, [
        'min_filter' => SDL_GPU_FILTER_LINEAR,
        'mag_filter' => SDL_GPU_FILTER_LINEAR,
    ]);
    pass("Created sampler={$sampler}");

    $pipeline = SDLGPU::SDLCreateGPUGraphicsPipeline($device, [
        'vertex_shader' => $vs,
        'fragment_shader' => $fs,
        'primitive_type' => SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
        'target_info' => [
            'color_target_descriptions' => [
                ['format' => SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM],
            ],
        ],
    ]);
    pass("Created graphics pipeline={$pipeline}");

    $tbTex = SDLGPU::SDLCreateGPUTransferBuffer($device, [
        'usage' => SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD,
        'size' => 64 * 64 * 4,
    ]);

    $cb = SDLGPU::SDLAcquireGPUCommandBuffer($device);
    SDLGPU::SDLPushGPUFragmentUniformData($cb, 0, pack('g4', 1.0, 0.0, 0.0, 1.0)); // red

    $renderPass = SDLGPU::SDLBeginGPURenderPass($cb, [
        [
            'texture' => $target,
            'clear_color' => ['r' => 0.0, 'g' => 0.0, 'b' => 1.0, 'a' => 1.0],
            'load_op' => SDL_GPU_LOADOP_CLEAR,
            'store_op' => SDL_GPU_STOREOP_STORE,
        ],
    ], null);
    SDLGPU::SDLBindGPUGraphicsPipeline($renderPass, $pipeline);
    SDLGPU::SDLSetGPUViewport($renderPass, ['x' => 0, 'y' => 0, 'w' => 64, 'h' => 64, 'min_depth' => 0.0, 'max_depth' => 1.0]);
    SDLGPU::SDLSetGPUScissor($renderPass, ['x' => 0, 'y' => 0, 'w' => 64, 'h' => 64]);
    SDLGPU::SDLSetGPUBlendConstants($renderPass, ['r' => 1.0, 'g' => 1.0, 'b' => 1.0, 'a' => 1.0]);
    SDLGPU::SDLSetGPUStencilReference($renderPass, 0);
    SDLGPU::SDLDrawGPUPrimitives($renderPass, 3, 1, 0, 0);
    SDLGPU::SDLEndGPURenderPass($renderPass);

    $copyPass = SDLGPU::SDLBeginGPUCopyPass($cb);
    SDLGPU::SDLDownloadFromGPUTexture(
        $copyPass,
        ['texture' => $target, 'mip_level' => 0, 'layer' => 0, 'x' => 0, 'y' => 0, 'z' => 0, 'w' => 64, 'h' => 64, 'd' => 1],
        ['transfer_buffer' => $tbTex, 'offset' => 0, 'pixels_per_row' => 0, 'rows_per_layer' => 0]
    );
    SDLGPU::SDLEndGPUCopyPass($copyPass);

    $fence = SDLGPU::SDLSubmitGPUCommandBufferAndAcquireFence($cb);
    SDLGPU::SDLWaitForGPUFences($device, true, [$fence]);
    SDLGPU::SDLReleaseGPUFence($device, $fence);

    $pixels = SDLGPU::readFromGPUTransferBuffer($device, $tbTex, 64 * 64 * 4);
    $topLeft = bin2hex(substr($pixels, 0, 4));
    $center = bin2hex(substr($pixels, (32 * 64 + 32) * 4, 4));
    if ($topLeft === 'ff0000ff' && $center === 'ff0000ff') {
        pass("Rendered triangle read back red (top-left={$topLeft}, center={$center})");
    } else {
        fail('Render readback', "top-left={$topLeft}, center={$center}, expected ff0000ff");
        $errors++;
    }

    section('Blit & mipmaps');
    $blitDst = SDLGPU::SDLCreateGPUTexture($device, [
        'type' => SDL_GPU_TEXTURETYPE_2D,
        'format' => SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
        'usage' => SDL_GPU_TEXTUREUSAGE_COLOR_TARGET | SDL_GPU_TEXTUREUSAGE_SAMPLER,
        'width' => 32,
        'height' => 32,
        'layer_count_or_depth' => 1,
        'num_levels' => 2,
    ]);
    $cb = SDLGPU::SDLAcquireGPUCommandBuffer($device);
    SDLGPU::SDLBlitGPUTexture($cb, [
        'source' => ['texture' => $target, 'x' => 0, 'y' => 0, 'w' => 64, 'h' => 64],
        'destination' => ['texture' => $blitDst, 'x' => 0, 'y' => 0, 'w' => 32, 'h' => 32],
        'load_op' => SDL_GPU_LOADOP_CLEAR,
        'clear_color' => ['r' => 0.0, 'g' => 0.0, 'b' => 0.0, 'a' => 1.0],
        'filter' => SDL_GPU_FILTER_LINEAR,
    ]);
    SDLGPU::SDLGenerateMipmapsForGPUTexture($cb, $blitDst);
    if (SDLGPU::SDLSubmitGPUCommandBuffer($cb)) {
        pass('Blit 64x64 -> 32x32 + mipmap generation submitted');
    } else {
        fail('SDLSubmitGPUCommandBuffer (blit)', sdl_err());
        $errors++;
    }
    SDLGPU::SDLWaitForGPUIdle($device);
    SDLGPU::SDLReleaseGPUTexture($device, $blitDst);

    SDLGPU::SDLReleaseGPUTransferBuffer($device, $tbTex);
    SDLGPU::SDLReleaseGPUSampler($device, $sampler);
    SDLGPU::SDLReleaseGPUGraphicsPipeline($device, $pipeline);
    SDLGPU::SDLReleaseGPUShader($device, $vs);
    SDLGPU::SDLReleaseGPUShader($device, $fs);
    SDLGPU::SDLReleaseGPUTexture($device, $target);
    pass('Render resources released');
}

section('Compute dispatch');
$csSource = <<<'MSL'
#include <metal_stdlib>
using namespace metal;
kernel void cs_main(device uint *outbuf [[buffer(0)]], uint3 gid [[thread_position_in_grid]])
{
    outbuf[gid.x] = gid.x * 7u;
}
MSL;

try {
    $computePipeline = SDLGPU::SDLCreateGPUComputePipeline($device, [
        'code' => $csSource,
        'entrypoint' => 'cs_main',
        'format' => SDL_GPU_SHADERFORMAT_MSL,
        'num_readwrite_storage_buffers' => 1,
        'threadcount_x' => 64,
        'threadcount_y' => 1,
        'threadcount_z' => 1,
    ]);
    pass("Created compute pipeline={$computePipeline}");

    $bufCompute = SDLGPU::SDLCreateGPUBuffer($device, [
        'usage' => SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_WRITE,
        'size' => 256,
    ]);

    $cb = SDLGPU::SDLAcquireGPUCommandBuffer($device);
    $computePass = SDLGPU::SDLBeginGPUComputePass($cb, null, [
        ['buffer' => $bufCompute, 'cycle' => false],
    ]);
    SDLGPU::SDLBindGPUComputePipeline($computePass, $computePipeline);
    SDLGPU::SDLDispatchGPUCompute($computePass, 1, 1, 1);
    SDLGPU::SDLEndGPUComputePass($computePass);

    $copyPass = SDLGPU::SDLBeginGPUCopyPass($cb);
    SDLGPU::SDLDownloadFromGPUBuffer($copyPass, ['buffer' => $bufCompute, 'offset' => 0, 'size' => 256], ['transfer_buffer' => $tbDown, 'offset' => 0]);
    SDLGPU::SDLEndGPUCopyPass($copyPass);

    $fence = SDLGPU::SDLSubmitGPUCommandBufferAndAcquireFence($cb);
    SDLGPU::SDLWaitForGPUFences($device, true, [$fence]);
    SDLGPU::SDLReleaseGPUFence($device, $fence);

    $values = array_values(unpack('V64', SDLGPU::readFromGPUTransferBuffer($device, $tbDown, 256)));
    $ok = true;
    foreach ($values as $i => $v) {
        if ($v !== $i * 7) {
            $ok = false;
            break;
        }
    }
    if ($ok) {
        pass('Compute kernel wrote gid*7 for all 64 threads');
    } else {
        fail('Compute readback mismatch', implode(',', array_slice($values, 0, 8)));
        $errors++;
    }

    SDLGPU::SDLReleaseGPUBuffer($device, $bufCompute);
    SDLGPU::SDLReleaseGPUComputePipeline($device, $computePipeline);
} catch (\RuntimeException $e) {
    skip('Compute pipeline unavailable', $e->getMessage());
}

section('Swapchain / window');
$window = 0;
try {
    $window = SDLVideo::SDLCreateWindow('sdl3 proof_gpu', 128, 96, SDL_WINDOW_HIDDEN);
} catch (\Throwable $e) {
    skip('Window creation failed (headless?)', $e->getMessage());
}

if ($window !== 0) {
    $supComp = SDLGPU::SDLWindowSupportsGPUSwapchainComposition($device, $window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR);
    $supMode = SDLGPU::SDLWindowSupportsGPUPresentMode($device, $window, SDL_GPU_PRESENTMODE_VSYNC);
    pass('Supports SDR composition=' . ($supComp ? 'true' : 'false') . ', vsync present mode=' . ($supMode ? 'true' : 'false'));

    if (SDLGPU::SDLClaimWindowForGPUDevice($device, $window)) {
        pass('Claimed window for GPU device');

        if (SDLGPU::SDLSetGPUSwapchainParameters($device, $window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC)) {
            pass('SDLSetGPUSwapchainParameters(SDR, VSYNC)');
        } else {
            fail('SDLSetGPUSwapchainParameters', sdl_err());
            $errors++;
        }

        $scFormat = SDLGPU::SDLGetGPUSwapchainTextureFormat($device, $window);
        pass("Swapchain texture format = {$scFormat}");

        if (SDLGPU::SDLWaitForGPUSwapchain($device, $window)) {
            pass('SDLWaitForGPUSwapchain');
        } else {
            fail('SDLWaitForGPUSwapchain', sdl_err());
            $errors++;
        }

        try {
            $cb = SDLGPU::SDLAcquireGPUCommandBuffer($device);
            $acquired = SDLGPU::SDLWaitAndAcquireGPUSwapchainTexture($cb, $window);
            if ($acquired['texture'] !== 0) {
                pass("Acquired swapchain texture {$acquired['width']}x{$acquired['height']}");
                SDLGPU::SDLSubmitGPUCommandBuffer($cb);
            } else {
                skip('Swapchain texture not ready');
                SDLGPU::SDLCancelGPUCommandBuffer($cb);
            }

            // Non-blocking variant.
            $cb = SDLGPU::SDLAcquireGPUCommandBuffer($device);
            $acquired = SDLGPU::SDLAcquireGPUSwapchainTexture($cb, $window);
            pass('SDLAcquireGPUSwapchainTexture texture=' . $acquired['texture']);
            if ($acquired['texture'] !== 0) {
                SDLGPU::SDLSubmitGPUCommandBuffer($cb);
            } else {
                SDLGPU::SDLCancelGPUCommandBuffer($cb);
            }
        } catch (\RuntimeException $e) {
            skip('Swapchain acquire unavailable', $e->getMessage());
        }

        SDLGPU::SDLWaitForGPUIdle($device);
        SDLGPU::SDLReleaseWindowFromGPUDevice($device, $window);
        pass('Released window from GPU device');
    } else {
        skip('SDLClaimWindowForGPUDevice', sdl_err());
    }

    SDLVideo::SDLDestroyWindow($window);
}

section('GPU renderer & render state (SDL_render.h)');
$rsWindow = 0;
try {
    $rsWindow = SDLVideo::SDLCreateWindow('sdl3 proof_gpu_rs', 128, 96, SDL_WINDOW_HIDDEN);
} catch (\Throwable $e) {
    skip('Window creation failed', $e->getMessage());
}

if ($rsWindow !== 0) {
    try {
        $renderer = SDLGPU::SDLCreateGPURenderer($device, $rsWindow);
        pass("Created GPU renderer={$renderer}");

        $rendererDevice = SDLGPU::SDLGetGPURendererDevice($renderer);
        if ($rendererDevice === $device) {
            pass('SDLGetGPURendererDevice matches our device handle');
        } else {
            fail('SDLGetGPURendererDevice', "expected {$device}, got {$rendererDevice}");
            $errors++;
        }

        $rsFsSource = <<<'MSL'
#include <metal_stdlib>
using namespace metal;
fragment float4 fs_rs(constant float4 &c [[buffer(0)]])
{
    return c;
}
MSL;
        $rsShader = SDLGPU::SDLCreateGPUShader($device, [
            'code' => $rsFsSource,
            'entrypoint' => 'fs_rs',
            'format' => SDL_GPU_SHADERFORMAT_MSL,
            'stage' => SDL_GPU_SHADERSTAGE_FRAGMENT,
            'num_uniform_buffers' => 1,
        ]);

        $renderState = SDLGPU::SDLCreateGPURenderState($renderer, [
            'fragment_shader' => $rsShader,
        ]);
        pass("Created GPU render state={$renderState}");

        if (SDLGPU::SDLSetGPURenderStateFragmentUniforms($renderState, 0, pack('g4', 0.0, 1.0, 0.0, 1.0))) {
            pass('SDLSetGPURenderStateFragmentUniforms');
        } else {
            fail('SDLSetGPURenderStateFragmentUniforms', sdl_err());
            $errors++;
        }

        if (SDLGPU::SDLSetGPURenderState($renderer, $renderState)) {
            pass('SDLSetGPURenderState(state)');
        } else {
            fail('SDLSetGPURenderState', sdl_err());
            $errors++;
        }

        SDLRender::SDLSetRenderDrawColor($renderer, 255, 255, 255, 255);
        SDLRender::SDLRenderClear($renderer);
        SDLRender::SDLRenderPresent($renderer);
        pass('Rendered a frame with the custom render state');

        if (SDLGPU::SDLSetGPURenderState($renderer, 0)) {
            pass('SDLSetGPURenderState(0) cleared state');
        } else {
            fail('SDLSetGPURenderState(0)', sdl_err());
            $errors++;
        }

        SDLGPU::SDLDestroyGPURenderState($renderState);
        pass('Destroyed GPU render state');

        SDLGPU::SDLReleaseGPUShader($device, $rsShader);
        SDLRender::SDLDestroyRenderer($renderer);
    } catch (\RuntimeException $e) {
        skip('GPU renderer / render state unavailable', $e->getMessage());
    }

    SDLVideo::SDLDestroyWindow($rsWindow);
}

section('GDK guards');
try {
    SDLGPU::SDLGDKSuspendGPU($device);
    fail('SDLGDKSuspendGPU should throw on non-GDK platforms');
    $errors++;
} catch (\RuntimeException $e) {
    pass('SDLGDKSuspendGPU throws on non-GDK platform');
}
try {
    SDLGPU::SDLGDKResumeGPU($device);
    fail('SDLGDKResumeGPU should throw on non-GDK platforms');
    $errors++;
} catch (\RuntimeException $e) {
    pass('SDLGDKResumeGPU throws on non-GDK platform');
}

section('Teardown');
SDLGPU::SDLReleaseGPUTransferBuffer($device, $tbUp);
SDLGPU::SDLReleaseGPUTransferBuffer($device, $tbDown);
SDLGPU::SDLReleaseGPUBuffer($device, $bufSrc);
SDLGPU::SDLReleaseGPUBuffer($device, $bufDst);
if (SDLGPU::SDLWaitForGPUIdle($device)) {
    pass('SDLWaitForGPUIdle');
} else {
    fail('SDLWaitForGPUIdle', sdl_err());
    $errors++;
}
SDLGPU::SDLDestroyGPUDevice($device);
pass('GPU device destroyed');

SDL::SDLQuit();

echo "\n";
if ($errors > 0) {
    echo "proof_gpu: {$errors} FAILURE(S)\n";
    exit(1);
}
echo "proof_gpu: ALL CHECKS PASSED\n";
exit(0);
