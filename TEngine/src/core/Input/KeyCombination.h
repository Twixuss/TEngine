#pragma once
#include "Core/Input/Keyboard.h"
#include "Core/Input/Mouse.h"
#include "Core/Input/Joystick.h"
namespace TEngine
{
   class LibraryInterface NoVirtualTable KeyCombination
   {
      virtual float Get() const noexcept = 0;
   };
   struct KeyAxis : public KeyCombination
   {
      KeyAxis(const Keyboard& kbd, const Joystick& jstk, Key positive, Key negative, Joystick::Axis a) :
         r_Keyboard(kbd), 
         r_Joystick(jstk), 
         m_Positive(positive), 
         m_Negative(negative),
         m_Axis(a)
      {
      }
      float Get() const noexcept override
      {
         auto result = r_Keyboard.KeyHeld(m_Positive) - r_Keyboard.KeyHeld(m_Negative);
         return result == 0 ? r_Joystick.IsAcquired() ? r_Joystick.GetAxis(m_Axis) : 0.0f : result;
      }
   private:
      const Keyboard& r_Keyboard;
      const Joystick& r_Joystick;
      Key m_Positive, m_Negative;
      Joystick::Axis m_Axis;
   };
}