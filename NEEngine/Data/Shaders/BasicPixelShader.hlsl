Texture2D shaderTexture;
SamplerState SampleType;

cbuffer PerApplication : register(b0)
{
	float4 fogColor;
}

struct PixelShaderInput
{
	float2 tex : TEXCOORD0;
	float fogFactor : FOG_FACTOR;
};
 
float4 SimplePixelShader(PixelShaderInput IN) : SV_TARGET
{
	float4 sourceColor = ((IN.tex.x == 0.f && IN.tex.y == 0.f) ? 0.f : shaderTexture.Sample(SampleType, IN.tex));
	
	return IN.fogFactor * sourceColor + (1.0 - IN.fogFactor) * fogColor;
}