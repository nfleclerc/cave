#ifndef TILE_H
#define TILE_H

#include "globals.h"

struct SDL_Texture;
class Graphics;

class Tile {
public:
	Tile();
	Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
	void update(int elapsedTime);
	void draw(Graphics &graphics);
protected:
	SDL_Texture* tileset;
	Vector2 size;
	Vector2 tilesetPosition;
	Vector2 position;
};



#endif // !TILE_H
