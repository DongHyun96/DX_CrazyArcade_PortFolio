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

private:

	void OnModePVP();
	void OnModePVE();

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

};
