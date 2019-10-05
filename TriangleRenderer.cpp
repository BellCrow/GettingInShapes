#include "TriangleRenderer.h"
#include <exception>
#include "Vertex.h"
#include <sstream>;

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

	if (m_vertexShader != nullptr)
	{
		m_vertexShader->Release();
		m_vertexShader = nullptr;
	}

	if (m_pixelShader != nullptr)
	{
		m_pixelShader->Release();
		m_pixelShader = nullptr;
	}
}

void TriangleRenderer::RenderTriangleFrame()
{
	ClearRenderTarget();

	// do 3D rendering on the back buffer here
		
	Vertex vertices[] =
	{
		Vertex(-0.5f,	0.5f, 0.0f,
				0.0f, 0.5f, 0.0f, 1.0f),

		Vertex(0.0f,	1.0f, 0.0f,
				1.0f, 1.0f, 0.5f, 1.0f),

		Vertex(0.0f,	0.0f, 0.0f,
				0.5f, 1.0f, 1.0f, 1.0f),

		Vertex(0.5f,	0.5f, 0.0f,
				0.5f, 1.0f, 1.0f, 1.0f),
	};

	ID3D11Buffer* pVBuffer;    // global

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
	bd.ByteWidth = sizeof(vertices);             // size is the VERTEX struct * 3
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

	m_device->CreateBuffer(&bd, NULL, &pVBuffer);
	
	D3D11_MAPPED_SUBRESOURCE ms;
	m_context->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);  
	memcpy(ms.pData, vertices, sizeof(vertices) ); 
	m_context->Unmap(pVBuffer, NULL);
	
	
	ID3D11InputLayout* pLayout;    // global

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	m_device->CreateInputLayout(ied, 2,m_vertexShaderData->GetBufferPointer(),m_vertexShaderData->GetBufferSize(), &pLayout);
	m_context->IASetInputLayout(pLayout);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_context->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	// select which primtive type we are using
	m_context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// draw the vertex buffer to the back buffer
	m_context->Draw(4, 0);


	PresentFrame();
}

void TriangleRenderer::PresentFrame()
{
	// switch the back buffer and the front buffer
	m_swapChain->Present(0, 0);
}

void TriangleRenderer::ClearRenderTarget()
{
	// clear the back buffer to a deep blue
	float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
	m_context->ClearRenderTargetView(m_renderTargetView, color);
}

void TriangleRenderer::InitD3d()
{
	CreateBase3dObjects();

	SetRenderTarget();

	SetViewport();

	InitShaders();

	
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

void TriangleRenderer::InitShaders()
{
	// load and compile the two shaders
	auto result = D3DCompileFromFile(L"Shaders.hlsl", 0, 0, "VShader", "vs_4_0", 0, 0, &m_vertexShaderData, nullptr);
	if (result != S_OK)
	{
		throw std::exception();
	}
	
	ID3DBlob* error = nullptr;
	result = D3DCompileFromFile(L"Shaders.hlsl", 0, 0, "PShader", "ps_4_0", 0, 0, &m_pixelShaderData, &error);
	if (result != S_OK)
	{
		auto ptr = error->GetBufferPointer();
		throw std::exception();
	}

	// encapsulate both shaders into shader objects
	m_device->CreateVertexShader(m_vertexShaderData->GetBufferPointer(), m_vertexShaderData->GetBufferSize(), NULL, &m_vertexShader);
	m_device->CreatePixelShader(m_pixelShaderData->GetBufferPointer(), m_pixelShaderData->GetBufferSize(), NULL, &m_pixelShader);

	// set the shader objects
	m_context->VSSetShader(m_vertexShader, 0, 0);
	m_context->PSSetShader(m_pixelShader, 0, 0);
}
