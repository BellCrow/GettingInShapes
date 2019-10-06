#pragma once
struct Vertex
{
	Vertex()
	{
		x = 0;
		y = 0;
		z = 0;
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}
	
	Vertex(float a_x,float a_y,float a_z,float a_r,float a_g,float a_b,float a_a)
	{
		x = a_x;
		y = a_y;
		z = a_z;
		r = a_r;
		g = a_g;
		b = a_b;
		a = a_a;
	}
	float x, y, z;
	float r, g, b, a;
};