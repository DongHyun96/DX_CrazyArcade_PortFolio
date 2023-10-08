#include "Framework.h"
#include "StreamBlock_Right.h"


StreamBlock_Right::StreamBlock_Right()
{
	mainAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/rightNormal.png", 11, 1, 11, 0.045f);
	mainAnim->SetIndex(ANIM_INDICES, false);
	mainAnim->SetEndEvent(bind(&StreamBlock_Right::SetActive, this, false));

	endAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/rightEnd.png", 11, 1, 11, 0.045f);
	endAnim->SetIndex(ANIM_INDICES, false);
	endAnim->SetEndEvent(bind(&StreamBlock_Right::SetActive, this, false));
}

StreamBlock_Right::~StreamBlock_Right()
{
}
