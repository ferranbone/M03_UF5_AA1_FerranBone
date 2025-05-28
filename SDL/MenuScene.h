#pragma once
#include "Scene.h"
#include "Button.h"
#include <vector>
#include <SDL_ttf.h>

class MenuScene : public Scene {
public:
    void Start(SDL_Renderer* renderer) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;
    void Exit() override;

    void SetChangeSceneFunction(std::function<void(const std::string&)> func) {
        changeSceneFunc = func;
    }

private:
    std::function<void(const std::string&)> changeSceneFunc;
    std::vector<Button*> buttons;
    TTF_Font* font = nullptr;
    SDL_Color backgroundColor = { 20, 20, 40, 255 };
    SDL_Renderer* renderer;
};