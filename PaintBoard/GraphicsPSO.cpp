#include "pch.h"
#include "GraphicsPSO.h"
#include "D3DUtils.h"


UINT GraphicsPSO::m_stencilRef = 0;
GraphicsPSO::GraphicsPSO(const GraphicsPSO& other)
	: m_vs(other.m_vs)
	, m_ps(other.m_ps)
	, m_inputLayout(other.m_inputLayout)
	, m_rs(other.m_rs)
	, m_dss(other.m_dss)
{}
GraphicsPSO& GraphicsPSO::operator=(const GraphicsPSO& other)
{
	m_inputLayout = other.m_inputLayout;
	m_vs = other.m_vs;
	m_ps = other.m_ps;
	m_rs = other.m_rs;
	m_dss = other.m_dss;
	return *this;
}
void GraphicsPSO::SetState()
{
	auto& context = GETCONTEXT();
	context->IASetInputLayout(m_inputLayout.Get());

	context->VSSetShader(m_vs.Get(), nullptr, 0);

	context->RSSetState(m_rs.Get());

	context->PSSetShader(m_ps.Get(), nullptr, 0);

	context->OMSetDepthStencilState(m_dss.Get(), m_stencilRef);
}
