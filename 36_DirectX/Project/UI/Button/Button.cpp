#include "Framework.h"
#include "Button.h"



Button::Button(const wstring& file, const UINT& frameX, const UINT& frameY, UINT nFrames)
{
	if (nFrames == 0)
		nFrames = frameX * frameY;

	switch (nFrames)
	{
	case 3:
		for (UINT i = 0; i < nFrames; i++)
		{
			UINT x = i % frameX; // 0, 1, 2, 3
			UINT y = i / frameX; // 0, 0, 0, 0, 1, 1, 1, 1

			Vector2 uvStart = { x / (float)frameX, y / (float)frameY };
			Vector2 uvEnd = { (x + 1) / (float)frameX, (y + 1) / (float)frameY };

			texMap[(State)i] = new Object(file, uvStart, uvEnd);
		}
		break;
	case 2:
		for (UINT i = 0; i < nFrames; i++)
		{
			UINT x = i % frameX; // 0, 1, 2, 3
			UINT y = i / frameX; // 0, 0, 0, 0, 1, 1, 1, 1

			Vector2 uvStart = { x / (float)frameX, y / (float)frameY };
			Vector2 uvEnd = { (x + 1) / (float)frameX, (y + 1) / (float)frameY };

			texMap[(State)i] = new Object(file, uvStart, uvEnd);
		}

		texMap[DOWN] = texMap[UP];
		break;
	case 1:
		// TODO - 시간되면 Implement
		return;
	default:
		break;
	}

	body = new ColliderRect(texMap[UP]->GetSize());
	body->zDepth = -0.1f;

	for (auto& p : texMap)
		p.second->SetParent(body);
}

Button::Button(const Vector2& size, const wstring& file, const UINT& frameX, const UINT& frameY, UINT nFrames)
{													 
	if (nFrames == 0) nFrames = frameX * frameY;

	switch (nFrames)
	{
	case 3:
		for (UINT i = 0; i < nFrames; i++)
		{
			UINT x = i % frameX; // 0, 1, 2, 3
			UINT y = i / frameX; // 0, 0, 0, 0, 1, 1, 1, 1

			Vector2 uvStart = { x / (float)frameX, y / (float)frameY };
			Vector2 uvEnd = { (x + 1) / (float)frameX, (y + 1) / (float)frameY };

			texMap[(State)i] = new Object(size, file, uvStart, uvEnd);
		}
		break;
	case 2:
		for (UINT i = 0; i < nFrames; i++)
		{
			UINT x = i % frameX; // 0, 1, 2, 3
			UINT y = i / frameX; // 0, 0, 0, 0, 1, 1, 1, 1

			Vector2 uvStart = { x / (float)frameX, y / (float)frameY };
			Vector2 uvEnd = { (x + 1) / (float)frameX, (y + 1) / (float)frameY };

			texMap[(State)i] = new Object(size, file, uvStart, uvEnd);
		}

		texMap[DOWN] = texMap[UP];
		break;
	case 1:
		// TODO - 시간되면 Implement
		return;
	default:
		break;
	}

	body = new ColliderRect(size);
	body->zDepth = -0.1f;

	for (auto& p : texMap)
		if (p.second) p.second->SetParent(body);
		
}												 

// x,y,z,w
Button::Button(const Vector4& UDLR, const wstring& file, const UINT& frameX, const UINT& frameY, UINT nFrames)
	:Button({ UDLR.w - UDLR.z, UDLR.x - UDLR.y }, file, frameX, frameY, nFrames)
{
	Vector2 size		= { UDLR.w - UDLR.z, UDLR.x - UDLR.y };
	body->translation	= { UDLR.z + size.x / 2.f, UDLR.y + size.y / 2.f };
	body->zDepth = -0.1f;

}

Button::Button(Object* downObject, Object* upObject, Object* hoverObject)
{
	texMap[DOWN]	= downObject;
	texMap[UP]		= upObject;
	texMap[HOVER]	= hoverObject;

	body = new ColliderRect(texMap[DOWN]->GetSize());
	body->zDepth = -0.1f;

	for (auto& p : texMap)
		if (p.second) p.second->SetParent(body);
		
}

Button::Button(const Vector4& UDLR, const wstring& downFile, const wstring& upFile, const wstring& hoverFile)
{
	Vector2 size	= { UDLR.w - UDLR.z, UDLR.x - UDLR.y };

	texMap[DOWN]	= new Object(size, downFile);
	texMap[UP]		= (upFile.empty()) ?	nullptr : new Object(size, upFile);
	texMap[HOVER]	= (hoverFile.empty()) ? nullptr : new Object(size, hoverFile);

	body = new ColliderRect(size);
	body->zDepth = -0.1f;


	for (auto& p : texMap) if (p.second) p.second->SetParent(body);

	body->translation = { UDLR.z + size.x / 2.f, UDLR.y + size.y / 2.f };
}


Button::~Button()
{
	for (auto& p : texMap)
	{
		if (p.second)
		{
			delete p.second;
			Object* temp = p.second;

			for (auto& p2 : texMap)
			{
				if (p2.second == temp) p2.second = nullptr;
			}
		}
	}

	texMap.clear();

	delete body;
}

void Button::Update()
{
	body->Update();

	for (auto& p : texMap)
		if (p.second) p.second->Update();

	if (body->AABBCollision(mousePos))
	{
		body->SetColor(1, 0, 0);

		state = HOVER;

		if (KEY_PRESS(VK_LBUTTON))
			state = DOWN;

		if (KEY_UP(VK_LBUTTON))
		{
			if (Event) Event();
		}
	}
	else
	{
		body->SetColor(0, 1, 0);
		state = UP;
	}

}

void Button::Render()
{
	body->Render();

	if (texMap[state]) texMap[state]->Render();
}

void Button::SetTexLocalTranslation(const Vector2& translation)
{
	for (auto& p : texMap)
	{
		if (p.second) p.second->translation = translation;
	}
}

void Button::SetTexLocalScale(const Vector2& scale)
{
	for (auto& p : texMap)
	{
		if (p.second) p.second->scale = scale;
	}
}
