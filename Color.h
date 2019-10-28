#pragma once
struct Color
{
public:
	float A;
	float R;
	float G;
	float B;

	Color() = default;

	Color(float a_alpha, float a_red, float a_green, float a_blue)
	{
		A = a_alpha;
		R = a_red;
		G = a_green;
		B = a_blue;
	}
};