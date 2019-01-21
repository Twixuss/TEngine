#pragma once
#include "renderer.h"
namespace TEngine {
   struct RendererD3D11 : public Renderer {
      RendererD3D11();
      void Init()override;
      void Clear(const Color& color)override;
      void ResizeBuffers(uint w, uint h)override;
      void Prepare(const Clock& time)override;
      void Present()override;
      bool GetFullscreen()override;
      void SetFullscreen(bool value)override;
      void CreateMeshBuffers(Mesh *mesh)override;
      void CreateMaterialBuffers(Material *mat)override;
      void DrawLine(float3 a, float3 b)override;
      void DrawLines(float3 *first, uint count)override;
      void Draw(Mesh *mesh, Shader *shader)override;
      void Draw(Mesh *mesh, Material *mat)override;
      void Draw(MeshRenderer *r)override;
      void CreateMeshRenderer(MeshRenderer *r)override;
      uint GetNewShaderID()override;
      bool CompileShaderFromFile(Shader *shader, CWString filename)override;
      void SetActiveShader(Shader *shader)override;
      CString GetName() override;
      void ReleaseShader(Shader *shader) override;
      void Release() override;
      ~RendererD3D11();
   private:
      IDXGISwapChain *m_SwapChain;
      ID3D11Device *m_Device;
      ID3D11DeviceContext *m_DevCon;
      ID3D11RenderTargetView *m_BackBuffer;
      ID3D11Buffer *m_FrameCBuffer;
   };
}