#include "includes/common.hlsl"
#pragma target 5.0
cbuffer vars : register(b7) {
   float4 color;
}
struct VSI {
   float4 pos : POSITION;
};
struct VSO {
   float4 pos : SV_POSITION;
};
VSO vs(VSI i) {
   VSO o;
   o.pos = mul(mat_mvp, i.pos);
   return o;
}
half4 ps(VSO i) : SV_Target{
   return color;//map(sin(i.pos.x*0.25) * sin(i.pos.y*0.25),-1,1,0,1);
}