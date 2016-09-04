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
	boundingBox = Rectangle(x, y, width * globals::SPRITESCALE, height * globals::SPRITESCALE);
}

Sprite::~Sprite()
{
}

void Sprite::update()
{
	boundingBox = Rectangle(x, y, sourceRect.w * globals::SPRITESCALE, sourceRect.h * globals::SPRITESCALE);
}

void Sprite::draw(Graphics & graphics, int x, int y)
{
	SDL_Rect destRect = { x, y, sourceRect.w * globals::SPRITESCALE, sourceRect.h * globals::SPRITESCALE};
	graphics.blitSurface(spriteSheet, &sourceRect, &destRect);
}

const Rectangle Sprite::getBoundingBox() const
{
	return boundingBox;
}

const sides::Side Sprite::getCollisionSide(Rectangle &rectangle) const
{
	int amountRight, amountLeft, amountTop, amountBottom;
	amountRight = getBoundingBox().getRight() - rectangle.getLeft();
	amountLeft = rectangle.getRight() - getBoundingBox().getLeft();
	amountTop = rectangle.getBottom() - getBoundingBox().getTop();
	amountBottom = getBoundingBox().getBottom() - rectangle.getTop();

	int vals[4] = { abs(amountRight), abs(amountLeft), abs(amountTop), abs(amountBottom) };
	int lowest = vals[0];
	for (int i = 0; i < 4; i++)
	{
		if (vals[i] < lowest) {
			lowest = vals[i];
		}
	}

	return lowest == abs(amountRight) ? sides::RIGHT :
		lowest == abs(amountLeft) ? sides::LEFT :
		lowest == abs(amountTop) ? sides::TOP :
		lowest == abs(amountBottom) ? sides::BOTTOM :
		sides::NONE;

}
