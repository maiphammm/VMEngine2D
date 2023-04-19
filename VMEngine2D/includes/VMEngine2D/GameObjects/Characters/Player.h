#pragma once
#include "VMEngine2D/GameObjects/Character.h"

enum PlayerAnims : unsigned int {
	BASE_FULL = 0,
	ENGINE_SUPER = 1,
	BOOSTERS_IDLE = 2,
	BOOSTERS_POWER = 3
};

class Player :
	public Character {
public:
	Player(Vector2 StartPosition, SDL_Renderer* Renderer);

	virtual void ProcessInput(Input* PlayerInput) override;

	virtual void Update() override;

	virtual void Draw(SDL_Renderer* Renderer) override;

	
protected:
	//Play the correct animation for the boosters
	unsigned int BoostersIndex;

};
