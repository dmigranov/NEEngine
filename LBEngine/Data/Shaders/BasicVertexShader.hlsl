cbuffer PerApplication : register(b0)
{
    matrix projectionMatrixFront;
	matrix projectionMatrixBack;
	float fogStart;
	float fogEnd;
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
    float4 color: COLOR;
};

struct VertexShaderOutput
{
	float4 position : SV_POSITION;
    float4 color : COLOR;
	float fogFactor : FOG_FACTOR;
};

//entry point
VertexShaderOutput SimpleVertexShader(VertexShaderInput IN, uint instanceID : SV_InstanceID)
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
	float distance = 2 * asin(chordLength/2.);
	if (instanceID == 1)
		distance += 3.14159265;
	OUT.fogFactor = saturate((fogEnd - distance) / (fogEnd - fogStart));
	
	return OUT;
}