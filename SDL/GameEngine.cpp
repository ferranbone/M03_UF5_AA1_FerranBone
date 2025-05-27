#include "GameEngine.h"
#include "GameObject.h"

GameEngine::GameEngine(int windowWidth, int windowHeight) {
	InitSDL();
	InitWindowAndRenderer(windowWidth, windowHeight);

}

void GameEngine::Update() {
	bool quitGame = false;

	GameObject object(renderer);

	//INT TIME
	float dt = 0.0f;
	float lastTime = (float)SDL_GetPerformanceCounter() /(float)SDL_GetPerformanceFrequency();

	const int FPS = 60;
	const float frameTime = 1.0f/(float)FPS;

	//SCENES
	std::map<std::string, Scene*> gameScene;

	gameScene["MainMenu"] = new MenuScene();
	gameScene["Gameplay"] = new GameplayScene();
	gameScene["HightScores"] = new HighscoresScene();

	Scene* currentScene = gameScene["Gameplay"];
	currentScene->Start(renderer);

	while (!quitGame) {
		//DETLTA TIME CONTROL
		float currentTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();
		dt += currentTime - lastTime;

		if (dt > frameTime) {
			//INPUTS
			SDL_Event e;

			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quitGame = true;
				}
			}

			//LOGIC
			currentScene->Update(dt);

			//RENDER
			SDL_SetRenderDrawColor(renderer, 255, 120, 0, 1); //Que queremos que pinte

			SDL_RenderClear(renderer);						  //Limpia lo anterior
			currentScene->Render(renderer);
			SDL_RenderPresent(renderer);					  //Pintamos lo nuevo


			//SCENES TRANSITION
			if (currentScene->IsFinished()) {
				currentScene->Exit();
				currentScene = gameScene[currentScene->GetTargetScene()];
				currentScene->Start(renderer);
			}

			dt -= frameTime;
		}
	}
}

void GameEngine::Finish() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void GameEngine::InitSDL() {
	int result = SDL_Init(SDL_INIT_VIDEO);

	if (result < 0) {
		std::cout << "Error al inicialzar SDL:" << SDL_GetError();
	}
}
void GameEngine::InitWindowAndRenderer(int windowWidth, int windowHeight) {
	//WINDOWS
	window = SDL_CreateWindow("My Fist Game Engine",		//NAME
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,		//POSITION
		windowWidth, windowHeight,							//SIZE
		SDL_WINDOW_SHOWN);									//SHOW BY DEFAULT
				
	if (window == nullptr) {
		std::cout << "Error al inicialzar window:" << SDL_GetError();
	}

	//RENDERER
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cout << "Error al inicialzar window:" << SDL_GetError();
	}

}