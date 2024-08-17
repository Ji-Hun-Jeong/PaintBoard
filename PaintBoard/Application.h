#pragma once
#include "ViewSpace.h"

class Application
{
public:
	Application() = default;
	Application(const Application&) = delete;
	Application(Application&&) = delete;
	~Application() = default;

public:
	void Initialize(HWND hWnd, UINT screenWidth, UINT screenHeight);
	void Run();
	void Update();
	void Render();

private:
	ViewSpace m_viewSpace;

	UINT m_screenWidth = 0;
	UINT m_screenHeight = 0;
	HWND m_hWnd = nullptr;

	D3D11_VIEWPORT m_viewPort = {};

	ComPtr<ID3D11Texture2D> m_backBuffer;
	ComPtr<ID3D11RenderTargetView> m_backBufferRTV;

	ComPtr<ID3D11Texture2D> m_depthBuffer;
	ComPtr<ID3D11DepthStencilView> m_dsv;
};

