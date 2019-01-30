#include "Transform.h"
namespace TEngine
{
   Transform::Transform(float3 pos, float3 rot, float3 scl, Transform *parent) :
      m_Position(pos.x, pos.y, pos.z, 0),
      m_Rotation(rot.x, rot.y, rot.z, 0),
      m_Scaling(scl.x, scl.y, scl.z, 0),
      m_Dirty(true),
      m_Parent(parent)
   {
   }
   void Transform::SetPosition(float x, float y, float z)
   {
      SetPosition(XMVectorSet(x, y, z, 0));
   }
   void Transform::SetRotation(float x, float y, float z)
   {
      SetRotation(XMVectorSet(x, y, z, 0));
   }
   void Transform::SetScaling(float x, float y, float z)
   {
      SetScaling(XMVectorSet(x, y, z, 0));
   }
   void Transform::Translate(float x, float y, float z)
   {
      Translate(XMVectorSet(x, y, z, 0));
   }
   void Transform::TranslateRelative(float x, float y, float z)
   {
      TranslateRelative(XMVectorSet(x, y, z, 0));
   }
   void Transform::Rotate(float x, float y, float z)
   {
      Rotate(XMVectorSet(x, y, z, 0));
   }
   void Transform::SetPosition(float3 v)
   {
      SetPosition(v.x, v.y, v.z);
   }
   void Transform::SetRotation(float3 v)
   {
      SetRotation(v.x, v.y, v.z);
   }
   void Transform::SetScaling(float3 v)
   {
      SetScaling(v.x, v.y, v.z);
   }
   void Transform::Translate(float3 v)
   {
      Translate(v.x, v.y, v.z);
   }
   void Transform::TranslateRelative(float3 v)
   {
      TranslateRelative(v.x, v.y, v.z);
   }
   void Transform::Rotate(float3 v)
   {
      Rotate(v.x, v.y, v.z);
   }
   void Transform::SetParent(Transform* p)
   {
      m_Parent = p; 
      p->m_Children.AddInPlace(this);
   }
   Transform* Transform::GetParent() const
   {
      return m_Parent;
   }
   float4 Transform::GetPosition() const
   {
      if (m_Parent)
      {
         return XMVectorAdd(m_Parent->GetPosition().xmv, XMVector4Transform(m_Position.xmv, XMMatrixRotationRollPitchYawFromVector(m_Parent->GetRotation().xmv)));
      }
      return m_Position;
   }
   float4 Transform::GetRotation() const
   {
      if (m_Parent)
      {
         return m_Rotation + m_Parent->GetRotation();
      }
      return m_Rotation;
   }
   float4 Transform::GetScaling() const
   {
      if (m_Parent)
      {
         return m_Scaling * m_Parent->GetScaling();
      }
      return m_Scaling;
   }
   float4 Transform::GetLocalPosition() const
   {
      return m_Position;
   }
   float4 Transform::GetLocalRotation() const
   {
      return m_Rotation;
   }
   float4 Transform::GetLocalScaling() const
   {
      return m_Scaling;
   }
   float4 Transform::GetRightDir() const
   {
      return XMVector4Transform(XMVectorSet(1, 0, 0, 0), XMMatrixRotationRollPitchYawFromVector(GetRotation().xmv));
   }
   float4 Transform::GetUpDir() const
   {
      return XMVector4Transform(XMVectorSet(0, 1, 0, 0), XMMatrixRotationRollPitchYawFromVector(GetRotation().xmv));
   }
   float4 Transform::GetForwardDir() const
   {
      return XMVector4Transform(XMVectorSet(0, 0, 1, 0), XMMatrixRotationRollPitchYawFromVector(GetRotation().xmv));
   }
   void Transform::SetPosition(const float4 &v)
   {
      if (v == m_Position)
         return;
      m_Position = v;
      BecomeDirty();
   }
   void Transform::SetRotation(const float4 &v)
   {
      if (v == m_Rotation)
         return;
      m_Rotation = v;
      BecomeDirty();
   }
   void Transform::SetScaling(const float4 &v)
   {
      if (v == m_Scaling)
         return;
      m_Scaling = v;
      BecomeDirty();
   }
   void Transform::Translate(const float4 &v)
   {
      if (v == float4::Zero())
         return;
      m_Position += v;
      BecomeDirty();
   }
   void Transform::TranslateRelative(const float4 &v)
   {
      if (v == float4::Zero())
         return;
      m_Position += XMVector4Transform(v.xmv, XMMatrixRotationRollPitchYawFromVector(m_Rotation.xmv));
      BecomeDirty();
   }
   void Transform::Rotate(const float4 &v)
   {
      if (v == float4::Zero())
         return;
      m_Rotation += v;
      BecomeDirty();
   }
   void Transform::BecomeDirty()
   {
      m_Dirty = true;
      for (auto& c : m_Children)
      {
         c->BecomeDirty();
      }
   }
}