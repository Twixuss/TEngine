#pragma once
#include <d3d10_1.h>
#include <d3d10.h>
#include <d3d11.h>
namespace TEngine {
   struct MeshBuffers {
      union {
         struct _D3D10 {
            ID3D10Buffer *vertexBuffer;
            ID3D10Buffer *indexBuffer;
            _D3D10() : vertexBuffer(nullptr), indexBuffer(nullptr) {}
            void Release() {
               if (vertexBuffer) {
                  vertexBuffer->Release();
                  vertexBuffer = nullptr;
               }
               if (indexBuffer) {
                  indexBuffer->Release();
                  indexBuffer = nullptr;
               }
            }
         }D3D10;
         struct _D3D11 {
            ID3D11Buffer *vertexBuffer;
            ID3D11Buffer *indexBuffer;
            _D3D11() : vertexBuffer(nullptr), indexBuffer(nullptr) {}
            void Release() {
               if (vertexBuffer) {
                  vertexBuffer->Release();
                  vertexBuffer = nullptr;
               }
               if (indexBuffer) {
                  indexBuffer->Release();
                  indexBuffer = nullptr;
               }
            }
         }D3D11;
      };
      MeshBuffers() : D3D10(), D3D11() {}
      void Release() {
         D3D10.Release();
         D3D11.Release();
      }
   };
}