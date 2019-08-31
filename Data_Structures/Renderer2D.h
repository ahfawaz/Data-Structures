#pragma once
#include <vector>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "UsefulMacros.h"

class Renderer2D
{
	ID2D1Factory* pFactory;

	struct tGraphicResources
	{
		ID2D1HwndRenderTarget* pRenderTarget;
		ID2D1SolidColorBrush* pBrush;
	};

	std::vector<tGraphicResources> arrGraphicResources;


public:
	Renderer2D();
	~Renderer2D();
	Renderer2D(Renderer2D& _cpy);
	Renderer2D& operator=(Renderer2D& _assign);

	HRESULT CreateD2DFactory();
	HRESULT InitializeGraphicResource(HWND _hWnd, int& _IDReturn);
	void Shutdown2DFactory();

	//If index == DISCARD_ALL or -1 
	//the function will clean the entire array.
	void DiscardGraphicResource(int _index = DISCARD_ALL);
	void Resize(HWND _hWnd, int _resourceID);
	void ChangeBrushColor(int _resourceID, D2D1_COLOR_F _color);
	void BeginDrawing(int _resourceID);
	HRESULT EndDrawing(int _resourceID);
	void ClearWindow(int _resourceID, D2D1_COLOR_F _color);
	D2D1_SIZE_F GetRenderTargetSize(int _resourceID);


	//Shape Drawing
	void DrawSquareFill(int _resourceID, D2D_VECTOR_2F _point, float _size);
	void DrawSquareFill(int _resourceID, D2D1_RECT_F _rectangle);
};

