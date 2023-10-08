#pragma once


class Balloon : public Transform
{
public:
	Balloon();
	~Balloon();

	void Update();
	void Render();

	bool Spawn(const Util::Coord& spawnCoord, Character* owner);

	void Explode();

	void OnColliderRectEnter(ColliderRect*	targetCollider, Transform* owner);

public:

	bool& Active() { return isActive; }
	ColliderRect* GetBody() const { return body; }
	
	void SetVisible(const bool& visible) { this->visible = visible; }

	static vector<Vector2> GetActiveBalloonPositions() { return activeBalloonPositions; }


private:

	bool Spawn(const Vector2& spawnPos);
	

private:

	Util::Coord spawnCoord{};

	static vector<Vector2> activeBalloonPositions;

	bool isActive{};
	bool visible{ true };

	ColliderRect*	body{};
	Animation*		balloonAnim{};


	float		explodeTime{};
	const float EXPLODE_TIME_LIMIT{ 1.5f };


	ColorBuffer*	colorBuffer{};
	VertexShader*	vertexShader{};
	PixelShader*	pixelShader{};

	MatrixBuffer*	worldBuffer{};

private:
	
	// 터졌을 때 owner의 물풍선 개수 회복해주기
	Character* owner{}; // spawn시에 자신의 owener를 받아올 것임

};
