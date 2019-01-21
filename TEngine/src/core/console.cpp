#include "console.h"
#if TENGINE_LOG_LEVEL > 0
#pragma warning(disable:4996)
namespace TEngine {
#if TENGINE_PLATFORM == TENGINE_PLATFORM_WINDOWS
   HANDLE hConsoleOutput, hConsoleInput;
   void Console::Init() {
      AllocConsole();
      //freopen("CONOUT$", "w", stdout);
      hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
      hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
      SetConsoleCP(1251);
      SetConsoleOutputCP(1251);
   }
   Timestamp Console::GetCurrentLocalTime() {
      SYSTEMTIME st;
      GetLocalTime(&st);
      Timestamp t;
      t.h = st.wHour;
      t.m = st.wMinute;
      t.s = st.wSecond;
      t.ms = st.wMilliseconds;
      return t;
   }
   void Console::SetColor(CONSOLE_COLOR fore, CONSOLE_COLOR back) {
      SetConsoleTextAttribute(hConsoleOutput, (WORD)fore + (WORD)back * 16);
   }
   void Console::WaitForKeyPress() {
      INPUT_RECORD r;
      DWORD s;
      FlushConsoleInputBuffer(hConsoleInput);
      while (1) {
         ReadConsoleInput(hConsoleInput, &r, 1, &s);
         //PRINT(
         //   s, ' ',
         //   r.Event.KeyEvent.bKeyDown, ' ',
         //   r.Event.KeyEvent.dwControlKeyState, ' ',
         //   r.Event.KeyEvent.uChar.AsciiChar, ' ',
         //   r.Event.KeyEvent.uChar.UnicodeChar, ' ',
         //   r.Event.KeyEvent.wRepeatCount, ' ',
         //   r.Event.KeyEvent.wVirtualKeyCode, ' ',
         //   r.Event.KeyEvent.wVirtualScanCode
         //);
         if (r.Event.KeyEvent.uChar.AsciiChar != 0) {
            break;
         }
      }
   }
#endif
}
#endif