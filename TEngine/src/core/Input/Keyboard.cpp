#include "Keyboard.h"
#include "Core/Console.h"
namespace TEngine
{
   Keyboard::Keyboard(const Input& input) noexcept
   {
      TE_HANDLE_HRESULT(input.m_DirectInput->CreateDevice(GUID_SysKeyboard, m_Device.GetAddressOf(), NULL));
      TE_HANDLE_HRESULT(m_Device->SetDataFormat(&c_dfDIKeyboard));
      TE_HANDLE_HRESULT(m_Device->SetCooperativeLevel(input.r_Window.GetHWND(), DISCL_FOREGROUND | DISCL_EXCLUSIVE));
      TE_HANDLE_HRESULT(m_Device->Acquire());
   }
   void  Keyboard::Update() noexcept
   {
      if (!IsAcquired())
         return;
      memcpy(m_LastState, m_State, sizeof(m_State));
      HRESULT hr;
      if (FAILED(hr = m_Device->GetDeviceState(sizeof(m_State), m_State)))
      {
         TE_WARN("Keyboard cannot get state");
         TE_PRINT_HRESULT(hr);
         if (FAILED(m_Device->Acquire()))
         {
            TE_WARN("Keyboard cannot be aquired");
            TE_PRINT_HRESULT(hr);
         }
      }
   }
   Key   Keyboard::AnyKeyDown() const noexcept
   {
      for (int i = 0;i < 256;i++)
      {
         if (!m_LastState[i] && m_State[i])
         {
            return (Key)i;
         }
      }
      return (Key)0;
   }
   Key   Keyboard::AnyKeyHeld() const noexcept
   {
      for (int i = 0;i < 256;i++)
      {
         if (m_State[i])
         {
            return (Key)i;
         }
      }
      return (Key)0;
   }
   Key   Keyboard::AnyKeyUp() const noexcept
   {
      for (int i = 0;i < 256;i++)
      {
         if (m_LastState[i] && !m_State[i])
         {
            return (Key)i;
         }
      }
      return (Key)0;
   }
   bool  Keyboard::KeyDown(Key key) const noexcept
   {
      return !m_LastState[(byte)key] && m_State[(byte)key];
   }
   bool  Keyboard::KeyHeld(Key key) const noexcept
   {
      return m_State[(byte)key];
   }
   bool  Keyboard::KeyUp(Key key) const noexcept
   {
      return m_LastState[(byte)key] && !m_State[(byte)key];
   }
}
