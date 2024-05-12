// �̰͵��� ���Ŀ� �Ұ�
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


struct VertexInput // Sementic�� ���߸� ��
{
    float4 pos : POSITION;
};

struct VertexOutput // Sementic�� ���߸� ��
{
    float4 pos : SV_POSITION;
};

// SV_Position - ���ϰ��� sementic (sv�� System Value) -> System���� IA RS OM�� �ְ� ����� RS�� �ѱ�� ����
VertexOutput main(VertexInput input)
{
    VertexOutput output;
    
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);

    return output;
}