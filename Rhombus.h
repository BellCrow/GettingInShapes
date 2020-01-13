#pragma once

#include "Vertex.h"
#include "Point.h"
#include "AbstractShape.h"


class Rhombus: public AbstractShape
{
public:
	Rhombus(Point pos, float width, float height, float depth, Color color);
	~Rhombus();

private:
	// Inherited via AbstractShape
	int GetTriangleCount() override;
	void CalculateRenderData() override;

	// Inherited via AbstractShape
	virtual int GetWireframeLineCount() override;
};

