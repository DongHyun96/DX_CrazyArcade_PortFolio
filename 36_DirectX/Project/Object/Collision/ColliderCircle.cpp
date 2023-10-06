#include "Framework.h"
#include "ColliderCircle.h"


ColliderCircle::ColliderCircle(float radius)
    :radius(radius)
{
    SetVertex();
}

ColliderCircle::~ColliderCircle()
{
}

void ColliderCircle::SetVertex()
{
    for (UINT i = 0; i < VERTEX_COUNT + 1; i++)
    {
        float angle = XM_2PI / VERTEX_COUNT * i;

        Vertex vertex;

        vertex.pos =
        {
            radius * cosf(angle),
            radius * sinf(angle),
            0.f
        };

        vertices.push_back(vertex);
    }

    vertexBuffer = new VertexBuffer(vertices);
}

bool ColliderCircle::OBBCollision(const Vector2& point, Transform* owner)
{
    float distance = (point - globalPosition).Length();

    return distance <= Radius();
}

bool ColliderCircle::OBBCollision(ColliderRect* other, Transform* owner)
{
    return other->OBBCollision(this);
}

bool ColliderCircle::OBBCollision(ColliderCircle* other)
{
    float distance = (other->GlobalPosition() - this->globalPosition).Length();

    return distance <= this->Radius() + other->Radius();
}
