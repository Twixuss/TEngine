#pragma once
#include "common.h"
enum class CONSOLE_COLOR {
   BLACK, BLUE_DARK, GREEN_DARK, CYAN_DARK, RED_DARK, PINK_DARK, YELLOW_DARK, GREY_LIGHT, GREY_DARK, BLUE, GREEN, CYAN, RED, PINK, YELLOW, WHITE
};
#define NO_CONSOLE
#ifdef NDEBUG
#ifdef NO_CONSOLE
#define TENGINE_LOG_LEVEL 0
#else
#define TENGINE_LOG_LEVEL 1
#endif
#else
#define TENGINE_LOG_LEVEL 2
#endif
#if TENGINE_LOG_LEVEL > 0 // LEVEL 1+
#ifdef TENGINE_LIBRARY
#define _CONSOLE_TEXTCOLOR CONSOLE_COLOR::GREY_DARK
#else
#define _CONSOLE_TEXTCOLOR CONSOLE_COLOR::GREY_LIGHT
#endif
#define _CONSOLE_BACKCOLOR CONSOLE_COLOR::BLACK
#define TE_WARN(...) ::TEngine::Console::PrintText(CONSOLE_COLOR::YELLOW,__VA_ARGS__, '\n')
#define TE_ERROR(...) {::TEngine::Console::PrintText(CONSOLE_COLOR::RED  ,__VA_ARGS__," - FILE: ",__FILE__," - LINE: ",__LINE__,'\n');MessageBoxA(nullptr,"File: " TEXTA(__FILE__)"\nLine: " TEXTA(__LINE__),"Error",MB_OK);exit(-1);}
#define TE_HANDLE_HRESULT(expr)  {HRESULT hr;if (FAILED(hr = expr)){Console::PrintHRESULT(hr) ;TE_ERROR(TEXTA(expr));}}
#define TE_RETRYIF(condition, msg)           \
      {bool retry;                        \
      do {                                \
         retry = false;                   \
         if (condition) {                 \
            TE_WARN(msg);                 \
            if(MessageBoxA(nullptr,"File: " TEXTA(__FILE__)"\nLine: " TEXTA(__LINE__),"Error", MB_RETRYCANCEL)!=2){retry = true;}\
         }                                \
      } while (retry);}
