#include "Framework.h"
#include "Object.h"


Object::Object(Vector2 size)
{
    /* VertexBuffer */

//vertices =
//{
//    {XMFLOAT3(-0.5f, +0.5f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 1.f)}, //LT
//    {XMFLOAT3(+0.5f, +0.5f, 0.f), XMFLOAT4(0.f, 1.f, 0.f, 1.f)}, //RT
//    {XMFLOAT3(-0.5f, -0.5f, 0.f), XMFLOAT4(0.f, 0.f, 1.f, 1.f)}, //LB

//    {XMFLOAT3(-0.5f, -0.5f, 0.f), XMFLOAT4(0.f, 1.f, 1.f, 1.f)}, //LB
//    {XMFLOAT3(+0.5f, +0.5f, 0.f), XMFLOAT4(1.f, 0.f, 1.f, 1.f)}, //RT
//    {XMFLOAT3(+0.5f, -0.5f, 0.f), XMFLOAT4(1.f, 1.f, 0.f, 1.f)}  //RB
//    //BackFace Culling 고려

//    // Polygons
//};

    Vector3 pos    = { 0.f, 0.f, 0.f};

    float L = pos.x - size.x * 0.5f;
    float R = pos.x + size.x * 0.5f;
    float B = pos.y - size.y * 0.5f;
    float T = pos.y + size.y * 0.5f;


    vertices =
    {
        {Vector3(L, T, 0.f), Vector2(0.f, 0.f)}, //LT
        {Vector3(R, T, 0.f), Vector2(1.f, 0.f)}, //RT
        {Vector3(L, B, 0.f),  Vector2(0.f, 1.f)}, //LB
        {Vector3(R, B, 0.f),  Vector2(1.f, 1.f)}  //RB
    };

    indices =
    {
        0, 1, 2,
        2, 1, 3
    };


    vertexBuffer = new VertexBuffer(vertices);
    indexBuffer = new IndexBuffer(indices);

    vertexShader = new VertexShader(L"VertexTexture");
    pixelShader = new PixelShader(L"PixelTexture");

    worldBuffer = new MatrixBuffer();
    colorBuffer = new ColorBuffer();
}

Object::Object(wstring file, Vector2 uvStart, Vector2 uvEnd)
{
    texture = Texture::GetTexture(file);

    Vector3 pos = { 0.f, 0.f, 0.f };
    Vector2 size = texture->GetSize();

    float L = pos.x - size.x * 0.5f;
    float R = pos.x + size.x * 0.5f;
    float B = pos.y - size.y * 0.5f;
    float T = pos.y + size.y * 0.5f;


    vertices =
    {
        {Vector3(L, T, 0.f),  Vector2(uvStart.x, uvStart.y)}, //LT
        {Vector3(R, T, 0.f),  Vector2(  uvEnd.x, uvStart.y)}, //RT
        {Vector3(L, B, 0.f),  Vector2(uvStart.x, uvEnd.y)}, //LB
        {Vector3(R, B, 0.f),  Vector2(  uvEnd.x, uvEnd.y)}  //RB
    };

    indices =
    {
        0, 1, 2,
        2, 1, 3
    };

    vertexBuffer    = new VertexBuffer(vertices);
    indexBuffer     = new IndexBuffer(indices);

    vertexShader    = new VertexShader(L"VertexTexture");
    pixelShader     = new PixelShader(L"PixelTexture");

    worldBuffer     = new MatrixBuffer();
    colorBuffer     = new ColorBuffer();
}

Object::Object(Vector2 size, wstring file, Vector2 uvStart, Vector2 uvEnd)
{
    texture = Texture::GetTexture(file);

    Vector3 pos = { 0.f, 0.f, 0.f };

    float L = pos.x - size.x * 0.5f;
    float R = pos.x + size.x * 0.5f;
    float B = pos.y - size.y * 0.5f;
    float T = pos.y + size.y * 0.5f;


    vertices =
    {
        {Vector3(L, T, 0.f), Vector2(uvStart.x,    uvStart.y)}, //LT
        {Vector3(R, T, 0.f), Vector2(uvEnd.x,    uvStart.y)}, //RT
        {Vector3(L, B, 0.f),  Vector2(uvStart.x,      uvEnd.y)}, //LB
        {Vector3(R, B, 0.f),  Vector2(uvEnd.x,      uvEnd.y)}  //RB
    };

    indices =
    {
        0, 1, 2,
        2, 1, 3
    };

    vertexBuffer = new VertexBuffer(vertices);
    indexBuffer = new IndexBuffer(indices);

    vertexShader = new VertexShader(L"VertexTexture");
    pixelShader = new PixelShader(L"PixelTexture");

    worldBuffer = new MatrixBuffer();

    colorBuffer = new ColorBuffer();
}

Object::Object(Vector2 size, wstring file, UINT frameX, UINT frameY, UINT targetX, UINT targetY)
{
    UINT x = targetX - 1;
    UINT y = targetY - 1;

    Vector2 uvStart = { x / (float)frameX, y / (float)frameY };
    Vector2 uvEnd   = { (x + 1) / (float)frameX, (y + 1) / (float)frameY };

    texture = Texture::GetTexture(file);

    Vector3 pos = { 0.f, 0.f, 0.f };

    float L = pos.x - size.x * 0.5f;
    float R = pos.x + size.x * 0.5f;
    float B = pos.y - size.y * 0.5f;
    float T = pos.y + size.y * 0.5f;


    vertices =
    {
        {Vector3(L, T, 0.f), Vector2(uvStart.x,  uvStart.y)},   //LT
        {Vector3(R, T, 0.f), Vector2(uvEnd.x,    uvStart.y)},   //RT
        {Vector3(L, B, 0.f), Vector2(uvStart.x,  uvEnd.y)},     //LB
        {Vector3(R, B, 0.f), Vector2(uvEnd.x,    uvEnd.y)}      //RB
    };

    indices =
    {
        0, 1, 2,
        2, 1, 3
    };

    vertexBuffer = new VertexBuffer(vertices);
    indexBuffer = new IndexBuffer(indices);

    vertexShader = new VertexShader(L"VertexTexture");
    pixelShader = new PixelShader(L"PixelTexture");

    worldBuffer = new MatrixBuffer();

    colorBuffer = new ColorBuffer();

}

Object::Object(const Vector4& UDLR, const wstring& file, Vector2 uvStart, Vector2 uvEnd)
    :Object({ UDLR.w - UDLR.z, UDLR.x - UDLR.y }, file, uvStart, uvEnd)
{
    Vector2 size = { UDLR.w - UDLR.z, UDLR.x - UDLR.y };
    translation = { UDLR.z + size.x / 2.f, UDLR.y + size.y / 2.f };
}

Object::~Object()
{
    delete vertexBuffer;
    delete vertexShader;
    delete pixelShader;
    delete indexBuffer;
    delete worldBuffer;
    delete colorBuffer;

}

void Object::Render() // 모든 data 세팅은 "draw call전에 해야함
{
    SetData();
    
    DC->DrawIndexed(indices.size(), 0, 0);
}

void Object::SetData()
{
    vertexBuffer->SetBuffer();
    indexBuffer->SetBuffer();

    vertexShader->SetShader();
    pixelShader->SetShader();

    worldBuffer->SetData(world);
    worldBuffer->VSSetBuffer(0);

    colorBuffer->PSSetBuffer(0);

    if (texture)
        texture->SetPS();
}

