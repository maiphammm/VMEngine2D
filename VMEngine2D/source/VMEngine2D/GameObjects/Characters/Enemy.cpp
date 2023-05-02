#include "VMEngine2D/GameObjects/Characters/Enemy.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"

Enemy::Enemy(Vector2 StartPosition, SDL_Renderer* Renderer)
	: Character(StartPosition)
{
	Tag = "Enemy";
	Scale = 1.5f;
	
	Rotation = 180.0;

	MovementDir = Vector2(0.0f, 1.0f);
	Physics->MaxVelocity = 100.0f;

	Collision->Dimensions.Height = 55.0f;
	Collision->Dimensions.Width = 55.0f;

	Collision->Dimensions.Offset = Vector2(20.0f, 20.0f);

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


void Enemy::Update()
{
	//call to the parent function
	Character::Update();

	//move velocity down
	Physics->AddForce(MovementDir, 10000.0f);

	//teleport the enemy back up if they reach the bottom of the screen
	if (Position.y > 540.0f) {
		Position.y = -64.0f * Scale;
	}

	//check if Lives are 0
	if (GetLives() == 0) {
		Game::GetGameInstance().GameScore += 100;
		//destroy self if 0
		this->DestroyGameObject();
	}
}

void Enemy::Draw(SDL_Renderer* Renderer)
{
	//draw the boosters
	CharacterAnimations->Draw(Renderer, EnemyEnims::BOOSTERS, Position, Rotation, Scale, bFlipped);

	//draw the main ship
	Character::Draw(Renderer);
}
