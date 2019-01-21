#pragma once
namespace TEngine::Math {
   template<typename Scalar>
   struct Vector2 {
      using Self = Vector2<Scalar>;
      using SelfRef = Vector2<Scalar>&;
      using SelfCRef = Vector2<Scalar>& const;
      Scalar x, y;
      Vector2() : x(0), y(0) {}
      Vector2(Scalar v) : x(v), y(v) {}
      Vector2(Scalar x, Scalar y) : x(x), y(y) {}
      Vector2(SelfCRef v) : x(v.x), y(v.y) {}
      SelfRef Set(Scalar x, Scalar y) {
         this->x = x;
         this->y = y;
         return *this;
      }
      SelfRef Set(SelfCRef v) {
         this->x = v.x;
         this->y = v.y;
         return *this;
      }
      Scalar  LengthSqr() const {
         return x * x + y * y;
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
         return Vector2(+x, +y);
      }
      Self    operator- () {
         return Vector2(-x, -y);
      }
      SelfRef operator= (const Scalar  &v) {
         x = v;
         y = v;
         return *this;
      }
      SelfRef operator+=(const Scalar  &v) {
         x += v;
         y += v;
         return *this;
      }
      SelfRef operator-=(const Scalar  &v) {
         x -= v;
         y -= v;
         return *this;
      }
      SelfRef operator*=(const Scalar  &v) {
         x *= v;
         y *= v;
         return *this;
      }
      SelfRef operator/=(const Scalar  &v) {
         x /= v;
         y /= v;
         return *this;
      }
      Self    operator+ (const Scalar  &v) {
         return Vector2(x + v, y + v);
      }
      Self    operator- (const Scalar  &v) {
         return Vector2(x - v, y - v);
      }
      Self    operator* (const Scalar  &v) {
         return Vector2(x * v, y * v);
      }
      Self    operator/ (const Scalar  &v) {
         return Vector2(x / v, y / v);
      }
      SelfRef operator= (SelfCRef v) {
         x = v.x;
         y = v.y;
         return *this;
      }
      SelfRef operator+=(SelfCRef v) {
         x += v.x;
         y += v.y;
         return *this;
      }
      SelfRef operator-=(SelfCRef v) {
         x -= v.x;
         y -= v.y;
         return *this;
      }
      SelfRef operator*=(SelfCRef v) {
         x *= v.x;
         y *= v.y;
         return *this;
      }
      SelfRef operator/=(SelfCRef v) {
         x /= v.x;
         y /= v.y;
         return *this;
      }
      Self    operator+ (SelfCRef v) {
         return Vector2(x + v.x, y + v.y);
      }
      Self    operator- (SelfCRef v) {
         return Vector2(x - v.x, y - v.y);
      }
      Self    operator* (SelfCRef v) {
         return Vector2(x * v.x, y * v.y);
      }
      Self    operator/ (SelfCRef v) {
         return Vector2(x / v.x, y / v.y);
      }
      Scalar  operator^ (SelfCRef v) {
         return acos(Dot(*this, v) / (Length() * v.Length()));
      }
      static Scalar Dot(SelfCRef a, SelfCRef b) {
         return a.x * b.x + a.y * b.y;
      }
      template<typename T>
      friend std::basic_ostream<T> & operator<<(std::basic_ostream<T> & stream, SelfCRef vec) {
         stream << "[x:" << vec.x << ", y:" << vec.y << ']';
         return stream;
      }
   };
   typedef Vector2<long> long2;
   typedef Vector2<float> float2;
   typedef Vector2<double> double2;
}