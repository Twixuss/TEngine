#pragma once
#include "renderer.h"
namespace TEngine::Graphics {
   inline void Clear(const Color& color) { Renderer::instance->Clear(color); }
   inline void ResizeBuffers(uint w, uint h) { Renderer::instance->ResizeBuffers(w, h); }
   inline void Prepare(const Clock& time) { Renderer::instance->Prepare(time); }
   inline void Present() {}
   inline bool GetFullscreen() {}
   inline void SetFullscreen(bool value) {}
   inline void CreateMeshBuffers(Mesh *mesh) {}
   inline void CreateMaterialBuffers(Material *mat) {}
   inline void DrawLine(float3 a, float3 b) {}
   inline void DrawLines(float3 *first, uint count) {}
   inline void Draw(Mesh *mesh, Shader *shader) {}
   inline void Draw(Mesh *mesh, Material *mat) {}
   inline void Draw(MeshRenderer *r) {}
   inline void CreateMeshRenderer(MeshRenderer *r) {}
   inline uint GetNewShaderID() {}
   inline bool CompileShaderFromFile(Shader *shader, CWString filename) {}
   inline void SetActiveShader(Shader *shader) {}
   inline CString GetRendererName() {}
   inline void ReleaseShader(Shader *shader) {}
   inline void Release() {}
}