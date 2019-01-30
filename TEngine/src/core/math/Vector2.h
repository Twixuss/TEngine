#pragma once
//#include "Vector.h"
namespace TEngine::Math {
   template<typename Scalar>
   struct Vector2 { 
      using Vector = Vector2<Scalar>;
      Scalar x, y;
      Vector() : x(0), y(0) {}
      Vector(const Scalar& v) : x(v), y(v) {}
      Vector(const Scalar& x, const Scalar& y) : x(x), y(y) {}
      Vector(const Vector& v) : x(v.x), y(v.y) {}
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
      Vector& Set(const Scalar& x, const Scalar& y) {
         this->x = x;
         this->y = y;
         return *this;
      }
      Vector  Copy() {
         return Vector(*this);
      }
      Scalar  LengthSqr() const {
         return x * x + y * y;
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
         return *this = v.Normalized() * Dot(*this, v.Normalized());
      }
      Vector  ProjectedOn(const Vector& v) const {
         return v.Normalized() * Dot(*this, v.Normalized());
      }
      friend bool operator==(const Vector& a, const Vector& b) {
         return a.x == b.x && a.y == b.y;
      }
      friend bool operator!=(const Vector& a, const Vector& b) {
         return !operator==(a, b);
      }
      friend Vector& operator+=(Vector& a, const Scalar&  b) {
         x += v;
         y += v;
         return a;
      }
      friend Vector& operator-=(Vector& a, const Scalar&  b) {
         x -= v;
         y -= v;
         return a;
      }
      friend Vector& operator*=(Vector& a, const Scalar&  b) {
         x *= v;
         y *= v;
         return a;
      }
      friend Vector& operator/=(Vector& a, const Scalar&  b) {
         x /= v;
         y /= v;
         return a;
      }
      friend Vector& operator+=(Vector& a, const Vector& b) {
         x += v.x;
         y += v.y;
         return a;
      }
      friend Vector& operator-=(Vector& a, const Vector& b) {
         x -= v.x;
         y -= v.y;
         return a;
      }
      friend Vector& operator*=(Vector& a, const Vector& b) {
         x *= v.x;
         y *= v.y;
         return a;
      }
      friend Vector& operator/=(Vector& a, const Vector& b) {
         x /= v.x;
         y /= v.y;
         return a;
      }
      friend Vector  operator+ (const Vector& a) {
         return Vector(+a.x, +a.y);
      }
      friend Vector  operator- (const Vector& a) {
         return Vector(-a.x, -a.y);
      }
      friend Vector  operator+ (const Vector& a, const Scalar&  b) {
         return Vector(x + v, y + v);
      }
      friend Vector  operator- (const Vector& a, const Scalar&  b) {
         return Vector(x - v, y - v);
      }
      friend Vector  operator* (const Vector& a, const Scalar&  b) {
         return Vector(x * v, y * v);
      }
      friend Vector  operator/ (const Vector& a, const Scalar&  b) {
         return Vector(x / v, y / v);
      }
      friend Vector  operator+ (const Vector& a, const Vector& b) {
         return Vector(a.x + b.x, a.y + b.y);
      }
      friend Vector  operator- (const Vector& a, const Vector& b) {
         return Vector(a.x - b.x, a.y - b.y);
      }
      friend Vector  operator* (const Vector& a, const Vector& b) {
         return Vector(a.x * b.x, a.y * b.y);
      }
      friend Vector  operator/ (const Vector& a, const Vector& b) {
         return Vector(a.x / b.x, a.y / b.y);
      }
      friend Scalar  operator^ (const Vector& a, const Vector& b) {
         return acos(Dot(a, b) / (a.Length() * b.Length()));
      }
      template<typename T>
      friend std::basic_ostream<T> & operator<<(std::basic_ostream<T> & stream, const Vector& vec) {
         stream << "[x:" << vec.x << ", y:" << vec.y << ']';
         return stream;
      }
      static Scalar Dot(const Vector& a, const Vector& b) {
         return a.x * b.x + a.y * b.y;
      }
   };
   typedef Vector2<long> long2;
   typedef Vector2<float> float2;
   typedef Vector2<double> double2;
}