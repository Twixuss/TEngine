#include "core.h"
#include "console.h"
#include "window.h"
#include "input.h"
#include "graphics/mesh.h"
#include "Monitor.h"
#include "FixedUpdater.h"
namespace TEngine {
   namespace Monitor {
      CWString Name;
      TEngine::Orientation Orientation;
      long2 Resolution;
      uint RefreshRate;
      uint BitsPerPixel;
      void Init() {
         DEVMODE d;
         d.dmSize = sizeof(DEVMODE);
         EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &d);
         RefreshRate = d.dmDisplayFrequency;
         Resolution.x = d.dmPelsWidth;
         Resolution.y = d.dmPelsHeight;
         BitsPerPixel = d.dmBitsPerPel;
         Name = d.dmDeviceName;
         Orientation = (TEngine::Orientation)d.dmDisplayOrientation;
         TE_PRINT("===Monitor===");
         TE_PRINT("Name:           ", Name);
         TE_PRINT("Resolution:     ", Resolution);
         TE_PRINT("Refresh rate:   ", RefreshRate);
         TE_PRINT("Bits per pixel: ", BitsPerPixel);
         TE_PRINT("Orientation:    ", Orientation);
         TE_PRINT("");
      }
   }
   namespace Application {
      CWString WindowName;
      GraphicsAPI UsingGraphicsAPI;
      float UpdateDelta;
      float FixedDelta;
      Clock Time;
   }
   void Run(int argc, char **argv, char **env, ApplicationSetupData &d) {
      using namespace Application;
      hInstance = GetModuleHandleA(nullptr);
#if TENGINE_LOG_LEVEL > 0
      Console::Init();
#else
#if TENGINE_PLATFORM == TENGINE_PLATFORM_WINDOWS
      ShowWindow(FindWindowA("ConsoleWindowClass", nullptr), SW_HIDE);
#endif
#endif
      TE_PRINT("--Arguments:--");
      for (int i = 0;i < argc;i++) {
         TE_PRINT(argv[i]);
      }
      TE_PRINT("--------------");
      int index = 0;
      while (env[index] != nullptr) {
         TE_PRINT(env[index]);
         index++;
      }
      TE_PRINT("--------------");

      Monitor::Init();
      Common::Init();
      
      /*App::App()*/{
         UsingGraphicsAPI = GraphicsAPI::Direct3D11;
         FixedDelta = 1.0f / 64;
         UpdateDelta = 1.0f / Monitor::RefreshRate;
         WindowName = L"Window name";
         d.Setup();
      }
      /*App::Run()*/ {
         Window::Init(WindowName, 800, 800);

         Renderer::Create(UsingGraphicsAPI);
         Renderer::instance->Init();

         Input::Init();
         AudioPlayer::Init();

         std::string title = ("TEngine - version: " TEXTA(TENGINE_VERSION)" - ") + std::string(Renderer::instance->GetName()) + std::string(" - draws: ");

         d.Start();

         Time.Begin();

         Repeater fixedUpdater(FixedDelta);
         fixedUpdater.Begin();

         auto e = WindowEvent::Close;
         while ((e = Window::Update()) != WindowEvent::Close) {
            switch (e)
            {
            case WindowEvent::Resize:
               TE_PRINT("Resized resolution: ", Window::Width, 'x', Window::Height);
               Renderer::instance->ResizeBuffers(Window::Width, Window::Height);
            case WindowEvent::Nothing: {
               if (Window::Focused) {
                  Input::Update();
                  if (Input::KeyDown(Key::F11)) {
                     Renderer::instance->SetFullscreen(!Renderer::instance->GetFullscreen());
                  }
               }

               auto fixedUpdates = fixedUpdater.Update();
               while (fixedUpdates--) {
                  d.FixedUpdate();
               }

               Renderer::instance->Prepare(Time);

               d.Update();

               Renderer::instance->Present();

#if 1// TENGINE_LOG_LEVEL > 0
               static Repeater titleUpdater(1);
               static int draws = 0;
               draws++;
               if (titleUpdater.Update()) {
                  SetWindowTextA(Window::hWnd,
                     std::string(title)
                     .append(std::to_string(draws))
                     .c_str());
                  draws = 0;
               }
#endif
               Time.Update(UpdateDelta);
               Window::Resized = false;
               break;
            }
            case WindowEvent::GotFocus:
               TE_PRINT("Got focus");
               break;
            case WindowEvent::LostFocus:
               TE_PRINT("Lost focus");
               break;
            case WindowEvent::Error:
               break;
            default:
               break;
            }
         }
      }
      /*App::~App()*/ {
         Input::Release();
         Audio::Release();
         Renderer::instance->Release();
#if TENGINE_LOG_LEVEL > 0
         TE_WARN("Execution is over. Press any key to exit.");
         Console::WaitForKeyPress();
#endif
      }
   }
}