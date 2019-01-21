#pragma once
#include "common.h"
#include "console.h"
#include "ShaderBuffers.h"
namespace TEngine {
   struct TENGINE_API Shader {
      Shader();
      void Release();
      ~Shader();
      static Shader *CreateFromFile(CWString filename);
      static Shader *CreateFromSource(CString sourceCode);
      inline uint &GetVertexSize() { return m_Stride; }
      //inline ShaderBuffers &GetBuffers() { return m_Buffers; }
      inline uint GetID() const { return m_ID; }
   private:
      uint m_Stride;
      //ShaderBuffers m_Buffers;
      uint m_ID;
   };
}