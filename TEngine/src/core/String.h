#pragma once
#include "precompiled.h"
namespace TEngine
{
   class LibraryInterface String
   {
   public:
      String() noexcept;
      String(const Char*) noexcept;
      String(const std::wstring&) noexcept;
      ~String() noexcept;
      String& AddChar(char) noexcept;
      String& AddChar(wchar_t) noexcept;
      int Length() const noexcept;
      const Char* CStr() const noexcept;
      Char operator[](int i) const noexcept;
      Char& operator[](int i) noexcept;
      friend String operator+ (const String& a, const String& b) noexcept;
      friend bool operator==(const String& a, const String& b) noexcept;
      template<typename T>
      friend std::basic_ostream<T>& operator<<(std::basic_ostream<T>& stream, const String& str) noexcept
      {
         return stream << str.m_String;
      }
   private:
      std::wstring m_String;
   };
}
