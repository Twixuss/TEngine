#pragma once
#include "core/common.h"
namespace TEngine {
   using namespace Math;
   struct TENGINE_API Material {
      Material(Shader *shader) : m_Shader(shader), m_Properties(nullptr), m_PropertyCount(0), m_Dirty(true) {
         data.D3D11.CBuffer = nullptr;
      }
      inline void SetProperties(float *props, uint count) {
         if (m_Properties)
            delete m_Properties;
         m_Properties = new float[count];
         m_PropertyCount = count;
         while (count--) {
            m_Properties[count] = props[count];
         }
      }
      inline Shader *GetShader() const { return m_Shader; }
      inline float *GetProperties() const { return m_Properties; }
      inline uint GetPropertyCount() const { return m_PropertyCount; }
      inline bool _IsDirty() const { return m_Dirty; }
      inline void _SetDirty(bool v) { m_Dirty = v; }
      inline auto &_GetBuffers() { return data; }
   private:
      Shader *m_Shader;
      float *m_Properties;
      uint m_PropertyCount;
      bool m_Dirty = true;
      union {
         struct {
            ID3D10Buffer *CBuffer;
         }D3D10;
         struct {
            ID3D11Buffer *CBuffer;
         }D3D11;
      } data;
   };
}