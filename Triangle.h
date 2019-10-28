#pragma once
#include "AbstractShape.h"
class Triangle : public AbstractShape
{
public:
	Triangle(Point center, float width, float height, Color color);

	// Inherited via AbstractShape
	virtual void SetHeight(float) override;
	virtual void SetWidth(float) override;
	virtual void SetPosition(Point) override;
private:
	void CalculateTriangles();

	// Inherited via AbstractShape
	virtual void SetColor(Color) override;

	// Inherited via AbstractShape
	virtual int GetTriangleCount() override;
};

