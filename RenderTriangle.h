#pragma once
#include "Point.h"

struct RenderTriangle
{
public:
	Point pointA, pointB, pointC;
	RenderTriangle(Point a_pointA, Point a_pointB,Point a_pointC);
	RenderTriangle() = default;
};

