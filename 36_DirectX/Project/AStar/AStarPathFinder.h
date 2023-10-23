#pragma once

#define INF 10000

/*
��� �� & Balloon�� ���踦 �ؾ� ��
*/

struct ASNode
{
	ASNode() {}
	ASNode(const Util::Coord& coord)
		:coord(coord) {}


	Util::Coord coord{};
	ASNode* parent{};

	UINT g{}; // �� ���ڱ� ����
	UINT h{}; // �޸���ƽ ��

	int f{INF}; // �ջ� �Ÿ� ����
};

struct CompareNode
{
	bool operator()(const ASNode* node1, const ASNode* node2) const
	{
		return node1->f > node2->f;
	}
};


class AStarPathFinder : public Singleton<AStarPathFinder> // AStar �ʱ�ȭ ������ ������ �� �� ȣ���ϰ� �ܺο����� static �޼��� �ٷ� ȣ���� ����
{

	friend class Singleton;

private:

	AStarPathFinder();
	~AStarPathFinder();

public:


	/// <returns> path, �˻��� visited </returns>
	static pair<stack<Util::Coord>, set<Util::Coord>> GetPath(const Util::Coord& start, const Util::Coord& dest, const bool& isC_SPACE);

private:
	
	static bool IsAvailableCell(const Util::Coord& coord, const bool& isC_SPACE);

	static void InitFields();

private:

	static ASNode* fieldNodes[MAP_ROW][MAP_COL];

};
