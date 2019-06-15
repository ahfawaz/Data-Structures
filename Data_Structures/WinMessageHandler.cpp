#include "WinMessageHandler.h"
#include "WinMain_stdfx.h"

namespace WinMessages
{
	void OnSize(HWND _hwnd, WPARAM _wParam, int _width, int _height)
	{
		RECT current_rect = {};
		RECT resized_rect = {};
		GetWindowRect(_hwnd, &current_rect);

		LONG width = current_rect.right - current_rect.left;
		LONG height = current_rect.bottom - current_rect.top;
		resized_rect = {
			current_rect.left,
			current_rect.top,
			current_rect.right + (_width - width),
			current_rect.bottom + (_height - height)
		};

		AdjustWindowRect(&resized_rect, WINDOW_STYLE_VALUE, HAS_MENU);
	}

	void UpdatePaintRegion(HWND _hwnd, WPARAM _wParam, HDC &_hdc, PAINTSTRUCT &_ps)
	{
		//TODO: Add paint calls here.
	}

}