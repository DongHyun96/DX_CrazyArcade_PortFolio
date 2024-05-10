#pragma once

#define INF 10000	// �Ÿ� ���Ѵ� defined

struct ASNode
{
	ASNode() {}
	ASNode(const Util::Coord& coord)
		:coord(coord) {}


	Util::Coord coord{};	// �� node�� ��ġ
	ASNode*		parent{};

	UINT g{};				// �� ���ڱ� ����
	UINT h{};				// �޸���ƽ ��

	int f = INF;			// �ջ� �Ÿ� ����
};

/* A* �˰��� ������ prioriy_queue�� Priority ���� */
struct CompareNode
{
	bool operator()(const ASNode* node1, const ASNode* node2) const
	{
		return node1->f > node2->f;
	}
};


/* CONCRETE CLASS | SINGLETON */
class AStarPathFinder : public Singleton<AStarPathFinder> // AStar �ʱ�ȭ ������ ������ �� �� ȣ���ϰ� �ܺο����� static �޼��� �ٷ� ȣ���� ����
{

	friend class Singleton;

private:

	AStarPathFinder();
	~AStarPathFinder();

public:


	/// <returns> path, �˻��� visited coords </returns>

	/// <summary>
	/// A* �˰����� ���� start���� dest������ ��� ã��
	/// </summary>
	/// <param name="start"> : ����� </param>
	/// <param name="dest"> : ������ </param>
	/// <param name="isC_SPACE"> : �����̷��� ��ü�� ���°� C_SPACE����(���ּ��� ��� �ִܰ�� ����� �޶���) </param>
	/// <returns> path, �˻��� visited coords | ���� ��ΰ� �������� �ʴٸ� empty path return </returns>
	static pair<stack<Util::Coord>, set<Util::Coord>> GetPath(const Util::Coord& start, const Util::Coord& dest, const bool& isC_SPACE);

private:
	
	/* �̵� ������ cell ��ǥ���� �˻� */
	static bool IsAvailableCell(const Util::Coord& coord, const bool& isC_SPACE);

	/* fieldNode���� ������ �ʱ�ȭ */
	static void InitFields();

private:

	/* Game field �� cell ��ġ�� �ش��ϴ� ASNode�� */
	static ASNode* fieldNodes[MAP_ROW][MAP_COL];

};
