#pragma once
#include "core/math/Vector3.h"
namespace TEngine::Math {
   template<typename Scalar>
   struct LibraryInterface Vector4 : public Vector3<Scalar> {
      using Base = Vector3<Scalar>;
      using Vector = Vector4<Scalar>;
      Scalar w;
      Vector() : Base(0), w(0) {}
      Vector(const Scalar& v) : Base(v), w(v) {}
      Vector(const Scalar& x, const Scalar& y) : Base(x, y, 0), w(0) {}
      Vector(const Scalar& x, const Scalar& y, const Scalar& z) : Base(x, y, z), w(0) {}
      Vector(const Scalar& x, const Scalar& y, const Scalar& z, const Scalar& w) : Base(x, y, z), w(w) {}
      Vector& operator= (const Scalar& v) {
         return Set(v);
      }
      Vector& operator= (const Vector& v) {
         return Set(v);
      }
      Vector& Set(const Scalar& v) {
         return Set(v, v);
      }
      Vector& Set(const Vector& v) {
         return Set(v.x, v.y);
      }
      Vector& Set(const Scalar& x, const Scalar& y, const Scalar& z, const Scalar& w) {
         this->x = x;
         this->y = y;
         this->z = z;
         this->w = w;
         return *this;
      }
      Scalar  LengthSqr() const {
         return x * x + y * y + z * z + w * w;
      }
      Scalar  Length() const {
         return sqrt(LengthSqr());
      }
      Vector& Normalize() {
         return *this *= 1.0f / Length();
      }
      Vector  Normalized() const {
         return Vector(*this) * (1.0f / Length());
      }
      Vector& ProjectOn(const Vector& v) {
         return *this = Project(*this, v);
      }
      Vector  ProjectedOn(const Vector& v) const {
         return Project(*this, v);
      }
      friend Vector& operator+=(Vector& a, const Scalar& b) {
         a.x += b;
         a.y += b;
         a.z += b;
         a.w += b;
         return a;
      }
      friend Vector& operator-=(Vector& a, const Scalar& b) {
         a.x -= b;
         a.y -= b;
         a.z -= b;
         a.w -= b;
         return a;
      }
      friend Vector& operator*=(Vector& a, const Scalar& b) {
         a.x *= b;
         a.y *= b;
         a.z *= b;
         a.w *= b;
         return a;
      }
      friend Vector& operator/=(Vector& a, const Scalar& b) {
         a.x /= b;
         a.y /= b;
         a.z /= b;
         a.w /= b;
         return a;
      }
      friend Vector& operator+=(Vector& a, const Vector& b) {
         a.x += b.x;
         a.y += b.y;
         a.z += b.z;
         a.w += b.w;
         return a;
      }
      friend Vector& operator-=(Vector& a, const Vector& b) {
         a.x -= b.x;
         a.y -= b.y;
         a.z -= b.z;
         a.w -= b.w;
         return a;
      }
      friend Vector& operator*=(Vector& a, const Vector& b) {
         a.x *= b.x;
         a.y *= b.y;
         a.z *= b.z;
         a.w *= b.w;
         return a;
      }
      friend Vector& operator/=(Vector& a, const Vector& b) {
         a.x /= b.x;
         a.y /= b.y;
         a.z /= b.z;
         a.w /= b.w;
         return a;
      }
      friend Vector  operator+ (const Vector& a) {
         return Vector(+a.x, +a.y, +a.z, +a.w);
      }
      friend Vector  operator- (const Vector& a) {
         return Vector(-a.x, -a.y, -a.z, + a.w);
      }
      friend Vector  operator+ (const Vector& a, const Scalar& b) {
         return Vector(a.x + b, a.y + b, a.z + b, a.w + b);
      }
      friend Vector  operator- (const Vector& a, const Scalar& b) {
         return Vector(a.x - b, a.y - b, a.z - b, a.w - b);
      }
      friend Vector  operator* (const Vector& a, const Scalar& b) {
         return Vector(a.x * b, a.y * b, a.z * b, a.w * b);
      }
      friend Vector  operator/ (const Vector& a, const Scalar& b) {
         return Vector(a.x * b, a.y * b, a.z * b, a.w * b);
      }
      friend Vector  operator+ (const Vector& a, const Vector& b) {
         return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
      }
      friend Vector  operator- (const Vector& a, const Vector& b) {
         return Vector(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
      }
      friend Vector  operator* (const Vector& a, const Vector& b) {
         return Vector(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
      }
      friend Vector  operator/ (const Vector& a, const Vector& b) {
         return Vector(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
      }
      friend Scalar  operator^ (const Vector& a, const Vector& b) {
         return acos(Dot(a, b) / (a.Length() * b.Length()));
      }
      template<typename T>
      friend std::basic_ostream<T> & operator<<(std::basic_ostream<T> & stream, const Vector& vec) {
         stream << "[x:" << vec.x << ", y:" << vec.y << ", z:" << vec.z << ", w:" << vec.w << ']';
         return stream;
      }
      static Scalar Dot(const Vector& a, const Vector& b) {
         return a.x * b.x + a.y * b.y + a.z * b.z;
      }
      static Vector Cross(const Vector& a, const Vector& b) {
         return Vector3<Scalar>(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
            );
      }
      static Vector Project(const Vector& a, const Vector& b) {
         return b.Normalized() * Dot(a, b.Normalized());
      }
   };
   typedef Vector4<float>  float4;
   typedef Vector4<double> double4;
}