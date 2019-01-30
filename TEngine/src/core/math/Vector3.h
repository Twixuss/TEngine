#pragma once
#include "Vector2.h"
namespace TEngine::Math {
   template<typename Scalar>
   struct Vector3 : public Vector2<Scalar> {
      using Base = Vector2<Scalar>;
      using Vector = Vector3<Scalar>;
      Scalar z;
      Vector() : Base(0), z(0) {}
      Vector(const Scalar& v) : Base(v), z(v) {}
      Vector(const Scalar& x, const Scalar& y) : Base(x, y), z(0) {}
      Vector(const Scalar& x, const Scalar& y, const Scalar& z) : Base(x, y), z(z) {}
      Vector(const Vector& v) : Base(v.x, v.y), z(v.z) {}
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
      Vector& Set(const Scalar& x, const Scalar& y, const Scalar& z) {
         this->x = x;
         this->y = y;
         this->z = z;
         return *this;
      }
      Scalar  LengthSqr() const {
         return x * x + y * y + z * z;
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
         return a;
      }
      friend Vector& operator-=(Vector& a, const Scalar& b) {
         a.x -= b;
         a.y -= b;
         a.z -= b;
         return a;
      }
      friend Vector& operator*=(Vector& a, const Scalar& b) {
         a.x *= b;
         a.y *= b;
         a.z *= b;
         return a;
      }
      friend Vector& operator/=(Vector& a, const Scalar& b) {
         a.x /= b;
         a.y /= b;
         a.z /= b;
         return a;
      }
      friend Vector& operator+=(Vector& a, const Vector& b) {
         a.x += b.x;
         a.y += b.y;
         a.z += b.z;
         return a;
      }
      friend Vector& operator-=(Vector& a, const Vector& b) {
         a.x -= b.x;
         a.y -= b.y;
         a.z -= b.z;
         return a;
      }
      friend Vector& operator*=(Vector& a, const Vector& b) {
         a.x *= b.x;
         a.y *= b.y;
         a.z *= b.z;
         return a;
      }
      friend Vector& operator/=(Vector& a, const Vector& b) {
         a.x /= b.x;
         a.y /= b.y;
         a.z /= b.z;
         return a;
      }
      friend Vector  operator+ (const Vector& a) {
         return Vector(+a.x, +a.y, +a.z);
      }
      friend Vector  operator- (const Vector& a) {
         return Vector(-a.x, -a.y, -a.z);
      }
      friend Vector  operator+ (const Vector& a, const Scalar& b) {
         return Vector(a.x + b, a.y + b, a.z + b);
      }
      friend Vector  operator- (const Vector& a, const Scalar& b) {
         return Vector(a.x - b, a.y - b, a.z - b);
      }
      friend Vector  operator* (const Vector& a, const Scalar& b) {
         return Vector(a.x * b, a.y * b, a.z * b);
      }
      friend Vector  operator/ (const Vector& a, const Scalar& b) {
         return Vector(a.x * b, a.y * b, a.z * b);
      }
      friend Vector  operator+ (const Vector& a, const Vector& b) {
         return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
      }
      friend Vector  operator- (const Vector& a, const Vector& b) {
         return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
      }
      friend Vector  operator* (const Vector& a, const Vector& b) {
         return Vector(a.x * b.x, a.y * b.y, a.z * b.z);
      }
      friend Vector  operator/ (const Vector& a, const Vector& b) {
         return Vector(a.x / b.x, a.y / b.y, a.z / b.z);
      }
      friend Scalar  operator^ (const Vector& a, const Vector& b) {
         return acos(Dot(a, b) / (a.Length() * b.Length()));
      }
      template<typename T>
      friend std::basic_ostream<T> & operator<<(std::basic_ostream<T>& stream, const Vector& v) {
         stream << L"[x:" << v.x << L", y:" << v.y << L", z:" << v.z << L']';
         return stream;
      }
      static Scalar Dot(const Vector& a, const Vector& b) {
         return a.x * b.x + a.y * b.y + a.z * b.z;
      }
      static Vector Cross(const Vector& a, const Vector& b) {
         return Vector(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
            );
      }
      static Vector Project(const Vector& a, const Vector& b) {
         return b.Normalized() * Dot(a, b.Normalized());
      }
   };
   typedef Vector3<float> float3;
   typedef Vector3<double> double3;
}