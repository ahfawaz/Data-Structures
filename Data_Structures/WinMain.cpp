#ifndef UNICODE
#define UNICODE
#endif 

#include "WinMain_stdfx.h"
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

#ifdef MEM_LEAK_DECTECTION
	_CrtDumpMemoryLeaks();
#endif // MEM_LEAK_DECTECTION


	return 0;
}


