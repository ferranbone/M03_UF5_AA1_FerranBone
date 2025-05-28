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
    if (!texture) return;

    // Rectángulo fuente del sprite sheet
    SDL_Rect srcRect = {
        textureCoor.x,
        textureCoor.y,
        size.x,
        size.y
    };

    // Rectángulo destino en pantalla (aplicando escala)
    int scaledWidth = static_cast<int>(size.x * scale.x);
    int scaledHeight = static_cast<int>(size.y * scale.y);

    SDL_Rect destRect = {
        static_cast<int>(position.x - scaledWidth / 2),
        static_cast<int>(position.y - scaledHeight / 2),
        scaledWidth,
        scaledHeight
    };

    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, zRotation, nullptr, SDL_FLIP_NONE);
}
