#include "includes/common.hlsl"
struct VSI {
   float4 pos : POSITION;
};
struct VSO {
   float4 pos : SV_POSITION;
   float4 lpos : ASD;
};
VSO vs(VSI i) {
   VSO o;
   o.lpos = i.pos;
   o.pos = mul(mat_mvp, i.pos);
   return o;
}
half4 ps(VSO i) : SV_Target{
   float f = (
      frac(i.lpos.x) +
      frac(i.lpos.y) +
      frac(i.lpos.z)
      ) / 3;
   return half4(f,0,f,1);
}