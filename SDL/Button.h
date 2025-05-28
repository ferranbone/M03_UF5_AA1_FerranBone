#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <functional>
#include <string>

class Button {
public:
    Button(SDL_Renderer* renderer, TTF_Font* font, const std::string& text,
        int x, int y, int width, int height,
        SDL_Color normalColor, SDL_Color hoverColor, SDL_Color pressColor,
        std::function<void()> onClick);
    ~Button();

    void HandleEvent(const SDL_Event& e);
    void Render(SDL_Renderer* renderer);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string text;
    SDL_Rect rect;
    SDL_Color normalColor;
    SDL_Color hoverColor;
    SDL_Color pressColor;
    SDL_Color currentColor;
    std::function<void()> onClick;

    SDL_Texture* texture = nullptr;
    bool isHovered = false;
    bool isPressed = false;

    void UpdateTexture();
    bool IsMouseOver(int mouseX, int mouseY) const;
};