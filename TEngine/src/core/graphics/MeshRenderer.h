#pragma once
#include "core/common.h"
#include "core/Transform.h"
#include "Material.h"
namespace TEngine
{
   using namespace Math;
   using namespace Microsoft::WRL;
   // TODO: remove inheritance
   class LibraryInterface MeshRenderer : public Transform
   {
      friend class RendererD3D11;
   public:
      inline void SetMesh(Mesh *mesh)
      {
         m_Mesh = mesh;
      }
      inline void SetMaterial(Material *mat)
      {
         m_Material = mat;
      }
      inline Mesh *GetMesh() const
      {
         return m_Mesh;
      }
      inline Material *GetMaterial() const
      {
         return m_Material;
      }
   private:
      MeshRenderer(Mesh *mesh, Material *mat, float3 pos, float3 rot, float3 scl);
   private:
      Mesh *m_Mesh;
      Material *m_Material;
      ComPtr<ID3D11Buffer> m_MatrixBuffer;
   };
}
