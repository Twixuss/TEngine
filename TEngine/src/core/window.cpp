#include "window.h"
#include "console.h"
#include "Monitor.h"
namespace TEngine {
   LRESULT CALLBACK Window::UpdateProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
      Window* const pWnd = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
      // forward message to window instance handler
      return pWnd->WndProc(hWnd, msg, wParam, lParam);
   }
   LRESULT CALLBACK Window::SetupProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
      if (msg == WM_NCCREATE) {
         Window* const pWnd = (Window*)((CREATESTRUCTW*)lp)->lpCreateParams;
         SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pWnd);
         SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)&UpdateProc);
         return pWnd->WndProc(hwnd, msg, wp, lp);
      }
      return DefWindowProc(hwnd, msg, wp, lp);
   }
   Window::Class::Class(String name, HINSTANCE hInst) noexcept : m_Name(name), m_HInst(hInst) {
      WNDCLASS wc = { 0 };
      wc.style = CS_OWNDC;
      wc.lpfnWndProc = SetupProc;
      wc.hInstance = m_HInst;
      wc.hCursor = LoadCursor(0, IDC_ARROW);
      wc.lpszClassName = name.CStr();
      ASSERT_EXEC(RegisterClassW(&wc));
   }
   Window::Window(const Window::Class& c, String title, uint _width, uint _height) noexcept :
      m_Class(c),
      Resized(false),
      Focused(true),
      ChangingFocus(false),
      Width(_width),
      Height(_height),
      m_Title(title) {
      RECT rect{ 0, 0, Width, Height };
      AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

      hWnd = CreateWindowW(c.GetName().CStr(), m_Title.CStr(), WS_OVERLAPPEDWINDOW,
         200, 200, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, c.GetHINSTANCE(), this);
      if (!hWnd) {
         TE_PRINT_HRESULT(GetLastError());
         StopProgram(-1);
      }
      ShowWindow(hWnd, SW_SHOW);
   }
   Window::Event Window::Update() {
      MSG msg;
      BOOL result;
      if ((result = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) != 0) {
         if (result == -1) {
            return Window::Event::Error;
         }
         if (msg.message == WM_QUIT) {
            return Window::Event::Close;
         }
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
      if (ChangingFocus) {
         ChangingFocus = false;
         Resized = false;
         if (!Focused) {
         }
         return Focused ? Window::Event::GotFocus : Window::Event::LostFocus;
      }
      if (Resized) {
         return Window::Event::Resize;
      }
      return Window::Event::Nothing;
   }
   void Window::EventsHandled() {
      Resized = false;
   }
   LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
      switch (msg) {
      case WM_GETMINMAXINFO: {
         LPMINMAXINFO m = (LPMINMAXINFO)lp;

         m->ptMinTrackSize.x = 256 + 16;
         m->ptMinTrackSize.y = 128 + 40;

         RECT rect{ 0,0,Monitor::GetResolution().x, Monitor::GetResolution().y };
         AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

         m->ptMaxTrackSize.x = rect.right - rect.left;
         m->ptMaxTrackSize.y = rect.bottom - rect.top;

         break;
      }
      case WM_SIZE:
         Width = LOWORD(lp);
         Height = HIWORD(lp);
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
}