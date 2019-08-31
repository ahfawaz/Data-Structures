#pragma once
#include "BaseWindow.h"

class Renderer2D;

class MainWindow : public BaseWindow<MainWindow>
{
	Renderer2D* pMainRender;

public:
	MainWindow();
	~MainWindow();
	MainWindow(MainWindow& _cpy);
	MainWindow& operator=(MainWindow& _assign);

	PCWSTR ClassName() const { return L"Data Structure and Algorithm Visualizer"; }
	LRESULT HandleMessage(UINT _uMsg, WPARAM _wParam, LPARAM _lParam);
	HRESULT	InitializeCOMLib();

	void OnPaint();
};

