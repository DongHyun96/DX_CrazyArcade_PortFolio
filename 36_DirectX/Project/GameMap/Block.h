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
	// texWorldSize에 디폴트로 y offset을 조금 두어 머리부분이 뒤로 조금 넘어가게끔 미세하게 조정할 것임
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
	Animation* destroyedAnim{}; // BlockManager에서 받아옴

};
