#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "globals.h"
#include "tile.h"
#include <vector>


class Graphics;
struct SDL_Texture;
struct Tileset;
struct SDL_Rect;

class Level {
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
	~Level();
	void update(int elapsedTime);
	void draw(Graphics &graphics);
private:
	std::string mapName;
	Vector2 spawnPoint;
	Vector2 size;
	Vector2 tileSize;
	SDL_Texture* backgroundTexture;
	std::vector<Tile> tileList;
	std::vector<Tileset> tilesets;

	void loadMap(std::string mapName, Graphics &graphics);
};

struct Tileset {
	SDL_Texture* texture;
	int firstgid;
	Tileset() {
		firstgid = -1;
	}
	Tileset(SDL_Texture* texture, int firstgid) {
		this->texture = texture;
		this->firstgid = firstgid;
	}
};

#endif LEVEL_H