#pragma once
#include "core/math/Vector3.h"
namespace TEngine::Math {
   template<typename Scalar>
   struct Vector4 : public Vector3<Scalar> {
      using super = Vector3<Scalar>;
      float w;
      Vector4() : super(0, 0, 0), w(0) {}
      Vector4(Scalar v) : super(v, v, v), w(v) {}
      Vector4(Scalar x, Scalar y) : super(x, y, 0), w(0) {}
      Vector4(Scalar x, Scalar y, Scalar z) : super(x, y, z), w(0) {}
      Vector4(Scalar x, Scalar y, Scalar z, Scalar w) : super(x, y, z), w(w) {}
      explicit Vector4(CXMVECTOR v) : Vector4(v) {}
      Vector4<Scalar> &Set(float x, float y, float z, float w) {
         this->x = x;
         this->y = y;
         this->z = z;
         this->w = w;
         return *this;
      }
      Vector4<Scalar> &Set(Vector4<Scalar> v) {
         return Set(v.x, v.y, v.z, v.w);
      }
      template<typename T>
      friend std::basic_ostream<T> & operator<<(std::basic_ostream<T> & stream, Vector4<Scalar> vec) {
         stream << "[x:" << vec.x << ", y:" << vec.y << ", z:" << vec.z << ", w:" << vec.w << ']';
         return stream;
      }
   };
   typedef Vector4<float>  float4;
   typedef Vector4<double> double4;
}