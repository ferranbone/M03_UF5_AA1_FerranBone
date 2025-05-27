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
    SDL_Color hoverColor = { 255, 0, 0, 255 };      // rojo

    buttons.push_back(new Button(renderer, font, "Play", { 300, 200, 200, 50 }, normalColor, hoverColor, []() {
        std::cout << "Play clicked\n";
        }));

    buttons.push_back(new Button(renderer, font, "Exit", { 300, 300, 200, 50 }, normalColor, hoverColor, []() {
        std::cout << "Exit clicked\n";
        SDL_Quit();
        exit(0);
        }));
}

void Button::HandleEvent(SDL_Event& e) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Point mousePos = { mouseX, mouseY };
    isHovered = SDL_PointInRect(&mousePos, &rect);

    if (isHovered && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        onClick();
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
