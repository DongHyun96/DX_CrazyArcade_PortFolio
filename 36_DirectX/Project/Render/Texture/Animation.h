#pragma once
class Animation
{
public:
	Animation(Vector2 texWorldSize, wstring file, UINT frameX, UINT frameY, UINT nFrames = 0, float updateTime = 0.1f); // 이미지 크기를 texWorldSize에 맞춤

	Animation(wstring file, UINT frameX, UINT frameY, UINT nFrames = 0, float updateTime = 0.1f); // 이미지 본연의 크기 그대로 사용

	Animation(vector<Frame*> frames, float updateTime = 0.1f); // 이미지 파일 하나씩 쓸 경우

	~Animation();

	void Update();
	void Render();

	void Play();
	void Play(const bool& isLoop);

	void Stop();

	void Stop(UINT rewindIdx);

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
