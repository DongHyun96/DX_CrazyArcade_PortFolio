#include "Framework.h"
#include "AStar.h"

ASNode* AStar::fieldNodes[MAP_ROW][MAP_COL];

AStar::AStar()
{
    for (UINT i = 0; i < MAP_ROW; i++)
    {
        for (UINT j = 0; j < MAP_COL; j++)
        {
            fieldNodes[i][j] = new ASNode({ j, i });
        }
    }
}

AStar::~AStar()
{
    for (UINT i = 0; i < MAP_ROW; i++)
    {
        for (UINT j = 0; j < MAP_COL; j++)
        {
            delete fieldNodes[i][j];
        }
    }
}

  

stack<Util::Coord> AStar::GetPath(const Util::Coord& start, const Util::Coord& dest, const bool& isC_SPACE)
{
    static const int dx[4] = { 0, 0, -1, 1 };
    static const int dy[4] = { 1, -1, 0, 0 };
    
    InitFields();


    stack<Util::Coord> path{};

    if (start == dest) return path;

    priority_queue<ASNode*, vector<ASNode*>, CompareNode> pq{};

    set<Util::Coord> visited{};
    
    UINT startH = Util::GetDist(start, dest);
    fieldNodes[start.y][start.x]->g = 0;
    fieldNodes[start.y][start.x]->h = startH;
    fieldNodes[start.y][start.x]->g = startH;

    //visited[start] = &startNode;

    pq.push(fieldNodes[start.y][start.x]);

    while (!pq.empty())
    {
        ASNode* curNode = pq.top();
        pq.pop();

        if (visited.find(curNode->coord) != visited.end()) continue;

        visited.insert(curNode->coord);

        if (curNode->coord == dest) // 최단경로 탐색 완료
        {
            path.push(curNode->coord);
            curNode = curNode->parent;

            while (curNode->coord != start)
            {
                path.push(curNode->coord);
                curNode = curNode->parent;
            }
            
            return path;
        }

        for (UINT i = 0; i < 4; i++)
        {
            int nx = curNode->coord.x + dx[i];
            int ny = curNode->coord.y + dy[i];
            
            // 범위 판정 먼저
            if (nx < 0 || nx >= MAP_COL || ny < 0 || ny >= MAP_ROW) continue;
            
            Util::Coord nextCoord{ (UINT)nx, (UINT)ny};

            if (!IsAvailableCell(nextCoord, isC_SPACE)) continue;
            
            // f, g, h값 구하기
            UINT g = curNode->g + 1;
            UINT h = Util::GetDist(nextCoord, dest);
            int f = g + h;
            
            if (f < fieldNodes[nextCoord.y][nextCoord.x]->f)
            {
                fieldNodes[nextCoord.y][nextCoord.x]->g = g;
                fieldNodes[nextCoord.y][nextCoord.x]->h = h;
                fieldNodes[nextCoord.y][nextCoord.x]->f = f;
                fieldNodes[nextCoord.y][nextCoord.x]->parent = curNode;
                pq.push(fieldNodes[nextCoord.y][nextCoord.x]);
            }
        }
    }

	return path; // return empty path
}

bool AStar::IsAvailableCell(const Util::Coord& coord, const bool& isC_SPACE)
{
    /*
    블럭과 벌룬과 스트림이 모두 없어야 가능함
    TODO : 스트림 검사도 추가 (일단 블럭과 벌룬만 시도)
    */

    // 안되는 조건 모두 검사

    // 블럭 먼저 체크
    Block* block = BlockManager::GetCoordBlock(coord);

    if (block)
    {
        if (block->IsActive())
        {
            if (isC_SPACE)
            {
                if (!block->IsBreakable()) return false;
            }
            else if (!block->IsHidable()) return false;
        }
    }

    // 벌룬 조사
    if (Balloon::IsActiveBalloonOnCoord(coord)) return false;

    return true;
}

void AStar::InitFields()
{
    for (UINT i = 0; i < MAP_ROW; i++)
    {
        for (UINT j = 0; j < MAP_COL; j++)
        {
            fieldNodes[i][j]->g = 0;
            fieldNodes[i][j]->h = 0;
            fieldNodes[i][j]->f = INF;
        }
    }
}
