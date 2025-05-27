#include "GameplayScene.h"

void GameplayScene::Start(SDL_Renderer* rend) {
	Scene::Start(rend);
	objects.push_back(new GameObject(rend));
}

void GameplayScene::Update(float dt) {
	Scene::Update(dt);
}

void GameplayScene::Render(SDL_Renderer* rend) {
	Scene::Render(rend);
}

void GameplayScene::Exit() {
	for (int i = 0; i < objects.size(); i++)
	{
		delete(objects[i]);
	}
	objects.clear();
}