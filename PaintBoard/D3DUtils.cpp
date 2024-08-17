#include "pch.h"
#include "D3DUtils.h"

void D3DUtils::CreateVertexShaderAndInputLayout(const wstring& vsPrefixPath, ComPtr<ID3D11VertexShader>& vs
	, const vector<D3D11_INPUT_ELEMENT_DESC>& desc
	, ComPtr<ID3D11InputLayout>& inputLayout)
{
	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif
	wstring fileName = vsPrefixPath + L"VertexShader.hlsl";

	ComPtr<ID3DBlob> shaderBlob;
	ComPtr<ID3DBlob> errorBlob;

	CHECKRESULT(D3DCompileFromFile(fileName.c_str(), nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "vs_5_0",
		flags, 0, shaderBlob.GetAddressOf(), errorBlob.GetAddressOf()));

	CHECKRESULT(m_device->CreateVertexShader(shaderBlob->GetBufferPointer()
		, shaderBlob->GetBufferSize(), nullptr, vs.GetAddressOf()));

	CHECKRESULT(m_device->CreateInputLayout(desc.data(), UINT(desc.size()), shaderBlob->GetBufferPointer()
		, shaderBlob->GetBufferSize(), inputLayout.GetAddressOf()));
}

void D3DUtils::CreatePixelShader(const wstring& psPrefixPath, ComPtr<ID3D11PixelShader>& ps)
{
	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif
	wstring fileName = psPrefixPath + L"PixelShader.hlsl";

	ComPtr<ID3DBlob> shaderBlob;
	ComPtr<ID3DBlob> errorBlob;

	CHECKRESULT(D3DCompileFromFile(fileName.c_str(), nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "ps_5_0",
		flags, 0, shaderBlob.GetAddressOf(), errorBlob.GetAddressOf()));

	CHECKRESULT(m_device->CreatePixelShader(shaderBlob->GetBufferPointer()
		, shaderBlob->GetBufferSize(), nullptr, ps.GetAddressOf()));
}
void D3DUtils::CreateBuffer(UINT numOfElement, UINT elementSize, D3D11_BIND_FLAG bindFlag
	, ComPtr<ID3D11Buffer>& buffer)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = numOfElement * elementSize;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = bindFlag;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = elementSize;

	CHECKRESULT(m_device->CreateBuffer(&desc, nullptr, buffer.GetAddressOf()));
}
void D3DUtils::CreateStagingBuffer(void* initData, UINT numOfElement, UINT elementSize
	, ComPtr<ID3D11Buffer>& stagingBuffer)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = numOfElement * elementSize;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	desc.MiscFlags = 0;
	desc.StructureByteStride = elementSize;

	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = initData;

	CHECKRESULT(m_device->CreateBuffer(&desc, &sd, stagingBuffer.GetAddressOf()));
}
void D3DUtils::UpdateBuffer(void* pData, UINT numOfElement, UINT elementSize
	, ComPtr<ID3D11Buffer>& buffer, ComPtr<ID3D11Buffer>& stagingBuffer)
{
	D3D11_MAPPED_SUBRESOURCE ms;
	m_context->Map(stagingBuffer.Get(), 0, D3D11_MAP_WRITE, 0, &ms);
	size_t byteWidth = static_cast<size_t>(numOfElement * elementSize);
	memcpy(ms.pData, pData, byteWidth);
	m_context->Unmap(stagingBuffer.Get(), 0);

	m_context->CopyResource(buffer.Get(), stagingBuffer.Get());
}
void D3DUtils::CreateVertexBuffer(UINT numOfElement, UINT elementSize, ComPtr<ID3D11Buffer>& buffer)
{
	CreateBuffer(numOfElement, elementSize, D3D11_BIND_VERTEX_BUFFER, buffer);
}
void D3DUtils::CreateIndexBuffer(UINT numOfElement, UINT elementSize, ComPtr<ID3D11Buffer>& buffer)
{
	CreateBuffer(numOfElement, elementSize, D3D11_BIND_INDEX_BUFFER, buffer);
}
void D3DUtils::Initialize(HWND hWnd, UINT screenWidth, UINT screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE;
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_0 ,D3D_FEATURE_LEVEL_9_3 };
	D3D_FEATURE_LEVEL outputLevel;

	CHECKRESULT(D3D11CreateDevice(nullptr, driverType, 0, createDeviceFlags, featureLevel,
		ARRAYSIZE(featureLevel), D3D11_SDK_VERSION, m_device.GetAddressOf(),
		&outputLevel, m_context.GetAddressOf()));

	CHECKRESULT(m_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM,
		4, &m_msaaLevel));

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferDesc.Width = m_screenWidth;
	swapChainDesc.BufferDesc.Height = m_screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	if (m_msaaLevel > 0)
	{
		swapChainDesc.SampleDesc.Count = 4;
		swapChainDesc.SampleDesc.Quality = m_msaaLevel - 1;
	}
	else
	{
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
	}


	CHECKRESULT(D3D11CreateDeviceAndSwapChain(nullptr, driverType, 0
		, createDeviceFlags, featureLevel, 1
		, D3D11_SDK_VERSION, &swapChainDesc
		, m_swapChain.GetAddressOf(), m_device.GetAddressOf()
		, &outputLevel, m_context.GetAddressOf()));
}

D3DUtils& D3DUtils::GetInst()
{
	static D3DUtils singleInstance;
	return singleInstance;
}
