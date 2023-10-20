#pragma once
class LobbyScene : public Scene
{
public:
	LobbyScene();
	~LobbyScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	void HandleInfoHover();

private:

	void OnMapLeftButton();
	void OnMapRightButton();

	void OnModePVP();
	void OnModePVE();

	void OnCharacterSelect(const CharacterType& cType, const PlayerType& pType) { GM->P_SelectedCharacterMap()[pType] = cType; }

	void OnGameStart();

private:

	Object* mainBackground{};
	Object* instruction{};

	Button* gameStartButton{};

	Button* mapLeftButton{};
	Button* mapRightButton{};

	ToggleButton* pvpButton{};
	ToggleButton* pveButton{};
	
	map< CharacterType, map<PlayerType, ToggleButton*> > characterSelectButtons{};
	map<CharacterType, Object*> characterHoverObjects{};
	CharacterType curShowInfo = RANDOM;

	map<GameMap, Object*> mapThumbnails{};

	Object* xTex{};
	bool xTexHide = true;

	map<CharacterType, Object*> characterP1Thumbnail{};
	map<CharacterType, Object*> characterP2Thumbnail{};

};
