#include "SceneBoard.h"
#include <memory>
#include <array>

SceneBoard::SceneBoard(HWND windowHandle) :m_handle(windowHandle)
{
	InitD3d();
}

void SceneBoard::Tick()
{
	for (auto animation : m_animations)
	{
		animation->Tick();
	}
}

void SceneBoard::SetViewProjectionMatrix(sp<Camera> camera)
{
	auto viewMatrix = camera->GetViewMatrix();
	SetVertexShaderConstantBuffer(1, viewMatrix);
	
	auto projMatrix = camera->GetProjectionMatrix();		
	SetVertexShaderConstantBuffer(2, projMatrix);
}

void SceneBoard::SetVertexShaderConstantBuffer(int slot, DirectX::XMMATRIX matrix)
{
	ID3D11Buffer* matrixBuffer = nullptr;
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(XMMATRIX);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (FAILED(m_device->CreateBuffer(&bd, nullptr, &matrixBuffer)) || matrixBuffer == nullptr)
	{
		throw std::exception("Could not create matrix buffer");
	}

	D3D11_MAPPED_SUBRESOURCE res = {};
	m_context->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res);
	memcpy(res.pData, &matrix, sizeof(XMMATRIX));
	m_context->Unmap(matrixBuffer, 0);

	ID3D11Buffer* const cBuffer = const_cast<ID3D11Buffer* const>(matrixBuffer);
	m_context->VSSetConstantBuffers(slot, 1, &cBuffer);
	cBuffer->Release();
}

void SceneBoard::RenderShape(sp<AbstractShape> shape)
{
	//set model matrix here
	auto modelMatrix = shape->GetModelmatrix();

	SetVertexShaderConstantBuffer(0, *modelMatrix);

	auto shapeColor = shape->GetColor();
	auto triangles = shape->GetTriangles();
	auto triangleCount = shape->GetTriangleCount();
	UINT vertexCount = triangleCount * 3;
	UINT vertexBufferByteCount = vertexCount * sizeof(Vertex);
	auto m_vertexBuffer = new Vertex[vertexCount];

	for (int i = 0; i < triangleCount; i++)
	{
		//POINT A
		m_vertexBuffer[i * 3].position.x = triangles[i].pointA.x;
		m_vertexBuffer[i * 3].position.y = triangles[i].pointA.y;
		m_vertexBuffer[i * 3].position.z = 1.0f;

		m_vertexBuffer[i * 3].color.x = shapeColor.R;
		m_vertexBuffer[i * 3].color.y = shapeColor.G;
		m_vertexBuffer[i * 3].color.z = shapeColor.B;
		m_vertexBuffer[i * 3].color.w = shapeColor.A;

		//POINT B
		m_vertexBuffer[i * 3 + 1].position.x = triangles[i].pointB.x;
		m_vertexBuffer[i * 3 + 1].position.y = triangles[i].pointB.y;
		m_vertexBuffer[i * 3 + 1].position.z = 1.0f;
		
		m_vertexBuffer[i * 3 + 1].color.x = shapeColor.R;
		m_vertexBuffer[i * 3 + 1].color.y = shapeColor.G;
		m_vertexBuffer[i * 3 + 1].color.z = shapeColor.B;
		m_vertexBuffer[i * 3 + 1].color.w = shapeColor.A;


		//POINT C
		m_vertexBuffer[i * 3 + 2].position.x = triangles[i].pointC.x;
		m_vertexBuffer[i * 3 + 2].position.y = triangles[i].pointC.y;
		m_vertexBuffer[i * 3 + 2].position.z = 1.0f;

		m_vertexBuffer[i * 3 + 2].color.x = shapeColor.R;
		m_vertexBuffer[i * 3 + 2].color.y = shapeColor.G;
		m_vertexBuffer[i * 3 + 2].color.z = shapeColor.B;
		m_vertexBuffer[i * 3 + 2].color.w = shapeColor.A;

	}

	ID3D11Buffer* pVBuffer;

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
	bd.ByteWidth = vertexBufferByteCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

	if (FAILED(m_device->CreateBuffer(&bd, NULL, &pVBuffer)) || pVBuffer == nullptr)
	{
		throw std::exception("Could not create vertex buffer");
	}

	D3D11_MAPPED_SUBRESOURCE ms;
	m_context->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	auto vertexPtr = m_vertexBuffer;
	memcpy(ms.pData, vertexPtr, vertexBufferByteCount);
	m_context->Unmap(pVBuffer, NULL);
	
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_context->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	// select which primtive type we are using
	m_context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw the vertex buffer to the back buffer
	m_context->Draw(vertexCount, 0);

	pVBuffer->Release();

	delete[] m_vertexBuffer;
}

void SceneBoard::Render(sp<Camera> camera)
{
	ClearRenderTarget();
	//set view/projection matrix here

	SetViewProjectionMatrix(camera);

	for (auto shape : m_shapes)
	{
		RenderShape(shape);
	}

	m_swapChain->Present(0, 0);
}

void SceneBoard::AddShape(sp<AbstractShape> shape)
{
	m_shapes.push_back(shape);
}

void SceneBoard::RemoveShape(sp<AbstractShape> shape)
{
	auto eraseIter = std::remove_if(m_shapes.begin(), m_shapes.end(), [&shape](sp<AbstractShape> iterShape)
		{
			auto result = shape == iterShape;
			return result;
		});
	m_shapes.erase(eraseIter);
}

void SceneBoard::AddAnimation(sp<AbstractAnimation> animation)
{
	m_animations.push_back(animation);
}


void SceneBoard::InitD3d()
{
	CreateBase3dObjects();

	SetRenderTarget();

	SetViewport();

	InitShaders();
}

void SceneBoard::SetViewport()
{
	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 1024;
	viewport.Height = 786;

	m_context->RSSetViewports(1, &viewport);
}

void SceneBoard::SetRenderTarget()
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

void SceneBoard::CreateBase3dObjects()
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
		D3D11_CREATE_DEVICE_DEBUG,
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

void SceneBoard::InitShaders()
{
	// load and compile the two shaders
	ID3DBlob* errorBlob = nullptr;
	auto result = D3DCompileFromFile(L"Shaders.hlsl", 0, 0, "VShader", "vs_4_0",D3DCOMPILE_DEBUG,0, &m_vertexShaderData, &errorBlob);
	if (result != S_OK)
	{
		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
		}

		throw std::exception();
	}

	ID3DBlob* error = nullptr;
	result = D3DCompileFromFile(L"Shaders.hlsl", 0, 0, "PShader", "ps_4_0", D3DCOMPILE_DEBUG, 0, &m_pixelShaderData, &error);
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


	ID3D11InputLayout* pLayout;    // global
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	m_device->CreateInputLayout(ied, 2, m_vertexShaderData->GetBufferPointer(), m_vertexShaderData->GetBufferSize(), &pLayout);
	m_context->IASetInputLayout(pLayout);
	pLayout->Release();

}

void SceneBoard::ClearRenderTarget()
{
	// clear the back buffer to a deep blue
	float color[4] = { 0.0f, 0.1f, 0.2f, 0.7f };
	m_context->ClearRenderTargetView(m_renderTargetView, color);
}
