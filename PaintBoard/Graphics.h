#pragma once
#include "GraphicsPSO.h"
namespace Graphics
{
	extern ComPtr<ID3D11InputLayout> g_basicInputLayout;

	extern ComPtr<ID3D11VertexShader> g_basicVS;

	extern ComPtr<ID3D11PixelShader> g_basicPS;

	extern ComPtr<ID3D11RasterizerState> g_solidCWRS;

	extern ComPtr<ID3D11DepthStencilState> g_basicDSS;

	extern GraphicsPSO g_basicSolidPSO;

	void InitCommons();
	void InitShader();
	void InitRasterizerState(ComPtr<ID3D11Device>& device);
	void InitDepthStencilState(ComPtr<ID3D11Device>& device);
	void InitPSO();
}