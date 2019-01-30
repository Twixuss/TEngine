#pragma once
#include "core/common.h"
#include "MeshBuffers.h"
namespace TEngine
{
   using namespace Math;
   class LibraryInterface Mesh
   {
      friend class RendererD3D11;
   public:
      inline float3 *GetVertices() const
      {
         return m_Vertices;
      }
      inline uint GetVertexCount() const
      {
         return m_VertexCount;
      }
      inline uint *GetIndices() const
      {
         return m_Indices;
      }
      inline uint GetIndexCount() const
      {
         return m_IndexCount;
      }
      inline MeshBuffers &GetBuffers()
      {
         return m_Buffers;
      }
   private:
      Mesh();
      Mesh(float3 *positions, uint vertexCount, uint *indices, uint indexCount);
   private:
      float3 *m_Vertices;
      uint m_VertexCount;
      uint *m_Indices;
      uint m_IndexCount;
      MeshBuffers m_Buffers;
   public:
      static Mesh ScreenQuad;
   };
}
