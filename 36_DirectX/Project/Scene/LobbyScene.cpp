#include "Framework.h"
#include "LobbyScene.h"


LobbyScene::LobbyScene()
{
	// InGame\UI\LobbyScene
	mainBackground = new Object(WIN_SIZE, L"InGame/UI/LobbyScene/Lobby.png");
	mainBackground->translation = WIN_CENTER;

	instruction = new Object({ 337, 43, 55, 1074 }, L"InGame/UI/LobbyScene/Instruction.png");
	instruction->zDepth = -1.f;

	gameStartButton = new Button({ 139, 37, 1228, 1690 }, L"InGame/UI/LobbyScene/gameStartButton.png", 2, 1, 2);
	gameStartButton->SetEvent(bind(&LobbyScene::OnGameStart, this));

	//Button(const Vector4 & UDLR, const wstring & downFile, const wstring & upFile = L"", const wstring & hoverFile = L"");
	mapLeftButton = new Button({ 260, 184, 1562, 1649 },
		L"InGame/UI/LobbyScene/LeftButtonSelected.png",
		L"InGame/UI/LobbyScene/LeftButtonIdle.png",
		L"InGame/UI/LobbyScene/LeftButtonHover.png");
	mapLeftButton->SetEvent(bind(&LobbyScene::OnMapLeftButton, this));

	mapRightButton = new Button({ 260, 184, 1747, 1834 },
		L"InGame/UI/LobbyScene/RightButtonSelected.png",
		L"InGame/UI/LobbyScene/RightButtonIdle.png",
		L"InGame/UI/LobbyScene/RightButtonHover.png");
	mapRightButton->SetEvent(bind(&LobbyScene::OnMapRightButton, this));


	//ToggleButton(const string & toggleGroupKey, const Vector4 & UDLR, const wstring & downFile, const wstring & upFile = L"", const wstring & hoverFile = L"");
	pvpButton = new ToggleButton("mode", { 545, 470, 1252, 1461 },
		L"InGame/UI/LobbyScene/PVPSelected.png",
		VK_LBUTTON,
		L"InGame/UI/LobbyScene/PVPNormal.png",
		L"InGame/UI/LobbyScene/PVPHover.png");
	pvpButton->SetEvent(bind(&LobbyScene::OnModePVP, this));

	pveButton = new ToggleButton("mode", { 545, 470, 1562, 1771 },
		L"InGame/UI/LobbyScene/PVEPressed.png",
		VK_LBUTTON,
		L"InGame/UI/LobbyScene/PVENormal.png",
		L"InGame/UI/LobbyScene/PVEHover.png");
	pveButton->SetEvent(bind(&LobbyScene::OnModePVE, this));

	map<PlayerType, ToggleButton*> temp{};

	characterSelectButtons =
	{
		{
			BAZZI, 
			{
				{P1, new ToggleButton("cSelectp1", { 770, 696, 1350, 1498 }, L"InGame/UI/LobbyScene/check1.png") },
				{P2, new ToggleButton("cSelectp2", { 770, 696, 1350, 1498 }, L"InGame/UI/LobbyScene/check2.png", VK_RBUTTON) }
			}
		},

		{
			MARID,
			{
				{P1, new ToggleButton("cSelectp1", { 770, 696, 1177, 1324 }, L"InGame/UI/LobbyScene/check1.png") },
				{P2, new ToggleButton("cSelectp2", { 770, 696, 1177, 1324 }, L"InGame/UI/LobbyScene/check2.png", VK_RBUTTON) }
			}
		},

		{
			DAO,
			{
				{P1, new ToggleButton("cSelectp1", { 861, 784, 1177, 1324 }, L"InGame/UI/LobbyScene/check1.png") },
				{P2, new ToggleButton("cSelectp2", { 861, 784, 1177, 1324 }, L"InGame/UI/LobbyScene/check2.png", VK_RBUTTON) }
			}
		},

		{
			CAPPI,
			{
				{P1, new ToggleButton("cSelectp1", { 861, 784, 1350, 1498 }, L"InGame/UI/LobbyScene/check1.png") },
				{P2, new ToggleButton("cSelectp2", { 861, 784, 1350, 1498 }, L"InGame/UI/LobbyScene/check2.png", VK_RBUTTON) }
			}
		},

		{
			RANDOM,
			{
				{P1, new ToggleButton("cSelectp1", { 1040, 880, 1173, 1846 }, L"InGame/UI/LobbyScene/check1.png") },
				{P2, new ToggleButton("cSelectp2", { 1040, 880, 1173, 1846 }, L"InGame/UI/LobbyScene/check2.png", VK_RBUTTON) }
			}
		}
	};

	//map< CharacterType, map<PlayerType, ToggleButton*> > characterSelectButtons{};
	
	characterSelectButtons[RANDOM][P1]->SetTexLocalScale({ 0.15f, 0.3f });
	characterSelectButtons[RANDOM][P2]->SetTexLocalScale({ 0.15f, 0.3f });
	characterSelectButtons[RANDOM][P1]->SetTexLocalTranslation({ 50.f, -20.f });
	characterSelectButtons[RANDOM][P2]->SetTexLocalTranslation({ 50.f, 20.f });

	for (auto& p : characterSelectButtons)
	{
		CharacterType cType = p.first;

		for (auto& p2 : p.second)
		{
			PlayerType pType = p2.first;
			
			p2.second->SetCSelectEvent(bind(&LobbyScene::OnCharacterSelect, this, cType, pType));
			p2.second->SetHoverSound("HoverSound2");
		}
	}
	
	for (UINT i = 0; i < 4; i++)
	{
		for (UINT j = 0; j < 2; j++)
		{
			characterSelectButtons[(CharacterType)i][(PlayerType)j]->SetTexLocalScale({ 0.5f, 0.5f });
			characterSelectButtons[(CharacterType)i][(PlayerType)j]->SetTexLocalTranslation({ 50.f, -10.f + 20.f * j});
		}
	}

	characterHoverObjects[BAZZI]	= new Object(L"InGame/UI/LobbyScene/BazziInfo.png");
	characterHoverObjects[DAO]		= new Object(L"InGame/UI/LobbyScene/DaoInfo.png");
	characterHoverObjects[CAPPI]	= new Object(L"InGame/UI/LobbyScene/CappiInfo.png");
	characterHoverObjects[MARID]	= new Object(L"InGame/UI/LobbyScene/MaridInfo.png");
	characterHoverObjects[BAZZI]->zDepth = -2.f;
	characterHoverObjects[DAO]->zDepth = -2.f;
	characterHoverObjects[CAPPI]->zDepth = -2.f;
	characterHoverObjects[MARID]->zDepth = -2.f;


	mapThumbnails[VILLAGE]	= new Object({ 420, 175, 1170, 1531 }, L"InGame/UI/LobbyScene/MapThumbNail/Village.png");
	mapThumbnails[VILLAGE]->zDepth = -1.f;
	mapThumbnails[FACTORY]	= new Object({ 420, 175, 1170, 1531 }, L"InGame/UI/LobbyScene/MapThumbNail/Factory.png");
	mapThumbnails[FACTORY]->zDepth = -1.f;
	mapThumbnails[FOREST]	= new Object({ 420, 175, 1170, 1531 }, L"InGame/UI/LobbyScene/MapThumbNail/Forest.png");
	mapThumbnails[FOREST]->zDepth = -1.f;
	/*mapThumbnails[TEST_FIELD] = new Object({ 420, 175, 1170, 1531 }, L"InGame/UI/LobbyScene/MapThumbNail/Testing.png");
	mapThumbnails[TEST_FIELD]->zDepth = -1.f;*/

	xTex = new Object({ 897, 722, 324, 548 }, L"InGame/UI/LobbyScene/X.jpg");
	xTex->zDepth = -2.f;

	Vector2 idleSize = { CELL_WORLD_SIZE.x - 5, CELL_WORLD_SIZE.y + 15 };

	characterP1Thumbnail[BAZZI]		= new Object({ CELL_WORLD_SIZE.x - 5, CELL_WORLD_SIZE.y + 15 }, L"InGame/UI/LobbyScene/Bazzi.png");
	characterP1Thumbnail[DAO]		= new Object({ CELL_WORLD_SIZE.x + 5, CELL_WORLD_SIZE.y + 25 }, L"InGame/UI/LobbyScene/Dao.png");
	characterP1Thumbnail[CAPPI]		= new Object({ CELL_WORLD_SIZE.x + 5, CELL_WORLD_SIZE.y + 25 }, L"InGame/UI/LobbyScene/Cappi.png");
	characterP1Thumbnail[MARID]		= new Object({ CELL_WORLD_SIZE.x + 5, CELL_WORLD_SIZE.y + 25 }, L"InGame/UI/LobbyScene/Marid.png");
	characterP1Thumbnail[RANDOM]	= new Object({ CELL_WORLD_SIZE.x + 5, CELL_WORLD_SIZE.y + 25 }, L"InGame/UI/LobbyScene/Random1.png");

	for (auto& p : characterP1Thumbnail)
	{
		p.second->translation = { 179, 808 };
		p.second->zDepth = -1.f;
	}

	characterP2Thumbnail[BAZZI]		= new Object({ CELL_WORLD_SIZE.x - 5, CELL_WORLD_SIZE.y + 15 }, L"InGame/UI/LobbyScene/Bazzi.png");
	characterP2Thumbnail[DAO]		= new Object({ CELL_WORLD_SIZE.x + 5, CELL_WORLD_SIZE.y + 25 }, L"InGame/UI/LobbyScene/Dao.png");
	characterP2Thumbnail[CAPPI]		= new Object({ CELL_WORLD_SIZE.x + 5, CELL_WORLD_SIZE.y + 25 }, L"InGame/UI/LobbyScene/Cappi.png");
	characterP2Thumbnail[MARID]		= new Object({ CELL_WORLD_SIZE.x + 5, CELL_WORLD_SIZE.y + 25 }, L"InGame/UI/LobbyScene/Marid.png");
	characterP2Thumbnail[RANDOM]	= new Object({ CELL_WORLD_SIZE.x + 5, CELL_WORLD_SIZE.y + 25 }, L"InGame/UI/LobbyScene/Random2.png");

	for (auto& p : characterP2Thumbnail)
	{
		p.second->translation = { 433, 808 };
		p.second->zDepth = -1.f;
	}

}


