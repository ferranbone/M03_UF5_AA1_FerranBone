#pragma once
#include "GameObject.h"
#include "Utils.h"
#include <vector>

class Bullet;

class Player : public GameObject {
public:
    Vector2 velocity;
    float speed;
    float rotationSpeed;

    Player(SDL_Renderer* renderer);

    void HandleInput(const Uint8* keystates, std::vector<Bullet*>& bullets, SDL_Renderer* renderer);
    void Update(float dt) override;
};
