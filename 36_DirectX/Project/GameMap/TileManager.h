#pragma once
/* CONCRETE CLASS */
class TileManager
{
public:
	TileManager();
	~TileManager();

	void Update();
	void Render();

private:

	/// <summary>
	/// 새로운 TileManager 생성 시, GameManager의 curMapType에 따른 미리 저장된 Tile들을 Load하면서 Tile을 생성할 때 사용
	/// </summary>
	/// <param name="info"> : 해당 자리 Tile info </param>
	/// <param name="boardX"> : 생성할 자리의 cell pos X </param>
	/// <param name="boardY"> : 생성할 자리의 cell pos Y </param>
	void CreateTile(const TileInfo& info, UINT boardX, UINT boardY);

	/*
	GameManager에서 curMapType(현재 선택된 게임맵)에 따른 타일들 정보 로딩
	현재 GameMap의 각 cell에 대한 Tile info를 불러오고 해당 cell의 타일 정보로 타일들 초기화 담당
	*/
	void Load();

private:
	/* Total tile fields */
	Object*		tiles[MAP_ROW][MAP_COL]{};

	TileInfo	infos[MAP_ROW][MAP_COL]{};

};
