#include "Asteroid.h"
#include <cmath>
#include <cstdlib>

Asteroid::Asteroid(SDL_Renderer* renderer, AsteroidSize s) : GameObject(renderer, new Vector2int(0, 53), new Vector2int(73, 70)) {
    asteroidSize = s;
    position = GetRandomOffscreenPosition();

    switch (asteroidSize) {
    case LARGE:  scale = Vector2(1.0f, 1.0f); break;
    case MEDIUM: scale = Vector2(0.6f, 0.6f); break;
    case SMALL:  scale = Vector2(0.3f, 0.3f); break;
    }

    float speed = 50 + rand() % 100;
    float angle = rand() % 360;
    float rad = angle * 3.14159f / 180.0f;
    velocity = Vector2(cos(rad) * speed, sin(rad) * speed);
}

Asteroid::Asteroid(SDL_Renderer* renderer, Vector2 pos, Vector2 parentVel, AsteroidSize s) :
    GameObject(renderer, new Vector2int(0, 53), new Vector2int(73, 70)) {

    asteroidSize = s;
    position = pos;

    switch (asteroidSize) {
    case LARGE:  scale = Vector2(1.0f, 1.0f); break;
    case MEDIUM: scale = Vector2(0.6f, 0.6f); break;
    case SMALL:  scale = Vector2(0.3f, 0.3f); break;
    }

    float variation = 0.5f + (rand() % 100) / 100.0f; // 0.5 - 1.5
    velocity = Vector2(
        parentVel.x * variation,
        parentVel.y * variation
    );
}

Vector2 Asteroid::GetRandomOffscreenPosition() {
    int edge = rand() % 4;
    switch (edge) {
    case 0: return Vector2(rand() % 600, -100);
    case 1: return Vector2(700, rand() % 600);
    case 2: return Vector2(rand() % 600, 700);
    case 3: return Vector2(-100, rand() % 600);
    default: return Vector2(rand() % 600, -100);
    }
}

void Asteroid::Update(float dt) {
    position = position + velocity * dt;

    if (position.x < 0) position.x = 600;
    if (position.x > 600) position.x = 0;
    if (position.y < 0) position.y = 600;
    if (position.y > 600) position.y = 0;
}

void Asteroid::Render(SDL_Renderer* rend) {
    if (!texture) return;


    int scaledWidth = static_cast<int>(size.x * scale.x);
    int scaledHeight = static_cast<int>(size.y * scale.y);

    SDL_Rect destRect = {
        static_cast<int>(position.x - scaledWidth / 2),
        static_cast<int>(position.y - scaledHeight / 2),
        scaledWidth,
        scaledHeight
    };

    SDL_Rect srcRect = {
        textureCoor.x,
        textureCoor.y,
        size.x,
        size.y
    };
    SDL_RenderCopyEx(rend, texture, &srcRect, &destRect, zRotation, nullptr, SDL_FLIP_NONE);
}