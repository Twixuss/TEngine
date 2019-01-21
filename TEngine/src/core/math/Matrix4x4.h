#pragma once
#include "core/math/Vector4.h"
namespace TEngine::Math {
   template<class Scalar>
   struct Matrix4x4 {
      Vector4<Scalar> i, j, k, l;
      Matrix4x4() :i(0), j(0), k(0), l(0) {}
      Matrix4x4(Scalar v) :i(v), j(v), k(v), l(v) {}
      Matrix4x4(Vector4<Scalar> v) :i(v), j(v), k(v), l(v) {}
      Matrix4x4(Vector4<Scalar> i, Vector4<Scalar> j, Vector4<Scalar> k, Vector4<Scalar> l) :i(i), j(j), k(k), l(l) {}
      Matrix4x4(
         Scalar ix, Scalar jx, Scalar kx, Scalar lx,
         Scalar iy, Scalar jy, Scalar ky, Scalar ly,
         Scalar iz, Scalar jz, Scalar kz, Scalar lz,
         Scalar iw, Scalar jw, Scalar kw, Scalar lw)
         :
         i(ix, iy, iz, iw),
         j(jx, jy, jz, jw),
         k(kx, ky, kz, kw),
         l(lx, ly, lz, lw)
      {}
      explicit Matrix4x4(XMMATRIX m) : i(m[0]), j(m[1]), k(m[2]), l(m[3]) {}
      void Set(Matrix4x4<Scalar> m) {
         i.Set(m.i);
         j.Set(m.j);
         k.Set(m.k);
         l.Set(m.l);
      }
      operator XMMATRIX() const { return XMMATRIX(i, j, k, l); };
      Vector4<Scalar> operator *(Vector4<Scalar> v) {
         return Matrix4x4<Scalar>(
            m * i,
            m * j,
            m * k,
            m * l
            );
      }
      Matrix4x4<Scalar> operator *(Matrix4x4<Scalar> m) {
         return reinterpret_cast<Matrix4x4<Scalar>>(XMMatrixMultiply(reinterpret_cast<XMMATRIX>(*this), reinterpret_cast<XMMATRIX>(m)));
      }
      static constexpr Matrix4x4<Scalar> Identity() {
         return Matrix4x4<Scalar>(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
            );
      }
      static constexpr Matrix4x4<Scalar> Translation(float x, float y, float z) {
         return Matrix4x4<Scalar>(
            1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1
            );
      }
      static constexpr Matrix4x4<Scalar> Translation(Vector3<Scalar> v) {
         return Translation(v.x, v.y, v.z);
      }
      static constexpr Matrix4x4<Scalar> RotationX(float a) {
         return Matrix4x4<Scalar>(
            1, 0, 0, 0,
            0, cos(a), sin(a), 0,
            0, -sin(a), cos(a), 0,
            0, 0, 0, 1
            );
      }
      static constexpr Matrix4x4<Scalar> RotationY(float a) {
         return Matrix4x4<Scalar>(
            cos(a), 0, sin(a), 0,
            0, 1, 0, 0,
            -sin(a), 0, cos(a), 0,
            0, 0, 0, 1
            );
      }
      static constexpr Matrix4x4<Scalar> RotationZ(float a) {
         return Matrix4x4<Scalar>(
            cos(a), sin(a), 0, 0,
            -sin(a), cos(a), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
            );
      }
      static constexpr Matrix4x4<Scalar> RotationXYZ(float x, float y, float z) {
         return RotationX(x) * RotationY(y) * RotationZ(z);
      }
      static constexpr Matrix4x4<Scalar> RotationXYZ(Vector3<Scalar> v) {
         return RotationX(v.x) * RotationY(v.y) * RotationZ(v.z);
      }
      static constexpr Matrix4x4<Scalar> Scale(float x, float y, float z) {
         return Matrix4x4<Scalar>(
            x, 0, 0, 0,
            0, y, 0, 0,
            0, 0, z, 0,
            0, 0, 0, 1
            );
      }
      template<typename T>
      friend std::basic_ostream<T> & operator<<(std::basic_ostream<T> & stream, Matrix4x4<Scalar> m) {
         constexpr int W = 5, P = 2;
         stream
            << '[' << std::setprecision(P) << std::setw(W) << m.i.x << " ]["
            << std::setprecision(P) << std::setw(W) << m.j.x << " ]["
            << std::setprecision(P) << std::setw(W) << m.k.x << " ]["
            << std::setprecision(P) << std::setw(W) << m.l.x
            << " ]\n               [" << std::setprecision(P) << std::setw(W) << m.i.y << " ]["
            << std::setprecision(P) << std::setw(W) << m.j.y << " ]["
            << std::setprecision(P) << std::setw(W) << m.k.y << " ]["
            << std::setprecision(P) << std::setw(W) << m.l.y
            << " ]\n               [" << std::setprecision(P) << std::setw(W) << m.i.z << " ]["
            << std::setprecision(P) << std::setw(W) << m.j.z << " ]["
            << std::setprecision(P) << std::setw(W) << m.k.z << " ]["
            << std::setprecision(P) << std::setw(W) << m.l.z
            << " ]\n               [" << std::setprecision(P) << std::setw(W) << m.i.w << " ]["
            << std::setprecision(P) << std::setw(W) << m.j.w << " ]["
            << std::setprecision(P) << std::setw(W) << m.k.w << " ]["
            << std::setprecision(P) << std::setw(W) << m.l.w << " ]";
         return stream;
      }
   };
   typedef Matrix4x4<float> float4x4;
   typedef Matrix4x4<double> double4x4;
}