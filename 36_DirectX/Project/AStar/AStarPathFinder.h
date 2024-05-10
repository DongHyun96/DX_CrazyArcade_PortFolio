#pragma once

#define INF 10000	// 거리 무한대 defined

struct ASNode
{
	ASNode() {}
	ASNode(const Util::Coord& coord)
		:coord(coord) {}


	Util::Coord coord{};	// 이 node의 위치
	ASNode*		parent{};

	UINT g{};				// 현 발자국 점수
	UINT h{};				// 휴리스틱 값

	int f = INF;			// 합산 거리 점수
};

/* A* 알고리즘 내에서 prioriy_queue의 Priority 조건 */
struct CompareNode
{
	bool operator()(const ASNode* node1, const ASNode* node2) const
	{
		return node1->f > node2->f;
	}
};


/* CONCRETE CLASS | SINGLETON */
class AStarPathFinder : public Singleton<AStarPathFinder> // AStar 초기화 때문에 생성자 한 번 호출하고 외부에서는 static 메서드 바로 호출할 예정
{

	friend class Singleton;

private:

	AStarPathFinder();
	~AStarPathFinder();

public:


	/// <returns> path, 검사한 visited coords </returns>

	/// <summary>
	/// A* 알고리즘을 통한 start부터 dest까지의 경로 찾기
	/// </summary>
	/// <param name="start"> : 출발점 </param>
	/// <param name="dest"> : 도착점 </param>
	/// <param name="isC_SPACE"> : 움직이려는 객체의 상태가 C_SPACE인지(우주선일 경우 최단경로 계산이 달라짐) </param>
	/// <returns> path, 검사한 visited coords | 만약 경로가 존재하지 않다면 empty path return </returns>
	static pair<stack<Util::Coord>, set<Util::Coord>> GetPath(const Util::Coord& start, const Util::Coord& dest, const bool& isC_SPACE);

private:
	
	/* 이동 가능한 cell 좌표인지 검사 */
	static bool IsAvailableCell(const Util::Coord& coord, const bool& isC_SPACE);

	/* fieldNode들의 변수값 초기화 */
	static void InitFields();

private:

	/* Game field 각 cell 위치에 해당하는 ASNode들 */
	static ASNode* fieldNodes[MAP_ROW][MAP_COL];

};
