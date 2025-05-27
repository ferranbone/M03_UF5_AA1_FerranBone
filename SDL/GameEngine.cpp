#include "GameEngine.h"
#include "GameObject.h"

GameEngine::GameEngine(int windowWidth, int windowHeight) {
    InitSDL();
    InitWindowAndRenderer(windowWidth, windowHeight);

    // Crear escenas
    gameScene["MainMenu"] = new MenuScene();
    gameScene["Gameplay"] = new GameplayScene();
    gameScene["HighScores"] = new HighscoresScene();

    // Pasar la función para cambiar escena al MenuScene
    MenuScene* menu = static_cast<MenuScene*>(gameScene["MainMenu"]);
    if (menu) {
        menu->SetChangeSceneFunction([this](const std::string& sceneName) {
            if (currentScene) {
                currentScene->Exit();
            }
            currentScene = gameScene[sceneName];
            if (currentScene) {
                currentScene->Start(renderer);
            }
            });
    }

    // Iniciar escena actual
    currentScene = gameScene["MainMenu"];
    if (currentScene) {
        currentScene->Start(renderer);
    }
}


void GameEngine::Update() {
    bool quitGame = false;

    float dt = 0.0f;
    float lastTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();
    const int FPS = 60;
    const float frameTime = 1.0f / (float)FPS;

    while (!quitGame) {
        float currentTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();
        dt += currentTime - lastTime;
        lastTime = currentTime;

        if (dt > frameTime) {
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quitGame = true;
                }
                if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                    case SDLK_m:
                        if (currentScene) currentScene->Exit();
                        currentScene = gameScene["MainMenu"];
                        if (currentScene) currentScene->Start(renderer);
                        break;
                    case SDLK_h:
                        if (currentScene) currentScene->Exit();
                        currentScene = gameScene["HighScores"];
                        if (currentScene) currentScene->Start(renderer);
                        break;
                    case SDLK_g:
                        if (currentScene) currentScene->Exit();
                        currentScene = gameScene["Gameplay"];
                        if (currentScene) currentScene->Start(renderer);
                        break;
                    }
                }
            }

            if (currentScene) {
                currentScene->Update(dt);

                SDL_SetRenderDrawColor(renderer, 255, 120, 0, 255);
                SDL_RenderClear(renderer);
                currentScene->Render(renderer);
                SDL_RenderPresent(renderer);

                if (currentScene->IsFinished()) {
                    currentScene->Exit();
                    currentScene = gameScene[currentScene->GetTargetScene()];
                    if (currentScene)
                        currentScene->Start(renderer);
                }
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
    // WINDOWS
    window = SDL_CreateWindow("My Fist Game Engine",        // NAME
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,      // POSITION
        windowWidth, windowHeight,                            // SIZE
        SDL_WINDOW_SHOWN);                                    // SHOW BY DEFAULT

    if (window == nullptr) {
        std::cout << "Error al inicialzar window:" << SDL_GetError();
    }

    // RENDERER
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cout << "Error al inicialzar window:" << SDL_GetError();
    }
}
