#pragma once
#include "core/common.h"
#include "core/console.h"
namespace TEngine
{
   class LibraryInterface NoVirtualTable Shader
   {
      friend class RendererD3D11;
   public:
      Shader(const Shader&) = delete;
      virtual ~Shader()
      {
      }
      //inline ShaderBuffers &GetBuffers() { return m_Buffers; }
      inline String& GetFilename()
      {
         return m_Filename;
      }
   protected:
      Shader();
      Shader(const String& filename);
   private:
      uint m_Stride;
      //ShaderBuffers m_Buffers;
      uint m_ID;
      String m_Filename;
   };
}
