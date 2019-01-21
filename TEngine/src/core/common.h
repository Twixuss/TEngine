#pragma once
#include "precompiled.h"
namespace TEngine {
   extern HINSTANCE hInstance;
   inline wchar CurrentDirectory[MAX_PATH];
   struct Timestamp {
      ushort ms, s, m, h;
      template<typename T>
      friend std::basic_ostream<T> & operator<<(std::basic_ostream<T> & stream, const Timestamp & t) {
         stream << '[';
         if (t.h < 10)
            stream << '0';
         stream << t.h << ':';
         if (t.m < 10)
            stream << '0';
         stream << t.m << ':';
         if (t.s < 10)
            stream << '0';
         stream << t.s << '.';
         if (t.ms < 100) {
            stream << '0';
            if (t.ms < 10)
               stream << '0';
         }
         stream << t.ms << "] ";
         return stream;
      }
   };
      
   struct TENGINE_API Color {
      // normalized values
      float r, g, b, a;
      Color();
      Color(float gray);
      Color(float R, float G, float B, float A = 1);
      Color HSVtoRGB();
      Color HSLtoRGB();
      Color CMYKtoRGB();
      template<typename T>
      friend std::basic_ostream<T> & operator<<(std::basic_ostream<T> &stream, Color c) {
         stream << "[r:" << c.r << ", g:" << c.g << ", b:" << c.b << ", a:" << c.a << ']';
         return stream;
      }
   };

   namespace Common {
      inline void Init() {
#if TENGINE_PLATFORM == TENGINE_PLATFORM_WINDOWS
         GetCurrentDirectory(MAX_PATH, CurrentDirectory);
#endif
      }
   }
}