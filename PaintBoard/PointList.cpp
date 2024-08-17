#include "pch.h"
#include "PointList.h"

PointList::PointList()
	: Shape()
{
	m_topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
}
