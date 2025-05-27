#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Scene.h"

class GameplayScene : public Scene {
private:
    Player* player;
    std::vector<Bullet*> bullets;
    std::vector<Asteroid*> asteroids;
    int wave = 1;
    SDL_Renderer* renderer = nullptr;

public:
    void Start(SDL_Renderer* rend) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* rend) override;
    void Exit() override;
    void SpawnAsteroids(int count);
};
