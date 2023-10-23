#pragma once

#define INF 10000

/*
블록 맵 & Balloon과 연계를 해야 함
*/

struct ASNode
{
	ASNode() {}
	ASNode(const Util::Coord& coord)
		:coord(coord) {}


	Util::Coord coord{};
	ASNode* parent{};

	UINT g{}; // 현 발자국 점수
	UINT h{}; // 휴리스틱 값

	int f{INF}; // 합산 거리 점수
};

struct CompareNode
{
	bool operator()(const ASNode* node1, const ASNode* node2) const
	{
		return node1->f > node2->f;
	}
};


class AStarPathFinder : public Singleton<AStarPathFinder> // AStar 초기화 때문에 생성자 한 번 호출하고 외부에서는 static 메서드 바로 호출할 예정
{

	friend class Singleton;

private:

	AStarPathFinder();
	~AStarPathFinder();

public:


	/// <returns> path, 검사한 visited </returns>
	static pair<stack<Util::Coord>, set<Util::Coord>> GetPath(const Util::Coord& start, const Util::Coord& dest, const bool& isC_SPACE);

private:
	
	static bool IsAvailableCell(const Util::Coord& coord, const bool& isC_SPACE);

	static void InitFields();

private:

	static ASNode* fieldNodes[MAP_ROW][MAP_COL];

};
