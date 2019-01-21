#pragma once
#include "common.h"
namespace TEngine{
   struct TENGINE_API Clock {
      Clock();
      void Begin();
      void Reset();
      // Calculates time passed from the last call
      void Update();
      // Calculates time passed from the last call and blocks current thread until (delta - minDelta) is passed
      void Update(float minDelta);
      inline float GetDelta() const { return m_Delta; }
      inline uint GetTotalCounts() const { return m_TotalCounts; }
      inline float GetTotalTime() const { return m_TotalTime; }
   private:
      float m_Delta;
      u64 m_TicksOld;
      uint m_TotalCounts;
      float m_TotalTime;
   };
}