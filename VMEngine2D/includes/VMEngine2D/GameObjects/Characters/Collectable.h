#pragma once
#include "VMEngine2D/GameObjects/Character.h"


class Collectable :
	public Character {
public:
	Collectable(Vector2 StartPosition, SDL_Renderer* Renderer);
	virtual ~Collectable() {}

	virtual void Update() override;

	virtual void Draw(SDL_Renderer* Renderer) override;

};