#if TENGINE_LOG_LEVEL > 1 // LEVEL 2+
#define TE_PRINTLN()    ::TEngine::Console::PrintText(CONSOLE_COLOR::WHITE, '\n')
#define TE_PRINT(...)   ::TEngine::Console::PrintText(CONSOLE_COLOR::WHITE, __VA_ARGS__, '\n')
#define TE_SUCCESS(...) ::TEngine::Console::PrintText(CONSOLE_COLOR::GREEN, __VA_ARGS__, '\n')
#else
#define TE_PRINTLN()
#define TE_PRINT()  
#define TE_SUCCESS()
#endif
namespace TEngine {
   struct TENGINE_API Console {
      static void Init();
      static void SetColor(CONSOLE_COLOR fore, CONSOLE_COLOR back);
      static Timestamp GetCurrentLocalTime();
      template<typename T>
      static void PrintText(CONSOLE_COLOR color, T msg) {
         SetColor(_CONSOLE_TEXTCOLOR, _CONSOLE_BACKCOLOR);
         PrintText(GetCurrentLocalTime());
         SetColor(color, _CONSOLE_BACKCOLOR);
         PrintText(msg);
      }
      template<typename T, typename... R>
      static void PrintText(CONSOLE_COLOR color, T msg, R ...args) {
         SetColor(_CONSOLE_TEXTCOLOR, _CONSOLE_BACKCOLOR);
         PrintText(GetCurrentLocalTime());
         SetColor(color, _CONSOLE_BACKCOLOR);
         PrintText(msg);
         PrintText(args...);
      }
      static void WaitForKeyPress();
#define p(r) case r: TE_WARN(#r);return
      inline static void PrintHRESULT(HRESULT hr) {
         TE_WARN("HRESULT Failed: 0x", std::hex, hr, std::dec);
         switch (hr){
            p(DXGI_ERROR_ACCESS_DENIED);
            p(DXGI_ERROR_ACCESS_LOST);
            p(DXGI_ERROR_ALREADY_EXISTS);
            p(DXGI_ERROR_CACHE_CORRUPT);
            p(DXGI_ERROR_CACHE_FULL);
            p(DXGI_ERROR_CACHE_HASH_COLLISION);
            p(DXGI_ERROR_CANNOT_PROTECT_CONTENT);
            p(DXGI_ERROR_DEVICE_HUNG);
            p(DXGI_ERROR_DEVICE_REMOVED);
            p(DXGI_ERROR_DEVICE_RESET);
            p(DXGI_ERROR_DRIVER_INTERNAL_ERROR);
            p(DXGI_ERROR_DYNAMIC_CODE_POLICY_VIOLATION);
            p(DXGI_ERROR_FRAME_STATISTICS_DISJOINT);
            p(DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE);
            p(DXGI_ERROR_HW_PROTECTION_OUTOFMEMORY);
            p(DXGI_ERROR_INVALID_CALL);
            p(DXGI_ERROR_MODE_CHANGE_IN_PROGRESS);
            p(DXGI_ERROR_MORE_DATA);
            p(DXGI_ERROR_NAME_ALREADY_EXISTS);
            p(DXGI_ERROR_NONEXCLUSIVE);
            p(DXGI_ERROR_NON_COMPOSITED_UI);
            p(DXGI_ERROR_NOT_CURRENT);
            p(DXGI_ERROR_NOT_CURRENTLY_AVAILABLE);
            p(DXGI_ERROR_NOT_FOUND);
            p(DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED);
            p(DXGI_ERROR_REMOTE_OUTOFMEMORY);
            p(DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE);
            p(DXGI_ERROR_SDK_COMPONENT_MISSING);
            p(DXGI_ERROR_SESSION_DISCONNECTED);
            p(DXGI_ERROR_UNSUPPORTED);
            p(DXGI_ERROR_WAIT_TIMEOUT);
            p(DXGI_ERROR_WAS_STILL_DRAWING);
            p(D3D10_ERROR_FILE_NOT_FOUND);
            p(D3D10_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS);
            p(D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD);
            p(D3D11_ERROR_FILE_NOT_FOUND);
            p(D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS);
            p(D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS);
            p(D3D12_ERROR_ADAPTER_NOT_FOUND);
            p(D3D12_ERROR_DRIVER_VERSION_MISMATCH);
            p(E_ABORT);
            p(E_ACCESSDENIED);
            p(E_APPLICATION_ACTIVATION_EXEC_FAILURE);
            p(E_APPLICATION_ACTIVATION_TIMED_OUT);
            p(E_APPLICATION_EXITING);
            p(E_APPLICATION_MANAGER_NOT_RUNNING);
            p(E_APPLICATION_NOT_REGISTERED);
            p(E_APPLICATION_TEMPORARY_LICENSE_ERROR);
            p(E_APPLICATION_TRIAL_LICENSE_EXPIRED);
            p(E_APPLICATION_VIEW_EXITING);
            p(E_ASYNC_OPERATION_NOT_STARTED);
            p(E_AUDIO_ENGINE_NODE_NOT_FOUND);
            p(E_BLUETOOTH_ATT_ATTRIBUTE_NOT_FOUND);
            p(E_BLUETOOTH_ATT_ATTRIBUTE_NOT_LONG);
            p(E_BLUETOOTH_ATT_INSUFFICIENT_AUTHENTICATION);
            p(E_BLUETOOTH_ATT_INSUFFICIENT_AUTHORIZATION);
            p(E_BLUETOOTH_ATT_INSUFFICIENT_ENCRYPTION);
            p(E_BLUETOOTH_ATT_INSUFFICIENT_ENCRYPTION_KEY_SIZE);
            p(E_BLUETOOTH_ATT_INSUFFICIENT_RESOURCES);
            p(E_BLUETOOTH_ATT_INVALID_ATTRIBUTE_VALUE_LENGTH);
            p(E_BLUETOOTH_ATT_INVALID_HANDLE);
            p(E_BLUETOOTH_ATT_INVALID_OFFSET);
            p(E_BLUETOOTH_ATT_INVALID_PDU);
            p(E_BLUETOOTH_ATT_PREPARE_QUEUE_FULL);
            p(E_BLUETOOTH_ATT_READ_NOT_PERMITTED);
            p(E_BLUETOOTH_ATT_REQUEST_NOT_SUPPORTED);
            p(E_BLUETOOTH_ATT_UNKNOWN_ERROR);
            p(E_BLUETOOTH_ATT_UNLIKELY);
            p(E_BLUETOOTH_ATT_UNSUPPORTED_GROUP_TYPE);
            p(E_BLUETOOTH_ATT_WRITE_NOT_PERMITTED);
            p(E_BOUNDS);
            p(E_CHANGED_STATE);
            p(E_DRAW);
            p(E_ELEVATED_ACTIVATION_NOT_SUPPORTED);
            p(E_FAIL);
            p(E_FULL_ADMIN_NOT_SUPPORTED);
            p(E_HANDLE);
            p(E_HDAUDIO_CONNECTION_LIST_NOT_SUPPORTED);
            p(E_HDAUDIO_EMPTY_CONNECTION_LIST);
            p(E_HDAUDIO_NO_LOGICAL_DEVICES_CREATED);
            p(E_HDAUDIO_NULL_LINKED_LIST_ENTRY);
            p(E_ILLEGAL_DELEGATE_ASSIGNMENT);
            p(E_ILLEGAL_METHOD_CALL);
            p(E_ILLEGAL_STATE_CHANGE);
            p(E_INVALIDARG);
            p(E_INVALID_PROTOCOL_FORMAT);
            p(E_INVALID_PROTOCOL_OPERATION);
            p(E_MBN_BAD_SIM);
            p(E_MBN_CONTEXT_NOT_ACTIVATED);
            p(E_MBN_DATA_CLASS_NOT_AVAILABLE);
            p(E_MBN_DEFAULT_PROFILE_EXIST);
            p(E_MBN_FAILURE);
            p(E_MBN_INVALID_ACCESS_STRING);
            p(E_MBN_INVALID_CACHE);
            p(E_MBN_INVALID_PROFILE);
            p(E_MBN_MAX_ACTIVATED_CONTEXTS);
            p(E_MBN_NOT_REGISTERED);
            p(E_MBN_PACKET_SVC_DETACHED);
            p(E_MBN_PIN_DISABLED);
            p(E_MBN_PIN_NOT_SUPPORTED);
            p(E_MBN_PIN_REQUIRED);
            p(E_MBN_PROVIDERS_NOT_FOUND);
            p(E_MBN_PROVIDER_NOT_VISIBLE);
            p(E_MBN_RADIO_POWER_OFF);
            p(E_MBN_SERVICE_NOT_ACTIVATED);
            p(E_MBN_SIM_NOT_INSERTED);
            p(E_MBN_SMS_ENCODING_NOT_SUPPORTED);
            p(E_MBN_SMS_FILTER_NOT_SUPPORTED);
            p(E_MBN_SMS_FORMAT_NOT_SUPPORTED);
            p(E_MBN_SMS_INVALID_MEMORY_INDEX);
            p(E_MBN_SMS_LANG_NOT_SUPPORTED);
            p(E_MBN_SMS_MEMORY_FAILURE);
            p(E_MBN_SMS_MEMORY_FULL);
            p(E_MBN_SMS_NETWORK_TIMEOUT);
            p(E_MBN_SMS_OPERATION_NOT_ALLOWED);
            p(E_MBN_SMS_UNKNOWN_SMSC_ADDRESS);
            p(E_MBN_VOICE_CALL_IN_PROGRESS);
            p(E_MONITOR_RESOLUTION_TOO_LOW);
            p(E_MULTIPLE_EXTENSIONS_FOR_APPLICATION);
            p(E_MULTIPLE_PACKAGES_FOR_FAMILY);
            p(E_NOINTERFACE);
            p(E_NOTIMPL);
            p(E_NOT_SET);
            p(E_NOT_SUFFICIENT_BUFFER);
            p(E_NOT_VALID_STATE);
            p(E_OUTOFMEMORY);
            p(E_PENDING);
            p(E_POINTER);
            p(E_PROTOCOL_EXTENSIONS_NOT_SUPPORTED);
            p(E_PROTOCOL_VERSION_NOT_SUPPORTED);
            p(E_SKYDRIVE_FILE_NOT_UPLOADED);
            p(E_SKYDRIVE_ROOT_TARGET_CANNOT_INDEX);
            p(E_SKYDRIVE_ROOT_TARGET_FILE_SYSTEM_NOT_SUPPORTED);
            p(E_SKYDRIVE_ROOT_TARGET_OVERLAP);
            p(E_SKYDRIVE_ROOT_TARGET_VOLUME_ROOT_NOT_SUPPORTED);
            p(E_SKYDRIVE_UPDATE_AVAILABILITY_FAIL);
            p(E_STRING_NOT_NULL_TERMINATED);
            p(E_SUBPROTOCOL_NOT_SUPPORTED);
            p(E_SYNCENGINE_CLIENT_UPDATE_NEEDED);
            p(E_SYNCENGINE_FILE_IDENTIFIER_UNKNOWN);
            p(E_SYNCENGINE_FILE_SIZE_EXCEEDS_REMAINING_QUOTA);
            p(E_SYNCENGINE_FILE_SIZE_OVER_LIMIT);
            p(E_SYNCENGINE_FILE_SYNC_PARTNER_ERROR);
            p(E_SYNCENGINE_FOLDER_INACCESSIBLE);
            p(E_SYNCENGINE_FOLDER_IN_REDIRECTION);
            p(E_SYNCENGINE_FOLDER_ITEM_COUNT_LIMIT_EXCEEDED);
            p(E_SYNCENGINE_PATH_LENGTH_LIMIT_EXCEEDED);
            p(E_SYNCENGINE_PROXY_AUTHENTICATION_REQUIRED);
            p(E_SYNCENGINE_REMOTE_PATH_LENGTH_LIMIT_EXCEEDED);
            p(E_SYNCENGINE_REQUEST_BLOCKED_BY_SERVICE);
            p(E_SYNCENGINE_REQUEST_BLOCKED_DUE_TO_CLIENT_ERROR);
            p(E_SYNCENGINE_SERVICE_AUTHENTICATION_FAILED);
            p(E_SYNCENGINE_SERVICE_RETURNED_UNEXPECTED_SIZE);
            p(E_SYNCENGINE_STORAGE_SERVICE_BLOCKED);
            p(E_SYNCENGINE_STORAGE_SERVICE_PROVISIONING_FAILED);
            p(E_SYNCENGINE_SYNC_PAUSED_BY_SERVICE);
            p(E_SYNCENGINE_UNKNOWN_SERVICE_ERROR);
            p(E_SYNCENGINE_UNSUPPORTED_FILE_NAME);
            p(E_SYNCENGINE_UNSUPPORTED_FOLDER_NAME);
            p(E_SYNCENGINE_UNSUPPORTED_MARKET);
            p(E_SYNCENGINE_UNSUPPORTED_REPARSE_POINT);
            p(E_UAC_DISABLED);
            p(E_UNEXPECTED);
         default:
            TE_WARN("Unresolved");
            break;
         }
      }
#undef p
   private:
      template<typename T, typename... R>
      static void PrintText(T msg) {
         std::wcout << msg;
      }
      template<typename T, typename... R>
      static void PrintText(T msg, R ...args) {
         PrintText(msg);
         PrintText(args...);
      }
   };
}
#else // LEVEL 0
#define SetConsoleTitleA()
#define SetConsoleTitleW()
#define TE_PRINTLN()
#define TE_PRINT(x)
#define TE_SUCCESS(x)
#define TE_WARN(x)
#define TE_ERROR(x) {MessageBoxA(nullptr, "Expression: "#x "\nFile: " TEXTA(__FILE__) "\nLine: " TEXTA(__LINE__), "Error", MB_OK);exit(-1);}
#define TE_HANDLE_HRESULT(expr)  if (FAILED(expr))TE_ERROR(TEXTA(expr));
#define TE_RETRYIF(condition, msg)           \
      {bool retry;                        \
      do {                                \
         retry = false;                   \
         if (condition) {                 \
            if(MessageBoxA(nullptr, "Error", "Error", MB_RETRYCANCEL)!=2){system("PAUSE");}                 \
            retry = true;                 \
         }                                \
      } while (retry);}
#endif