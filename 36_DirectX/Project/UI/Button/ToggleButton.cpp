#include "Framework.h"
#include "ToggleButton.h"

map<string, vector<ToggleButton*>> ToggleButton::toggleGroups{};

ToggleButton::ToggleButton(const string& toggleGroupKey, const Vector4& UDLR, const wstring& downFile, const byte& customKey, const wstring& upFile, const wstring& hoverFile)
	:Button(UDLR, downFile, upFile, hoverFile), myToggleKey(toggleGroupKey), customKey(customKey)
{
	if (toggleGroups.find(toggleGroupKey) == toggleGroups.end()) // �ű� ���� (ù ��ư�� ���� ���·� �� ����)
		this->state = DOWN;

	toggleGroups[toggleGroupKey].push_back(this);
}

ToggleButton::~ToggleButton()
{
	// �θ�ܿ��� ��� ����ó��
}

void ToggleButton::Update()
{
	body->Update();

	for (auto& p : texMap)
		if (p.second) p.second->Update();
	
	// Down ���¸� Ǯ �� �ִ� ���� ������ �ٸ� ��ư�� ������ ��


	if (body->AABBCollision(mousePos))
	{
		body->SetColor(1, 0, 0);

		if (state != DOWN)
		{
			if (state != HOVER) SOUND->Play(hoverSound, 1.f);
			state = HOVER;
		}

		if (KEY_PRESS(customKey))
		{
			if (state != DOWN) SOUND->Play("Click", 1.f);
			state = DOWN;
		}

		if (KEY_UP(customKey))
		{

			for (ToggleButton* button : toggleGroups[myToggleKey])
			{
				if (button == this) continue;

				if (button->state == DOWN)
				{
					button->state = UP;
					break;
				}
			}

			if (Event) Event();
			if (CharacterSelectEvent) CharacterSelectEvent(RANDOM, P1); // ������ param�� ��� x
		}
	}
	else if (state != DOWN)
	{
		body->SetColor(0, 1, 0);
		state = UP;
	}
}

void ToggleButton::Render()
{
	body->Render();

	if (texMap[state]) texMap[state]->Render();

}
