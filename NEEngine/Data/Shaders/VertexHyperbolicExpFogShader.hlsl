cbuffer PerApplication : register(b0)
{
	matrix projectionMatrix;
	double density;
}

cbuffer PerFrame : register(b1)
{
	matrix viewMatrix;
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

float asinh(float z)
{
	return log(z + sqrt(z*z + 1));
}

//entry point
VertexShaderOutput main(VertexShaderInput IN)
{
	VertexShaderOutput OUT;

	matrix viewWorld = mul(viewMatrix, worldMatrix);
	float4 cameraSpacePosition = mul(viewWorld, IN.position);
	float chordLength = distance(float4(0, 0, 0, 1), cameraSpacePosition); //длина хорды
	//float chordLength = sqrt(cameraSpacePosition.x * cameraSpacePosition.x + cameraSpacePosition.y * cameraSpacePosition.y + cameraSpacePosition.z * cameraSpacePosition.z - (cameraSpacePosition.w - 1) * (cameraSpacePosition.w - 1));

	float distance = 2 * asinh(chordLength / 2.);

	OUT.position = mul(projectionMatrix, cameraSpacePosition);
	OUT.tex = IN.tex;
	OUT.fogFactor = saturate(exp(-density * distance));
	

	return OUT;
}