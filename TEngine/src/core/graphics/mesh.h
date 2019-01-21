#pragma once
#include "core/common.h"
#include "MeshBuffers.h"
namespace TEngine {
   using namespace Math;
   struct TENGINE_API Mesh {
      static Mesh ScreenQuad;
      Mesh();
      Mesh(const Mesh &other);
      Mesh(float3 *positions, uint vertexCount, uint *indices, uint indexCount);
      void Release();
      ~Mesh();
      inline float3 *GetVertices() const { return m_Vertices; }
      inline uint GetVertexCount() const { return m_VertexCount; }
      inline uint *GetIndices() const { return m_Indices; }
      inline uint GetIndexCount() const { return m_IndexCount; }
      inline MeshBuffers &GetBuffers() { return m_Buffers; }
   private:
      float3 *m_Vertices;
      uint m_VertexCount;
      uint *m_Indices;
      uint m_IndexCount;
      MeshBuffers m_Buffers;
   };
   namespace MeshCreator {
      inline Mesh *Quad(float hsx, float hsy) {
        float3 *verts = new float3[4]{
            float3( hsx, hsy),
            float3(-hsx, hsy),
            float3( hsx,-hsy),
            float3(-hsx,-hsy)
         };
         uint *inds = new uint[6]{
            2,1,0,2,3,1
         };
         return new Mesh(verts, 4, inds, 6);
      }
      inline Mesh *Cube(float hsx, float hsy, float hsz) {

      }
   }
}

