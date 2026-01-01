#include "Framework.h"
#include "StreamBlock_Right.h"


StreamBlock_Right::StreamBlock_Right()
{
	mainAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/rightNormal.png", 11, 1, 11, ANIM_SPEED);
	mainAnim->SetIndex(ANIM_INDICES, false);
	mainAnim->SetEndEvent(bind(&StreamBlock_Right::SetActive, this, false));
	mainAnim->SetClipEvent(bind(&StreamBlock_Right::DisableBodyCollider, this), BODY_COLLISION_DISABLE_IDX);

	endAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/rightEnd.png", 11, 1, 11, ANIM_SPEED);
	endAnim->SetIndex(ANIM_INDICES, false);
	endAnim->SetEndEvent(bind(&StreamBlock_Right::SetActive, this, false));
	endAnim->SetClipEvent(bind(&StreamBlock_Right::DisableBodyCollider, this), BODY_COLLISION_DISABLE_IDX);

}

StreamBlock_Right::~StreamBlock_Right()
{
}
