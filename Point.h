#pragma once
struct Point
{
	float x;
	float y;
	float z;

	Point()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Point(float a_x, float a_y, float a_z)
	{
		x = a_x;
		y = a_y;
		z = a_z;
	}
};