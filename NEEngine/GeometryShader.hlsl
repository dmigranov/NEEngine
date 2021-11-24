//todo: correct structures

struct VertexInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD0;
	float fogFactor : FOG_FACTOR;
};

struct VertexOutput
{
    float4 color : COLOR;
	noperspective float3 edgeDistance : EDGEDISTANCE;
	float fogFactor : FOG_FACTOR;
	float2 tex : TEXCOORD0;
	float4 position : SV_POSITION; //стандартный System-Value для вертекса, который требуется на RS
};

//todo: возможно надо передавать координаты в мировой

[maxvertexcount(3)] // максимальное кол-во вертексов, которое мы можем добавить
void SimpleGeometryShader(triangle VertexInput input[3], inout TriangleStream<VertexOutput> stream)
{
	//БАРИОЦЕНТРИЧЕСКИЕ КООРДИНАТЫ!
	
	float3 xyz1 = input[1].position.xyz; // / input[1].position.w;
	float3 xyz2 = input[2].position.xyz; // / input[2].position.w;
	float3 xyz0 = input[0].position.xyz; // / input[0].position.w;

	float a = length(xyz1 - xyz2);
	float b = length(xyz2 - xyz0);
	float c = length(xyz1 - xyz0);
		
	float alpha = acos((b * b + c * c - a * a) / (2.0 * b * c));
	float beta = acos((a * a + c * c - b * b) / (2.0 * a * c));
	float ha = abs(c * sin(beta));
	float hb = abs(c * sin(alpha));
	float hc = abs(b * sin(alpha));
	
	float4 color = (input[0].color + input[1].color + input[2].color) / 3.f;	//
	
	VertexOutput v1 = { color, float3(ha, 0, 0), input[0].fogFactor, input[0].tex, input[0].position };
	stream.Append(v1); // добавление вертекса
	VertexOutput v2 = { color, float3(0, hb, 0), input[1].fogFactor, input[1].tex, input[1].position };
	stream.Append(v2); // добавление вертекса
	VertexOutput v3 = { color, float3(0, 0, hc), input[2].fogFactor, input[2].tex, input[2].position };
	stream.Append(v3); // добавление вертекса
	
	stream.RestartStrip(); // создаем примитив 
}