#pragma once
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
#define NOMINMAX
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

#pragma warning(disable:4005) // изменение макроопределения
#pragma warning(disable:4244) // преобразование "Тип1" в "Тип2", возможна потеря данных
#pragma warning(disable:4251) // "Тип1" должен иметь dll - интерфейс для использования клиентами "Тип2"
#pragma warning(disable:4305) // усечение из "Тип1" в "Тип2"
#pragma warning(disable:4838) // преобразование "Тип1" в "Тип2" требует сужающего преобразования

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
#include <dinput.h>
#include <DWrite.h>
#include <xnamath.h>
#include <DxErr.h>
#include <wrl.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3d10_1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3DCSX.lib")
#pragma comment(lib, "D3DCSXd.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dx10d.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx11d.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx9d.lib")
#pragma comment(lib, "d3dxof.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "DxErr.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "X3DAudio.lib")
#pragma comment(lib, "xapobase.lib")
#pragma comment(lib, "xapobased.lib")
#pragma comment(lib, "XAPOFX.lib")
#pragma comment(lib, "XInput.lib")

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
#include <filesystem>

#define TENGINE_PLATFORM_WINDOWS 0
#if TENGINE_LIBRARY_TYPE == TENGINE_LIBRARY_DLL && !defined(TENGINE_USE_SOURCE)
#ifdef TENGINE_LIBRARY
#define LibraryInterface __declspec(dllexport)
#else
#define LibraryInterface __declspec(dllimport)
#endif
#else
#define LibraryInterface
#endif

#define NoVirtualTable DECLSPEC_NOVTABLE
#define Interface __interface

#define _TEXTA(str) #str
#define _TEXTW(str) L#str
#define TEXTA(str) _TEXTA(str)
#define TEXTW(str) _TEXTW(str)

#define CASE_STR(c) case c:return L"[" TEXTA(c) "]"

#define RELEASE(ptr) if(ptr){ptr->Release();ptr=nullptr;}

#define GETTER(ret,name,member) inline ret name() const {return member;}inline ret& name(){return member;}
#define GET_CONST(ret,name,member) inline ret name() const {return member;}
#define GET_REF(ret,name,member) inline ret& name(){return member;}

#define TENGINE_VERSION 0.00

#ifdef NDEBUG
#define TE_ASSERT()
// Expression will be always executed whether it's Debug or Release config
#define ASSERT_EXEC(expression) expression
#else
//#define TE_ASSERT(x, msg) ((!!(x)) || MessageBoxA(nullptr, "File: " TEXTA(__FILE__) "\nLine: " TEXTA(__LINE__) "\nMessage: " msg, "Assertion failed", MB_OK))
//#define TE_ASSERT(x, msg) (void)((!!(x)) || (_wassert(_CRT_WIDE(#x), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0));
#define TE_ASSERT(x) assert(x)
// Expression will be always executed whether it's Debug or Release config
#define ASSERT_EXEC(expression) TE_ASSERT(expression)
#define DEBUG_CRT
#endif

#ifdef DEBUG_CRT
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

namespace TEngine {
   typedef wchar_t Char;

   typedef signed char sbyte;
   typedef signed long long i64;

   typedef unsigned short ushort;
   typedef unsigned int uint;
   typedef unsigned long ulong;
   typedef unsigned long long u64;

   class Application;
   class Input;
   class InputDevice;
   class Keyboard;
   class Mouse;
   class Joystick;
   class Renderer;
   class RendererD3D11;
   class Mesh;
   class Shader;
}

#include "core/math/Constants.h"
#include "core/math/Functions.h"
#include "core/math/Vector.h"
#include "core/math/Vector2.h"
#include "core/math/Vector3.h"
#include "core/math/Vector4.h"
#include "core/math/Vector4XM.h"
#include "core/math/Matrix4x4.h"
