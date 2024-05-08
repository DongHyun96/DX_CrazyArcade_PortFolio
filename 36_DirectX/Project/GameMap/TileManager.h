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
	/// ���ο� TileManager ���� ��, GameManager�� curMapType�� ���� �̸� ����� Tile���� Load�ϸ鼭 Tile�� ������ �� ���
	/// </summary>
	/// <param name="info"> : �ش� �ڸ� Tile info </param>
	/// <param name="boardX"> : ������ �ڸ��� cell pos X </param>
	/// <param name="boardY"> : ������ �ڸ��� cell pos Y </param>
	void CreateTile(const TileInfo& info, UINT boardX, UINT boardY);

	/*
	GameManager���� curMapType(���� ���õ� ���Ӹ�)�� ���� Ÿ�ϵ� ���� �ε�
	���� GameMap�� �� cell�� ���� Tile info�� �ҷ����� �ش� cell�� Ÿ�� ������ Ÿ�ϵ� �ʱ�ȭ ���
	*/
	void Load();

private:
	/* Total tile fields */
	Object*		tiles[MAP_ROW][MAP_COL]{};

	TileInfo	infos[MAP_ROW][MAP_COL]{};

};
