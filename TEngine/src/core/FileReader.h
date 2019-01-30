#pragma once
#include "common.h"
namespace TEngine {
   struct LibraryInterface FileReader {
      FileReader(const String& f, int m = 1);
      FileReader(const FileReader &other) = delete;
      inline ~FileReader() { Close(); }
      inline int Peek() { return s.peek(); }
      template<typename Type>
      Type Read() {
         Type res;
         s.read((char*)&res, sizeof(Type));
         return res;
      }
      template<typename Type>
      Type &Read(Type &val) {
         s.read((char*)&val, sizeof(Type));
         return val;
      }
      // allocates in heap
      char* Read(int byteCount) {
         auto buf = new char[byteCount];
         s.read(buf, byteCount);
         return buf;
      }
      template<typename Type>
      void ReadBlock(const Type *ptr, uint count) {
         s.read((char*)ptr, sizeof(Type) * count);
      }
      String ReadWord(const String& separators);
      inline bool IsOpen() const { return s.is_open() && !s.eof() && !s.bad(); }
      void Close();
      inline bool IsClosed() const { return closed; }
   private:
      std::ifstream s;
      bool closed;
   };
}
