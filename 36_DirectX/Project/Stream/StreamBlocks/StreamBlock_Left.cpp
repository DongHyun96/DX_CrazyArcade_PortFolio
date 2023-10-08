#include "Framework.h"
#include "StreamBlock_Left.h"


StreamBlock_Left::StreamBlock_Left()
{
	// _Texture\InGame\Stream
	// mainAnim / endAnim ÃÊ±âÈ­
	// L"InGame/Characters/Bazzi/playerBubble.png"

	mainAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/leftNormal.png", 11, 1, 11, 0.045f);
	mainAnim->SetIndex(ANIM_INDICES, false);
	mainAnim->SetEndEvent(bind(&StreamBlock_Left::SetActive, this, false));

	endAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/leftEnd.png", 11, 1, 11, 0.045f);
	endAnim->SetIndex(ANIM_INDICES, false);
	endAnim->SetEndEvent(bind(&StreamBlock_Left::SetActive, this, false));

}

StreamBlock_Left::~StreamBlock_Left()
{
}