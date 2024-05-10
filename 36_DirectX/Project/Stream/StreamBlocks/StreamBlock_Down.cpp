#include "Framework.h"
#include "StreamBlock_Down.h"


StreamBlock_Down::StreamBlock_Down()
{
	mainAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/downNormal.png", 11, 1, 11, ANIM_SPEED);
	mainAnim->SetIndex(ANIM_INDICES, false);
	mainAnim->SetEndEvent(bind(&StreamBlock_Down::SetActive, this, false));
	mainAnim->SetClipEvent(bind(&StreamBlock_Down::DisableBodyCollider, this), BODY_COLLISION_DISABLE_IDX);

	endAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/downEnd.png", 11, 1, 11, ANIM_SPEED);
	endAnim->SetIndex(ANIM_INDICES, false);
	endAnim->SetEndEvent(bind(&StreamBlock_Down::SetActive, this, false));
	endAnim->SetClipEvent(bind(&StreamBlock_Down::DisableBodyCollider, this), BODY_COLLISION_DISABLE_IDX);

}

StreamBlock_Down::~StreamBlock_Down()
{
}