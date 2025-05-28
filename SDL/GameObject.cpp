#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer, Vector2int* _textureCoor, Vector2int* _size) {

	position = Vector2(50, 50);
	zRotation = 0.f;
	scale = Vector2(1.f, 1.f);

	textureCoor = *_textureCoor;
	size = *_size;

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
	zRotation += 90 * dt;
}

void GameObject::Render(SDL_Renderer* renderer) {
	SDL_Rect source{
			textureCoor.x,
			textureCoor.y,
			size.x,
			size.y
	};
	SDL_Rect destination{
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(source.w * scale.x),
		static_cast<int>(source.h * scale.y)
	};

	SDL_RenderCopyEx(renderer, texture, &source, &destination, zRotation, nullptr, SDL_FLIP_NONE);
}
