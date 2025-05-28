#include "GameEngine.h"

int SDL_main(int argc, char* argv[]) {

	GameEngine myEngine(1920,1080);
	myEngine.Update();
	myEngine.Finish();


	return 0;
}