#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Utils.h"

class GameObject {
public:
	GameObject(SDL_Renderer* renderer, Vector2int* _textureCoor, Vector2int* _size);

	virtual void Update(float dt);
	void Render(SDL_Renderer* renderer);



	Vector2 position;
	Vector2 scale;
	float zRotation;

	SDL_Texture* texture;

protected:
	Vector2int size;
	Vector2int textureCoor;
};