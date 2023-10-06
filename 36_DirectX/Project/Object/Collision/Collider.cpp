#include "Framework.h"
#include "Collider.h"


Collider::Collider()
{
	vertexShader	= new VertexShader(L"VertexLine");
	pixelShader		= new PixelShader(L"PixelLine");

	worldBuffer		= new MatrixBuffer();
	colorBuffer		= new ColorBuffer();
	colorBuffer->SetData(Vector4(0, 1, 0, 1));

	// VertexBuffer는 자식에서 모양이 정해지기 때문에 자식에서 만듦
}

Collider::~Collider()
{
	delete vertexBuffer;

	delete vertexShader;
	delete pixelShader;	

	delete worldBuffer;	
	delete colorBuffer;	
}

void Collider::Render()
{
	if (hiddenInGame)
		return;

	if (!isActive)
		return;

	vertexBuffer->SetBuffer(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	vertexShader->SetShader();
	pixelShader->SetShader();

	worldBuffer->SetData(world);
	worldBuffer->VSSetBuffer(0);
	colorBuffer->PSSetBuffer(0);

	DC->Draw(vertices.size(), 0);
}

bool Collider::OBBCollision(Collider* other)
{
	if (!isActive)
		return false;

	ColliderRect* rect = dynamic_cast<ColliderRect*>(other);

	if (rect)
		return OBBCollision(rect);
	else
	{
		ColliderCircle* circle = dynamic_cast<ColliderCircle*>(other);

		return OBBCollision(circle);
	}

	return false;
}
