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
		pair<UINT, UINT> boardXY, wstring texFile, 
		pair<UINT, UINT> frameXY = {1, 1},
		pair<UINT, UINT> targetXY = {1, 1},
		Vector2 texWorldSize = Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW),
		BlockProperty bProp = {}
	);

	~Block();

	void Update();
	void Render();

	void PlayBushInteraction();

	void Move(Vector2 destination);

	void ApplyDamage();

	bool& IsActive() { return isActive; }

private:

	Collider* rectBody{};
	Object* texObj{};

	bool isActive = true;

	bool breakable{};
	bool movable{};
	bool hidable{};

	UINT hp{};
	Animation* destroyedAnim{}; // BlockManager���� �޾ƿ�

};
