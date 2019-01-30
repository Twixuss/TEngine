#pragma once
#include "Core/Graphics/Renderer.h"
#include "Core/Input/Input.h"
#include "Core/Input/Keyboard.h"
#include "Core/Input/Mouse.h"
#include "Core/Input/Joystick.h"
#include "Core/Clock.h"
#include "Core/Common.h"
#include "Core/Console.h"
namespace TEngine
{
   class LibraryInterface NoVirtualTable Application
   {
   public:
      Application(const String& title, int w, int h);
      void Run(int, char**, char**);
      virtual ~Application();
   protected:
      virtual void Start()
      {
      }
      virtual void Resize()
      {
      }
      virtual void FixedUpdate()
      {
      }
      virtual void Update()
      {
      }
      virtual void Draw()
      {
      }
   private:
      HINSTANCE m_HInst;
   protected:
      Window m_Window;
      Input m_Input;
      Keyboard m_Keyboard;
      Mouse m_Mouse;
      Joystick m_Joystick;
      GraphicsAPI m_GraphicsAPI;
      Renderer* m_Renderer;
      float m_UpdateDelta;
      float m_FixedDelta;
      Clock m_Time;
   };
}
