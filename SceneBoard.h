#pragma once

#include "MyWinHeader.h"
#include "Point.h"
#include "Vertex.h"
#include "AbstractShape.h"
#include "Camera.h"

#include <d3d11.h>
#include <d3d10.h>
#include <d3dcompiler.h>
#include <vector>
#include "AbstractAnimation.h"

#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"d3d10.lib")
#pragma comment (lib,"D3DCompiler.lib")

class SceneBoard
{
	std::vector<AbstractShape*> m_shapes;
	std::vector<AbstractAnimation*> m_animations;
	
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;

	ID3D11RenderTargetView* m_renderTargetView;

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D10Blob* m_vertexShaderData;
	ID3D10Blob* m_pixelShaderData;
	
	HWND m_handle;

	Point m_pos;
	float m_height;
	float m_width;

private:
	void InitD3d();
	void SetViewport();
	void SetRenderTarget();
	void CreateBase3dObjects();
	void InitShaders();
	void ClearRenderTarget();
	void SetViewProjectionMatrix(Camera* camera);
	void SetVertexShaderConstantBuffer(int slot, DirectX::XMMATRIX matrix);	
	void RenderShape(AbstractShape* shape);
public:
	SceneBoard(HWND windowHandle);
	void Tick();
	void Render(Camera* camera);
	void AddShape(AbstractShape* shape);
	void AddAnimation(AbstractAnimation* animation);

};

