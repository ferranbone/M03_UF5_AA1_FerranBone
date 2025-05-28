#include "MenuScene.h"
#include <SDL.h>
#include <iostream>

void MenuScene::Start(SDL_Renderer* renderer) {

    if (TTF_WasInit() == 0) {
        if (TTF_Init() == -1) {
            std::cout << "Error inicializando SDL_ttf: " << TTF_GetError() << "\n";
            return;
        }
    }

    font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);
    if (!font) {
        std::cout << "Error cargando la fuente: " << TTF_GetError() << "\n";
        return;
    }

    SDL_Color normalColor = { 255, 255, 255, 255 }; // blanco
    SDL_Color hoverColor = { 0, 0, 0, 0 };      // rojo

    int centerX = 1920 / 2 - 100;
    int centerY = 1080 / 2 - 25;

    buttons.push_back(new Button(renderer, font, "Play", { centerX, centerY - 50, 200, 50 }, normalColor, hoverColor, [this]() {
        std::cout << "Botón Play clickeado!" << std::endl;  // <-- Aquí la comprobación

        this->SetTargetScene("Gameplay");
        this->MarkAsFinished();
        }));

    buttons.push_back(new Button(renderer, font, "Exit", { centerX, centerY + 50, 200, 50 }, normalColor, hoverColor, []() {
        std::cout << "Exit clicked\n";
        SDL_Quit();
        exit(0);
        }));
}

void MenuScene::Update(float dt) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        for (auto button : buttons) {
            button->HandleEvent(e);
        }
        if (e.type == SDL_QUIT) {
            // Si quieres, maneja quit aquí o en otro lugar
        }
    }
}

void MenuScene::SetChangeSceneFunction(std::function<void(const std::string&)> func) {
    changeSceneFunc = func;
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
