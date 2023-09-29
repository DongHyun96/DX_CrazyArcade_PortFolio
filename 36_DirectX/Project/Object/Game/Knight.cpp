#include "Framework.h"
#include "Knight.h"


Knight::Knight()
{
	translation = WIN_CENTER;

	AddAction();

	curAction = actions[state];
	curAction->Play();

	moveSpeed = 500.f;

	bodyCollider = new ColliderRect(Vector2(100, 100));
	bodyCollider->SetParent(this);
	bodyCollider->translation.y -= 50;
	bodyCollider->SetLabel("KnightBodyCollider");

	weaponCollider = new ColliderRect(Vector2(150, 150));
	weaponCollider->SetParent(bodyCollider);
	weaponCollider->translation.x = 100.f;
	weaponCollider->IsActive() = true;
	weaponCollider->SetLabel("KnightWeaponCollider");

	Load();
}

Knight::~Knight()
{
	Save();

	delete bodyCollider;
	delete weaponCollider;
}

void Knight::Update()
{
	bodyCollider->Update();
	weaponCollider->Update();


	moveDir = Vector2();

	if (KEY_DOWN(VK_SPACE))
		SetAction(ATTACK);

	if (KEY_PRESS('A'))
	{
		SetAction(WALK);

		moveDir.x -= 1;

		rotation.y = XM_PI;
	}

	if (KEY_PRESS('D'))
	{
		SetAction(WALK);

		moveDir.x += 1;

		rotation.y = 0;
	}

	if (KEY_PRESS('S'))
	{
		SetAction(WALK);

		moveDir.y -= 1;
	}

	if (KEY_PRESS('W'))
	{
		SetAction(WALK);

		moveDir.y += 1;
	}

	if (moveDir.Length() != 0)
		moveDir.Normalize();
	

	translation += moveDir * moveSpeed * Time::Delta();

	if (moveDir.Length() == 0 && state != ATTACK)
		SetAction(IDLE);

	if (KEY_DOWN(VK_SPACE))
	{
		SetAction(ATTACK);
		weaponCollider->IsActive() = true;
	}

	//__super::Update();
	Character::Update();
}

void Knight::Render()
{
	Character::Render();

	weaponCollider->Render();

	bodyCollider->Render();

	weaponCollider->Debug();
	bodyCollider->Debug();


}

void Knight::EndAttack()
{
	SetAction(IDLE);

	weaponCollider->IsActive() = false;
}

void Knight::Save()
{
	BinaryWriter data(L"KnightData");

	data.WriteData(bodyCollider->GetLabel());
	data.WriteData(bodyCollider->scale);
	data.WriteData(bodyCollider->rotation);
	data.WriteData(bodyCollider->translation);

	data.WriteData(weaponCollider->GetLabel());
	data.WriteData(weaponCollider->scale);
	data.WriteData(weaponCollider->rotation);
	data.WriteData(weaponCollider->translation);
}

void Knight::Load()
{
	BinaryReader data(L"KnightData");

	if (!data.Succeeded())
		return;

	bodyCollider->SetLabel(data.ReadString());
	bodyCollider->scale			= data.ReadVector2();
	bodyCollider->rotation		= data.ReadVector3();
	bodyCollider->translation	= data.ReadVector2();

	weaponCollider->SetLabel(data.ReadString());
	weaponCollider->scale		= data.ReadVector2();
	weaponCollider->rotation	= data.ReadVector3();
	weaponCollider->translation	= data.ReadVector2();


}

void Knight::AddAction()
{
	vector<Frame*> frames;

	for (UINT i = 0; i < 6; i++)
	{
		wstring str = L"Knight PNG/Knight_attack_0" + to_wstring(i + 1) + L".png";
		frames.push_back(new Frame(str));
	}

	actions.emplace(ATTACK, new Animation(frames));
	actions[ATTACK]->SetAll(false);
	//actions[ATTACK]->SetEndEvent(bind(&Character::SetAction, this, IDLE));
	actions[ATTACK]->SetEndEvent(bind(&Knight::EndAttack, this));

	frames.clear();

	//////////////////////////////////////////////////////////////////////////////////////////

	for (UINT i = 0; i < 6; i++)
	{
		wstring str = L"Knight PNG/Knight_idle_0" + to_wstring(i + 1) + L".png";
		frames.push_back(new Frame(str));
	}

	actions.emplace(IDLE, new Animation(frames));

	frames.clear();

	//////////////////////////////////////////////////////////////////////////////////////////

	for (UINT i = 0; i < 6; i++)
	{
		wstring str = L"Knight PNG/Knight_walk_0" + to_wstring(i + 1) + L".png";
		frames.push_back(new Frame(str));
	}

	actions.emplace(WALK, new Animation(frames));

	frames.clear();
}

