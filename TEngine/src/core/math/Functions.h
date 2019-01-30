#pragma once
#include "core/math/Constants.h"
namespace TEngine::Math {
   template<typename T>
   T& Max(const T& a, const T& b) {
      return a < b ? b : a;
   }
   template<typename T>
   T& Min(const T& a, const T& b) {
      return a > b ? b : a;
   }
   template<typename Scalar>
   inline constexpr auto Rad2Deg(Scalar v) { return v * PIdiv180inv; }
   template<typename Scalar>
   inline constexpr auto Deg2Rad(Scalar v) { return v * PIdiv180; }
   template<typename T1, typename T2, typename T3, typename T4, typename T5>
   inline auto Map(T1 val, T2 smin, T3 smax, T4 dmin, T5 dmax) {
      return ((float)val - smin) / (smax - smin) * (dmax - dmin) + dmin;
   }
   template<typename T1, typename T2, typename T3>
   inline auto Lerp(T1 v, T2 d, T3 f) {
      return v + (d - v) * f;
   }
   template<typename T> inline auto Pow2(T v) { return v * v; }
   template<typename T> inline auto Pow3(T v) { return v * v * v; }
   template<typename T> inline auto Pow4(T v) { return Pow2(v * v); }
   template<typename T> inline auto Pow5(T v) { return Pow2(v * v) * v; }
   template<typename T> inline auto Flip(T v) { return (T)1 - v; }
   template<typename T1, typename T2, typename T3> inline auto SmoothStart2(T1 v, T2 min, T3 max) { return Pow2((v - min) / (max - min)) * (max - min) + min; }
   template<typename T1, typename T2, typename T3> inline auto SmoothStart3(T1 v, T2 min, T3 max) { return Pow3((v - min) / (max - min)) * (max - min) + min; }
   template<typename T1, typename T2, typename T3> inline auto SmoothStart4(T1 v, T2 min, T3 max) { return Pow4((v - min) / (max - min)) * (max - min) + min; }
   template<typename T1, typename T2, typename T3> inline auto SmoothStart5(T1 v, T2 min, T3 max) { return Pow5((v - min) / (max - min)) * (max - min) + min; }
   template<typename T1, typename T2, typename T3> inline auto SmoothStop2(T1 v, T2 min, T3 max) { return Flip(Pow2(Flip((v - min) / (max - min)))) * (max - min) + min; }
   template<typename T1, typename T2, typename T3> inline auto SmoothStop3(T1 v, T2 min, T3 max) { return Flip(Pow3(Flip((v - min) / (max - min)))) * (max - min) + min; }
   template<typename T1, typename T2, typename T3> inline auto SmoothStop4(T1 v, T2 min, T3 max) { return Flip(Pow4(Flip((v - min) / (max - min)))) * (max - min) + min; }
   template<typename T1, typename T2, typename T3> inline auto SmoothStop5(T1 v, T2 min, T3 max) { return Flip(Pow5(Flip((v - min) / (max - min)))) * (max - min) + min; }
   template<typename T1, typename T2, typename T3> inline auto SmoothStep2(T1 v, T2 min, T3 max) { return Lerp(SmoothStart2(v, min, max), SmoothStop2(v, min, max), (v - min) / (max - min)); }
   template<typename T1, typename T2, typename T3> inline auto SmoothStep3(T1 v, T2 min, T3 max) { return Lerp(SmoothStart3(v, min, max), SmoothStop3(v, min, max), (v - min) / (max - min)); }
   template<typename T1, typename T2, typename T3> inline auto SmoothStep4(T1 v, T2 min, T3 max) { return Lerp(SmoothStart4(v, min, max), SmoothStop4(v, min, max), (v - min) / (max - min)); }
   template<typename T1, typename T2, typename T3> inline auto SmoothStep5(T1 v, T2 min, T3 max) { return Lerp(SmoothStart5(v, min, max), SmoothStop5(v, min, max), (v - min) / (max - min)); }
}