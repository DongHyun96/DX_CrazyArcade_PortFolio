#pragma once

extern function<int()> randGenerator;

/* 4 way movement basic directions */
enum Direction
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_NONE
};

namespace Util
{
	struct Coord
	{
		Coord() {};

		Coord(const UINT& x,const UINT& y) :x(x), y(y) {}

		bool operator==(const Coord& other) const
		{
			return (this->x == other.x && this->y == other.y);
		}

		bool operator!=(const Coord& other) const
		{
			return (this->x != other.x || this->y != other.y);
		}

		bool operator<(const Coord& other) const
		{
			
			if (this->x != other.x) return this->x < other.x;
				

			return this->y < other.y;

		}
			
		UINT x{};
		UINT y{};
	};

	/* 유클리드 거리 */
	static UINT GetDist(const Util::Coord& src, const Util::Coord& dst)
	{
		int sx = src.x;
		int sy = src.y;
		int dx = dst.x;
		int dy = dst.y;

		return sqrt(pow(sx - dx, 2) + pow(dx - dy, 2));
	}
	

	static Vector2 ConvertBoardIdxToWorldPos(const UINT& x, const UINT& y)
	{
		return Vector2
		(
			WIN_WIDTH / (MAP_COL * 2.f)  + x * (WIN_WIDTH / MAP_COL)  - WIN_CENTER.x,
			WIN_HEIGHT / (MAP_ROW * 2.f) + y * (WIN_HEIGHT / MAP_ROW) - WIN_CENTER.y
		);
	}

	static Vector2 ConvertBoardIdxToWorldPos(const Coord& xy)
	{
		return ConvertBoardIdxToWorldPos(xy.x, xy.y);
	}

	// 정확히 떨어지는 중점만 사용가능함 (거의 사용을 못함) -> AABB 충돌처리로 하면 끝남
	//static Coord ConvertWorldPosToBoardIdx(const Vector2& pos)
	//{
	//	return Coord
	//	(
	//		(pos.x + WIN_CENTER.x) * (MAP_COL / WIN_WIDTH) - 0.5f,
	//		(pos.y + WIN_CENTER.y) * (MAP_ROW / WIN_HEIGHT) - 0.5f
	//	);
	//}

	static void SetTransformToGameBoard(Transform* target, const UINT& x, const UINT& y)
	{
		target->translation = ConvertBoardIdxToWorldPos(x, y);
		target->SetParent(GM->GetGameFieldTransform());
	}

	static void SetTransformToGameBoard(Transform* target, const Coord& boardXY)
	{
		SetTransformToGameBoard(target, boardXY.x, boardXY.y);
	}

	template<typename T>
	static void Swap(T*& t1, T*& t2)
	{
		T* temp = t1;
		t1 = t2;
		t2 = temp;
	}

	template <typename T>
	static T GetRandom(const T& start, const T& end)
	{
		if (start >= end)
			return (T)0;

		int range = (int)(end - start + 1);

		return (T)(start + randGenerator() % range);
	}

	template <typename T>
	static void Clamp(T& target, const T& floor, const T& ceil)
	{
		if (target < floor) target = floor;
		else if (target > ceil) target = ceil;
	}

	template <typename T>
	static T MappingtoNewRange(T num, T srcMin, T srcMax, T dstMin, T dstMax)
	{
		if (srcMin > srcMax)
			return T();

		if (dstMin > dstMax)
			return T();

		if (srcMin == srcMax)
			return (T)(((num - srcMin) * (dstMax - dstMin)) + dstMin);

		return (T)(((num - srcMin) * (dstMax - dstMin)) / (srcMax - srcMin) + dstMin);
	}

	static float Lerp(float src, float dst, float alpha)
	{
		if (alpha >= 1)
			return dst;

		if (alpha <= 0)
			return src;

		return (1 - alpha) * src + alpha * dst;

		//return start + (end - start) * factor;
	}
	
	static void PlayFloatingEffect(float& targetSrc, float& timeChecker, float& effectSpeed, const float& UPDATE_TICK)
	{
		timeChecker += Time::Delta();

		if (timeChecker < UPDATE_TICK)
			targetSrc += effectSpeed * Time::Delta();
		else
		{
			timeChecker = 0.f;
			effectSpeed = -effectSpeed;
		}
	}

	static Vector2 ConvertDxPosToAPIPos(const Vector2& dxPos)
	{
		return { dxPos.x, WIN_HEIGHT - dxPos.y };
	}

	static Vector3 ConvertRGB_UINT_To_Float(const Vector3& color)
	{
		return Vector3(color.x / 255.f, color.y / 255.f, color.z / 255.f);
	}

	static Vector3 ConvertRGB_UINT_To_Float(const UINT& r, const UINT& g, const UINT& b)
	{
		return Vector3(r / 255.f, g / 255.f, b / 255.f);
	}
}
