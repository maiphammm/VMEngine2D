#include "VMEngine2D/GameObjects/Character.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"
#include <iostream>

using namespace std;

Character::Character(Vector2 StartPosition)
{
	CharacterAnimations = new AnimStateMachine();
	AnimIndex = 0;
	bFlipped = false;
	Position = StartPosition;
	bOverlapDetected = false;
	bDebugCollision = false;

	//create a new physics component and store it
	Physics = new PhysicsComponent(this);

	//creat a new Collision component and store it
	Collision = new CollisionComponent(this);

	//resize the collision custom to the object
	Collision->Dimensions.Width = 150.0f;
	Collision->Dimensions.Height = 150.0f;

	//make sure nothing is dead on spawn
	Lives = 1;

	cout << "Character created." << endl;
}

Character::~Character()
{
	//remove the anim state machine from memory
	delete CharacterAnimations;
	cout << "Character Destroyed." << endl;
}

void Character::Update()
{
	//run the parent class update first
	GameObject::Update();
}

void Character::Draw(SDL_Renderer* Renderer)
{
	//draw the animations for the character
	CharacterAnimations->Draw(Renderer, AnimIndex, Position, Rotation, Scale, bFlipped);

	//if we have the debug set to true show the collider
	if (bDebugCollision) {
		//draw the collision
		if (bOverlapDetected) {
			SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255); // this will draw green
		}
		else {
			SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255); // this will draw red
		}

		//convert Dimensions into an SDL_Frect
		SDL_FRect ColRect = {
			Collision->Dimensions.Position.x,
			Collision->Dimensions.Position.y,
			Collision->Dimensions.Width,
			Collision->Dimensions.Height
		};

		//Draw the collider
		SDL_RenderDrawRectF(Renderer, &ColRect);

	}
		
}

void Character::AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData)
{
	//Add an animation to anim state machine using the anim scale machine function
	CharacterAnimations->AddAnimation(Renderer, SpriteSheetPath, AnimationData);
}

void Character::AddLives(int Amount)
{
	//clamping amount at a minimum value of 0
	Amount = max(0, Amount);

	//adding the amount to our current lives
	Lives += Amount;
}

void Character::RemoveLives(int Amount)
{
	//creating a temp lives varriable that can be negative
	int NewLives = Lives - Amount;

	//clamping the value to 0 if the number is negative
	NewLives = max(0, NewLives);

	//set the lives to the new value
	Lives = NewLives;
}
