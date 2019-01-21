#pragma once
#include "core/common.h"
namespace TEngine {
   using namespace Math;
   enum class Orientation {
      Horizontal,
      Vertical,
      HorizontalFlipped,
      VerticalFlipped
   };
   template<typename T>
   std::basic_ostream<T> &operator<<(std::basic_ostream<T> &stream, const Orientation o) {
      switch (o)
      {
      case TEngine::Orientation::Horizontal:
         stream << "[Orientation::Horizontal]";
         break;
      case TEngine::Orientation::Vertical:
         stream << "[Orientation::Vertical]";
         break;
      case TEngine::Orientation::HorizontalFlipped:
         stream << "[Orientation::HorizontalFlipped]";
         break;
      case TEngine::Orientation::VerticalFlipped:
         stream << "[Orientation::VerticalFlipped]";
         break;
      default:
         stream << "[Invalid Orientation]";
         break;
      }
      return stream;
   }
   namespace Monitor {
      extern TENGINE_API CWString Name;
      extern TENGINE_API TEngine::Orientation Orientation;
      extern TENGINE_API long2 Resolution;
      extern TENGINE_API uint RefreshRate;
      extern TENGINE_API uint BitsPerPixel;
   };
}