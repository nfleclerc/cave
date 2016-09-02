#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "globals.h"
#include <iostream>


Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(globals::SCREENWIDTH, globals::SCREENHEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Cavestory");
}

SDL_Surface* Graphics::loadImage(const std::string &filepath) {
	if (spriteSheets.count(filepath) == 0) {
		spriteSheets[filepath] = IMG_Load(filepath.c_str());
			std::cout << "ERROR: " << IMG_GetError() << std::endl;
	}
	return spriteSheets[filepath];
}

void Graphics::blitSurface(SDL_Texture* source, SDL_Rect* sourceRect, SDL_Rect* destRect)
{
	SDL_RenderCopy(renderer, source, sourceRect, destRect);
}

void Graphics::flip()
{
	SDL_RenderPresent(renderer);
}

void Graphics::clear()
{
	SDL_RenderClear(renderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
	return renderer;
}

Graphics::~Graphics() {
	SDL_DestroyWindow(window);
}
