#include "core/input/input.h"
#include "core/graphics/mesh.h"
#include "core/graphics/shader.h"
#include "core/graphics/renderer.h"
namespace TEngine {
   Mesh::Mesh() : m_Buffers() {
      m_Vertices = new float3[3]{
         float3( 1, -1, 0.5),
         float3( 0,  1, 0.5),
         float3(-1, -1, 0.5)
      };
      m_VertexCount = 3;
      m_Indices = new uint[3]{
         2,1,0
      };
      m_IndexCount = 3;
   }
   Mesh::Mesh(float3 *positions, uint vertexCount, uint *indices, uint indexCount) : 
      m_Vertices(positions), 
      m_VertexCount(vertexCount),
      m_Indices(indices),
      m_IndexCount(indexCount)
   {
   }
}