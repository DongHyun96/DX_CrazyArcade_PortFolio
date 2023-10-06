#include "Framework.h"
#include "Balloon.h"

vector<Vector2> Balloon::activeBalloonPositions{};


Balloon::Balloon()
{
	body = new ColliderRect(CELL_WORLD_SIZE);
	body->SetParent(GM->GetGameFieldTransform());

	balloonAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Balloon/1.png", 4, 1, 4, 0.15f);

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

void Balloon::Update()
{
	if (!isActive)
		return;
	
	body->Update();
	body->UpdateZDepthToY();

	balloonAnim->Update();
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

bool Balloon::Spawn(const Util::Coord& spawnCoord)
{
	return Spawn(Util::ConvertBoardIdxToWorldPos(spawnCoord));
}

bool Balloon::Spawn(const Vector2& spawnPos)
{
	//if (isActive)
	//	return false;
	
	// 이미 해당위치에 벌룬이 존재
	if (find(activeBalloonPositions.begin(), activeBalloonPositions.end(), spawnPos) != activeBalloonPositions.end())
		return false;

	body->translation = spawnPos;
	balloonAnim->Play();

	visible = true;
	isActive = true;

	// TODO :
	// Spawn 시에 현재 위에 있는 플레이어들을 모두(나머지 플레이어들은 Update한번하고 충돌검사 한번은 해야함) entered set에 포함시킴으로써 처음에는
	// OnColliderRectEnter 콜백을 받지 말아야 함
	body->EnteredBodies().insert(GM->GetPlayer()->GetBody());
	activeBalloonPositions.push_back(spawnPos);

	return true;
}

void Balloon::OnColliderRectEnter(ColliderRect* targetCollider, Transform* owner)
{
	if (!isActive)
		return;

	Character* c = dynamic_cast<Character*>(owner);

	if (c) CollisionUtil::HandleCommonCollision(body, targetCollider);
}

