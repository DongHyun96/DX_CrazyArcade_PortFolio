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
	Game Scene���� Lobby Scene���� ���ƿ� ��, ������ ĳ���� ����â pick�� Random�̾��ٸ�
	�ٽ� ĳ���� select���¸� random���� ��������
	*/
	void InitPlayerCharacters();

private:
	/* ĳ���� �ɷ�ġ UI ���� */
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

private: /* Button ���� */

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
