#pragma once
/* CONCRETE CLASS */
class LobbyScene : public Scene
{
public:
	LobbyScene();
	~LobbyScene();

	virtual void Update() override;
	virtual void Render() override;

	/*
	Game Scene에서 Lobby Scene으로 돌아올 때, 이전에 캐릭터 선택창 pick이 Random이었다면
	다시 캐릭터 select상태를 random으로 돌려놓음
	*/
	void InitPlayerCharacters();

private:
	/* 캐릭터 능력치 UI 띄우기 */
	void HandleInfoHover();

private: /* Button click call back functions */

	void OnMapLeftButton();
	void OnMapRightButton();

	void OnModePVP();
	void OnModePVE();

	void OnCharacterSelect(const CharacterType& cType, const PlayerType& pType) { GM->P_SelectedCharacterMap()[pType] = cType; }

	void OnGameStart();

private:

	Object* mainBackground{};
	Object* instruction{};

private: /* Button 관련 */

	Button* gameStartButton{};

	Button*					mapLeftButton{};
	Button*					mapRightButton{};
	map<GameMap, Object*>	mapThumbnails{};

	ToggleButton* pvpButton{};
	ToggleButton* pveButton{};
	
	map< CharacterType, map<PlayerType, ToggleButton*> >	characterSelectButtons{};
	map<CharacterType, Object*>								characterHoverObjects{};
	CharacterType											curCharacterShowInfoType = RANDOM;

	map<CharacterType, Object*> characterP1Thumbnail{};
	map<CharacterType, Object*> characterP2Thumbnail{};

private:

	Object* xTex{};
	bool xTexHide = true;

};
