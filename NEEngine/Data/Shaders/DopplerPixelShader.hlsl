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

	h *= 60.f;  //degrees

	if (h < 0.f)
		h += 360.f;

	hsv.x = h;
	hsv.y = s;
	hsv.z = v;
	return hsv;
}

#define PI 3.14159265
#define C 299792458

float getFrequency(float hue)
{
	float lambda = 650.f - 250.f / 270.f * hue;
	float frequency = 2 * PI * C / lambda;
	return frequency;
}

float4 main(PixelShaderInput IN) : SV_TARGET
{
	float4 sourceColor = ((IN.tex.x == 0.f && IN.tex.y == 0.f) ? 1.f : shaderTexture.Sample(SampleType, IN.tex));

	float3 rgb = float3(sourceColor.x, sourceColor.y, sourceColor.z);
	float3 hsv = rgb2hsv(rgb);
	float hue = hsv.x;

	float4 retColor = IN.fogFactor * sourceColor + (1.0 - IN.fogFactor) * fogColor;
	return retColor;
}