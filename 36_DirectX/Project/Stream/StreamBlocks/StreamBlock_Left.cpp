#include "Framework.h"
#include "StreamBlock_Left.h"


StreamBlock_Left::StreamBlock_Left()
{
	// _Texture\InGame\Stream
	// mainAnim / endAnim ÃÊ±âÈ­
	// L"InGame/Characters/Bazzi/playerBubble.png"

	mainAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/leftNormal.png", 11, 1, 11, ANIM_SPEED);
	mainAnim->SetIndex(ANIM_INDICES, false);
	mainAnim->SetEndEvent(bind(&StreamBlock_Left::SetActive, this, false));
	mainAnim->SetClipEvent(bind(&StreamBlock_Left::DisableBodyCollider, this), BODY_COLLISION_DISABLE_IDX);


	endAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/leftEnd.png", 11, 1, 11, ANIM_SPEED);
	endAnim->SetIndex(ANIM_INDICES, false);
	endAnim->SetEndEvent(bind(&StreamBlock_Left::SetActive, this, false));
	endAnim->SetClipEvent(bind(&StreamBlock_Left::DisableBodyCollider, this), BODY_COLLISION_DISABLE_IDX);

}

StreamBlock_Left::~StreamBlock_Left()
{
}