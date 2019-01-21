#pragma once
#include "core/common.h"
namespace TEngine {
   using namespace Math;
   struct TENGINE_API Transform  {
      inline Transform(float3 pos, float3 rot, float3 scl, Transform *parent = nullptr) :
         m_Position(XMVectorSet(pos.x, pos.y, pos.z, 0)),
         m_Rotation(XMVectorSet(rot.x, rot.y, rot.z, 0)),
         m_Scaling (XMVectorSet(scl.x, scl.y, scl.z, 0)),
         m_Dirty(true),
         m_Parent(parent) {}
      inline void SetPosition      (float x, float y, float z) { _SetPosition      (XMVectorSet(x, y, z, 0)); }
      inline void SetRotation      (float x, float y, float z) { _SetRotation      (XMVectorSet(x, y, z, 0)); }
      inline void SetScaling       (float x, float y, float z) { _SetScaling       (XMVectorSet(x, y, z, 0)); }
      inline void Translate        (float x, float y, float z) { _Translate        (XMVectorSet(x, y, z, 0)); }
      inline void TranslateRelative(float x, float y, float z) { _TranslateRelative(XMVectorSet(x, y, z, 0)); }
      inline void Rotate           (float x, float y, float z) { _Rotate           (XMVectorSet(x, y, z, 0)); }
      inline void SetPosition      (float3 v) { SetPosition      (v.x, v.y, v.z); }
      inline void SetRotation      (float3 v) { SetRotation      (v.x, v.y, v.z); }
      inline void SetScaling       (float3 v) { SetScaling       (v.x, v.y, v.z); }
      inline void Translate        (float3 v) { Translate        (v.x, v.y, v.z); }
      inline void TranslateRelative(float3 v) { TranslateRelative(v.x, v.y, v.z); }
      inline void Rotate           (float3 v) { Rotate           (v.x, v.y, v.z); }
      inline void SetParent(Transform *p) { m_Parent = p; }
      inline Transform *GetParent() const { return m_Parent; }
      inline float4 GetPosition     () const { 
         if (m_Parent) {
            return XMVectorAdd(m_Parent->GetPosition().xmv, XMVector4Transform(m_Position.xmv, XMMatrixRotationRollPitchYawFromVector(m_Parent->GetRotation().xmv)));
         }
         return m_Position;
      }
      inline float4 GetRotation     () const {
         if (m_Parent) {
            return m_Rotation + m_Parent->GetRotation();
         }
         return m_Rotation;
      }
      inline float4 GetScaling      () const {
         if (m_Parent) {
            return m_Scaling * m_Parent->GetScaling();
         }
         return m_Scaling;
      }
      inline float4 GetLocalPosition() const { return m_Position; }
      inline float4 GetLocalRotation() const { return m_Rotation; }
      inline float4 GetLocalScaling () const { return m_Scaling ; }
      inline float4 GetRightDir     () const {
         return XMVector4Transform(XMVectorSet(1, 0, 0, 0), XMMatrixRotationRollPitchYawFromVector(GetRotation().xmv));
      }
      inline float4 GetUpDir        () const {
         return XMVector4Transform(XMVectorSet(0, 1, 0, 0), XMMatrixRotationRollPitchYawFromVector(GetRotation().xmv));
      }
      inline float4 GetForwardDir   () const {
         return XMVector4Transform(XMVectorSet(0, 0, 1, 0), XMMatrixRotationRollPitchYawFromVector(GetRotation().xmv));
      }
      inline void _SetPosition      (const float4 &v) {
         if (v == m_Position)
            return;
         m_Position = v;
         m_Dirty = true;
      }
      inline void _SetRotation      (const float4 &v) {
         if (v == m_Rotation)
            return;
         m_Rotation = v;
         m_Dirty = true;
      }
      inline void _SetScaling       (const float4 &v) {
         if (v == m_Scaling)
            return;
         m_Scaling = v;
         m_Dirty = true;
      }
      inline void _Translate        (const float4 &v) {
         if (v == float4::Zero())
            return;
         m_Position += v;
         m_Dirty = true;
      }
      inline void _TranslateRelative(const float4 &v) {
         if (v == float4::Zero())
            return;
         m_Position += XMVector4Transform(v.xmv, XMMatrixRotationRollPitchYawFromVector(m_Rotation.xmv));
         m_Dirty = true;
      }
      inline void _Rotate           (const float4 &v) {
         if (v == float4::Zero())
            return;
         m_Rotation += v;
         m_Dirty = true;
      }
      inline bool _IsDirty() const { return m_Dirty; }
      inline void _SetDirty(bool v) { m_Dirty = v; }
   private:
      float4 m_Position, m_Rotation, m_Scaling;
      Transform *m_Parent;
      bool m_Dirty;
   };
}