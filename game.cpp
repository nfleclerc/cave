#include <SDL.h>
#include <stdio.h>
#include <algorithm>
#include "game.h"
#include "graphics.h"
#include "input.h"


namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}

void Game::draw(Graphics &graphics) 
{
	graphics.clear();
	player.draw(graphics, 100, 100);
	graphics.flip();
}

void Game::gameLoop()
{
	Graphics graphics;
	Input input;
	SDL_Event event;
	player = Sprite(graphics, 
		"MyChar.png", 
		0, 0, 16, 16, 100, 100);
	
	int LAST_UPDATE_TIME = SDL_GetTicks();
	while (true)
	{
		input.beginNewFrame();
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}
		const int CURRENT_TIME = SDL_GetTicks();
		int ELAPSED_TIME = CURRENT_TIME - LAST_UPDATE_TIME;
		update(std::min(ELAPSED_TIME, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME;
		draw(graphics);
	}
}

void Game::update(float elapsedTime)
{

}

Game::~Game() {

}