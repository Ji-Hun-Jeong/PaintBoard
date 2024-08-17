#include "pch.h"
#include "Shape.h"
#include "D3DUtils.h"
#include "Buffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

Shape::Shape()
	: m_stride(sizeof(Vertex))
	, m_offset(0)
	, m_topology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST)
	, m_completeProcessCpuData(false)
{

}

Shape::Shape(const Shape& other)
	: m_vecVertices(other.m_vecVertices)
	, m_vecIndices(other.m_vecIndices)
	, m_stride(other.m_stride)
	, m_offset(other.m_offset)
	, m_topology(other.m_topology)
	, m_completeProcessCpuData(other.m_completeProcessCpuData)
{

}

void Shape::Initialize(const ShapeData& initData)
{
	m_vecVertices = initData.vertices;
	m_vecIndices = initData.indices;

	m_vertexBuffer = make_shared<VertexBuffer>();
	m_indexBuffer = make_shared<IndexBuffer>();
	
	m_vertexBuffer->Initialize(m_vecVertices.data(), UINT(m_vecVertices.size()),
		sizeof(Vertex));
	m_indexBuffer->Initialize(m_vecIndices.data(), UINT(m_vecIndices.size())
		, sizeof(uint32_t));
}

void Shape::Update()
{
}

void Shape::Render()
{
	auto& context = GETCONTEXT();
	context->IASetVertexBuffers(0, 1, m_vertexBuffer->GetBufferAddress(), &m_stride, &m_offset);
	context->IASetIndexBuffer(m_indexBuffer->GetBuffer(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(m_topology);

	UINT indexCount = static_cast<UINT>(m_vecIndices.size());
	context->DrawIndexed(indexCount, 0, 0);
}

