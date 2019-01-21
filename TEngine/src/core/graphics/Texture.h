#pragma once
#include "precompiled.h"
namespace TEngine {
   struct Texture {
      Texture(CWString filename);
      ~Texture();
      void SetToSlot(uint slot);
      void Release();
      inline uint GetID() const { return m_ID; }
   private:
      uint m_ID;
   };
}