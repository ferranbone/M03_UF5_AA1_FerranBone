#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
public:
    Vector2 velocity;
    float lifetime;

    Bullet(SDL_Renderer* renderer, Vector2 pos, float angle);

    void Update(float dt) override;
};
