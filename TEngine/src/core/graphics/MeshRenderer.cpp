#include "MeshRenderer.h"
#include "renderer.h"
namespace TEngine
{
   MeshRenderer::MeshRenderer(Mesh *mesh, Material *mat, float3 pos, float3 rot, float3 scl) :
      Transform(pos, rot, scl),
      m_Mesh(mesh),
      m_Material(mat)
   {
   }
}