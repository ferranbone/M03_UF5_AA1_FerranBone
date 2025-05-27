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
                if (asteroids[j]->size == LARGE) {
                    asteroids.push_back(new Asteroid(renderer, asteroids[j]->position, MEDIUM));
                    asteroids.push_back(new Asteroid(renderer, asteroids[j]->position, MEDIUM));
                } else if (asteroids[j]->size == MEDIUM) {
                    asteroids.push_back(new Asteroid(renderer, asteroids[j]->position, SMALL));
                    asteroids.push_back(new Asteroid(renderer, asteroids[j]->position, SMALL));
                }
                delete asteroids[j];
                asteroids.erase(asteroids.begin() + j);
                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                break;
            }
        }
    }

    // Muerte del jugador
    for (auto a : asteroids) {
        float dx = a->position.x - player->position.x;
        float dy = a->position.y - player->position.y;
        if (sqrt(dx * dx + dy * dy) < 20.0f) {
            targetScene = "MainMenu";
            isFinished = true;
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
}

void GameplayScene::SpawnAsteroids(int count) {
    for (int i = 0; i < count; ++i) {
        Vector2 pos(rand() % 500, rand() % 500);
        asteroids.push_back(new Asteroid(renderer, pos, LARGE));
    }
}

void GameplayScene::Exit() {
    delete player;
    for (auto b : bullets) delete b;
    for (auto a : asteroids) delete a;
    bullets.clear();
    asteroids.clear();
}
