#pragma once
#include "Common.h"
namespace TEngine
{
   struct LibraryInterface Window
   {
      struct LibraryInterface Class
      {
         Class(String name, HINSTANCE hinst) noexcept;
         inline String GetName() const
         {
            return m_Name;
         }
         inline HINSTANCE GetHINSTANCE() const
         {
            return m_HInst;
         }
      private:
         String m_Name;
         HINSTANCE m_HInst;
      };
      enum class Event
      {
         Close,
         Nothing,
         Resize,
         GotFocus,
         LostFocus,
         Error
      };
      Window(const Class& c, String title, uint width, uint height) noexcept;
      Event Update();
      void EventsHandled();
      inline int GetClientWidth() const
      {
         return Width;
      }
      inline int GetClientHeight() const
      {
         return Height;
      }
      inline HWND GetHWND() const
      {
         return hWnd;
      }
      inline String GetTitle() const
      {
         return m_Title;
      }
      inline bool IsResized() const
      {
         return Resized;
      }
      inline bool IsFocused() const
      {
         return Focused;
      }
      inline bool IsChangingFocus() const
      {
         return ChangingFocus;
      }
      inline const Class& GetClass() const
      {
         return m_Class;
      }
   private:
      const Class& m_Class;
      HWND hWnd;
      int Width, Height;
      bool Resized, Focused, ChangingFocus;
      String m_Title;
      LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
      static LRESULT CALLBACK SetupProc(HWND, UINT, WPARAM, LPARAM) noexcept;
      static LRESULT CALLBACK UpdateProc(HWND, UINT, WPARAM, LPARAM) noexcept;
   };
}