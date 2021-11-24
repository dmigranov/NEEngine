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

const float epsilon = 0.001;

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

float SphericalDistance(float4 vec1, float4 vec2, float radius)
{
	float chordLength = distance(vec1, vec2); //длина хорды
	return 2 * radius * asin(chordLength / (2.f * radius)); //угол - 2arcsin(L/2R), длина дуги = угол * R
}

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
	
	//IN.position: sum of squares must be 1!

	matrix viewWorld = mul(viewMatrix, worldMatrix);

	float4 position; //итоговая позиция
	float4 position1 = normalize(IN.position); //нормализованные координаты: лежат на единичной гиперсфере
	float4 objectCenter1 = float4(0, 0, 0, 1); //координаты центра объекта для единичной гиперсферы в координатах world
	float distanceFromPointToCenter = SphericalDistance(position1, objectCenter1, 1.); //must stay the same!
	if (distanceFromPointToCenter < epsilon)
		position = IN.position;
	else
	{
		float w_new = radius * (1 - 2 * pow(sin(distanceFromPointToCenter / (2 * radius)), 2));
		float lambda = sqrt((position1.x * position1.x + position1.y * position1.y + position1.z * position1.z) / (radius * radius - w_new * w_new));
		float x_new = position1.x / lambda, y_new = position1.y / lambda, z_new = position1.z / lambda;
		position = float4(x_new, y_new, z_new, w_new);
	}


	float4 cameraSpacePosition = mul(viewWorld, position);
	//float chordLength = distance(float4(0, 0, 0, radius), cameraSpacePosition); //длина хорды
	//float distance = 2 * radius * asin(chordLength / (2. * radius));
	float distance = SphericalDistance(float4(0, 0, 0, radius), cameraSpacePosition, radius);
	
	OUT.position = mul(projectionMatrix, cameraSpacePosition);
	OUT.tex = IN.tex;

	OUT.fogFactor = saturate(exp(-density * distance));
	
	return OUT;
}