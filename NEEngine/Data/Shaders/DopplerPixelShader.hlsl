Texture2D shaderTexture;
SamplerState SampleType;

cbuffer PerApplication : register(b0)
{
	float4 fogColor;
	double distance;
}

struct PixelShaderInput
{
	float2 tex : TEXCOORD0;
	float fogFactor : FOG_FACTOR;
};

float3 rgb2hsv(float3 rgb)
{

}

float4 main(PixelShaderInput IN) : SV_TARGET
{
	float4 sourceColor = ((IN.tex.x == 0.f && IN.tex.y == 0.f) ? 1.f : shaderTexture.Sample(SampleType, IN.tex));

	float4 retColor = IN.fogFactor * sourceColor + (1.0 - IN.fogFactor) * fogColor;
	return retColor;
}