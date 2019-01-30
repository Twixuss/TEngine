#include "Core/Graphics/MaterialParser.h"
#include "Core/Graphics/RendererD3D11.h"
#include "Core/Clock.h"
#include "Core/FileReader.h"
namespace TEngine
{
   
   typedef ID3D10Blob ID3D11Blob;

   uint _zero = 0;
   ComPtr<ID3D11RasterizerState> RSWire;
   Shader *WireShader;

#define CBUFFER struct DECLSPEC_ALIGN(16)

   CBUFFER FrameData
   {
      float timeDelta;
      float timeTotal;
   }frameData;

   CBUFFER MatrixData
   {
      XMMATRIX rot;
      XMMATRIX prj;
      XMMATRIX mvp;
   }matrixData;

   void CreateBackBuffer(IDXGISwapChain *swapChain, ID3D11Device *device, ID3D11RenderTargetView **backBuffer)
   {
      TE_ASSERT(swapChain);
      TE_ASSERT(device);
      TE_ASSERT(backBuffer);
      ComPtr<ID3D11Texture2D> BackBuffer;
      TE_HANDLE_HRESULT(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)BackBuffer.GetAddressOf()));
      TE_HANDLE_HRESULT(device->CreateRenderTargetView(BackBuffer.Get(), NULL, backBuffer));
   }
   void SetViewport(ID3D11DeviceContext *devCon, float w, float h)
   {
      TE_ASSERT(devCon);
      D3D11_VIEWPORT v{ 0,0,w,h,0,1 };
      devCon->RSSetViewports(1, &v);
   }
   bool CompileShader(const String& filename, LPCSTR entry, LPCSTR profile, ID3D11Blob **out)
   {
      ID3D11Blob *errors = nullptr;
      if (FAILED(D3DX11CompileFromFileW(filename.CStr(), 0, 0, entry, profile, 0, 0, 0, out, &errors, 0)))
      {
         if (errors)
         {
            char* compileErrors;
            compileErrors = (char*)(errors->GetBufferPointer());
            char* prev = compileErrors;
            for (int i = 0;i < errors->GetBufferSize();i++)
            {
               while (compileErrors[i] != '\n')++i;
               compileErrors[i] = '\0';
               ++i;
               TE_WARN(prev);
               prev = compileErrors + i;
            }
            errors->Release();
         }
         else
         {
            TE_WARN(filename, " - Shader file doesn't exist");
         }
         return false;
      }
      return true;
   }
   void CreateBuffer(ID3D11Device *device, ID3D11Buffer **out, UINT byteWidth, D3D11_BIND_FLAG flag)
   {
      TE_ASSERT(device);
      TE_ASSERT(out);
      D3D11_BUFFER_DESC bufferDesc{ 0,D3D11_USAGE_DEFAULT,0,0,0,0 };
      bufferDesc.Usage = D3D11_USAGE_DEFAULT;
      bufferDesc.ByteWidth = byteWidth;
      bufferDesc.BindFlags = flag;
      bufferDesc.CPUAccessFlags = 0;
      bufferDesc.MiscFlags = 0;
      TE_HANDLE_HRESULT(device->CreateBuffer(&bufferDesc, nullptr, out));
   }
   template<class T>
   void CreateBuffer(ID3D11Device *device, ID3D11Buffer **out, const T& data, D3D11_BIND_FLAG flag)
   {
      TE_ASSERT(device);
      TE_ASSERT(out);
      D3D11_BUFFER_DESC bufferDesc{ 0 };
      bufferDesc.Usage = D3D11_USAGE_DEFAULT;
      bufferDesc.ByteWidth = sizeof(T);
      bufferDesc.BindFlags = flag;
      bufferDesc.CPUAccessFlags = 0;
      bufferDesc.MiscFlags = 0;
      D3D11_SUBRESOURCE_DATA subResourceData{ 0 };
      subResourceData.pSysMem = &data;
      TE_HANDLE_HRESULT(device->CreateBuffer(&bufferDesc, &subResourceData, out));
   }
   template<class T>
   void CreateBuffer(ID3D11Device *device, ID3D11Buffer **out, const T* data, UINT count, D3D11_BIND_FLAG flag)
   {
      TE_ASSERT(device);
      TE_ASSERT(out);
      TE_ASSERT(data);
      D3D11_BUFFER_DESC bufferDesc{ 0 };
      bufferDesc.Usage = D3D11_USAGE_DEFAULT;
      bufferDesc.ByteWidth = sizeof(T) * count;
      bufferDesc.BindFlags = flag;
      bufferDesc.CPUAccessFlags = 0;
      bufferDesc.MiscFlags = 0;
      D3D11_SUBRESOURCE_DATA subResourceData{ 0 };
      subResourceData.pSysMem = data;
      TE_HANDLE_HRESULT(device->CreateBuffer(&bufferDesc, &subResourceData, out));
   }
   void UpdateBuffer(ID3D11DeviceContext *devCon, ID3D11Buffer *buf, const void *data)
   {
      TE_ASSERT(devCon);
      TE_ASSERT(buf);
      TE_ASSERT(data);
      devCon->UpdateSubresource(buf, 0, nullptr, data, 0, 0);
   }
   void CreateDepthStencilView(ID3D11Device *device, uint width, uint height, ID3D11DepthStencilView** out)
   {
      TE_ASSERT(device);
      TE_ASSERT(width);
      TE_ASSERT(height);
      TE_ASSERT(out);
      D3D11_TEXTURE2D_DESC dstdesc;
      ZeroMemory(&dstdesc, sizeof(D3D11_TEXTURE2D_DESC));
      dstdesc.ArraySize = 1;
      dstdesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
      dstdesc.CPUAccessFlags = 0;
      dstdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
      dstdesc.Height = height;
      dstdesc.Width = width;
      dstdesc.MipLevels = 1;
      dstdesc.MiscFlags = 0;
      dstdesc.SampleDesc.Count = 1;
      dstdesc.SampleDesc.Quality = 0;
      dstdesc.Usage = D3D11_USAGE_DEFAULT;

      ID3D11Texture2D *dstex;
      TE_HANDLE_HRESULT(device->CreateTexture2D(&dstdesc, NULL, &dstex));

      D3D11_DEPTH_STENCIL_VIEW_DESC dsdesc;
      ZeroMemory(&dsdesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
      dsdesc.Flags = 0;
      dsdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
      dsdesc.Texture2D.MipSlice = 0;
      dsdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

      TE_HANDLE_HRESULT(device->CreateDepthStencilView(dstex, &dsdesc, out));
      dstex->Release();
   }

   void UpdateScreen(const Window& wnd, IDXGISwapChain *swapChain, ID3D11Device *device, ID3D11DeviceContext *devCon, ID3D11RenderTargetView **backBuffer, ID3D11DepthStencilView** dsv)
   {
      CreateBackBuffer(swapChain, device, backBuffer);
      CreateDepthStencilView(device, wnd.GetClientWidth(), wnd.GetClientHeight(), dsv);
      devCon->OMSetRenderTargets(1, backBuffer, *dsv);
      SetViewport(devCon, wnd.GetClientWidth(), wnd.GetClientHeight());
      //PerspectiveMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV2, (float)Window::Width / Window::Height, 0.5f, 1);
      matrixData.prj = XMMatrixOrthographicLH(wnd.GetClientWidth(), wnd.GetClientHeight(), -1, 1);
      //TE_PRINT(*(float4x4*)&PerspectiveMatrix);
   }

#ifndef SHADER_COUNT
#define SHADER_COUNT 128
#endif
   struct ShaderData : public Shader
   {
      ComPtr<ID3D11VertexShader> vs;
      ComPtr<ID3D11PixelShader> ps;
      ComPtr<ID3D10Blob> vsbuffer;
      ComPtr<ID3D10Blob> psbuffer;
      ComPtr<ID3D11InputLayout> layout;
   };
   ShaderData shaders[SHADER_COUNT];

#ifndef MATERIAL_COUNT
#define MATERIAL_COUNT 128
#endif
   struct MaterialData : public Material
   {
      void OnChange() override
      {
         m_Dirty = true;
      }
      ComPtr<ID3D11Buffer> m_PropertiesBuffer;
      bool m_Dirty;
   };
   MaterialData materials[MATERIAL_COUNT];

   RendererD3D11::RendererD3D11() :
      m_BackBuffer(nullptr),
      m_DevCon(nullptr),
      m_Device(nullptr),
      m_SwapChain(nullptr),
      m_FrameCBuffer(nullptr)
   {
   }
   RendererD3D11::~RendererD3D11()
   {
   }
   void RendererD3D11::Init(const Window& wnd)
   {
      DXGI_MODE_DESC bufferDesc{};
      bufferDesc.Width = wnd.GetClientWidth();
      bufferDesc.Height = wnd.GetClientHeight();
      bufferDesc.RefreshRate.Numerator = 60;
      bufferDesc.RefreshRate.Denominator = 1;
      bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
      bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

      DXGI_SWAP_CHAIN_DESC swapChainDesc{};
      swapChainDesc.BufferDesc = bufferDesc;
      swapChainDesc.SampleDesc.Count = 1;
      swapChainDesc.SampleDesc.Quality = 0;
      swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
      swapChainDesc.BufferCount = 1;
      swapChainDesc.OutputWindow = wnd.GetHWND();
      swapChainDesc.Windowed = TRUE;
      swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
      TE_HANDLE_HRESULT(D3D11CreateDeviceAndSwapChain(
         nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
         D3D11_SDK_VERSION, &swapChainDesc, m_SwapChain.GetAddressOf(),
         m_Device.GetAddressOf(), nullptr, m_DevCon.GetAddressOf()));

      UpdateScreen(wnd, m_SwapChain.Get(), m_Device.Get(), m_DevCon.Get(),
                   m_BackBuffer.GetAddressOf(), m_DepthStencil.GetAddressOf());

      m_DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

      D3D11_RASTERIZER_DESC desc{ D3D11_FILL_SOLID, D3D11_CULL_BACK };
      ID3D11RasterizerState *rs;
      TE_HANDLE_HRESULT(m_Device->CreateRasterizerState(&desc, &rs));
      m_DevCon->RSSetState(rs);

      D3D11_RASTERIZER_DESC wdesc{ D3D11_FILL_WIREFRAME, D3D11_CULL_NONE };
      TE_HANDLE_HRESULT(m_Device->CreateRasterizerState(&wdesc, RSWire.GetAddressOf()));

      CreateBuffer(m_Device.Get(), m_FrameCBuffer.GetAddressOf(), frameData, D3D11_BIND_CONSTANT_BUFFER);

      // Init all shaders
      int i = 0;
      for (const String &f : Common::GetFilesInDirectory(L"data\\shaders"))
      {
         TE_PRINT("Compiling ", f, " ...");
         auto& s = shaders[i];
         s.m_Filename = f;
         s.m_ID = i;

         // TODO: determine this when compiling//
              s.m_Stride = sizeof(float3);
         ////////////////////////////////////////

         if (!CompileShader(s.m_Filename, "vs", "vs_5_0", s.vsbuffer.GetAddressOf()))
         {
            TE_ERROR("Vertex shader compilation error");
         }
         if (!CompileShader(s.m_Filename, "ps", "ps_5_0", s.psbuffer.GetAddressOf()))
         {
            TE_ERROR("Pixel shader compilation error");
         }

         TE_HANDLE_HRESULT(
            m_Device->CreateVertexShader(
               s.vsbuffer->GetBufferPointer(),
               s.vsbuffer->GetBufferSize(),
               nullptr,
               s.vs.GetAddressOf()
            )
         );
         TE_HANDLE_HRESULT(
            m_Device->CreatePixelShader(
               s.psbuffer->GetBufferPointer(),
               s.psbuffer->GetBufferSize(),
               nullptr,
               s.ps.GetAddressOf()
            )
         );

         D3D11_INPUT_ELEMENT_DESC elements[]{
             {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0 , D3D11_INPUT_PER_VERTEX_DATA, 0},
         };
         TE_HANDLE_HRESULT(
            m_Device->CreateInputLayout(
               elements,
               1,
               s.vsbuffer->GetBufferPointer(),
               s.vsbuffer->GetBufferSize(),
               s.layout.GetAddressOf()
            )
         );
         TE_SUCCESS("Created shader: ", s.m_Filename);
         ++i;
      }
      ///////////////////
      i = 0;
      for (const String& f : Common::GetFilesInDirectory(L"data\\materials"))
      {
         auto &mat = materials[i];

         MaterialParser parser(f);
         mat.m_Shader = GetShader(parser.m_ShaderPath);
         mat.m_Properties = parser.m_Props;
         mat.m_Dirty = true;
         mat.m_ID = i;
         mat.m_Filename = f;

         ++i;
      }

      WireShader = GetShader(L"data\\shaders\\wire.hlsl");
   }
   void RendererD3D11::Clear(const Color& color)
   {
      m_DevCon->ClearRenderTargetView(m_BackBuffer.Get(), (float*)&color);
      m_DevCon->ClearDepthStencilView(m_DepthStencil.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, -1);
   }
   void RendererD3D11::ResizeBuffers(const Window& wnd)
   {
      m_BackBuffer = nullptr;
      m_DepthStencil = nullptr;
      TE_HANDLE_HRESULT(m_SwapChain->ResizeBuffers(1, wnd.GetClientWidth(),
                                                   wnd.GetClientHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, 0));
      UpdateScreen(wnd, m_SwapChain.Get(), m_Device.Get(), m_DevCon.Get(),
                   m_BackBuffer.GetAddressOf(), m_DepthStencil.GetAddressOf());
   }
   void RendererD3D11::Prepare(const Clock& time)
   {
      frameData.timeDelta = time.GetDelta();
      frameData.timeTotal = time.GetTotalTime();
      UpdateBuffer(m_DevCon.Get(), m_FrameCBuffer.Get(), &frameData);
      m_DevCon->VSSetConstantBuffers(0, 1, m_FrameCBuffer.GetAddressOf());
      m_DevCon->PSSetConstantBuffers(0, 1, m_FrameCBuffer.GetAddressOf());
   }
   void RendererD3D11::Present()
   {
      TE_HANDLE_HRESULT(m_SwapChain->Present(0, 0));
      // DXGI_FRAME_STATISTICS stats{ 0 };
      // m_SwapChain->GetFrameStatistics(&stats);
      // stats.
   }
   bool RendererD3D11::GetFullscreen()
   {
      BOOL result;
      TE_HANDLE_HRESULT(m_SwapChain->GetFullscreenState(&result, nullptr));
      return result;
   }
   void RendererD3D11::SetFullscreen(bool value)
   {
      TE_HANDLE_HRESULT(m_SwapChain->SetFullscreenState(value, nullptr));
   }
   void CreateMeshBuffers(ID3D11Device* device, Mesh* mesh)
   {
      TE_ASSERT(mesh);
      auto &data = mesh->GetBuffers();

      D3D11_BUFFER_DESC bd{ 0 };
      bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
      bd.ByteWidth = sizeof(float3) * mesh->GetVertexCount();

      D3D11_SUBRESOURCE_DATA buf{ 0 };
      buf.pSysMem = mesh->GetVertices();

      TE_HANDLE_HRESULT(device->CreateBuffer(&bd, &buf, data.vertexBuffer.GetAddressOf()));

      bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
      bd.ByteWidth = sizeof(uint) * mesh->GetIndexCount();

      buf.pSysMem = mesh->GetIndices();

      TE_HANDLE_HRESULT(device->CreateBuffer(&bd, &buf, data.indexBuffer.GetAddressOf()));
   }
   Mesh* RendererD3D11::CreateMesh()
   {
      Mesh* mesh = new Mesh;

      CreateMeshBuffers(m_Device.Get(), mesh);

      return mesh;
   }
   Mesh* RendererD3D11::CreateMesh(float3 *positions, uint vertexCount, uint *indices, uint indexCount)
   {
      Mesh* mesh = new Mesh(positions, vertexCount, indices, indexCount);

      CreateMeshBuffers(m_Device.Get(), mesh);

      return mesh;
   }
   Material* RendererD3D11::GetMaterial(const String& filename)
   {
      for (auto& s : materials)
      {
         if (s.m_Filename.Length() == 0)
            break;
         if (filename == s.m_Filename)
         {
            return &s;
         }
      }
      TE_PRINT("Available materials:");
      for (auto& s : materials)
      {
         if (s.m_Filename.Length() == 0)
            break;
         TE_PRINT(s.m_Filename);
      }
      TE_ERROR("Material ", filename, " not found");
      return nullptr;
      //TE_ASSERT(mat);
      //auto &data = mat->_GetBuffers().D3D11;
      //D3D11_BUFFER_DESC bd{ 0 };
      //D3D11_SUBRESOURCE_DATA buf{ 0 };

      //bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
      //bd.ByteWidth = sizeof(float) * mat->GetPropertyCount();
      //buf.pSysMem = mat->GetProperties();

      //TE_HANDLE_HRESULT(m_Device->CreateBuffer(&bd, &buf, &data.CBuffer));
   }
   void RendererD3D11::DrawLine(float3 a, float3 b)
   {
      ComPtr<ID3D11Buffer> tempBuffer;
      float3 verts[] = { a,b };
      CreateBuffer(m_Device.Get(), tempBuffer.GetAddressOf(), verts, 2, D3D11_BIND_VERTEX_BUFFER);
      static uint size = sizeof float3;
      m_DevCon->IASetVertexBuffers(0, 1, tempBuffer.GetAddressOf(), &size, &_zero);
      SetActiveShader(*WireShader);
      ID3D11RasterizerState *prev;
      m_DevCon->RSGetState(&prev);
      m_DevCon->RSSetState(RSWire.Get());
      D3D11_PRIMITIVE_TOPOLOGY pt;
      m_DevCon->IAGetPrimitiveTopology(&pt);
      m_DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
      m_DevCon->Draw(2, 0);
      m_DevCon->RSSetState(prev);
      m_DevCon->IASetPrimitiveTopology(pt);
   }
   void RendererD3D11::DrawLines(float3 *first, uint count)
   {
      ComPtr<ID3D11Buffer> tempBuffer;
      CreateBuffer(m_Device.Get(), tempBuffer.GetAddressOf(), first, count, D3D11_BIND_VERTEX_BUFFER);
      static uint size = sizeof float3;
      m_DevCon->IASetVertexBuffers(0, 1, tempBuffer.GetAddressOf(), &size, &_zero);
      SetActiveShader(*WireShader);

      ID3D11RasterizerState *prev;
      m_DevCon->RSGetState(&prev);

      D3D11_PRIMITIVE_TOPOLOGY pt;
      m_DevCon->IAGetPrimitiveTopology(&pt);

      m_DevCon->RSSetState(RSWire.Get());
      m_DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
      m_DevCon->Draw(count, 0);

      m_DevCon->RSSetState(prev);
      m_DevCon->IASetPrimitiveTopology(pt);
   }
   void RendererD3D11::Draw(Mesh* mesh, const Shader* shader)
   {
      auto &data = mesh->GetBuffers();
      TE_ASSERT(data.vertexBuffer.Get());
      TE_ASSERT(data.indexBuffer.Get());
      SetActiveShader(*shader);
      m_DevCon->IASetVertexBuffers(0, 1, data.vertexBuffer.GetAddressOf(), &shader->m_Stride, &_zero);
      m_DevCon->IASetIndexBuffer(data.indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
      m_DevCon->DrawIndexed(mesh->GetIndexCount(), 0, 0);
   }
   void RendererD3D11::Draw(Mesh* mesh, Material* mat)
   {
      auto &data = materials[mat->m_ID];
      if (data.m_Dirty)
      {
         data.m_Dirty = false;
         data.m_PropertiesBuffer = nullptr;
         if (mat->GetProperties().size() > 3)
            CreateBuffer(
               m_Device.Get(),
               data.m_PropertiesBuffer.GetAddressOf(),
               &mat->GetProperties()[0],
               mat->GetProperties().size(),
               D3D11_BIND_CONSTANT_BUFFER
            );
      }
      if (data.m_PropertiesBuffer.Get())
      {
         m_DevCon->VSSetConstantBuffers(7, 1, data.m_PropertiesBuffer.GetAddressOf());
         m_DevCon->PSSetConstantBuffers(7, 1, data.m_PropertiesBuffer.GetAddressOf());
      }
      Draw(mesh, mat->GetShader());
   }
   void RendererD3D11::Draw(MeshRenderer* r)
   {
      if (r->m_Dirty) {
         r->m_Dirty = false;
         matrixData.rot = XMMatrixRotationRollPitchYawFromVector(r->GetRotation().xmv);
         matrixData.mvp = XMMatrixScalingFromVector(r->GetScaling().xmv) * matrixData.rot * XMMatrixTranslationFromVector(r->GetPosition().xmv) * matrixData.prj;
         UpdateBuffer(m_DevCon.Get(), r->m_MatrixBuffer.Get(), &matrixData);
      }
      m_DevCon->VSSetConstantBuffers(1, 1, r->m_MatrixBuffer.GetAddressOf());
      m_DevCon->PSSetConstantBuffers(1, 1, r->m_MatrixBuffer.GetAddressOf());
      Draw(r->GetMesh(), r->GetMaterial());
   }
   MeshRenderer* RendererD3D11::CreateMeshRenderer(Mesh *mesh, Material *mat, float3 pos, float3 rot, float3 scl)
   {
      TE_ASSERT(mesh);
      TE_ASSERT(mesh->m_Vertices);
      TE_ASSERT(mesh->m_Buffers.indexBuffer.Get());
      TE_ASSERT(mesh->m_Buffers.vertexBuffer.Get());
      TE_ASSERT(mat);
      // TODO: create on stack
      auto out = new MeshRenderer(mesh, mat, pos, rot, scl);
      CreateBuffer(m_Device.Get(), out->m_MatrixBuffer.GetAddressOf(), matrixData, D3D11_BIND_CONSTANT_BUFFER);
      return out;
   }
   Shader* RendererD3D11::GetShader(const String& filename)
   {
      for (auto& s : shaders)
      {
         if (s.m_Filename.Length() == 0)
            break;
         if (filename == s.m_Filename)
         {
            return &s;
         }
      }
      TE_PRINT("Available shaders:");
      for (auto& s : shaders)
      {
         if (s.m_Filename.Length() == 0)
            break;
         TE_PRINT(s.m_Filename);
      }
      TE_ERROR("Shader ", filename, " not found");
      return nullptr;
   }
   void RendererD3D11::SetActiveShader(const Shader& shader)
   {
      auto &data = shaders[shader.m_ID];
      TE_ASSERT(data.layout);
      TE_ASSERT(data.vs);
      TE_ASSERT(data.ps);
      m_DevCon->VSSetShader(data.vs.Get(), nullptr, 0);
      m_DevCon->PSSetShader(data.ps.Get(), nullptr, 0);
      m_DevCon->IASetInputLayout(data.layout.Get());
   }
   const String RendererD3D11::GetName()
   {
      return L"Direct3D11";
   }
   
}