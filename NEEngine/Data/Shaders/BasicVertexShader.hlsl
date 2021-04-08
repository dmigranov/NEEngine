cbuffer PerApplication : register(b0)
{
	matrix projectionMatrix;
}

cbuffer PerFrame : register(b1)
{
	matrix viewMatrix;
}

cbuffer PerObject : register(b2)
{
    matrix worldMatrix;
}

//POSITION and COLOR are semantics that are used to link vs variables to ps variables
struct VertexShaderInput
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
};

struct VertexShaderOutput
{
	float2 tex : TEXCOORD0;
	float4 position : SV_POSITION;
};

//entry point
VertexShaderOutput SimpleVertexShader(VertexShaderInput IN)
{
	VertexShaderOutput OUT;

	float4 position = float4(IN.position.x, IN.position.y, IN.position.z, 1);
	matrix viewWorld = mul(viewMatrix, worldMatrix);
	float4 cameraSpacePosition = mul(viewWorld, position);
	OUT.position = mul(projectionMatrix, cameraSpacePosition);
	
	OUT.tex = IN.tex;

	
	return OUT;
}