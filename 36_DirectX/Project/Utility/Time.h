#pragma once

class Time : public Singleton<Time>
{
	friend class Singleton;
private:
	Time();
	~Time();

public:
	void Update();
	void Render();

	static float Delta() { return timeElapsed; }

	void RefreshTimer() 
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTick);
		timeElapsed = 0.f;
	}

	UINT GetFPS() { return frameRate; }

private:
	static float timeElapsed;

	float timeScale;

	INT64  curTick;
	INT64 lastTick;
	INT64 ticksPerSecond;

	UINT frameCount;
	UINT frameRate;

	float runningTime;

	float scanningRate;

	float oneSecCount;
};
