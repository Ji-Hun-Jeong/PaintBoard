#include "pch.h"
#include "Application.h"
#include "D3DUtils.h"
#include "Graphics.h"
#include "GraphicsPSO.h"


void Application::Initialize(HWND hWnd, UINT screenWidth, UINT screenHeight)
{
	m_hWnd = hWnd;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	D3DUtils::GetInst().Initialize(m_hWnd, m_screenWidth, m_screenHeight);

	Graphics::InitCommons();

	m_viewPort.TopLeftX = 0.0f;
	m_viewPort.TopLeftY = 0.0f;
	m_viewPort.Width = static_cast<float>(m_screenWidth);
	m_viewPort.Height = static_cast<float>(m_screenHeight);
	m_viewPort.MinDepth = 0.0f;
	m_viewPort.MaxDepth = 1.0f;

	auto& swapChain = D3DUtils::GetInst().GetSwapChain();
	auto& device = GETDEVICE();
	CHECKRESULT(swapChain->GetBuffer(0, IID_PPV_ARGS(m_backBuffer.GetAddressOf())));

	CHECKRESULT(device->CreateRenderTargetView(m_backBuffer.Get(), nullptr, m_backBufferRTV.GetAddressOf()));

	UINT msaaLevel = D3DUtils::GetInst().GetMSAALevel();
	D3D11_TEXTURE2D_DESC depthDesc;
	depthDesc.Width = m_screenWidth;
	depthDesc.Height = m_screenHeight;
	depthDesc.MipLevels = depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	if (msaaLevel > 0)
	{
		depthDesc.SampleDesc.Count = 4;
		depthDesc.SampleDesc.Quality = msaaLevel - 1;
	}
	else
	{
		depthDesc.SampleDesc.Count = 1;
		depthDesc.SampleDesc.Quality = 0;
	}
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;

	CHECKRESULT(device->CreateTexture2D(&depthDesc, nullptr, m_depthBuffer.GetAddressOf()));
	CHECKRESULT(device->CreateDepthStencilView(m_depthBuffer.Get(), nullptr, m_dsv.GetAddressOf()));
	
	m_viewSpace.Initialize();
}
void Application::Run()
{
	Update();
	Render();
}
void Application::Update()
{
	m_viewSpace.Update();
}
void Application::Render()
{
	auto& context = GETCONTEXT();
	float clearColor[4] = { 0.0f,0.0f,0.0f,1.0f };
	context->ClearRenderTargetView(m_backBufferRTV.Get(), clearColor);
	context->ClearDepthStencilView(m_dsv.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	context->OMSetRenderTargets(1, m_backBufferRTV.GetAddressOf(), m_dsv.Get());

	context->RSSetViewports(1, &m_viewPort);
	Graphics::g_basicSolidPSO.SetState();

	m_viewSpace.Render();

	auto& swapChain = D3DUtils::GetInst().GetSwapChain();
	swapChain->Present(1, 0);
}
