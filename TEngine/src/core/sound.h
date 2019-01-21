#pragma once
#include "window.h"
#include <dsound.h>
namespace TEngine {
   struct TENGINE_API AudioClip {
      AudioClip(LPCWSTR filename);
      ~AudioClip();
      void PlayWaveFile();
      void Test();
   private:
      IDirectSoundBuffer8* m_secondaryBuffer1;
   };
   struct TENGINE_API AudioPlayer {
      static void Init();
      void Play(AudioClip *clip);
   };
   struct TENGINE_API Audio {
      static void Release();
   };
}