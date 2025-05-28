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

    int lives = 3;
    bool isDead = false;
    float deathTimer = 0.f;
    const float DEATH_ANIMATION_TIME = 3.0f;

    float shootCooldown = 0.0f;
    const float SHOOT_COOLDOWN_TIME = 0.5f;
    bool canShoot = true;

    void Reset();

    Player(SDL_Renderer* renderer);

    void HandleInput(const Uint8* keystates, std::vector<Bullet*>& bullets, SDL_Renderer* renderer);
    void Update(float dt) override;
};
