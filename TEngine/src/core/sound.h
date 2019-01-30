#pragma once
#include "window.h"
#include <dsound.h>
namespace TEngine {
   using namespace Microsoft::WRL;
   struct LibraryInterface AudioClip {
      AudioClip(LPCWSTR filename);
      ~AudioClip();
      void PlayWaveFile();
      void Test();
   private:
      ComPtr<IDirectSoundBuffer8> m_secondaryBuffer1;
   };
   struct LibraryInterface AudioPlayer {
      static void Init(const Window& wnd);
      void Play(AudioClip *clip);
   };
   struct LibraryInterface Audio {
   };
}