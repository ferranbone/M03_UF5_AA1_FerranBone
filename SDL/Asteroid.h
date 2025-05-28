#pragma once
#include "GameObject.h"
#include "Utils.h"

enum AsteroidSize { LARGE, MEDIUM, SMALL };

class Asteroid : public GameObject {
public:
    Vector2 velocity;
    AsteroidSize asteroidSize;

    Asteroid(SDL_Renderer* renderer, AsteroidSize size);
    Asteroid(SDL_Renderer* renderer, Vector2 pos, Vector2 parentVel, AsteroidSize size);

    void Update(float dt) override;
    void Render(SDL_Renderer* rend) override;
    static Vector2 GetRandomOffscreenPosition();
};
