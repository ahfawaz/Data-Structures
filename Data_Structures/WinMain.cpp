#ifndef UNICODE
#define UNICODE
#endif 

#include "WinMain_stdfx.h"
#include "WinMessageHelpers.h"
#include "BaseWindow.h"
#include "MainWindow.h"

#define MAIN_WINDOW window0

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow MAIN_WINDOW;

	if (!MAIN_WINDOW.Create(L"Building Structures...Data Structures", WS_OVERLAPPEDWINDOW))
	{
		return 0;
	}


	ShowWindow(MAIN_WINDOW.Window(), nCmdShow);
	UpdateWindow(MAIN_WINDOW.Window());

	// Run the message loop.

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


