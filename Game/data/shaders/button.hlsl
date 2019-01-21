#include "common.hlsl"
struct VSI
{
    float4 pos : POSITION;
    float2 uv : UV;
};
struct VSO
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};
TEX2D(dtex, 0)
TEX2D(htex, 1)
TEX2D(ptex, 2)
#define ss ssPointClamp
// these values are set in UIToggle::Draw() 
#define uiH_P uiParams0.x
#define uiD_HP uiParams0.y
#define uiCenter uiParams0.zw
VSO vs(VSI i){
    VSO o;

    o.pos = i.pos;
    o.pos.xy = lerp(o.pos.xy, uiCenter, uiH_P * 0.1);
    o.uv = i.uv;

    return o;
}
half4 ps(VSO i) : SV_Target
{
    return lerp(
        dtex.Sample(ss, i.uv),
        lerp(
            htex.Sample(ss, i.uv),
            ptex.Sample(ss, i.uv), uiH_P),uiD_HP);
//return (half4(
//    sin((tex.Sample(ssLinearClamp, i.uv).x + timeTotal) * 10),
//    sin((tex.Sample(ssLinearClamp, i.uv).y + timeTotal) * 10),
//    sin((tex.Sample(ssLinearClamp, i.uv).z + timeTotal) * 10), 1
//    )*0.5 + 0.5);
}