struct VertexOutput // Sementic�� ���߸� ��
{
    float4 pos   : SV_POSITION;
    float4 color : COLOR;
};

// ���⼭���ʹ� position ������ �ʿ����

float4 main(VertexOutput input) : SV_TARGET
{
    return input.color;
}