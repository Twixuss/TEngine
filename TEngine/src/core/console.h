#pragma once
#include "core/common.h"
#define NO_CONSOLE
#ifdef NDEBUG
#ifdef NO_CONSOLE
#define TENGINE_LOG_LEVEL 0
#else
#define TENGINE_LOG_LEVEL 1
#endif
#else
#define TENGINE_LOG_LEVEL 2
#endif
#if TENGINE_LOG_LEVEL > 0 // LEVEL 1+
#ifdef TENGINE_LIBRARY
#define _CONSOLE_TEXTCOLOR ::TEngine::Console::Color::GREY_DARK
#else
#define _CONSOLE_TEXTCOLOR ::TEngine::Console::Color::GREY_LIGHT
#endif
#define _CONSOLE_BACKCOLOR ::TEngine::Console::Color::BLACK
#define TE_WARN(...) ::TEngine::Console::PrintText(::TEngine::Console::Color::YELLOW,__VA_ARGS__, '\n')
#define TE_ERROR(...) ::TEngine::Console::Error(__FILE__,__LINE__,__FUNCSIG__,__VA_ARGS__)
#define TE_HANDLE_HRESULT(expr)  {HRESULT hr;TE_ASSERT(!FAILED(hr = expr));if (FAILED(hr)){Console::PrintHRESULT(hr) ;TE_ERROR(TEXTA(expr));}}
#define TE_PRINT_HRESULT(hr) Console::PrintHRESULT(hr)
#if TENGINE_LOG_LEVEL > 1 // LEVEL 2+
#define TE_PRINTLN()    ::TEngine::Console::PrintText(::TEngine::Console::Color::WHITE, '\n')
#define TE_PRINT(...)   ::TEngine::Console::PrintText(::TEngine::Console::Color::WHITE, __VA_ARGS__, '\n')
#define TE_SUCCESS(...) ::TEngine::Console::PrintText(::TEngine::Console::Color::GREEN, __VA_ARGS__, '\n')
#else
#define TE_PRINTLN()
#define TE_PRINT()  
#define TE_SUCCESS()
#endif
namespace TEngine
{
   struct LibraryInterface Console
   {
      enum class Color
      {
         BLACK, BLUE_DARK, GREEN_DARK, CYAN_DARK, RED_DARK, PINK_DARK, YELLOW_DARK, GREY_LIGHT, GREY_DARK, BLUE, GREEN, CYAN, RED, PINK, YELLOW, WHITE
      };
      static void Init();
      static void SetColor(Color fore, Color back = Color::BLACK);
      static Timestamp GetCurrentLocalTime();
      template<typename T>
      static void PrintText(Color color, T msg)
      {
         SetColor(_CONSOLE_TEXTCOLOR, _CONSOLE_BACKCOLOR);
         PrintText(GetCurrentLocalTime());
         SetColor(color, _CONSOLE_BACKCOLOR);
         PrintText(msg);
      }
      template<typename T, typename... R>
      static void PrintText(Color color, T msg, R ...args)
      {
         SetColor(_CONSOLE_TEXTCOLOR, _CONSOLE_BACKCOLOR);
         PrintText(GetCurrentLocalTime());
         SetColor(color, _CONSOLE_BACKCOLOR);
         PrintText(msg);
         PrintText(args...);
      }
      template<class... T>
      static void Error(const char* file, int line, const char* func, T ...args)
      {
         PrintText(Color::RED, "File: ");
         SetColor(Color::YELLOW);
         PrintText(file, "\a\n");
         PrintText(Color::RED, "Line: ");
         SetColor(Color::YELLOW);
         PrintText(line, '\n');
         PrintText(Color::RED, "Function: ");
         SetColor(Color::YELLOW);
         PrintText(func, '\n');
         PrintText(Color::RED, "Message: ");
         SetColor(Color::YELLOW);
         PrintText(args..., '\n');
         system("pause");
         exit(-1);
      }
      inline static void PrintHRESULT(HRESULT hr)
      {
         if (FAILED(hr))
         {
            TE_WARN("HRESULT Failed: 0x", std::hex, std::uppercase, hr, std::dec);
         }
         else
         {
            TE_SUCCESS("HRESULT Succeeded");
         }
         char* pMsgBuf;
         DWORD nMsgLen = FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (char*)&pMsgBuf, 0, nullptr
         );
         if (!nMsgLen)
         {
            TE_WARN("Unidentified error code");
         }
         TE_WARN("Message: ", pMsgBuf);
         LocalFree(pMsgBuf);
      }
   private:
      static void PrintFunc(const char*);
      template<typename T>
      inline static void PrintText(T msg)
      {
         std::wcout << msg;
      }
      template<typename T, typename... R>
      inline static void PrintText(T msg, R ...args)
      {
         PrintText(msg);
         PrintText(args...);
      }
   };
}
#else // LEVEL 0
#define SetConsoleTitleA()
#define SetConsoleTitleW()
#define TE_PRINTLN()
#define TE_PRINT(x)
#define TE_SUCCESS(x)
#define TE_WARN(x)
#define TE_ERROR(x) {MessageBoxA(nullptr, "Expression: "#x "\nFile: " TEXTA(__FILE__) "\nLine: " TEXTA(__LINE__), "Error", MB_OK);exit(-1);}
#define TE_HANDLE_HRESULT(expr)  if (FAILED(expr))TE_ERROR(TEXTA(expr));
#define TE_PRINT_HRESULT(hr)
#define TE_RETRYIF(condition, msg)           \
      {bool retry;                        \
      do {                                \
         retry = false;                   \
         if (condition) {                 \
            if(MessageBoxA(nullptr, "Error", "Error", MB_RETRYCANCEL)!=2){system("PAUSE");}                 \
            retry = true;                 \
         }                                \
      } while (retry);}
#endif
