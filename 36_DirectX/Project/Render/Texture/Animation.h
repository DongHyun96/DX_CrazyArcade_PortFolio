#pragma once
class Animation
{
public:
	Animation(wstring file, UINT frameX, UINT frameY, UINT nFrames = 0, float updateTime = 0.1f);
	Animation(vector<Frame*> frames, float updateTime = 0.1f); // 이미지 파일 하나씩 쓸 경우

	~Animation();

	void Update();
	void Render();

	void Play();
	void Stop();

	void SetAll(bool isLoop = true);
	void SetPart(int start, int end, bool isLoop = true);
	void SetIndex(vector<UINT> indices, bool isLoop = true);

	void SetEndEvent(function<void()> EndEvent) { this->EndEvent = EndEvent; }

	Vector2 Size() const { return actions[0]->Size(); }

private:
	vector<Frame*> frames{};
	vector<Frame*> actions{};

	float updateTime{};
	float frameTime{};
	float playTime{};

	bool isLoop = true;
	bool isPlay = true;

	UINT curPlayIndex{};

	function<void()> EndEvent = nullptr;
};
