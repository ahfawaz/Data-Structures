#pragma once
#include "BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:

	PCWSTR ClassName() const { return L"Data Structure Class"; }
	LRESULT HandleMessage(UINT _uMsg, WPARAM _wParam, LPARAM _lParam);
};

