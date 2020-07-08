
Texture2D shaderTexture;
SamplerState SampleType;

cbuffer PerApplication : register(b0)
{
	float4 fogColor;
	float thickness;
}

struct PixelShaderInput
{
	float4 color : COLOR;
	noperspective float3 edgeDistance : EDGEDISTANCE;
	float fogFactor : FOG_FACTOR;
	float2 tex : TEXCOORD0;
};
 
float4 SimplePixelShader(PixelShaderInput IN) : SV_TARGET
{
	float3 edgeDistance = IN.edgeDistance;
	float distance = min(edgeDistance.x, min(edgeDistance.y, edgeDistance.z));
	
	float4 preFogColor;
	float4 sourceColor = ((IN.tex.x == 0.f && IN.tex.y == 0.f) ? IN.color : shaderTexture.Sample(SampleType, IN.tex));
	
	if (thickness > 0 && distance < thickness)
		preFogColor = 0.7 * float4(0, 0, 0, 1) + 0.3 * sourceColor; //draw fragment if close to edge
	else 
		preFogColor = sourceColor; //а можно дискард
	
	//todo: исправить черные полоски при выключенном edgeDistance а то некрасиво
	
	return IN.fogFactor * preFogColor + (1.0 - IN.fogFactor) * fogColor;
;
}