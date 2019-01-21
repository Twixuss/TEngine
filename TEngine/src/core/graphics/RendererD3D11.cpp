#include "RendererD3D11.h"
#include "Clock.h"
namespace TEngine {
   typedef ID3D10Blob ID3D11Blob;

   uint _zero = 0;
   ID3D11RasterizerState *RSWire;
   Shader *WireShader;

#define CBUFFER_ALIGN DECLSPEC_ALIGN(16)

   CBUFFER_ALIGN struct FrameData {
      float timeDelta;
      float timeTotal;
   }frameData;

   CBUFFER_ALIGN struct MatrixData {
      XMMATRIX rot;
      XMMATRIX prj;
      XMMATRIX mvp;
   }matrixData;

   void CreateBackBuffer(IDXGISwapChain *swapChain, ID3D11Device *device, ID3D11RenderTargetView **backBuffer) {
      TE_ASSERT(swapChain);
      TE_ASSERT(device);
      TE_ASSERT(backBuffer);
      ID3D11Texture2D *BackBuffer;
      TE_HANDLE_HRESULT(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer));
      TE_HANDLE_HRESULT(device->CreateRenderTargetView(BackBuffer, NULL, backBuffer));
      BackBuffer->Release();
   }
   void SetViewport(ID3D11DeviceContext *devCon, float w, float h) {
      TE_ASSERT(devCon);
      D3D11_VIEWPORT v{ 0,0,w,h,0,1 };
      devCon->RSSetViewports(1, &v);
   }
   bool CompileShader(CWString filename, CString entry, CString profile, ID3D11Blob **out) {
      TE_ASSERT(filename);
      TE_ASSERT(entry);
      TE_ASSERT(profile);
      TE_ASSERT(out);
      ID3D11Blob *errors = nullptr;
      if (FAILED(D3DX11CompileFromFileW(filename, 0, 0, entry, profile, 0, 0, 0, out, &errors, 0))) {
         if (errors) {
            char* compileErrors;
            compileErrors = (char*)(errors->GetBufferPointer());
            char* prev = compileErrors;
            for (int i = 0;i < errors->GetBufferSize();i++) {
               while (compileErrors[i] != '\n')++i;
               compileErrors[i] = '\0';
               ++i;
               TE_WARN(prev);
               prev = compileErrors + i;
            }
            errors->Release();
         }
         else {
            TE_WARN(filename, " - Shader file doesn't exist");
         }
         return false;
      }
      return true;
   }
   void CreateBuffer(ID3D11Device *device, ID3D11Buffer **out, UINT byteWidth, D3D11_BIND_FLAG flag) {
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
   void CreateBuffer(ID3D11Device *device, ID3D11Buffer **out, T *data, D3D11_BIND_FLAG flag) {
      TE_ASSERT(device);
      TE_ASSERT(out);
      TE_ASSERT(data);
      D3D11_BUFFER_DESC bufferDesc{ 0 };
      bufferDesc.Usage = D3D11_USAGE_DEFAULT;
      bufferDesc.ByteWidth = sizeof(T);
      bufferDesc.BindFlags = flag;
      bufferDesc.CPUAccessFlags = 0;
      bufferDesc.MiscFlags = 0;
      D3D11_SUBRESOURCE_DATA subResourceData{ 0 };
      subResourceData.pSysMem = data;
      TE_HANDLE_HRESULT(device->CreateBuffer(&bufferDesc, &subResourceData, out));
   }
   template<class T>
   void CreateBuffer(ID3D11Device *device, ID3D11Buffer **out, T *data, UINT count, D3D11_BIND_FLAG flag) {
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
   void UpdateBuffer(ID3D11DeviceContext *devCon, ID3D11Buffer *buf, const void *data) {
      devCon->UpdateSubresource(buf, 0, nullptr, data, 0, 0);
   }

   void UpdateScreen(IDXGISwapChain *swapChain, ID3D11Device *device, ID3D11DeviceContext *devCon, ID3D11RenderTargetView **backBuffer, uint w, uint h) {
      CreateBackBuffer(swapChain, device, backBuffer);
      devCon->OMSetRenderTargets(1, backBuffer, nullptr);
      SetViewport(devCon, w, h);
      //PerspectiveMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV2, (float)Window::Width / Window::Height, 0.5f, 1);
      matrixData.prj = XMMatrixOrthographicLH(Window::Width, Window::Height, 0, 1);
      //TE_PRINT(*(float4x4*)&PerspectiveMatrix);
   }

   struct ShaderData {
      ID3D11VertexShader *vs;
      ID3D11PixelShader *ps;
      ID3D10Blob *vsbuffer;
      ID3D10Blob *psbuffer;
      ID3D11InputLayout *layout;
      ShaderData() { ZeroMemory(this, sizeof(*this)); }
      ~ShaderData() { Release(); }
      void Release() {
         RELEASE(vs);
         RELEASE(ps);
         RELEASE(vsbuffer);
         RELEASE(psbuffer);
         RELEASE(layout);
      }
   };
   std::vector<Shader*> shaders;
   ShaderData shaderDatas[128];

   uint shaderCount = 0;

   RendererD3D11::RendererD3D11() :
      m_BackBuffer(nullptr),
      m_DevCon(nullptr),
      m_Device(nullptr),
      m_SwapChain(nullptr),
      m_FrameCBuffer(nullptr)
   {}
   RendererD3D11::~RendererD3D11() {
      Release();
   }
   void RendererD3D11::Init() {
      TE_ASSERT(Window::hWnd);
      DXGI_MODE_DESC bufferDesc{ 0 };
      bufferDesc.Width = Window::Width;
      bufferDesc.Height = Window::Height;
      bufferDesc.RefreshRate.Numerator = 60;
      bufferDesc.RefreshRate.Denominator = 1;
      bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
      bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

      DXGI_SWAP_CHAIN_DESC swapChainDesc{ 0 };
      swapChainDesc.BufferDesc = bufferDesc;
      swapChainDesc.SampleDesc.Count = 1;
      swapChainDesc.SampleDesc.Quality = 0;
      swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
      swapChainDesc.BufferCount = 1;
      swapChainDesc.OutputWindow = Window::hWnd;
      swapChainDesc.Windowed = TRUE;
      swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
      TE_HANDLE_HRESULT(D3D11CreateDeviceAndSwapChain(
         nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
         D3D11_SDK_VERSION, &swapChainDesc, &m_SwapChain, &m_Device, nullptr, &m_DevCon));

      UpdateScreen(m_SwapChain, m_Device, m_DevCon, &m_BackBuffer, Window::Width, Window::Height);

      m_DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

      D3D11_RASTERIZER_DESC desc{ D3D11_FILL_SOLID, D3D11_CULL_BACK };
      ID3D11RasterizerState *rs;
      TE_HANDLE_HRESULT(m_Device->CreateRasterizerState(&desc, &rs));
      m_DevCon->RSSetState(rs);

      D3D11_RASTERIZER_DESC wdesc{ D3D11_FILL_WIREFRAME, D3D11_CULL_NONE };
      TE_HANDLE_HRESULT(m_Device->CreateRasterizerState(&wdesc, &RSWire));

      WireShader = Shader::CreateFromFile(L"data/shaders/wire.hlsl");

      CreateBuffer(m_Device, &m_FrameCBuffer, &frameData, D3D11_BIND_CONSTANT_BUFFER);
   }
   void RendererD3D11::Clear(const Color& color) {
      m_DevCon->ClearRenderTargetView(m_BackBuffer, (float*)&color);
   }
   void RendererD3D11::ResizeBuffers(uint w, uint h) {
      m_BackBuffer->Release();
      TE_HANDLE_HRESULT(m_SwapChain->ResizeBuffers(1, w, h, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
      UpdateScreen(m_SwapChain, m_Device, m_DevCon, &m_BackBuffer, Window::Width, Window::Height);
   }
   void RendererD3D11::Prepare(const Clock& time) {
      frameData.timeDelta = time.GetDelta();
      frameData.timeTotal = time.GetTotalTime();
      UpdateBuffer(m_DevCon, m_FrameCBuffer, &frameData);
      m_DevCon->VSSetConstantBuffers(0, 1, &m_FrameCBuffer);
      m_DevCon->PSSetConstantBuffers(0, 1, &m_FrameCBuffer);
   }
   void RendererD3D11::Present() {
      TE_HANDLE_HRESULT(m_SwapChain->Present(0, 0));
   }
   bool RendererD3D11::GetFullscreen() {
      BOOL result;
      TE_HANDLE_HRESULT(m_SwapChain->GetFullscreenState(&result, nullptr));
      return result;
   }
   void RendererD3D11::SetFullscreen(bool value) {
      TE_HANDLE_HRESULT(m_SwapChain->SetFullscreenState(value, nullptr));
   }
   void RendererD3D11::CreateMeshBuffers(Mesh *mesh) {
      TE_ASSERT(mesh);
      auto &data = mesh->GetBuffers().D3D11;
      D3D11_BUFFER_DESC bd{ 0 };
      D3D11_SUBRESOURCE_DATA buf{ 0 };

      bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
      bd.ByteWidth = sizeof(float3) * mesh->GetVertexCount();
      buf.pSysMem = mesh->GetVertices();

      TE_HANDLE_HRESULT(m_Device->CreateBuffer(&bd, &buf, &data.vertexBuffer));

      bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
      bd.ByteWidth = sizeof(uint) * mesh->GetIndexCount();
      buf.pSysMem = mesh->GetIndices();

      TE_HANDLE_HRESULT(m_Device->CreateBuffer(&bd, &buf, &data.indexBuffer));
   }
   void RendererD3D11::CreateMaterialBuffers(Material *mat) {
      //TE_ASSERT(mat);
      //auto &data = mat->_GetBuffers().D3D11;
      //D3D11_BUFFER_DESC bd{ 0 };
      //D3D11_SUBRESOURCE_DATA buf{ 0 };

      //bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
      //bd.ByteWidth = sizeof(float) * mat->GetPropertyCount();
      //buf.pSysMem = mat->GetProperties();

      //TE_HANDLE_HRESULT(m_Device->CreateBuffer(&bd, &buf, &data.CBuffer));
   }
   void RendererD3D11::DrawLine(float3 a, float3 b) {
      ID3D11Buffer *tempBuffer;
      float3 verts[] = { a,b };
      CreateBuffer(m_Device, &tempBuffer, verts, 2, D3D11_BIND_VERTEX_BUFFER);
      static uint size = sizeof float3;
      m_DevCon->IASetVertexBuffers(0, 1, &tempBuffer, &size, &_zero);
      SetActiveShader(WireShader);
      ID3D11RasterizerState *prev;
      m_DevCon->RSGetState(&prev);
      m_DevCon->RSSetState(RSWire);
      D3D11_PRIMITIVE_TOPOLOGY pt;
      m_DevCon->IAGetPrimitiveTopology(&pt);
      m_DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
      m_DevCon->Draw(2, 0);
      tempBuffer->Release();
      m_DevCon->RSSetState(prev);
      m_DevCon->IASetPrimitiveTopology(pt);
   }
   void RendererD3D11::DrawLines(float3 *first, uint count) {
      ID3D11Buffer *tempBuffer;
      CreateBuffer(m_Device, &tempBuffer, first, count, D3D11_BIND_VERTEX_BUFFER);
      static uint size = sizeof float3;
      m_DevCon->IASetVertexBuffers(0, 1, &tempBuffer, &size, &_zero);
      SetActiveShader(WireShader);

      ID3D11RasterizerState *prev;
      m_DevCon->RSGetState(&prev);

      D3D11_PRIMITIVE_TOPOLOGY pt;
      m_DevCon->IAGetPrimitiveTopology(&pt);

      m_DevCon->RSSetState(RSWire);
      m_DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
      m_DevCon->Draw(count, 0);

      m_DevCon->RSSetState(prev);
      m_DevCon->IASetPrimitiveTopology(pt);

      tempBuffer->Release();
   }
   void RendererD3D11::Draw(Mesh *mesh, Shader *shader) {
      TE_ASSERT(mesh);
      auto &data = mesh->GetBuffers().D3D11;
      TE_ASSERT(data.vertexBuffer);
      TE_ASSERT(data.indexBuffer);
      TE_ASSERT(shader);
      SetActiveShader(shader);
      m_DevCon->IASetVertexBuffers(0, 1, &data.vertexBuffer, &shader->GetVertexSize(), &_zero);
      m_DevCon->IASetIndexBuffer(data.indexBuffer, DXGI_FORMAT_R32_UINT, 0);
      m_DevCon->DrawIndexed(mesh->GetIndexCount(), 0, 0);
   }
   void RendererD3D11::Draw(Mesh *mesh, Material *mat) {
      TE_ASSERT(mesh);
      TE_ASSERT(mat);
      auto &data = mat->_GetBuffers().D3D11;
      if (mat->_IsDirty()) {
         mat->_SetDirty(false);
         if (data.CBuffer) {
            data.CBuffer->Release();
            data.CBuffer = nullptr;
         }
         if (mat->GetPropertyCount() > 3)
            CreateBuffer(m_Device, &data.CBuffer, mat->GetProperties(), mat->GetPropertyCount(), D3D11_BIND_CONSTANT_BUFFER);
      }
      if (data.CBuffer) {
         m_DevCon->VSSetConstantBuffers(7, 1, &data.CBuffer);
         m_DevCon->PSSetConstantBuffers(7, 1, &data.CBuffer);
      }
      Draw(mesh, mat->GetShader());
   }
   void RendererD3D11::Draw(MeshRenderer *r) {
      auto &data = r->_GetBuffers().D3D11;
      //if (r->_IsDirty() || Window::Resized) {
      r->_SetDirty(false);
      matrixData.rot = XMMatrixRotationRollPitchYawFromVector(r->GetRotation().xmv);
      matrixData.mvp = XMMatrixScalingFromVector(r->GetScaling().xmv) * matrixData.rot * XMMatrixTranslationFromVector(r->GetPosition().xmv) * matrixData.prj;
      UpdateBuffer(m_DevCon, data.m_MatrixBuffer, &matrixData);
      //}
      m_DevCon->VSSetConstantBuffers(1, 1, &data.m_MatrixBuffer);
      m_DevCon->PSSetConstantBuffers(1, 1, &data.m_MatrixBuffer);
      Draw(r->GetMesh(), r->GetMaterial());
   }
   void RendererD3D11::CreateMeshRenderer(MeshRenderer *r) {
      auto &data = r->_GetBuffers().D3D11;
      CreateBuffer(m_Device, &data.m_MatrixBuffer, &matrixData, D3D11_BIND_CONSTANT_BUFFER);
   }
   uint RendererD3D11::GetNewShaderID() {
      return shaderCount++;
   }
   bool RendererD3D11::CompileShaderFromFile(Shader *shader, CWString filename) {
      TE_ASSERT(shader);
      TE_ASSERT(filename);
      auto &data = shaderDatas[shader->GetID()];
      if (!CompileShader(filename, "vs", "vs_5_0", &data.vsbuffer)) {
         TE_WARN("Vertex shader compilation error");
         return false;
      }
      if (!CompileShader(filename, "ps", "ps_5_0", &data.psbuffer)) {
         TE_WARN("Pixel shader compilation error");
         return false;
      }

      TE_HANDLE_HRESULT(m_Device->CreateVertexShader(data.vsbuffer->GetBufferPointer(), data.vsbuffer->GetBufferSize(), nullptr, &data.vs));
      TE_HANDLE_HRESULT(m_Device->CreatePixelShader(data.psbuffer->GetBufferPointer(), data.psbuffer->GetBufferSize(), nullptr, &data.ps));

      D3D11_INPUT_ELEMENT_DESC elements[]{
          {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0 , D3D11_INPUT_PER_VERTEX_DATA, 0},
      };
      TE_HANDLE_HRESULT(m_Device->CreateInputLayout(elements, 1, data.vsbuffer->GetBufferPointer(), data.vsbuffer->GetBufferSize(), &data.layout));
      TE_SUCCESS("Created shader: ", filename);
      return true;
   }
   void RendererD3D11::SetActiveShader(Shader *shader) {
      TE_ASSERT(shader);
      auto &data = shaderDatas[shader->GetID()];
      TE_ASSERT(data.layout);
      TE_ASSERT(data.vs);
      TE_ASSERT(data.ps);
      m_DevCon->VSSetShader(data.vs, nullptr, 0);
      m_DevCon->PSSetShader(data.ps, nullptr, 0);
      m_DevCon->IASetInputLayout(data.layout);
   }
   CString RendererD3D11::GetName() {
      return "Direct3D11";
   }
   void RendererD3D11::ReleaseShader(Shader *shader) {
      shaderDatas[shader->GetID()].Release();
   }
   void RendererD3D11::Release() {
      if (m_BackBuffer) {
         m_BackBuffer->Release();
         m_BackBuffer = nullptr;
      }
      if (m_DevCon) {
         m_DevCon->Release();
         m_DevCon = nullptr;
      }
      if (m_Device) {
         m_Device->Release();
         m_Device = nullptr;
      }
      if (m_SwapChain) {
         m_SwapChain->Release();
         m_SwapChain = nullptr;
      }
      TE_WARN("~~~ Released D3D11");
   }
}