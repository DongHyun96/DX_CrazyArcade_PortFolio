#include "Framework.h"
#include "StreamBlock_Down.h"


StreamBlock_Down::StreamBlock_Down()
{
	mainAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/downNormal.png", 11, 1, 11, 0.045f);
	mainAnim->SetIndex(ANIM_INDICES, false);
	mainAnim->SetEndEvent(bind(&StreamBlock_Down::SetActive, this, false));

	endAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/downEnd.png", 11, 1, 11, 0.045f);
	endAnim->SetIndex(ANIM_INDICES, false);
	endAnim->SetEndEvent(bind(&StreamBlock_Down::SetActive, this, false));
}

StreamBlock_Down::~StreamBlock_Down()
{
}