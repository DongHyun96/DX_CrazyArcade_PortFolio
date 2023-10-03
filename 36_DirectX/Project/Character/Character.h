#pragma once

class CharacterAnim;

#define SPEED_BASE 50.f

enum CharacterType
{
	BAZZI,
	DAO,
	CAPPI,
	MARID
};

enum CharacterState
{
	C_SPAWN,

	C_IDLE,

	C_SPACECRAFT,
	C_OWL,
	C_TURTLE,

	C_CAPTURED,

	C_RETURN_IDLE,

	C_DEAD
};

class Character : public Transform // Character Transform �� ��ü�� Animation �������� ��ġ������ ��
{
public:
	Character(const CharacterType& cType);

	virtual ~Character();

	virtual void Update();
	virtual void Render();

	void SetAction(int state);

	virtual void Move() = 0;

	void SetCharacterState(const CharacterState& state) { this->mainState = state; }

protected:

	VertexShader*						vertexShader{};
	PixelShader*						pixelShader{};

	MatrixBuffer*						worldBuffer{};


	Collider*							body{};
	Vector2								velocity{};

	CharacterState						mainState{C_IDLE};
	

	CharacterAnim*						actionHandler;
	
	/*
	�ӵ� / ��ǳ�� / ���ٱ�
	*/
	UINT speedLvMin{};
	UINT speedLvMax{};
	UINT balloonCntMin{};
	UINT balloonCntMax{};
	UINT streamLvMin{};
	UINT streamLvMax{};

	UINT speedLv{ 1 };
	UINT balloonCnt{ 1 };
	UINT streamLv{ 1 };

};
