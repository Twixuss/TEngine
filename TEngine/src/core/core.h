#pragma once
#include "common.h"
#include "console.h"
#include "graphics/renderer.h"
#include "sound.h"
#include "Clock.h"
namespace TEngine {
   struct ApplicationSetupData {
      using CallBack = void(*)();
      CallBack Setup;
      CallBack Start;
      CallBack Destroy;
      CallBack Resize;
      CallBack FixedUpdate;
      CallBack Update;
   };
   namespace Application {
      extern TENGINE_API CWString WindowName;
      extern TENGINE_API GraphicsAPI UsingGraphicsAPI;
      extern TENGINE_API float UpdateDelta;
      extern TENGINE_API float FixedDelta;
      extern TENGINE_API Clock Time;
   };
   TENGINE_API void Run(int argc, char **argv, char **env, ApplicationSetupData &data);
}