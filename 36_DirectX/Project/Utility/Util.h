#pragma once


namespace Util
{
	static bool CompareRendererZorder(Renderer* a, Renderer* b)
	{
		Transform* aT = dynamic_cast<Transform*>(a);
		Transform* bT = dynamic_cast<Transform*>(b);

		assert(aT && bT);

		return aT->zDepth > bT->zDepth;
	}

	static Vector2 ConvertBoardIdxToWorldPos(UINT x, UINT y)
	{
		return Vector2
		(
			WIN_WIDTH / 30.f + x * (WIN_WIDTH / 15.f) - WIN_CENTER.x,
			WIN_HEIGHT / 26.f + y * (WIN_HEIGHT / 13.f) - WIN_CENTER.y
		);
	}
}


