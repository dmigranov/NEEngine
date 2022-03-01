Texture2D shaderTexture;
SamplerState SampleType;

cbuffer PerApplication : register(b0)
{
	float4 fogColor;
	float4 selectionColor;
	double velocity_coeff;
}

cbuffer PerObject : register(b1)
{
	int isSelected;
}

struct PixelShaderInput
{
	float2 tex : TEXCOORD0;
	float fogFactor : FOG_FACTOR;
	float velocity : VELOCITY;
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

double getFrequency(double hue)
{
	double lambda = 650. - 250. / 270. * hue;
	double frequency = 2. * PI * C / lambda;
	return frequency;
}

double getHue(double frequency)
{
	double lambda = 2. * PI * C / frequency;
	/*
	if (lambda > 650)
		//return -1; 
		lambda = 650.; 
	if (lambda < 400)
		//return -1;
		lambda = 400; 
	*/
	double hue = (650. - lambda) * 270 / 250;
	//ключевой вопрос - что делать со значениями на границе!
	//допустим, lambda > 650. тогда hue будет отрицательным - легко проверить!
	//наоборот, если lambda < 400. тогда hue будет больше, чем 270 - тоже легко проверить
	//тогда, в зависимости от отдаления от этих границ, можно интеролировать с черным?
	return hue;
}

float3 hsv2rgb(float3 hsv)
{
	float h = hsv.x, s = hsv.y, v = hsv.z;
	float r, g, b;

	if (s <= 0.0) {       // < is bogus, just shuts up warnings
		r = v;
		g = v;
		b = v;
		return float3(r, g, b);
	}

	float hh, ff, p, q, t;
	hh = h;
	if (hh >= 360.f) hh = 0.f;
	hh /= 60.f;
	int i = (int)hh;
	ff = hh - i;
	p = v * (1.0 - s);
	q = v * (1.0 - (s * ff));
	t = v * (1.0 - (s * (1.0 - ff)));

	switch (i) {
	case 0:
		r = v;
		g = t;
		b = p;
		break;
	case 1:
		r = q;
		g = v;
		b = p;
		break;
	case 2:
		r = p;
		g = v;
		b = t;
		break;

	case 3:
		r = p;
		g = q;
		b = v;
		break; 
	case 4:
		r = t;
		g = p;
		b = v;
		break;
	case 5:
	default:
		r = v;
		g = p;
		b = q;
		break;
	}

	return float3(r, g, b);
}


float4 main(PixelShaderInput IN) : SV_TARGET
{
	float velocity = (float)velocity_coeff * IN.velocity;

	//float4 sourceColor = ((IN.tex.x == 0.f && IN.tex.y == 0.f) ? 1.f : shaderTexture.Sample(SampleType, IN.tex));
	float4 sourceColor = shaderTexture.Sample(SampleType, IN.tex);
	if (sourceColor.x < 0.01f && sourceColor.y < 0.01f && sourceColor.z < 0.01f)
	{
		float4 retColor = IN.fogFactor * sourceColor + (1.0 - IN.fogFactor) * fogColor;
		return retColor;
	}

	float3 rgb = float3(sourceColor.x, sourceColor.y, sourceColor.z);
	float3 hsv = rgb2hsv(rgb);
	double hue = hsv.x;
	double freq = getFrequency(hue);

	double freqNew = freq * (1 - velocity  / C);
	double hueNew = getHue(freqNew);
	if (lambda > 650)
		//return -1; 
		lambda = 650.;
	if (lambda < 400)
		//return -1;
		lambda = 400;
	*/
	float3 rgbNew;
	if (hueNew > 0)
	{
		float3 hsvNew = float3((float)hueNew, 1, 1);
		rgbNew = hsv2rgb(hsvNew);
	}
	else
		rgbNew = float3(0., 0., 0.);

	float4 sourceColorNew = float4(rgbNew.x, rgbNew.y, rgbNew.z, sourceColor.w);
	float4 retColor = IN.fogFactor * sourceColorNew + (1.0 - IN.fogFactor) * fogColor; //было sourceColor вместо sourceColorNew
	
	if (isSelected != 0)
		retColor = 0.3 * retColor + 0.7 * selectionColor;
	
	return retColor;
}