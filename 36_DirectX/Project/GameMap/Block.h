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
	Animation* destroyedAnim{}; // BlockManager에서 받아옴

	// Movable 관련
	Vector2 destination{};
	bool currentlyMoving{};

	// Bush Interaction 관련
	bool currentlyBushing{};
	float interactTime{};

};
