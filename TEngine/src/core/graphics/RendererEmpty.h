#pragma once
#include "renderer.h"
namespace TEngine {
   struct TENGINE_API RendererEmpty : public Renderer {
      virtual void Init() override;
      virtual void Clear(const Color& color) override;
      virtual void ResizeBuffers(uint w, uint h) override;
      virtual void Prepare(const Clock& time) override;
      virtual void Present() override;
      virtual bool GetFullscreen() override;
      virtual void SetFullscreen(bool value) override;
      virtual void CreateMeshBuffers(Mesh * mesh) override;
      virtual void CreateMaterialBuffers(Material * mat) override;
      virtual void DrawLine(float3 a, float3 b) override;
      virtual void DrawLines(float3 * first, uint count) override;
      virtual void Draw(Mesh * mesh, Shader * shader) override;
      virtual void Draw(Mesh * mesh, Material * mat) override;
      virtual void Draw(MeshRenderer * r) override;
      virtual void CreateMeshRenderer(MeshRenderer * r) override;
      virtual uint GetNewShaderID() override;
      virtual bool CompileShaderFromFile(Shader * shader, CWString filename) override;
      virtual void SetActiveShader(Shader * shader) override;
      virtual CString GetName() override;
      virtual void ReleaseShader(Shader * shader) override;
      virtual void Release() override;
   };
}