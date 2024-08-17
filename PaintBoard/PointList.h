#pragma once
#include "Shape.h"
class PointList :
	public Shape
{
public:
	PointList();
	PointList(const PointList&) = default;
	PointList(PointList&&) = delete;
	virtual ~PointList() = default;

public:


private:

};

