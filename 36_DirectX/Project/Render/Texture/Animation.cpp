#include "Framework.h"
#include "Animation.h"


Animation::Animation(Vector2 texWorldSize, wstring file, UINT frameX, UINT frameY, UINT nFrames, float updateTime)
	:updateTime(updateTime)
{
	if (nFrames == 0)
		nFrames = frameX * frameY;

	for (UINT i = 0; i < nFrames; i++)
	{
		UINT x = i % frameX; // 0, 1, 2, 3
		UINT y = i / frameX; // 0, 0, 0, 0, 1, 1, 1, 1

		Vector2 uvStart = { x / (float)frameX, y / (float)frameY };
		Vector2 uvEnd = { (x + 1) / (float)frameX, (y + 1) / (float)frameY };

		frames.push_back(new Frame(texWorldSize, file, uvStart, uvEnd));
	}

	SetAll();
}

Animation::Animation(wstring file, UINT frameX, UINT frameY, UINT nFrames, float updateTime)
	:updateTime(updateTime)
{
	if (nFrames == 0)
		nFrames = frameX * frameY;

	for (UINT i = 0; i < nFrames; i++)
	{
		UINT x = i % frameX; // 0, 1, 2, 3
		UINT y = i / frameX; // 0, 0, 0, 0, 1, 1, 1, 1

		Vector2 uvStart = { x / (float)frameX, y / (float)frameY };
		Vector2 uvEnd	= { (x + 1) / (float)frameX, (y + 1) / (float)frameY };

		frames.push_back(new Frame(file, uvStart, uvEnd));
	}

	SetAll();
}

Animation::Animation(vector<Frame*> frames, float updateTime)
	:updateTime(updateTime), frames(frames)
{
	SetAll();
}

Animation::~Animation()
{
	for (Frame* frame : frames)
		delete frame;

	frames.clear();
	actions.clear();
}

void Animation::Update()
{
	if (!isPlay)
		return;

	frameTime += Time::Delta();
	playTime += Time::Delta();

	if (frameTime < updateTime)
		return;

	frameTime -= updateTime;

	if (isLoop)
	{
		++curPlayIndex %= actions.size();

		if (curPlayIndex == clipIdx)
			if (ClipEvent) ClipEvent();

		if (curPlayIndex == 0)
			playTime = 0.f;
	}
	else
	{
		curPlayIndex++;

		if (curPlayIndex == clipIdx)
			if (ClipEvent) ClipEvent();

		if (curPlayIndex >= actions.size())
		{
			curPlayIndex--;

			if (EndEvent) EndEvent();

			Stop();
		}
	}
}

void Animation::Render()
{


	actions[curPlayIndex]->Render();
}

void Animation::Play()
{
	//if (isPlay) return;

	isPlay = true;

	frameTime = 0.f;
	playTime = 0.f;

	curPlayIndex = 0;
}

void Animation::Play(const bool& isLoop)
{
	Play();
	this->isLoop = isLoop;
}

void Animation::Stop()
{
	isPlay = false;

	frameTime = 0.f;
	playTime = 0.f;
		
}

void Animation::Stop(UINT rewindIdx)
{
	Stop();
	curPlayIndex = rewindIdx;
}

void Animation::SetAll(bool isLoop)
{
	this->isLoop = isLoop;

	actions.clear();

	for (UINT i = 0; i < frames.size(); i++)
	{
		actions.push_back(frames[i]);
	}
}

void Animation::SetPart(int start, int end, bool isLoop)
{
	this->isLoop = isLoop;

	actions.clear();

	if (end > start)
	{
		for (int i = start; i <= end; i++)
		{
			actions.push_back(frames[i]);
		}
	}
	else
	{
		for (int i = start; i >= end; i--)
		{
			actions.push_back(frames[i]);
		}
	}
}

void Animation::SetIndex(vector<UINT> indices, bool isLoop)
{
	this->isLoop = isLoop;

	actions.clear();

	for (UINT i = 0; i < indices.size(); i++)
	{
		actions.push_back(frames[indices[i]]);
	}
}

void Animation::SetClipEvent(function<void()> ClipEvent, const UINT& targetIdx)
{
	this->ClipEvent = ClipEvent;
	this->clipIdx = targetIdx;
}

