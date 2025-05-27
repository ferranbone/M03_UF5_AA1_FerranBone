#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <functional>

class Button {
public:
    Button(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Rect rect,
        SDL_Color normalColor, SDL_Color hoverColor, std::function<void()> onClick);

    void HandleEvent(SDL_Event& e);
    void Render(SDL_Renderer* renderer);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string text;
    SDL_Rect rect;
    SDL_Color normalColor, hoverColor;
    std::function<void()> onClick;
    bool isHovered;
};