LobbyScene::~LobbyScene()
{
	delete mainBackground;

	delete instruction;

	delete gameStartButton;

	delete mapLeftButton;
	delete mapRightButton;

	delete pvpButton;
	delete pveButton;

	for (auto& p : characterSelectButtons)
	{
		for (auto& p2 : p.second)
			delete p2.second;
	}

	for (auto& p : characterHoverObjects)
	{
		if (p.second) delete p.second;
	}

	for (auto& p : mapThumbnails)
		delete p.second;

	delete xTex;

	for (auto& p : characterP1Thumbnail)
		delete p.second;

	for (auto& p : characterP2Thumbnail)
		delete p.second;

}

void LobbyScene::Update()
{
	mainBackground->Update();

	instruction->Update();


	mapLeftButton->Update();
	mapRightButton->Update();

	pvpButton->Update();
	pveButton->Update();

	for (auto& p : characterSelectButtons)
	{
		for (auto& p2 : p.second)
			p2.second->Update();
	}

	for (auto& p : characterHoverObjects)
		if (p.second) p.second->Update();

	for (auto& p : mapThumbnails)
		p.second->Update();

	xTex->Update();

	for (auto& p : characterP1Thumbnail)
		p.second->Update();

	for (auto& p : characterP2Thumbnail)
		p.second->Update();

	HandleInfoHover();

	gameStartButton->Update();
}

