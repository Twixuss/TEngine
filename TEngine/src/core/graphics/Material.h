#pragma once
#include "core/common.h"
namespace TEngine
{
   using namespace Math;
   class LibraryInterface NoVirtualTable Material
   {
   public:
      Material(const Material&) = delete;
      virtual ~Material()
      {
      }
      inline void SetProperties(const std::vector<float>& props)
      {
         m_Properties = props;
      }
      inline const Shader *GetShader() const
      {
         return m_Shader;
      }
      inline std::vector<float>& GetProperties()
      {
         return m_Properties;
      }
      inline void SetFloat(int i, float f)
      {
         m_Properties[i] = f;
         OnChange();
      }
   protected:
      Material()
      {

      }
      virtual void OnChange() = 0;
   private:
      String m_Filename;
      const Shader *m_Shader;
      std::vector<float> m_Properties;
      uint m_ID;

      friend class RendererD3D11;
   };
}