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
	
	// ������ �� owner�� ��ǳ�� ���� ȸ�����ֱ�
	Character* owner{}; // spawn�ÿ� �ڽ��� owener�� �޾ƿ� ����

};
