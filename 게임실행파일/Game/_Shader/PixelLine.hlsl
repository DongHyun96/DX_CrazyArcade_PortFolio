cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

struct VertexOutput // Sementic�� ���߸� ��
{
    float4 pos : SV_POSITION;
};

// ���⼭���ʹ� position ������ �ʿ����

float4 main(VertexOutput input) : SV_TARGET
{
    return color;
}