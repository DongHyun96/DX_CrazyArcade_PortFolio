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

	static Vector2 ConvertBoardIdxToWorldPos(const UINT& x, const UINT& y)
	{
		return Vector2
		(
			WIN_WIDTH / (MAP_COL * 2.f)  + x * (WIN_WIDTH / MAP_COL)  - WIN_CENTER.x,
			WIN_HEIGHT / (MAP_ROW * 2.f) + y * (WIN_HEIGHT / MAP_ROW) - WIN_CENTER.y
		);
	}

	static Vector2 ConvertBoardIdxToWorldPos(const pair<UINT, UINT>& xy)
	{
		return ConvertBoardIdxToWorldPos(xy.first, xy.second);
	}

	static void SetTransformToGameBoard(Transform* target, const UINT& x, const UINT& y)
	{
		target->translation = ConvertBoardIdxToWorldPos(x, y);
		target->SetParent(GM->GetGameFieldTransform());
	}

	static void SetTransformToGameBoard(Transform* target, const pair<UINT, UINT> boardXY)
	{
		SetTransformToGameBoard(target, boardXY.first, boardXY.second);
	}
}


