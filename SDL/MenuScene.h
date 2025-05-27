#pragma once
#include "Scene.h"
#include "Button.h"
#include <vector>
#include <SDL_ttf.h>
#include <functional>

class MenuScene : public Scene {
public:
    void SetChangeSceneFunction(std::function<void(const std::string&)> func);


    void Start(SDL_Renderer* renderer) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;
    void Exit() override;

private:
    std::function<void(const std::string&)> changeSceneFunc;
    std::vector<Button*> buttons;
    TTF_Font* font = nullptr;
};
