#pragma once
#include "precompiled.h"
#include "String.h"
namespace TEngine {
   LibraryInterface extern Char CurrentDirectory[MAX_PATH];
   LibraryInterface void StopProgram(int code);
   struct LibraryInterface Timestamp {
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
      
   struct LibraryInterface Color {
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

   template<typename Elem>
   struct List {
      std::vector<Elem> vec;
      Elem& Add(const Elem& elem) {
         vec.push_back(elem);
         return vec.back();
      }
      template<typename... Params>
      Elem& AddInPlace(Params ...params) {
         vec.emplace_back(params...);
         return vec.back();
      }
      Elem& operator[](size_t index) {
         return vec[index];
      }
      inline auto begin() { return vec.begin(); }
      inline auto end() { return vec.end(); }
   };

   namespace Common {
      LibraryInterface void Init();
      LibraryInterface List<String> GetFilesInDirectory(const String& path);
   }
}
