#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Vector2 {
public:
	float x;
	float y;

	Vector2() { x = 0; y = 0; }
	Vector2(float _x, float _y) { x = _x; y = _y; }

	Vector2 operator +(Vector2& other) {
		return Vector2(x + other.x, y + other.y);
	}
};

class GameObject {
public:
	GameObject(SDL_Renderer* renderer);

	void Update(float dt);
	void Render(SDL_Renderer* renderer);



	Vector2 position;
	Vector2 scale;
	float zRotation;

	SDL_Texture* texture;

};