#pragma once
#if TENGINE_USE_INTRINSICS == 0
#define _XM_NO_INTRINSICS_
#endif
#include "Core/Precompiled.h"
#if TENGINE_USE_SOURCE == 1
#undef LibraryInterface
#define LibraryInterface
#endif
#include "Core/Graphics/Mesh.h"
#include "Core/Graphics/MeshRenderer.h"
#include "Core/Graphics/Shader.h"
#include "Core/Input/Input.h"
#include "Core/Input/Joystick.h"
#include "Core/Input/Keyboard.h"
#include "Core/Input/Mouse.h"
#include "Core/Input/KeyCombination.h"
#include "Core/Application.h"
#include "Core/Common.h"
#include "Core/Console.h"
#include "Core/FileReader.h"
#include "Core/FileWriter.h"
#include "Core/Monitor.h"
#include "Core/Transform.h"
#include "Core/Sound.h"
extern TEngine::Application* SetupApp();
int main(int argc, char **argv, char **env)
{
#ifdef DEBUG_CRT
   _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#if TENGINE_LOG_LEVEL > 0
   TEngine::Console::Init();
   ShowWindow(FindWindowA("ConsoleWindowClass", nullptr), SW_SHOW);
#else
   ShowWindow(FindWindowA("ConsoleWindowClass", nullptr), SW_HIDE);
#endif
   TEngine::Monitor::Init();
   TEngine::Common::Init();
   auto app = SetupApp();
   app->Run(argc, argv, env);
   delete app;
#ifdef DEBUG_CRT
   _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
   _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
   _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
   _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
   _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
   _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
#endif
   TE_PRINT("Program terminated");
   return 0;
}
#if TENGINE_USE_SOURCE == 1
#include "Core/Graphics/Mesh.cpp"
#include "Core/Graphics/MeshRenderer.cpp"
#include "Core/Graphics/Renderer.cpp"
#include "Core/Graphics/RendererD3D11.cpp"
#include "Core/Graphics/RendererD3D12.cpp"
#include "Core/Graphics/Shader.cpp"
#include "Core/Graphics/Texture.cpp"
#include "Core/Input/Input.cpp"
#include "Core/Input/Keyboard.cpp"
#include "Core/Input/Mouse.cpp"
#include "Core/Application.cpp"
#include "Core/Clock.cpp"
#include "Core/Common.cpp"
#include "Core/Console.cpp"
#include "Core/FileReader.cpp"
#include "Core/FileWriter.cpp"
#include "Core/FixedUpdater.cpp"
#include "Core/Monitor.cpp"
#include "Core/Sound.cpp"
#include "Core/String.cpp"
#include "Core/Transform.cpp"
#include "Core/Window.cpp"
#endif