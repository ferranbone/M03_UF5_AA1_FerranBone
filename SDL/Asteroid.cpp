#include "Asteroid.h"
#include <cstdlib>

Asteroid::Asteroid(SDL_Renderer* renderer, Vector2 pos, AsteroidSize s) : GameObject(renderer) {
    position = pos;
    size = s;

    float speed = 50 + rand() % 100;
    float angle = rand() % 360;
    float rad = angle * 3.14159f / 180.0f;
    velocity = Vector2(cos(rad) * speed, sin(rad) * speed);
}

void Asteroid::Update(float dt) {
    position = Vector2(position.x + velocity.x * dt, position.y + velocity.y * dt);

    if (position.x < 0) position.x = 500;
    if (position.x > 500) position.x = 0;
    if (position.y < 0) position.y = 500;
    if (position.y > 500) position.y = 0;
}
