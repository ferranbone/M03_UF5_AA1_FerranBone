#pragma once
#include <SDL.h>
#include <iostream>
#include <map>

#include "Scene.h"
#include "MenuScene.h"
#include "HighscoresScene.h"
#include "GameplayScene.h"

class GameEngine {
public:
    GameEngine(int windowWidth, int windowHeight);
    void Update();
    void Finish();

private:
    void InitSDL();
    void InitWindowAndRenderer(int windowWidth, int windowHeight);

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::map<std::string, Scene*> gameScene;
    Scene* currentScene = nullptr;
};
