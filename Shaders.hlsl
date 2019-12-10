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

cbuffer g_modelMatrix
{
    row_major matrix modelMatrix;
};

cbuffer g_viewMatrix
{
    row_major matrix viewMatrix;
}

cbuffer g_projMatrix
{
    row_major matrix projMatrix;
}

PixelInputType VShader(VertexInputType input)
{
	PixelInputType output;

	// Change the position vector to be 4 units for proper matrix calculations.	
    input.position.w = 1;
    
    float4 pos = input.position;
    pos = mul(pos, modelMatrix);
    pos = mul(pos, viewMatrix);
    pos = mul(pos, projMatrix);
	output.position = pos;
    
	// Store the input color for the pixel shader to use.
	output.color = input.color;
	return output;
}

float4 PShader(PixelInputType input) : SV_TARGET
{
	return input.color;
}