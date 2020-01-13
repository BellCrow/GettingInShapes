#pragma once
#include <DirectXMath.h>

struct Vertex
{

	Vertex()
	{
		position = {};
		position.x = 0;
		position.y = 0;
		position.z = 0;
		position.w = 0;

		color = {};
		color.x = 0;
		color.y = 0;
		color.z = 0;
		color.w = 0;
	}
	
	Vertex(float a_x,float a_y,float a_z,float a_w,
		   float a_r,float a_g,float a_b,float a_a)
	{
		position = {};
		position.x = a_x;
		position.y = a_y;
		position.z = a_z;
		position.w = a_w;

		color = {};
		color.x = a_r;
		color.y = a_g;
		color.z = a_b;
		color.w = a_a;
	}

	DirectX::XMFLOAT4A position;
	DirectX::XMFLOAT4A color;
};