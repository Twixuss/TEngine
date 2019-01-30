#include "String.h"
namespace TEngine {
   String::String() noexcept
   {

   }
   String::String(const Char* str) noexcept :
      m_String(str)
   {

   }
   String::String(const std::wstring& str) noexcept :
      m_String(str)
   {

   }
   String::~String() noexcept
   {
   }
   String& String::AddChar(char c) noexcept
   {
      m_String.push_back(c);
      return *this;
   }
   String& String::AddChar(wchar_t c) noexcept
   {
      m_String.push_back(c);
      return *this;
   }
   int String::Length() const noexcept
   {
      return m_String.length();
   }
   const Char* String::CStr() const noexcept
   {
      return m_String.c_str();
   }
   Char String::operator[](int i) const noexcept
   {
      return m_String[i];
   }
   Char& String::operator[](int i) noexcept
   {
      return m_String[i];
   }
   String operator+(const String& a, const String& b) noexcept
   {
      String result;
      result.m_String = a.m_String + b.m_String;
      return result;
   }
   bool operator==(const String & a, const String & b) noexcept
   {
      return a.m_String == b.m_String;
   }
}
