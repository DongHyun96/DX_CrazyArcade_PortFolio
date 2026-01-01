#include "Framework.h"
#include "MaridAnim.h"


MaridAnim::MaridAnim(ColliderRect* parent)
	:CharacterAnim(parent)
{
	vector<Frame*> frames{};

	Vector2 winActionSize = { CELL_WORLD_SIZE.x - 5, CELL_WORLD_SIZE.y + 15 };

	for (UINT i = 0; i < 4; i++)
	{
		wstring path = L"InGame/Characters/Marid/Win/" + to_wstring(i) + L".png";
		frames.push_back(new Frame(winActionSize, path));
	}

	winAction = new Animation(frames, 0.2f);
	frames.clear();

	Vector2 idleSize = { CELL_WORLD_SIZE.x + 5, CELL_WORLD_SIZE.y + 25 };

	for (UINT i = 0; i < 5; i++)
	{
		wstring path = L"InGame/Characters/Marid/MaridDownWalk_" + to_wstring(i) + L".png";
		frames.push_back(new Frame(idleSize, path));
	}

	idleActions[A_DOWN] = new Animation(frames);
	frames.clear();

	for (UINT i = 0; i < 5; i++)
	{
		wstring path = L"InGame/Characters/Marid/MaridUpWalk_" + to_wstring(i) + L".png";
		frames.push_back(new Frame(idleSize, path));
	}

	idleActions[A_UP] = new Animation(frames);
	frames.clear();

	for (UINT i = 0; i < 5; i++)
	{
		wstring path = L"InGame/Characters/Marid/MaridLeftWalk_" + to_wstring(i) + L".png";
		frames.push_back(new Frame(idleSize, path));
	}

	idleActions[A_LEFT] = new Animation(frames);
	frames.clear();

	for (UINT i = 0; i < 5; i++)
	{
		wstring path = L"InGame/Characters/Marid/MaridRightWalk_" + to_wstring(i) + L".png";
		frames.push_back(new Frame(idleSize, path));
	}

	idleActions[A_RIGHT] = new Animation(frames);
	frames.clear();

	Vector2 bubbleSize = { CELL_WORLD_SIZE.x + 35, CELL_WORLD_SIZE.y + 35 };
	//Vector2 idleSize = { CELL_WORLD_SIZE.x - 5, CELL_WORLD_SIZE.y + 15 };

	for (UINT i = 0; i < 4; i++)
	{
		wstring path = L"InGame/Characters/Marid/Bubble/Marid bubble " + to_wstring(i + 1) + L".png";
		frames.push_back(new Frame(bubbleSize, path));
	}

	bubbleActions[A_BUBBLE_CAPTURED] = new Animation(frames, 2.f);
	bubbleActions[A_BUBBLE_CAPTURED]->SetLoop(false);
	frames.clear();

	for (UINT i = 0; i < 5; i++)
	{
		wstring path = L"InGame/Characters/Marid/Bubble/Marid bubble dead " + to_wstring(i + 1) + L".png";
		frames.push_back(new Frame(bubbleSize, path));
	}

	bubbleActions[A_BUBBLE_DEAD] = new Animation(frames, 0.2f);
	bubbleActions[A_BUBBLE_DEAD]->SetLoop(false);
	frames.clear();

	for (UINT i = 0; i < 3; i++)
	{
		wstring path = L"InGame/Characters/Marid/Bubble/Marid bubble saved " + to_wstring(i + 1) + L".png";
		frames.push_back(new Frame(bubbleSize, path));
	}

	bubbleActions[A_BUBBLE_SAVED] = new Animation(frames, 0.15f);
	bubbleActions[A_BUBBLE_SAVED]->SetLoop(false);
	frames.clear();

	Vector2 spaceSize = { CELL_WORLD_SIZE.x, CELL_WORLD_SIZE.y + 50 };
	Vector2 owlSize = { CELL_WORLD_SIZE.x, CELL_WORLD_SIZE.y + 30 };

	for (UINT i = 0; i < 4; i++)
	{
		vector<Frame*> frames{};
		wstring path = L"InGame/Characters/Marid/Space" + to_wstring(i) + L".png";
		frames.push_back(new Frame(spaceSize, path));
		spaceActions[(CharacterAnimDir)i] = new Animation(frames);
		frames.clear();
	}

	for (UINT i = 0; i < 4; i++)
	{
		vector<Frame*> frames{};
		for (UINT j = 0; j < 2; j++)
		{
			wstring path = L"InGame/Characters/Marid/Owl" + to_wstring(i) + to_wstring(j) + L".png";
			frames.push_back(new Frame(spaceSize, path));
		}
		owlActions[(CharacterAnimDir)i] = new Animation(frames);
		frames.clear();
	}

	for (UINT i = 0; i < 4; i++)
	{
		vector<Frame*> frames{};
		wstring path = L"InGame/Characters/Marid/Turtle" + to_wstring(i) + L".png";
		frames.push_back(new Frame(spaceSize, path));
		turtleActions[(CharacterAnimDir)i] = new Animation(frames);
		frames.clear();
	}

	curAction = idleActions[A_DOWN];
}

MaridAnim::~MaridAnim()
{
}