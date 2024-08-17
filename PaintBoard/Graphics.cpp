#include "pch.h"
#include "Graphics.h"
#include "D3DUtils.h"
#include "ResourceMgr.h"
namespace Graphics
{
	ComPtr<ID3D11InputLayout>		g_basicInputLayout;

	ComPtr<ID3D11VertexShader>		g_basicVS;

	ComPtr<ID3D11PixelShader>		g_basicPS;

	ComPtr<ID3D11RasterizerState>	g_solidCWRS;

	ComPtr<ID3D11DepthStencilState> g_basicDSS;

	GraphicsPSO						g_basicSolidPSO;

	void InitCommons()
	{
		ComPtr<ID3D11Device>& device = GETDEVICE();
		InitShader();
		InitRasterizerState(device);
		InitDepthStencilState(device);
		InitPSO();
	}

	void InitShader()
	{
		vector<D3D11_INPUT_ELEMENT_DESC> desc =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA , 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA , 0},
		};

		D3DUtils::GetInst().CreateVertexShaderAndInputLayout(
			L"Basic", g_basicVS, desc, g_basicInputLayout);

		D3DUtils::GetInst().CreatePixelShader(
			L"Basic", g_basicPS);
	}

	void InitRasterizerState(ComPtr<ID3D11Device>& device)
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_NONE;
		desc.FrontCounterClockwise = false;
		desc.DepthClipEnable = true;
		desc.MultisampleEnable = true;

		CHECKRESULT(device->CreateRasterizerState(&desc, g_solidCWRS.GetAddressOf()));
	}

	void InitDepthStencilState(ComPtr<ID3D11Device>& device)
	{
		D3D11_DEPTH_STENCIL_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.DepthEnable = true;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthFunc = D3D11_COMPARISON_LESS;
		desc.StencilEnable = false;
		desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

		desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		CHECKRESULT(device->CreateDepthStencilState(&desc, g_basicDSS.GetAddressOf()));
	}
	void InitPSO()
	{
		g_basicSolidPSO.SetInputLayout(g_basicInputLayout);
		g_basicSolidPSO.SetVS(g_basicVS);
		g_basicSolidPSO.SetPS(g_basicPS);
		g_basicSolidPSO.SetRS(g_solidCWRS);
		g_basicSolidPSO.SetDSS(g_basicDSS);
	}
}