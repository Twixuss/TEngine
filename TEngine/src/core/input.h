#pragma once
#include "window.h"
namespace TEngine {
   enum class Key {
      None = 0x00,
      Escape = 0x01,
      K1 = 0x02,
      K2 = 0x03,
      K3 = 0x04,
      K4 = 0x05,
      K5 = 0x06,
      K6 = 0x07,
      K7 = 0x08,
      K8 = 0x09,
      K9 = 0x0A,
      K0 = 0x0B,
      Minus = 0x0C,    
      Equals = 0x0D,
      Backspace = 0x0E,    
      Tab = 0x0F,
      Q = 0x10,
      W = 0x11,
      E = 0x12,
      R = 0x13,
      T = 0x14,
      Y = 0x15,
      U = 0x16,
      I = 0x17,
      O = 0x18,
      P = 0x19,
      LeftBracket = 0x1A,
      RightBracket = 0x1B,
      Enter = 0x1C,   
      LeftControl = 0x1D,
      A = 0x1E,
      S = 0x1F,
      D = 0x20,
      F = 0x21,
      G = 0x22,
      H = 0x23,
      J = 0x24,
      K = 0x25,
      L = 0x26,
      Semicolon = 0x27,
      Apostrophe = 0x28,
      Grave = 0x29, 
      LeftShift = 0x2A,
      Backslash = 0x2B,
      Z = 0x2C,
      X = 0x2D,
      C = 0x2E,
      V = 0x2F,
      B = 0x30,
      N = 0x31,
      M = 0x32,
      Comma = 0x33,
      Period = 0x34,
      Slash = 0x35,    
      RightShift = 0x36,
      NumpadMultiply = 0x37, 
      LeftAlt = 0x38, 
      Space = 0x39,
      CapsLock = 0x3A,
      F1 = 0x3B,
      F2 = 0x3C,
      F3 = 0x3D,
      F4 = 0x3E,
      F5 = 0x3F,
      F6 = 0x40,
      F7 = 0x41,
      F8 = 0x42,
      F9 = 0x43,
      F10 = 0x44,
      NumLock = 0x45,
      ScrollLock = 0x46,  
      Numpad7 = 0x47,
      Numpad8 = 0x48,
      Numpad9 = 0x49,
      NumpadMinus = 0x4A,   
      Numpad4 = 0x4B,
      Numpad5 = 0x4C,
      Numpad6 = 0x4D,
      NumpadPlus = 0x4E,   
      Numpad1 = 0x4F,
      Numpad2 = 0x50,
      Numpad3 = 0x51,
      Numpad0 = 0x52,
      NumpadDot = 0x53,  
      OEM_102 =0x56,    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
      F11 = 0x57,
      F12 = 0x58,
      F13 = 0x64,    /*                     (NEC PC98) */
      F14 = 0x65,    /*                     (NEC PC98) */
      F15 = 0x66,    /*                     (NEC PC98) */
      KANA = 0x70,    /* (Japanese keyboard)            */
      ABNT_C1 = 0x73,    /* /? on Brazilian keyboard */
      CONVERT = 0x79,    /* (Japanese keyboard)            */
      NOCONVERT = 0x7B,    /* (Japanese keyboard)            */
      YEN = 0x7D,    /* (Japanese keyboard)            */
      ABNT_C2 = 0x7E,    /* Numpad . on Brazilian keyboard */
      NUMPADEQUALS = 0x8D,    /* = on numeric keypad (NEC PC98) */
      PREVTRACK = 0x90,    /* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */
      AT = 0x91,    /*                     (NEC PC98) */
      COLON = 0x92,    /*                     (NEC PC98) */
      UNDERLINE = 0x93,    /*                     (NEC PC98) */
      KANJI = 0x94,    /* (Japanese keyboard)            */
      STOP = 0x95,    /*                     (NEC PC98) */
      AX = 0x96,    /*                     (Japan AX) */
      UNLABELED = 0x97,    /*                        (J3100) */
      NextTrack = 0x99, 
      NumpadEnter = 0x9C,
      RightControl = 0x9D,
      Mute = 0xA0,   
      Calculator = 0xA1,    
      PlayPause = 0xA2,    
      MediaStop = 0xA4,   
      VolumeDown = 0xAE,    
      VolumeUp = 0xB0,    
      WebHome = 0xB2,    
      NumpadComma = 0xB3,
      NumpadDivide = 0xB5,
      SystemRequest = 0xB7,
      RightAlt = 0xB8,    
      Pause = 0xC5,    
      Home = 0xC7,        
      Up = 0xC8,          
      PageUp = 0xC9,      
      Left = 0xCB,        
      Right = 0xCD,       
      End = 0xCF,         
      Down = 0xD0,        
      PageDown = 0xD1,    
      Insert = 0xD2,      
      Delete = 0xD3,      
      LeftWindows = 0xDB, 
      RightWindows = 0xDC,
      AppMenu = 0xDD,     
      SysPower = 0xDE,    
      SysSleep = 0xDF,    
      SysWake = 0xE3,     
      WebSearch = 0xE5,   
      WebFavorites = 0xE6,
      WebRefresh = 0xE7,  
      WebStop = 0xE8,     
      WebForward = 0xE9,  
      WebBack = 0xEA,     
      MyComputer = 0xEB,  
      Mail = 0xEC,        
      MediaSelect = 0xED
   };
   constexpr CString TENGINE_API ToString(Key key) {
      switch (key) {
         CASE_STR(Key::None);
         CASE_STR(Key::Escape);
         CASE_STR(Key::K1);
         CASE_STR(Key::K2);
         CASE_STR(Key::K3);
         CASE_STR(Key::K4);
         CASE_STR(Key::K5);
         CASE_STR(Key::K6);
         CASE_STR(Key::K7);
         CASE_STR(Key::K8);
         CASE_STR(Key::K9);
         CASE_STR(Key::K0);
         CASE_STR(Key::Minus);
         CASE_STR(Key::Equals);
         CASE_STR(Key::Backspace);
         CASE_STR(Key::Tab);
         CASE_STR(Key::Q);
         CASE_STR(Key::W);
         CASE_STR(Key::E);
         CASE_STR(Key::R);
         CASE_STR(Key::T);
         CASE_STR(Key::Y);
         CASE_STR(Key::U);
         CASE_STR(Key::I);
         CASE_STR(Key::O);
         CASE_STR(Key::P);
         CASE_STR(Key::LeftBracket);
         CASE_STR(Key::RightBracket);
         CASE_STR(Key::Enter);
         CASE_STR(Key::LeftControl);
         CASE_STR(Key::A);
         CASE_STR(Key::S);
         CASE_STR(Key::D);
         CASE_STR(Key::F);
         CASE_STR(Key::G);
         CASE_STR(Key::H);
         CASE_STR(Key::J);
         CASE_STR(Key::K);
         CASE_STR(Key::L);
         CASE_STR(Key::Semicolon);
         CASE_STR(Key::Apostrophe);
         CASE_STR(Key::Grave);
         CASE_STR(Key::LeftShift);
         CASE_STR(Key::Backslash);
         CASE_STR(Key::Z);
         CASE_STR(Key::X);
         CASE_STR(Key::C);
         CASE_STR(Key::V);
         CASE_STR(Key::B);
         CASE_STR(Key::N);
         CASE_STR(Key::M);
         CASE_STR(Key::Comma);
         CASE_STR(Key::Period);
         CASE_STR(Key::Slash);
         CASE_STR(Key::RightShift);
         CASE_STR(Key::NumpadMultiply);
         CASE_STR(Key::LeftAlt);
         CASE_STR(Key::Space);
         CASE_STR(Key::CapsLock);
         CASE_STR(Key::F1);
         CASE_STR(Key::F2);
         CASE_STR(Key::F3);
         CASE_STR(Key::F4);
         CASE_STR(Key::F5);
         CASE_STR(Key::F6);
         CASE_STR(Key::F7);
         CASE_STR(Key::F8);
         CASE_STR(Key::F9);
         CASE_STR(Key::F10);
         CASE_STR(Key::NumLock);
         CASE_STR(Key::ScrollLock);
         CASE_STR(Key::Numpad7);
         CASE_STR(Key::Numpad8);
         CASE_STR(Key::Numpad9);
         CASE_STR(Key::NumpadMinus);
         CASE_STR(Key::Numpad4);
         CASE_STR(Key::Numpad5);
         CASE_STR(Key::Numpad6);
         CASE_STR(Key::NumpadPlus);
         CASE_STR(Key::Numpad1);
         CASE_STR(Key::Numpad2);
         CASE_STR(Key::Numpad3);
         CASE_STR(Key::Numpad0);
         CASE_STR(Key::NumpadDot);
         CASE_STR(Key::OEM_102);
         CASE_STR(Key::F11);
         CASE_STR(Key::F12);
         CASE_STR(Key::F13);
         CASE_STR(Key::F14);
         CASE_STR(Key::F15);
         CASE_STR(Key::KANA);
         CASE_STR(Key::ABNT_C1);
         CASE_STR(Key::CONVERT);
         CASE_STR(Key::NOCONVERT);
         CASE_STR(Key::YEN);
         CASE_STR(Key::ABNT_C2);
         CASE_STR(Key::NUMPADEQUALS);
         CASE_STR(Key::PREVTRACK);
         CASE_STR(Key::AT);
         CASE_STR(Key::COLON);
         CASE_STR(Key::UNDERLINE);
         CASE_STR(Key::KANJI);
         CASE_STR(Key::STOP);
         CASE_STR(Key::AX);
         CASE_STR(Key::UNLABELED);
         CASE_STR(Key::NextTrack);
         CASE_STR(Key::NumpadEnter);
         CASE_STR(Key::RightControl);
         CASE_STR(Key::Mute);
         CASE_STR(Key::Calculator);
         CASE_STR(Key::PlayPause);
         CASE_STR(Key::MediaStop);
         CASE_STR(Key::VolumeDown);
         CASE_STR(Key::VolumeUp);
         CASE_STR(Key::WebHome);
         CASE_STR(Key::NumpadComma);
         CASE_STR(Key::NumpadDivide);
         CASE_STR(Key::SystemRequest);
         CASE_STR(Key::RightAlt);
         CASE_STR(Key::Pause);
         CASE_STR(Key::Home);
         CASE_STR(Key::Up);
         CASE_STR(Key::PageUp);
         CASE_STR(Key::Left);
         CASE_STR(Key::Right);
         CASE_STR(Key::End);
         CASE_STR(Key::Down);
         CASE_STR(Key::PageDown);
         CASE_STR(Key::Insert);
         CASE_STR(Key::Delete);
         CASE_STR(Key::LeftWindows);
         CASE_STR(Key::RightWindows);
         CASE_STR(Key::AppMenu);
         CASE_STR(Key::SysPower);
         CASE_STR(Key::SysSleep);
         CASE_STR(Key::SysWake);
         CASE_STR(Key::WebSearch);
         CASE_STR(Key::WebFavorites);
         CASE_STR(Key::WebRefresh);
         CASE_STR(Key::WebStop);
         CASE_STR(Key::WebForward);
         CASE_STR(Key::WebBack);
         CASE_STR(Key::MyComputer);
         CASE_STR(Key::Mail);
         CASE_STR(Key::MediaSelect);
      default:                 return"[Key::Unknown]";
      }
   }
   template<typename T>
   std::basic_ostream<T> &operator<<(std::basic_ostream<T> &stream, const Key key) {
      stream << ToString(key);
      return stream;
   }
   namespace Input {
      enum class Axis {
         JoystickXPos = 0,
         JoystickYPos = 1,
         JoystickZPos = 2,
         JoystickXRot = 3,
         JoystickYRot = 4,
         JoystickZRot = 5,
      };
      void TENGINE_API Init();
      // Checks connected devices and returns their number
      byte  TENGINE_API CheckDevices();
      void  TENGINE_API Update();
      void  TENGINE_API Release();
      bool  TENGINE_API IsKeyboardAcquired() noexcept;
      bool  TENGINE_API IsMouseAcquired() noexcept;
      bool  TENGINE_API IsJoystickAcquired() noexcept;
      int   TENGINE_API MouseDeltaX() noexcept;
      int   TENGINE_API MouseDeltaY() noexcept;
      int   TENGINE_API MouseDeltaZ() noexcept;
      bool  TENGINE_API MouseDown(byte key) noexcept;
      bool  TENGINE_API MouseHeld(byte key) noexcept;
      bool  TENGINE_API MouseUp(byte key) noexcept;
      Key   TENGINE_API AnyKeyDown() noexcept;
      Key   TENGINE_API AnyKeyHeld() noexcept;
      Key   TENGINE_API AnyKeyUp() noexcept;
      bool  TENGINE_API KeyDown(Key key) noexcept;
      bool  TENGINE_API KeyHeld(Key key) noexcept;
      bool  TENGINE_API KeyUp(Key key) noexcept;
      bool  TENGINE_API JoystickDown(byte key) noexcept;
      bool  TENGINE_API JoystickHeld(byte key) noexcept;
      bool  TENGINE_API JoystickUp(byte key) noexcept;
      float TENGINE_API JoystickAxis(Axis axis) noexcept;
      uint  TENGINE_API JoystickPOV(byte key) noexcept;
      int   TENGINE_API JoystickSlider(byte key) noexcept;
      struct KeyPair {
         Key positive, negative;
         Axis a;
         KeyPair(Key positive, Key negative, Axis a) : positive(positive), negative(negative), a(a) {}
         float operator()() {
            auto result = Input::KeyHeld(positive) - Input::KeyHeld(negative);
            return result ? result : JoystickAxis(a);
         }
         operator float() {
            return (*this)();
         }
      };
   };
}