#pragma once
#include "MyWinHeader.h"

#include <d3d11.h>
#include <d3d10.h>

#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"d3d10.lib")

class TriangleRenderer
{
public:
	TriangleRenderer(HWND handle);
	~TriangleRenderer();
	void RenderTriangles();
private:
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;

	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;


	HWND m_handle;

	void InitD3d();
	void SetViewport();
	void SetRenderTarget();
	void CreateBase3dObjects();
	void CreateShaders();
};

