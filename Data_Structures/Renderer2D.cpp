#include "WinMain_stdfx.h"
#include "Renderer2D.h"
#include "Framework.h"

Renderer2D::Renderer2D() : pFactory(NULL)
{
}

Renderer2D::~Renderer2D()
{
	DiscardGraphicResource();
	Shutdown2DFactory();
}

Renderer2D::Renderer2D(Renderer2D& _cpy)
{
	*this = _cpy;
}

Renderer2D& Renderer2D::operator=(Renderer2D& _assign)
{
	if (this != &_assign)
	{
		Shutdown2DFactory();
		this->pFactory = _assign.pFactory;
		DiscardGraphicResource();
		this->arrGraphicResources = _assign.arrGraphicResources;
	}
	return *this;
}

HRESULT Renderer2D::CreateD2DFactory()
{
	return D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
}

HRESULT Renderer2D::InitializeGraphicResource(HWND _hWnd, int& _IDReturn)
{
	static int resource_size = 0;
	HRESULT hr = S_OK;
	tGraphicResources new_resource;


	//Create RenderTarget
	RECT rc;
	GetClientRect(_hWnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

	hr = pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(_hWnd, size),
		&new_resource.pRenderTarget);

	//Make sure the RenderTarget was created correctly
	if (FAILED(hr))
	{
		return hr;
	}

	//Create the Brush
	const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0.0f);
	hr = new_resource.pRenderTarget->CreateSolidColorBrush(color, &new_resource.pBrush);

	//Make sure the Brush was created correctly
	if (FAILED(hr))
	{
		return hr;
	}


	arrGraphicResources.push_back(new_resource);
	_IDReturn = resource_size++;
	return hr;
}

void Renderer2D::Shutdown2DFactory()
{
	SafeRelease(pFactory);
}

//If index == DISCARD_ALL or -1 
//the function will clean the entire array.
void Renderer2D::DiscardGraphicResource(int _index)
{
	if (_index == DISCARD_ALL)
	{
		for (size_t i = 0; i < this->arrGraphicResources.size(); i++)
		{
			SafeRelease(arrGraphicResources[i].pBrush);
			SafeRelease(arrGraphicResources[i].pRenderTarget);
		}

		this->arrGraphicResources.clear();
	}
	else
	{
		auto itr_resource = arrGraphicResources.begin() + _index;
		this->arrGraphicResources.erase(itr_resource);
	}
}

void Renderer2D::Resize(HWND _hWnd, int _resourceID)
{
	if (_resourceID != NO_ID)
	{
		RECT rc;
		GetClientRect(_hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		arrGraphicResources[_resourceID].pRenderTarget->Resize(size);
		InvalidateRect(_hWnd, NULL, FALSE);
	}
}

void Renderer2D::ChangeBrushColor(int _resourceID, D2D1_COLOR_F _color)
{
	if (_resourceID != NO_ID)
	{
		arrGraphicResources[_resourceID].pBrush->SetColor(_color);
	}
}

void Renderer2D::BeginDrawing(int _resourceID)
{
	if (_resourceID != NO_ID)
	{
		arrGraphicResources[_resourceID].pRenderTarget->BeginDraw();
	}
}

HRESULT Renderer2D::EndDrawing(int _resourceID)
{
	if (_resourceID != NO_ID)
	{
		return arrGraphicResources[_resourceID].pRenderTarget->EndDraw();
	}
	return D2DERR_INVALID_TARGET;
}

void Renderer2D::ClearWindow(int _resourceID, D2D1_COLOR_F _color)
{
	if (_resourceID != NO_ID)
	{
		arrGraphicResources[_resourceID].pRenderTarget->Clear(_color);
	}
}

D2D1_SIZE_F Renderer2D::GetRenderTargetSize(int _resourceID)
{
	D2D1_SIZE_F size_return = INVALID_SIZE_F;
	if (_resourceID != NO_ID)
	{
		size_return = arrGraphicResources[_resourceID].pRenderTarget->GetSize();
	}
	return size_return;
}

void Renderer2D::DrawSquareFill(int _resourceID, D2D_VECTOR_2F _point, float _size)
{
	if (_resourceID != NO_ID)
	{
		ID2D1RenderTarget* render_target = arrGraphicResources[_resourceID].pRenderTarget;
		ID2D1Brush* brush = arrGraphicResources[_resourceID].pBrush;

		D2D_RECT_F rectangle_pass;
		float half_size = _size / 2.0f;

		rectangle_pass.left = _point.x - half_size;
		rectangle_pass.top = _point.y - half_size;
		rectangle_pass.right = _point.x + half_size;
		rectangle_pass.bottom = _point.y + half_size;

		render_target->FillRectangle(rectangle_pass, brush);
	}

}

void Renderer2D::DrawSquareFill(int _resourceID, D2D1_RECT_F _rectangle)
{
	if (_resourceID != NO_ID)
	{
		arrGraphicResources[_resourceID].pRenderTarget->FillRectangle(_rectangle, arrGraphicResources[_resourceID].pBrush);
	}
}
