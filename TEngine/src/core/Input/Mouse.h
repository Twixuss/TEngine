#pragma once
#include "core/input/input.h"
namespace TEngine
{
   class LibraryInterface Mouse : public InputDevice
   {
   public:
      Mouse(const Input& input) noexcept;
      void  Update() noexcept override;
      int   DeltaX()const noexcept;
      int   DeltaY()const noexcept;
      int   DeltaZ()const noexcept;
      bool  Down(byte key)const noexcept;
      bool  Held(byte key)const noexcept;
      bool  Up(byte key)  const noexcept;
   private:
      DIMOUSESTATE m_LastState;
      DIMOUSESTATE m_State;
   };
}