void LobbyScene::Render()
{
	mainBackground->Render();

	instruction->Render();

	gameStartButton->Render();

	mapLeftButton->Render();
	mapRightButton->Render();

	pvpButton->Render();
	pveButton->Render();

	for (auto& p : characterSelectButtons)
	{
		p.second[P1]->Render();

		if (xTexHide)
			p.second[P2]->Render();
	}

	mapThumbnails[GM->GetCurMapType()]->Render();

	if (!xTexHide)
		xTex->Render();

	if (curCharacterShowInfoType != RANDOM)
		characterHoverObjects[curCharacterShowInfoType]->Render();

	characterP1Thumbnail[GM->P_SelectedCharacterMap()[P1]]->Render();
	characterP2Thumbnail[GM->P_SelectedCharacterMap()[P2]]->Render();

	switch (GM->GetCurMapType())
	{
	case VILLAGE:
		FONT->RenderText(L"ºô¸®Áö 10", "BazziFontBold50", Util::ConvertDxPosToAPIPos({1694, 350}));
		break;
	case FOREST:
		FONT->RenderText(L"Æ÷·¹½ºÆ® 07", "BazziFontBold50", Util::ConvertDxPosToAPIPos({ 1694, 350 }));
		break;
	case FACTORY:
		FONT->RenderText(L"ÆÑÅä¸® 07", "BazziFontBold50", Util::ConvertDxPosToAPIPos({ 1694, 350 }));
		break;
	/*case TEST_FIELD:
		FONT->RenderText(L"TestField", "BazziFontBold50", Util::ConvertDxPosToAPIPos({ 1694, 350 }));
		break;*/
	default:
		break;
	}

	FONT->RenderText(L"1P", "BazziFontBold", Util::ConvertDxPosToAPIPos({ 181, 689 }));
	FONT->RenderText(L"2P", "BazziFontBold", Util::ConvertDxPosToAPIPos({ 434, 689 }));


}

