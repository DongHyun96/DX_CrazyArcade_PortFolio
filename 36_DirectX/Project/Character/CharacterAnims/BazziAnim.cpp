#include "Framework.h"
#include "BazziAnim.h"

BazziAnim::BazziAnim()
{
	//spawnAction = new Animation // TODO - 스폰 애님 통일 작업 및 생성 & EndEvent로 owner의 MainState를 Idle로 바꿔줘야 함

	winAction = new Animation(CELL_WORLD_SIZE, L"InGame/Characters/Bazzi/playerBubble.png", 6, 4, 24, 0.15f);
	winAction->SetPart(18, 19);

	Vector2 idleSize = { CELL_WORLD_SIZE.x + 60, CELL_WORLD_SIZE.y + 30 };

	idleActions[A_IDLE_UP] = new Animation(idleSize, L"InGame/Characters/Bazzi/playerMove.png", 5, 4);
	idleActions[A_IDLE_UP]->SetPart(0, 4);

	idleActions[A_IDLE_DOWN] = new Animation(idleSize, L"InGame/Characters/Bazzi/playerMove.png", 5, 4);
	idleActions[A_IDLE_DOWN]->SetPart(5, 9);

	idleActions[A_IDLE_RIGHT] = new Animation(idleSize, L"InGame/Characters/Bazzi/playerMove.png", 5, 4);
	idleActions[A_IDLE_RIGHT]->SetPart(10, 13);

	idleActions[A_IDLE_LEFT] = new Animation(idleSize, L"InGame/Characters/Bazzi/playerMove.png", 5, 4);
	idleActions[A_IDLE_LEFT]->SetPart(18, 15);

	bubbleActions[A_BUBBLE_CAPTURED] = new Animation(idleSize, L"InGame/Characters/Bazzi/playerBubble.png", 6, 4, 24, 0.3f);
	bubbleActions[A_BUBBLE_CAPTURED]->SetPart(0, 3, false);

	bubbleActions[A_BUBBLE_SAVED] = new Animation(idleSize, L"InGame/Characters/Bazzi/playerBubble.png", 6, 4, 24, 0.2f);
	bubbleActions[A_BUBBLE_SAVED]->SetPart(6, 8, false);

	bubbleActions[A_BUBBLE_DEAD] = new Animation(idleSize, L"InGame/Characters/Bazzi/playerBubble.png", 6, 4, 24, 0.15f);
	bubbleActions[A_BUBBLE_DEAD]->SetPart(12, 16, false);

	//  TODO -> 각 vehicle destroyed anim 넣어줘야 함 + EndEvent로 owner의 MainState를 Idle로 바꿔줘야 함

	Vector2 ridingSize = { CELL_WORLD_SIZE.x, CELL_WORLD_SIZE.y + 50 };

	for (UINT i = 0; i < 4; i++)
	{
		vector<Frame*> frames{};
		wstring path = L"InGame/Characters/Bazzi/BazziSpace" + to_wstring(i) + L".png";
		frames.push_back(new Frame(ridingSize, path));
		spaceActions[(SpaceAnimState)i] = new Animation(frames);
		frames.clear();
	}

	for (UINT i = 0; i < 4; i++)
	{
		vector<Frame*> frames{};
		wstring path = L"InGame/Characters/Bazzi/BazziOwl" + to_wstring(i) + L".png";
		frames.push_back(new Frame(ridingSize, path));
		owlActions[(OwlAnimState)i] = new Animation(frames);
		frames.clear();
	}

	for (UINT i = 0; i < 4; i++)
	{
		vector<Frame*> frames{};
		wstring path = L"InGame/Characters/Bazzi/BazziTurtle" + to_wstring(i) + L".png";
		frames.push_back(new Frame(ridingSize, path));
		turtleActions[(TurtleAnimState)i] = new Animation(frames);
		frames.clear();
	}

	curAction = idleActions[A_IDLE_DOWN]; // TODO -> Spawn으로 바꾸기

}

BazziAnim::~BazziAnim()
{
}