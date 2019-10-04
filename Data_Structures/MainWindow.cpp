#include "WinMain_stdfx.h"
#include "MainWindow.h"
#include "Renderer2D.h"


MainWindow::MainWindow() : pMainRender(NULL)
{
}

MainWindow::~MainWindow()
{
}

MainWindow::MainWindow(MainWindow& _cpy)
{
	//This is done to limit the trilogy of evil to one point of failure.
	*this = _cpy;
}

MainWindow& MainWindow::operator=(MainWindow& _assign)
{
	if (this != &_assign)
	{
	}
	return *this;
}

LRESULT MainWindow::HandleMessage(UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uMsg)
	{
	case WM_CREATE:
	{
		pMainRender = DBG_NEW Renderer2D();
		if (FAILED(pMainRender->CreateD2DFactory()))
		{
			SafeDelete(pMainRender);
			return -1;
		}
		return 0;
	}
	case WM_DESTROY:
		SafeDelete(pMainRender);
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		OnPaint();
		return 0;
	}
	case WM_SIZE:
	{
		pMainRender->Resize(this->m_hWnd, this->GetRenderResourceID());
	}
	default:
		return DefWindowProc(this->m_hWnd, _uMsg, _wParam, _lParam);
	}
	return TRUE;
}

HRESULT	MainWindow::InitializeCOMLib()
{
	return CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
}

void MainWindow::OnPaint()
{
	PAINTSTRUCT ps;
	HRESULT hr = S_OK;

	//Get this Windows RenderResourceID
	int resource_id = GetRenderResourceID();
	//Validate: if NO_ID then create the resources needed.
	if (resource_id == NO_ID)
	{
		if (SUCCEEDED(pMainRender->InitializeGraphicResource(this->m_hWnd, resource_id)))
		{
			SetRenderResourceID(resource_id);
		}
	}

	HDC hdc = BeginPaint(this->m_hWnd, &ps);

	if(resource_id != NO_ID)
	{
		//Do all D2D renders here.
		pMainRender->BeginDrawing(resource_id);

		pMainRender->ClearWindow(resource_id, CLEAR_COLOR);
		
		D2D_VECTOR_2F center = RENDER_TARGET_CENTER(pMainRender->GetRenderTargetSize(resource_id));
		pMainRender->DrawSquareFill(resource_id, center, DEFAULT_RECT_DRAW_SIZE);


		hr = pMainRender->EndDrawing(resource_id);
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			pMainRender->DiscardGraphicResource(resource_id);
		}
	}

	EndPaint(this->m_hWnd, &ps);
}