void LobbyScene::InitPlayerCharacters()
{
	if (characterSelectButtons[RANDOM][P1]->IsDown())
		GM->P_SelectedCharacterMap()[P1] = RANDOM;

	if (characterSelectButtons[RANDOM][P2]->IsDown())
		GM->P_SelectedCharacterMap()[P2] = RANDOM;
}

void LobbyScene::HandleInfoHover()
{
	for (UINT i = 0; i < CHARACTER_MAX; i++)
	{
		CharacterType type = (CharacterType)i;

		if (characterSelectButtons[type][P1]->GetBody()->AABBCollision(mousePos))
		{
			curCharacterShowInfoType = type;

			if (curCharacterShowInfoType == RANDOM) return;

			if (curCharacterShowInfoType == DAO || curCharacterShowInfoType == MARID)
				characterHoverObjects[curCharacterShowInfoType]->translation = { mousePos.x - 300.f, mousePos.y };
			else
				characterHoverObjects[curCharacterShowInfoType]->translation = { mousePos.x + 300.f, mousePos.y };

			return;
		}
	}

	curCharacterShowInfoType = RANDOM;
}

void LobbyScene::OnMapLeftButton()
{
	int iter = (UINT)GM->GetCurMapType() - 1;

	if (iter == -1)
	{
		GM->SetCurMapType(GameMap(MAP_MAX - 1));
		return;
	}

	GM->SetCurMapType((GameMap)iter);
}

void LobbyScene::OnMapRightButton()
{
	GM->SetCurMapType((GameMap)((UINT)GM->GetCurMapType() + 1));

	if (GM->GetCurMapType() == MAP_MAX)
		GM->SetCurMapType((GameMap)0);
}

void LobbyScene::OnModePVP()
{
	xTexHide = true;
	GM->SetGameMode(PVP);
}

void LobbyScene::OnModePVE()
{
	xTexHide = false;

	GM->SetGameMode(PVE);
}

void LobbyScene::OnGameStart()
{
	SM->SetCurScene(GAME_SCENE);
}
