#pragma once
#include "GameObject.h"
#include "Utils.h"

enum AsteroidSize { LARGE, MEDIUM, SMALL };

class Asteroid : public GameObject {
public:
    Vector2 velocity;
    AsteroidSize size;

    Asteroid(SDL_Renderer* renderer, Vector2 pos, AsteroidSize size);

    void Update(float dt) override;
};
