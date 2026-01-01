#include "Framework.h"
#include "ColliderRect.h"


ColliderRect::ColliderRect(Vector2 size)
    :size(size)
{
    SetVertex();
}

ColliderRect::~ColliderRect()
{
}

void ColliderRect::SetVertex()
{
    Vector3 pos = { 0.f, 0.f, 0.f };

    float L = pos.x - size.x * 0.5f;
    float R = pos.x + size.x * 0.5f;
    float B = pos.y - size.y * 0.5f;
    float T = pos.y + size.y * 0.5f;


    vertices =
    {
        {Vector3(L, T, 0.f) },      //LT
        {Vector3(R, T, 0.f) },      //RT
        {Vector3(R, B, 0.f) },      //RB
        {Vector3(L, B, 0.f) },      //LB
        {Vector3(L, T, 0.f) },      //LT
    };

    vertexBuffer = new VertexBuffer(vertices);
}

bool ColliderRect::OBBCollision(const Vector2& point, ColliderHolder* owner)
{
    if (!isActive) return false;

    Matrix invWorld = XMMatrixInverse(nullptr, this->world);

    Vector2 invPoint = point * invWorld;

    if (abs(invPoint.x) < this->size.x * 0.5f && abs(invPoint.y) < this->size.y * 0.5f) // Collided
    {
        if (!owner) return true;

        if (enteredPointOwners.find(owner) == enteredPointOwners.end()) // new Point owner entered
        {
            enteredPointOwners.insert(owner);
            if (PointEnterEvent) PointEnterEvent(owner);
        }
        else // existing Point owner entered
        {
            if (PointStayEvent) PointStayEvent(owner);
        }

        return true;
    }
    else // Not Collided
    {
        if (!owner) return false;

        auto targetIt = enteredPointOwners.find(owner);

        if (targetIt != enteredPointOwners.end())
        {
            enteredPointOwners.erase(targetIt);
            if (PointExitEvent) PointExitEvent(owner);
        }
        
        return false;
    }
}

bool ColliderRect::OBBCollision(ColliderRect* rect, ColliderHolder* owner)
{
    if (!isActive) return false;

    Vector2 distance = this->globalPosition - rect->globalPosition;

    Vector2 axes[4] =
    {
        this->right,
        this->up,
        rect->right,
        rect->up
    };

    Vector2 vectors[4] =
    {
        axes[0] * (this->GlobalSize().x * 0.5f),
        axes[1] * (this->GlobalSize().y * 0.5f),
        axes[2] * (rect->GlobalSize().x * 0.5f),
        axes[3] * (rect->GlobalSize().y * 0.5f)
    };

    for (UINT i = 0; i < 4; i++)
    {
        float sum{};

        for (UINT j = 0; j < 4; j++)
            sum += abs(Vector2::Dot(axes[i], vectors[j]));

        if (sum <= abs(Vector2::Dot(axes[i], distance)))
        {
            if (!owner) return false;

            auto targetIt = enteredBodies.find(rect);

            if (targetIt != enteredBodies.end())
            {
                enteredBodies.erase(targetIt);
                if(RectExitEvent) RectExitEvent(rect, owner);
            }
            return false;
        }
    }

    if (!owner) return true;
 
    if (enteredBodies.find(rect) == enteredBodies.end()) // new rect owner entered
    {
        enteredBodies.insert(rect);

        if (RectEnterEvent) RectEnterEvent(rect, owner);
    }
    else // Existing rect owner collided
    {
        if (RectStayEvent) RectStayEvent(rect, owner);
    }

    return true;
}

bool ColliderRect::OBBCollision(ColliderCircle* other)
{
    if (!isActive)  return false;

    Vector2 distance = this->globalPosition - other->GlobalPosition();

    Vector2 axes[2] =
    {
        this->right,
        this->up
    };

    float lengthX = abs(Vector2::Dot(axes[0], distance));
    float lengthY = abs(Vector2::Dot(axes[1], distance));

    float radius = other->Radius();

    if (lengthX >= this->GlobalSize().x * 0.5f + radius) return false;
    if (lengthY >= this->GlobalSize().y * 0.5f + radius) return false;

    if (lengthX < this->GlobalSize().x * 0.5f) return true;
    if (lengthY < this->GlobalSize().y * 0.5f) return true;

    float x = lengthX - this->GlobalSize().x * 0.5f;
    float y = lengthY - this->GlobalSize().y * 0.5f;

    float edgeToCircle = sqrt(pow(x, 2) + pow(y, 2));

    return edgeToCircle < radius;
}

bool ColliderRect::AABBCollision(const Vector2& point, ColliderHolder* owner)
{
    if (!isActive)  return false;

    float x = abs(point.x - this->GlobalPosition().x);
    float y = abs(point.y - this->GlobalPosition().y);

    if (x < this->GlobalSize().x * 0.5f && y < this->GlobalSize().y * 0.5f)
    {
        // Collided
        if (!owner) return true;

        if (enteredPointOwners.find(owner) == enteredPointOwners.end()) // new Point owner entered
        {
            enteredPointOwners.insert(owner);
            if (PointEnterEvent) PointEnterEvent(owner);
        }
        else // existing Point owner entered
        {
            if (PointStayEvent) PointStayEvent(owner);
        }

        return true;
    }

    if (!owner) return false;

    auto targetIt = enteredPointOwners.find(owner);

    if (targetIt != enteredPointOwners.end())
    {
        enteredPointOwners.erase(targetIt);
        if (PointExitEvent) PointExitEvent(owner);
    }

    return false;
}

bool ColliderRect::AABBCollision(ColliderRect* rect, ColliderHolder* owner)
{
    if (!isActive)  return false;

    float x = abs(this->GlobalPosition().x - rect->GlobalPosition().x);
    float y = abs(this->GlobalPosition().y - rect->GlobalPosition().y);

    float sizeX = (this->GlobalSize().x + rect->GlobalSize().x) * 0.5f;
    float sizeY = (this->GlobalSize().y + rect->GlobalSize().y) * 0.5f;

    if (x < sizeX && y < sizeY) // Collided
    {
        if (!owner) return true;

        if (enteredBodies.find(rect) == enteredBodies.end()) // new rect owner entered
        {
            enteredBodies.insert(rect);

            if (RectEnterEvent) RectEnterEvent(rect, owner);
        }
        else // Existing rect owner collided
        {
            if (RectStayEvent) RectStayEvent(rect, owner);
        }

        return true;
    }

    // Not collided
    if (!owner) return false;

    auto targetIt = enteredBodies.find(rect);

    if (targetIt != enteredBodies.end())
    {
        enteredBodies.erase(targetIt);
        if (RectExitEvent) RectExitEvent(rect, owner);
    }

    return false;
}

void ColliderRect::SetColliderRect(const Vector4& UDLR)
{
    size = { UDLR.w - UDLR.z, UDLR.x - UDLR.y };
    translation = { UDLR.z + size.x / 2.f, UDLR.y + size.y / 2.f };
}
