#include "FileReader.h"
namespace TEngine {
   FileReader::FileReader(CWString f, int m) : s(f, m) {
      closed = false;
      TE_ASSERT(s);
   }
   std::string FileReader::ReadWord(CString separators) {
      std::string out;
      char c;
      const auto Contains = [](CString sep, char ch) {
         for (int i = 0;i < strlen(sep);i++)
            if (sep[i] == ch)
               return true;
         return false;
      };
      while (!Contains(separators, c = Peek())) {
         out.push_back(c);
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