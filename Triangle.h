#pragma once
#include "AbstractShape.h"
class Triangle :
	public AbstractShape
{
public:
	Triangle(Point center, float width, float height);

	// Inherited via AbstractShape
	virtual void SetHeight(float) override;
	virtual void SetWidth(float) override;
	virtual void SetPosition(Point) override;
private:
	void CalculateTriangles();
};

