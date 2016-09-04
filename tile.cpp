#include "tile.h"
#include "graphics.h"
#include <SDL.h>

Tile::Tile()
{
}

Tile::Tile(SDL_Texture * tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position) :
	tileset(tileset),
	size(size),
	tilesetPosition(tilesetPosition),
	position(Vector2(position.x * globals::SPRITESCALE, position.y * globals::SPRITESCALE))
{
}

void Tile::update(int elapsedTime)
{
}

void Tile::draw(Graphics & graphics)
{
	SDL_Rect destRect = { position.x, position.y, size.x * globals::SPRITESCALE,
		size.y * globals::SPRITESCALE };
	SDL_Rect sourceRect = { tilesetPosition.x, tilesetPosition.y, size.x, size.y };
	graphics.blitSurface(tileset, &sourceRect, &destRect);
}
