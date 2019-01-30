#include "core/common.h"
#include "core/console.h"
#include "core/FileReader.h"
namespace TEngine {
   HINSTANCE hInstance = nullptr;
   Char CurrentDirectory[MAX_PATH];

   void StopProgram(int code) {
      exit(code);
   }

   Color::Color() : r(0), g(0), b(0), a(0) {}
   Color::Color(float gray) : r(gray), g(gray), b(gray), a(1) {}
   Color::Color(float R, float G, float B, float A) : r(R), g(G), b(B), a(A) {}
   Color Color::HSVtoRGB() {
      float H = r * 360;
      float S = g;
      float V = b;
      float C = V * S;
      float X = C * (1 - abs(fmod(H / 60, 2) - 1));
      float m = V - C;
      float R = 0, G = 0, B = 0;
      if (H >= 0 && H < 60) {
         R = C;
         G = X;
         B = 0;
      }
      else if (H >= 60 && H < 120) {
         R = X;
         G = C;
         B = 0;
      }
      else if (H >= 120 && H < 180) {
         R = 0;
         G = C;
         B = X;
      }
      else if (H >= 180 && H < 240) {
         R = 0;
         G = X;
         B = C;
      }
      else if (H >= 240 && H < 300) {
         R = X;
         G = 0;
         B = C;
      }
      else if (H >= 300 && H <= 360) {
         R = C;
         G = 0;
         B = X;
      }
      R += m;
      G += m;
      B += m;
      return Color(R, G, B);
   }
   Color Color::HSLtoRGB() {
      float C = (1 - abs(2 * b - 1)) * g;
      float X = C * (1 - abs(fmod(r / 60, 2) - 1));
      float m = b - C / 2;
      float R = 0, G = 0, B = 0;
      if (r >= 0.0f && r < 0.166666666f) {
         R = C;
         G = X;
         B = 0;
      }
      else if (r >= 0.166666666f && r < 0.333333333f) {
         R = X;
         G = C;
         B = 0;
      }
      else if (r >= 0.333333333f && r < 0.5f) {
         R = 0;
         G = C;
         B = X;
      }
      else if (r >= 0.5f && r < 0.666666666f) {
         R = 0;
         G = X;
         B = C;
      }
      else if (r >= 0.666666666f && r < 0.833333333f) {
         R = X;
         G = 0;
         B = C;
      }
      else if (r >= 0.833333333f && r <= 1.0f) {
         R = C;
         G = 0;
         B = X;
      }
      R += m;
      G += m;
      B += m;
      return Color(R, G, B);
   }
   Color Color::CMYKtoRGB() {
      return Color(
         (1 - r)*(1 - a),
         (1 - g)*(1 - a),
         (1 - b)*(1 - a));
   }

   namespace Common {
      void Init() {
         GetCurrentDirectory(MAX_PATH, CurrentDirectory);
      }

      List<String> GetFilesInDirectory(const String& path) {
         List<String> result;
         for (const auto & f : std::filesystem::directory_iterator(path.CStr()))
            if(f.is_regular_file())
               result.AddInPlace(f.path().wstring());
         return result;
      }
   }
}