#pragma once
#include "Vector4.h"
namespace TEngine::Math {
   template<>
   struct Vector4<float> {
      using Self = Vector4<float>;
      using SelfRef = Vector4<float>&;
      using SelfCRef = const Vector4<float>&;
      union {
         struct {
            float x, y, z, w;
         };
         XMVECTOR xmv;
      };
      XMFINLINE Vector4() : xmv(XMVectorZero()) {}
      XMFINLINE Vector4(SelfCRef other) : xmv(other.xmv) {}
      XMFINLINE Vector4(FXMVECTOR v) : xmv(v) {}
      operator float3() {
         return float3(x, y, z);
      }
      XMFINLINE explicit operator FXMVECTOR() {
         return xmv;
      }
      XMFINLINE explicit operator XMVECTOR() const {
         return xmv;
      }
      XMFINLINE bool Equals(SelfCRef v) {
         return XMVector4Equal(xmv, v.xmv);
      }
      XMFINLINE Self operator+() {
         return Self(*this);
      }
      XMFINLINE Self operator-() {
         return XMVectorNegate(xmv);
      }
      XMFINLINE Self operator+(SelfCRef v) {
         return XMVectorAdd(xmv, v.xmv);
      }
      XMFINLINE Self operator+(const float3 &v) {
         return XMVectorAdd(xmv, XMVectorSet(v.x, v.y, v.z, 0));
      }
      XMFINLINE Self operator*(SelfCRef v) {
         return XMVectorMultiply(xmv, v.xmv);
      }
      XMFINLINE SelfRef operator+=(SelfCRef v) {
         xmv = XMVectorAdd(xmv, v.xmv);
         return *this;
      }
      XMFINLINE SelfRef operator*=(SelfCRef v) {
         xmv = XMVectorAdd(xmv, v.xmv);
         return *this;
      }
      XMFINLINE static const Self Zero() {
         return XMVectorZero();
      }
   };
   typedef float4 &float4Ref;
   typedef const float4 &float4CRef;
   XMFINLINE float4 operator+ (float4CRef a, float4CRef b) {
      return XMVectorAdd(a.xmv, b.xmv);
   }
   XMFINLINE float4 operator- (float4CRef a, float4CRef b) {
      return XMVectorSubtract(a.xmv, b.xmv);
   }
   XMFINLINE float4 operator* (float4CRef a, float4CRef b) {
      return XMVectorMultiply(a.xmv, b.xmv);
   }
   XMFINLINE float4 operator/ (float4CRef a, float4CRef b) {
      return XMVectorDivide(a.xmv, b.xmv);
   }
   XMFINLINE bool   operator==(float4CRef a, float4CRef b) {
      return XMVector4Equal(a.xmv, b.xmv);
   }
}