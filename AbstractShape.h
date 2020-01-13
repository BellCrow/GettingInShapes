#pragma once
#include <vector>
#include <string>
#include <memory>
#include <array>
#include <DirectXMath.h>

#include "SmartPointer.h"
#include "RenderTriangle.h"
#include "Color.h"
#include "RenderLine.h"

using namespace DirectX;

class AbstractShape
{
public:

	AbstractShape(Point position, float width, float height, float depth, Color color) {
		m_position = position;
		m_width = width;
		m_height = height;
		m_depth = depth;
		m_color = color;
		m_triangles = nullptr;
		m_isDirty = true;
		m_modelMatrix = {};
	}

	~AbstractShape() {
		m_triangles = nullptr;
	}

	virtual int GetTriangleCount() = 0;
	virtual int GetWireframeLineCount() = 0;

	void SetHeight(float);
	void SetWidth(float);
	void SetDepth(float);
	void SetPosition(Point);
	void SetColor(Color);

	const float& GetHeight() const { return m_height; }
	const float& GetWidth() const { return m_width; }
	const Point& GetPosition() const { return m_position; }
	const Color& GetColor() const { return m_color; }
		
	const sp<RenderTriangle[]> GetTriangles() {return m_triangles;}
	const sp<RenderLine[]> GetWireframeLines() {return m_wireframeLines;}
	const XMMATRIX* GetModelmatrix();

protected:
	
	virtual void CalculateRenderData() = 0;

	bool m_isDirty;
	Color m_color;
	float m_height;
	float m_width;
	float m_depth;

	Point m_position;
	std::string m_name;
	std::shared_ptr<RenderTriangle[]> m_triangles;
	std::shared_ptr<RenderLine[]> m_wireframeLines;
	XMMATRIX m_modelMatrix;
};
