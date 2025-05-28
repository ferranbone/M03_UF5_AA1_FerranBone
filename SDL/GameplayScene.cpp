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

    if (keystates[SDL_SCANCODE_SPACE] && player->canShoot) {
        bullets.push_back(new Bullet(renderer, player->position, player->zRotation));
        player->canShoot = false;
        player->shootCooldown = player->SHOOT_COOLDOWN_TIME;
    }

    for (auto b : bullets) b->Update(dt);
    for (auto a : asteroids) a->Update(dt);
    player->Update(dt);

    if (player->isDead && player->lives <= 0 && player->deathTimer <= 0) {
        targetScene = "MenuScene";
        isFinished = true;
        return;
    }

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
                    score += 50;
                    asteroids.push_back(new Asteroid(renderer, parentPos, parentVel, MEDIUM));
                    asteroids.push_back(new Asteroid(renderer, parentPos, parentVel, MEDIUM));
                }
                else if (parentSize == MEDIUM) {
                    score += 30;
                    asteroids.push_back(new Asteroid(renderer, parentPos, parentVel, SMALL));
                    asteroids.push_back(new Asteroid(renderer, parentPos, parentVel, SMALL));
                }
                else {
                    score += 20;
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
    // Spawn de enemigos
    enemySpawnTimer += dt;
    if (enemySpawnTimer >= ENEMY_SPAWN_TIME) {
        SpawnEnemy();
        enemySpawnTimer = 0.0f;
    }

    // Actualizar enemigos
    for (auto e : enemies) {
        e->Update(dt);
    }

    // Colisión enemigo-asteroide
    for (auto e = enemies.begin(); e != enemies.end(); ) {
        bool enemyDestroyed = false;

        for (auto a = asteroids.begin(); a != asteroids.end(); ) {
            if (CheckCollision(*e, *a)) {
                // Romper asteroide
                if ((*a)->asteroidSize == LARGE) {
                    asteroids.push_back(new Asteroid(renderer, (*a)->position, (*a)->velocity, MEDIUM));
                    asteroids.push_back(new Asteroid(renderer, (*a)->position, (*a)->velocity, MEDIUM));
                }
                else if ((*a)->asteroidSize == MEDIUM) {
                    asteroids.push_back(new Asteroid(renderer, (*a)->position, (*a)->velocity, SMALL));
                    asteroids.push_back(new Asteroid(renderer, (*a)->position, (*a)->velocity, SMALL));
                }

                delete* a;
                a = asteroids.erase(a);
                enemyDestroyed = true;
                break;
            }
            else {
                ++a;
            }
        }

        if (enemyDestroyed) {
            delete* e;
            e = enemies.erase(e);
        }
        else {
            ++e;
        }
    }

    // Colisión enemigo-jugador
    for (auto e = enemies.begin(); e != enemies.end(); ) {
        if (CheckCollision(*e, player) && !player->isDead) {
            player->lives--;
            player->isDead = true;
            player->deathTimer = player->DEATH_ANIMATION_TIME;

            delete* e;
            e = enemies.erase(e);
        }
        else {
            ++e;
        }
    }

    // Colisión enemigo-bala
    for (auto b = bullets.begin(); b != bullets.end(); ) {
        bool bulletDestroyed = false;

        for (auto e = enemies.begin(); e != enemies.end(); ) {
            if (CheckCollision(*b, *e)) {
                delete* e;
                e = enemies.erase(e);
                bulletDestroyed = true;
                score += 150;
                break;
            }
            else {
                ++e;
            }
        }

        if (bulletDestroyed) {
            delete* b;
            b = bullets.erase(b);
        }
        else {
            ++b;
        }
    }

}

void GameplayScene::Render(SDL_Renderer* rend) {
    for (auto b : bullets) b->Render(rend);
    for (auto a : asteroids) a->Render(rend);
    player->Render(rend);
    RenderHUD(rend);
    for (auto e : enemies) {
        e->Render(rend);
    }
}

void GameplayScene::RenderHUD(SDL_Renderer* rend) {
    SDL_Color white = { 255, 255, 255, 255 };
    for (int i = 0; i < player->lives; i++) {
        SDL_Rect lifeRect = { 10 + i * 30, 10, 20, 20 };
        SDL_SetRenderDrawColor(rend, white.r, white.g, white.b, white.a);
        SDL_RenderFillRect(rend, &lifeRect);
    }

    TTF_Font* font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);
    if (font) {
        std::string scoreText = "Score: " + std::to_string(score);
        SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), white);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surface);

        SDL_Rect dstRect = { 10, 40, surface->w, surface->h };
        SDL_RenderCopy(rend, texture, nullptr, &dstRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
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
    for (auto e : enemies) {
        delete e;
    }
    enemies.clear();
}

void GameplayScene::SpawnEnemy() {
    Vector2 spawnPos;
    int edge = rand() % 4;
    switch (edge) {
    case 0: spawnPos = Vector2(rand() % 600, -50); break;
    case 1: spawnPos = Vector2(590, rand() % 600); break;
    case 2: spawnPos = Vector2(rand() % 600, 700); break;
    case 3: spawnPos = Vector2(-50, rand() % 600); break;
    }

    enemies.push_back(new Enemy(renderer, spawnPos));
}

bool GameplayScene::CheckCollision(GameObject* a, GameObject* b) {
    if (!a || !b) return false;

    float dx = a->position.x - b->position.x;
    float dy = a->position.y - b->position.y;
    float distanceSquared = dx * dx + dy * dy;

    float collisionDistance = 25.0f;
    float collisionDistanceSquared = collisionDistance * collisionDistance;

    return distanceSquared < collisionDistanceSquared;
}