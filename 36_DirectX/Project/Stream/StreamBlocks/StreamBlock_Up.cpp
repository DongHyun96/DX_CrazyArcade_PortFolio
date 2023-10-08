#include "Framework.h"
#include "StreamBlock_Up.h"


StreamBlock_Up::StreamBlock_Up()
{
	mainAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/upNormal.png", 11, 1, 11, 0.045f);
	mainAnim->SetIndex(ANIM_INDICES, false);
	mainAnim->SetEndEvent(bind(&StreamBlock_Up::SetActive, this, false));

	endAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/upEnd.png", 11, 1, 11, 0.045f);
	endAnim->SetIndex(ANIM_INDICES, false);
	endAnim->SetEndEvent(bind(&StreamBlock_Up::SetActive, this, false));
}

StreamBlock_Up::~StreamBlock_Up()
{
}