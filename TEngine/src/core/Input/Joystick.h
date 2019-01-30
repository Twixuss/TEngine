#pragma once
#include "Core/Input/Input.h"
namespace TEngine
{
   class LibraryInterface Joystick : public InputDevice
   {
   public:
      enum class Axis
      {
         XPos,
         YPos,
         ZPos,
         XRot,
         YRot,
         ZRot,
      };
   public:
      Joystick(const Input& input) noexcept;
      void  Update() noexcept override;
      bool  Down(byte key) const noexcept;
      bool  Held(byte key) const noexcept;
      bool  Up(byte key) const noexcept;
      float GetAxis(Axis axis) const noexcept;
      uint  POV(byte key) const noexcept;
      int   Slider(byte key) const noexcept;
   private:
      struct JoystickState
      {
         union
         {
            LONG    l[6];                   /* xyz axis position, xyz axis rotation            */
            float   f[6];
         };
         LONG    rglSlider[2];           /* extra axes positions         */
         DWORD   rgdwPOV[4];             /* POV directions               */
         BYTE    rgbButtons[32];         /* 32 buttons                   */
      };
      JoystickState m_LastState;
      JoystickState m_State;
   };
}
