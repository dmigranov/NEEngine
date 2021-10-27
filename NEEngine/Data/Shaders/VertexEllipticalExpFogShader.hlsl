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
	float4 position : SV_POSITION;
};

//entry point
VertexShaderOutput main(VertexShaderInput IN, uint instanceID : SV_InstanceID)
{
	matrix viewMatrixBack = -viewMatrixFront;
	VertexShaderOutput OUT;
 
	matrix viewMatrix, projectionMatrix;


	if (instanceID % 2 == 0)
	{
		projectionMatrix = projectionMatrixFront;
		viewMatrix = viewMatrixFront;
	}
	else if (instanceID % 2 == 1)
	{
		projectionMatrix = projectionMatrixBack;
		viewMatrix = viewMatrixBack;
	}
	
	//IN.position: должно давать в сумме 1!
	matrix viewWorld = mul(viewMatrix, worldMatrix);

	float4 position1 = normalize(IN.position); //нормализованные координаты: лежат на единичной гиперсфере
	float4 objectCenter = mul(viewWorld, float4(0, 0, 0, 1)); //координаты центра объекта
	float4 position = radius * position1; 	//todo: перерасчЄт позиции (это неправильно: не сохран€ютс€ размеры, смотри в тетради)

	float4 cameraSpacePosition = mul(viewWorld, position);
	float chordLength = distance(float4(0, 0, 0, radius), cameraSpacePosition); //длина хорды
	float distance = 2 * radius * asin(chordLength / (2. * radius));
	
	OUT.position = mul(projectionMatrix, cameraSpacePosition);
	OUT.tex = IN.tex;

	OUT.fogFactor = saturate(exp(-density * distance));
	
	return OUT;
}