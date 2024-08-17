#pragma once
class Shape;
struct Vertex
{
	Vector3 pos;
	Vector3 color;
};
struct ShapeData
{
	vector<Vertex> vertices;
	vector<uint32_t> indices;
};
class ViewSpace
{
public:
	void Initialize();
	void Update();
	void Render();

private:
	void ClearShapeData();

private:
	ShapeData m_shapeData;
	vector<shared_ptr<Shape>> m_vecShapes;
};


