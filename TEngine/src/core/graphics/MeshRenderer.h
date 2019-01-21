#pragma once
#include "core/common.h"
#include "core/Transform.h"
#include "Material.h"
namespace TEngine {
   using namespace Math;
   struct TENGINE_API MeshRenderer : public Transform {
      MeshRenderer(Mesh *mesh, Material *mat, float3 pos, float3 rot, float3 scl);
      inline void SetMesh(Mesh *mesh) { m_Mesh = mesh; }
      inline void SetMaterial(Material *mat) { m_Material = mat; }
      inline Mesh *GetMesh() const { return m_Mesh; }
      inline Material *GetMaterial() const { return m_Material; }
      inline auto& _GetBuffers() { return data; }
   private:
      Mesh *m_Mesh;
      Material *m_Material;
      union {
         struct {
            ID3D10Buffer *m_MatrixBuffer;
         }D3D10;
         struct {
            ID3D11Buffer *m_MatrixBuffer;
         }D3D11;
      } data;
   };
}