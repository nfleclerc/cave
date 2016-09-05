#include "animatedtile.h"
#include "graphics.h"

AnimatedTile::AnimatedTile(std::vector<Vector2> tilesetPostions, int duration, SDL_Texture * tileset,
	Vector2 size, Vector2 position) :
	Tile(tileset, size, tilesetPositions.at(0), position),
	tilesetPositions(tilesetPositions),
	duration(duration),
	tileToDraw(0)
{
}

void AnimatedTile::update(int elapsedTime)
{
	if (amountOfTime <= 0) {
		if (tileToDraw == tilesetPositions.size() - 1) {
			tileToDraw = 0;
		}
		else {
			tileToDraw++;
		}
		amountOfTime = duration;
	}
	else {
		amountOfTime -= elapsedTime;
	}
	Tile::update(elapsedTime);
}

void AnimatedTile::draw(Graphics & graphics)
{
	SDL_Rect destRect = { position.x, position.y,
		size.x * globals::SPRITE_SCALE, size.y * globals::SPRITE_SCALE };
	SDL_Rect sourceRect = { tilesetPositions.at(tileToDraw).x, tilesetPositions.at(tileToDraw).y,
		size.x, size.y };
	graphics.blitSurface(tileset, &sourceRect, &destRect);
}
