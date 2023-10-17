#pragma once

class TileManager
{
public:
	TileManager();
	~TileManager();

	void Update();
	void Render();

private:

	void CreateTile(const TileInfo& info, UINT boardX, UINT boardY);

	void Load();

private:
	Object* tiles[MAP_ROW][MAP_COL]{};

	TileInfo infos[MAP_ROW][MAP_COL]{};

};
