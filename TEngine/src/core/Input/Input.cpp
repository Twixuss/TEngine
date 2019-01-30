#include "core/console.h"
#include "core/window.h"
#include "core/input/input.h"
namespace TEngine
{   
   Input::Input(const Window& wnd) : r_Window(wnd)
   {
      TE_HANDLE_HRESULT(
         DirectInput8Create(
            wnd.GetClass().GetHINSTANCE(),
            DIRECTINPUT_VERSION,
            IID_IDirectInput8W, 
            (void**)m_DirectInput.GetAddressOf(), 
            nullptr
         )
      );
   }
   bool InputDevice::IsAcquired() const noexcept
   {
      return m_Device.Get() != nullptr;
   }
}