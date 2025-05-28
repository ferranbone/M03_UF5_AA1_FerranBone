#include "Button.h"
#include <iostream>

Button::Button(SDL_Renderer* renderer, TTF_Font* font, const std::string& text,
    int x, int y, int width, int height,
    SDL_Color normalColor, SDL_Color hoverColor, SDL_Color pressColor,
    std::function<void()> onClick)
    : renderer(renderer), font(font), text(text),
    normalColor(normalColor), hoverColor(hoverColor), pressColor(pressColor),
    onClick(onClick) {
    rect = { x, y, width, height };
    currentColor = normalColor;
    UpdateTexture();
}

Button::~Button() {
    if (texture) SDL_DestroyTexture(texture);
}

void Button::HandleEvent(const SDL_Event& e) {
    switch (e.type) {
    case SDL_MOUSEMOTION: {
        int mouseX = e.motion.x;
        int mouseY = e.motion.y;

        bool wasHovered = isHovered;
        isHovered = IsMouseOver(mouseX, mouseY);

        if (isHovered != wasHovered) {
            currentColor = isHovered ? (isPressed ? pressColor : hoverColor) : normalColor;
            UpdateTexture();
            std::cout << text << ": " << (isHovered ? "HOVER" : "NORMAL") << std::endl;
        }
        break;
    }

    case SDL_MOUSEBUTTONDOWN: {
        if (e.button.button == SDL_BUTTON_LEFT && isHovered) {
            isPressed = true;
            currentColor = pressColor;
            UpdateTexture();
            std::cout << text << ": PRESSED" << std::endl;
        }
        break;
    }

    case SDL_MOUSEBUTTONUP: {
        if (e.button.button == SDL_BUTTON_LEFT && isPressed && isHovered) {
            if (onClick) onClick();
            std::cout << text << ": CLICKED" << std::endl;
        }
        isPressed = false;
        currentColor = isHovered ? hoverColor : normalColor;
        UpdateTexture();
        break;
    }
    }
}

void Button::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, 100);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);

    if (texture) {
        int texW, texH;
        SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
        SDL_Rect textRect = {
            rect.x + (rect.w - texW) / 2,
            rect.y + (rect.h - texH) / 2,
            texW,
            texH
        };
        SDL_RenderCopy(renderer, texture, nullptr, &textRect);
    }
}

void Button::UpdateTexture() {
    if (texture) SDL_DestroyTexture(texture);

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), { 255, 255, 255, 255 });
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}

bool Button::IsMouseOver(int mouseX, int mouseY) const {
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
        mouseY >= rect.y && mouseY <= rect.y + rect.h);
}