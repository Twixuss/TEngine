#pragma once
#include "Vector2.h"
namespace TEngine::Math {
   template<typename Scalar>
   struct Vector3 : public Vector2<Scalar> {
      using Base = Vector2<Scalar>;
      using Self = Vector3<Scalar>;
      using SelfRef = Vector3<Scalar>&;
      using SelfCRef = const Vector3<Scalar>&;
      float z;
      Vector3() : Base(0, 0), z(0) {}
      Vector3(Scalar v) : Base(v, v), z(v) {}
      Vector3(Scalar x, Scalar y) : Base(x, y), z(0) {}
      Vector3(Scalar x, Scalar y, Scalar z) : Base(x, y), z(z) {}
      Vector3(SelfCRef v) : Base(v.x, v.y), z(v.z) {}
      SelfRef Set(Scalar x, Scalar y, Scalar z) {
         this->x = x;
         this->y = y;
         this->z = z;
         return *this;
      }
      SelfRef Set(SelfCRef v) {
         this->x = v.x;
         this->y = v.y;
         this->z = v.z;
         return *this;
      }
      Scalar  LengthSqr() const {
         return x * x + y * y + z * z;
      }
      Scalar  Length() const {
         return sqrt(LengthSqr());
      }
      SelfRef Normalize() {
         return *this *= 1.0f / Length();
      }
      Self    Normalized() const {
         return Self(*this) * (1.0f / Length());
      }
      SelfRef ProjectOn(SelfCRef v) {
         return *this = v.Normalized() * Dot(*this, v.Normalized());
      }
      Self    ProjectedOn(SelfCRef v) const {
         return v.Normalized() * Dot(*this, v.Normalized());
      }
      Self    operator+ () {
         return Vector3(+x, +y, +z);
      }
      Self    operator- () {
         return Vector3(-x, -y, -z);
      }
      SelfRef operator= (Scalar   v) {
         x = v;
         y = v;
         z = v;
         return *this;
      }
      Self    operator+ (Scalar   v) {
         return Vector3(x + v, y + v, z + v);
      }
      Self    operator- (Scalar   v) {
         return Vector3(x - v, y - v, z - v);
      }
      Self    operator* (Scalar   v) {
         return Vector3(x * v, y * v, z * v);
      }
      Self    operator/ (Scalar   v) {
         return Vector3(x / v, y / v, z / v);
      }
      SelfRef operator+=(Scalar   v) {
         x += v;
         y += v;
         z += v;
         return *this;
      }
      SelfRef operator-=(Scalar   v) {
         x -= v;
         y -= v;
         z -= v;
         return *this;
      }
      SelfRef operator*=(Scalar   v) {
         x *= v;
         y *= v;
         z *= v;
         return *this;
      }
      SelfRef operator/=(Scalar   v) {
         x /= v;
         y /= v;
         z /= v;
         return *this;
      }
      SelfRef operator= (SelfCRef v) {
         x = v.x;
         y = v.y;
         z = v.z;
         return *this;
      }
      Self    operator+ (SelfCRef v) {
         return Vector3(x + v.x, y + v.y, z + v.z);
      }
      Self    operator- (SelfCRef v) {
         return Vector3(x - v.x, y - v.y, z - v.z);
      }
      Self    operator* (SelfCRef v) {
         return Vector3(x * v.x, y * v.y, z * v.z);
      }
      Self    operator/ (SelfCRef v) {
         return Vector3(x / v.x, y / v.y, z / v.z);
      }
      SelfRef operator+=(SelfCRef v) {
         x += v.x;
         y += v.y;
         z += v.z;
         return *this;
      }
      SelfRef operator-=(SelfCRef v) {
         x -= v.x;
         y -= v.y;
         z -= v.z;
         return *this;
      }
      SelfRef operator*=(SelfCRef v) {
         x *= v.x;
         y *= v.y;
         z *= v.z;
         return *this;
      }
      SelfRef operator/=(SelfCRef v) {
         x /= v.x;
         y /= v.y;
         z /= v.z;
         return *this;
      }
      Scalar  operator^ (SelfCRef v) {
         return acos(Dot(*this, v) / (Length() * v.Length()));
      }
      static Scalar Dot(Self a, Self b) {
         return a.x * b.x + a.y * b.y + a.z * b.z;
      }
      static Self   Cross(Self a, Self b) {
         return Vector3<Scalar>(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
            );
      }
      template<typename T>
      friend std::basic_ostream<T> & operator<<(std::basic_ostream<T> & stream, SelfCRef vec) {
         stream << L"[x:" << vec.x << L", y:" << vec.y << L", z:" << vec.z << L']';
         return stream;
      }
   };
   typedef Vector3<float> float3;
   typedef Vector3<double> double3;
}