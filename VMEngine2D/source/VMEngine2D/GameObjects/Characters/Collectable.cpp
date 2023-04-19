#include "VMEngine2D/GameObjects/Characters/Collectable.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"

Collectable::Collectable(Vector2 StartPosition, SDL_Renderer* Renderer)
	: Character(StartPosition)
{
	Tag = "Collectable";
	Scale = 1.0f;

	Rotation = 0.0;

	MovementDir = Vector2(0.0f, 1.0f);

	STAnimationData AnimData = STAnimationData();


	//set the AnimData for the booster animation
	AnimData.FPS = 24;
	AnimData.MaxFrames = 15;
	AnimData.EndFrame = 14;

	//Add the booster animation to AnimState - 1
	AddAnimation(Renderer,
		"Content/Images/Pickup/EngineEffects/Pickup Icon - Shield Generator - Invincibility Shield.png",
		AnimData);

}


void Collectable::Update()
{
	//call to the parent function
	Character::Update();

	//move velocity down
	Physics->AddForce(MovementDir, 10000.0f);

	//teleport the collectable back up if they reach the bottom of the screen
	if (Position.y > 540.0f) {
		Position.y = -64.0f * Scale;
	}
}

void Collectable::Draw(SDL_Renderer* Renderer)
{
	//draw the main collectable
	Character::Draw(Renderer);
}
