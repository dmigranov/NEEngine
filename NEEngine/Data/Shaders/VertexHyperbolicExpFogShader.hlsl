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

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}