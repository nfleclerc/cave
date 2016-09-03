#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>

class Graphics;

class Sprite {
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
		int height, int width, float posX, float posY);
	virtual ~Sprite();
	virtual void update();
	void draw(Graphics &graphics, int x, int y);
protected:
	SDL_Rect sourceRect;
	SDL_Texture* spriteSheet;
	float x, y;
};

#endif // !SPRITE_H
