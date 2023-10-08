#include "Framework.h"
#include "StreamBlock_Center.h"


StreamBlock_Center::StreamBlock_Center()
{
	mainAnim = new Animation(CELL_WORLD_SIZE, L"InGame/Stream/center.png", 3, 1, 3, 0.045f);
	// 20¹ø
	
	vector<UINT> indices{};

	for (UINT i = 0; i < 6; i++)
	{
		for (UINT j = 0; j < 3; j++)
			indices.push_back(j);
	}
	
	indices.push_back(0);
	indices.push_back(1);

	mainAnim->SetIndex(indices, false);
	mainAnim->SetEndEvent(bind(&StreamBlock_Center::SetActive, this, false));
}

StreamBlock_Center::~StreamBlock_Center()
{
}