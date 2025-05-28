#pragma once
#include "GameObject.h"
#include "Utils.h"

class Enemy : public GameObject {
public:
    Vector2 velocity;
    float directionChangeTimer = 0.0f;
    const float DIRECTION_CHANGE_TIME = 1.0f;

    Enemy(SDL_Renderer* renderer, Vector2 position);
    void Update(float dt) override;
    void ChangeDirection();
};