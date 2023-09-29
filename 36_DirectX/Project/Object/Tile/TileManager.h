#pragma once
class TileManager
{
public:
	TileManager();
	~TileManager();

	void Update();
	void Render();

private:

	void CreateTile(UINT boardX, UINT boardY, wstring file, 
					UINT frameX = 1, UINT frameY = 1,
					UINT targetX = 1, UINT targetY = 1,
					Vector2 size = Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW));

private:

	
	Object* tiles[MAP_ROW][MAP_COL]{};

};
