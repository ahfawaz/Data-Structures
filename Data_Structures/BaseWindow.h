#pragma once
#include "Framework.h"

template <class DERIVED_TYPE>
class BaseWindow
{
	int RenderResourceID;

public:
	static LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
	{
		DERIVED_TYPE* pThis = NULL;

		if (_uMsg == WM_CREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)_lParam;
			pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
			SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
		}
		else
		{
			pThis = (DERIVED_TYPE*)GetWindowLong(_hWnd, GWLP_USERDATA);
		}

		if (pThis)
		{
			return pThis->HandleMessage(_uMsg, _wParam, _lParam);
		}
		else
		{
			return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
		}
	}

	BaseWindow() : m_hWnd(NULL), RenderResourceID(NO_ID) {}

	BOOL Create(
		PCWSTR	_lpWindowName,
		DWORD	_dwStryle,
		DWORD	_dwExStyle = 0,
		int		_x = CW_USEDEFAULT,
		int		_y = CW_USEDEFAULT,
		int		_nWidth = CW_USEDEFAULT,
		int		_nHeight = CW_USEDEFAULT,
		HWND	_hWndParent = 0,
		HMENU	_hMenu = 0
		)
	{
		WNDCLASS wc;
		ZeroMemory(&wc, sizeof(wc));

		wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = ClassName();

		RegisterClass(&wc);

		m_hWnd = CreateWindowEx(_dwExStyle, ClassName(), _lpWindowName, _dwStryle, _x, _y,
			_nWidth, _nHeight, _hWndParent, _hMenu, GetModuleHandle(NULL), this);

		return (m_hWnd ? TRUE : FALSE);
	}

	HWND Window() const { return m_hWnd; }

protected:

	virtual PCWSTR ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT _uMsg, WPARAM _wParam, LPARAM _lParam) = 0;
	virtual HRESULT	InitializeCOMLib() = 0;
	int GetRenderResourceID() { return RenderResourceID; };
	void SetRenderResourceID(int _ID) { RenderResourceID = _ID; }

	HWND m_hWnd;
};