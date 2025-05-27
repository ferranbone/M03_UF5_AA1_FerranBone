#pragma once
#include "Scene.h"

class HighscoresScene : public Scene {
public:
	HighscoresScene()
		: Scene() {
	}

	void Start(SDL_Renderer* rend) override;
	void Update(float dt) override;
	void Render(SDL_Renderer* rend) override;
	void Exit()override;
};