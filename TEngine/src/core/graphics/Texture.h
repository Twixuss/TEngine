#pragma once
#include "core/common.h"
namespace TEngine {
   struct Texture {
      Texture(String filename);
      ~Texture();
      void SetToSlot(uint slot);
      void Release();
      inline uint GetID() const { return m_ID; }
   private:
      uint m_ID;
   };
}
