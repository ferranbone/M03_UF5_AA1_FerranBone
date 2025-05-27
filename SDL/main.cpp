#include "GameEngine.h"

int SDL_main(int argc, char* argv[]) {

	GameEngine myEngine(500,500);
	myEngine.Update();
	myEngine.Finish();


	return 0;
}