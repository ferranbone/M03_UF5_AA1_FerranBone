#pragma once
#include "Scene.h"
#include "Button.h"
#include <vector>

class MenuScene : public Scene {
public:
    void Start(SDL_Renderer* renderer) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;
    void Exit() override;

private:
    std::vector<Button*> buttons;
};
