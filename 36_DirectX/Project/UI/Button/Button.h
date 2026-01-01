#pragma once

// 알아야 할 것 : 창모드를 못 씀 (정확한 mousePos가 잡힐 수 없음)
class Button
{
protected:

	enum State
	{
		UP,
		HOVER,
		DOWN
	};

public:

	// nFrame 2개 -> (UP, DOWN) (HOVER)
	Button(const wstring& file, const UINT& frameX, const UINT& frameY, UINT nFrames = 0);

	Button(const Vector2& size, const wstring& file, const UINT& frameX, const UINT& frameY, UINT nFrames = 0);
	Button(const Vector4& UDLR, const wstring& file, const UINT& frameX, const UINT& frameY, UINT nFrames = 0);


	Button(Object* downObject, Object* upObject = nullptr, Object* hoverObject = nullptr);
	Button(const Vector4& UDLR, const wstring& downFile, const wstring& upFile = L"", const wstring& hoverFile = L"");


	virtual ~Button();

	virtual void Update();
	virtual void Render();


	void SetEvent(function<void()> Event) { this->Event = Event; }

	ColliderRect* GetBody() const { return body; }

	void SetHoverSound(const string& hoverSound) { this->hoverSound = hoverSound; }

public:

	void SetBodyUDLR(const Vector4& UDLR) { body->SetColliderRect(UDLR); }
	
	void SetTexLocalTranslation(const Vector2& translation);
	void SetTexLocalScale(const Vector2& scale);

protected:

	map<State, Object*> texMap{};

	ColliderRect* body{};

	function<void()> Event = nullptr;
	
	State state = UP;

	string hoverSound{ "HoverSound" };


};
