#pragma once
#include <d3d10_1.h>
#include <d3d10.h>
#include <d3d11.h>
namespace TEngine
{
   using namespace Microsoft::WRL;
   struct MeshBuffers
   {
      ComPtr<ID3D11Buffer> vertexBuffer;
      ComPtr<ID3D11Buffer> indexBuffer;
   };
}