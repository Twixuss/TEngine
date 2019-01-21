#include "FileWriter.h"
namespace TEngine {
   FileWriter::FileWriter(CWString f, int m) : s(f, m), closed(false) {
      TE_ASSERT(s);
   }
   void FileWriter::Close() {
      if (closed)
         return;
      closed = true;
      s.close();
   }
}