#include "level.h"
#include "graphics.h"
#include <SDL.h>
#include "globals.h"

Level::Level()
{
}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics & graphics) :
	mapName(mapName), 
	spawnPoint(spawnPoint),
	size(Vector2())
{
	loadMap(mapName, graphics);
}

Level::~Level()
{
}

void Level::update(int elapsedTime)
{

}

void Level::draw(Graphics & graphics)
{
	SDL_Rect sourceRect = {0, 0, 64, 64};
	SDL_Rect destRect;
	for (int x = 0; x < size.x / 64; x++)
	{
		for (int y = 0; y < size.y / 64; y++)
		{
			destRect.x = x * 64 * globals::SPRITESCALE;
			destRect.y = y * 64 * globals::SPRITESCALE;
			destRect.w = 64 * globals::SPRITESCALE;
			destRect.h = 64 * globals::SPRITESCALE;
			graphics.blitSurface(backgroundTexture, &sourceRect, &destRect);
		}
	}
}

void Level::loadMap(std::string mapName, Graphics & graphics)
{
	//load bg
	backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
		graphics.loadImage("bkBlue.png"));
	size = Vector2(1280, 960);
}
