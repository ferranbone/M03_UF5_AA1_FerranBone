#include "Bullet.h"
#include <cmath>

Bullet::Bullet(SDL_Renderer* renderer, Vector2 pos, float angle) : GameObject(renderer, new Vector2int(34, 32), new Vector2int(5, 5)) {
    position = pos;
    float rad = (angle - 90.0f) * 3.14159f / 180.0f;
    velocity = Vector2(cos(rad) * 300, sin(rad) * 300);
    lifetime = 2.0f;
}

void Bullet::Update(float dt) {
    position = Vector2(position.x + velocity.x * dt, position.y + velocity.y * dt);
    lifetime -= dt;

    if (position.x < 0) position.x = 600;
    if (position.x > 600) position.x = 0;
    if (position.y < 0) position.y = 600;
    if (position.y > 600) position.y = 0;
}
