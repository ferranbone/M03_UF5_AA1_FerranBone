#include "HighscoresScene.h"
#include <fstream>
#include <algorithm>
#include <iostream>

void HighscoresScene::Start(SDL_Renderer* renderer) {
    font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);
    if (!font) {
        std::cout << "Error cargando fuente: " << TTF_GetError() << "\n";
        return;
    }

    LoadScores();
    isFinished = false;
}

void HighscoresScene::Update(float dt) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_m) {
            targetScene = "MainMenu";
            isFinished = true;
        }
    }
}

void HighscoresScene::Render(SDL_Renderer* renderer) {
    SDL_Color color = { 255, 255, 255, 255 };

    int y = 100;
    for (size_t i = 0; i < scores.size(); ++i) {
        std::string text = std::to_string(i + 1) + ". " + std::to_string(scores[i]);
        SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);

        SDL_Rect rect = { 100, y, surf->w, surf->h };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);

        SDL_FreeSurface(surf);
        SDL_DestroyTexture(texture);

        y += 40;
    }
}

void HighscoresScene::Exit() {
    if (font) TTF_CloseFont(font);
    scores.clear();
}

void HighscoresScene::LoadScores() {
    scores.clear();
    std::ifstream file("highscores.txt");
    int score;

    while (file >> score && scores.size() < 10) {
        scores.push_back(score);
    }
    file.close();
}

void HighscoresScene::SaveScores() {
    std::ofstream file("highscores.txt");
    for (int score : scores) {
        file << score << "\n";
    }
    file.close();
}

void HighscoresScene::AddScore(int score) {
    scores.push_back(score);
    std::sort(scores.begin(), scores.end(), std::greater<int>());

    if (scores.size() > 10) {
        scores.resize(10);
    }

    SaveScores();
}
