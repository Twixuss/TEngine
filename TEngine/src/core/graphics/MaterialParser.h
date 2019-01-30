#pragma once
#include "Core/Common.h"
#include "Core/Console.h"
#include "Core/FileReader.h"
namespace TEngine
{
   class MaterialParser
   {
      struct Token
      {
         enum class Type
         {
            Value,
            Comma
         };
         String str;
         Type type;
      };
      int m_Line = 0;
      Token ReadToken(FileReader& r)
      {
         Token result;
         char c;
         r.Read(c);
         while (c == ' ' || c == '\n')
         {
            if (c == '\n')
               m_Line++;
            r.Read(c);
         }
         while (1)
         {
            if (c == ',')
            {
               return { L"", Token::Type::Comma };
            }
            if (!r.IsOpen() || c == ' ' || c == '\n')
            {
               if (c == '\n')
                  m_Line++;
               break;
            }
            result.str.AddChar((char)c);
            c = r.Peek();
            if (c == ' ' || c == ',')
            {
               break;
            }
            else
            {
               r.Read(c);
            }
         }
         return result;
      }
   public:
      String m_ShaderPath;
      std::vector<float> m_Props;
      MaterialParser(const String& path)
      {
         FileReader r(path);
         Token token;
         while (r.IsOpen())
         {
            token = ReadToken(r);
            if (token.str == L"shader")
            {
               m_ShaderPath = ReadToken(r).str;
            }
            else if (token.str == L"data")
            {
               token = ReadToken(r);
               if (token.str == L"{")
               {
                  while (r.IsOpen())
                  {
                     token = ReadToken(r);
                     if (token.str == L"}")
                     {
                        break;
                     }
                     else if (token.type == Token::Type::Comma)
                     {
                        continue;
                     }
                     m_Props.emplace_back(wcstof(token.str.CStr(), nullptr));
                  }
               }
               else
               {
                  TE_WARN("File: ", path);
                  TE_WARN("Line: ", m_Line);
                  TE_WARN("Unresolved token: ", token.str, ". Expected \"{\"");
                  TE_ERROR("Material parse failed");
               }
            }
         }
         r.Close();
      }
   };
}