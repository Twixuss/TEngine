#pragma once
#include "common.h"
namespace TEngine {
   enum class WindowEvent {
      Close,
      Nothing,
      Resize,
      GotFocus,
      LostFocus,
      Error
   };
   namespace Window {
      extern TENGINE_API HWND hWnd;
      extern TENGINE_API int Width, Height;
      extern TENGINE_API bool Resized, Focused, ChangingFocus;
      void Init(CWString name, uint width, uint height);
      WindowEvent Update();
   };
}