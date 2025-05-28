#include "GameplayScene.h"
#include "MenuScene.h"

void GameplayScene::Start(SDL_Renderer* rend) {
    Scene::Start(rend);
    renderer = rend;
    player = new Player(renderer);
    objects.push_back(player);
    SpawnAsteroids(wave);
}

void GameplayScene::Update(float dt) {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    player->HandleInput(keystates, bullets, renderer);

    if (keystates[SDL_SCANCODE_SPACE]) {
        bullets.push_back(new Bullet(renderer, player->position, player->zRotation));
    }

    for (auto b : bullets) b->Update(dt);
    for (auto a : asteroids) a->Update(dt);
    player->Update(dt);

    // Colisiones
    for (int i = 0; i < bullets.size(); ++i) {
        for (int j = 0; j < asteroids.size(); ++j) {
            float dx = bullets[i]->position.x - asteroids[j]->position.x;
            float dy = bullets[i]->position.y - asteroids[j]->position.y;
            if (sqrt(dx * dx + dy * dy) < 20.0f) {
                Vector2 parentPos = asteroids[j]->position;
                Vector2 parentVel = asteroids[j]->velocity;
                AsteroidSize parentSize = asteroids[j]->asteroidSize;

                // Eliminar asteroide actual
                delete asteroids[j];
                asteroids.erase(asteroids.begin() + j);

                // Eliminar bala
                delete bullets[i];
                bullets.erase(bullets.begin() + i);

                // Spawn nuevos asteroides según tamaño
                if (parentSize == LARGE) {
                    asteroids.push_back(new Asteroid(renderer, parentPos, parentVel, MEDIUM));
                    asteroids.push_back(new Asteroid(renderer, parentPos, parentVel, MEDIUM));
                }
                else if (parentSize == MEDIUM) {
                    asteroids.push_back(new Asteroid(renderer, parentPos, parentVel, SMALL));
                    asteroids.push_back(new Asteroid(renderer, parentPos, parentVel, SMALL));
                }

                break;
            }
        }
    }

    // Muerte del jugador
    for (auto a : asteroids) {
        float dx = a->position.x - player->position.x;
        float dy = a->position.y - player->position.y;
        if (sqrt(dx * dx + dy * dy) < 20.0f && !player->isDead) {
            player->lives--;
            player->isDead = true;
            player->deathTimer = player->DEATH_ANIMATION_TIME;
            break;
        }
    }

    // Eliminar balas viejas
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet* b) {
        return b->lifetime <= 0;
    }), bullets.end());

    // Nueva oleada
    if (asteroids.empty()) {
        ++wave;
        SpawnAsteroids(wave);
    }
}

void GameplayScene::Render(SDL_Renderer* rend) {
    for (auto b : bullets) b->Render(rend);
    for (auto a : asteroids) a->Render(rend);
    player->Render(rend);
    RenderHUD(rend);
}

void GameplayScene::RenderHUD(SDL_Renderer* rend) {
    SDL_Color white = { 255, 255, 255, 255 };
    for (int i = 0; i < player->lives; i++) {
        SDL_Rect lifeRect = { 10 + i * 30, 10, 20, 20 };  // Iconos de vida
        SDL_SetRenderDrawColor(rend, white.r, white.g, white.b, white.a);
        SDL_RenderFillRect(rend, &lifeRect);
    }
}

void GameplayScene::SpawnAsteroids(int count) {
    for (int i = 0; i < count; ++i) {
        asteroids.push_back(new Asteroid(renderer, LARGE));
    }
}

void GameplayScene::Exit() {
    delete player;
    for (auto b : bullets) delete b;
    for (auto a : asteroids) delete a;
    bullets.clear();
    asteroids.clear();
}