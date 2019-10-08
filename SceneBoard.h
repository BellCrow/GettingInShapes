#pragma once

#include "MyWinHeader.h"
#include "Point.h"
#include "Vertex.h"
#include "AbstractShape.h"

#include <d3d11.h>
#include <d3d10.h>
#include <d3dcompiler.h>
#include <vector>

#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"d3d10.lib")
#pragma comment (lib,"D3DCompiler.lib")

class SceneBoard
{
	std::vector<AbstractShape*> m_shapes;


	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;

	ID3D11RenderTargetView* m_renderTargetView;

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D10Blob* m_vertexShaderData;
	ID3D10Blob* m_pixelShaderData;
	
	HWND m_handle;

	void InitD3d();
	void SetViewport();
	void SetRenderTarget();
	void CreateBase3dObjects();
	void InitShaders();

	Point m_pos;
	float m_height;
	float m_width;


public:
	SceneBoard(HWND windowHandle);
	void Tick();
	void Render();
	void AddShape(AbstractShape* shape);
};

