#include <metal_stdlib>
using namespace metal;

struct PointIn { float2 point [[attribute(0)]]; };
struct VertexOut { float4 position [[position]]; };

vertex VertexOut flat_vertex(PointIn in [[stage_in]])
{
    VertexOut out;
    out.position = float4(in.point, 0.0, 1.0);
    return out;
}

fragment float4 flat_fragment(constant float4 &rgba [[buffer(0)]])
{
    return rgba;
}
