#include "Core/Monitor.h"
#include "Core/Console.h"
namespace TEngine::Monitor {
   String Name;
   TEngine::Orientation Orientation;
   long2 Resolution;
   uint RefreshRate;
   uint BitsPerPixel;
   String GetName() { return Name; }
   TEngine::Orientation GetOrientation() { return Orientation; }
   long2 GetResolution() { return Resolution; }
   uint GetRefreshRate() { return RefreshRate; }
   uint GetBitsPerPixel() { return BitsPerPixel; }
   void Init() {
      DEVMODE d;
      d.dmSize = sizeof(DEVMODE);
      EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &d);
      RefreshRate = d.dmDisplayFrequency;
      Resolution.x = d.dmPelsWidth;
      Resolution.y = d.dmPelsHeight;
      BitsPerPixel = d.dmBitsPerPel;
      Name = d.dmDeviceName;
      Orientation = (TEngine::Orientation)d.dmDisplayOrientation;
      //TE_PRINT("===Monitor===");
      //TE_PRINT("Name:           ", Name);
      //TE_PRINT("Resolution:     ", Resolution);
      //TE_PRINT("Refresh rate:   ", RefreshRate);
      //TE_PRINT("Bits per pixel: ", BitsPerPixel);
      //TE_PRINT("Orientation:    ", Orientation);
      //TE_PRINT("");
   }
}