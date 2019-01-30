#include "FileReader.h"
#include "core/console.h"
namespace TEngine {
   FileReader::FileReader(const String& f, int m) : s(f.CStr(), m) {
      closed = false;
      if (!s) {
         TE_ERROR("File ", f, " cannot be found");
      }
   }
   String FileReader::ReadWord(const String& separators) {
      String out;
      char c;
      const auto Contains = [](const String& sep, Char ch) {
         for (int i = 0;i < sep.Length();i++)
            if (sep[i] == ch)
               return true;
         return false;
      };
      while (!Contains(separators, c = Peek())) {
         out.AddChar(c);
         Read(c);
      }
      return out;
   }
   void FileReader::Close() {
      if (closed)
         return;
      closed = true;
      s.close();
   }
}