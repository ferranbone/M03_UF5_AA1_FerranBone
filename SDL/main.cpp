#include "GameEngine.h"

int SDL_main(int argc, char* argv[]) {

	GameEngine myEngine(600,600);
	myEngine.Update();
	myEngine.Finish();


	return 0;
}