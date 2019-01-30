#include "Core/Input/Joystick.h"
#include "Core/Console.h"
namespace TEngine
{
   Joystick::Joystick(const Input& input) noexcept
   {
      HRESULT hr;
      if (FAILED(hr = input.m_DirectInput->CreateDevice(GUID_Joystick, m_Device.GetAddressOf(), NULL)))
      {
         TE_WARN("Failed to create joystick");
         TE_PRINT_HRESULT(hr);
         return;
      }
      if (FAILED(hr = m_Device->SetDataFormat(&c_dfDIJoystick)))
      {
         TE_PRINT_HRESULT(hr);
         return;
      }
      if (FAILED(hr = m_Device->SetCooperativeLevel(input.r_Window.GetHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
      {
         TE_PRINT_HRESULT(hr);
         return;
      }
      if (FAILED(hr = m_Device->Acquire()))
      {
         TE_PRINT_HRESULT(hr);
         return;
      }
   }
   void Joystick::Update() noexcept
   {
      if (!IsAcquired())
         return;
      memcpy(&m_LastState, &m_State, sizeof(m_State));
      if (m_Device.Get())
      {
         HRESULT hr;
         if (FAILED(hr = m_Device->GetDeviceState(sizeof(m_State), &m_State)))
         {
            TE_WARN("Joystick cannot get state");
            TE_PRINT_HRESULT(hr);
            if (FAILED(m_Device->Acquire()))
            {
               TE_WARN("Joystick cannot be aquired");
               TE_PRINT_HRESULT(hr);
            }
         }
         for (int i = 0;i < 6;i++)
         {
            m_State.f[i] = Math::Map(m_State.l[i], 0, 65534, 1, -1);
         }
      }
      else
      {
         for (int i = 0;i < 6;i++)
         {
            m_State.f[i] = 0;
         }
      }
   }
   bool  Joystick::Down(byte key) const noexcept
   {
      return !m_LastState.rgbButtons[key] && m_State.rgbButtons[key];
   }
   bool  Joystick::Held(byte key) const noexcept
   {
      return m_State.rgbButtons[key];
   }
   bool  Joystick::Up(byte key) const noexcept
   {
      return m_LastState.rgbButtons[key] && !m_State.rgbButtons[key];
   }
   float Joystick::GetAxis(Axis axis) const noexcept
   {
      return m_State.f[(int)axis];
   }
   uint  Joystick::POV(byte key) const noexcept
   {
      return m_State.rgdwPOV[key];
   }
   int   Joystick::Slider(byte key) const noexcept
   {
      return m_State.rglSlider[key];
   }
}