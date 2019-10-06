#pragma once
struct Position
{
	float x;
	float y;

	Position()
	{
		x = 0;
		y = 0;
	}

	Position(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}
};