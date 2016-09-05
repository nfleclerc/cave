#ifndef ANIMATED_TILE_H
#define ANIMATED_TILE_H

#include "tile.h"
#include <vector>

class AnimatedTile : public Tile {
public:
	AnimatedTile(std::vector<Vector2> tilesetPostions, int duration, 
		SDL_Texture* tileset, Vector2 size, Vector2 position);
	void update(int elapsedTime);
	void draw(Graphics &graphics);
protected:
	int amountOfTime = 0;
	bool notDone = false;
private:
	std::vector<Vector2> tilesetPositions;
	int tileToDraw;
	int duration;
};

struct AnimatedTileInfo {
public:
	int tilesetsFirstGid;
	int startTileId;
	std::vector<int> tileIds;
	int duration;
};

#endif // !ANIMATED_TILE_H
