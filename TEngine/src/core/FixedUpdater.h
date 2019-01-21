#pragma once
#include "common.h"
namespace TEngine{
   struct TENGINE_API Repeater {
      Repeater(float step);
      void Begin();
      // Returns number of steps passed since last Update call
      uint Update();
      void Reset();
   private:
      float m_Step;
      u64 m_TicksOld;
      float m_TotalTime;
   };
}