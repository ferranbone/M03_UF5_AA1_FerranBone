#include "MenuScene.h"
#include <SDL.h>
#include <iostream>

void MenuScene::Start(SDL_Renderer* renderer) {
    this->renderer = renderer;

    if (TTF_Init() == -1) {
        std::cerr << "Error al inicializar SDL_ttf: " << TTF_GetError() << std::endl;
        return;
    }

    // Cargar fuente
    font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);
    if (!font) {
        std::cerr << "Error al cargar fuente: " << TTF_GetError() << std::endl;
        return;
    }

    // Definir colores
    SDL_Color normalColor = { 100, 100, 255, 255 };   // Azul
    SDL_Color hoverColor = { 150, 150, 255, 255 };    // Azul claro
    SDL_Color pressColor = { 50, 50, 200, 255 };      // Azul oscuro

    // Crear botones
    int screenWidth = 600;
    int buttonWidth = 200;
    int buttonHeight = 50;

    buttons.push_back(new Button(
        renderer, font, "JUGAR (pulsa g)",
        screenWidth / 2 - buttonWidth / 2, 200, buttonWidth, buttonHeight,
        normalColor, hoverColor, pressColor,
        [this]() {
            std::cout << "Cambiando a escena de juego" << std::endl;
            targetScene = "Gameplay";
            isFinished = true;
        }
    ));

    buttons.push_back(new Button(
        renderer, font, "SALIR",
        screenWidth / 2 - buttonWidth / 2, 300, buttonWidth, buttonHeight,
        normalColor, hoverColor, pressColor,
        [this]() {
            SDL_Event quitEvent;
            quitEvent.type = SDL_QUIT;
            SDL_PushEvent(&quitEvent);
        }
    ));
}

void MenuScene::Update(float dt) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        for (auto button : buttons) {
            button->HandleEvent(e);
        }
    }
}

void MenuScene::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 30, 30, 60, 255);
    SDL_RenderClear(renderer);

    for (auto button : buttons) {
        button->Render(renderer);
    }
}

void MenuScene::Exit() {
    for (auto button : buttons) {
        delete button;
    }
    buttons.clear();

    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}