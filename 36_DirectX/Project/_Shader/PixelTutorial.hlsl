struct VertexOutput // Sementic만 맞추면 됨
{
    float4 pos   : SV_POSITION;
    float4 color : COLOR;
};

// 여기서부터는 position 정보가 필요없음

float4 main(VertexOutput input) : SV_TARGET
{
    return input.color;
}