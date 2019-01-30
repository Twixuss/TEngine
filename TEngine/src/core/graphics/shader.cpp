#include "shader.h"
#include "renderer.h"
namespace TEngine
{
   Shader::Shader() :
      m_Stride(0),
      m_Filename(),
      m_ID(-1)
   {
   }
   Shader::Shader(const String& filename) :
      m_Stride(sizeof(float3)), 
      m_Filename(filename),
      m_ID(-1)
   {
   }
}