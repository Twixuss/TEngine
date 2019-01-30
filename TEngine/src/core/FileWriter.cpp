#include "FileWriter.h"
namespace TEngine {
   FileWriter::FileWriter(String f, int m) : s(f.CStr(), m), closed(false) {
      TE_ASSERT(s);
   }
   void FileWriter::Close() {
      if (closed)
         return;
      closed = true;
      s.close();
   }
}