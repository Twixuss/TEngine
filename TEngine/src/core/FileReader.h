#pragma once
#include "precompiled.h"
namespace TEngine {
   struct FileReader {
      FileReader(CWString f, int m = 1);
      FileReader(const FileReader &other) = delete;
      inline ~FileReader() { Close(); }
      inline char Peek() { return s.peek(); }
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
      template<typename Type>
      void ReadBlock(const Type *ptr, uint count) {
         s.read((char*)ptr, sizeof(Type) * count);
      }
      std::string ReadWord(CString separators);
      inline bool IsOpen() const { return s.is_open() && !s.eof(); }
      void Close();
      inline bool IsClosed() const { return closed; }
   private:
      std::ifstream s;
      bool closed;
   };
}