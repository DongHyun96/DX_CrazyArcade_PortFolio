#include "Framework.h"
#include "Balloon.h"

vector<Vector2> Balloon::activeBalloonPositions{};
vector<Util::Coord> Balloon::activeBalloonCoords{};

set<Util::Coord> Balloon::preDangerZone{};

bool Balloon::explodeSoundPlayed{};


Balloon::Balloon(Animation* animation)
{
	body = new ColliderRect(CELL_WORLD_SIZE);
	body->SetParent(GM->GetGameFieldTransform());

	balloonAnim = animation;

	vertexShader = new VertexShader(L"VertexTexture");
	pixelShader = new PixelShader(L"PixelTexture");
	worldBuffer = new MatrixBuffer();

	colorBuffer = new ColorBuffer();
	
	body->SetRectEnterEvent(bind(&Balloon::OnColliderRectEnter, this, placeholders::_1, placeholders::_2));

}

Balloon::~Balloon()
{
	delete body;
	delete balloonAnim;
	delete colorBuffer;

	delete vertexShader;
	delete pixelShader;
	delete worldBuffer;
}

void Balloon::Init()
{
	activeBalloonCoords.clear();
	activeBalloonPositions.clear();
	preDangerZone.clear();

	isActive = false;
	visible = true;

	streamLv = 0;

	owner = nullptr;

	explodeSoundPlayed = false;

	explodeTime = 0.f;
}

void Balloon::Update()
{
	if (!isActive)
		return;
	
	body->Update();
	body->UpdateZDepthToY();

	balloonAnim->Update();

	HandleExplode();
}

void Balloon::Render()
{
	if (!isActive)
		return;

	if (!visible)
		return;

	worldBuffer->SetData(body->GetWorld());
	worldBuffer->VSSetBuffer(0);

	vertexShader->SetShader();
	pixelShader->SetShader();

	colorBuffer->PSSetBuffer(0);

	balloonAnim->Render();
	body->Render();
}

bool Balloon::Spawn(const Util::Coord& spawnCoord, Character* owner) // public
{
	if (find(activeBalloonCoords.begin(), activeBalloonCoords.end(), spawnCoord) != activeBalloonCoords.end())
		return false;

	activeBalloonCoords.push_back(spawnCoord);

	Spawn(Util::ConvertBoardIdxToWorldPos(spawnCoord));
	
	this->spawnCoord = spawnCoord;
	this->streamLv = owner->GetStreamLv();
	this->owner = owner;

	AddPreDangerZone(spawnCoord, streamLv);

	return true;
}

void Balloon::Explode()
{
	isActive = false;

	owner->AddLeftBalloonCnt();

	// 위험 반경을 Stream에 저장함 (For AStar algorithm), 이것은 실질적인 위험 반경 / Balloon의 preDangerZone도 여기서 삭제됨
	Stream::AddStreamDanagerZone(spawnCoord, streamLv);


	explodeTime = 0.f;

	for (auto it = activeBalloonPositions.begin(); it != activeBalloonPositions.end(); it++)
	{
		if (*it == body->translation)
		{
			activeBalloonPositions.erase(it);
			break;
		}
	}

	for (auto it = activeBalloonCoords.begin(); it != activeBalloonCoords.end(); it++)
	{
		if (*it == spawnCoord)
		{
			activeBalloonCoords.erase(it);
			break;
		}
	}

	body->EnteredBodies().clear();

	GM->GetStreamManager()->SpawnStream(spawnCoord, streamLv);

	owner = nullptr;

	if (!explodeSoundPlayed)
	{
		SOUND->Play("BalloonExplode", 1.f);
		explodeSoundPlayed = true;
	}
}

bool Balloon::IsActiveBalloonOnCoord(const Util::Coord& coord)
{
	for (Util::Coord bCoord : activeBalloonCoords)
		if (bCoord == coord) return true;

	return false;
}

void Balloon::Spawn(const Vector2& spawnPos) // private
{
	
	// 이미 해당위치에 벌룬이 존재 (double checking)
	if (find(activeBalloonPositions.begin(), activeBalloonPositions.end(), spawnPos) != activeBalloonPositions.end())
		return;

	body->translation = spawnPos;
	balloonAnim->Play();
	
	visible = true;
	isActive = true;
	explodeTime = 0.f;

	for (Character* p : PM->GetWholePlayers())
	{
		body->EnteredBodies().insert(p->GetBody());
	}
	activeBalloonPositions.push_back(spawnPos);

}

void Balloon::HandleExplode()
{
	explodeTime += Time::Delta();

	if (explodeTime < EXPLODE_TIME_LIMIT)
		return;

	explodeTime = 0.f;

	Explode();
}

void Balloon::AddPreDangerZone(const Util::Coord& spawnCoord, const UINT& streamLv)
{
	static vector<int> dx = { 0, 0, -1, 1 }; // U, D, L, R
	static vector<int> dy = { 1, -1, 0, 0 };

	preDangerZone.insert(spawnCoord);

	for (UINT i = 0; i < 4; i++)
	{
		int x = spawnCoord.x;
		int y = spawnCoord.y;

		for (UINT lv = 1; lv <= streamLv; lv++)
		{
			x += dx[i];
			y += dy[i];

			if (x < 0 || x >= MAP_COL || y < 0 || y >= MAP_ROW) break;

			Util::Coord coord = { (UINT)x, (UINT)y };

			Block* targetBlock = GM->GetBlockManager()->GetCoordBlock(coord);

			if (targetBlock) if (targetBlock->IsActive() && !targetBlock->IsHidable()) break;

			preDangerZone.insert(coord);
		}
	}
}

void Balloon::OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner)
{
	if (!isActive)
		return;

	Character* c = dynamic_cast<Character*>(owner);

	if (c) CollisionUtil::HandleCharacterCommonCollision(body, targetCollider, c->GetSpeed());
}

