#include "Button.h"
#include <SDL_ttf.h>

Button::Button(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Rect rect,
    SDL_Color normalColor, SDL_Color hoverColor, std::function<void()> onClick)
    : renderer(renderer), font(font), text(text), rect(rect),
    normalColor(normalColor), hoverColor(hoverColor), onClick(onClick), isHovered(false) {}

void Button::HandleEvent(const SDL_Event& e) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Point point = { mouseX, mouseY };
    isHovered = SDL_PointInRect(&point, &rect);

    if (isHovered && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        onClick();
    }
}

void Button::Render(SDL_Renderer* renderer) {
    // Dibuja fondo del botón
    SDL_Color currentColor = isHovered ? hoverColor : normalColor;
    SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
    SDL_RenderFillRect(renderer, &rect);

    // Renderiza el texto del botón
    if (font && !text.empty()) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), { 0, 0, 0, 255 });  // Texto negro
        if (textSurface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (texture) {
                // Centra el texto en el rectángulo
                SDL_Rect textRect;
                textRect.w = textSurface->w;
                textRect.h = textSurface->h;
                textRect.x = rect.x + (rect.w - textRect.w) / 2;
                textRect.y = rect.y + (rect.h - textRect.h) / 2;

                SDL_RenderCopy(renderer, texture, nullptr, &textRect);
                SDL_DestroyTexture(texture);
            }
            SDL_FreeSurface(textSurface);
        }
    }
}
