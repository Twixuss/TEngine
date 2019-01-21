#include "window.h"
#include "console.h"
#include "Monitor.h"
namespace TEngine {
   namespace Window {
      HWND hWnd;
      int Width, Height;
      bool Resized, Focused, ChangingFocus;
      LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
         switch (msg) {
         case WM_GETMINMAXINFO: {
            LPMINMAXINFO m = (LPMINMAXINFO)lp;

            m->ptMinTrackSize.x = 256 + 16;
            m->ptMinTrackSize.y = 128 + 40;

            RECT rect{ 0,0,Monitor::Resolution.x, Monitor::Resolution.y };
            AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

            m->ptMaxTrackSize.x = rect.right - rect.left;
            m->ptMaxTrackSize.y = rect.bottom - rect.top;

            break;
         }
         case WM_SIZE:
            Width = LOWORD(lp);
            Height =  HIWORD(lp);
            Resized = true;
            break;
         case WM_SETFOCUS:
            Focused = true;
            ChangingFocus = true;
            break;
         case WM_KILLFOCUS:
            Focused = false;
            ChangingFocus = true;
            break;
         case WM_DESTROY:
            PostQuitMessage(0);
            break;
         default:
            break;
         }
         return DefWindowProc(hwnd, msg, wp, lp);
      }
      void Init(CWString name, uint _width, uint _height) {
         Resized = false;
         Focused = true;
         ChangingFocus = false;
         Width = _width;
         Height = _height;

         WNDCLASS wc = { 0 };
         wc.style = CS_OWNDC;
         wc.lpfnWndProc = WndProc;
         wc.hInstance = hInstance;
         wc.hCursor = LoadCursor(0, IDC_ARROW);
         wc.lpszClassName = name;
         ASSERT_EXEC(RegisterClassW(&wc));

         RECT rect{ 0, 0, Width, Height };
         AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

         ASSERT_EXEC(
            hWnd = CreateWindowW(name, name, WS_OVERLAPPEDWINDOW,
               200, 200, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr)
         );

         ShowWindow(hWnd, SW_SHOW);
      }
      WindowEvent Window::Update() {
         MSG msg;
         BOOL result;
         if ((result = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) != 0) {
            if (result == -1) {
               return WindowEvent::Error;
            }
            if (msg.message == WM_QUIT) {
               return WindowEvent::Close;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }
         if (ChangingFocus) {
            ChangingFocus = false;
            Resized = false;
            if (!Focused) {
            }
            return Focused ? WindowEvent::GotFocus : WindowEvent::LostFocus;
         }
         if (Resized) {
            return WindowEvent::Resize;
         }
         return WindowEvent::Nothing;
      }
   }
}