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

[maxvertexcount(16)]
void main(
	point GSInput input[1], 
	inout TriangleStream< GSOutput > output
)
{
	GSInput inputPoint = input[0];
	/*
	for (uint i = 0; i < 3; i++)
	{
		GSOutput element;
		element.position = input[i];
		output.Append(element);
	}
	*/
}