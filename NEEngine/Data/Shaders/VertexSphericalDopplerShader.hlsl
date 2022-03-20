cbuffer PerApplication : register(b0)
{
	matrix projectionMatrixFront;
	matrix projectionMatrixBack;
	double density;
	double mu;
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
	float radiusRatio : R_RATIO;
	float4 position : SV_POSITION; //должно быть последним при поступлении в пиксельный шейдер, если в нем не будем его брать (иначе всё сместится)
};

float SphericalDistance(float4 vec1, float4 vec2, float radius)
{
	float chordLength = distance(vec1, vec2); //chord length
	return 2 * radius * asin(chordLength / (2.f * radius)); //angle is 2arcsin(L/2R), length of arc equals angle * R
}

float RadiusFunction(float mu) 
{ 
	return 2 * (1 - cos(mu)); 
}

//entry point
VertexShaderOutput main(VertexShaderInput IN
	, uint instanceID : SV_InstanceID 
)
{
	//uint instanceID = 1; //todo: УБРАТЬ, ОТЛАДКА!
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

	//IN.position: sum of squares must be 1!

	matrix viewWorld = mul(viewMatrix, worldMatrix);

	float4 position; //итоговая позиция
	float4 position1 = normalize(IN.position); //нормализованные координаты: лежат на единичной гиперсфере

	const float epsilon = 0.3f;
	const float initialRadius = 0.1f; //!!!: pass to shader from CPU!
	const float bigRadius = 0.999f;

	float4 objectCenter = mul(viewWorld, float4(0, 0, 0, 1));
	float chiCenter = SphericalDistance(float4(0, 0, 0, 1), objectCenter, 1);
	if (instanceID == 1)
		chiCenter += 3.14159265; 

	float muStart = chiCenter;
	float muEnd = muStart + epsilon;
	float scaleCoeff, wScaleCoeff;
	
	float rNewAddition = (muEnd - clamp((float)mu, muStart, muEnd)) / epsilon;
	float rNew = initialRadius + (bigRadius - initialRadius) * rNewAddition;
	scaleCoeff = rNew / initialRadius;
	wScaleCoeff = sqrt((1 - rNew * rNew) / (1 - initialRadius * initialRadius));
	matrix scaleMatrix = matrix(scaleCoeff, 0, 0, 0,
								0, scaleCoeff, 0, 0,
								0, 0, scaleCoeff, 0,
								0, 0, 0, wScaleCoeff); 
	//position1 = mul(scaleMatrix, position1);			//!!! закомментировать если не нужно делать большими

	double radius = RadiusFunction(mu);

	if (abs(position1.w - 1) < 0.00001)
		position = position1 * radius;
	else
	{
		float4 objectCenter1 = float4(0, 0, 0, 1); //координаты центра объекта для единичной гиперсферы в координатах world
		float distanceFromPointToCenter = SphericalDistance(objectCenter1, position1, 1.); //must stay the same!
		//тут прибавлять ничего не надо, так как далее sin в квадрате, а sin^2 x = sin^2 (2pi-x) 

		// todo: можно воспользоваться знанием Хи центра объекта
		// и посчитать сразу тут radius_old
		// и использовать его для вычисления далее!
		// итак, radiusOldCenter - для вычисления размеров
		// radiusOld - для цвета
		double radiusOldСenter = RadiusFunction(mu - chiCenter);

		float w_new = radius * (1 - 2 * pow(sin(distanceFromPointToCenter / (2 * radius)), 2));

		// TODO: формулы ниже не до конца обоснованы теоретически
		// как это можно проверить: нужно пройти расстояние distanceFromPointToCenter от центра в том же самом направлении
		// направление - это вектор в касательном пространстве
		// Идея: найти уравнение прямой в гиперсфере

		float lambda = sqrt((position1.x * position1.x + position1.y * position1.y + position1.z * position1.z) / (radius * radius - w_new * w_new));
		float x_new = position1.x / lambda, y_new = position1.y / lambda, z_new = position1.z / lambda;
		position = float4(x_new, y_new, z_new, w_new);
	}
	
	float4 cameraSpacePosition = mul(viewWorld, position);
	
	float distance = SphericalDistance(float4(0, 0, 0, radius), cameraSpacePosition, radius);
	if (instanceID == 1)
		distance += 3.14159265 * radius;

	double chi;
	chi = distance / radius; //TODO: посмотреть альтернативные варианты: во-первых, старый вариант: до центра
	//во-вторых, до ближайшей к камере точки
	double radiusOld = RadiusFunction(mu - chi);

	OUT.position = mul(projectionMatrix, cameraSpacePosition);
	OUT.tex = IN.tex;
	OUT.fogFactor = saturate(exp(-density * distance));
	OUT.radiusRatio = radiusOld / radius;

	return OUT;
}