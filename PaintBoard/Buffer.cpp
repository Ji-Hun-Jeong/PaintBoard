#include "pch.h"
#include "Buffer.h"
#include "D3DUtils.h"

Buffer::Buffer()
	: m_bindFlag(D3D11_BIND_VERTEX_BUFFER)
{
}

void Buffer::Initialize(void* pData, UINT numOfElement, UINT elementSize)
{
	auto& d3d = D3DUtils::GetInst();
	d3d.CreateStagingBuffer(pData, numOfElement, elementSize, m_stagingBuffer);
	d3d.CreateBuffer(numOfElement, elementSize, m_bindFlag, m_mainBuffer);
	d3d.UpdateBuffer(pData, numOfElement, elementSize, m_mainBuffer, m_stagingBuffer);
}

void Buffer::Update(void* pData, UINT numOfElement, UINT elementSize)
{
	D3DUtils::GetInst().UpdateBuffer(pData, numOfElement, elementSize
		, m_mainBuffer, m_stagingBuffer);
}
