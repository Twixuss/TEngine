#include "precompiled.h"
#include "RendererEmpty.h"
namespace TEngine {
   void RendererEmpty::Init()
   {
   }
   void RendererEmpty::Clear(const Color& color)
   {
   }
   void RendererEmpty::ResizeBuffers(uint w, uint h)
   {
   }
   void RendererEmpty::Prepare(const Clock& time)
   {
   }
   void RendererEmpty::Present()
   {
   }
   bool RendererEmpty::GetFullscreen()
   {
      return false;
   }
   void RendererEmpty::SetFullscreen(bool value)
   {
   }
   void RendererEmpty::CreateMeshBuffers(Mesh * mesh)
   {
   }
   void RendererEmpty::CreateMaterialBuffers(Material * mat)
   {
   }
   void RendererEmpty::DrawLine(float3 a, float3 b)
   {
   }
   void RendererEmpty::Draw(Mesh * mesh, Shader * shader)
   {
   }
   void RendererEmpty::Draw(Mesh * mesh, Material * mat)
   {
   }
   void RendererEmpty::Draw(MeshRenderer * r)
   {
   }
   void RendererEmpty::CreateMeshRenderer(MeshRenderer * r)
   {
   }
   uint RendererEmpty::GetNewShaderID()
   {
      return 0;
   }
   bool RendererEmpty::CompileShaderFromFile(Shader * shader, CWString filename)
   {
      return true;
   }
   void RendererEmpty::SetActiveShader(Shader * shader)
   {
   }
   CString RendererEmpty::GetName()
   {
      return "None";
   }
   void RendererEmpty::ReleaseShader(Shader * shader)
   {
   }
   void RendererEmpty::Release()
   {
   }
   void RendererEmpty::DrawLines(float3 * first, uint count)
   {
   }
}