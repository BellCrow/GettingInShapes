#pragma once
struct Color
{
public:
	float R;
	float G;
	float B;
	float A;

	Color() = default;

	Color(float a_red, float a_green, float a_blue, float a_alpha)
	{
		R = a_red;
		G = a_green;
		B = a_blue;
		A = a_alpha;
	}
};