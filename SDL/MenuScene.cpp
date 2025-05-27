#include "MenuScene.h"
#include <SDL.h>
#include <iostream>

void MenuScene::Start(SDL_Renderer* renderer) {
    buttons.push_back(new Button({ 300, 200, 200, 50 }, []() {
        std::cout << "Play clicked\n";
        }));

    buttons.push_back(new Button({ 300, 300, 200, 50 }, []() {
        std::cout << "Exit clicked\n";
        SDL_Quit();
        exit(0);
        }));
}

void MenuScene::Update(float dt) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        for (auto& b : buttons) {
            b->HandleEvent(e);
        }
    }
}

void MenuScene::Render(SDL_Renderer* renderer) {
    for (auto& b : buttons) {
        b->Render(renderer);
    }
}

void MenuScene::Exit() {
    for (auto b : buttons) delete b;
    buttons.clear();
}
