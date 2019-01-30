#include "Mouse.h"
#include "Core/Console.h"
namespace TEngine
{
   Mouse::Mouse(const Input & input) noexcept
   {
      TE_HANDLE_HRESULT(input.m_DirectInput->CreateDevice(GUID_SysMouse, m_Device.GetAddressOf(), NULL));
      TE_HANDLE_HRESULT(m_Device->SetDataFormat(&c_dfDIMouse));
      TE_HANDLE_HRESULT(m_Device->SetCooperativeLevel(input.r_Window.GetHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
      TE_HANDLE_HRESULT(m_Device->Acquire());
   }
   void Mouse::Update() noexcept
   {
      if (!IsAcquired())
         return;
      memcpy(&m_LastState, &m_State, sizeof(m_State));
      HRESULT hr;
      if (FAILED(hr = m_Device->GetDeviceState(sizeof(m_State), &m_State)))
      {
         TE_WARN("Mouse cannot get state");
         TE_PRINT_HRESULT(hr);
         if (FAILED(m_Device->Acquire()))
         {
            TE_WARN("Mouse cannot be aquired");
            TE_PRINT_HRESULT(hr);
         }
      }
   }
   int   Mouse::DeltaX()const noexcept
   {
      return m_State.lX;
   }
   int   Mouse::DeltaY()const noexcept
   {
      return m_State.lY;
   }
   int   Mouse::DeltaZ()const noexcept
   {
      return m_State.lZ;
   }
   bool  Mouse::Down(byte key)const noexcept
   {
      return !m_LastState.rgbButtons[key] && m_State.rgbButtons[key];
   }
   bool  Mouse::Held(byte key)const noexcept
   {
      return m_State.rgbButtons[key];
   }
   bool  Mouse::Up(byte key)  const noexcept
   {
      return m_LastState.rgbButtons[key] && !m_State.rgbButtons[key];
   }
}