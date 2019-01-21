#include "Clock.h"
namespace TEngine{
   Clock::Clock() : m_Delta(0.0f), m_TicksOld(0ull), m_TotalCounts(0u), m_TotalTime(0.0f) {}
   void Clock::Begin() {
      LARGE_INTEGER currentTime;
      QueryPerformanceCounter(&currentTime);
      m_TicksOld = currentTime.QuadPart;
   }
   void Clock::Reset() {
      m_TotalCounts = 0;
      m_TotalTime = 0;
      m_Delta = 0;
   }
   void Clock::Update() {
      LARGE_INTEGER currentTime;
      QueryPerformanceCounter(&currentTime);

      UINT64 tickCount = currentTime.QuadPart - m_TicksOld;
      m_TicksOld = currentTime.QuadPart;

      LARGE_INTEGER frequencyCount;
      QueryPerformanceFrequency(&frequencyCount);
      auto countsPerSecond = frequencyCount.QuadPart;
      m_Delta = (float)tickCount / countsPerSecond;
      m_TotalTime += m_Delta;
      m_TotalCounts++;
   }
   void Clock::Update(float minDelta) {
      LARGE_INTEGER currentTime;
      LARGE_INTEGER frequencyCount;
      QueryPerformanceCounter(&currentTime);
      QueryPerformanceFrequency(&frequencyCount);
      auto countsPerSecond = frequencyCount.QuadPart;
      float tempDelta = (float)(currentTime.QuadPart - m_TicksOld) / countsPerSecond;
      if (tempDelta < minDelta) {
         //std::this_thread::sleep_for(std::chrono::milliseconds(((u64)((minDelta - tempDelta) * 1000))));
         Sleep(((DWORD)((minDelta - tempDelta) * 1000)));
      }
      Update();
   }
}