#pragma once

#include "Vertex.h"
#include "Point.h"
#include "AbstractShape.h"


class Rhombus: public AbstractShape
{
public:
	Rhombus(Point pos, float width, float height, Color color);
	~Rhombus();

	// Inherited via AbstractShape
	void SetHeight(float) override;
	void SetWidth(float) override;
	void SetPosition(Point) override;
	void SetColor(Color) override;
private:
	
	// Inherited via AbstractShape
	virtual int GetTriangleCount() override;

	// Inherited via AbstractShape
	virtual void CalculateRenderData() override;
};

