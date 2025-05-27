#include "Player.h"
#include "Bullet.h"
#include <cmath>

Player::Player(SDL_Renderer* renderer)
    : GameObject(renderer), velocity(0, 0), speed(100.0f), rotationSpeed(180.0f)
{
    position = Vector2(400, 300);  // posición inicial, cambia si quieres
    scale = Vector2(1, 1);
    zRotation = 0.0f;
}

void Player::HandleInput(const Uint8* keystates, std::vector<Bullet*>& bullets, SDL_Renderer* renderer) {
    if (keystates[SDL_SCANCODE_LEFT]) {
        zRotation -= rotationSpeed * 0.016f;
    }
    if (keystates[SDL_SCANCODE_RIGHT]) {
        zRotation += rotationSpeed * 0.016f;
    }
    if (keystates[SDL_SCANCODE_UP]) {
        float rad = (zRotation - 90.0f) * M_PI / 180.0f;
        velocity.x += cos(rad) * speed * 0.016f;
        velocity.y += sin(rad) * speed * 0.016f;
    }
}

void Player::Update(float dt) {
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // Freno gradual para que no salga volando
    velocity.x *= 0.98f;
    velocity.y *= 0.98f;

    // Reaparición en pantalla (ajusta según tamaño ventana)
    if (position.x < 0) position.x += 500;
    else if (position.x > 500) position.x -= 350;

    if (position.y < 0) position.y += 300;
    else if (position.y > 300) position.y -= 300;
}
