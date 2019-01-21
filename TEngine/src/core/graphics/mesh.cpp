#include "mesh.h"
#include "shader.h"
#include "input.h"
#include "renderer.h"
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
      Renderer::instance->CreateMeshBuffers(this);
   }
   Mesh::Mesh(float3 *positions, uint vertexCount, uint *indices, uint indexCount) : 
      m_Vertices(positions), 
      m_VertexCount(vertexCount),
      m_Indices(indices),
      m_IndexCount(indexCount)
   {
      Renderer::instance->CreateMeshBuffers(this);
   }
   Mesh::~Mesh() {
      Release();
   }
   void Mesh::Release() {
      m_Buffers.Release();
   }
}