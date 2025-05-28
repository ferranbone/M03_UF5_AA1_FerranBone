#include "Enemy.h"
#include <cstdlib>
#include <cmath>

Enemy::Enemy(SDL_Renderer* renderer, Vector2 position) :
    GameObject(renderer, /* spriteRect */) {
    this->position = position;
    ChangeDirection();
}

void Enemy::Update(float dt) {
    // Movimiento
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // Cambio de dirección
    directionChangeTimer -= dt;
    if (directionChangeTimer <= 0) {
        ChangeDirection();
        directionChangeTimer = DIRECTION_CHANGE_TIME;
    }
}

void Enemy::ChangeDirection() {
    float speed = 100.0f; // Velocidad base
    float angle = (rand() % 360) * (3.14159f / 180.0f);
    velocity = Vector2(cos(angle) * speed, sin(angle) * speed);
}