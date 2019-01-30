#pragma once
#include "core/input/input.h"
namespace TEngine
{
   class LibraryInterface Keyboard : public InputDevice
   {
   public:
      Keyboard(const Input& input) noexcept;
      void  Update() noexcept override;
      Key   AnyKeyDown() const noexcept;
      Key   AnyKeyHeld() const noexcept;
      Key   AnyKeyUp() const noexcept;
      bool  KeyDown(Key key) const noexcept;
      bool  KeyHeld(Key key) const noexcept;
      bool  KeyUp(Key key) const noexcept;
   private:
      BYTE m_LastState[256];
      BYTE m_State[256];
   };
}
