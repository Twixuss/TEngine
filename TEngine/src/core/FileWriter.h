#pragma once
#include "common.h"
namespace TEngine {
   struct FileWriter {
      FileWriter(CWString f, int m = std::ios::binary);
      FileWriter(const FileWriter &other) = delete;
      inline ~FileWriter() { Close(); }
      template<typename Type>
      void Write(const Type &val) {
         s.write((char*)&val, sizeof(Type));
      }
      void Close();
      inline bool IsClosed() const { return closed; }
   private:
      std::ofstream s;
      bool closed;
   };
}