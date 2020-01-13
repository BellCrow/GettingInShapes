#pragma once
#include "AbstractShape.h"

class Cuboid : public AbstractShape
{
public:
	Cuboid(Point position, float width, float height, float depth, Color color) :AbstractShape(position, width, height, depth, color) {
		CalculateRenderData();
	}
	// Inherited via AbstractShape
	virtual int GetTriangleCount() override;
	virtual int GetWireframeLineCount() override;
	virtual void CalculateRenderData() override;
	void CreateTriangles();

private:
	void CreateWireFrameLines();
};
