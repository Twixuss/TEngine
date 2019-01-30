#include "Core/Console.h"
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
   void Console::SetColor(Console::Color fore, Console::Color back) {
      SetConsoleTextAttribute(hConsoleOutput, (WORD)fore + (WORD)back * 16);
   }
   Console::Color CheckNameColor(const String& str)
   {
      if (str == L"TEngine")
         return Console::Color::WHITE;
      return Console::Color::GREEN;
   }
   void Console::PrintFunc(const char* func)
   {
      PrintText(Color::RED, "Function: ");
      String word[8];
      Color colors[8];
      int cw = 0;
      for (int i = 0;i < strlen(func);i++)
      {
         if (func[i] == ':')
         {
            colors[cw] = CheckNameColor(word[cw]);
            i++;
            cw++;
            continue;
         }
         word[cw].AddChar(func[i]);
      }
      cw++;
      for (int i = 0;i < cw;i++)
      {
         if (i != 0)
         {
            SetColor(Color::WHITE);
            PrintText("::");
         }
         if (i == cw - 1)
         {
            SetColor(Color::YELLOW);
         }
         else
         {
            SetColor(colors[i]);
         }
         PrintText(word[i]);
      }
      PrintText('\n');
   }
#endif
}
#endif