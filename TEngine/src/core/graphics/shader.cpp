#include "shader.h"
#include "renderer.h"
namespace TEngine {
   Shader::Shader() : m_Stride(sizeof(float3)) {
      m_ID = Renderer::instance->GetNewShaderID();
   }
   Shader *Shader::CreateFromFile(CWString filename) {
      auto s = new Shader;
      if (!Renderer::instance->CompileShaderFromFile(s, filename)) {
         s->Release();
         static Shader *errorShader = CreateFromFile(L"data/shaders/error.hlsl");
         return errorShader;
      }
      return s;
   }
   Shader *Shader::CreateFromSource(CString src) {
      return nullptr;
   }
   void Shader::Release() {
      Renderer::instance->ReleaseShader(this);
   }
   Shader::~Shader() {
      Release();
   }
}