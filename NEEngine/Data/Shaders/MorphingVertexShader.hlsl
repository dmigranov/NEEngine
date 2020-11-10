cbuffer PerApplication : register(b0)
{
	matrix projectionMatrix;
}

cbuffer PerFrame : register(b1)
{
	matrix viewMatrix;
}

cbuffer PerObject : register(b2)
{
	matrix worldMatrix;
    matrix morphMatrix;
}

//POSITION and COLOR are semantics that are used to link vs variables to ps variables
struct AppData
{
	float4 position : POSITION;
	float3 color : COLOR;
};

struct VertexShaderOutput
{
	float4 color : COLOR;
	float4 position : SV_POSITION; //system-value semantic that is required by the rasterizer stage
};

//entry point
VertexShaderOutput MorphingVertexShader(AppData IN)
{
	VertexShaderOutput OUT;
    
	float3 p1 = IN.position;
	float alpha = (p1.y + 1.0) / 2.0;
    
    static matrix eye =
	{
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    };
	//newWorld[1][1] *= 2;
    matrix newWorld = mul(worldMatrix, lerp(eye, morphMatrix, alpha));
    matrix mvp = mul(projectionMatrix, mul(viewMatrix, newWorld));
	OUT.position = mul(mvp, IN.position);
	OUT.color = float4(IN.color, 1.0f);
 
	return OUT;
}