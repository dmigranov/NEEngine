cbuffer PerApplication : register(b0)
{
	matrix projectionMatrixFront;
	matrix projectionMatrixBack;
	double density;
	double radius;
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

	//IN.position: ������ ������ � ����� 1!
	matrix viewWorld = mul(viewMatrix, worldMatrix);

	float4 objectCenter = mul(viewWorld, float4(0, 0, 0, 1)); //���������� ������ �������
	float4 position = radius * IN.position; 	//todo: ���������� ������� (��� �����������: �� ����������� �������, ������ � �������)

	float4 cameraSpacePosition = mul(viewWorld, position);
	
	OUT.position = mul(projectionMatrix, cameraSpacePosition);

	
	float chordLength = distance(float4(0, 0, 0, radius), cameraSpacePosition); //����� �����
	float distance = 2 * radius * asin(chordLength / (2. * radius)); //���� - 2arcsin(L/2R), ����� ���� = ���� * R
	if (instanceID == 1)
		distance += 3.14159265 * radius;
	OUT.fogFactor = saturate(exp(-density * distance));
	OUT.tex = IN.tex;

	return OUT;
}