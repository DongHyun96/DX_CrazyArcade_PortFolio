#include "Framework.h"
#include "AStar.h"


AStar::AStar()
{
}

AStar::~AStar()
{
}

  //ASNode node1{ nullptr, Util::Coord{}, 100, 20, 30 };
  //ASNode node2{ nullptr, Util::Coord{}, 15, 25, 35 };
  //ASNode node3{ nullptr, Util::Coord{}, 5, 15, 25 };

  //pq.push(&node1);
  //pq.push(&node2);
  //pq.push(&node3);

  //while (!pq.empty()) 
  //{
  //    ASNode* topNode = pq.top();
  //    pq.pop();
  //}

stack<Util::Coord> AStar::GetPath(const Util::Coord& start, const Util::Coord& dest, const bool& isC_SPACE)
{
    static const int dx[4] = { 0, 0, -1, 1 };
    static const int dy[4] = { 1, -1, 0, 0 };

    stack<Util::Coord> path{};

    if (start == dest) return path;

    priority_queue<ASNode*, vector<ASNode*>, CompareNode> pq{};
    set<Util::Coord> visited{};
    
    ASNode startNode{ nullptr, start, 0, 0, 0};
    visited.insert(start);
    pq.push(&startNode);
    


    while (!pq.empty())
    {
        ASNode* curNode = pq.top();
        pq.pop();

        if (curNode->coord == dest) // 최단경로 탐색 완료
        {
            path.push(curNode->coord);
            curNode = curNode->parent;

            while (curNode->parent)
            {
                path.push(curNode->coord);
                curNode = curNode->parent;
            }

            return path;
        }

        for (UINT i = 0; i < 4; i++)
        {
            pair<int, int> temp = { curNode->coord.x + dx[i], curNode->coord.y + dy[i] };
            
            // 범위 판정 먼저
            if (temp.first < 0 || temp.first >= MAP_COL || temp.second < 0 || temp.second >= MAP_ROW) continue;
                
            Util::Coord nextCoord{ (UINT)temp.first, (UINT)temp.second };

            if (find(visited.begin(), visited.end(), nextCoord) != visited.end()) continue; // 이미 방문했던 자리

            // 탐색할 자리여서 pq에 넣던 or 아니던 visited에는 넣어 놓음
            visited.insert(nextCoord);

            /*
            블럭과 벌룬과 스트림이 모두 없어야 가능함
            TODO : 스트림 검사도 추가 (일단 블럭과 벌룬만 시도)
            */

            // 안되는 조건 모두 검사

            // 블럭 먼저 체크
            Block* block = BlockManager::GetCoordBlock(nextCoord);
            
            if (block)
            {
                if (block->IsActive())
                {
                    if (isC_SPACE)
                    {
                        if (!block->IsBreakable()) continue;
                    }
                    else if (!block->IsHidable()) continue;
                }
            }

            // 벌룬 조사
            if (Balloon::IsActiveBalloonOnCoord(nextCoord)) continue;
            
            // 길은 있음
            ASNode node;
            node.parent = curNode;
            node.coord = nextCoord;
            node.g = curNode->g + 1;
            node.h = Util::GetDist(nextCoord, dest);
            node.f = node.g + node.h;

            pq.push(&node);
        }
    }

	return path;
}
