struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

PixelInputType VShader(VertexInputType input)
{
	PixelInputType output;

	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;
	output.position = input.position;

	// Store the input color for the pixel shader to use.
	output.color = input.color;

	return output;
}

float4 PShader(PixelInputType input) : SV_TARGET
{
	return input.color;
}