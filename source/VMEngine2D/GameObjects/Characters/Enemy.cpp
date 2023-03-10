#include "VMEngine2D/GameObjects/Characters/Enemy.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Game.h"

Enemy::Enemy(Vector2 StartPosition, SDL_Renderer* Renderer)
	: Character(StartPosition)
{
	Scale = 3.0f;
	Direction = Vector2(0.0f, 1.0f);
	Rotation = 180.0;

	STAnimationData AnimData = STAnimationData();
	AnimData.FPS = 0;

	//Add the ship base as the main sprite to AnimState - 0
	AddAnimation(Renderer,
		"Content/Images/Naran/Base/Nairan - Bomber - Base.png",
		AnimData);

	//set the AnimData for the booster animation
	AnimData.FPS = 24;
	AnimData.MaxFrames = 8;
	AnimData.EndFrame = 7;

	//Add the booster animation to AnimState - 1
	AddAnimation(Renderer,
		"Content/Images/Naran/EngineEffects/Nairan - Bomber - Engine.png",
		AnimData);

}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//get the full movement direction
	Vector2 MoveDir = Direction * MaxMoveSpeed;

	//set the direction based on input and move speed
	Position += MoveDir * Game::GetGameInstance().GetFDeltaTime();

	//teleport the enemy back up if they reach the bottom of the screen
	if (Position.y > 540.0f) {
		Position.y = -64.0f * Scale;
	}
}

void Enemy::Draw(SDL_Renderer* Renderer)
{
	//draw the boosters
	CharacterAnimations->Draw(Renderer, EnemyEnims::BOOSTERS, Position, Rotation, Scale, bFlipped);

	//draw the main ship
	Character::Draw(Renderer);

}
