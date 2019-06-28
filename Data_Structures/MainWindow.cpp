#include "WinMain_stdfx.h"
#include "MainWindow.h"

LRESULT MainWindow::HandleMessage(UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(this->m_hWnd, &ps);



		EndPaint(this->m_hWnd, &ps);
	}
	return 0;
	case WM_SIZE:
	{
		int width = LOWORD(_lParam);
		int height = HIWORD(_lParam);

		OnSize(this->m_hWnd, (UINT)_wParam, width, height);
	}
	default:
		return DefWindowProc(this->m_hWnd, _uMsg, _wParam, _lParam);
	}
	return TRUE;
}
