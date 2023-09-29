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

    return textureColor;
}