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
	float4 position : SV_POSITION; //должно быть последним при поступлении в пиксельный шейдер, если в нем не будем его брать (иначе всё сместится)
};

float SphericalDistance(float4 vec1, float4 vec2, double radius)
{
	float chordLength = distance(vec1, vec2); //chord length
	return 2 * radius * asin(chordLength / (2. * radius)); //angle is 2arcsin(L/2R), length of arc equals angle * R
}

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

	//IN.position: сумма квадратов должна быть 1!
	matrix viewWorld = mul(viewMatrix, worldMatrix);

	float4 position1 = normalize(IN.position); //нормализованные координаты: лежат на единичной гиперсфере
	float4 objectCenter1 = float4(0, 0, 0, 1); //координаты центра объекта для единичной гиперсферы в координатах world
	float distanceFromPointToCenter = SphericalDistance(position1, objectCenter1, 1); //must stay the same!
	float w_new = radius * (1 - 2 * pow(sin(distanceFromPointToCenter / (2 * radius)), 2));
	float lambda = sqrt((position1.x * position1.x + position1.y * position1.y + position1.z * position1.z) / (radius * radius - w_new * w_new));
	float x_new = position1.x / lambda, y_new = position1.y / lambda, z_new = position1.z / lambda;

	//todo: расстояние должно сохраняться.
	//нужно пройти расстояние distanceFromPointToCenter от центра в том же самом направлении
	//и записать его в position
	// 
	// 	   Идея: найти уравнение прямой в гиперсфере
	// 	   Построить согласно этому уравнению точку, лежащую на нужном расстоянии 6
	// 	   расстояние будет пропорционально углу/параметру в уравнении (он один)
	// 
	//окружность лежит в плоскости, образовываемой векторами position1 и objectCenter1
	//If we find two orthonormal vectors u and v in this plane then the equation of the great circle will be
	//c = r(u cos ? + v sin ?)
	//угол надо будет изменить пропорционально расстояния
	//как найти вектора u и v?
	//в качестве u возьмем (0, 0, 0, 1)
	

	float4 position = float4(0, 0, 0, distanceFromPointToCenter);
	//float4 position = radius * position1; 

	float4 cameraSpacePosition = mul(viewWorld, position);
	
	OUT.position = mul(projectionMatrix, cameraSpacePosition);

	
	//float chordLength = distance(float4(0, 0, 0, radius), cameraSpacePosition); //длина хорды
	//float distance = 2 * radius * asin(chordLength / (2. * radius)); //угол - 2arcsin(L/2R), длина дуги = угол * R
	float distance = SphericalDistance(float4(0, 0, 0, radius), cameraSpacePosition, radius);
	if (instanceID == 1)
		distance += 3.14159265 * radius;
	OUT.fogFactor = saturate(exp(-density * distance));
	OUT.tex = IN.tex;

	return OUT;
}