#pragma once
#include "Scene.h"

class GameplayScene : public Scene {
public:
	GameplayScene()
		: Scene() {
	}

	void Start(SDL_Renderer* rend) override;
	void Update(float dt) override;
	void Render(SDL_Renderer* rend) override;
	void Exit()override;
};