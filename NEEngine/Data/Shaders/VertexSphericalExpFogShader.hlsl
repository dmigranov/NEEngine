cbuffer PerApplication : register(b0)
{
	matrix projectionMatrixFront;
	matrix projectionMatrixBack;
	double density;
}

cbuffer PerFrame : register(b1)
{
	matrix viewMatrixFront;
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
	float fogFactor : FOG_FACTOR;
	float4 position : SV_POSITION; //������ ���� ��������� ��� ����������� � ���������� ������, ���� � ��� �� ����� ��� ����� (����� �� ���������)
};

//entry point
VertexShaderOutput main(VertexShaderInput IN, uint instanceID : SV_InstanceID)
{
	matrix viewMatrixBack = -viewMatrixFront;
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
	
	OUT.position = mul(projectionMatrix, cameraSpacePosition);
	
	float chordLength = distance(float4(0, 0, 0, 1), cameraSpacePosition); //����� �����
	float distance = 2 * asin(chordLength / 2.);
	if (instanceID == 1)
		distance += 3.14159265;
	OUT.fogFactor = saturate(exp(-density * distance));
	OUT.tex = IN.tex;

	return OUT;
}