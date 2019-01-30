#pragma once
#include "core/common.h"
namespace TEngine
{
   using namespace Math;
   class LibraryInterface Transform
   {
   public:
      Transform(float3 pos, float3 rot, float3 scl, Transform *parent = nullptr);
      void SetPosition(float x, float y, float z);
      void SetRotation(float x, float y, float z);
      void SetScaling(float x, float y, float z);
      void Translate(float x, float y, float z);
      void TranslateRelative(float x, float y, float z);
      void Rotate(float x, float y, float z);
      void SetPosition(float3 v);
      void SetRotation(float3 v);
      void SetScaling(float3 v);
      void Translate(float3 v);
      void TranslateRelative(float3 v);
      void Rotate(float3 v);
      void SetParent(Transform* p);
      Transform* GetParent() const;
      float4 GetPosition() const;
      float4 GetRotation() const;
      float4 GetScaling() const;
      float4 GetLocalPosition() const;
      float4 GetLocalRotation() const;
      float4 GetLocalScaling() const;
      float4 GetRightDir() const;
      float4 GetUpDir() const;
      float4 GetForwardDir() const;
      void SetPosition(const float4 &v);
      void SetRotation(const float4 &v);
      void SetScaling(const float4 &v);
      void Translate(const float4 &v);
      void TranslateRelative(const float4 &v);
      void Rotate(const float4 &v);
   private:
      void BecomeDirty();
   private:
      float4 m_Position, m_Rotation, m_Scaling;
      Transform *m_Parent;
      List<Transform*> m_Children;
      bool m_Dirty;

      friend class RendererD3D11;
   };
}