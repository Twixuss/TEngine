#pragma once
//#pragma warning(disable:4838)
#pragma warning(disable:4005) // изменение макроопределения
#pragma warning(disable:4244) // преобразование "Тип1" в "Тип2", возможна потеря данных
//#define WIN32_LEAN_AND_MEAN
//#define NOGDICAPMASKS
//#define NOSYSMETRICS
//#define NOMENUS
//#define NOICONS
//#define NOSYSCOMMANDS
//#define NORASTEROPS
//#define OEMRESOURCE
//#define NOATOM
//#define NOCLIPBOARD
//#define NOCOLOR
//#define NOCTLMGR
//#define NODRAWTEXT
//#define NOKERNEL
//#define NONLS
//#define NOMEMMGR
//#define NOMETAFILE
//#define NOMINMAX
//#define NOOPENFILE
//#define NOSCROLL
//#define NOSERVICE
//#define NOSOUND
//#define NOWH
//#define NOCOMM
//#define NOKANJI
//#define NOHELP
//#define NOPROFILER
//#define NODEFERWINDOWPOS
//#define NOMCX
//#define NORPC
//#define NOPROXYSTUB
//#define NOIMAGE
//#define NOTAPE

#include <Windows.h>
#include <time.h>

#include <dxgi.h>
#include <DXGIFormat.h>
#include <DXGIType.h>
#include <D3Dcompiler.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <D3D10_1.h>
#include <D3D10.h>
#include <D3DX10.h>
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DCSX.h>
#include <dsound.h>
#include <DWrite.h>
#include <xnamath.h>
#include <DxErr.h>

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <array>
#include <atomic>
#include <cassert>
#include <chrono>
#include <cfloat>
#include <thread>
#include <locale>
#include <codecvt>
#include <map>

#include "core/math/Constants.h"
#include "core/math/Functions.h"
#include "core/math/Vector2.h"
#include "core/math/Vector3.h"
#include "core/math/Vector4.h"
#include "core/math/Vector4XM.h"
#include "core/math/Matrix4x4.h"

#define TENGINE_PLATFORM_WINDOWS 0
#if 0//TENGINE_LIBRARY_TYPE == TENGINE_LIBRARY_DLL
#ifdef TENGINE_LIBRARY
#define TENGINE_API __declspec(dllexport)
#else
#define TENGINE_API __declspec(dllimport)
#endif
#else
#define TENGINE_API
#endif
#define _TEXTA(str) #str
#define _TEXTW(str) L#str
#define TEXTA(str) _TEXTA(str)
#define TEXTW(str) _TEXTW(str)

#define CASE_STR(c) case c:return"[" TEXTA(c) "]"

#define RELEASE(ptr) if(ptr){ptr->Release();ptr=nullptr;}

#define TENGINE_VERSION 0.00

#ifdef NDEBUG
#define TE_ASSERT()
// Expression will be always executed whether it's Debug or Release config
#define ASSERT_EXEC(expression) expression
#else
#define TE_ASSERT(x) assert(x)
// Expression will be always executed whether it's Debug or Release config
#define ASSERT_EXEC(expression) TE_ASSERT(expression)
#endif

namespace TEngine {
   typedef wchar_t wchar;
   typedef char *String;
   typedef wchar *WString;
   typedef const char *CString;
   typedef const wchar *CWString;

   typedef signed char sbyte;
   typedef signed long long i64;

   typedef unsigned short ushort;
   typedef unsigned int uint;
   typedef unsigned long ulong;
   typedef unsigned long long u64;

   struct App;
   struct Renderer;
   struct MeshBuffers;
   struct Mesh;
   struct Shader;
   struct ShaderBuffers;
}