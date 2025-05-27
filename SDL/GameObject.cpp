#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer) {

	position = Vector2(50, 50);
	zRotation = 0.f;
	scale = Vector2(1.f, 1.f);

	//LOAD TEXTURE
	SDL_Surface* surf = IMG_Load("resources/asteroids_spritesheet.png");
	if (surf == nullptr) {
		std::cout << "Error al cargar la surface:" << SDL_GetError();
	}

	texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr) {
		std::cout << "Error al cargar la textura:" << SDL_GetError();
	}

	SDL_FreeSurface(surf);
}

void GameObject::Update(float dt) {
	zRotation = 10 * dt;
}

void GameObject::Render(SDL_Renderer* renderer) {
	SDL_Rect source{ 0,0,		// TEXTURE POSITION
					30,40 };	//TEXTURE SIZE
	
	SDL_Rect destination{ position.x,position.y,		//WINDOW POSITION
				source.w*scale.x,source.h *scale.y };	//WINDOW SIZE

	SDL_RenderCopy(renderer, texture, &source, &destination);
}