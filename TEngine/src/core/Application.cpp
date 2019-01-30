#include "Core/Graphics/Mesh.h"
#include "Core/Input/Input.h"
#include "Core/Application.h"
#include "Core/Console.h"
#include "Core/FixedUpdater.h"
#include "Core/Monitor.h"
#include "Core/Sound.h"
#include "Core/Window.h"
namespace TEngine
{
   Application::Application(const String& title, int w, int h) :
      m_HInst(GetModuleHandleA(nullptr)),
      m_Window(Window::Class(L"DefaultTEngineClass", m_HInst), title, w, h),
      m_Input(m_Window),
      m_Keyboard(m_Input),
      m_Mouse(m_Input),
      m_Joystick(m_Input),
      m_GraphicsAPI(GraphicsAPI::Direct3D11),
      m_FixedDelta(1.0f / 64),
      m_UpdateDelta(1.0f / float(Monitor::GetRefreshRate()))
   {
   }
   Application::~Application()
   {
      delete m_Renderer;
   }
   void Application::Run(int argc, char **argv, char **env)
   {
      TE_PRINT("--Arguments:--");
      for (int i = 0;i < argc;i++)
      {
         TE_PRINT(argv[i]);
      }
      TE_PRINT("--------------");
      int index = 0;
      while (env[index] != nullptr)
      {
         TE_PRINT(env[index]);
         index++;
      }
      TE_PRINT("--------------");

      m_Renderer = Renderer::Create(m_GraphicsAPI);
      m_Renderer->Init(m_Window);

      AudioPlayer::Init(m_Window);

      String title = L"TEngine - version: " TEXTA(TENGINE_VERSION)" - " + m_Renderer->GetName() + String(L" - draws: ");

      Start();

      m_Time.Begin();

      Repeater fixedUpdater(m_FixedDelta);
      fixedUpdater.Begin();

      auto e = Window::Event::Close;

      while ((e = m_Window.Update()) != Window::Event::Close)
      {
         switch (e)
         {
         case Window::Event::Resize:
         {
            TE_PRINT("Resized resolution: ", m_Window.GetClientWidth(), 'x', m_Window.GetClientHeight());
            m_Renderer->ResizeBuffers(m_Window);
         }
         case Window::Event::Nothing:
         {
            if (m_Window.IsFocused())
            {
               m_Keyboard.Update();
               m_Mouse.Update();
               m_Joystick.Update();
               if (m_Keyboard.KeyDown(Key::F11))
               {
                  m_Renderer->SetFullscreen(!m_Renderer->GetFullscreen());
               }
            }

            auto fixedUpdates = fixedUpdater.Update();
            while (fixedUpdates--)
            {
               FixedUpdate();
            }

            m_Renderer->Prepare(m_Time);

            Update();
            Draw();

            m_Renderer->Present();

#if 1// TENGINE_LOG_LEVEL > 0
            static Repeater titleUpdater(1);
            static int draws = 0;
            draws++;
            if (titleUpdater.Update())
            {
               SetWindowTextW(m_Window.GetHWND(),
                              std::wstring(title.CStr())
                              .append(std::to_wstring(draws))
                              .c_str());
               draws = 0;
            }
#endif
            m_Time.Update(m_UpdateDelta);
            break;
         }
         case Window::Event::GotFocus:
            TE_PRINT("Got focus");
            break;
         case Window::Event::LostFocus:
            TE_PRINT("Lost focus");
            break;
         case Window::Event::Error:
            break;
         default:
            break;
         }
         m_Window.EventsHandled();
      }
   }
}
