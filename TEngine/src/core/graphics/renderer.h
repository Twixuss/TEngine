#pragma once
#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "Clock.h"
#include "MeshRenderer.h"
#include "Material.h"
namespace TEngine {
   enum class GraphicsAPI {
      None,
      Direct3D9,
      Direct3D10,
      Direct3D11,
      Direct3D12
   };
   struct DECLSPEC_NOVTABLE TENGINE_API Renderer {
      virtual void Init() = 0;
      virtual void Clear(const Color& color) = 0;
      virtual void ResizeBuffers(uint w, uint h) = 0;
      virtual void Prepare(const Clock& time) = 0;
      virtual void Present() = 0;
      virtual bool GetFullscreen() = 0;
      virtual void SetFullscreen(bool value) = 0;
      virtual void CreateMeshBuffers(Mesh *mesh) = 0;
      virtual void CreateMaterialBuffers(Material *mat) = 0;
      virtual void DrawLine(float3 a, float3 b) = 0;
      virtual void DrawLines(float3 *first, uint count) = 0;
      virtual void Draw(Mesh *mesh, Shader *shader) = 0;
      virtual void Draw(Mesh *mesh, Material *mat) = 0;
      virtual void Draw(MeshRenderer *r) = 0;
      virtual void CreateMeshRenderer(MeshRenderer *r) = 0;
      virtual uint GetNewShaderID() = 0;
      virtual bool CompileShaderFromFile(Shader *shader, CWString filename) = 0;
      virtual void SetActiveShader(Shader *shader) = 0;
      virtual CString GetName() = 0;
      virtual void ReleaseShader(Shader *shader) = 0;
      virtual void Release() = 0;
      virtual ~Renderer() { }
      inline static Renderer *instance;
      static void Create(GraphicsAPI api);
   };
}