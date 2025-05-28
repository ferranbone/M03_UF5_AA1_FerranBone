#pragma once
#include "Scene.h"
#include <vector>
#include <string>
#include <SDL_ttf.h>

class HighscoresScene : public Scene {
private:
    std::vector<int> scores;
    TTF_Font* font = nullptr;

public:
    void Start(SDL_Renderer* renderer) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;
    void Exit() override;

    void LoadScores();
    void SaveScores();
    void AddScore(int score);
};
