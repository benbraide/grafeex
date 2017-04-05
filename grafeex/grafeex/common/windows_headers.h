#pragma once

#ifndef GRAFEEX_WINDOWS_HEADERS_H
#define GRAFEEX_WINDOWS_HEADERS_H

#define NOMINMAX

#include <windows.h>
#include <windowsx.h>

#include <wingdi.h>
#include <commctrl.h>

#include <mmreg.h>
#include <wmsdk.h>

#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "comctl32.lib")

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "wmvcore.lib")

#ifdef max
#undef max
#endif // max

#ifdef min
#undef min
#endif // min


#endif /* !GRAFEEX_WINDOWS_HEADERS_H */
