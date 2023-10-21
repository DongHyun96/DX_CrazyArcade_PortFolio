#pragma once

/*
블록 맵 & Balloon과 연계를 해야 함
*/

struct ASNode
{

	ASNode* parent{};
	Util::Coord coord{};

	UINT g{}; // 현 발자국 점수
	UINT h{}; // 휴리스틱 값

	int f{}; // 합산 거리 점수
};

struct CompareNode
{
	bool operator()(const ASNode* node1, const ASNode* node2) const
	{
		return node1->f > node2->f;
	}
};


class AStar
{
public:

	AStar();
	~AStar();

	// path가 empty이면 경로가 없거나 이미 도달한 상태
	static stack<Util::Coord> GetPath(const Util::Coord& start, const Util::Coord& dest, const bool& isC_SPACE);

};
