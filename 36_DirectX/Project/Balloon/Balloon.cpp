#include "Framework.h"
#include "Balloon.h"

vector<Vector2> Balloon::activeBalloonPositions{};

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
	activeBalloonPositions.clear();

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
	
	if (Spawn(Util::ConvertBoardIdxToWorldPos(spawnCoord)))
	{
		this->spawnCoord = spawnCoord;
		this->streamLv = owner->GetStreamLv();
		this->owner = owner;

		return true;
	}

	return false;
}

void Balloon::Explode()
{
	isActive = false;

	owner->AddLeftBalloonCnt();

	explodeTime = 0.f;

	for (auto it = activeBalloonPositions.begin(); it != activeBalloonPositions.end(); it++)
	{
		if (*it == body->translation)
		{
			activeBalloonPositions.erase(it);
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

bool Balloon::Spawn(const Vector2& spawnPos) // private
{
	
	// �̹� �ش���ġ�� ������ ����
	if (find(activeBalloonPositions.begin(), activeBalloonPositions.end(), spawnPos) != activeBalloonPositions.end())
		return false;

	body->translation = spawnPos;
	balloonAnim->Play();
	
	visible = true;
	isActive = true;
	explodeTime = 0.f;

	// TODO :
	// Spawn �ÿ� ���� ���� �ִ� �÷��̾���� ���(������ �÷��̾���� Update�ѹ��ϰ� �浹�˻� �ѹ��� �ؾ���) entered set�� ���Խ�Ŵ���ν� ó������
	// OnColliderRectEnter �ݹ��� ���� ���ƾ� ��

	//body->EnteredBodies().insert(GM->GetPlayer()->GetBody());

	for (Character* p : PM->GetWholePlayers())
	{
		body->EnteredBodies().insert(p->GetBody());
	}
	activeBalloonPositions.push_back(spawnPos);

	return true;
}

void Balloon::HandleExplode()
{
	explodeTime += Time::Delta();

	if (explodeTime < EXPLODE_TIME_LIMIT)
		return;

	explodeTime = 0.f;

	Explode();
}

void Balloon::OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner)
{
	if (!isActive)
		return;

	Character* c = dynamic_cast<Character*>(owner);

	if (c) CollisionUtil::HandleCharacterCommonCollision(body, targetCollider);
}

