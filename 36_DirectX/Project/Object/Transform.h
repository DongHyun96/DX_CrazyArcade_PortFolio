#pragma once

class Transform
{
public:

	Transform();

	virtual ~Transform();
	
	void Debug();

	virtual void Update();
	void UpdateWorld();

	void UpdateZDepthToY();

	void SetParent(Transform* parent) { this->parent = parent; }

	Matrix GetWorld() const { return world; }

	Matrix GetT() const { return T; }

	void SetPivot(const Vector2& pivot) { this->pivot = pivot; }

	void SetLabel(string label) { this->label = label; }
	string GetLabel() const { return label; }


	Vector2 GlobalPosition() const { return globalPosition; }
	Vector2 GlobalScale()	 const { return globalScale; }

public:

	Vector2 scale		= { 1.f, 1.f };
	Vector3 rotation	= { 0.f, 0.f, 0.f };
	Vector2 translation	= { 0.f, 0.f };
	float zDepth{};

protected:

	Matrix		S, R, T;

	Matrix		world{};

	Transform*	parent{};

	Vector2		pivot{};

	string label{};

	Vector2 globalScale{};
	Vector2 globalPosition{};

	Vector2 right{}, up{};
};
