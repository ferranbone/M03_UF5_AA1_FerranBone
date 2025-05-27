#pragma once
#include <SDL.h>
#include <iostream>

class GameEngine {
public:
	SDL_Window* window;
	SDL_Renderer* renderer;

	GameEngine(int windowWidth, int windowHeight);

	void Update();
	void Finish();

	void InitSDL();
	void InitWindowAndRenderer(int windowWidth, int windowHeight);

};