#include "pch.h"
#include "ViewSpace.h"
#include "PointList.h"

void ViewSpace::Initialize()
{
	auto& vertices = m_shapeData.vertices;
	auto& indices = m_shapeData.indices;
	Vertex v;
	v.pos = Vector3(0.0f, 0.0f,0.0f);
	v.color = Vector3(0.0f, 0.0f, 1.0f);
	vertices.push_back(v);
	v.pos = Vector3(1.0f, 0.0f,0.0f);
	v.color = Vector3(1.0f, 1.0f, 1.0f);
	vertices.push_back(v);
	v.pos = Vector3(0.0f, 1.0f,0.0f);
	v.color = Vector3(1.0f, 1.0f, 0.0f);
	vertices.push_back(v);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	m_vecShapes.resize(1);
	m_vecShapes[0] = make_shared<PointList>();
	m_vecShapes[0]->Initialize(m_shapeData);

	ClearShapeData();
}

void ViewSpace::Update()
{

}

void ViewSpace::Render()
{
	for (auto& shape : m_vecShapes)
		shape->Render();
}

void ViewSpace::ClearShapeData()
{
	m_shapeData.vertices.clear();
	m_shapeData.indices.clear();
}
