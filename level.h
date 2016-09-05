#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "globals.h"
#include "tile.h"
#include <vector>
#include "rectangle.h"
#include "slope.h"

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
	std::vector<Rectangle> checkTileCollisions(const Rectangle &rectangle);
	std::vector<Slope> checkSlopeCollisions(const Rectangle &other);
	const Vector2 getPlayerSpawnPoint() const;
private:
	std::string mapName;
	Vector2 spawnPoint;
	Vector2 size;
	Vector2 tileSize;
	SDL_Texture* backgroundTexture;
	std::vector<Tile> tileList;
	std::vector<Tileset> tilesets;
	std::vector<Rectangle> collisionRects;
	std::vector<Slope> slopes;
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