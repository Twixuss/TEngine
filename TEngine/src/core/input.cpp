#pragma once
#include <dinput.h>
#include "console.h"
#include "window.h"
#include "input.h"
namespace TEngine {
   namespace Input {
      IDirectInput8 *directInput = nullptr;
      IDirectInputDevice8 *keyboard = nullptr;
      IDirectInputDevice8 *mouse = nullptr;
      IDirectInputDevice8 *joystick = nullptr;
      BYTE lastKeyboardState[256];
      BYTE keyboardState[256];
      DIMOUSESTATE lastMouseState;
      DIMOUSESTATE mouseState;
      struct JoystickState {
         union {
            LONG    l[6];                   /* xyz axis position, xyz axis rotation            */
            float   f[6];
         };
         LONG    rglSlider[2];           /* extra axes positions         */
         DWORD   rgdwPOV[4];             /* POV directions               */
         BYTE    rgbButtons[32];         /* 32 buttons                   */
      };
      JoystickState lastJoystickState;
      JoystickState joystickState;
      bool CreateDevice(const GUID guid, IDirectInputDevice8 **device, LPCDIDATAFORMAT lpcDidf, HWND hwnd, DWORD flags) {
         if (FAILED(directInput->CreateDevice(guid, device, NULL))) {
            return false;
         }
         if (FAILED((*device)->SetDataFormat(lpcDidf))) {
            return false;
         }
         if (FAILED((*device)->SetCooperativeLevel(hwnd, flags))) {
            return false;
         }
         if (FAILED((*device)->Acquire())) {
            return false;
         }
         return true;
      }
      void UpdateDevice(IDirectInputDevice8 *device, DWORD stateSize, LPVOID state, CString deviceName) {
         static HRESULT hr;
         if (FAILED(hr = device->GetDeviceState(stateSize, state))) {
            if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED)) {
               if (SUCCEEDED(device->Acquire())) {
                  TE_WARN(deviceName, " wasn't acquired. Now it's ok.");
               }
            }
            else {
               TE_WARN("Unknown error occurred while getting ", deviceName, " state");
            }
         }
      }
      void ReleaseDevices() {
         if (keyboard) { keyboard->Unacquire(); keyboard->Release(); keyboard = nullptr; }
         if (mouse) { mouse->Unacquire(); mouse->Release(); mouse = nullptr; }
         if (joystick) { joystick->Unacquire(); joystick->Release(); joystick = nullptr; }
      }
      void  Release() {
         if (directInput) {
            directInput->Release();
            directInput = nullptr;
         }
         ReleaseDevices();
         TE_WARN("~~~ DirectInput has been released");
      }
      void  Init() {
         TE_HANDLE_HRESULT(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL));
         while (!Window::Focused)
            Sleep(10);
         TE_RETRYIF(CheckDevices() == 0, "No input devices. Unable to run engine");
      }
      byte  CheckDevices() {
         ReleaseDevices();
         byte result = 0;
         if (CreateDevice(GUID_SysKeyboard, &keyboard, &c_dfDIKeyboard, Window::hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)) {
            TE_SUCCESS("Created keyboard device");
            result++;
         }
         else {
            TE_WARN("Failed to create keyboard device");
         }
         if (CreateDevice(GUID_SysMouse, &mouse, &c_dfDIMouse, Window::hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)) {
            TE_SUCCESS("Created mouse device");
            result++;
         }
         else {
            TE_WARN("Failed to create mouse device");
         }
         if (CreateDevice(GUID_Joystick, &joystick, &c_dfDIJoystick, Window::hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)) {
            TE_SUCCESS("Created joystick device");
            result++;
         }
         else {
            TE_WARN("Failed to create joystick device");
         }
         return result;
      }
      void  Update()
      {
         for (int i = 0;i < 256;i++) {
            lastKeyboardState[i] = keyboardState[i];
         }
         lastMouseState = mouseState;
         lastJoystickState = joystickState;
         if (keyboard)
            UpdateDevice(keyboard, sizeof(keyboardState), keyboardState, "Keyboard");
         if (mouse)
            UpdateDevice(mouse, sizeof(DIMOUSESTATE), &mouseState, "Mouse");
         if (joystick) {
            UpdateDevice(joystick, sizeof(DIJOYSTATE), &joystickState, "Joystick");
            for (int i = 0;i < 6;i++) {
               joystickState.f[i] = Math::Map(joystickState.l[i], 0, 65534, 1, -1);
            }
         }
         else {
            for (int i = 0;i < 6;i++) {
               joystickState.f[i] = 0;
            }
         }
      }
      bool  IsKeyboardAcquired() noexcept {
         return keyboard;
      }
      bool  IsMouseAcquired() noexcept {
         return mouse;
      }
      bool  IsJoystickAcquired() noexcept {
         return joystick;
      }
      int   MouseDeltaX() noexcept {
         return mouseState.lX;
      }
      int   MouseDeltaY() noexcept {
         return mouseState.lY;
      }
      int   MouseDeltaZ() noexcept {
         return mouseState.lZ;
      }
      bool  MouseDown(byte key) noexcept {
         return !lastMouseState.rgbButtons[key] && mouseState.rgbButtons[key];
      }
      bool  MouseHeld(byte key) noexcept {
         return mouseState.rgbButtons[key];
      }
      bool  MouseUp(byte key) noexcept {
         return lastMouseState.rgbButtons[key] && !mouseState.rgbButtons[key];
      }
      Key   AnyKeyDown() noexcept {
         for (int i = 0;i < 256;i++) {
            if (!lastKeyboardState[i] && keyboardState[i]) {
               return (Key)i;
            }
         }
         return (Key)0;
      }
      Key   AnyKeyHeld() noexcept {
         for (int i = 0;i < 256;i++) {
            if (keyboardState[i]) {
               return (Key)i;
            }
         }
         return (Key)0;
      }
      Key   AnyKeyUp() noexcept {
         for (int i = 0;i < 256;i++) {
            if (lastKeyboardState[i] && !keyboardState[i]) {
               return (Key)i;
            }
         }
         return (Key)0;
      }
      bool  KeyDown(Key key) noexcept {
         return !lastKeyboardState[(byte)key] && keyboardState[(byte)key];
      }
      bool  KeyHeld(Key key) noexcept {
         return keyboardState[(byte)key];
      }
      bool  KeyUp(Key key) noexcept {
         return lastKeyboardState[(byte)key] && !keyboardState[(byte)key];
      }
      bool  JoystickDown(byte key) noexcept {
         return !lastJoystickState.rgbButtons[key] && joystickState.rgbButtons[key];
      }
      bool  JoystickHeld(byte key) noexcept {
         return joystickState.rgbButtons[key];
      }
      bool  JoystickUp(byte key) noexcept {
         return lastJoystickState.rgbButtons[key] && !joystickState.rgbButtons[key];
      }
      float JoystickAxis(Axis axis) noexcept {
         return joystickState.f[(int)axis];
      }
      uint  JoystickPOV(byte key)noexcept {
         return joystickState.rgdwPOV[key];
      }
      int   JoystickSlider(byte key) noexcept {
         return joystickState.rglSlider[key];
      }
   }
}