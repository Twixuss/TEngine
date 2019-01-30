#pragma once
#include "core/window.h"
#include "core/graphics/shader.h"
#include "core/graphics/mesh.h"
#include "core/Clock.h"
#include "core/graphics/MeshRenderer.h"
#include "core/graphics/Material.h"
namespace TEngine
{
   enum class GraphicsAPI
   {
      Direct3D9,
      Direct3D10,
      Direct3D11,
      Direct3D12
   };
   class LibraryInterface NoVirtualTable Renderer
   {
   public:
      virtual void Init(const Window& wnd) = 0;
      virtual void Clear(const Color& color) = 0;
      virtual void ResizeBuffers(const Window& wnd) = 0;
      virtual void Prepare(const Clock& time) = 0;

      virtual bool GetFullscreen() = 0;
      virtual void SetFullscreen(bool value) = 0;

      virtual void DrawLine(float3 a, float3 b) = 0;
      virtual void DrawLines(float3 *first, uint count) = 0;

      virtual void Draw(Mesh *mesh, const Shader *shader) = 0;
      virtual void Draw(Mesh *mesh, Material *mat) = 0;
      virtual void Draw(MeshRenderer *r) = 0;

      virtual void Present() = 0;

      virtual Mesh* CreateMesh() = 0;
      virtual Mesh* CreateMesh(float3 *positions, uint vertexCount, uint *indices, uint indexCount) = 0;

      virtual Shader* GetShader(const String& filename) = 0;
      virtual void SetActiveShader(const Shader& shader) = 0;

      virtual Material* GetMaterial(const String&) = 0;

      virtual MeshRenderer* CreateMeshRenderer(Mesh *mesh, Material *mat, float3 pos, float3 rot, float3 scl) = 0;

      virtual const String GetName() = 0;

      virtual ~Renderer()
      {
      }

      static Renderer* Create(GraphicsAPI api);
   };
}
