#include "Framework.h"
#include "Polygons.h"


Polygons::Polygons(float radius, UINT sectorCount, Vector4 color)
{
    for (UINT i = 0; i < sectorCount; i++)
    {
        float angle = XM_2PI / sectorCount * i;

        Vector3 pos =
        {
            radius * cosf(angle),
            radius * sinf(angle),
            0.f
        };

        vertices.push_back(VertexColor( pos, color ));
    }

    for (UINT i = 0; i < sectorCount - 2; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 2);
        indices.push_back(i + 1);
    }

    vertexBuffer    = new VertexBuffer(vertices);
    indexBuffer     = new IndexBuffer(indices);

    vertexShader    = new VertexShader(L"VertexTutorial");
    pixelShader     = new PixelShader(L"PixelTutorial");

    worldBuffer     = new MatrixBuffer();

}

Polygons::~Polygons()
{
    delete vertexBuffer;
    delete vertexShader;
    delete pixelShader;
    delete indexBuffer;
    delete worldBuffer;
}

void Polygons::Render()
{
    vertexBuffer->SetBuffer();
    indexBuffer->SetBuffer();

    vertexShader->SetShader();
    pixelShader->SetShader();

    worldBuffer->SetData(world);
    worldBuffer->VSSetBuffer(0);

    DC->DrawIndexed(indices.size(), 0, 0);
}
