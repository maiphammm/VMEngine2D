#include "VMEngine2D/GameObjects/Projectile.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameState.h"
#include "VMEngine2D/GameObjects/Character.h"

Projectile::Projectile()
{
	DeathTimer = 10.0f;
	Acceleration = 1000.0f;
	Direction = Vector2::Zero();
	Rotation = 0.0;
	Scale = 1.0f;
	TargetTag = "";

	Animations = new AnimStateMachine();

	Collision = new CollisionComponent(this);
	Collision->Dimensions.Position = Position;
	Collision->Dimensions.Width = 25.0f;
	Collision->Dimensions.Height = 25.0f;

	Physics = new PhysicsComponent(this);
	Physics->MaxVelocity = 1000.0f;
	Physics->Drag = 1.0f;

	STAnimationData AnimData;
	AnimData.MaxFrames = 10;
	AnimData.EndFrame = 9;
	AnimData.StartFrame = 0;
	AnimData.FPS = 24;

	SDL_Renderer* R = Game::GetGameInstance().GetGameState()->GetCurrentState()->GetRenderer();

	Animations->AddAnimation(R, "Content/Images/MainShip/Projectile/Projectile - Big Space Gun.png",
		AnimData);
}

Projectile::~Projectile()
{
	//remove the animations
	delete Animations;

	Animations = nullptr;
}

void Projectile::Update()
{
	GameObject::Update();

	//move the projectile constant in a direction
	Physics->AddForce(Direction, Acceleration); 

	//check iif we are overlapping a collider with the target tag
	if (Collision->IsOverlappingTag(TargetTag)) {
		//oop through all targets
		for (CollisionComponent* Target : Collision->GetOverlappedByTag(TargetTag)) {
			//remove 1 life from characters and destroy sefl
			if (Target->GetOwner()->ShouldDestroy()) {
				dynamic_cast<Character*>(Target->GetOwner())->RemoveLives(1);
				this->DestroyGameObject();
			}
		}
	}
}

void Projectile::Draw(SDL_Renderer* Renderer)
{
	GameObject::Draw(Renderer);

	//draw the projectile spritesheet to the screen
	Animations->Draw(Renderer, 0, Position, Rotation, Scale, false);
}
