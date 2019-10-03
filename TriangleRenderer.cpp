#include "TriangleRenderer.h"
#include <exception>
#include <d3dcompiler.h>

TriangleRenderer::TriangleRenderer(HWND handle)
{
	m_handle = handle;
	InitD3d();
}

TriangleRenderer::~TriangleRenderer()
{
	if (m_context != nullptr)
	{
		m_context->Release();
		m_context = nullptr;
	}

	if (m_device != nullptr)
	{
		m_device->Release();
		m_device = nullptr;
	}

	if (m_swapChain != nullptr)
	{
		m_swapChain->Release();
		m_swapChain = nullptr;
	}

	if (m_renderTargetView != nullptr)
	{
		m_renderTargetView->Release();
		m_renderTargetView = nullptr;
	}
}

void TriangleRenderer::RenderTriangles()
{
	// this is the function used to render a single frame

	// clear the back buffer to a deep blue
	float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
	m_context->ClearRenderTargetView(m_renderTargetView, color);

	// do 3D rendering on the back buffer here
	
	// switch the back buffer and the front buffer
	m_swapChain->Present(0, 0);
}

void TriangleRenderer::InitD3d()
{
	CreateBase3dObjects();

	SetRenderTarget();

	SetViewport();

	CreateShaders();
}

void TriangleRenderer::SetViewport()
{
	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 600;

	m_context->RSSetViewports(1, &viewport);
}

void TriangleRenderer::SetRenderTarget()
{
	// get the address of the back buffer
	ID3D11Texture2D* backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	if (backBuffer == nullptr)
	{
		throw std::exception("Error retrieving backbuffer");
	}
	// use the back buffer address to create the render target
	m_device->CreateRenderTargetView(backBuffer, NULL, &m_renderTargetView);
	backBuffer->Release();

	// set the render target as the back buffer
	m_context->OMSetRenderTargets(1, &m_renderTargetView, NULL);
}

void TriangleRenderer::CreateBase3dObjects()
{
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDescription;

	// clear out the struct for use
	ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	swapChainDescription.BufferCount = 1;                                    // one back buffer
	swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	swapChainDescription.OutputWindow = m_handle;                            // the window to be used
	swapChainDescription.SampleDesc.Count = 4;                               // how many multisamples
	swapChainDescription.Windowed = TRUE;                                    // windowed/full-screen mode

	// create a device, device context and swap chain using the information in the swapChainDescription struct
	auto result = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainDescription,
		&m_swapChain,
		&m_device,
		nullptr,
		&m_context);

	if (result != S_OK)
	{
		throw std::exception("Failed to initialize d3d objects");
	}
}

void TriangleRenderer::CreateShaders()
{
	// load and compile the two shaders
	ID3D10Blob* VS, * PS;
	
	D3DCompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, &VS, nullptr);
	D3DCompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, &PS, nullptr);

	// encapsulate both shaders into shader objects
	m_device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_vertexShader);
	m_device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pixelShader);
	
}
