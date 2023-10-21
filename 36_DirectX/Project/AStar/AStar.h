#pragma once

/*
��� �� & Balloon�� ���踦 �ؾ� ��
*/

struct ASNode
{

	ASNode* parent{};
	Util::Coord coord{};

	UINT g{}; // �� ���ڱ� ����
	UINT h{}; // �޸���ƽ ��

	int f{}; // �ջ� �Ÿ� ����
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

	// path�� empty�̸� ��ΰ� ���ų� �̹� ������ ����
	static stack<Util::Coord> GetPath(const Util::Coord& start, const Util::Coord& dest, const bool& isC_SPACE);

};
