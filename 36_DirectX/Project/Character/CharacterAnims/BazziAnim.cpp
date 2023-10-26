#include "Framework.h"
#include "BazziAnim.h"

BazziAnim::BazziAnim(ColliderRect* parent)
	:CharacterAnim(parent)
{
	vector<Frame*> frames{};

	Vector2 winActionSize = { CELL_WORLD_SIZE.x - 5, CELL_WORLD_SIZE.y + 15 };

	for (UINT i = 0; i < 4; i++)
	{
		wstring path = L"InGame/Characters/Bazzi/Win/" + to_wstring(i) + L".png";
		frames.push_back(new Frame(winActionSize, path));
	}

	winAction = new Animation(frames, 0.2f);
	frames.clear();


	//Vector2 idleSize = CELL_WORLD_SIZE;

	//idleActions[A_IDLE_UP] = new Animation(idleSize, L"InGame/Characters/Bazzi/playerMove.png", 5, 4);
	//idleActions[A_IDLE_UP]->SetPart(0, 4);

	//idleActions[A_IDLE_DOWN] = new Animation(idleSize, L"InGame/Characters/Bazzi/playerMove.png", 5, 4);
	//idleActions[A_IDLE_DOWN]->SetPart(5, 9);

	//idleActions[A_IDLE_RIGHT] = new Animation(idleSize, L"InGame/Characters/Bazzi/playerMove.png", 5, 4);
	//idleActions[A_IDLE_RIGHT]->SetPart(10, 13);

	//idleActions[A_IDLE_LEFT] = new Animation(idleSize, L"InGame/Characters/Bazzi/playerMove.png", 5, 4);
	//idleActions[A_IDLE_LEFT]->SetPart(18, 15);

	Vector2 idleSize = { CELL_WORLD_SIZE.x - 5, CELL_WORLD_SIZE.y + 15 };

	for (UINT i = 0; i < 5; i++)
	{
		wstring path = L"InGame/Characters/Bazzi/BazziDownWalk_" + to_wstring(i) + L".png";
		frames.push_back(new Frame(idleSize, path));
	}

	idleActions[A_DOWN] = new Animation(frames, 0.1f);
	frames.clear();

	for (UINT i = 0; i < 5; i++)
	{
		wstring path = L"InGame/Characters/Bazzi/BazziUpWalk_" + to_wstring(i) + L".png";
		frames.push_back(new Frame(idleSize, path));
	}

	idleActions[A_UP] = new Animation(frames, 0.1f);
	frames.clear();

	for (UINT i = 0; i < 5; i++)
	{
		wstring path = L"InGame/Characters/Bazzi/BazziLeftWalk_" + to_wstring(i) + L".png";
		frames.push_back(new Frame(idleSize, path));
	}

	idleActions[A_LEFT] = new Animation(frames, 0.1f);
	frames.clear();

	for (UINT i = 0; i < 5; i++)
	{
		wstring path = L"InGame/Characters/Bazzi/BazziRightWalk_" + to_wstring(i) + L".png";
		frames.push_back(new Frame(idleSize, path));
	}

	idleActions[A_RIGHT] = new Animation(frames, 0.1f);
	frames.clear();

	Vector2 bubbleSize = { CELL_WORLD_SIZE.x + 50, CELL_WORLD_SIZE.y + 50 };

	bubbleActions[A_BUBBLE_CAPTURED] = new Animation(bubbleSize, L"InGame/Characters/Bazzi/playerBubble.png", 6, 4, 24, 2.f);
	bubbleActions[A_BUBBLE_CAPTURED]->SetPart(0, 3, false);

	bubbleActions[A_BUBBLE_SAVED] = new Animation(bubbleSize, L"InGame/Characters/Bazzi/playerBubble.png", 6, 4, 24, 0.2f);
	bubbleActions[A_BUBBLE_SAVED]->SetPart(6, 8, false);

	bubbleActions[A_BUBBLE_DEAD] = new Animation(bubbleSize, L"InGame/Characters/Bazzi/playerBubble.png", 6, 4, 24, 0.15f);
	bubbleActions[A_BUBBLE_DEAD]->SetPart(12, 16, false);


	Vector2 spaceSize = { CELL_WORLD_SIZE.x, CELL_WORLD_SIZE.y + 50 };
	Vector2 owlSize = { CELL_WORLD_SIZE.x, CELL_WORLD_SIZE.y + 30 };
	for (UINT i = 0; i < 4; i++)
	{
		vector<Frame*> frames{};
		wstring path = L"InGame/Characters/Bazzi/BazziSpace" + to_wstring(i) + L".png";
		frames.push_back(new Frame(spaceSize, path));
		spaceActions[(CharacterAnimDir)i] = new Animation(frames);
		frames.clear();
	}

	for (UINT i = 0; i < 4; i++)
	{
		vector<Frame*> frames{};
		for (UINT j = 0; j < 2; j++)
		{
			wstring path = L"InGame/Characters/Bazzi/BazziOwl" + to_wstring(i) + to_wstring(j) + L".png";
			frames.push_back(new Frame(spaceSize, path));
		}
		owlActions[(CharacterAnimDir)i] = new Animation(frames);
		frames.clear();
	}

	for (UINT i = 0; i < 4; i++)
	{
		vector<Frame*> frames{};
		wstring path = L"InGame/Characters/Bazzi/BazziTurtle" + to_wstring(i) + L".png";
		frames.push_back(new Frame(spaceSize, path));
		turtleActions[(CharacterAnimDir)i] = new Animation(frames);
		frames.clear();
	}

	curAction = idleActions[A_DOWN];

	// 애니메이션 바닥면 parent의 body에 맞추기

}

BazziAnim::~BazziAnim()
{
}