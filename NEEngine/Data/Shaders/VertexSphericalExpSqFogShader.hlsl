cbuffer PerApplication : register(b0)
{
	matrix projectionMatrixFront;
	matrix projectionMatrixBack;
	float density;
}

cbuffer PerFrame : register(b1)
{
	matrix viewMatrixFront;
	matrix viewMatrixBack;
}

cbuffer PerObject : register(b2)
{
	matrix worldMatrix;
}

//POSITION and COLOR are semantics that are used to link vs variables to ps variables
struct VertexShaderInput
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD;
};

struct VertexShaderOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD0;
	float fogFactor : FOG_FACTOR;
};
//entry point
VertexShaderOutput main(VertexShaderInput IN, uint instanceID : SV_InstanceID)
{
	VertexShaderOutput OUT;
 
	matrix viewMatrix, projectionMatrix;
	if (instanceID == 0)
	{
		projectionMatrix = projectionMatrixFront;
		viewMatrix = viewMatrixFront;
	}
	else if (instanceID == 1)
	{
		projectionMatrix = projectionMatrixBack;
		viewMatrix = viewMatrixBack;
	}

	matrix viewWorld = mul(viewMatrix, worldMatrix);
	float4 cameraSpacePosition = mul(viewWorld, IN.position);
	OUT.color = IN.color;
	OUT.position = mul(projectionMatrix, cameraSpacePosition);
	
	float chordLength = distance(float4(0, 0, 0, 1), cameraSpacePosition); //длина хорды
	float distance = 2 * asin(chordLength / 2.);
	if (instanceID == 1)
		distance += 3.14159265; //это работает потому что для instanceID = 1 камера из антиподальной точки
	OUT.fogFactor = saturate(exp(-pow(density * distance, 2)));
	OUT.tex = IN.tex;

	return OUT;
}