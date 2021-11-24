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

[maxvertexcount(30)]
void main(
	point GSInput input[1], 
	inout TriangleStream< GSOutput > output
)
{
	GSInput inputPoint = input[0];
	
	int side_count = 8;
	for (int i = 0; i <= side_count; i++) {
		float ang = PI * 2.0 / side_count * i;
		float4 offset = float4(cos(ang) * 0.1, -sin(ang) * 0.1, 0.0, 0.0);
		float4 newPoint = inputPoint.position + offset;
	}


	/*
	for (uint i = 0; i < 3; i++)
	{
		GSOutput element;
		element.position = input[i];
		output.Append(element);
	}
	*/
}