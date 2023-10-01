#pragma once

#define Y_OFFSET 20.f

struct BlockProperty
{
	bool breakable{};
	bool movable{};
	bool hidable{};
};

class Block
{
public:
	// texWorldSize�� ����Ʈ�� y offset�� ���� �ξ� �Ӹ��κ��� �ڷ� ���� �Ѿ�Բ� �̼��ϰ� ������ ����
	Block
	(
		Util::Coord boardXY, wstring texFile, 
		Util::Coord frameXY  = {1, 1},
		Util::Coord targetXY = {1, 1},
		Vector2 texWorldSize = Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW),
		BlockProperty bProp = {}
	);

	~Block();

	void Update();
	void Render();

	void PlayBushInteraction();

	void Move(const UINT& destBoardCoordX, const UINT& destBoardCoordY);
	void Move(const Util::Coord& destCoord);

	void ApplyDamage();

	void Debug();
	void SetLabel(const string& label) { this->label = label; }

public:

	Collider* GetBody() { return rectBody; }
	Vector2 GetTranslation() const { return rectBody->translation; }
	Util::Coord GetBoardPos() const { return boardPos; }
	bool& IsActive() { return isActive; }

private:

	bool Move(Vector2 destination);
	void Move();

	void HandleBushInteract();


private:

private:
	
	string label{};

	Util::Coord	boardPos{};

	Collider*	rectBody{};
	Object*		texObj{};

	bool isActive = true;

	bool breakable{};
	bool movable{};
	bool hidable{};

	UINT hp{};
	Animation* destroyedAnim{}; // BlockManager���� �޾ƿ�

	// Movable ����
	Vector2 destination{};
	bool currentlyMoving{};

	// Bush Interaction ����
	bool currentlyBushing{};
	float interactTime{};

};
