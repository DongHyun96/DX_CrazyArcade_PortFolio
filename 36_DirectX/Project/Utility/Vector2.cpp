#include "Framework.h"
#include "Vector2.h"

Vector2::Vector2()
	:XMFLOAT2(0, 0)
{
}

Vector2::Vector2(float x, float y)
	:XMFLOAT2(x, y)
{
}

float Vector2::Length() const
{
	return sqrtf(powf(x, 2) + powf(y, 2));
}

Vector2 Vector2::GetNormal() const
{
	if (Length() == 0)
		return *this;

	//assert(Length() != 0);

	return *this / Length();
}

void Vector2::Normalize()
{
	*this = GetNormal();
}

float Vector2::Dot(const Vector2& v1, const Vector2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Vector2::Cross(const Vector2& v1, const Vector2& v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

float Vector2::Distance(const Vector2& p1, const Vector2& p2)
{
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;

	float distance = sqrtf(x * x + y * y);

	return distance;
}

Vector2 Vector2::Lerp(const Vector2& start, const Vector2& end, const float& factor)
{
	return start + (end - start) * factor;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(this->x - other.x, this->y - other.y);
}

Vector2 Vector2::operator*(const float& value) const
{
	return Vector2(this->x * value, this->y * value);
}

Vector2 Vector2::operator/(const float& value) const
{
	return Vector2(this->x / value, this->y / value);
}

bool Vector2::operator==(const Vector2& other) const
{
	return this->x == other.x && this->y == other.y;
}

void Vector2::operator+=(const Vector2& other)
{
	this->x += other.x;
	this->y += other.y;
}

void Vector2::operator-=(const Vector2& other)
{
	this->x -= other.x;
	this->y -= other.y;
}

void Vector2::operator*=(const float& value)
{
	this->x *= value;
	this->y *= value;
}

void Vector2::operator/=(const float& value)
{
	this->x /= value;
	this->y /= value;
}

Vector2 Vector2::operator*(const Matrix& value) const
{
	XMVECTOR point = XMLoadFloat2(this);

	// XMVector2TransformNormal -> return하는 동차좌표의 w값이 point, vector냐에 따라 달라짐
	point = XMVector2TransformCoord(point, value);

	Vector2 position;

	XMStoreFloat2(&position, point);

	return position;
}

void Vector2::operator*=(const Matrix& value)
{
	XMVECTOR point = XMLoadFloat2(this);

	// XMVector2TransformNormal -> return하는 동차좌표의 w값이 point, vector냐에 따라 달라짐
	point = XMVector2TransformCoord(point, value);

	Vector2 position;

	XMStoreFloat2(&position, point);

	*this = position;
}

bool Vector2::IsBetween(const Vector2& factor, const Vector2& v1, const Vector2& v2)
{
	// Factor가 들어가는 순서도 일정해야 함
	return Cross(factor, v1) * Cross(factor, v2) < 0;
}
