#pragma once
#include "ViewSpace.h"
class VertexBuffer;
class IndexBuffer;
class Shape
{
public:
	Shape();
	Shape(const Shape& other);
	Shape(Shape&& other) = delete;
	virtual ~Shape() = default;

public:
	void Initialize(const ShapeData& initData);
	void Update();
	void Render();

protected:
	vector<Vertex> m_vecVertices;
	vector<uint32_t> m_vecIndices;
	shared_ptr<VertexBuffer> m_vertexBuffer;
	shared_ptr<IndexBuffer> m_indexBuffer;
	D3D11_PRIMITIVE_TOPOLOGY m_topology;

	UINT m_stride;
	UINT m_offset;

	bool m_completeProcessCpuData;
};


