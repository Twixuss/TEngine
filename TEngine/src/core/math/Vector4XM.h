#pragma once
#include "Vector4.h"
namespace TEngine::Math {
   template<>
   struct Vector4<float> {
      using Vector = Vector4<float>;
      union {
         struct {
            float x, y, z, w;
         };
         XMVECTOR xmv;
      };
      XMFINLINE Vector4() : xmv(XMVectorZero()) {}
      XMFINLINE Vector(float x, float y, float z, float w) : xmv(XMVectorSet(x, y, z, w)) {}
      XMFINLINE Vector4(const Vector& other) : xmv(other.xmv) {}
      XMFINLINE Vector4(const XMVECTOR& v) : xmv(v) {}
      operator float3() {
         return float3(x, y, z);
      }
      XMFINLINE bool Equals(const Vector& v) {
         return XMVector4Equal(xmv, v.xmv);
      }
      XMFINLINE friend Vector& operator+=(Vector& a, const Vector& b) {
         a.xmv = XMVectorAdd(a.xmv, b.xmv);
         return a;
      }
      XMFINLINE friend Vector& operator-=(Vector& a, const Vector& b) {
         a.xmv = XMVectorSubtract(a.xmv, b.xmv);
         return a;
      }
      XMFINLINE friend Vector& operator*=(Vector& a, const Vector& b) {
         a.xmv = XMVectorMultiply(a.xmv, b.xmv);
         return a;
      }
      XMFINLINE friend Vector& operator/=(Vector& a, const Vector& b) {
         a.xmv = XMVectorDivide(a.xmv, b.xmv);
         return a;
      }
      XMFINLINE friend Vector  operator+ (const Vector& a) {
         return Vector(a);
      }
      XMFINLINE friend Vector  operator- (const Vector& a) {
         return XMVectorNegate(a.xmv);
      }
      XMFINLINE friend Vector  operator+ (const Vector& a, const Vector& b) {
         return XMVectorAdd(a.xmv, b.xmv);
      }
      XMFINLINE friend Vector  operator- (const Vector& a, const Vector& b) {
         return XMVectorSubtract(a.xmv, b.xmv);
      }
      XMFINLINE friend Vector  operator* (const Vector& a, const Vector& b) {
         return XMVectorMultiply(a.xmv, b.xmv);
      }
      XMFINLINE friend Vector  operator/ (const Vector& a, const Vector& b) {
         return XMVectorDivide(a.xmv, b.xmv);
      }
      XMFINLINE friend bool    operator==(const Vector& a, const Vector& b) {
         return XMVector4Equal(a.xmv, b.xmv);
      }
      XMFINLINE friend bool    operator!=(const Vector& a, const Vector& b) {
         return XMVector4NotEqual(a.xmv, b.xmv);
      }
      XMFINLINE static const Vector Zero() {
         return XMVectorZero();
      }
   };
}