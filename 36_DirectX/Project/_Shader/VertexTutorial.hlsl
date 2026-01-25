// 이것들은 형식에 불과
cbuffer World : register(b0)
{
    matrix world;
}

cbuffer View : register(b1)
{
    matrix view;
}

cbuffer Proj : register(b2)
{
    matrix proj;
}


struct VertexInput // Semantic만 맞추면 됨
{
    float4 pos   : POSITION;
    float4 color : COLOR;
};

struct VertexOutput // Semantic만 맞추면 됨
{
    float4 pos   : SV_POSITION;
    float4 color : COLOR;
};

// SV_Position - 리턴값의 semantic (sv는 system value) -> System에는 IA RS OM이 있고 여기는 RS에 넘기는 것임
VertexOutput main( VertexInput input )
{
    VertexOutput output;
    
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);

    output.color = input.color;
    
	return output;
}