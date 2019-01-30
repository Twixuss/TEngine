#ifndef COMMON_HLSL
#define COMMON_HLSL

#define TWOPI  6.283185307179586232f
#define PI     3.141592653589793116f
#define HALFPI 1.570796326794896558f
#define RAD2DEG(v) ((v) * 180.0 / PI)
#define DEG2RAD(v) ((v) * PI / 180.0)

#define TEX2D(name,index) Texture2D name : register(t##index);
#define SAMPLER(name,index) SamplerState name : register(s##index);

SAMPLER(ssLinearWrap, 0)
SAMPLER(ssLinearClamp, 1)
SAMPLER(ssPointWrap, 2)
SAMPLER(ssPointClamp, 3)

cbuffer frame : register(b0) {
    float timeDelta;
    float timeTotal;
    float2 dummy;
}
cbuffer mesh : register(b1) {
   float4x4 mat_rot;
   float4x4 mat_proj;
   float4x4 mat_mvp;
}
//cbuffer ui : register(b1) {
//    float4 uiParams0;
//    float4 uiParams1;
//}
float map(float v, float smin, float smax, float dmin, float dmax) {
   return (v - smin) / (smax - smin) * (dmax - dmin) + dmin;
}
#endif