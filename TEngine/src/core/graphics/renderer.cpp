#include "console.h"
#include "renderer.h"
#include "RendererEmpty.h"
#include "RendererD3D11.h"
namespace TEngine {
   void Renderer::Create(GraphicsAPI api) {
      if (instance) {
         TE_ERROR("Changing renderer at runtime is not supported yet");
      }
      switch (api) {
      case GraphicsAPI::None:
         instance = new RendererEmpty;
         break;
      case GraphicsAPI::Direct3D9:
         TE_ERROR("Direct3D9 is not supported yet");
         break;
      case GraphicsAPI::Direct3D10:
         TE_ERROR("Direct3D10 is not supported yet");
         break;
      case GraphicsAPI::Direct3D11:
         instance = new RendererD3D11;
         break;
      case GraphicsAPI::Direct3D12:
         TE_ERROR("Direct3D12 is not supported yet");
         break;
      default:
         TE_ERROR("Unresolved renderer");
         break;
      }
   }
      /*
      namespace D3D9 {
         IDXGISwapChain *swapChain = nullptr;
         IDirect3D9 *d3d9 = nullptr;
         void Init(Window *wnd) {

         }
      }
      namespace D3D10 {
         struct ShaderPreprocessData {
            ShaderPreprocessData() :
               versionMajor('3'),
               versionMinor('0') {}
            char versionMajor;
            char versionMinor;
            D3D10_INPUT_ELEMENT_DESC *elements;
            uint elementCount;
         };
         bool PreprocessShader(cwstring filename, ShaderPreprocessData &data) {
            FileReader f(filename, std::ios::binary);
            char c;
            uint line = 0;
            int index = 0;
            std::vector<D3D10_INPUT_ELEMENT_DESC> elements;
            while (f.IsOpen()) {
               f.Read(c);
               if (c == '\n') {
                  line++;
               }
               else if (c == '#') {
                  f.Read(c);
                  if (c == 'p') {
                     f.Read(c);
                     if (c == 'r') {
                        f.Read(c);
                        if (c == 'a') {
                           f.Read(c);
                           if (c == 'g') {
                              f.Read(c);
                              if (c == 'm') {
                                 f.Read(c);
                                 if (c == 'a') {
                                    f.Read(c);
                                    if (c == ' ') {
                                       f.Read(c);
                                       if (c == 't') {
                                          f.Read(c);
                                          if (c == 'a') {
                                             f.Read(c);
                                             if (c == 'r') {
                                                f.Read(c);
                                                if (c == 'g') {
                                                   f.Read(c);
                                                   if (c == 'e') {
                                                      f.Read(c);
                                                      if (c == 't') {
                                                         f.Read(c);
                                                         if (c == ' ') {
                                                            //"#pragma target "
                                                            f.Read(data.versionMajor);
                                                            f.Read(c);
                                                            if (c != '.') {

                                                            }
                                                            f.Read(data.versionMinor);
                                                            if (data.versionMajor < '0' ||
                                                               data.versionMajor > '9' ||
                                                               data.versionMinor < '0' ||
                                                               data.versionMinor > '9') {
                                                               ERROR("Preprocessor error: Bad #pragma target at line: ", line);
                                                               return false;
                                                            }
                                                         }
                                                      }
                                                   }
                                                }
                                             }
                                          }
                                       }
                                    }
                                 }
                              }
                           }
                        }
                     }
                  }
               }
               else if (c == 's') {
                  f.Read(c);
                  if (c == 't') {
                     f.Read(c);
                     if (c == 'r') {
                        f.Read(c);
                        if (c == 'u') {
                           f.Read(c);
                           if (c == 'c') {
                              f.Read(c);
                              if (c == 't') {
                                 f.Read(c);
                                 if (c == ' ') {
                                    f.Read(c);
                                    if (c == 'V') {
                                       f.Read(c);
                                       if (c == 'S') {
                                          f.Read(c);
                                          if (c == 'I') {
                                             while (f.Read(c) != '}') {
                                                if (c == 'f') {
                                                   f.Read(c);
                                                   if (c == 'l') {
                                                      f.Read(c);
                                                      if (c == 'o') {
                                                         f.Read(c);
                                                         if (c == 'a') {
                                                            f.Read(c);
                                                            if (c == 't') {
                                                               f.Read(c);
                                                               if (c == '4') {
                                                                  f.Read(c);// ' '
                                                                  std::string semantic;
                                                                  while (f.Read<char>() != ':');
                                                                  while (f.Read<char>() == ' ');
                                                                  while (f.Read(c) != ';' && c != ' ') {
                                                                     semantic.push_back(c);
                                                                  }
                                                                  //{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                                                                  PRINT(semantic.c_str());
                                                                  elements.emplace_back();
                                                               }
                                                            }
                                                         }
                                                      }
                                                   }
                                                }
                                             }
                                          }
                                       }
                                    }
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            }
            return true;
         }
         void CreateBackBuffer(IDXGISwapChain *swapChain, ID3D10Device *device, ID3D10RenderTargetView **backBuffer) {
            ASSERT(swapChain);
            ASSERT(device);
            ASSERT(backBuffer);
            ID3D10Texture2D *BackBuffer;
            HANDLE_DXGI_ERROR(swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (void**)&BackBuffer));
            HANDLE_D3D10_ERROR(device->CreateRenderTargetView(BackBuffer, NULL, backBuffer));
            BackBuffer->Release();
         }
         void SetViewport(ID3D10Device *device, uint w, uint h) {
            ASSERT(device);
            D3D10_VIEWPORT v{ 0,0,w,h,0,1 };
            device->RSSetViewports(1, &v);
         }
         bool CompileShaderFromFile(cwstring filename, cstring entry, cstring profile, ID3D10Blob **out) {
            ASSERT(filename);
            ASSERT(entry);
            ASSERT(profile);
            ASSERT(out);
            ID3D10Blob *errors = nullptr;
            if (FAILED(D3DX10CompileFromFileW(filename, 0, 0, entry, profile, 0, 0, 0, out, &errors, 0))) {
               if (errors) {
                  ERROR(filename, " - Shader compilation error");
                  char* compileErrors;
                  compileErrors = (char*)(errors->GetBufferPointer());
                  char* prev = compileErrors;
                  for (int i = 0;i < errors->GetBufferSize();i++) {
                     while (compileErrors[i] != '\n')++i;
                     compileErrors[i] = '\0';
                     ++i;
                     ERROR(prev);
                     prev = compileErrors + i;
                  }
                  errors->Release();
               }
               else {
                  ERROR(filename, " - Shader file doesn't exist");
               }
               return false;
            }
            return true;
         }
         IDXGISwapChain *swapChain = nullptr;
         ID3D10Device *device = nullptr;
         ID3D10RenderTargetView *backBuffer = nullptr;
         void Init(Window *wnd) {
            ASSERT(wnd);

            DXGI_MODE_DESC bufferDesc{ 0 };
            bufferDesc.Width = wnd->GetWidth();
            bufferDesc.Height = wnd->GetHeight();
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
            swapChainDesc.OutputWindow = wnd->hWnd;
            swapChainDesc.Windowed = TRUE;
            swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
            HANDLE_D3D10_ERROR(D3D10CreateDeviceAndSwapChain(
               nullptr, D3D10_DRIVER_TYPE_HARDWARE, nullptr, 0,
               D3D10_SDK_VERSION, &swapChainDesc, &swapChain, &device));

            CreateBackBuffer(swapChain, device, &backBuffer);
            device->OMSetRenderTargets(1, &backBuffer, nullptr);
            SetViewport(device, bufferDesc.Width, bufferDesc.Height);

            device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            D3D10_RASTERIZER_DESC desc{ D3D10_FILL_SOLID, D3D10_CULL_BACK };
            ID3D10RasterizerState *rs;
            HANDLE_D3D10_ERROR(device->CreateRasterizerState(&desc, &rs));
            device->RSSetState(rs);
         }
         void Clear(Color c) {
            device->ClearRenderTargetView(backBuffer, (float*)&c);
         }
         void ResizeBuffers(uint w, uint h) {
            backBuffer->Release();
            HANDLE_DXGI_ERROR(swapChain->ResizeBuffers(1, w, h, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
            CreateBackBuffer(swapChain, device, &backBuffer);
            device->OMSetRenderTargets(1, &backBuffer, nullptr);
            SetViewport(device, w, h);
         }
         void Present() {
            HANDLE_DXGI_ERROR(swapChain->Present(0, 0));
         }
         bool GetFullscreen() {
            BOOL result;
            HANDLE_DXGI_ERROR(swapChain->GetFullscreenState(&result, nullptr));
            return result;
         }
         void SetFullscreen(bool value) {
            HANDLE_DXGI_ERROR(swapChain->SetFullscreenState(value, nullptr));
         }
         void CreateMeshBuffers(Mesh *mesh) {
            ASSERT(mesh);
            ASSERT(mesh->D3D10.vertexBuffer);
            ASSERT(mesh->D3D10.indexBuffer);
            D3D10_BUFFER_DESC bd{ 0 };
            D3D10_SUBRESOURCE_DATA data{ 0 };

            bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
            bd.ByteWidth = sizeof(mesh->vertices[0]) * mesh->vertexCount;
            data.pSysMem = mesh->vertices;

            HANDLE_D3D10_ERROR(device->CreateBuffer(&bd, &data, &mesh->D3D10.vertexBuffer));

            bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
            bd.ByteWidth = sizeof(uint) * mesh->indexCount;
            data.pSysMem = mesh->indices;

            HANDLE_D3D10_ERROR(device->CreateBuffer(&bd, &data, &mesh->D3D10.indexBuffer));
         }
         void DrawMesh(Mesh *mesh, Shader *shader) {
            ASSERT(mesh);
            ASSERT(mesh->D3D10.vertexBuffer);
            ASSERT(mesh->D3D10.indexBuffer);
            ASSERT(shader);
            SetActiveShader(shader);
            device->IASetVertexBuffers(0, 1, &mesh->D3D10.vertexBuffer, &shader->stride, &shader->offset);
            device->IASetIndexBuffer(mesh->D3D10.indexBuffer, DXGI_FORMAT_R32_UINT, 0);
            device->DrawIndexed(mesh->indexCount, 0, 0);
         }
         bool CompileShaderFromFile(cwstring filename, Shader *shader) {
            ASSERT(shader);
            ASSERT(shader->filename);

            ShaderPreprocessData data;
            if (!PreprocessShader(shader->filename, data)) {
               ERROR(shader->filename, " - preprocess failed");
               return false;
            }
            if (data.versionMajor > '4') {
               ERROR(shader->filename, " - D3D10 does not support shader model >4");
               return false;
            }

            char profile[]{ 'v','s','_',data.versionMajor,'_',data.versionMinor,'\0' };
            if (CompileShaderFromFile(shader->filename, "vs", "vs_4_0", &shader->D3D10.vsbuffer) == false) { ERROR("Vertex shader compilation error"); return false; }
            profile[0] = 'p';
            if (CompileShaderFromFile(shader->filename, "ps", "ps_4_0", &shader->D3D10.psbuffer) == false) { ERROR("Pixel shader compilation error"); return false; }


            HANDLE_D3D10_ERROR(device->CreateVertexShader(shader->D3D10.vsbuffer->GetBufferPointer(), shader->D3D10.vsbuffer->GetBufferSize(), &shader->D3D10.vs));
            HANDLE_D3D10_ERROR(device->CreatePixelShader(shader->D3D10.psbuffer->GetBufferPointer(), shader->D3D10.psbuffer->GetBufferSize(), &shader->D3D10.ps));
                        
            //HANDLE_D3D10_ERROR(device->CreateInputLayout(shader->D3D10.elements, shader->D3D10.elementCount, shader->D3D10.vsbuffer->GetBufferPointer(), shader->D3D10.vsbuffer->GetBufferSize(), &shader->D3D10.layout));
            SUCCESS("Created shader: ", shader->filename);
            return true;
         }
         void SetActiveShader(Shader *shader) {
            ASSERT(shader);
            ASSERT(shader->D3D10.layout);
            ASSERT(shader->D3D10.vs);
            ASSERT(shader->D3D10.ps);
            device->VSSetShader(shader->D3D10.vs);
            device->PSSetShader(shader->D3D10.ps);
            device->IASetInputLayout(shader->D3D10.layout);
         }
      }
      */ 
      /*namespace D3D12 {
         IDXGISwapChain *swapChain = nullptr;
         ID3D12Device *device = nullptr;
         ID3D12CommandQueue *commandQueue = nullptr;
         IDXGIFactory *factory = nullptr;
         IDXGIAdapter *adapter = nullptr;
         IDXGIOutput *adapterOutput = nullptr;
         ID3D12DescriptorHeap *renderTargetViewHeap;
         uint numModes;
         void Init(Window *wnd) {
            HANDLE_D3D12_ERROR(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, __uuidof(ID3D12Device), (void**)&device));
            D3D12_COMMAND_QUEUE_DESC cqd;
            cqd.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
            cqd.NodeMask = 0;
            cqd.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
            cqd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
            HANDLE_D3D12_ERROR(device->CreateCommandQueue(&cqd, __uuidof(ID3D12CommandQueue), (void**)&commandQueue));
            HANDLE_DXGI_ERROR(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory));
            HANDLE_DXGI_ERROR(factory->EnumAdapters(0, &adapter));
            HANDLE_DXGI_ERROR(adapter->EnumOutputs(0, &adapterOutput));
            HANDLE_DXGI_ERROR(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL));
            auto displayModeList = new DXGI_MODE_DESC[numModes];
            HANDLE_DXGI_ERROR(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList));
            uint numerator, denominator;
            for (int i = 0; i < numModes; i++)
            {
               if (displayModeList[i].Height == wnd->GetHeight())
               {
                  if (displayModeList[i].Width == wnd->GetWidth())
                  {
                     numerator = displayModeList[i].RefreshRate.Numerator;
                     denominator = displayModeList[i].RefreshRate.Denominator;
                  }
               }
            }
            DXGI_ADAPTER_DESC adapterDesc;
            HANDLE_DXGI_ERROR(adapter->GetDesc(&adapterDesc));

            auto m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
            size_t stringLength;
            char *m_videoCardDescription;
            if (wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128) != 0)
            {
               ERRORSRC("d3d12 failed");
            }

            delete[] displayModeList;
            displayModeList = 0;

            adapterOutput->Release();
            adapterOutput = 0;

            adapter->Release();
            adapter = 0;

            DXGI_SWAP_CHAIN_DESC swapChainDesc;
            ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

            swapChainDesc.BufferCount = 2;
            swapChainDesc.BufferDesc.Height = wnd->GetHeight();
            swapChainDesc.BufferDesc.Width = wnd->GetWidth();
            swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
            swapChainDesc.OutputWindow = wnd->hWnd;

            swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
            swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;

            // Turn multisampling off.
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;

            // Set the scan line ordering and scaling to unspecified.
            swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
            swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

            // Don't set the advanced flags.
            swapChainDesc.Flags = 0;

            // Finally create the swap chain using the swap chain description.
            HANDLE_DXGI_ERROR(factory->CreateSwapChain(commandQueue, &swapChainDesc, &swapChain));

            // Next upgrade the IDXGISwapChain to a IDXGISwapChain3 interface and store it in a private member variable named m_swapChain.
            // This will allow us to use the newer functionality such as getting the current back buffer index.
            // HANDLE_DXGI_ERROR(swapChain->QueryInterface(__uuidof(IDXGISwapChain), (void**)&swapChain));

            // Clear pointer to original swap chain interface since we are using version 3 instead (m_swapChain).
            // swapChain = 0;

            // Release the factory now that the swap chain has been created.
            factory->Release();
            factory = 0;

               // Initialize the render target view heap description for the two back buffers.
            D3D12_DESCRIPTOR_HEAP_DESC renderTargetViewHeapDesc;
            // Set the number of descriptors to two for our two back buffers.  Also set the heap tyupe to render target views.
            renderTargetViewHeapDesc.NumDescriptors = 2;
            renderTargetViewHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
            renderTargetViewHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

            // Create the render target view heap for the back buffers.
            HANDLE_D3D12_ERROR(device->CreateDescriptorHeap(&renderTargetViewHeapDesc, __uuidof(ID3D12DescriptorHeap), (void**)&renderTargetViewHeap));

            // Get a handle to the starting memory location in the render target view heap to identify where the render target views will be located for the two back buffers.
            auto renderTargetViewHandle = renderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();

            // Get the size of the memory location for the render target view descriptors.
            auto renderTargetViewDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

            // Get a pointer to the first back buffer from the swap chain.
            HANDLE_DXGI_ERROR(m_swapChain->GetBuffer(0, __uuidof(ID3D12Resource), (void**)&m_backBufferRenderTarget[0]));
            if (FAILED(result))
            {
               return false;
            }

            // Create a render target view for the first back buffer.
            m_device->CreateRenderTargetView(m_backBufferRenderTarget[0], NULL, renderTargetViewHandle);

            // Increment the view handle to the next descriptor location in the render target view heap.
            renderTargetViewHandle.ptr += renderTargetViewDescriptorSize;

            // Get a pointer to the second back buffer from the swap chain.
            result = m_swapChain->GetBuffer(1, __uuidof(ID3D12Resource), (void**)&m_backBufferRenderTarget[1]);
            if (FAILED(result))
            {
               return false;
            }

            // Create a render target view for the second back buffer.
            m_device->CreateRenderTargetView(m_backBufferRenderTarget[1], NULL, renderTargetViewHandle);
            With the two render target views created for our two back buffers we will be able to use them for rendering.To start we need to get an index to which buffer is the current one to be drawing to.

               // Finally get the initial index to which buffer is the current back buffer.
               m_bufferIndex = m_swapChain->GetCurrentBackBufferIndex();
            The next thing we create is the command allocator.The command allocator is going to be used for allocating memory for the list of commands that we send to the GPU each frame to render graphics.

               // Create a command allocator.
               result = m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&m_commandAllocator);
            if (FAILED(result))
            {
               return false;
            }
            The next thing we are going to do is create a command list.Command lists are one of key the components to understand in DirectX 12. Basically you fill the command list with all your rendering commands each frame and then send it into the command queue to execute the command list.And when you get more advanced you will create multiple command lists and execute them in parallel to get more efficiency in rendering.However that is where it gets tricky as you need to manage resources like you would in any multi - threaded program and ensure the execution order and dependencies between threads is safely handled.But for simplicity reasons in this tutorial I will just create a single one here for the time being.In future tutorials this will be removed from the D3DClass as it belongs elsewhere.

               // Create a basic command list.
               result = m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator, NULL, __uuidof(ID3D12GraphicsCommandList), (void**)&m_commandList);
            if (FAILED(result))
            {
               return false;
            }

            // Initially we need to close the command list during initialization as it is created in a recording state.
            result = m_commandList->Close();
            if (FAILED(result))
            {
               return false;
            }
            The final thing we are going to create is the fence.We use the fence as a signaling mechanism to notify us when the GPU is completely done rendering the command list that we submitted via the command queue.GPU and CPU synchronization is completely up to us to handle in DirectX 12, so fences become a very necessary tool.

               // Create a fence for GPU synchronization.
               result = m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), (void**)&m_fence);
            if (FAILED(result))
            {
               return false;
            }

            // Create an event object for the fence.
            m_fenceEvent = CreateEventEx(NULL, FALSE, FALSE, EVENT_ALL_ACCESS);
            if (m_fenceEvent == NULL)
            {
               return false;
            }

            // Initialize the starting fence value.
            m_fenceValue = 1;
         }
      }*/
      /*
      void(*_Init)(Window *wnd) = nullptr;
      void(*_Clear)(Color color) = nullptr;
      void(*_ResizeBuffers)(uint w, uint h) = nullptr;
      void(*_Present)() = nullptr;
      bool(*_GetFullscreen)() = nullptr;
      void(*_SetFullscreen)(bool value) = nullptr;
      void(*_CreateMeshBuffers)(Mesh *mesh) = nullptr;
      void(*_DrawMesh)(Mesh *mesh, Shader *shader) = nullptr;
      bool(*_CompileShaderFromFile)(Shader *shader) = nullptr;
      void(*_SetActiveShader)(Shader *shader) = nullptr;
      void Init(Window *wnd) {
         _Init(wnd);
      }
      void Clear(Color color) {
         _Clear(color);
      }
      void ResizeBuffers(uint w, uint h) {
         _ResizeBuffers(w, h);
      }
      void Present() {
         _Present();
      }
      bool GetFullscreen() {
         return _GetFullscreen();
      }
      void SetFullscreen(bool value) {
         _SetFullscreen(value);
      }
      void CreateMeshBuffers(Mesh *mesh) {
         _CreateMeshBuffers(mesh);
      }
      void DrawMesh(Mesh *mesh, Shader *shader) {
         _DrawMesh(mesh, shader);
      }
      bool CompileShaderFromFile(Shader *shader) {
         return _CompileShaderFromFile(shader);
      }
      void SetActiveShader(Shader *shader) {
         _SetActiveShader(shader);
      }
      int current = -1;
      void Set(int renderer) {
         if (current != -1) {
            ERROR("Changing renderer at runtime is not supported yet");
            return;
         }
         switch (renderer) {
         case Direct3D11:
            _Init = D3D11::Init;
            _Clear = D3D11::Clear;
            _ResizeBuffers = D3D11::ResizeBuffers;
            _Present = D3D11::Present;
            _GetFullscreen = D3D11::GetFullscreen;
            _SetFullscreen = D3D11::SetFullscreen;
            _CreateMeshBuffers = D3D11::CreateMeshBuffers;
            _DrawMesh = D3D11::DrawMesh;
            _CompileShaderFromFile = D3D11::CompileShader;
            _SetActiveShader = D3D11::SetActiveShader;
            break;
         //case Direct3D10:
         //   _Init = D3D10::Init;
         //   _Clear = D3D10::Clear;
         //   _ResizeBuffers = D3D10::ResizeBuffers;
         //   _Present = D3D10::Present;
         //   _GetFullscreen = D3D10::GetFullscreen;
         //   _SetFullscreen = D3D10::SetFullscreen;
         //   _CreateMeshBuffers = D3D10::CreateMeshBuffers;
         //   _DrawMesh = D3D10::DrawMesh;
         //   _CompileShaderFromFile = D3D10::CompileShaderFromFile;
         //   _SetActiveShader = D3D10::SetActiveShader;
         //   break;
         default:
            CRITICALERROR("Unresolved renderer");
            break;
         }
         current = renderer;
      }
      cstring GetName() {
         switch (current) {
         case Direct3D9:  return "Direct3D9";
         case Direct3D10: return "Direct3D10";
         case Direct3D11: return "Direct3D11";
         case Direct3D12: return "Direct3D12";
         default: return "Unresolved";
         }
      }
      */
}