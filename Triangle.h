#pragma once
#include "AbstractShape.h"
class Triangle :
	public AbstractShape
{
public:
	Triangle(Point center, float width, float height, Color color);	
private:
	
	// Inherited via AbstractShape
	virtual int GetTriangleCount() override;
	virtual void CalculateRenderData() override;

	// Inherited via AbstractShape
	virtual int GetWireframeLineCount() override;
};

