//todo: correct structures
//https://open.gl/geometry

struct GSInput
{
	float2 tex : TEXCOORD0;
	float fogFactor : FOG_FACTOR;
	float4 position : SV_POSITION;
};

struct GSOutput
{
	float2 tex : TEXCOORD0;
	float fogFactor : FOG_FACTOR;
	float4 position : SV_POSITION;	//has to be the last before RS
};

#define PI 3.14159265

//TODO: учёт соотношения сторон

[maxvertexcount(10)]
void main(
	point GSInput input[1], 
	inout TriangleStream< GSOutput > outputStream
)
{
	GSInput inputVertex = input[0];
	if (inputVertex.position.z < 0) 
		return;
	//зачем то, что сверху нужно? мы полагаемся на то, что точки с z < 0 отсекаются.
	//но это отсечение происходит уже после этого этапа!
	//мы же полностью теряем эту информацию при делении, если не делаем проверку услови выше.

	float4 centerPoint = inputVertex.position / inputVertex.position.w;

	float4 points[10];
	points[0] = centerPoint;

	for (int i = 0; i <= 8; i++) {
		float ang = PI * 2.f / 8 * i;
		float4 offset = float4(cos(ang) * 0.015f, -sin(ang) * 0.02f, 0.f, 0.f);
		float4 newPoint = centerPoint + offset;
		points[i + 1] = newPoint;
	}

	for (i = 0; i < 10; i++)
	{
		int pointIndex;
		if (i % 2 != 0)
			pointIndex = i / 2;
		else
			pointIndex = 9 - i / 2;
		GSOutput output;
		output.position = points[pointIndex];
		output.fogFactor = inputVertex.fogFactor;
		output.tex = inputVertex.tex;

		outputStream.Append(output);
	}

	outputStream.RestartStrip(); // создаем примитив 
}