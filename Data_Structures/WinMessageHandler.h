#pragma once

#include "Framework.h"

namespace WinMessages
{
#define HAS_MENU FALSE
#define WINDOW_STYLE_VALUE WS_OVERLAPPEDWINDOW

	void OnSize(HWND, WPARAM, int, int);
	void UpdatePaintRegion(HWND, WPARAM, HDC&, PAINTSTRUCT&);
}