#include "includes/common.hlsl"
struct VSI {
   float4 pos : POSITION;
};
struct VSO {
   float4 pos : SV_POSITION;
};
VSO vs(VSI i) {
   VSO o;
   o.pos = mul(mat_proj, i.pos);
   return o;
}
half4 ps(VSO i) : SV_Target{
   return 0.5;//map(sin(i.pos.x*0.25) * sin(i.pos.y*0.25),-1,1,0,1);
}