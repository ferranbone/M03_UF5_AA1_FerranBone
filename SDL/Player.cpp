#include "Player.h"
#include "Bullet.h"
#include "Scene.h"
#include "MenuScene.h"
#include <cmath>

Player::Player(SDL_Renderer* renderer)
    : GameObject(renderer, new Vector2int(0, 0), new Vector2int(30, 40)), velocity(0, 0), speed(100.0f), rotationSpeed(180.0f)
{
    position = Vector2(1920/2, 1080/2);  // posición inicial, cambia si quieres
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

    if (!canShoot) {
        shootCooldown -= dt;
        if (shootCooldown <= 0.0f) {
            canShoot = true;
            shootCooldown = 0.0f;
        }
    }

    if (isDead) {
        deathTimer -= dt;
        if (deathTimer <= 0) {
            if (lives > 0) {
                Reset();
            }
        }
        return;
    }
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    velocity.x *= 0.98f;
    velocity.y *= 0.98f;

    // Reaparición en pantalla (ajusta según tamaño ventana)
    if (position.x < 0) position.x += 600;
    else if (position.x > 600) position.x -= 600;

    if (position.y < 0) position.y += 600;
    else if (position.y > 600) position.y -= 600;
}

void Player::Reset() {
    isDead = false;
    position = Vector2(300, 300);
}
