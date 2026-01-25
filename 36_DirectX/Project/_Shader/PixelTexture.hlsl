cbuffer ColorBuffer : register(b0)
{
    float4 color;
}


struct VertexOutput
{
    float4 pos  : SV_POSITION;
    float2 uv   : UV;
};

Texture2D       map     : register(t0); // SRV 정보가 여기로 옴
SamplerState    samp    : register(s0); // Mapping descriptor

// 여기서부터는 position 정보가 필요없음

float4 main(VertexOutput input) : SV_TARGET
{
    float4 textureColor = map.Sample(samp, input.uv);



   /* if (all(textureColor == float4(1, 0, 1, 1)))
        textureColor.a = 0.f;

    if (textureColor.a < 0.1f)
        discard;*/

    //discard;
    if (all(color == float4(0, 0, 0, 1)) && textureColor.a != 0.f)
        return float4(1,1,1,1);

    return textureColor * color;
}