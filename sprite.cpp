#include "sprite.h"
#include "graphics.h"
#include "globals.h"
#include <stdio.h>

Sprite::Sprite()
{
}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
	int height, int width, float posX, float posY) : x(posX), y(posY)
{
	sourceRect.x = sourceX;
	sourceRect.y = sourceY;
	sourceRect.w = width;
	sourceRect.h = height;
	spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (spriteSheet == NULL) {
		printf("\nError: Unable to load image\n");
	}
}

Sprite::~Sprite()
{
}

void Sprite::update()
{
}

void Sprite::draw(Graphics & graphics, int x, int y)
{
	SDL_Rect destRect = { x, y, sourceRect.w * globals::SPRITESCALE, sourceRect.h * globals::SPRITESCALE};
	graphics.blitSurface(spriteSheet, &sourceRect, &destRect);
}
