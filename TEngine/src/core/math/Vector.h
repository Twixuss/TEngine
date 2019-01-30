/*
#pragma once
#define RETURN_SUM_OF_ELEMENTS(expr) Vector result;expr;Scalar sum = (Scalar)0;for (int i = 0;i < result.GetDimensions();i++) { sum += result[i];}return sum;
#define RETURN_NEW_VECTOR(expr) Vector result; expr; return result;
#define FOR_EACH_DIMENSION(expr)  for (int i = 0;i < dimensions;i++) { expr; }
namespace TEngine::Math {
   template<int dimensions, typename Scalar>
   struct Vector {
      constexpr int GetDimensions() const { return dimensions; }
      Scalar v[dimensions];
      Vector() {
         static_assert(dimensions > 0, "Vector must contain at least 1 elements");
         FOR_EACH_DIMENSION(v[i] = (Scalar)0);
      }
      template<typename... Params>
      Vector(Params ...params) {
         static_assert(dimensions > 0, "Vector must contain at least 1 elements");
         FOR_EACH_DIMENSION(v[i] = (Scalar)0);
         Init(0, params...);
      }
      Vector(const Vector& other) {
         FOR_EACH_DIMENSION(v[i] = other.v[i]);
      }
      Scalar operator[](int i) const {
         return v[i];
      }
      Scalar& operator[](int i) {
         return v[i];
      }
      template<typename T>
      friend std::basic_ostream<T>& operator<<(std::basic_ostream<T>& stream, const Vector& v) {
         stream << '[' << v[0];
         for (int i = 1;i < v.GetDimensions();i++) {
            stream << ',' << v[i];
         }
         return stream << ']';
      }
      static Scalar Dot(const Vector& a, const Vector& b) {
         RETURN_SUM_OF_ELEMENTS(FOR_EACH_DIMENSION(result[i] = a[i] * b[i]));
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
   private:
      template<typename Param>
      void Init(int i, Param param) {
         v[i] = param;
      }
      template<typename Param, typename... Params>
      void Init(int i, Param param, Params ...params) {
         v[i] = param;
         Init(++i, params...);
      }
   };
   template<int d1, int d2, typename s1, typename s2>
   auto& operator+=(Vector<d1, s1>& a, const Vector<d2, s2>& b) {
      for (int i = 0;i < Min(a.GetDimensions(), b.GetDimensions());i++) {
         a[i] += b[i];
      }
      return a;
   }
   template<int d1, int d2, typename s1, typename s2>
   auto& operator-=(Vector<d1, s1>& a, const Vector<d2, s2>& b) {
      for (int i = 0;i < Min(a.GetDimensions(), b.GetDimensions());i++) {
         a[i] -= b[i];
      }
      return a;
   }
   template<int d1, int d2, typename s1, typename s2>
   auto& operator*=(Vector<d1, s1>& a, const Vector<d2, s2>& b) {
      for (int i = 0;i < Min(a.GetDimensions(), b.GetDimensions());i++) {
         a[i] *= b[i];
      }
      return a;
   }
   template<int d1, int d2, typename s1, typename s2>
   auto& operator/=(Vector<d1, s1>& a, const Vector<d2, s2>& b) {
      for (int i = 0;i < Min(a.GetDimensions(), b.GetDimensions());i++) {
         a[i] /= b[i];
      }
      return a;
   }
   template<int d, typename s>
   auto  operator+ (const Vector<d, s>& a) {
      Vector<d, s> result;
      for (int i = 0;i < a.GetDimensions();i++) {
         result[i] = +a[i];
      }
      return result;
   }
   template<int d, typename s>
   auto  operator- (const Vector<d, s>& a) {
      Vector<d, s> result;
      for (int i = 0;i < a.GetDimensions();i++) {
         result[i] = -a[i];
      }
      return result;
   }
   template<int d1, int d2, typename s1, typename s2>
   auto  operator+ (const Vector<d1, s1>& a, const Vector<d2, s2>& b) {
      Vector<d, s> result;
      for (int i = 0;i < Min(a.GetDimensions(), b.GetDimensions());i++) {
         result[i] = a[i] + b[i];
      }
      return result;
   }
   template<int d1, int d2, typename s1, typename s2>
   auto  operator- (const Vector<d1, s1>& a, const Vector<d2, s2>& b) {
      Vector<d, s> result;
      for (int i = 0;i < Min(a.GetDimensions(), b.GetDimensions());i++) {
         result[i] = a[i] - b[i];
      }
      return result;
   }
   template<int d1, int d2, typename s1, typename s2>
   auto  operator* (const Vector<d1, s1>& a, const Vector<d2, s2>& b) {
      Vector<d1, s1> result;
      for (int i = 0;i < Min(a.GetDimensions(), b.GetDimensions());i++) {
         result[i] = a[i] * b[i];
      }
      return result;
   }
   template<int d1, int d2, typename s1, typename s2>
   auto  operator/ (const Vector<d1, s1>& a, const Vector<d2, s2>& b) {
      Vector<d1, s1> result;
      for (int i = 0;i < Min(a.GetDimensions(), b.GetDimensions());i++) {
         result[i] = a[i] / b[i];
      }
      return result;
   }
}
#undef RETURN_NEW_VECTOR
#undef FOR_EACH_DIMENSION
*/