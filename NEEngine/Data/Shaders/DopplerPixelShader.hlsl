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
	float r = rgb.x, g = rgb.y, b = rgb.z;
	float min, max, delta;
	float3 hsv;
	float h, s, v;

	min = r < g ? r : g;
	min = min < b ? min : b;

	max = r > g ? r : g;
	max = max > b ? max : b;

	delta = max - min;

	//! v
	v = max; 
	if (delta < 0.00001)
	{
		s = 0.f;
		h = 0.f; 
		return float3(h, s, v);
	}


	//! s
	if (max > 0.f)
		s = (delta / max); 
	else
	{
		// max is 0 -> r = g = b = 
		s = 0.f;
		h = 0.f; // in fact, undefined
		return float3(h, s, v);
	}


	//! h
	if (r >= max)                          
		h = (g - b) / delta;
	else
		if (g >= max)
			h = 2.f + (b - r) / delta; 
		else
			h = 4.f + (r - g) / delta;  

	out.h *= 60.f;                              // degrees

	if (out.h < 0.0)
		out.h += 360.0;

	hsv.x = h;
	hsv.y = s;
	hsv.z = v;
	return hsv;
}

float4 main(PixelShaderInput IN) : SV_TARGET
{
	float4 sourceColor = ((IN.tex.x == 0.f && IN.tex.y == 0.f) ? 1.f : shaderTexture.Sample(SampleType, IN.tex));

	float4 retColor = IN.fogFactor * sourceColor + (1.0 - IN.fogFactor) * fogColor;
	return retColor;
}