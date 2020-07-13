
Texture2D shaderTexture;
SamplerState SampleType;


struct PixelShaderInput
{
	float4 color : COLOR;
	float2 tex : TEXCOORD0;
};
 
float4 SimplePixelShader(PixelShaderInput IN) : SV_TARGET
{
	float4 sourceColor = ((IN.tex.x == 0.f && IN.tex.y == 0.f) ? IN.color : shaderTexture.Sample(SampleType, IN.tex));
	
	return sourceColor;
;
}