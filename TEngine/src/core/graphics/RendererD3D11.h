#pragma once
#include "renderer.h"
namespace TEngine
{
   using namespace Microsoft::WRL;
   class RendererD3D11 : public Renderer
   {
   public:
      RendererD3D11();
      void Init(const Window& wnd)override;
      void Clear(const Color& color)override;
      void ResizeBuffers(const Window& wnd)override;
      void Prepare(const Clock& time)override;
      void Present()override;
      bool GetFullscreen()override;
      void SetFullscreen(bool value)override;
      Mesh* CreateMesh()override;
      Mesh* CreateMesh(float3 *positions, uint vertexCount, uint *indices, uint indexCount)override;
      Material* GetMaterial(const String&)override;
      void DrawLine(float3 a, float3 b)override;
      void DrawLines(float3 *first, uint count)override;
      void Draw(Mesh *mesh, const Shader *shader)override;
      void Draw(Mesh *mesh, Material *mat)override;
      void Draw(MeshRenderer *r)override;
      MeshRenderer* CreateMeshRenderer(Mesh *mesh, Material *mat, float3 pos, float3 rot, float3 scl)override;
      Shader* GetShader(const String& filename) override;
      void SetActiveShader(const Shader& shader)override;
      const String GetName() override;
      ~RendererD3D11();
   private:
      ComPtr<IDXGISwapChain> m_SwapChain;
      ComPtr<ID3D11Device> m_Device;
      ComPtr<ID3D11DeviceContext> m_DevCon;
      ComPtr<ID3D11RenderTargetView> m_BackBuffer;
      ComPtr<ID3D11DepthStencilView> m_DepthStencil;
      ComPtr<ID3D11Buffer> m_FrameCBuffer;
   };
}
