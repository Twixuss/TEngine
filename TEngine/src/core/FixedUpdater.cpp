#include "FixedUpdater.h"
namespace TEngine {
   Repeater::Repeater(float step) : m_Step(step), m_TicksOld(0), m_TotalTime(0.0f) { }
   void Repeater::Begin() {
      LARGE_INTEGER currentTime;
      QueryPerformanceCounter(&currentTime);
      m_TicksOld = currentTime.QuadPart;
   }
   uint Repeater::Update() {
      LARGE_INTEGER currentTime;
      QueryPerformanceCounter(&currentTime);

      UINT64 tickCount = currentTime.QuadPart - m_TicksOld;
      m_TicksOld = currentTime.QuadPart;

      LARGE_INTEGER frequencyCount;
      QueryPerformanceFrequency(&frequencyCount);
      auto countsPerSecond = frequencyCount.QuadPart;
      m_TotalTime += (float)tickCount / countsPerSecond;
      uint result = 0;
      while (m_TotalTime > 0) {
         m_TotalTime -= m_Step;
         result++;
      }
      return result;
   }
   void Repeater::Reset() {
      m_TotalTime = 0.0f;
      m_TicksOld = 0;
   }
}